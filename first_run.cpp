#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

const int GRIDW = 20;
const int GRIDH = 20;

vector<vector<int>> grid(GRIDH, vector<int>(GRIDW, 0));
vector<vector<int>> next_grid(GRIDH, vector<int>(GRIDW, 0));

void initialize_grid() {
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;
}

void show_grid() {
    system("cls");
    for (int i = 0; i < GRIDH; i++) {
        for (int j = 0; j < GRIDW; j++) {
            if (grid[i][j]) cout << "|#|"; else cout << "|_|";
        }
        cout << "\n";
    }
}

int count(int x, int y) {
    int c = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < GRIDH && ny >= 0 && ny < GRIDW) {
                c += grid[nx][ny];
            }
        }
    }
    return c;
}

void update_grid() {
    for (int i = 0; i < GRIDH; i++) {
        for (int j = 0; j < GRIDW; j++) {
            int c = count(i, j);
            if (grid[i][j]) {
                next_grid[i][j] = (c == 2 || c == 3);
            } else {
                next_grid[i][j] = (c == 3);
            }
        }
    }
    grid = next_grid;
}

int main() {
    initialize_grid();
    int first = 1;
    while (true) {
        show_grid();
        update_grid();
        // if (grid == next_grid && first == 0) break;
        this_thread::sleep_for(chrono::milliseconds(500));
        first = 0;
    }
    return 0;
}
