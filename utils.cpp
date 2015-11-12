#include "utils.h"

std::string to_string(Direction dir) {
    static const std::array<std::string, Direction::SizeDirection> names {
        "none",
        "up",
        "down",
        "left",
        "right",
        "above",
        "below",
    };
    return names[int(dir)];
}

bool cRect::Intersect(const cRect &other) const {
    return left < other.right && right > other.left && top > other.bottom &&
           bottom < other.top;
}

std::string to_string(const cRect &rect) {
    return "{top: " + std::to_string(rect.top) +
           ", bottom: " + std::to_string(rect.bottom) +
           ", left: " + std::to_string(rect.left) +
           ", right: " + std::to_string(rect.right) + "}";
}
