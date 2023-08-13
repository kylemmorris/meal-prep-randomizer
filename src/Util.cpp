/*
 * Meal Prep Randomizer
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 * 
 * FILE: Util.cpp
 *
 * DESCRIPTION: Common utilities for any file, including frequently-used functions and type definitions.
 *
 * SINCE: v0.1
 *
 */

#include <chrono>
#include <ctime>
#include <time.h>
#include <sys/stat.h>
#include <cstdlib>
#include "include/Util.h"

namespace mpr {

    const char* Exception::what() const noexcept {
            return _msg.c_str();
    }

    bool TryOpenFile(const str& filePath, std::ifstream& file) {
		// Check file status before anything else.
		struct stat st = { 0 };
		if (stat(filePath.c_str(), &st) == -1) {
            throw Exception("Could not find file: " + filePath);
			return false;
		}
		file.open(filePath, std::ios::out | std::ios::out);
		if (!file.is_open()) {
            throw Exception("Could not open file: " + filePath);
			file.close();
			return false;
		}
		return true;
	}

    bool SeparateString(str s, str separation, strvec& outVals) {
        outVals.clear();
		size_t len = separation.length();
		size_t index = s.find(separation);
		// If this does not contain the separation character, return false
		if (index == std::string::npos) {
			outVals.push_back(s);
			return false;
		}
		while (index != std::string::npos) {
			auto val = s.substr(0, index);
			if (val != "") {
				outVals.push_back(s.substr(0, index));
			}
			s.erase(0, index + len);
			index = s.find(separation);
		}
		// Last value won't have char after it
		Trim(s);
		outVals.push_back(s);
		return true;
    }

	void Trim(str& s, char c) {
        if (!s.empty()) {
			while (s[0] == c) { s.erase(s.begin(), s.begin() + 1); }
			while (s[s.length() - 1] == c) { s.erase(s.length() - 1); }
		}
    }

};