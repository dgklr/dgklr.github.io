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

  s.render().writeToFile("myImage.png");
  return 0;
}
