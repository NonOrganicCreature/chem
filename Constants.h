#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <map>
#include <string>
#include "AtomInfo.h"

static const std::map<const std::string, const AtomInfo*> AtomsInfo = {
    // 1
    {
        std::string("H"),
        new AtomInfo(
                    std::string("H"),
                    std::string("Hydrogenium"), 1, 1, 1, 1, 1.074)
    },

    // 6
    {
        std::string("C"),
        new AtomInfo(std::string("C"), std::string("Carbon"), 4, 2, 2, 6, 12.011)
    },

    // 8
    {
        std::string("O"),
        new AtomInfo(std::string("O"), std::string("Oxygenium"), 6, 2, 2, 8, 15.999)
    },

    // 9
    {
        std::string("F"),
        new AtomInfo(std::string("F"), std::string("Fluorum"), 7, 2, 2, 9, 18.998)
    },

    // 11
    {
        std::string("Na"),
        new AtomInfo(std::string("Na"), std::string("Natrium"), 1, 3, 3, 11, 22.990)
    },



};

static const double angstrem = 1.0e-10;
static const double Na = 6.02e23;

#endif // CONSTANTS_H
