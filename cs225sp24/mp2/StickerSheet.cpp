#include "StickerSheet.h"
#include <cstring>
namespace cs225{
    void StickerSheet::copy(const StickerSheet &rhs){
        // assuming rhs != *this
        clear();
        total = rhs.total;
        base = rhs.base;
        now = rhs.now;
        list = new Image[rhs.total];//(Image*) malloc(rhs.total * sizeof(Image));
        for (unsigned i=0; i<rhs.total; i++)
            list[i] = rhs.list[i];
        //memcpy(list, rhs.list, rhs.total * sizeof(Image));
        x_ = (int*) malloc(rhs.total * sizeof(int));
        memcpy(x_, rhs.x_, rhs.total * sizeof(int));
        y_ = (int*) malloc(rhs.total * sizeof(int));
        memcpy(y_, rhs.y_, rhs.total * sizeof(int));
        deleted_ = (int*) malloc(rhs.total * sizeof(int));
        memcpy(deleted_, rhs.deleted_, rhs.total * sizeof(int));
    }
    void StickerSheet::clear(){
        delete[] list;
        free(x_);
        free(y_);
        free(deleted_);
        list = nullptr;
    }
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        base = picture;
        total = max;
        now = 0;
        list = new Image[max]; //(Image*) malloc(max * sizeof(Image));
        x_ = (int*) malloc(max * sizeof(int));
        y_ = (int*) malloc(max * sizeof(int));
        deleted_ = (int*) malloc(max * sizeof(int));
    }
    StickerSheet::~StickerSheet(){
        clear();
    }
    StickerSheet::StickerSheet(const StickerSheet &other){
        copy(other);
    }
    const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
        if (this == &other) {
            return *this;
        }
        clear();
        copy(other);
        return *this;
    }
    void StickerSheet::changeMaxStickers(unsigned max){
        total = max;
        if (now >= max) now = max;
        Image* tmp = new Image[max];
        for (unsigned int i=0; i<now; i++)
            tmp[i] = list[i];
        delete[] list;
        list = tmp;
        x_ = (int*) realloc(x_, max * sizeof(int));
        y_ = (int*) realloc(y_, max * sizeof(int));
        deleted_ = (int*) realloc(deleted_, max * sizeof(int));
        // If the memory exceeds, let it crash
    }
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        int index = -1;
        for (unsigned int i = 0; i<now; i++) {
            if (deleted_[i] == 1) {
                deleted_[i] = 0;
                index = i;
                break;
            }
        }
        if (now == total && index == -1) return -1;
        if (index == -1) index = now, now ++;
        list[index] = sticker;
        x_[index] = x;
        y_[index] = y;
        deleted_[index] = 0;
        return index;
    }
    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
        if (index >= now) return false;
        if (deleted_[index] == 1) return false;
        x_[index] = x;
        y_[index] = y;
        return true;
    }
    void StickerSheet::removeSticker(unsigned index){
        if (index >= now) return;
        deleted_[index] = 1;
    }
    Image * StickerSheet::getSticker(unsigned index) const{
        if (index > now) return nullptr;
        if (deleted_[index] == 1) return nullptr;
        return list + index;
    }
    Image StickerSheet::render ()const{
        Image ret(base);
        for (unsigned int t = 0; t<now; t++)
            for (unsigned int i=0; i<ret.width(); i++)
                for (unsigned int j=0; j<ret.height(); j++) {
                    if (deleted_[t] == 1) continue;
                    HSLAPixel* to = ret.getPixel(i, j);
                    int px = i - x_[t], py = j - y_[t];
                    if (px < 0 || py < 0 || px >= (int)list[t].width() || py >= (int)list[t].height()) continue;
                    HSLAPixel* from = list[t].getPixel(px, py);
                    if (from -> a == 0) continue;
                    to -> h = from -> h;
                    to -> s = from -> s;
                    to -> l = from -> l;
                    to -> a = from -> a;
                }
        return ret;
    }
}