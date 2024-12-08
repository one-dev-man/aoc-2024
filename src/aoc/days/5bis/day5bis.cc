#include "day5bis.hh"

// 

static bool isUpadteValid(const vector<int> &update, map<int, vector<int>> &ruleMap) {
    bool isValid = true;
    
    for(
        vector<int>::const_iterator it = update.begin(), itend = update.end()-1;
        (
            it != itend
            && isValid
        );
        ++it
    ) {
        int current = *it;
        int next = *(it+1);

        isValid = ruleMap.contains(current) && (collections::find<int>(ruleMap[current], next) != collections::nindex);
    }

    return isValid;
}

static void fixUpdate(vector<int> &update, map<int, vector<int>> &ruleMap) {
    bool foundError = false;
    for(
        vector<int>::iterator it = update.begin(), itend = update.end()-1;
        it != itend;
        ++it
    ) {
        int current = *it;
        int next = *(it+1);

        if(!(ruleMap.contains(current) && (collections::find<int>(ruleMap[current], next) != collections::nindex))) {
            foundError = true;
            *it = next;
            *(it+1) = current;
        }
    }

    if(foundError) fixUpdate(update, ruleMap);
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day5bis = new Day(
    "5bis",
    "./resources/days/5/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> inputSplit = strings::split(input, "\n\n");

        vector<pair<int, int>> rules = collections::map<string, pair<int, int>>(
            strings::split(inputSplit[0], "\n"),
            [](string ruleLine) -> pair<int, int> {
                vector<int> ruleLineSplit = collections::map<string, int>(
                    strings::split(ruleLine, "|"),
                    [](string pageNumStr) -> int { return atoi(pageNumStr.c_str()); }
                );

                return pair(ruleLineSplit[0], ruleLineSplit[1]);
            }
        );

        vector<vector<int>> updates = collections::map<string, vector<int>>(
            strings::split(inputSplit[1], "\n"),
            [](string updateLine) {
                return collections::map<string, int>(
                    strings::split(updateLine, ","),
                    [](string pageNumStr) -> int { return atoi(pageNumStr.c_str()); }
                );
            }
        );

        map<int, vector<int>> ruleMap;
        for(const pair<int, int> &rule : rules) ruleMap[rule.first].push_back(rule.second);

        int resultScore = 0;

        for(const vector<int> &update : updates) {
            vector<int> updateCopy(update);
            if(!isUpadteValid(update, ruleMap)) {
                fixUpdate(updateCopy, ruleMap);

                const int updateCopySize = updateCopy.size();
                resultScore += updateCopy[(int) (updateCopySize / 2)];
            }
        }

        return to_string(resultScore);
    }
);