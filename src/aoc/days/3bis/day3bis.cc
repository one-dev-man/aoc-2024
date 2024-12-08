#include "day3bis.hh"

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day3bis = new Day(
    "3bis",
    "./resources/days/3/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> lines = strings::split(input, "\n");

        //

        regex mulOpPattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");
        regex opPattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)|do\\(\\)|don't\\(\\)");

        bool canDo = true;

        size_t total = 0;
        for(const string &line : lines) {
            regex_iterator opMatchesIteratorBegin = sregex_iterator(line.begin(), line.end(), opPattern);
            sregex_iterator opMatchesIteratorEnd = sregex_iterator();

            for(sregex_iterator opMatchPtr = opMatchesIteratorBegin; opMatchPtr != opMatchesIteratorEnd; ++opMatchPtr) {
                smatch match = *opMatchPtr;
                string opStr = match.str();

                if(opStr.compare("do()") == 0) canDo = true;
                else if(opStr.compare("don't()") == 0) canDo = false;
                else if(canDo && regex_match(opStr, mulOpPattern)) {
                    string mulOpStr = opStr.substr(4);
                    mulOpStr.pop_back();

                    vector<short> mulArgs = collections::map<string, short>(strings::split(mulOpStr, ","), [](string value) -> short { return atoi(value.c_str()); });
                    
                    size_t mulResult = mulArgs[0] * mulArgs[1];
                    total += mulResult;
                }
            }
        }

        return to_string(total);
    }
);