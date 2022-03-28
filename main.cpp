
#include "util.h"
#include "maxheap.h"
#include "ratio.h"
#include "hashtable.h"
#include "bstmgr.h"

using namespace std;

// Queries
// 1. find max <worker>     <n>
//             total/m/f    1<=n<=50
void findMax(string occFileYear, string worker, int n)
{
    // Reading the file as per input year
    string occFileName = "Occupation-Dist-All-" + occFileYear + ".csv";
    ifstream occupationFile(occFileName);
    if (!occupationFile.is_open())
    {
        // Throw if file not found
        throw 1;
    }

    // Ignoring first 5 lines of CSV
    string line;
    int lineNo = 0;
    for (int i = 0; (i < 5) && getline(occupationFile, line); i++)
    {
        lineNo++;
    }

    Module::WorkerType lWorkerType;
    if (worker == "male")
    {
        lWorkerType = Module::WorkerType::MALE;
    }
    else if (worker == "female")
    {
        lWorkerType = Module::WorkerType::FEMALE;
    }
    else
    {
        lWorkerType = Module::WorkerType::TOTAL;
    }

    // Creating max heap of the data as per Worker type
    Module::maxheap lMaxHeap(lWorkerType, occFileYear);
    while (getline(occupationFile, line))
    {
        lineNo++;
        if(line.length() <= 1)
        {
            continue;
        }

        // Reading each line of data and tokenizing it into SOC struct
        SOC * newSOC = Module::util::tokenizeSOC(line);
        // Adding SOC struct in Array
        lMaxHeap.addValue(newSOC);
    }
    occupationFile.close();

    // Building max-heap from array of SOCs
    lMaxHeap.buildMaxHeap();

    // Popping the root node (max node) n times as the query requested
    lMaxHeap.popMaxElements(n);
}

void readOccupation(string occFileYear, Module::bstmgr* pBST, Module::hashtable* pHashT)
{
    // Reading the file as per input year
    string occFileName = "Occupation-Dist-All-" + occFileYear + ".csv";
    ifstream occupationFile(occFileName);
    if (!occupationFile.is_open())
    {
        // Throw if file not found
        throw 1;
    }

    // Ignoring first 5 lines of CSV
    string line;
    int lineNo = 0;
    for (int i = 0; (i < 5) && getline(occupationFile, line); i++)
    {
        lineNo++;
    }

    // Creating data structures of the data from occupation file
    pBST = new Module::bstmgr();
    while (getline(occupationFile, line))
    {
        lineNo++;
        if(line.length() <= 1)
        {
            continue;
        }

        // Reading each line of data and tokenizing it into SOC struct
        SOC * newSOC = Module::util::tokenizeSOC(line);
        // Adding SOC struct in Array
        // TODO - Add stuff here
        pBST->addValue(newSOC);
        delete newSOC;
        newSOC = nullptr;
    }
    occupationFile.close();

    pHashT = new Module::hashtable(pBST->getTotalValues());
    pHashT->createTable(pBST->getRoot());
}

// main
int main(int argc, char** argv)
{
    // Arguements read and verify
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }

    // Occupation data year for filename
    string occFileYear(argv[1]);

    // Earning data filename
    string earnFileName = "Earnings-1960-2019.csv";
    ifstream earnFile(earnFileName);
    if (!earnFile.is_open())
    {
        return EXIT_FAILURE;
    }

    // Reading earning data file and skipping first 8 lines
    string line;
    int lineNo = 0;
    for (int i = 0; (i < 8) && getline(earnFile, line); i++)
    {
        lineNo++;
    }
    // Creating an array for ratio queries
    Module::ratio LPlusRatio;

    // Reading earning data line by line
    while (getline(earnFile, line))
    {
        lineNo++;
        if(line.length() <= 1)
        {
            continue;
        }

        // Formatting CSV data to create earning struct
        earnings * newEarnings = Module::util::tokenizeEarnings(line);
        // Adding data to array
        LPlusRatio.addValue(newEarnings);
    }
    earnFile.close();
    // Sorting the array using heapsort by year values
    LPlusRatio.heapSort();

    //Reading Occupation file to create BST and Hashtable
    Module::bstmgr* lBST;
    Module::hashtable* lHashT;
//    readOccupation(occFileYear, lBST, lHashT);

    // Read number of queries 'N'
    string in_line;
    int q_n = 0;
    if (getline(cin, in_line))
    {
        q_n = stoi(in_line);
        // Read N lines each containing a query
        for (int i = 0; i < q_n; i++)
        {
            getline(cin, in_line);
            
            // Check the query type
            if (in_line.rfind("find max", 0) == 0)
            {
                cout << "Query: " << in_line << "\n\n";
                in_line = in_line.substr(9);
                string token;
                istringstream iss(in_line);
                // Read query input
                try
                {
                    string worker;
                    string str_n;
                    if(!std::getline(iss, worker, ' '))
                    {
                        throw 1;
                    }
                    if(!std::getline(iss, str_n, '\n'))
                    {
                        throw 1;
                    }
                    
                    findMax(occFileYear, worker, stoi(str_n));
                }
                catch (...)
                {
                    cout << "Query failed" << '\n';
                }
            }
            else if (in_line.rfind("find ratio", 0) == 0)
            {
                cout << "Query: " << in_line << "\n\n";
                in_line = in_line.substr(11);
                string token;
                istringstream iss(in_line);
                // Read query input
                try
                {
                    string startYear;
                    string endYear;
                    if(!std::getline(iss, startYear, ' '))
                    {
                        throw 1;
                    }
                    if(!std::getline(iss, endYear, '\n'))
                    {
                        throw 1;
                    }
                    LPlusRatio.printRatios(stoi(startYear), stoi(endYear));
                }
                catch (...)
                {
                    //  For failed query, exception (integer for simplicity) is thrown
                    cout << "Query failed" << '\n';
                }
            }
            else if (in_line.rfind("find occupation", 0) == 0)
            {
                cout << "Query: " << in_line << "\n\n";
                in_line = in_line.substr(17);
                try
                {
                    lHashT->printEntry(in_line);
                }
                catch (...)
                {
                    //  For failed query, exception (integer for simplicity) is thrown
                    cout << "Query failed" << '\n';
                }
            }
            else if (in_line.rfind("range occupation", 0) == 0)
            {
                cout << in_line << '\n';
                // Implementation not needed for milestone
            }
            cout << endl;

        }
    }

    return 0;
}
