#include "StickerSheet.h"
#include "Image.h"
using namespace cs225;
int main() {
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");
  i.scale(0.2);

  StickerSheet s(alma, 5);
  s.addSticker(i, 330, 80);
  s.addSticker(i, 430, 30);
  s.addSticker(i, 530, 80);
/*
  s.addSticker(i, 100, 120);
  s.addSticker(i, 120, 140);
  s.addSticker(i, 140, 160);
 // s.removeSticker(3);
  s.addSticker(i, 80, 100);
  s.addSticker(i, 160, 180);
  s.addSticker(i, 180, 200);

  s.changeMaxStickers(1);
  s.changeMaxStickers(10);
  s.addSticker(i, 120, 140);
  s.addSticker(i, 140, 160);
  s.removeSticker(0);
  s.addSticker(i, 80, 100);
  s.addSticker(i, 160, 180);
  s.addSticker(i, 180, 200);
  s.addSticker(i, 120, 140);
  s.addSticker(i, 140, 160);
  s.removeSticker(3);
  s.addSticker(i, 80, 100);
  s.addSticker(i, 160, 180);
  s.addSticker(i, 180, 200);
*/
  s.render().writeToFile("myImage.png");
  return 0;
}
