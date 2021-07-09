#include "Formulatreenode.h"

const std::string &FormulaTreeNode::getRawTextFormula() const
{
    return rawTextFormula;
}

void FormulaTreeNode::setRawTextFormula(const std::string &newRawTextFormula)
{
    rawTextFormula = newRawTextFormula;
}

float FormulaTreeNode::getMultiplicator() const
{
    return multiplicator;
}

void FormulaTreeNode::setMultiplicator(float newMultiplicator)
{
    multiplicator = newMultiplicator;
}

FormulaTreeNode::FormulaTreeNode(const std::string rawTextFormula, float multiplicator)
{
    this->rawTextFormula = rawTextFormula;
    this->multiplicator = multiplicator;
}

std::vector<FormulaTreeNode*>& FormulaTreeNode::getNext()
{
    return this->next;
}

void FormulaTreeNode::setNext(const std::vector<FormulaTreeNode *>& next)
{
    this->next = next;
}
