#include <stdint.h>

typedef unsigned char byte;

typedef struct {
  byte r;
  byte g;
  byte b;
} Pixel;

enum PixelType {
  AIR,
  SAND
};

const Pixel pixelTypes[] = {
  { 0xb2, 0xee, 0xff }, // AIR
  { 0xe3, 0xb5, 0x2e }  // SAND
};

class Map
{
  public:
  static const int mapWidth = 160;
  static const int mapHeight = 90;

  Map();
  ~Map();

  Pixel *getMap();
  void paintPixel(int windowWidth, int windowHeight, double mouseX, double mouseY);
  void computePhysics();

  private:
  void _setPixel(uint32_t x, uint32_t y, const Pixel &pixel);

  uint32_t _coordsToIndex(uint32_t x, uint32_t y);
  void _indexToCoords(uint32_t index, uint32_t &x, uint32_t &y);

  Pixel _map[Map::mapWidth * Map::mapHeight];
};
