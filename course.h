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
        vector<int> periods;
        int day;  // Monday = 1, Tuesday = 2, etc...
        string location;  // Room code

        CourseTime(stringstream& ss) {
            ss >> this->day >> this->location;
            string indicator;
            ss >> indicator;
            if (indicator != ".") {
                periods.push_back(stoi(indicator));
                ss >> indicator;
            }
        }
    };
    struct Section {
        vector<CourseTime*> course_times;
        int seats;  // total seats
        int enrolled;  // taken seats
        Section(int& s, int& e) : seats(s), enrolled(e) {};
    };
public:
    string code;  // ex: "COP3530"
    string name;  // ex: "Data Structures and Algorithms"
    string professor;  // ex: "Amanpreet Kapoor"
    vector<Section*> sections;
    int credits;
    vector<string> prerequisites;

    Course(const string& c, const string& n, const string& p, const int& cr, vector<string> pre) {
        this->code = c;
        this->name = n;
        this->professor = p;
        this->credits = cr;
        this->prerequisites = pre;
    }
    void addSection(int& s, int& e) {
        Section* temp = new Section(s, e);
        this->sections.push_back(temp);
    }
    void addCourseTime(stringstream& ss, const int& section) {
        CourseTime* temp = new CourseTime(ss);
        this->sections[section-1]->course_times.push_back(temp);
    }
    vector<vector<int>> allSectionTimes(const int& section) {
        // Vector of vectors of times in a section, [days of week][period(s)]
        vector<vector<int>> times;
        for (CourseTime* ct : this->sections[section]->course_times) {
            for (int p : ct->periods) {
                times[(ct->day)-1].push_back(p);
            }
        }
        return times;
    }
    int openSeats(const int& section) {
        return (this->sections[section]->seats) - (this->sections[section]->enrolled);
    }

};


#endif //PROJECT3_COURSE_H
