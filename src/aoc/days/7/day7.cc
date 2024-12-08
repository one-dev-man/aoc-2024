#include "day7.hh"

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day7 = new Day(
    "7",
    "./resources/days/7/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> lines = strings::split(input, "\n");

        vector<pair<long, vector<long>>> equations = collections::map<string, pair<long, vector<long>>>(lines, [](string line) -> pair<long, vector<long>> {
            vector<string> linesplit = strings::split(line, ": ");

            vector<long> values = collections::map<string, long>(strings::split(linesplit[1], " "), [](string valueStr) -> long { return stol(valueStr.c_str()); });

            return pair(stol(linesplit[0]), values);
        });

        long testValueSum = 0;
        for(const pair<long, vector<long>> &equation : equations) {
            long testValue = equation.first;
            
            list<long> values = {};
            for(const long &v : equation.second) values.push_back(v);

            bool possiblyTrue = false;

            list<long> possibilities = { values.front() };
            values.pop_front();

            while(!values.empty()) {
                long value = values.front();
                values.pop_front();

                const size_t possibilityCount = possibilities.size();
                for(size_t j = 0; j < possibilityCount && !possiblyTrue; ++j) {
                    long possibility = possibilities.front();
                    possibilities.pop_front();

                    possibilities.push_back(possibility + value);
                    possibilities.push_back(possibility * value);
                }
            }

            if(collections::find(possibilities, testValue) != collections::nindex) testValueSum += testValue;
        }

        return to_string(testValueSum);
    }
);