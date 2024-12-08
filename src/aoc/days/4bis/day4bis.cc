#include "day4bis.hh"

//

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day4bis = new Day(
    "4bis",
    "./resources/days/4/input.txt",
    [](const string &input, ostream &logs) -> string {
        size_t totalCrossCount = 0;

        vector<string> lines = strings::split(input, "\n");

        const size_t lineCount = lines.size();
        const size_t lineLength = lines[0].length();
        
        for(size_t lineIndex = 1; lineIndex < lineCount-1; ++lineIndex) {
            for(size_t charIndex = 1; charIndex < lineLength-1; ++charIndex) {
                char center = lines[lineIndex][charIndex];

                if(center == 'A') {
                    char corners[4];
                    int cornerFillIndex = 0;
                    
                    for(int i = -1; i < 2; i+=2) {
                        for(int j = -1; j < 2; j+=2) {
                            corners[cornerFillIndex] = lines[lineIndex+i][charIndex+(j*(-i))];
                            cornerFillIndex++;
                        }
                    }

                    bool cornersFit = false;
                    for(int cornerIndex = 0; cornerIndex < 4 && !cornersFit; ++cornerIndex) {
                        char rc[4];
                        for(int i = 0; i < 4; ++i) rc[i] = corners[(cornerIndex+i)%4];
                        if(
                            rc[0] == rc[1]
                            && rc[2] == rc[3]
                            && (rc[0] == 'M' || rc[0] == 'S')
                            && (rc[2] == 'M' || rc[2] == 'S')
                            && rc[0] != rc[2]
                        ) cornersFit = true;
                    }

                    if(cornersFit) totalCrossCount++;
                }
            }
        }

        return to_string(totalCrossCount);
    }
);