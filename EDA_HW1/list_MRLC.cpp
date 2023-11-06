#include "list_MRLC.h"
#include "main.h"
void node_init(std::vector<std::vector<int>>& data, std::vector<struct node>& nodes)
{
    
    for (int i = 0; i < data.size(); i++) {
        nodes[i].number = data[i][0];
        nodes[i].type = data[i][1];
        if (nodes[i].type == NOP) {
            nodes[i].state = scheduled;
            nodes[i].TS = data[i][1];
        } else {
            nodes[i].state = unscheduled;
        }
        
        for (int j = 0; j < data[i][2]; j++) {
            if (data[i][2] > 0)
                nodes[data[i][j + 3]].predcessor.push_back(data[i][0]);
        }
    }
}

void ASAP(std::vector<struct node>& nodes)
{
    int unscheduled_node = nodes.size() - 2;
    int sel = 1;
    while (unscheduled_node) {
        if (nodes[sel].state == unscheduled) {
            int pred_state = unscheduled;
            int max_TS = 0;
            for (int i = 0; i < nodes[sel].predcessor.size(); i++) {
                struct node pred_node = nodes[nodes[sel].predcessor[i]];
                pred_state = pred_node.state;
                
                if (pred_state == unscheduled)
                    break;
                if (pred_node.TS >= max_TS) {
                    max_TS = pred_node.TS + 1;
                }
                    
            }
            
            if (pred_state == scheduled) {
                nodes[sel].TS = max_TS;
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
        if (nodes[i].TS > max_len) 
            max_len = nodes[i].TS;
        
    }
    
    std::vector<std::vector<int>> TS_graph (max_len);

    for (int i = 1; i < nodes.size() - 1; i++) {
        TS_graph[nodes[i].TS - 1].push_back(nodes[i].number);
    }
    
    for (int i = 0; i < max_len; i++)
    {
        for (int j = 0; j < TS_graph[i].size(); j++)
            std::cout << TS_graph[i][j] << " ";
        std::cout << std::endl;
    }
    
}
