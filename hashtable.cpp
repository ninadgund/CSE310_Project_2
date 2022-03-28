
#include "hashtable.h"
#include "util.h"

Module::hashtable::hashtable(int m)
{
    int firstPrime;
    for (firstPrime = ((3 * m) + 1); !(util::TestForPrime(firstPrime)); firstPrime++)
    {

    }

    hashArr = new hash_table_entry*[firstPrime];
    sizeM = firstPrime;
    for (int i = 0; i < sizeM; i++)
    {
        hashArr[i] = nullptr;
    }
}

Module::hashtable::~hashtable()
{
    for (int i = 0; i < sizeM; i++)
    {
        delete hashArr[i];
        hashArr = nullptr;
    }
}

int Module::hashtable::hashfn(int k)
{
    return (k % sizeM);
}

void Module::hashtable::createTable(bst* node)
{
    if (node == nullptr)
    {
        return;
    }
    insertEntry(node);
    createTable(node->left);
    createTable(node->right);
}

void Module::hashtable::insertEntry(bst* node)
{
    StrArray* lSOCCodes = util::splitSOCCodes(node->soc);
    StrArray* lCurrArr = lSOCCodes;
    while (lCurrArr != nullptr)
    {
        string strCode = lCurrArr->str;
        strCode.erase(std::remove(strCode.begin(), strCode.end(), '-'), strCode.end());
        int liSOCCOde = stoi(strCode);
        insertEntry(node, liSOCCOde, lCurrArr->str);
        lCurrArr = lCurrArr->next;
    }

    while (lSOCCodes != nullptr)
    {
        lCurrArr = lSOCCodes;
        lSOCCodes = lSOCCodes->next;
        delete lCurrArr;
    }
}

void Module::hashtable::insertEntry(bst* node, int piSOCCode, string pstrSOCCOde)
{
    int h = hashfn(piSOCCode);

    if (hashArr[h] == nullptr)
    {
        hashArr[h] = new hash_table_entry;
        strncpy(hashArr[h]->SOC_code, pstrSOCCOde.c_str(), pstrSOCCOde.length());
        hashArr[h]->node = node;
        hashArr[h]->next = nullptr;
        return;
    }

    hash_table_entry* currEntry = hashArr[h];
    if (strcmp(currEntry->SOC_code, pstrSOCCOde.c_str()) == 0)
    {
        return;
    }
    while (currEntry->next != nullptr)
    {
        currEntry = currEntry->next;
        if (strcmp(currEntry->SOC_code, pstrSOCCOde.c_str()) == 0)
        {
            return;
        }
    }
    currEntry->next = new hash_table_entry;
    currEntry = currEntry->next;
    strncpy(currEntry->SOC_code, pstrSOCCOde.c_str(), pstrSOCCOde.length());
    currEntry->node = node;
    currEntry->next = nullptr;
    return;
}

void Module::hashtable::printEntry(std::string pstrSOCCOde)
{
    string lstrSOCCOde = pstrSOCCOde;
    lstrSOCCOde.erase(std::remove(lstrSOCCOde.begin(), lstrSOCCOde.end(), '-'), lstrSOCCOde.end());
    int liSOCCOde = stoi(lstrSOCCOde);

    bst* lBST = findEntry(liSOCCOde, pstrSOCCOde);
    if (lBST == nullptr)
    {
        cout << "Occupation with SOC code " + pstrSOCCOde + " not found.\n";
        return;
    }
    cout << "The occupation with SOC code " + pstrSOCCOde + ":\n";
    util::printSOC(lBST->soc, WorkerType::ALL);
}

bst* Module::hashtable::findEntry(int piSOCCOde, std::string pstrSOCCOde)
{
    int h = hashfn(piSOCCOde);

    if (hashArr[h] == nullptr)
    {
        return nullptr;
    }

    hash_table_entry* currEntry = hashArr[h];
    if (strcmp(currEntry->SOC_code, pstrSOCCOde.c_str()) == 0)
    {
        return currEntry->node;
    }
    while (currEntry->next != nullptr)
    {
        currEntry = currEntry->next;
        if (strcmp(currEntry->SOC_code, pstrSOCCOde.c_str()) == 0)
        {
            return currEntry->node;
        }
    }
    return nullptr;
}
