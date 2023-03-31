#include <iostream>
using namespace std;

int m;
int y_dir[4] = { -1, 0, 1, 0 };
int x_dir[4] = { 0, 1, 0, -1 };

template <class T> class Stack {
public:
	T* arr;
	int cap; // capacity
	int top; // counter

	Stack() {
		arr = new T[1];
		cap = 1;
		top = -1;
	}

	void push(T data) {
		top++;
		if (top == cap) {
			T* tmp = new T[2 * cap];
			for (int i = 0; i < cap; i++) {
				tmp[i] = arr[i];
			}
			arr = tmp;
			cap *= 2;

		}
		arr[top] = data;
	}
	T pop() {
		return arr[top--];
	}
	bool isEmpty() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	}

};

struct Pos {
	int y;
	int x;
};

void pushDirection(Stack<char> &dir, int i) {
	switch (i) {
		case 0:
			dir.push('N');
			break;
		case 1:
			dir.push('E');
			break;
		case 2:
			dir.push('S');
			break;
		case 3:
			dir.push('W');
			break;
	}
}

void wayfinding(bool maze[][50], Pos pos, Pos des, Stack<Pos> route, Stack<char> dir, int previousDir) {
	maze[pos.y][pos.x] = 0;
	route.push(pos);
	pushDirection(dir, previousDir);
	// cout << "Position: " << pos.y << " " << pos.x << "\n";
	if (pos.y == des.y && pos.x == des.x) {
		Stack<char> tmpDir;
		while (!dir.isEmpty()) {
			tmpDir.push(dir.pop());
		}
		while (!tmpDir.isEmpty()) {
			cout << tmpDir.pop();
		}

		// while (!route.isEmpty()) {
		// 	Pos tmpPos = route.pop();
		// 	cout << tmpPos.y << ", " << tmpPos.x << "\n";
		// }
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (pos.y + y_dir[i] >= 0 && pos.y + y_dir[i] <= m - 1 && pos.x + x_dir[i] >= 0 && pos.x + x_dir[i] <= m - 1) {
				if (maze[pos.y + y_dir[i]][pos.x + x_dir[i]] == 1) {
					Pos tmpPos;
					tmpPos.y = pos.y + y_dir[i];
					tmpPos.x = pos.x + x_dir[i];
					
					wayfinding(maze, tmpPos, des, route, dir, i);
				}
			}
		}
	}
}

int main() {
	cin >> m;
	bool maze[50][50] = { 0 };
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cin >> maze[i][j];
		}
	}

	Pos pos;
	pos.y = 0;
	pos.x = 0;

	Pos des;
	des.y = m - 1;
	des.x = m - 1;

	Stack<Pos> route;
	Stack<char> dir;
	wayfinding(maze, pos, des, route, dir, -1);
}

/*
0 represents the wall
1 represents the aisles he can go through

3
1 1 0
0 1 1
1 0 1
*/