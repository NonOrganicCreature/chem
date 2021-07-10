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
                    && !isOpeningParenthesis(currentSymbol)
            ) {
                if (std::isupper(currentSymbol)) {
                    currentFormulaPartBuffer += currentSymbol;

                    // start with next symbol after upper letter
                    i += 1;

                    // read from text formula string symbols while they are in lower case(to read whole element name)
                    while (!(std::isupper(currentRawTextFormula[i]) ||
                        isOpeningParenthesis(currentRawTextFormula[i]) ||
                        isClosingParenthesis(currentRawTextFormula[i]))) {
                        char lowerCaseLetter = currentRawTextFormula[i];
                        currentFormulaPartBuffer += lowerCaseLetter;
                        i += 1;
                    }

                    // parsing multiplicator
                    currentFormulaPartMultiplicatorBuffer = currentFormulaPartBuffer;
                    int letterCount = 0;
                    while (std::isalpha(currentFormulaPartMultiplicatorBuffer[0])) {
                        letterCount += 1;
                        currentFormulaPartMultiplicatorBuffer =
                                currentFormulaPartMultiplicatorBuffer.substr(1, currentFormulaPartMultiplicatorBuffer.size());
                    }

                    float multiplicator = currentFormulaPartMultiplicatorBuffer.size() > 0 ? std::stof(currentFormulaPartMultiplicatorBuffer) : 1;

                    FormulaTreeNode* newFTN = new FormulaTreeNode(
                        currentFormulaPartBuffer.substr(0, letterCount),
                        multiplicator
                    );

                    walkPath.push(newFTN);
                    ftn->getNext().push_back(
                        newFTN
                    );

                    currentFormulaPartBuffer.erase();
                    currentFormulaPartMultiplicatorBuffer.erase();
                    // decrease
                    i -= 1;
                    continue;
                }
            }


            // parsing parentheis content
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
                        if (std::isalpha(currentRawTextFormula[j + 1])) {
                            i = j + 1;
                            break;
                        } else {
                            for (int k = j + 1;;k++) {
                                char potentialDigit = currentRawTextFormula[k];
                                if (
                                        std::isdigit(potentialDigit)
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
        if (isOpeningParenthesis(st.front()) && isClosingParenthesis(st.back())) {
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
