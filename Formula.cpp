#include "formula.h"
#include "constants.h"
#include <deque>
#include <queue>
#include <vector>

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

float Formula::getMolecularMass()
{
    std::vector<FormulaTreeNode*> leaves = this->treeView->getLeaves();
    float resultMass = 0;
    for (FormulaTreeNode* leaf : leaves) {
        resultMass +=
                AtomsInfo.find(leaf->getRawTextFormula())
                    ->second
                    ->getRelativeAtomMass() * leaf->getMultiplicator();
    }

    return resultMass;
}

float Formula::getMolarMass()
{
    return this->getMolarMass();
}

float Formula::getMolecularMassPercentageOfAtom(const AtomInfo* target)
{
    std::vector<FormulaTreeNode*> leaves = this->treeView->getLeaves();
    float totalMass = 0;
    float targetMass = 0;
    for (FormulaTreeNode* leaf : leaves) {
        if (leaf->getRawTextFormula() == target->getShortName()) {
            targetMass += AtomsInfo.find(leaf->getRawTextFormula())
                    ->second
                    ->getRelativeAtomMass() * leaf->getMultiplicator();
        }
        totalMass +=
                AtomsInfo.find(leaf->getRawTextFormula())
                    ->second
                    ->getRelativeAtomMass() * leaf->getMultiplicator();
    }

    if (targetMass == 0) {
        return 0;
    }

    return (targetMass / totalMass) * 100 ;
}





void Formula::parse()
{
    FormulaTree* tree = this->getTreeView();
    std::deque<char> parenthesisSequence;
    std::string currentFormulaPartBuffer;
    std::queue<FormulaTreeNode*> walkPath;
    walkPath.push(tree->getRoot());
    while(!walkPath.empty()) {
        FormulaTreeNode* ftn = walkPath.front();
        walkPath.pop();
        std::string currentRawTextFormula = ftn->getRawTextFormula();

        // if at tree node we have only atom and multiplicator
        if (isFormulaAtomary(currentRawTextFormula)) {
            continue;
        }
        for (int i = 0; i < currentRawTextFormula.size(); i++) {
            char currentSymbol = currentRawTextFormula[i];
            if (
                    !std::isdigit(currentSymbol)
                    && !isOpeningParenthesis(currentSymbol)
            ) {
                if (std::isupper(currentSymbol)) {
                    currentFormulaPartBuffer += currentSymbol;

                    // start with next symbol after upper letter to read atom short name
                    i += 1;

                    // read from text formula string symbols while they are in lower case(to read whole element name)
                    while (currentRawTextFormula[i] && !(std::isupper(currentRawTextFormula[i]) ||
                        isOpeningParenthesis(currentRawTextFormula[i]) ||
                        isClosingParenthesis(currentRawTextFormula[i]))) {
                        char lowerCaseLetter = currentRawTextFormula[i];
                        currentFormulaPartBuffer += lowerCaseLetter;
                        i += 1;
                    }

                    // creating result node
                    FormulaTreeNode* newFTN = new FormulaTreeNode(
                        getFormulaWithoutMultiplicator(currentFormulaPartBuffer),
                        getMultiplicator(currentFormulaPartBuffer) * ftn->getMultiplicator()
                    );

                    walkPath.push(newFTN);
                    ftn->getNext().push_back(
                        newFTN
                    );

                    currentFormulaPartBuffer.clear();

                    // while at 56 line of code increases to next symbol for checking, but for loop increases after continue too
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
                        parenthesisSequence.push_back(symbolBetweenParenthesis);
                    }

                    currentFormulaPartBuffer += symbolBetweenParenthesis;

                    if (isValidParenthesisSequence(parenthesisSequence)) {
                        // if next after parenthesis is digit then parse rest of the formula (multiplicator)
                        if (std::isdigit(rawTextFormula[j + 1])) {
                            j += 1;
                            while(std::isdigit(rawTextFormula[j])) {
                                currentFormulaPartBuffer += rawTextFormula[j];
                                j += 1;
                            }
                        }

                        // creating result node
                        FormulaTreeNode* newFTN = new FormulaTreeNode(
                            getTextFormulaWithoutParenthesis(getFormulaWithoutMultiplicator(currentFormulaPartBuffer)),
                            getMultiplicator(currentFormulaPartBuffer) * ftn->getMultiplicator()
                        );

                        walkPath.push(newFTN);
                        ftn->getNext().push_back(
                            newFTN
                        );

                        currentFormulaPartBuffer.clear();
                        i = j;
                        break;
                    }
                }
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

std::string Formula::getTextFormulaWithoutParenthesis(const std::string &textFormula)
{
    return textFormula.substr(1, textFormula.size() - 2);
}

float Formula::getMultiplicator(const std::string &textFormula)
{
    int currentIndex = textFormula.size() - 1;
    if (!std::isdigit(textFormula[currentIndex])) {
        return 1;
    }

    std::string multiplicatorBuffer = "";
    while (std::isdigit(textFormula[currentIndex])) {
        multiplicatorBuffer += textFormula[currentIndex];
        currentIndex -= 1;
    }

    std::string multiplicatorBufferReversed = "";
    for (int i = multiplicatorBuffer.size() - 1; i >= 0; i--) {
        multiplicatorBufferReversed += multiplicatorBuffer[i];
    }
    return std::stof(multiplicatorBufferReversed);
}

std::string Formula::getFormulaWithoutMultiplicator(const std::string &textFormulaWithMultiplicator)
{
    int currentIndex = textFormulaWithMultiplicator.size() - 1;
    if (!std::isdigit(textFormulaWithMultiplicator[currentIndex])) {
        return textFormulaWithMultiplicator;
    }

    while (std::isdigit(textFormulaWithMultiplicator[currentIndex])) {
        currentIndex -= 1;
    }

    return textFormulaWithMultiplicator.substr(0, currentIndex + 1);
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

bool Formula::isFormulaAtomary(const std::string &formula)
{
    return AtomsInfo.find(formula)->second;
}
