#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "mp1.h"

void rotate(std::string inputFile, std::string outputFile) {
    cs225::PNG image;
    image.readFromFile(inputFile);
    for (unsigned x = 0; x < image.width() / 2; x++) {
        for (unsigned y = 0; y < image.height(); y++) {
            HSLAPixel *pixel1 = image.getPixel(x, y);
            HSLAPixel *pixel2 = image.getPixel(image.width() - x - 1, y);
            std::swap(pixel1->h, pixel2->h);
            std::swap(pixel1->s, pixel2->s);
            std::swap(pixel1->l, pixel2->l);
            std::swap(pixel1->a, pixel2->a);
        }
    }
    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height() / 2; y++) {
            HSLAPixel *pixel1 = image.getPixel(x, y);
            HSLAPixel *pixel2 = image.getPixel(x, image.height() - y - 1);
            std::swap(pixel1->h, pixel2->h);
            std::swap(pixel1->s, pixel2->s);
            std::swap(pixel1->l, pixel2->l);
            std::swap(pixel1->a, pixel2->a);
        }
    }
    image.writeToFile(outputFile);
}
