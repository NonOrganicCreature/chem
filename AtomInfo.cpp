#include "AtomInfo.h"

const std::string &AtomInfo::getName() const
{
    return name;
}

void AtomInfo::setName(const std::string &newName)
{
    name = newName;
}

int AtomInfo::getGroup() const
{
    return group;
}

void AtomInfo::setGroup(int newGroup)
{
    group = newGroup;
}

int AtomInfo::getRow() const
{
    return row;
}

void AtomInfo::setRow(int newRow)
{
    row = newRow;
}

int AtomInfo::getPeriod() const
{
    return period;
}

void AtomInfo::setPeriod(int newPeriod)
{
    period = newPeriod;
}

int AtomInfo::getNuclearCharge() const
{
    return nuclearCharge;
}

void AtomInfo::setNuclearCharge(int newNuclearCharge)
{
    nuclearCharge = newNuclearCharge;
}

double AtomInfo::getRelativeAtomMass() const
{
    return relativeAtomMass;
}

void AtomInfo::setRelativeAtomMass(double newRelativeAtomMass)
{
    relativeAtomMass = newRelativeAtomMass;
}

const std::string &AtomInfo::getShortName() const
{
    return shortName;
}

void AtomInfo::setShortName(const std::string &newShortName)
{
    shortName = newShortName;
}
