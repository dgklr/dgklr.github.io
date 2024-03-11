#ifndef __STICKERSHEET_H
#define __STICKERSHEET_H
#include "Image.h"
namespace cs225{
    class StickerSheet{
        private:
            unsigned int total;
            unsigned int now;
            Image* list;
            int* x_;
            int* y_;
            int* deleted_;
            Image base;
            void copy(const StickerSheet &rhs);
            void clear();
        public:
            StickerSheet(const Image &picture, unsigned max);
            ~StickerSheet();
            StickerSheet(const StickerSheet &other);
            const StickerSheet &operator=(const StickerSheet &other);
            void changeMaxStickers(unsigned max);
            int addSticker(Image &sticker, unsigned x, unsigned y);
            bool translate(unsigned index, unsigned x, unsigned y);
            void removeSticker(unsigned index);
            Image * getSticker(unsigned index) const;
            Image render ()const;
    };
}
#endif