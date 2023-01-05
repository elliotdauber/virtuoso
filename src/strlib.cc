#include <algorithm>
#include <sstream>
#include <vector>
#include "strlib.hh"

const string StringLib::WHITESPACE = " \n\r\t\f\v";

string StringLib::ltrim(const string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}
    
string StringLib::rtrim(const string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
    
string StringLib::trim(const string &s) {
    return rtrim(ltrim(s));
}

vector<string> StringLib::tokenize(string &s) {
    vector<string> tokens{};
    istringstream ss(s);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

bool StringLib::is_num(string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int StringLib::to_num(string &s) {
    char* p;
    int converted = strtol(s.c_str(), &p, 10);
    if (*p) {
        return -1; //TODO: should probably throw an error
    }
    return converted;
}