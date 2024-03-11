#include "Image.h"
#include <cmath>

namespace cs225 {
    void Image::lighten(double amount){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++)
                this -> getPixel(i, j) -> l = min(1.0, this -> getPixel(i, j) -> l + amount);

    }
    void Image::darken(double amount){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++)
                this -> getPixel(i, j) -> l = max(0.0, this -> getPixel(i, j) -> l - amount);
    }
    void Image::saturate(double amount){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++)
                this -> getPixel(i, j) -> s = min(1.0, this -> getPixel(i, j) -> s + amount);
    }
    void Image::desaturate(double amount){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++)
                this -> getPixel(i, j) -> s = max(0.0, this -> getPixel(i, j) -> s - amount);
    }
    void Image::grayscale(){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++)
                this -> getPixel(i, j) -> s = 0;
    }
    void Image::rotateColor(double degrees){
        degrees -= 360 * (floor(degrees / 360));
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        for (unsigned int i=0; i<width; i++)
            for (unsigned int j=0; j<height; j++){
                this -> getPixel(i, j) -> h += degrees;
                if (this -> getPixel(i,j) -> h >= 360)
                    this -> getPixel(i,j) -> h -= 360;
            }
    }
    void Image::illinify(){
        double IlliniOrange = 11;
        double IlliniBlue = 216;
        for (unsigned x = 0; x < this -> width(); x++) {
                for (unsigned y = 0; y < this -> height(); y++) {
                HSLAPixel *pixel = this -> getPixel(x, y);
                double minO, minB;
                if (pixel -> h > IlliniOrange) {
                    minO = std::min(pixel -> h - IlliniOrange, IlliniOrange + 360 - pixel -> h);
                } else {
                    minO = std::min(-pixel -> h + IlliniOrange, -IlliniOrange + 360 + pixel -> h);
                }
                if (pixel -> h > IlliniBlue) {
                    minB = std::min(pixel -> h - IlliniBlue, IlliniBlue + 360 - pixel -> h);
                } else {
                    minB = std::min(-pixel -> h + IlliniBlue, -IlliniBlue + 360 + pixel -> h);
                }
                if (minB > minO) {
                    pixel -> h = IlliniOrange;
                } else {
                    pixel -> h = IlliniBlue;
                }
            }
        }

    }
    void Image::scale(double factor){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        PNG tmp(this -> width() * factor, this -> height() * factor);

        for (unsigned int i=0; i<tmp.width(); i++)
            for (unsigned int j=0; j<tmp.height(); j++) {
                HSLAPixel* now = tmp.getPixel(i, j);
                HSLAPixel* from = this -> getPixel((double)i / tmp.width() * width, (double)j / tmp.height() * height);
                now->h = from->h;
                now->s = from->s;
                now->l = from->l;
                now->a = from->a;
            }
        this -> resize(this -> width() * factor, this -> height() * factor);
        
        for (unsigned int i=0; i<this -> width(); i++)
            for (unsigned int j=0; j<this -> height(); j++) {
                HSLAPixel* from = tmp.getPixel(i, j);
                HSLAPixel* now = this -> getPixel(i, j);
                now->h = from->h;
                now->s = from->s;
                now->l = from->l;
                now->a = from->a;
            }
    }
    void Image::scale(unsigned w, unsigned h){
        unsigned int width = this -> width();
        unsigned int height = this -> height();
        if ((double) w / width > (double) h / height) w = (double)h * width / height;
        else h = (double)w * height / width;

        PNG tmp(w, h);

        for (unsigned int i=0; i<tmp.width(); i++)
            for (unsigned int j=0; j<tmp.height(); j++) {
                HSLAPixel* now = tmp.getPixel(i, j);
                HSLAPixel* from = this -> getPixel((double)i / tmp.width() * width, (double)j / tmp.height() * height);
                now->h = from->h;
                now->s = from->s;
                now->l = from->l;
                now->a = from->a;
            }
        this -> resize(w, h);
        
        for (unsigned int i=0; i<this -> width(); i++)
            for (unsigned int j=0; j<this -> height(); j++) {
                HSLAPixel* from = tmp.getPixel(i, j);
                HSLAPixel* now = this -> getPixel(i, j);
                now->h = from->h;
                now->s = from->s;
                now->l = from->l;
                now->a = from->a;
            }
    }
}