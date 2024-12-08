#pragma once

#include <iostream>
#include <map>

using namespace std;

// 

namespace cli {

    map<string, string> parseargs(const int argc, const char* argv[]);

};