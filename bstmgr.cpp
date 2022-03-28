
#include "bstmgr.h"

Module::bstmgr::bstmgr(/* args */)
{
    root = nullptr;
    currValues = 0;
}

Module::bstmgr::~bstmgr()
{
    deleteNodeRec(root);
    root = nullptr;
    currValues = 0;
}

void Module::bstmgr::deleteNodeRec(bst * node)
{
    if (node == nullptr)
    {
        return;
    }
    deleteNodeRec(node->left);
    node->left = nullptr;
    deleteNodeRec(node->right);
    node->right = nullptr;
    delete node;
}

void Module::bstmgr::addValue(SOC* newNode)
{
    root = addValueToNode(root, newNode);
    currValues++;
}

bst* Module::bstmgr::addValueToNode(bst* node, SOC* newNode)
{
    if (node == nullptr)
    {
        node = new bst;
        util::initSOC(node->soc, newNode);
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    int cmp = util::compareSOCOcc(node->soc, *newNode);
    if (cmp < 0)
    {
        node->left = addValueToNode(node->left, newNode);
    }
    else if (cmp > 0)
    {
        node->right = addValueToNode(node->right, newNode);
    }
    return node;
}

int Module::bstmgr::getTotalValues()
{
    return currValues;
}

bst* Module::bstmgr::getRoot()
{
    return root;
}
