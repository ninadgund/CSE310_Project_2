
#include "util.h"

Module::util::~util()
{

}

int Module::util::compareSOC(const SOC& SOC1, const SOC& SOC2, WorkerType pWorkerType)
{
    int SOC1_value, SOC2_value;
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
        return strcmp(SOC1.occupation, SOC2.occupation);
    }
    return 0;
}

void Module::util::printSOC(const SOC& pSOC, WorkerType pWorkerType)
{
    cout << '\t' << pSOC.occupation << ": ";
    switch (pWorkerType)
    {
    case WorkerType::MALE:
        cout << pSOC.male;
        break;
    
    case WorkerType::FEMALE:
        cout << pSOC.female;
        break;
    
    case WorkerType::TOTAL:
        cout << pSOC.total;
        break;
    
    default:
        break;
    }
    cout << '\n';
}

Module::StrArray* Module::util::tokenizeCSV(string& pData)
{
    istringstream iss(pData);
    string token;
    Module::StrArray* lStrArray = nullptr;
    Module::StrArray* lCurrStrArray = nullptr;
    
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
    int i = 0;
    for (Module::StrArray* itr = lStrArray; itr != nullptr; itr = itr->next)
    {
        i++;
    }

    return lStrArray;
}

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

earnings* Module::util::tokenizeEarnings(string& pData)
{
    Module::StrArray* lStrArray = tokenizeCSV(pData);
    earnings* lSOC = new earnings;
    Module::StrArray* lCurrArray = lStrArray;

    lSOC->year = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->male_total = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->male_with_earnings = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->male_earnings = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->male_earnings_moe = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->female_total = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->female_with_earnings = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->female_earnings = stoi(lCurrArray->str);
    lCurrArray = lCurrArray->next;

    lSOC->female_earnings_moe = stoi(lCurrArray->str);

    while (lStrArray != nullptr)
    {
        lCurrArray = lStrArray;
        lStrArray = lStrArray->next;
        delete lCurrArray;
    }
    return lSOC;
}
