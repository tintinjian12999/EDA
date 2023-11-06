<<<<<<< HEAD
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
    int number;
    int type;
    std::vector<int> predcessor;
    int state;
    int TS;
};



void node_init(std::vector<std::vector<int>>& data, std::vector<struct node>& nodes);
void ASAP(std::vector<struct node>& node);
#endif
=======
#include <iostream>
#define NOP 0
#define MULT 1
#define ALU 2
>>>>>>> 9bf3c2e6e9d77c228004716e251467126b81cdde
