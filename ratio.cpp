
#include "ratio.h"

Module::ratio::ratio()
{
    currValues = 0;
    for (int i = 0; i < RATIO_NODES; i++)
    {
        data[i] = nullptr;
    }
    
}

Module::ratio::~ratio()
{
    for (int i = 0; i < RATIO_NODES; i++)
    {
        if (data[i] != nullptr)
        {
//            delete data[i];
            data[i] = nullptr;
        }
    }
}

int Module::ratio::left(int index)
{
    return ((index * 2) + 1);
}

int Module::ratio::right(int index)
{
    return ((index * 2) + 2);
}

void Module::ratio::addValue(earnings* newNode)
{
    data[currValues] = newNode;
    currValues++;
}

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

void Module::ratio::buildMinHeap()
{
    for (int i = ((currValues + 1)/2); i >= 1; i--)
    {
        minHeapify(i - 1, currValues);
    }
}

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

void Module::ratio::printRatios(int startYear, int endYear)
{
    cout << "The female-to-male earnings ratio for " << startYear << "-" << endYear << ":\n";
    for (int i = (startYear - 1960); (i <= (endYear - 1960)) && (data[i] != nullptr); i++)
    {
        util::printRatio(*data[i]);
    }
}
