#pragma once

#include <vector>
#include <unordered_set>

class cMap {
public:
    cMap(int width = 0, int height = 0);
    void SetCell(int x, int y, int value);
    bool Obstacle(int x, int y) const;
    bool DungeonDoor(int x, int y) const;
    bool LockedDoor(int x, int y) const;
    int Width() const;
    int Height() const;
    int GetCell(int i, int j);
    void OpenDoor(int x, int y);

private:
    static const std::unordered_set<int> walkable;
    static const std::unordered_set<int> dungeonDoor;
    static const std::unordered_set<int> lockedDoor;

    int width;
    int height;
    std::vector<std::vector<int>> map;    
};
