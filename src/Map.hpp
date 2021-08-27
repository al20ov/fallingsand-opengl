#include <stdint.h>

typedef unsigned char byte;

struct Pixel {
  byte r;
  byte g;
  byte b;

  const inline bool operator==(const Pixel& other) const {
    // TODO: change this to memcmp
    return r == other.r and g == other.g and b == other.b;
  }
};

enum PixelType {
  AIR,
  SAND,
  STONE
};

const Pixel pixelTypes[] = {
  { 0x17, 0x24, 0x63 }, // AIR
  { 0xf0, 0xb0, 0x42 }, // SAND
  { 0x48, 0x48, 0x48 }  // STONE
};

class Map
{
  public:
  // static const int mapWidth = 128;
  // static const int mapHeight = 128;
  static const int mapWidth = 160;
  static const int mapHeight = 90;

  Map();
  ~Map();

  Pixel *getMap();
  void paintPixel(int windowWidth, int windowHeight, double mouseX, double mouseY, PixelType pixel);
  void computePhysics();

  private:
  void _setPixel(uint32_t x, uint32_t y, PixelType type);

  uint32_t _coordsToIndex(uint32_t x, uint32_t y);
  void _indexToCoords(uint32_t index, uint32_t &x, uint32_t &y);

  bool _isOutOfBounds(uint32_t x, uint32_t y);
  bool _isPixelFree(uint32_t x, uint32_t y);

  void _computeSandPhysics(uint32_t i);

  Pixel _map[Map::mapWidth * Map::mapHeight];
};
