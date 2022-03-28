
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
#include <cmath>

using namespace std;

//Util class for utility functions
namespace Module
{
    // Enum classes for queries
    enum class WorkerType
    {
        DEFAULT_NONE,
        TOTAL,
        MALE,
        FEMALE,
        ALL,
    };

    // Linked list of string data type
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

        static void initSOC(SOC& dest, SOC* src);
        static StrArray* splitSOCCodes(SOC& pSOC);
        static int compareSOC(const SOC& SOC1, const SOC& SOC2, WorkerType pWorkerType);
        static int compareSOCOcc(const SOC& SOC1, const SOC& SOC2);
        static int compareSOCOcc(const SOC& SOC1, const std::string& str);
        static void printSOC(const SOC& pSOC, WorkerType pWorkerType);
        static StrArray* tokenizeCSV(string& pData);
        static SOC* tokenizeSOC(string& pData);
        static earnings* tokenizeEarnings(string& pData);
        static string printThousands(int pInt);

        static int compareEarnings(const earnings& earnings1, const earnings& earnings2);
        static void printRatio(const earnings& pEarnings);
        
        static bool TestForPrime( int val );

    };
}
