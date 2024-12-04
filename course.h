#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
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
            // cout << "| Day: " << day << endl;
            // cout << "- Location: " << location << endl;
            // cout << "- Periods: ";
            string indicator;
            ss >> indicator;
            while(indicator != ".") {
                // cout << indicator << " ";
                periods.push_back(stoi(indicator));
                ss >> indicator;
            }
            // cout << endl;
        }
        void displayTime() {
            string days[] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
            cout << "> Day: " << days[day] << " | Location: " << location << " | Period: " << periods[0] << endl;
            // Can only support one-period classes
        }
    };
    struct Section {
        vector<CourseTime*> course_times;
        int seats;  // total seats
        int enrolled;  // taken seats
        set<string> enrolled_IDs;  // UFIDs of currently registered students
        Section(int& s, int& e) : seats(s), enrolled(e) {};
    };
public:
    string code;  // ex: "COP3530"
    string name;  // ex: "Data Structures and Algorithms"
    string professor;  // ex: "Amanpreet Kapoor"
    vector<Section*> sections;
    int credits;
    vector<string> prerequisites;
    vector<string> majors;  // either vector of major(s) if major-specific, or "Any"

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
    void addMajors(vector<string>& maj) {
        this->majors = maj;
    }
    vector<vector<int>> allSectionTimes(const int& section) {
        // Vector of vectors of times in a section, [days of week][period(s)]
        vector<vector<int>> times(5);
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
    set<string> enrollledStudents(const int& section) {
        return this->sections[section]->enrolled_IDs;
    }
    void displaySections() {
        for (int i = 0; i < sections.size(); i++){
            Section* current = sections[i];
            if (current) {
                cout << "Section: " << (i + 1) << endl;
                cout << "- Seats Available: " << (current->seats) - (current->enrolled) << "/" << current->seats << endl;
                cout << "- Meeting Times:" << endl;
                for (auto time : current->course_times) {
                    time->displayTime();
                }
                cout << "----------" << endl;
            }
        }
    }
};


#endif //PROJECT3_COURSE_H
