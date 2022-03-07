
#include "maxheap.h"

Module::maxheap::maxheap(Module::WorkerType pWorkerType) : mWorkerType{pWorkerType}
{
    currValues = 0;
    for (int i = 0; i < HEAP_NODES; i++)
    {
        data[i] = nullptr;
    }
}

Module::maxheap::~maxheap()
{
    for (int i = 0; i < HEAP_NODES; i++)
    {
        if (data[i] != nullptr)
        {
//            delete data[i];
            data[i] = nullptr;
        }
    }
}

int Module::maxheap::left(int index)
{
    return ((index * 2) + 1);
}

int Module::maxheap::right(int index)
{
    return ((index * 2) + 2);
}

void Module::maxheap::addValue(SOC* newNode)
{
    data[currValues] = newNode;
    currValues++;
}

void Module::maxheap::maxHeapify(int index)
{
    int lIndex = left(index);
    int rIndex = right(index);
    int largest;

    if(lIndex < currValues && (util::compareSOC(*data[lIndex], *data[index], mWorkerType) > 0))
    {
        largest = lIndex;
    }
    else
    {
        largest = index;
    }
    if(rIndex < currValues && (util::compareSOC(*data[rIndex], *data[largest], mWorkerType) > 0))
    {
        largest = rIndex;
    }
    if (largest != index)
    {
        SOC * tempNode = data[index];
        data[index] = data[largest];
        data[largest] = tempNode;
        maxHeapify(largest);
    }
}

void Module::maxheap::buildMaxHeap()
{
    for (int i = ((currValues + 1)/2); i >= 1; i--)
    {
        maxHeapify(i - 1);
    }
}

void Module::maxheap::deleteRoot()
{
    if (currValues == 0)
    {
        return;        
    }
    delete data[0];
    if (currValues == 1)
    {
        data[0] = nullptr;
        return;
    }
    data[0] = data[currValues - 1];
//    data[currValues - 1] = nullptr;
    maxHeapify(0);
}

void Module::maxheap::popMaxElements(int n)
{
    for (int i = 0; (i < n) && (data[0] != nullptr); i++)
    {
        util::printSOC(*data[0], mWorkerType);
        deleteRoot();
    }
}
