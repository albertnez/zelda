#pragma once

enum Direction {
	None = 0,
	Up,
	Down,
	Left,
	Right,
	Above,
	Below,
};

struct cRect {
	int left,top, right,bottom;
};
