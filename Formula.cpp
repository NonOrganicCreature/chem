#include "Formula.h"
#include <deque>
#include <queue>

const std::string &Formula::getRawTextFormula() const
{
    return rawTextFormula;
}

void Formula::setRawTextFormula(const std::string &newRawTextFormula)
{
    rawTextFormula = newRawTextFormula;
}

FormulaTree *Formula::getTreeView() const
{
    return treeView;
}

void Formula::setTreeView(FormulaTree *newTreeView)
{
    treeView = newTreeView;
}



void Formula::parse()
{
    FormulaTree* tree = this->getTreeView();
    std::deque<char> parenthesisSequence;
    std::string parenthesisBuffer;
    std::string currentFormulaPartBuffer;
    std::string currentFormulaPartMultiplicatorBuffer;
    std::queue<FormulaTreeNode*> walkPath;
    walkPath.push(tree->getRoot());
    while(!walkPath.empty()) {
        FormulaTreeNode* ftn = walkPath.front();
        walkPath.pop();
        std::string currentRawTextFormula = ftn->getRawTextFormula();
        for (int i = 0; i < currentRawTextFormula.size(); i++) {
            char currentSymbol = currentRawTextFormula[i];
            if (
                    !std::isdigit(currentSymbol)
                    && currentSymbol != '('
                    && currentSymbol != '['
            ) {
                currentFormulaPartBuffer += currentSymbol;
                continue;
            }

            if (std::isdigit(currentSymbol)) {
                for (int j = i;;j++) {
                    char potentialDigit = currentRawTextFormula[j];
                    if (
                            !isOpeningParenthesis(potentialDigit)
                            && !std::isalpha(potentialDigit)
                    ) {
                        currentFormulaPartMultiplicatorBuffer += potentialDigit;
                    } else {
                        i = j;
                        break;
                    }
                }
                FormulaTreeNode* newFTN = new FormulaTreeNode(
                    currentFormulaPartBuffer,
                    std::stof(currentFormulaPartMultiplicatorBuffer)
                );

                walkPath.push(newFTN);
                ftn->getNext().push_back(
                    newFTN
                );

                currentFormulaPartBuffer.erase();
                currentFormulaPartMultiplicatorBuffer.erase();
                continue;
            }

            if (isOpeningParenthesis(currentSymbol)) {
                for (int j = i;; j++) {
                    char symbolBetweenParenthesis = currentRawTextFormula[j];

                    if (
                        isOpeningParenthesis(symbolBetweenParenthesis)
                        || isClosingParenthesis(symbolBetweenParenthesis)
                    ) {
                        parenthesisBuffer.push_back(symbolBetweenParenthesis);
                        parenthesisSequence.push_back(symbolBetweenParenthesis);
                    }

                    currentFormulaPartBuffer += symbolBetweenParenthesis;

                    if (isValidParenthesisSequence(parenthesisSequence)) {
                        if (std::isalpha(symbolBetweenParenthesis)) {
                            i = j;
                            break;
                        } else {
                            for (int k = j;;k++) {
                                char potentialDigit = currentRawTextFormula[k];
                                if (
                                        !isOpeningParenthesis(potentialDigit)
                                        && !std::isalpha(potentialDigit)
                                ) {
                                    currentFormulaPartMultiplicatorBuffer += potentialDigit;
                                } else {
                                    i = k;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }

                FormulaTreeNode* newFTN = new FormulaTreeNode(
                    currentFormulaPartBuffer,
                    std::stof(currentFormulaPartMultiplicatorBuffer)
                );

                walkPath.push(newFTN);
                ftn->getNext().push_back(
                    newFTN
                );

                currentFormulaPartBuffer.erase();
                currentFormulaPartMultiplicatorBuffer.erase();
            }
        }
    }
}


bool Formula::isClosingParenthesis(const char& symbol)
{
    return symbol == ')' || symbol == ']';
}

bool Formula::isValidParenthesisSequence(const std::deque<char>& pDeq)
{
    if (pDeq.size() < 2) {
        return false;
    }
    std::deque<char> st = pDeq;
    while (!st.empty()) {
        if (st.front() == st.back()) {
            st.pop_back();
            st.pop_front();
        } else {
            return false;
        }
    }

    return true;
}

bool Formula::isOpeningParenthesis(const char& symbol)
{
    return symbol == '(' || symbol == '[';
}

Formula::Formula(const std::string& rawTextFormula)
{
    this->rawTextFormula = rawTextFormula;
    this->treeView = new FormulaTree(rawTextFormula);
}
