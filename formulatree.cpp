#include "formulatree.h"
#include <queue>
#include <iostream>

FormulaTree::FormulaTree(const std::string& rootRawTextFormula)
{
    this->rootRawTextFormula = rootRawTextFormula;
    this->root = new FormulaTreeNode(rootRawTextFormula, 1);
}

FormulaTreeNode *FormulaTree::getRoot() const
{
    return root;
}

void FormulaTree::setRoot(FormulaTreeNode *newRoot)
{
    root = newRoot;
}

std::vector<FormulaTreeNode*> FormulaTree::getLeaves()
{
    FormulaTreeNode* currentNode = this->getRoot();
    std::queue<FormulaTreeNode*> walkPath;
    std::vector<FormulaTreeNode*> leaves;
    walkPath.push(currentNode);

    while(!walkPath.empty()) {
        currentNode = walkPath.front();
        walkPath.pop();
        for (FormulaTreeNode* nextNode: currentNode->getNext()) {
            if (nextNode->getNext().size() < 1) {
                leaves.push_back(nextNode);
            } else {
                walkPath.push(nextNode);
            }
        }
    }

    return leaves;
}

void FormulaTree::printLeaves()
{
    FormulaTreeNode* currentNode = this->getRoot();
    std::queue<FormulaTreeNode*> walkPath;
    walkPath.push(currentNode);

    std::cout << "Formula: ";
    while(!walkPath.empty()) {
        currentNode = walkPath.front();
        walkPath.pop();
        for (FormulaTreeNode* nextNode: currentNode->getNext()) {
            if (nextNode->getNext().size() < 1) {
                std::cout << nextNode->getRawTextFormula() << nextNode->getMultiplicator();
            } else {
                walkPath.push(nextNode);
            }
        }
    }
}
