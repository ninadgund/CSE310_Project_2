
#include "ratio.h"

// Constructor
Module::ratio::ratio()
{
    currValues = 0;
    for (int i = 0; i < RATIO_NODES; i++)
    {
        data[i] = nullptr;
    }
    
}

// Destructor
Module::ratio::~ratio()
{
    for (int i = 0; i < RATIO_NODES; i++)
    {
        if (data[i] != nullptr)
        {
            data[i] = nullptr;
        }
    }
}

// Resolve the index of Left leaf
int Module::ratio::left(int index)
{
    return ((index * 2) + 1);
}

// Resolve the index of Right leaf
int Module::ratio::right(int index)
{
    return ((index * 2) + 2);
}

// Add a new value at the end of the array
void Module::ratio::addValue(earnings* newNode)
{
    data[currValues] = newNode;
    currValues++;
}

// Standard heapify algorithm
void Module::ratio::minHeapify(int index, int size)
{
    int lIndex = left(index);
    int rIndex = right(index);
    int smallest;

    if(lIndex < size && (util::compareEarnings(*data[lIndex], *data[index]) > 0))
    {
        smallest = lIndex;
    }
    else
    {
        smallest = index;
    }
    if(rIndex < size && (util::compareEarnings(*data[rIndex], *data[smallest]) > 0))
    {
        smallest = rIndex;
    }
    if (smallest != index)
    {
        earnings * tempNode = data[index];
        data[index] = data[smallest];
        data[smallest] = tempNode;
        minHeapify(smallest, size);
    }
}

// Heapifying the array to make a min heap (for ascending order)
void Module::ratio::buildMinHeap()
{
    for (int i = ((currValues + 1)/2); i >= 1; i--)
    {
        minHeapify(i - 1, currValues);
    }
}

// Heap sort the array
void Module::ratio::heapSort()
{
    buildMinHeap();
    for (int i = currValues - 1; i >= 1; i--)
    {
        // exchange data[0] and data[i - 1]
        earnings * tempNode = data[0];
        data[0] = data[i];
        data[i] = tempNode;
        minHeapify(0, i);
    }
}

// Print the ratio of the range of years as specified
void Module::ratio::printRatios(int startYear, int endYear)
{
    cout << "The female-to-male earnings ratio for " << startYear << "-" << endYear << ":\n";
    for (int i = (startYear - 1960); (i <= (endYear - 1960)) && (data[i] != nullptr); i++)
    {
        util::printRatio(*data[i]);
    }
}
