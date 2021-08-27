#include <Map.hpp>

#include <iostream>
#include <cstring>

Map::Map()
{
  for (int i = 0; i < Map::mapWidth * (Map::mapHeight - 2); i += 1) {
    this->_map[i] = pixelTypes[AIR];
  }
  for (int i = Map::mapWidth * (Map::mapHeight - 2); i < Map::mapWidth * Map::mapHeight; i += 1) {
    this->_map[i] = pixelTypes[SAND];
  }
}

Map::~Map()
{
}

Pixel *Map::getMap()
{
  return this->_map;
}
