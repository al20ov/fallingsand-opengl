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
  static const int mapWidth = 80;
  static const int mapHeight = 45;

  Map();
  ~Map();

  Pixel *getMap();
  void setPixel(int windowWidth, int windowHeight, double mouseX, double mouseY);

  private:
  Pixel _map[Map::mapWidth * Map::mapHeight];
};
