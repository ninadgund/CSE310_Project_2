
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

    public:
        bstmgr();
        ~bstmgr();

        void addValue(SOC* newNode);
        int getTotalValues();
        bst* getRoot();
//        void heapSort();
//        void printRatios(int startYear, int endYear);

    };
}
