
#pragma once

#include "util.h"

namespace Module
{
    class bstmgr
    {
    private:
        /* data */
//        string mYear;
        bst* root;
        int currValues;
    
        static void deleteNodeRec(bst * node);
        static bst* addValueToNode(bst* node, SOC* newNode);

//        void minHeapify(int index, int size);
//        void buildMinHeap();
        static bool printRange(bst* node, std::string& low, std::string& high, bool found);

    public:
        bstmgr();
        ~bstmgr();

        void addValue(SOC* newNode);
        int getTotalValues();
        bst* getRoot();
        void printRange(std::string& low, std::string& high);

    };
}
