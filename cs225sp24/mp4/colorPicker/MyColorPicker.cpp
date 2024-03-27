#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <random>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
    static double h = rand() % 360, s = (double)rand()/RAND_MAX, l = (double)rand()/RAND_MAX;
    h += rand()%9 - 4;
    if (h > 360) h -= 360;
    if (h < 0) h += 360;
    s *= (1 + (double)(rand()-RAND_MAX/2)/RAND_MAX/100);
    l *= (1 + (double)(rand()-RAND_MAX/2)/RAND_MAX/100);
    if (s < 0) s = 0; 
    if (s > 1) s = 1;
    if (l < 0) l = 0;
    if (l > 1) l = 1;
    /*
    if (s >= 0.5) s *= (1 - (double)(rand())/RAND_MAX/100);
    if (s <= 0.5) s *= (1 + (double)(rand())/RAND_MAX/100);
    if (l >= 0.5) l *= (1 - (double)(rand())/RAND_MAX/100);
    if (l <= 0.5) l *= (1 + (double)(rand())/RAND_MAX/100);*/
  return HSLAPixel(h, s, l);
}
