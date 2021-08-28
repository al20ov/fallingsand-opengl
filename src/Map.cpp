#include <Map.hpp>

#include <iostream>
#include <cstring>

Map::Map()
{
  for (int i = 0; i < Map::mapWidth * Map::mapHeight; i += 1) {
    this->_particles[i] = particleTypes[AIR];
    this->_map[i] = particleColors[AIR][0];
  }
}

Map::~Map()
{
}





void Map::computePhysics()
{
  for (uint32_t i = 0; i < Map::mapWidth * Map::mapHeight; i += 1)
  if (this->_particles[i] == particleTypes[SAND]) {
    this->_computeSandPhysics(i);
  }
}





void Map::paintParticle(int windowWidth, int windowHeight, double mouseX, double mouseY, ParticleType type)
{
  uint32_t xPos = mouseX / (double)windowWidth * Map::mapWidth;
  uint32_t yPos = Map::mapHeight - (mouseY / (double)windowHeight * Map::mapHeight);

  this->_setParticle(xPos, yPos, type);
}

void Map::paintSmallBrush(int windowWidth, int windowHeight, double mouseX, double mouseY, ParticleType type)
{
  uint32_t xPos = mouseX / (double)windowWidth * Map::mapWidth;
  uint32_t yPos = Map::mapHeight - (mouseY / (double)windowHeight * Map::mapHeight);

  // top, left, middle, right, bottom
  this->_setParticle(xPos, yPos + 1, type);
  this->_setParticle(xPos - 1, yPos, type);
  this->_setParticle(xPos, yPos, type);
  this->_setParticle(xPos + 1, yPos, type);
  this->_setParticle(xPos, yPos - 1, type);
}

void Map::_setParticle(uint32_t x, uint32_t y, ParticleType type)
{
  static byte colorIndex = 0;

  if (!this->_isOutOfBounds(x, y)) {
    uint32_t index = this->_coordsToIndex(x, y);

    this->_particles[index] = { type };
    this->_map[index] = particleColors[type][colorIndex % 4];
  }
  colorIndex++;
}

uint32_t Map::_coordsToIndex(uint32_t x, uint32_t y)
{
  return x + Map::mapWidth * y;
}


void Map::_computeSandPhysics(uint32_t i)
{
  uint32_t x, y;

  this->_indexToCoords(i, x, y);
  if (!this->_isOutOfBounds(x, y - 1) and this->_isParticleFree(x, y - 1)) {
    this->_particles[this->_coordsToIndex(x, y - 1)] = particleTypes[SAND];
    this->_map[this->_coordsToIndex(x, y - 1)] = this->_map[i];

    this->_particles[i] = particleTypes[AIR];
    this->_map[i] = particleColors[AIR][0];
  } else if (!this->_isOutOfBounds(x - 1, y - 1) and this->_isParticleFree(x - 1, y - 1)) {
    this->_particles[this->_coordsToIndex(x - 1, y - 1)] = particleTypes[SAND];
    this->_map[this->_coordsToIndex(x - 1, y - 1)] = this->_map[i];

    this->_particles[i] = particleTypes[AIR];
    this->_map[i] = particleColors[AIR][0];
  } else if (!this->_isOutOfBounds(x + 1, y - 1) and this->_isParticleFree(x + 1, y - 1)) {
    this->_particles[this->_coordsToIndex(x + 1, y - 1)] = particleTypes[SAND];
    this->_map[this->_coordsToIndex(x + 1, y - 1)] = this->_map[i];

    this->_particles[i] = particleTypes[AIR];
    this->_map[i] = particleColors[AIR][0];
  }
}


bool Map::_isParticleFree(uint32_t x, uint32_t y)
{
  return this->_particles[this->_coordsToIndex(x, y)] == particleTypes[AIR];
  // return this->_map[this->_coordsToIndex(x, y)] == particleColors[AIR];
}

bool Map::_isOutOfBounds(uint32_t x, uint32_t y)
{
  return x < 0 || x >= Map::mapWidth || y < 0 || y >= Map::mapHeight;
}

void Map::_indexToCoords(uint32_t index, uint32_t &x, uint32_t &y)
{
  x = index % Map::mapWidth;
  y = index / Map::mapWidth;
}

Color *Map::getMap()
{
  return this->_map;
}






Particle::Particle(ParticleType type)
  : _type(type)
{
}

Particle::Particle()
{
}
