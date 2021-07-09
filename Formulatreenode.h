#ifndef FORMULATREENODE_H
#define FORMULATREENODE_H

#include <vector>
#include <string>

class FormulaTreeNode
{
private:
    std::vector<FormulaTreeNode*> next;
    std::string rawTextFormula;
    float multiplicator;
public:
    FormulaTreeNode(const std::string rawTextFormula, float multiplicator);

    std::vector<FormulaTreeNode*>& getNext();
    void setNext(const std::vector<FormulaTreeNode*>& next);
    const std::string &getRawTextFormula() const;
    void setRawTextFormula(const std::string &newRawTextFormula);
    float getMultiplicator() const;
    void setMultiplicator(float newMultiplicator);
};

#endif // FORMULATREENODE_H
