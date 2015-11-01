#pragma once

#include <vector>
#include <unordered_set>

class cMap {
public:
	cMap(int width = 0, int height = 0);
	void SetCell(int x, int y, int value);
	bool Obstacle(int x, int y) const;
	int Width() const;
	int Height() const;

private:
	static const std::unordered_set<int> walkable;
	int width;
	int height;
	std::vector<std::vector<int>> map;	
};
