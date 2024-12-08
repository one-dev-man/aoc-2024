#include "cli.hh"

// 

map<string, string> cli::parseargs(const int argc, const char* argv[]) {
    map<string, string> argsmap = {};

    // 

    string arg;
    int arg_length;
    for(int i = 0; i < argc; ++i) {
        arg = argv[i];
        arg_length = arg.length();

        string argkey;
        string argvalue = "";

        if(arg.starts_with("--") && arg_length > 3) {
            size_t equal_char_pos = arg.find("=");
            if(equal_char_pos == string::npos) {
                argkey = arg.substr(2, arg_length-2);
            }
            else {
                argkey = arg.substr(2, equal_char_pos-2);
                argvalue = arg.substr(equal_char_pos+1, arg_length-equal_char_pos-1);
            }

            argsmap[argkey] = argvalue;
        }
        else if(arg.starts_with("-") && arg_length > 2) {
            argkey = arg.substr(1, 1);
            argvalue = arg.substr(2, arg_length-2);
            argsmap[argkey] = argvalue;
        }
    }

    //

    return argsmap;
}