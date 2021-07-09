#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <deque>
#include "AtomInfo.h"
#include "formulatree.h"
class Formula {
private:
    std::string rawTextFormula;
    FormulaTree* treeView;
    static bool isOpeningParenthesis(const char& symbol);
    static bool isClosingParenthesis(const char& symbol);
    static bool isValidParenthesisSequence(const std::deque<char>& pStack);
public:
    Formula(const std::string& rawTextFormula);

    const std::string &getRawTextFormula() const;
    void setRawTextFormula(const std::string &newRawTextFormula);
    FormulaTree *getTreeView() const;
    void setTreeView(FormulaTree *newTreeView);

    float getMolecularMass();
    std::vector<AtomInfo> getAllAtomsMass();
    void parse();
};

#endif // FORMULA_H
