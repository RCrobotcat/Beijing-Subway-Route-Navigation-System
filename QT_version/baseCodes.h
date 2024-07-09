//
// Created by 刘宇杰 on 24-4-18.
//

#ifndef PK_SUBWAY_BASECODES_H
#define PK_SUBWAY_BASECODES_H

#include "iostream"
using namespace std;

class baseCodes {
public:
    string base_code(const string& start, const string& end, int choice_2);
    string insert_or_delete(char choice_1, const string& line_name);
    void graphInitial();
};


#endif //PK_SUBWAY_BASECODES_H
