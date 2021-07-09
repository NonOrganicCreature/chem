#include "formulatree.h"

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
