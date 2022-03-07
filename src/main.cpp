
#include "util.h"
#include "maxheap.h"
#include "hashtable.h"
#include "bst.h"

using namespace std;

// Queries
// 1. find max <worker>     <n>
//             total/m/f    1<=n<=50
void findMax(string occFileYear, string worker, int n)
{
    string occFileName = "Occupation-Dist-All-" + occFileYear + ".csv";
    ifstream occupationFile(occFileName);
    if (!occupationFile.is_open())
    {
        throw 1;
    }

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
    cout << endl;

    Module::maxheap lMaxHeap(lWorkerType);
    while (getline(occupationFile, line))
    {
        lineNo++;
        if(line.length() <= 1)
        {
            continue;
        }

        SOC * newSOC = Module::util::tokenizeSOC(line);
        lMaxHeap.addValue(newSOC);
    }
    occupationFile.close();

    lMaxHeap.buildMaxHeap();

    cout << "find max " << worker << " " << n << '\n';
    lMaxHeap.popMaxElements(n);
    cout << endl;
}

// 2. find ratio <yyyy>     <zzzz>
//               1960<=yyyy<=zzzz<=2019
void findRatio(string worker, int n)
{
    // TODO - Can make array (heap) once then answer using that
}

// main
int main(int argc, char** argv)
{
    // Arguements read and verify
    if (argc < 2)
    {
        return EXIT_FAILURE;
    }

    string occFileYear(argv[1]);

    string earnFileName = "Earnings-1960-2019.csv";
    ifstream earnFile(earnFileName);
    if (!earnFile.is_open())
    {
        return EXIT_FAILURE;
    }

    // Read number of queries 'N'
    string in_line;
    int q_n = 0;
    if (getline(cin, in_line))
    {
        q_n = stoi(in_line);
        // Read N lines each containing a query
        for (int i = 0; i < q_n; i++)
        {
            cout << "hyhy:" << q_n << endl;
            getline(cin, in_line);
            
            if (in_line.rfind("find max", 0) == 0)
            {
                cout << in_line << '\n';
                in_line = in_line.substr(9);
                string token;
                istringstream iss(in_line);
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
                    cout << "Here 4" << endl;
                }
                catch (...)
                {
                    cout << "Query failed" << '\n';
                }
            }
            else if (in_line.rfind("find ratio", 0) == 0)
            {
                cout << in_line << '\n';
                in_line = in_line.substr(11);
                string token;
                istringstream iss(in_line);
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
                    
                    findRatio(worker, stoi(str_n));
                }
                catch (...)
                {
                    cout << "Query failed" << '\n';
                }
            }
            else if (in_line.rfind("find occupation", 0) == 0)
            {
                cout << in_line << '\n';
                // Implementation not needed for milestone
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
