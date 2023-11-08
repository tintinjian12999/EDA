#include "list_MRLC.h"
void node_init(std::vector<std::vector<int>>& data, std::vector<struct node>& nodes, int L)
{
    // Updeatte the informations of each nodes from the input data
    for (int i = 0; i < data.size(); i++) {
        nodes[i].number = data[i][0];
        nodes[i].type = data[i][1];
        if (nodes[i].type == NOP) {
            nodes[i].state = scheduled;
            nodes[i].TF = data[i][1];
            nodes[i].TL = L + 1;
        } else {
            nodes[i].state = unscheduled;
        }
        
        for (int j = 0; j < data[i][2]; j++) {
            if (data[i][2] > 0) {
                nodes[i].successor.push_back(data[i][j + 3]);
                nodes[data[i][j + 3]].predcessor.push_back(data[i][0]);
            }
        }
    }
}

void ASAP(std::vector<struct node> nodes)
{
    int unscheduled_node = nodes.size() - 2;
    int sel = 1; // To iterate over nodes
    while (unscheduled_node) {
        // Consider the unscheduled state
        if (nodes[sel].state == unscheduled) {
            int pred_state = unscheduled;
            int max_TS = 0;
            // terate over all predcessor nodes
            for (int i = 0; i < nodes[sel].predcessor.size(); i++) {
                struct node pred_node = nodes[nodes[sel].predcessor[i]];
                pred_state = pred_node.state;
                if (pred_state == unscheduled)
                    break;
                // Scheduled the node where predecessors are scheduled
                if (pred_node.TF >= max_TS) {
                    max_TS = pred_node.TF + 1;
                } 
            }
            if (pred_state == scheduled) {
                nodes[sel].TF = max_TS;
                nodes[sel].state = scheduled;
                unscheduled_node--;
            }
        }
        if (sel == nodes.size() - 2)
            sel = 1;
        else 
            sel++;
    }
    int max_len = 1;
    
    for (int i = 1; i < nodes.size() - 1; i++) {
        if (nodes[i].TF > max_len) 
            max_len = nodes[i].TF;
    }
    std::vector<std::vector<int>> ASAP_graph (max_len);
    for (int i = 1; i < nodes.size() - 1; i++) {
        ASAP_graph[nodes[i].TF - 1].push_back(nodes[i].number);
    }
    for (int i = 0; i < max_len; i++)
    {
        for (int j = 0; j < ASAP_graph[i].size(); j++)
            std::cout << ASAP_graph[i][j] << " ";
        std::cout << std::endl;
    }
}

void ALAP(std::vector<struct node> nodes, int latency)
{
    int unscheduled_node = nodes.size() - 2;
    int sel = nodes.size() - 2;
    while (unscheduled_node) {
        if (nodes[sel].state == unscheduled) {
            int suc_state = unscheduled;
            int min_TS = latency + 1;
            for (int i = 0; i < nodes[sel].successor.size(); i++) {
                struct node suc_node = nodes[nodes[sel].successor[i]];
                suc_state = suc_node.state;
                if (suc_state == unscheduled)
                    break;
                // Scheduled the node where predecessors are scheduled
                if (suc_node.TL <= min_TS) {
                    min_TS = suc_node.TL - 1;
                } 
            }
            if (suc_state == scheduled) {
                nodes[sel].TL = min_TS;
                nodes[sel].state = scheduled;
                unscheduled_node--;
            }
        }
        if (sel == 1)
            sel = nodes.size() - 2;
        else 
            sel--; 
    }
    std::vector<std::vector<int>> ALAP_graph (latency);
    for (int i = 1; i < nodes.size() - 1; i++) {
        
        ALAP_graph[nodes[i].TL - 1].push_back(nodes[i].number);
    }
    for (int i = 0; i < latency; i++)
    {
        for (int j = 0; j < ALAP_graph[i].size(); j++)
            std::cout << ALAP_graph[i][j] << " ";
        std::cout << std::endl;
    }
}