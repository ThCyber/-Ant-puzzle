#include <iostream>
#include <iomanip>

using namespace std;

struct Node {
    int y = 0, x = 0;
};

class Block {
public:
    vector<vector<Node>> points;
    bool used = false;
};

int matrix[7][7] = {{0, 0, 0, 0,  0,  0,  -1},
                    {0, 0, 0, 0,  0,  0,  -1},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, 0,  0,  0,  0},
                    {0, 0, 0, -1, -1, -1, -1}};
Block blocks[8];

Node getxy() {
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 7; i++) {
            if (matrix[j][i] == 0) {
                Node cur{j, i};
                return cur;
            }
        }
    }
    cerr << "we met an error";
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
    Node origin = getxy();
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
    //initialization
    blocks[0].points.resize(2);
    blocks[1].points.resize(4);
    blocks[2].points.resize(8);
    blocks[3].points.resize(8);
    blocks[4].points.resize(4);
    blocks[5].points.resize(8);
    blocks[6].points.resize(4);
    blocks[7].points.resize(8);

    blocks[0].points[0].resize(6);
    blocks[0].points[1].resize(6);
    for (int i = 1; i < 8; i++) {
        for (auto &j: blocks[i].points) {
            j.resize(5);
        }
    }
//    assign value of 积木
    blocks[0].points[0] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {0, 2},
                           {1, 1},
                           {1, 2}};
    blocks[0].points[1] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {1, 1},
                           {2, 0},
                           {2, 1}};
    blocks[1].points[0] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {1, 2},
                           {0, 2}};
    blocks[1].points[1] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {1, 2},
                           {0, 2}};
    blocks[1].points[2] = {{0, 0},
                           {0, 1},
                           {1, 1},
                           {2, 0},
                           {2, 1}};
    blocks[1].points[3] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {2, 0},
                           {2, 1}};
    blocks[2].points[0] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {0, 1},
                           {1, 1}};
    blocks[2].points[1] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {0, 1},
                           {2, 1}};
    blocks[2].points[2] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {0, 1},
                           {1, 2}};
    blocks[2].points[3] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {0, 1},
                           {0, 2}};
    blocks[2].points[4] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {2, 0},
                           {2, 1}};
    blocks[2].points[5] = {{0, 0},
                           {1, 1},
                           {0, 1},
                           {1, 2},
                           {0, 2}};
    blocks[2].points[6] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {0, 1},
                           {2, 0}};
    blocks[2].points[7] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {2, -1},
                           {2, 0}};
    blocks[3].points[0] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {3, 1}};
    blocks[3].points[1] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {3, -1}};
    blocks[3].points[2] = {{0, 0},
                           {1, 3},
                           {0, 1},
                           {0, 2},
                           {0, 3}};
    blocks[3].points[3] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {0, 2},
                           {0, 3}};
    blocks[3].points[4] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {1, 2},
                           {1, 3}};
    blocks[3].points[5] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {1, -2},
                           {1, -3}};
    blocks[3].points[6] = {{0, 0},
                           {1, 1},
                           {0, 1},
                           {2, 1},
                           {3, 1}};
    blocks[3].points[7] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {2, 0},
                           {3, 0}};
    blocks[4].points[0] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {2, 1},
                           {2, 2}};
    blocks[4].points[1] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {2, -1},
                           {2, -2}};
    blocks[4].points[2] = {{0, 0},
                           {1, 2},
                           {0, 1},
                           {0, 2},
                           {2, 2}};
    blocks[4].points[3] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {0, 2},
                           {2, 0}};
    blocks[5].points[0] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {1, -1},
                           {1, -2}};
    blocks[5].points[1] = {{0, 0},
                           {0, 1},
                           {1, 1},
                           {1, 2},
                           {1, 3}};
    blocks[5].points[2] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {2, 1},
                           {3, 1}};
    blocks[5].points[3] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {2, -1},
                           {3, -1}};
    blocks[5].points[4] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {0, 2},
                           {1, -1}};
    blocks[5].points[5] = {{0, 0},
                           {0, 1},
                           {0, 2},
                           {1, 2},
                           {1, 3}};
    blocks[5].points[6] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {2, 1},
                           {3, 1}};
    blocks[5].points[7] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {2, -1},
                           {3, -1}};
    blocks[6].points[0] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {1, 2},
                           {2, 2}};
    blocks[6].points[1] = {{0, 0},
                           {1, 0},
                           {0, 1},
                           {2, 0},
                           {2, -1}};
    blocks[6].points[2] = {{0, 0},
                           {1, 1},
                           {0, 1},
                           {2, 1},
                           {2, 2}};
    blocks[6].points[3] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {1, -2},
                           {2, -2}};
    blocks[7].points[0] = {{0, 0},
                           {1, 0},
                           {1, 1},
                           {1, -1},
                           {1, -2}};
    blocks[7].points[1] = {{0, 0},
                           {1, 0},
                           {1, -1},
                           {1, 1},
                           {1, 2}};
    blocks[7].points[2] = {{0, 0},
                           {0, 1},
                           {0, 2},
                           {0, 3},
                           {1, 2}};
    blocks[7].points[3] = {{0, 0},
                           {0, 1},
                           {0, 2},
                           {0, 3},
                           {1, 1}};
    blocks[7].points[4] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {2, 1}};
    blocks[7].points[5] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {1, 1}};
    blocks[7].points[6] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {1, -1}};
    blocks[7].points[7] = {{0, 0},
                           {1, 0},
                           {2, 0},
                           {3, 0},
                           {2, -1}};

    int month, day;
    cin >> month >> day;
    day--;
    month--;
    matrix[month / 6][month % 6] = -1;
    matrix[day / 7 + 2][day % 7] = -1;

    if (dfs(0)) {
        matrix[month / 6][month % 6] = 0;
        matrix[day / 7 + 2][day % 7] = 0;
    }
    cout << cnt << endl;
    return 0;
}
