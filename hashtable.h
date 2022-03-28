
#pragma once

#include "util.h"

namespace Module
{
    class hashtable
    {
    private:
        /* data */
        hash_table_entry** hashArr;
        int sizeM;

        int hashfn(int k);
        bst* findEntry(int piSOCCOde, std::string pstrSOCCOde);

    public:
        hashtable(int m);
        ~hashtable();

        void createTable(bst* node);
        void insertEntry(bst* node);
        void insertEntry(bst* node, int piSOCCode, std::string pstrSOCCode);
        void printEntry(std::string pstrSOCCOde);
    };
}
