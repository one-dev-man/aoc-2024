#include "day4.hh"

// 

static vector<string> getDiagonals(const vector<string> &rows, int minLength) {
    vector<string> diagonals = {};

    int rowCount = rows.size();
    int rowLength = rows[0].length();
    int maxDiagonalLength = min(rowCount, rowLength);

    int currentRowIndexMax = rowCount+(rowLength-1)-1;
    for(int currentRowIndex = -(rowLength-1); currentRowIndex <= currentRowIndexMax; ++currentRowIndex) {
        string diagonal = "";
        int diagonalLength = min(abs((long long) (rowLength + currentRowIndex)), (long long) maxDiagonalLength);
        diagonalLength = min(rowCount - currentRowIndex, diagonalLength);

        if(diagonalLength >= minLength) {
            for(
                int i = 0, rowIndex = currentRowIndex;
                i < rowLength;
                ++i, ++rowIndex
            ) {
                if(0 <= rowIndex && rowIndex < rowCount) {
                    string row = rows[rowIndex];
                    diagonal.push_back(row.at(i));
                }
            }

            diagonals.push_back(diagonal);
        }
    }

    return diagonals;
}

// 

static vector<string> getColumns(const vector<string> &rows) {
    vector<string> columns = {};
    
    const size_t rowLength = rows[0].length();

    for(size_t i = 0; i < rowLength; ++i) columns.push_back("");

    for(const string &row : rows) {
        size_t i = 0;
        for(const char &c : row) {
            columns[i].push_back(c);
            ++i;
        }
    }

    return columns;
}

//

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* day4 = new Day(
    "4",
    "./resources/days/4/input.txt",
    [](const string &input, ostream &logs) -> string {
        const string searchedWord = "XMAS";
        const string reversedSearchedWord = string(searchedWord.rbegin(), searchedWord.rend());
        const size_t searchedWordLength = searchedWord.length();

        vector<string> rows = strings::split(input, "\n");
        vector<string> reversedRows = collections::map<string, string>(strings::split(input, "\n"), [](string row) -> string { return string(row.rbegin(), row.rend()); });
        vector<string> columns = getColumns(rows);
        vector<string> diagonals = getDiagonals(rows, searchedWordLength);
        vector<string> reversedDiagonals = getDiagonals(reversedRows, searchedWordLength);

        vector<string> lineLists[4] = { rows, columns, diagonals, reversedDiagonals };
        
        size_t totalSearchedWordCount = 0;
        for(const vector<string> &lineList : lineLists) {
            size_t searchedWordCount = 0;
            
            for(const string &line : lineList) {
                searchedWordCount += strings::count(line, searchedWord);
                searchedWordCount += strings::count(line, reversedSearchedWord);
            }

            totalSearchedWordCount += searchedWordCount;
        }

        return to_string(totalSearchedWordCount);
    }
);