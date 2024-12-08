#include "day3.hh"

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day3 = new Day(
    "3",
    "./resources/days/3/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> lines = strings::split(input, "\n");

        //

        regex mulOpPattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");

        size_t total = 0;
        for(const string &line : lines) {
            regex_iterator mulOpMatchesIteratorBegin = sregex_iterator(line.begin(), line.end(), mulOpPattern);
            sregex_iterator mulOpMatchesIteratorEnd = sregex_iterator();

            for(sregex_iterator mulOpMatchPtr = mulOpMatchesIteratorBegin; mulOpMatchPtr != mulOpMatchesIteratorEnd; ++mulOpMatchPtr) {
                smatch match = *mulOpMatchPtr;
                string mulOpStr = match.str().substr(4);
                mulOpStr.pop_back();

                vector<short> mulArgs = collections::map<string, short>(strings::split(mulOpStr, ","), [](string value) -> short { return atoi(value.c_str()); });
                
                size_t mulResult = mulArgs[0] * mulArgs[1];
                total += mulResult;
            }
        }

        return to_string(total);
    }
);