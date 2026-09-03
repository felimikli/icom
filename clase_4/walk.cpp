#include <iostream>
#include <time.h>
#include <cmath>
#include <cstdlib>

#define ITER 1000000
#define EXPER 100

enum Direction {
	LEFT, RIGHT, UP, DOWN, NONE, NUM_DIRS
};

struct Entity {
	int x, y;
	void set_pos(int px, int py) {
		x = px;
		y = py;
	}
	void move(Direction d) {
		switch(d) {
			case LEFT: x--; break;
			case RIGHT: x++; break;
			case DOWN: y--; break;
			case UP: y++; break;
			case NONE: break;
			default: break;
		}
	}
	double dist(int px, int py) {
		return std::sqrt((x-px)*(x-px) + (y-py)*(y-py));
	}
	void print() {
		std::cout << "X: " << x << "  Y: " << y << "  Dist.: " << dist(0, 0) << '\n';
	}
};

int main(void) {
	std::srand(time(0));
	/*
	for(int i = 0; i < ITER; i++) {
		std::cout << rand() << ' ';
	}
	std::cout << '\n';

	for(int i = 0; i < ITER; i++) {
		std::cout << rand()/(float) RAND_MAX << ' ';
	}
	std::cout << '\n';
	*/

	Entity e = {0, 0};

	double m_dist = 0;
	for(int n = 0; n < EXPER; n++) {
		e.set_pos(0, 0);
		for(int i = 0; i < ITER; i++) {
			e.move( (Direction) (rand() % NUM_DIRS) );
		}
		m_dist += e.dist(0, 0);
	}

	m_dist = m_dist / EXPER;
	std::cout << m_dist << '\n';

	return 0;
}
