#ifndef LIST_MRLC_H
#define LIST_MRLC_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#define NOP 0
#define MULT 1
#define ALU 2

#define unscheduled 0
#define scheduled 1
struct node {
    int number = 0;
    int type = 0;
    std::vector<int> predcessor;
    std::vector<int> successor;
    int state;
    int TF = 0, TL = 0;
};

void node_init(std::vector<std::vector<int>>& data, std::vector<struct node>& nodes, int L);
void ASAP(std::vector<struct node> node);
void ALAP(std::vector<struct node> node, int latency);

#endif
