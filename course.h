#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

#ifndef PROJECT3_COURSE_H
#define PROJECT3_COURSE_H

class Course {
    struct CourseTime {
        // Using military time
        int start_hr;
        int start_min;
        int end_hr;
        int end_min;

        int day;  // Monday = 1, Tuesday = 2, etc...
        string location;  // Room code

        CourseTime(stringstream& ss) {
            ss >> this->day >> this->location >> this->start_hr >> this->start_min >> this->end_hr >> this->end_min;
        }
    };
private:
    struct Section {
        vector<CourseTime*> course_times;
        Section() {};
    };
    string code;  // ex: "COP3530"
    string name;  // ex: "Data Structures and Algorithms"
    string professor;  // ex: "Amanpreet Kapoor"
    vector<Section*> sections;
    int credits;
    vector<string> prerequisites;

public:
    Course(const string& c, const string& n, const string& p, const int& cr, vector<string> pre) {
        this->code = c;
        this->name = n;
        this->professor = p;
        this->credits = cr;
        this->prerequisites = pre;
    }
    void addSection() {
        Section* temp = new Section();
        this->sections.push_back(temp);
    }
    void addCourseTime(stringstream& ss, const int& section) {
        CourseTime* temp = new CourseTime(ss);
        this->sections[section-1]->course_times.push_back(temp);
    }
};


#endif //PROJECT3_COURSE_H
