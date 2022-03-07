
#pragma once

#include "defns.h"
#include <cstring>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <iomanip>

using namespace std;

namespace Module
{
    // Enum classes for queries
    enum class WorkerType
    {
        DEFAULT_NONE,
        TOTAL,
        MALE,
        FEMALE,
    };

    struct StrArray
    {
        string str;
        StrArray * next;
    };

    class util
    {
    private:
        /* data */
    public:
        util() = delete;
        ~util();

        static int compareSOC(const SOC& SOC1, const SOC& SOC2, WorkerType pWorkerType);
        static void printSOC(const SOC& pSOC, WorkerType pWorkerType);
        static StrArray* tokenizeCSV(string& pData);
        static SOC* tokenizeSOC(string& pData);
        static earnings* tokenizeEarnings(string& pData);
        static string printThousands(int pInt);

        static int compareEarnings(const earnings& earnings1, const earnings& earnings2);
        static void printRatio(const earnings& pEarnings);
        
    };
}
