#include "cMap.h"

const std::unordered_set<int> cMap::walkable {
    3,
    86,
    100,
    389,
    390,
    418,
    388,
    202,
    203,
    398,
    399,
    364,
    368,
    369,
    389,
    390,
    342,
    165,
    168,
};

const std::unordered_set<int> cMap::dungeonDoor {
    3,
};

const std::unordered_set<int> cMap::lockedDoor{
    201,
    204,
};

cMap::cMap(int width, int height)
    : width(width), height(height), map(height, std::vector<int>(width)) {}

void cMap::OpenDoor(int x, int y) {
    if (map[y][x] == 201) {
        map[y][x] = 418;
        map[y][x+3] = 388;
    }
    else if (map[y][x] == 204) {
        map[y][x] = 388;
        map[y][x - 3] = 418;
    }
}

void cMap::SetCell(int x, int y, int value) {
    map[y][x] = value;
}

bool cMap::Obstacle(int x, int y) const {
    return (walkable.count(map[y][x]) != 1);
}

bool cMap::DungeonDoor(int x, int y) const {
    return (dungeonDoor.count(map[y][x]) == 1);
}

bool cMap::LockedDoor(int x, int y) const {
    if (lockedDoor.count(map[y][x]) == 1) {
        return true;
    }
    return false;
}

int cMap::Width() const {
    return width;
}

int cMap::Height() const {
    return height;
}

int cMap::GetCell(int i, int j) {
    return map[i][j];
}
