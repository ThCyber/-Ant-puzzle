#include <iostream>
#include <iomanip>

#include "Blocks.h"
using namespace std;

int matrix[7][7] = {{0, 0, 0, 0,  0,  0,  -1},
                    {0, 0, 0, 0,  0,  0,  -1},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, -1, -1, -1, -1}};
Block blocks[8];

Node getOrigin() {
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            if (matrix[j][i] == 0) {
                Node cur{j, i};
                return cur;
            }
        }
    }
    cerr << "We've met an error!";
    return {};
}

bool outbound(int x) {
    return x < 0 || 7 <= x;
}

bool updatematrix(vector<Node> &temp, Node origin, int block_id) {
    block_id++;
    for (auto t: temp) {
        if (outbound(t.y + origin.y) || outbound(t.x + origin.x)) return false;
        if (matrix[t.y + origin.y][t.x + origin.x] != 0) return false;
        matrix[t.y + origin.y][t.x + origin.x] = block_id;
    }
    return true;
}

void clearblock(int block_id) {
    block_id++;
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            if (matrix[j][i] == block_id) matrix[j][i] = 0;
        }
    }
}

int cnt = 0;

bool dfs(int have_used) {
    if (have_used == 8) {
        cnt++;
        for (int j = 0; j < 7; j++) {
            for (int i = 0; i < 7; i++) {
                cout << setw(3) << matrix[j][i];
            }
            cout << endl;
        }
        cout << endl;
        return true;
    }
    have_used++;
    Node origin = getOrigin();
    for (int i = 0; i < 8; i++) {
        if (blocks[i].used) continue;
        blocks[i].used = true;
        for (auto &j: blocks[i].points) {
            if (updatematrix(j, origin, i)) {
                dfs(have_used);
            }
            clearblock(i);
        }
        blocks[i].used = false;
    }
    return false;
}

int main() {

    initialize_blocks(blocks);
    int month, day;
    cin >> month >> day;
    day--;month--;
    matrix[month / 6][month % 6] = -1;
    matrix[day / 7 + 2][day % 7] = -1;

    if (dfs(0)) {
        matrix[month / 6][month % 6] = 0;
        matrix[day / 7 + 2][day % 7] = 0;
    }
    cout << "We've got "<< cnt << " solutions! Hurray!"<< endl;
    return 0;
}
