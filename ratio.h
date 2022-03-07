
#pragma once

#include "util.h"

#define	RATIO_NODES 65

namespace Module
{
    class ratio
    {
    private:
        string mYear;
        earnings* data[RATIO_NODES];
        int currValues;
        /* data */
    
        int left(int index);
        int right(int index);
        
        void minHeapify(int index, int size);
        void buildMinHeap();

    public:
        ratio();
        ~ratio();

        void addValue(earnings* newNode);
        void heapSort();
        void printRatios(int startYear, int endYear);

    };
}
