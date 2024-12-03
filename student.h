#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Course.h"
using namespace std;

#ifndef PROJECT3_STUDENT_H
#define PROJECT3_STUDENT_H

class Student {
private:
    string name;
    string student_id;
    string major;
    int year; // 1 = freshman, 2 = sophomore, 3 = junior, 4 = senior, 5 = other
    int credits; // Amount of credits taken
    int credit_limit; // Maximum number of credits student can take
    vector<Course*> courses; // Current registered classes
    vector<int> sections; // Current registered sections of courses (index corresponds to courses)
    vector<string> prev_courses;  // completed classes (pre-reqs)

public:
    Student(string& id, int& y, string& m, string& n, vector<string>& pc) : student_id(id), year(y), major(m), name(n), prev_courses(pc) {
        // Hard coded values in case want to be able to change per student
        this->credits = 0;
        this->credit_limit = 18;
    }
    Student(string& id, int& y, string& m, string& n) : student_id(id), year(y), major(m), name(n) {
        this->credits = 0;
        this->credit_limit = 18;
    }

    string Register(string& code, map<string, Course*>& catalog, int& section) {
        // Attempts to register student for section, returns message based on success or error
        Course* to_add = catalog[code];

        // 0. CHECK STUDENT HAS ADEQUATE REMAINING CREDITS
        if (to_add->credits + this->credits > credit_limit) {
            return "CREDIT EXCESS";  // Return credit limit reached message
        }

        // 1. CHECK FOR OPEN SEATS
        if (to_add->openSeats(section) < 1) {
            return "FULL";  // Return full message
        }

        // 2. CHECK FOR PREREQUISITES
        for (const string& req : to_add->prerequisites) {
            auto it = find(prev_courses.begin(), prev_courses.end(), req);
            if (it == prev_courses.end()) {
                return "MISSING" + req;  // Return missing prerequisite message
            }
        }

        // 3. CHECK FOR TIME CONFLICTS
        vector<vector<int>> new_times = to_add->allSectionTimes(section);
        vector<vector<int>> current_times;
        // Loop compares class times for all courses student is already registered in
        for (Course* c : this->courses) {
            for (int i=0; i<c->sections.size(); i++) {
                current_times = c->allSectionTimes(i);
                for (int day=0; day<5; day++) {
                    for (int period : new_times[day]) {
                        auto it = find(current_times[day].begin(), current_times[day].end(), period);
                        if (it != current_times[day].end()) {
                            // TIME CONFLICT w/already registered class
                            return c->code;  // Return course code
                        }
                    }
                }
            }
        }
        // NO time conflict found, register student
        this->courses.push_back(catalog[code]);
        this->sections.push_back(section);
        this->credits += catalog[code]->credits;

        return "SUCCESS";  // Return success message
    }

};

#endif //PROJECT3_STUDENT_H
