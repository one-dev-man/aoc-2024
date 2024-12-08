#include "files.hh"

// 

bool files::mkdirs(const string &path) {
    try {
        return filesystem::create_directories(path);
    } catch(const filesystem::filesystem_error& e) {
        throw e;
    }
}

// 

string files::readtxt(const string &path) {
    fstream txtfile;
    txtfile.open(path, fstream::in);

    string content = "";

    if(!txtfile.is_open()) throw "Unable to open txtfile";

    int lineCount = 0;
    string line;
    while(getline(txtfile, line)) {
        content.append(line);
        content.append("\n");

        lineCount++;
    }

    if(lineCount > 0) content.pop_back();
    txtfile.close();

    return content;
}

// 

static void __writetxt(const string &path, const string &content, ios::openmode mode) {
    fstream txtfile;
    txtfile.open(path, fstream::out | mode);

    txtfile << content;

    txtfile.close();
}

void files::writetxt(const string &path, const string &content) {
    __writetxt(path, content, fstream::out);
}

void files::appendtxt(const string &path, const string &content) {
    __writetxt(path, content, ios::app);
}