#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "course.h"
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
    string Register(const string code, map<string, Course*>& catalog, const int section) {
        if (catalog.count(code) != 1) {
            return "Enroll " + code + ": ERROR (Invalid class code)";  // Class not found in catalog
        }
        // Attempts to register student for section, returns message based on success or error
        Course* to_add = catalog[code];
        if (section > to_add->sections.size()-1) {
            return "Enroll " + code + ": ERROR (" + to_string(section) + " is invalid section number)";
        }

        // 0a. CHECK STUDENT HAS ADEQUATE REMAINING CREDITS
        if (to_add->credits + this->credits > this->credit_limit) {
            return "Enroll " + code + ": ERROR (Credit limit exceeded)";  // Return credit limit reached message
        }

        // 0b. CHECK STUDENT NOT ALREADY ENROLLED IN COURSE
        for (auto c : this->courses) {
            if (c->code == code) {
                return "Enroll " + code + ": ERROR (Already enrolled in course)";  // Return missing prerequisite message
            }
        }

        // 1. CHECK FOR OPEN SEATS
        if (to_add->openSeats(section) < 1) {
            return "Enroll " + code + ": ERROR (Section " + to_string(section) + " is full)";  // Return full message
        }

        // 2a. CHECK FOR PREREQUISITES
        for (string req : to_add->prerequisites) {
            auto it = find(prev_courses.begin(), prev_courses.end(), req);
            if (it == prev_courses.end()) {
                return "Enroll " + code + ": ERROR (Missing prerequisite: " + req + ")";  // Return missing prerequisite message
            }
        }

        // 2b. CHECK FOR MAJOR RESTRICTIONS
        if (to_add->majors[0] != "Any") {
            auto it = find(to_add->majors.begin(), to_add->majors.end(), this->major);

            if (it == to_add->majors.end()) {
                return "Enroll " + code + ": ERROR (Course is restricted to certain majors)";
            }
        }

        // 3. CHECK FOR TIME CONFLICTS
        /*vector<vector<int>> new_times = to_add->allSectionTimes(section);
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
        }*/
        // NO time conflict found, register student
        this->courses.push_back(catalog[code]);
        this->sections.push_back(section);
        this->credits += catalog[code]->credits;
        catalog[code]->sections[section]->Enroll(this->student_id);

        return "Enroll " + code + ": SUCCESS";  // Return success message
    }
    string Unenroll(const string code, map<string, Course*>& catalog) {
        for (int i = 0; i < this->courses.size(); i++) {
            if (this->courses[i]->code == code) {
                int section = sections[i];
                string status = catalog[code]->sections[section]->Unenroll(this->student_id);
                if (status != "SUCCESS") {
                    return "Unenroll " + code + ": ERROR (Student not currently enrolled in course)";
                }
                this->credits -= courses[i]->credits;
                this->courses.erase(this->courses.begin() + i);
                this->sections.erase(this->sections.begin() + i);

                return "Unenroll " + code + ": SUCCESS";
            }
        }
        return "Unenroll " + code + ": ERROR (Student not currently enrolled in course)";
    }
    int currentCredits() {
        return this->credits;
    }
};

#endif //PROJECT3_STUDENT_H
