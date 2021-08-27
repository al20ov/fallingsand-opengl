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

void Map::setPixel(int windowWidth, int windowHeight, double mouseX, double mouseY)
{
  int xPos = mouseX / (double)windowWidth * Map::mapWidth;
  int yPos = Map::mapHeight - (mouseY / (double)windowHeight * Map::mapHeight);

  this->_map[xPos + Map::mapWidth * yPos] = pixelTypes[SAND];
}

Pixel *Map::getMap()
{
  return this->_map;
}
