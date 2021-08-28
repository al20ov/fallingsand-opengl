#include <stdint.h>
#include <array>

typedef unsigned char byte;

enum ParticleType {
  AIR,
  SAND,
  STONE
};

struct Color {
  byte r, g, b;
};

class Particle {
  public:
  Particle(ParticleType type);
  Particle();

  const inline bool operator==(const Particle& other) const {
    return this->_type == other._type;
  }
  ParticleType _type;
};

const Particle particleTypes[] = {
  Particle(AIR),
  Particle(SAND),
  Particle(STONE),
};

const Color particleColors[][4] = {
  {
    { 0x17, 0x24, 0x63 },
    { 0x17, 0x24, 0x63 },
    { 0x17, 0x24, 0x63 },
    { 0x17, 0x24, 0x63 },
  },
  {
    { 0xf0, 0xb0, 0x42 },
    { 0xf2, 0xb5, 0x4e },
    { 0xed, 0xaa, 0x36 },
    { 0xf0, 0xa4, 0x42 },
  },
  {
    { 0x6d, 0x6d, 0x6d },
    { 0x63, 0x63, 0x63 },
    { 0x73, 0x73, 0x73 },
    { 0x76, 0x6d, 0x6d },
  }
};

class Map
{
  public:
  static const int mapWidth = 320;
  static const int mapHeight = 180;

  Map();
  ~Map();

  Color *getMap();
  void paintParticle(int windowWidth, int windowHeight, double mouseX, double mouseY, ParticleType pixel);
  void paintSmallBrush(int windowWidth, int windowHeight, double mouseX, double mouseY, ParticleType type);
  void computePhysics();

  private:
  void _setParticle(uint32_t x, uint32_t y, ParticleType type);

  uint32_t _coordsToIndex(uint32_t x, uint32_t y);
  void _indexToCoords(uint32_t index, uint32_t &x, uint32_t &y);

  bool _isOutOfBounds(uint32_t x, uint32_t y);
  bool _isParticleFree(uint32_t x, uint32_t y);

  void _computeSandPhysics(uint32_t i);


  std::array<Particle, Map::mapWidth * Map::mapHeight> _particles;
  Color _map[Map::mapWidth * Map::mapHeight];
};
