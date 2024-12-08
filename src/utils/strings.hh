#pragma once

// 

#include <iostream>
// #include <cstdlib>
#include <vector>

// 

using namespace std;

// 

namespace strings {

    vector<string> split(const string &str, const string &separator);

    size_t count(const string &str, const string &searched);
    
}
