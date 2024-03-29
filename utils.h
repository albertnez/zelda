#pragma once

#include <array>
#include <string>
enum Direction {
    None = 0,
    Up,
    Down,
    Left,
    Right,
    Above,
    Below,
    SizeDirection,
};

std::string to_string(Direction dir);

struct cRect {
    int left,top, right,bottom;
    bool Intersect(const cRect &other) const;
};

std::string to_string(const cRect &rect);
