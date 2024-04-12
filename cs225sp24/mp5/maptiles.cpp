/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

Point<3> convert(HSLAPixel pixel) {
    return Point<3>(pixel.h / 360, pixel.s, pixel.l);
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    vector < Point<3> > pt;
    map <Point<3>, vector<TileImage>::iterator> m;
    for (auto i = theTiles.begin(); i != theTiles.end(); i ++) {
        pt.push_back(convert(i->getAverageColor()));
        m[convert(i->getAverageColor())] = i;
    }
    
    KDTree<3> tree(pt);

    auto ret = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    for (int i = 0; i < theSource.getRows(); i ++) {
        for (int j = 0; j < theSource.getColumns(); j ++) {
            ret -> setTile(i, j, &*m[tree.findNearestNeighbor(convert(theSource.getRegionColor(i, j)))]);
        }
    }

    return ret;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
