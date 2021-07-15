#ifndef FORMULA_H
#define FORMULA_H

#include <QObject>
#include <string>
#include <QDebug>
#include <deque>
#include "atomInfo.h"
#include "formulatree.h"

class Formula : public QObject {

    Q_OBJECT

public:
    Formula(const std::string& rawTextFormula);

    bool isFormulaAtomary(const std::string& formula);

    const std::string &getRawTextFormula() const;
    void setRawTextFormula(const std::string &newRawTextFormula);
    FormulaTree *getTreeView() const;
    void setTreeView(FormulaTree *newTreeView);

    float getMolecularMass();
    float getMolarMass();
    float getMolecularMassPercentageOfAtom(const AtomInfo* target);
    std::vector<AtomInfo> getAllAtomsMass();
    void parse();
public slots:
    void setFormulaText(std::string text);
signals:
    void parseResult(int resultCode, std::string description);
private:
    std::string rawTextFormula;
    FormulaTree* treeView;
    bool isOpeningParenthesis(const char& symbol);
    bool isClosingParenthesis(const char& symbol);
    bool isValidParenthesisSequence(const std::deque<char>& pStack);
    std::string getTextFormulaWithoutParenthesis(const std::string& textFormula);
    float getMultiplicator(const std::string& textFormula);
    std::string getFormulaWithoutMultiplicator(const std::string& textFormulaWithMultiplicator);
};

#endif // FORMULA_H
