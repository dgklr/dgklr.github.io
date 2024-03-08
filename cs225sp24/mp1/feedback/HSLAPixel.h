#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

class HSLAPixel{
public:
    double h, s, l, a;
    HSLAPixel();
    HSLAPixel(double hue, double saturation, double luminance);
    HSLAPixel(double hue, double saturation, double luminance, double alpha);
};

#endif