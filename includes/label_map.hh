#ifndef __LABEL_MAP_HH__
#define __LABEL_MAP_HH__

#include <string>
#include <map>

using namespace std;

class LabelMap {
public:
    int get(string& label);
    void put(string& label, int line);
    void print();
private:
    map<string, int> labels;
};

#endif