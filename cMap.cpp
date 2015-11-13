#include "cMap.h"

const std::unordered_set<int> cMap::walkable {
    3,
    86,
    100,
    389,
    390,
};

const std::unordered_set<int> cMap::dungeonDoor {
    3,
};

cMap::cMap(int width, int height)
    : width(width), height(height), map(height, std::vector<int>(width)) {}

void cMap::SetCell(int x, int y, int value) {
    map[y][x] = value;
}

bool cMap::Obstacle(int x, int y) const {
    return (walkable.count(map[y][x]) != 1);
}

bool cMap::DungeonDoor(int x, int y) const {
    return (dungeonDoor.count(map[y][x]) == 1);
}

int cMap::Width() const {
    return width;
}

int cMap::Height() const {
    return height;
}
