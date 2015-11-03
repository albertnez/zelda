#pragma once

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

struct cRect {
	int left,top, right,bottom;
};
