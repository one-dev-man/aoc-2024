#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <fstream>

// 

#include "../utils/files.hh"

// 

using namespace std;

// 

class Day {
    private:
        string key;
        string inputPath;
        function<string (const string &input, ostream &logs)> solver;
    
    public:
        Day(
            string key,
            string inputPath,
            function<string (const string &input, ostream &logs)> solver
        );

        // 

        string getKey();
        string getInputPath();

        // 

        string getInput();

        // 

        string solve();
};

// 

class days {
    private:
        static map<string, Day*>* dayMapPtr;
        static void checkDayMap();

    public: 
        static Day* getday(string key);

        static void setday(string key, Day* d);

};