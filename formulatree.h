#ifndef FORMULATREE_H
#define FORMULATREE_H

#include <string>
#include <vector>
#include "formulatreenode.h"
class FormulaTree
{
private:
    std::string rootRawTextFormula;
    FormulaTreeNode* root;
public:
    FormulaTree(const std::string& rootRawTextFormula);
    FormulaTreeNode *getRoot() const;
    void setRoot(FormulaTreeNode *newRoot);
    std::vector<FormulaTreeNode*> getLeaves();
    void printLeaves();
};

#endif // FORMULATREE_H
