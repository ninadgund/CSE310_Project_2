
#pragma once

#include "util.h"

#define	HEAP_NODES 513

namespace Module
{
    class maxheap
    {
    private:
        const WorkerType mWorkerType;
        SOC* data[HEAP_NODES];
        int currValues;
        /* data */
    
        int left(int index);
        int right(int index);
        
        void maxHeapify(int index);
        void deleteRoot();

    public:
        maxheap(WorkerType workerType);
        ~maxheap();

        void addValue(SOC* newNode);
        void buildMaxHeap();
        void popMaxElements(int n);

    };
}
