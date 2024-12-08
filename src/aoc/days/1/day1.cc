#include "day1.hh"

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day1 = new Day(
    "1",
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

        int distanceSum = 0;

        size_t l = lists.first.size();
        for(size_t i = 0; i < l; ++i) {
            int a = lists.first[i];
            int b = lists.second[i];

            distanceSum += abs(b-a);
        }

        return to_string(distanceSum);
    }
);