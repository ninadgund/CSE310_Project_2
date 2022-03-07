
#include "maxheap.h"

// Constructor
Module::maxheap::maxheap(Module::WorkerType pWorkerType, string pYear) : mWorkerType{pWorkerType}
{
    mYear = pYear;
    currValues = 0;
    for (int i = 0; i < HEAP_NODES; i++)
    {
        data[i] = nullptr;
    }
}

// Destructor
Module::maxheap::~maxheap()
{
    for (int i = 0; i < HEAP_NODES; i++)
    {
        if (data[i] != nullptr)
        {
            data[i] = nullptr;
        }
    }
}

// Resolve the index of Left leaf
int Module::maxheap::left(int index)
{
    return ((index * 2) + 1);
}

// Resolve the index of Right leaf
int Module::maxheap::right(int index)
{
    return ((index * 2) + 2);
}

// Add a new value at the end of the array
void Module::maxheap::addValue(SOC* newNode)
{
    data[currValues] = newNode;
    currValues++;
}

// Standard heapify algorithm
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
    // Building max heap
    for (int i = ((currValues + 1)/2); i >= 1; i--)
    {
        maxHeapify(i - 1);
    }
}

void Module::maxheap::deleteRoot()
{
    // Delete root node, and heapify the tree
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
    maxHeapify(0);
}

void Module::maxheap::popMaxElements(int n)
{
    string lWorkerType;
    if (mWorkerType == WorkerType::FEMALE)
    {
        lWorkerType = "female";
    }
    else if (mWorkerType == WorkerType::MALE)
    {
        lWorkerType = "male";
    }
    else
    {
        lWorkerType = "total";
    }
    cout << "Top " << n << " occupations in " << mYear << " for " << lWorkerType << " workers:\n";
    for (int i = 0; (i < n) && (data[0] != nullptr); i++)
    {
        // Print the root (max) element, then delete it, and heapify the tree
        util::printSOC(*data[0], mWorkerType);
        deleteRoot();
    }
}
