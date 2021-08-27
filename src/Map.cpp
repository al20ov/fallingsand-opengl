#include <Map.hpp>

#include <iostream>
#include <cstring>

Map::Map()
{
  for (int i = 0; i < Map::mapWidth * Map::mapHeight; i += 1) {
    this->_map[i] = pixelTypes[AIR];
  }
}

Map::~Map()
{
}





void Map::computePhysics()
{
  for (uint32_t i = 0; i < Map::mapWidth * Map::mapHeight; i += 1) {
    if (this->_map[i] == pixelTypes[SAND]) {
      this->_computeSandPhysics(i);
    }
  }
}





void Map::paintPixel(int windowWidth, int windowHeight, double mouseX, double mouseY)
{
  uint32_t xPos = mouseX / (double)windowWidth * Map::mapWidth;
  uint32_t yPos = Map::mapHeight - (mouseY / (double)windowHeight * Map::mapHeight);


  this->_setPixel(xPos, yPos, pixelTypes[SAND]);
}

void Map::_setPixel(uint32_t x, uint32_t y, const Pixel &pixel)
{
  if (!this->_isOutOfBounds(x, y))
  this->_map[this->_coordsToIndex(x, y)] = pixel;
}

uint32_t Map::_coordsToIndex(uint32_t x, uint32_t y)
{
  return x + Map::mapWidth * y;
}




void Map::_computeSandPhysics(uint32_t i)
{
  uint32_t x, y;

  this->_indexToCoords(i, x, y);
  if (!this->_isOutOfBounds(x, y - 1))
  if (this->_isPixelFree(x, y - 1)) {
    this->_map[i] = pixelTypes[AIR];
    this->_map[this->_coordsToIndex(x, y - 1)] = pixelTypes[SAND];
  }
}








bool Map::_isPixelFree(uint32_t x, uint32_t y)
{
  return this->_map[this->_coordsToIndex(x, y)] == pixelTypes[AIR];
}

bool Map::_isOutOfBounds(uint32_t x, uint32_t y)
{
  return x < 0 || x > Map::mapWidth || y < 0 || y > Map::mapHeight;
}

void Map::_indexToCoords(uint32_t index, uint32_t &x, uint32_t &y)
{
  x = index % Map::mapWidth;
  y = index / Map::mapWidth;
}

Pixel *Map::getMap()
{
  return this->_map;
}
