#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);
  MyColorPicker (int randnum, double H, double S, double L)
    {srand(randnum);h = _h = H; s = _s = S; l = _l = L;}
private:
  double _h, _s, _l;
  double h, s, l;
};

#endif
