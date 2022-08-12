#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
	int y;
	int x;
};

queue<Node> q;
vector<Node> v;

int map[8][8];
int temp[8][8];
int used[8][8];

int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };

int N, M;

int answer = -1;

void virus() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			temp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < v.size(); i++) {
		q.push({ v[i] });
	}

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || nx >= M || ny >= N) continue;
			if (temp[ny][nx] == 1 || temp[ny][nx] == 2) continue;
			temp[ny][nx] = 2;
			q.push({ ny,nx });
		}
	}

}


int count() {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (temp[i][j] == 0) cnt++;
		}
	}

	return cnt;
}

void wall(int cnt) {
	if (cnt == 3) {
		virus();
		int result = count();
		if (result > answer) answer = result;
		return;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				wall(cnt + 1);
				map[i][j] = 0;
			}
		}
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}

	wall(0);

	cout << answer;

	return 0;

}