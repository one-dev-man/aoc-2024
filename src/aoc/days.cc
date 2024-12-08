#include "days.hh"

// 

map<string, Day*>* days::dayMapPtr = nullptr;

void days::checkDayMap() {
    if(days::dayMapPtr == nullptr) days::dayMapPtr = new map<string, Day*>({});
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
Day* days::getday(string key) {
    days::checkDayMap();
    return (*days::dayMapPtr)[key];
}

void days::setday(string key, Day* d) {
    days::checkDayMap();
    (*days::dayMapPtr)[key] = d;
}

//
// 
// 

Day::Day(
    string key,
    string inputPath,
    function<string (const string &input, ostream &logs)> solver
) {
    this->key = key;

    this->inputPath = inputPath;
    this->solver = solver;

    //

    days::setday(this->getKey(), this);
}

// 

string Day::getKey() { return this->key; };
string Day::getInputPath() { return this->inputPath; };

// 

string Day::getInput() { return files::readtxt(this->getInputPath()); }

// 

string Day::solve() {
    string logsPath = "./logs/";
    
    try { files::mkdirs(logsPath); }
    catch(const filesystem::filesystem_error& e) {
        cerr << e.what() << " ||| " << e.code().value() << '\n';
    }

    logsPath.append("d");
    logsPath.append(this->getKey());
    logsPath.append(".logs.txt");

    fstream logs(logsPath, fstream::out);

    const string result = solver(this->getInput(), logs);

    logs.close();

    return result;
};