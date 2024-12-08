#pragma once

// 

#include <iostream>
#include <fstream>
#include <filesystem>

// 

using namespace std;

// 

namespace files {

    bool mkdirs(const string &path);

    string readtxt(const string &path);

    void writetxt(const string &path, const string &content);
    
    void appendtxt(const string &path, const string &content);

}