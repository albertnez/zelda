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
