#include "day1bis.hh"

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day1bis = new Day(
    "1bis",
    "./resources/days/1/input.txt",
    [](const string &input, ostream &logs) -> string {
        pair<vector<int>, vector<int>> lists = { {}, {} };
    
        for(const string &line : strings::split(input, "\n")) {
            const vector<string> linesplit = strings::split(line, "   ");
            lists.first.push_back(atoi(linesplit.front().c_str()));
            lists.second.push_back(atoi(linesplit.back().c_str()));
        }

        // 

        sort(lists.first.begin(), lists.first.end(), [](int x, int y) -> bool { return x <= y; });
        sort(lists.second.begin(), lists.second.end(), [](int x, int y) -> bool { return x <= y; });

        size_t similarityScore = 0;

        size_t l = lists.first.size();
        for(size_t i = 0; i < l; ++i) {
            const int value = lists.first[i];
            size_t count = 0;

            for(size_t j = 0; j < l; ++j) {
                if(value == lists.second[j]) count++;
            }

            similarityScore += value * count;
        }

        return to_string(similarityScore);
    }
);