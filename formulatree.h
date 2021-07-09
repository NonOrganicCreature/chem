#ifndef FORMULATREE_H
#define FORMULATREE_H

#include <string>
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
};

#endif // FORMULATREE_H
