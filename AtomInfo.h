#ifndef ATOMINFO_H
#define ATOMINFO_H
#include <string>

class AtomInfo
{
private:
    std::string shortName;
    std::string name;
    int group;
    int row;
    int period;
    int nuclearCharge;
    double relativeAtomMass;
public:

    const std::string &getShortName() const;
    void setShortName(const std::string &newShortName);
    const std::string &getName() const;
    void setName(const std::string &newName);
    int getGroup() const;
    void setGroup(int newGroup);
    int getRow() const;
    void setRow(int newRow);
    int getPeriod() const;
    void setPeriod(int newPeriod);
    int getNuclearCharge() const;
    void setNuclearCharge(int newNuclearCharge);
    double getRelativeAtomMass() const;
    void setRelativeAtomMass(double newRelativeAtomMass);
};

#endif // ATOMINFO_H
