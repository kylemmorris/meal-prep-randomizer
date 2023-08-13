/*
 * Meal Prep Randomizer
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 * 
 * FILE: Util.h
 *
 * DESCRIPTION: Common utilities for any file, including frequently-used functions and type definitions.
 *
 * SINCE: v1.0
 *
 */

#ifndef MPR_UTIL_H
#define MPR_UTIL_H

#include <string>
#include <vector>
#include <ctime>
#include <mutex>
#include <fstream>
#include <set>
#include <stdexcept>

namespace mpr {

    // TYPE DEFS

    /**
     * Shorthand for std::string.
    */
    typedef std::string         str;
    /**
     * Shorthand for std::vector<std::string>
    */
    typedef std::vector<str>    strvec;
    /**
     * Shorthand for std::set<std::string>
    */
    typedef std::set<str>       strset;

    /**
     * Merkaba-specific exception implementation.
    */
    class Exception : public std::exception {
    public:
        Exception(const str& msg) : _msg(msg) {}
        virtual const char* what() const noexcept override;
    private:
        const str _msg;
    };

    // END TYPE DEFS

    // UTILITY FUNCTIONS

    /**
     * @brief Attempts to open the file specified at filePath.
     * @param filePath Path to the file.
     * @param file The file stream being outputted.
     * @returns True if okay, false if not.
    */
    bool TryOpenFile(const str& filePath, std::ifstream& file);

    /**
     * @brief Separates a string via a delimeter sequence.
     * @param s - The input string.
     * @param separation The delimeter.
     * @param outVals The outputted string, separated.
     * @returns True if okay, false if separation was not found.
    */
    bool SeparateString(str s, str separation, strvec& outVals);

    /**
     * @brief Trims the character 'c' off each end of an input string.
     * @param s Input string.
     * @param c The characer to trim off.
    */
	void Trim(str& s, char c = ' ');

    // END UTILITY FUNCTIONS

};

#endif
