/*
 * Meal Prep Randomizer
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 * 
 * FILE: RunFile.cpp
 *
 * DESCRIPTION: Implementation of the RunFile.
 *
 * SINCE: v1.0
 *
 */

#include <fstream>
#include "include/RunFile.h"

namespace mpr {

	RunFile::RunFile() {}

	void RunFile::AddRequired(const str& req) {
		_required.insert(req);
	}

	bool RunFile::Open(const str& filePath) {
        _data.clear();
		std::ifstream file;
		if (!TryOpenFile(filePath, file)) {
			file.close();
			return false;
		}
		//dat.clear();
		file.clear();
		file.seekg(0);
		std::string line;
		while (std::getline(file, line)) {
			if (line.length() == 0) { continue; }
			if (line[0] == '#') { continue; }
			Trim(line);
			strvec lineContents;
			if (SeparateString(line, "=", lineContents)) {
				if (lineContents.size() == 2) {
					Trim(lineContents[0]);
					Trim(lineContents[1]);
					// If it already exists
					if (_data.find(lineContents[0]) != _data.end()) {
						_data.at(lineContents[0]).push_back(lineContents[1]);
					}
					else {
						std::vector<std::string> temp;
						temp.push_back(lineContents[1]);
						_data.insert(std::make_pair(
							lineContents[0],
							temp
						));
					}
				}
				else if (lineContents.size() == 1) {
					Trim(lineContents[0]);
					// If it already exists
					if (_data.find(lineContents[0]) != _data.end()) {
						_data.at(lineContents[0]).push_back(lineContents[1]);
					}
					else {
						std::vector<std::string> temp;
						_data.insert(std::make_pair(
							lineContents[0],
							temp
						));
					}
				}
			}
		}
		file.close();
		return true;
    }

    int RunFile::GetInt(const str& name, size_t index, int defaultVal) const {
		int ret = defaultVal;
		try {
			ret = std::stoi(_data.at(name).at(index));
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return ret;
	}

    float RunFile::GetFloat(const str& name, size_t index, float defaultVal) const {
		float ret = defaultVal;
		try {
			ret = std::stof(_data.at(name).at(index));
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return ret;
	}

	double RunFile::GetDouble(const str& name, size_t index, double defaultVal) const {
		double ret = defaultVal;
		try {
			ret = std::stod(_data.at(name).at(index));
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return ret;
	}

    bool RunFile::GetBool(const str& name, size_t index, bool defaultVal) const {
		bool ret = defaultVal;
		try {
			str s = _data.at(name).at(index);
            if(s == "true" || "TRUE" || "T") {
                ret = true;
            } 
            else if(s == "false" || s == "FALSE" || s == "F") {
                ret = false;
            }
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return ret;
	}

	str RunFile::GetString(const str& name, size_t index, std::string defaultVal) const {
		std::string ret = defaultVal;
		try {
			ret = _data.at(name).at(index);
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return ret;
	}

	size_t RunFile::GetNumOfValues(const str& name) const {
		try {
			return _data.at(name).size();
		}
		catch (std::exception e) {
			_checkRequired(name);
		}
		return 0ull;
	}

	void RunFile::_checkRequired(const str& name) const {
		if(_required.find(name) != _required.end()) {
			throw Exception("Required configuration parameter is missing: " + name);
		}
	}

};