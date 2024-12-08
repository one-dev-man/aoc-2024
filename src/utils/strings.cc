#include "strings.hh"

// 

// vector<string> strings::split(const string &str, const string &separator) {
//     vector<string> result = {};

//     const char* c_str = str.c_str();
//     const char* c_separator = separator.c_str();
//     const int strLength = str.length();
//     const int separatorLength = separator.length();

//     string parkourSeparatorPart = "";
//     int parkourSeparatorPartLength = 0;
    
//     string currentPart = "";
//     int currentPartLength = 0;

//     for(int charIndex = 0; charIndex < strLength; ++charIndex) {
//         const char chr = c_str[charIndex];

//         if(chr == c_separator[parkourSeparatorPartLength]) {
//             parkourSeparatorPart.push_back(chr);
//             parkourSeparatorPartLength++;
//         }
//         else {
//             if(parkourSeparatorPartLength == 0) {
//                 currentPart.push_back(chr);
//                 currentPartLength++;
//             }
//             else {
//                 currentPart.append(parkourSeparatorPart);
//                 currentPartLength += parkourSeparatorPartLength;

//                 parkourSeparatorPart = "";
//                 parkourSeparatorPartLength = 0;
//             }
//         }

//         if(parkourSeparatorPartLength == separatorLength) {
//             currentPart = currentPart.substr(0, currentPartLength-separatorLength);
//             result.push_back(currentPart);
            
//             parkourSeparatorPart = "";
//             parkourSeparatorPartLength = 0;
            
//             currentPart = "";
//             currentPartLength = 0;
//         }
//     }

//     result.push_back(currentPart);

//     return result;
// }

vector<string> strings::split(const string &str, const string &separator) {
    vector<string> result = {};
    
    const size_t separatorLength = separator.length();

    string remaining = str;

    size_t separatorIndex = string::npos;
    while((separatorIndex = remaining.find(separator)) != string::npos) {
        result.push_back(remaining.substr(0, separatorIndex));
        remaining = remaining.substr(separatorIndex + separatorLength);
    }

    result.push_back(remaining);
    
    return result;
}

// 

size_t strings::count(const string &str, const string &searched) {
    size_t result = 0;

    const size_t searchedLength = searched.length();

    string remaining = str;

    size_t searchedIndex = string::npos;
    while((searchedIndex = remaining.find(searched)) != string::npos) {
        result++;
        remaining = remaining.substr(searchedIndex + searchedLength);
    }

    return result;
}