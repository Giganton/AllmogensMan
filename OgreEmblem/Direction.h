#pragma once

enum class Direction { up, down, left, right };

namespace DIR {
	Direction oppositeDirection(Direction dir);
}