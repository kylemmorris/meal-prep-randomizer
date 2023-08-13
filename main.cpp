/*
 * Meal Prep Randomizer
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 * 
 * FILE: main.cpp
 *
 * DESCRIPTION: Starting point of the program.
 *
 * SINCE: v1.0
 *
 */

#ifndef MPR_H
#define MPR_H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include "include/RunFile.h"

static mpr::str Version = "v1.0";
static mpr::str Cat1 = "Protein";
static mpr::str Cat2 = "Veggies";
static mpr::str Cat3 = "Fat";
static mpr::str Cat4 = "Base";

/**
 * @brief Basic output function.
*/
void out(const std::string& in = "") {
    std::cout << "* " << in << std::endl;
}

/**
 * @brief Gets each value from the config file in the catergory "name".
*/
mpr::strvec populate(const mpr::RunFile& inFile, mpr::str name, size_t n) {
    mpr::strvec ret;
    for(size_t i = 0; i < n; i++) {
        ret.push_back(inFile.GetString(name, i));
    }
    return ret;
}

/**
 * @brief Gets a random element from the inputted vector.
*/
mpr::str getRandomElement(mpr::strvec& vec) {
    std::srand(unsigned(time(NULL)));
    std::random_shuffle(vec.begin(), vec.end());
    return vec[0];
}

/**
 * @brief Main function.
*/
int main(int argc, char* argv[]) {
    out("Meal Prep Randomizer");
    out("Version " + Version);
    out();

    if(argc != 2) {
        out("Usage: mpr <path to *.mpr file>");
        return 1;
    }

    mpr::str s = mpr::str(argv[1]);

    mpr::RunFile conf;
    conf.AddRequired(Cat1);
    conf.AddRequired(Cat2);
    conf.AddRequired(Cat3);
    conf.AddRequired(Cat4);

    if(!conf.Open(s)) {
        return 1;
    }

    // Create an array for each
    size_t nP = conf.GetNumOfValues(Cat1);
    size_t nV = conf.GetNumOfValues(Cat2);
    size_t nF = conf.GetNumOfValues(Cat3);
    size_t nB = conf.GetNumOfValues(Cat4);
    
    auto proteins = populate(conf, Cat1, nP);
    auto veggies = populate(conf, Cat2, nV);
    auto fats = populate(conf, Cat3, nF);
    auto bases = populate(conf, Cat4, nB);

    // Randomize like such:
    // 1 Protein
    // 2 Veggies
    // 1 Fat
    // 1 Base

    out("YOUR MEAL PREP:");
    out("Protein: " + getRandomElement(proteins));
    
    out("Veggie 1: " + getRandomElement(veggies));
    veggies.erase(veggies.begin());
    out("Veggie 2: " + getRandomElement(veggies));

    out("Fat: " + getRandomElement(fats));
    
    out("Base: " + getRandomElement(bases));

    return 0;
}

#endif
