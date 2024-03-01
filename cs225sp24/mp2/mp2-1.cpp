#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {
  /*
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");
  
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");
*/
  Image alma;
  alma.readFromFile("tests/alma.png");

  Image i;
  i.readFromFile("tests/i.png");
  Image i2;
  i2.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 30, 220);
  sheet.addSticker(i, 40, 250);
  sheet.addSticker(i, 50, 270);
  sheet.addSticker(i, 60, 250);
  sheet.addSticker(i, 70, 270);

  Image expected;
  expected.readFromFile("tests/expected.png");

  sheet.render().writeToFile("final.png");
  return 0;
}