
#include "util.h"

Module::util::~util()
{

}

// Copy function for SOC
void Module::util::initSOC(SOC& dest, SOC* src)
{
    strncpy(dest.occupation, src->occupation, OCC_LEN);
    strncpy(dest.SOC_code, src->SOC_code, CODE_LEN);
    dest.total = src->total;
    dest.female = src->female;
    dest.male = src->male;
}

// Separate SOC codes
Module::StrArray* Module::util::splitSOCCodes(SOC& pSOC)
{
    // Create String for easy tokenization
    string strCodes(pSOC.SOC_code);
    std::replace( strCodes.begin(), strCodes.end(), '&', ',');
    strCodes.erase(std::remove(strCodes.begin(), strCodes.end(), ' '), strCodes.end());

    istringstream iss(strCodes);
    string token;
    StrArray* lStrArray = nullptr;
    StrArray* lCurrStrArray = nullptr;
    
    // Tokenize by commas
    for (std::string line; std::getline(iss, line, ','); )
    {
        if (line.empty())
        {
            continue;
        }
        if (lStrArray == nullptr)
        {
            lCurrStrArray = new StrArray;
            lCurrStrArray->str = line;
            lCurrStrArray->next = nullptr;
            lStrArray = lCurrStrArray;
        }
        else
        {
            lCurrStrArray->next = new StrArray;
            lCurrStrArray = lCurrStrArray->next;
            lCurrStrArray->str = line;
            lCurrStrArray->next = nullptr;
        }
    }

    return lStrArray;
}

// Custom compare logic for SOC structs
int Module::util::compareSOC(const SOC& SOC1, const SOC& SOC2, WorkerType pWorkerType)
{
    int SOC1_value, SOC2_value;
    // Choosing the Worker type as key for primary sorting
    switch (pWorkerType)
    {
    case WorkerType::MALE:
        SOC1_value = SOC1.male;
        SOC2_value = SOC2.male;
        break;
    
    case WorkerType::FEMALE:
        SOC1_value = SOC1.female;
        SOC2_value = SOC2.female;
        break;
    
    case WorkerType::TOTAL:
        SOC1_value = SOC1.total;
        SOC2_value = SOC2.total;
        break;
    
    default:
        return 0;
        break;
    }

    // First sort by number of workers
    if (SOC1_value > SOC2_value)
    {
        return 1;
    }
    else if (SOC1_value < SOC2_value)
    {
        return -1;
    }
    else
    {
        // If same number of workers, then comapre occupation
        return compareSOCOcc(SOC1, SOC2);
    }
    return 0;
}

// Compare SOC based only on Occupation (lexicographically)
int Module::util::compareSOCOcc(const SOC& SOC1, const SOC& SOC2)
{
    // Comparing lexicographically
    return strcmp(SOC1.occupation, SOC2.occupation);
}

// Compare SOC Occupation (lexicographically) with string value
int Module::util::compareSOCOcc(const SOC& SOC1, const std::string& str)
{
    // Comparing lexicographically
    return strcmp(SOC1.occupation, str.c_str());
}

// Function to print out data from SOC struct as intended
void Module::util::printSOC(const SOC& pSOC, WorkerType pWorkerType)
{
    cout << '\t' << pSOC.occupation << ": ";
    switch (pWorkerType)
    {
    case WorkerType::MALE:
        cout << printThousands(pSOC.male);
        break;
    
    case WorkerType::FEMALE:
        cout << printThousands(pSOC.female);
        break;
    
    case WorkerType::TOTAL:
        cout << printThousands(pSOC.total);
        break;
    
    case WorkerType::ALL:
        cout << "YRFT: " << printThousands(pSOC.total) << ", ";
        cout << "Female: " << printThousands(pSOC.female) << ", ";
        cout << "Male: " << printThousands(pSOC.male);
        break;
    
    default:
        break;
    }
    cout << '\n';
}

// CSV data tokenizer,. returns linked list of String values
Module::StrArray* Module::util::tokenizeCSV(string& pData)
{
    istringstream iss(pData);
    string token;
    Module::StrArray* lStrArray = nullptr;
    Module::StrArray* lCurrStrArray = nullptr;
    
    // Tokenize by commas
    for (std::string line; std::getline(iss, line, ','); )
    {
        if (lStrArray == nullptr)
        {
            lCurrStrArray = new Module::StrArray;
            lCurrStrArray->str = line;
            lCurrStrArray->next = nullptr;
            lStrArray = lCurrStrArray;
        }
        else
        {
            lCurrStrArray->next = new Module::StrArray;
            lCurrStrArray = lCurrStrArray->next;
            lCurrStrArray->str = line;
            lCurrStrArray->next = nullptr;
        }
    }

    // For values with quotes, combine them again
    for (Module::StrArray* itr = lStrArray; itr != nullptr; itr = itr->next)
    {
        if (itr->str[0] == '\"')
        {
            Module::StrArray* startString = itr;
            itr->str = itr->str.substr(1);
            while ((itr->str.back() != '\"') && (itr->next != nullptr))
            {
                itr->str += ("," + itr->next->str);
                Module::StrArray* temp = itr->next;
                itr->next = itr->next->next;
                delete temp;
            }
            itr->str.pop_back();
        }
    }

    // Value count
    int i = 0;
    for (Module::StrArray* itr = lStrArray; itr != nullptr; itr = itr->next)
    {
        i++;
    }

    return lStrArray;
}

// Put the tokenized data into SOC struct
SOC* Module::util::tokenizeSOC(string& pData)
{
    Module::StrArray* lStrArray = tokenizeCSV(pData);
    SOC* lSOC = new SOC;
    Module::StrArray* lCurrArray = lStrArray;

    strcpy(lSOC->occupation, lCurrArray->str.c_str());
    lCurrArray = lCurrArray->next;

    strcpy(lSOC->SOC_code, lCurrArray->str.c_str());
    lCurrArray = lCurrArray->next;

    string temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    lSOC->total = stoi(temp);
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    lSOC->female = stoi(temp);
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    lSOC->male = stoi(temp);

    while (lStrArray != nullptr)
    {
        lCurrArray = lStrArray;
        lStrArray = lStrArray->next;
        delete lCurrArray;
    }
    return lSOC;
}

// Put the tokenized data into earnings struct
earnings* Module::util::tokenizeEarnings(string& pData)
{
    Module::StrArray* lStrArray = tokenizeCSV(pData);
    earnings* lEarn = new earnings;
    Module::StrArray* lCurrArray = lStrArray;

    string temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->year = stoi(temp);
    }
    catch(...)
    {
        lEarn->year = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->male_total = stoi(temp);
    }
    catch(...)
    {
        lEarn->male_total = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->male_with_earnings = stoi(temp);
    }
    catch(...)
    {
        lEarn->male_with_earnings = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->male_earnings = stoi(temp);
    }
    catch(...)
    {
        lEarn->male_earnings = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->male_earnings_moe = stoi(temp);
    }
    catch(...)
    {
        lEarn->male_earnings_moe = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->female_total = stoi(temp);
    }
    catch(...)
    {
        lEarn->female_total = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->female_with_earnings = stoi(temp);
    }
    catch(...)
    {
        lEarn->female_with_earnings = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->female_earnings = stoi(temp);
    }
    catch(...)
    {
        lEarn->female_earnings = -1;
    }
    lCurrArray = lCurrArray->next;

    temp = lCurrArray->str;
    temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
    try
    {
        lEarn->female_earnings_moe = stoi(temp);
    }
    catch(...)
    {
        lEarn->female_earnings_moe = -1;
    }
    lCurrArray = lCurrArray->next;

    while (lStrArray != nullptr)
    {
        lCurrArray = lStrArray;
        lStrArray = lStrArray->next;
        delete lCurrArray;
    }
    return lEarn;
}

// Add commas after each 3 digits while printing for readability
string Module::util::printThousands(int pInt)
{
    string str = "";
    while (pInt > 999)
    {
        string num = to_string(pInt % 1000);
        while (num.length() < 3)
        {
            num = "0" + num;
        }
        str = "," + num + str;
        pInt /= 1000;
    }
    str = to_string(pInt) + str;
    return str;
}

// Custom compare logic for earnings structs
int Module::util::compareEarnings(const earnings& earnings1, const earnings& earnings2)
{
    // Compared by year value
    if (earnings1.year > earnings2.year)
    {
        return 1;
    }
    else if (earnings1.year < earnings2.year)
    {
        return -1;
    }
    return 0;
}

// Calculate and print the ratio value of a earning struct
void Module::util::printRatio(const earnings& pEarnings)
{
    if (pEarnings.female_earnings < 0 || pEarnings.male_earnings < 0)
    {
        throw 1;
    }
    cout << '\t' << pEarnings.year << ": ";

    float lRatio = ((float)pEarnings.female_earnings / (float)pEarnings.male_earnings) * 100.0;
    cout << fixed << setprecision(1) << (lRatio - 0.05);
    cout << "%\n";
}

// Prime number check from prime.cc
bool Module::util::TestForPrime( int val )
{
    int limit, factor = 2;

    limit = (long)( sqrtf( (float) val ) + 0.5f );
    while( (factor <= limit) && (val % factor) )
        factor++;

    return( factor > limit );
}
