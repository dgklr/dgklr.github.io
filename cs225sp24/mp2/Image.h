#ifndef __IMAGE_H
#define __IMAGE_H
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
namespace cs225 {
    class Image : public PNG {
    public:
        void lighten(double amount=0.1);
        void darken(double amount=0.1);
        void saturate(double amount=0.1);
        void desaturate(double amount=0.1);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);
    };
}
#endif