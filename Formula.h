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
    bool isOpeningParenthesis(const char& symbol);
    bool isClosingParenthesis(const char& symbol);
    bool isValidParenthesisSequence(const std::deque<char>& pStack);
    std::string getTextFormulaWithoutParenthesis(const std::string& textFormula);
    float getMultiplicator(const std::string& textFormula);
    std::string getFormulaWithoutMultiplicator(const std::string& textFormulaWithMultiplicator);
public:
    Formula(const std::string& rawTextFormula);

    bool isFormulaAtomary(const std::string& formula);

    const std::string &getRawTextFormula() const;
    void setRawTextFormula(const std::string &newRawTextFormula);
    FormulaTree *getTreeView() const;
    void setTreeView(FormulaTree *newTreeView);

    float getMolecularMass();
    std::vector<AtomInfo> getAllAtomsMass();
    void parse();
};

#endif // FORMULA_H
