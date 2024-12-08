#include "day2bis.hh"

// 

static float sign(float x) {
    return x > 0 ? 1 : x == 0 ? 0 : -1;
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
static int previousLevelDifferenceGetter(
    void** previousLevelDifferenceGetterPtr,
    int currentLevelDifference,
    int previousLevelDifference
) {
    return previousLevelDifference;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
static int initialPreviousLevelDifferenceGetter(
    void** previousLevelDifferenceGetterPtr,
    int currentLevelDifference,
    int previousLevelDifference
) {
    *previousLevelDifferenceGetterPtr = (void*) previousLevelDifferenceGetter;
    return currentLevelDifference;
}

// 

bool testReport(vector<int> report) {
    const size_t reportSize = report.size();
    
    int previousLevel;
    int currentLevel;

    int previousLevelDifference;
    
    int currentLevelDifference = 0;
    int currentLevelDistance;

    int (*previousLevelDifferenceGetter)(
        void** previousLevelDifferenceGetterPtr,
        int currentLevelDifference,
        int previousLevelDifference
    ) = initialPreviousLevelDifferenceGetter;

    int contextualPreviousLevelDifference;
    
    bool isReportSafe = true;

    for(size_t currentLevelIndex = 1; currentLevelIndex < reportSize && isReportSafe; ++currentLevelIndex) {
        previousLevel = report[currentLevelIndex-1];
        currentLevel = report[currentLevelIndex];

        previousLevelDifference = currentLevelDifference;
        currentLevelDifference = currentLevel - previousLevel;
        currentLevelDistance = abs(currentLevelDifference);
        
        contextualPreviousLevelDifference = previousLevelDifferenceGetter((void**) &previousLevelDifferenceGetter, currentLevelDifference, previousLevelDifference);

        isReportSafe = sign(contextualPreviousLevelDifference) == sign(currentLevelDifference) && 1 <= currentLevelDistance && currentLevelDistance <= 3;
    }

    return isReportSafe;
}

// 

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day2bis = new Day(
    "2bis",
    "./resources/days/2/input.txt",
    [](const string &input, ostream &logs) -> string {
        vector<string> inputLines = strings::split(input, "\n");
        vector<vector<int>> reports = {};

        for(const string &line : inputLines) {
            vector<string> lineSplit = strings::split(line, " ");
            vector<int> report = {};

            for(const string &levelStr : lineSplit) {
                int level = atoi(levelStr.c_str());
                report.push_back(level);
            }

            reports.push_back(report);
        }

        // 

        size_t safeReportCount = 0;
        for(const vector<int> &report : reports) {
            const size_t reportSize = report.size();
            bool reportTestResult = testReport(report);

            if(reportTestResult) safeReportCount++;
            else {
                bool reportVariantTestResult = false;
                
                for(size_t i = 0; i < reportSize && !reportVariantTestResult; ++i) {
                    vector<int> reportVariant(report);
                    reportVariant.erase(reportVariant.begin() + i);
                
                    reportVariantTestResult = testReport(reportVariant);
                }

                if(reportVariantTestResult) safeReportCount++;
            }
        }

        //

        return to_string(safeReportCount);
    }
);