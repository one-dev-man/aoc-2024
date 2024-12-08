#include "day7bis.hh"

// 

// static unsigned long long power(unsigned long long n, unsigned long long p) {
//     unsigned long long result = 1;
//     for(unsigned long long i = 0; i < p; ++i) result *= n;
//     return n;
// }

// 

// static unsigned long long concatDigit(unsigned long long a, unsigned long long b) {
//     return a * power(10, ceilf128(log10f128(b))) + b;
// }

static unsigned long long concatDigit(unsigned long long a, unsigned long long b) {
    string r = "";
    std::stringstream sr;
    
    sr << a << b;
    sr >> r;

    return stoull(r);
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day7bis = new Day(
    "7bis",
    "./resources/days/7/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> lines = strings::split(input, "\n");

        vector<pair<unsigned long long, vector<unsigned long long>>> equations = collections::map<string, pair<unsigned long long, vector<unsigned long long>>>(lines, [](string line) -> pair<unsigned long long, vector<unsigned long long>> {
            vector<string> linesplit = strings::split(line, ": ");

            vector<unsigned long long> values = collections::map<string, unsigned long long>(strings::split(linesplit[1], " "), [](string valueStr) -> unsigned long long { return stoull(valueStr.c_str()); });

            return pair(stoull(linesplit[0]), values);
        });

        unsigned long long testValueSum = 0;
        for(const pair<unsigned long long, vector<unsigned long long>> &equation : equations) {
            unsigned long long testValue = equation.first;
            
            list<unsigned long long> values = {};
            for(const unsigned long long &v : equation.second) values.push_back(v);

            list<unsigned long long> possibilities = { values.front() };
            values.pop_front();

            while(!values.empty()) {
                unsigned long long value = values.front();
                values.pop_front();

                const size_t possibilityCount = possibilities.size();
                for(size_t j = 0; j < possibilityCount; ++j) {
                    unsigned long long possibility = possibilities.front();
                    possibilities.pop_front();

                    unsigned long long r1 = possibility + value;
                    unsigned long long r2 = possibility * value;
                    unsigned long long r3 = concatDigit(possibility, value);

                    // Check if results still have a chance to be equals to the test value before save them.
                    if(r1 <= testValue) possibilities.push_back(r1);
                    if(r2 <= testValue) possibilities.push_back(r2);
                    if(r3 <= testValue) possibilities.push_back(r3);
                }
            }

            if(collections::find(possibilities, testValue) != collections::nindex) testValueSum += testValue;
        }

        return to_string(testValueSum);
    }
);