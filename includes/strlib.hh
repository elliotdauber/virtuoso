#ifndef __STRING_LIB_HH__
#define __STRING_LIB_HH__

#include <string>
#include <vector>

using namespace std;

class StringLib {
public:
    static string ltrim(const string &s);
    static string rtrim(const string &s);
    static string trim(const string &s);
    static vector<string> tokenize(string &s);
    static bool is_num(string &s);
    static int to_num(string &s);
private:
    static const string WHITESPACE;
};
 
#endif