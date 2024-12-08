#include <iostream>
#include <cstdlib>

#include "./utils/cli.hh"

#include "./aoc/days.hh"

using namespace std;

// 

int main(const int argc, const char* argv[]) {
    map<string, string> argsmap = cli::parseargs(argc, argv);

    string dayChoice = argsmap["d"];

    // 

    Day* day = days::getday(dayChoice);

    if(day != nullptr) {
        string result = day->solve();
        cout.flush();
        cout << "Solution: " << result << '\n';
    }
    else {
        cerr << dayChoice << " doesn't seem to be solved." << '\n';
        return 0;
    }
}