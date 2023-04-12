//
// Created by 蔡恩光 on 2023/4/12.
//

#ifndef UNTITLED_BLOCKS_H
#define UNTITLED_BLOCKS_H
#include <vector>

struct Node {
    int y = 0, x = 0;
};

class Block {
public:
    std::vector<std::vector<Node>> points;
    bool used = false;
};
void initialize_blocks(Block (&blocks)[8]);

#endif //UNTITLED_BLOCKS_H
