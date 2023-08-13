/*
 * Meal Prep Randomizer
 * (C) Kyle Morris 2023 - See LICENSE.txt for license information.
 * 
 * FILE: RunFile.h
 *
 * DESCRIPTION: Built-in configuration file used in its CLI.
 *
 * SINCE: v1.0
 *
 */

#ifndef MPR_RUNFILE_H
#define MPR_RUNFILE_H

#include <map>
#include "Util.h"

namespace mpr {

    /**
     * The input config file used by MPR.
     * Contains information such as source files
     * to run, and various options.
    */
	class RunFile final {
    public:
        RunFile();
        void AddRequired(const str& req);
        bool Open(const str& filePath);
        int     GetInt      (const str& name, size_t index = 0ull, int defaultVal = 0) const;
        float   GetFloat    (const str& name, size_t index = 0ull, float defaultVal = 0.0f) const;
        double  GetDouble   (const str& name, size_t index = 0ull, double defaultVal = 0.0) const;
        bool    GetBool     (const str& name, size_t index = 0ull, bool defaultVal = false) const;
        str     GetString   (const str& name, size_t index = 0ull, str defaultVal = "") const;
        size_t  GetNumOfValues(const str& name) const;
    private:
        void _checkRequired(const str& name) const;
        strset _required;
        std::map<str,strvec> _data;
    };

};

#endif
