#include <iostream>
#include "label_map.hh"

int LabelMap::get(string& label) {
    if (labels.count(label)) {
        return labels[label];
    }
    return -1;
}

void LabelMap::put(string& label, int line) {
    labels.insert({label, line});
}

void LabelMap::print() {
    map<string, int>::iterator it;
    for (it = labels.begin(); it != labels.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
}