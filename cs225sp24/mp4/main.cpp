
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {
  PNG png;      png.readFromFile("tests/i.png");
  PNG expected; expected.readFromFile("tests/i-rainbow-bfs.png");
  PNG expected2; expected2.readFromFile("tests/i-rainbow-bfs-2.png");
  
  FloodFilledImage image(png);
  BFS bfs(png, Point(13, 13), 0.05);
  int veryGoodRandomNumbers[] = {1711524937, 1711525016, 1711525037, 1711525287};
  int size = 4;
  MyColorPicker my(veryGoodRandomNumbers[time(0) % size]);
  image.addFloodFill( bfs, my );

  Animation animation = image.animate(1000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );

  DFS dfs(lastFrame, Point(0, 0), 0.05);
    FloodFilledImage image2(lastFrame);
  image2.addFloodFill( dfs, my );
  Animation animation2 = image2.animate(1000);
    PNG lastFrame2 = animation2.getFrame(animation2.frameCount() - 1);
  lastFrame2.writeToFile("myFloodFill.png");

    return 0;
}
