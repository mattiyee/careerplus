#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "Course.h"
#include "student.h"
using namespace std;

map<string, Course*> parseCourseData(const string& file_name) {
    /*# COP3530 " Data Structures and Algorithms " 3 " Amanpreet Kapoor " ~ COP3503 MAC2312 .
    * SECTION 1
    - 2 CAR0100 11 45 13 40
    - 4 CAR0100 13 55 15 50*/
    ifstream text_file(file_name);
    map<string, Course*> course_output;
    if (text_file.is_open()) {
        string line;
        string indicator;
        int sections = 0;  // For parsing purposes only
        int seats;
        int enrolled;

        string code;
        string name;
        int credits;
        string professor;
        vector<string> prerequisites;

        while (getline(text_file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            ss >> indicator;

            if (indicator == "#") {
                ss >> indicator;
                code = indicator;
                ss >> indicator;
                ss >> indicator;
                while (indicator != "\"") {
                    name += indicator;
                    ss >> indicator;
                    if (indicator != "\"") {
                        name += " ";
                    }
                }
                ss >> indicator;
                credits = stoi(indicator);
                ss >> indicator;
                ss >> indicator;
                while (indicator != "\"") {
                    professor += indicator;
                    ss >> indicator;
                    if (indicator != "\"") {
                        professor += " ";
                    }
                }
                ss >> indicator;
                ss >> indicator;
                while (indicator != ".") {
                    prerequisites.push_back(indicator);
                    ss >> indicator;
                }

                Course* temp = new Course(code, name, professor, credits, prerequisites);
                course_output[code] = temp;

                continue;
            } else if (indicator == "*") {
                ss >> indicator;
                ss >> indicator;
                ss >> indicator;
                seats = stoi(indicator);
                ss >> indicator;
                enrolled = stoi(indicator);
                sections += 1;
                course_output[code]->addSection(seats, enrolled);
                continue;
            } else if (indicator == "-") {
                course_output[code]->addCourseTime(ss, sections);
                continue;
            }
        }
    }
    text_file.close();
    return course_output;
}

map<string, Student*> parseStudentData(const string& file_name) {
    ifstream text_file(file_name);
    map<string, Student*> student_list;
    if (text_file.is_open()) {
        string line;
        string indicator;

        string UFID;
        int year;
        string major;
        string name;
        vector<string> prev_courses;
        Student* temp;

        while(getline(text_file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            ss >> indicator;

            if (indicator == "#") {
                ss >> UFID;
                ss >> indicator;
                ss >> indicator;
                while (indicator != "\"") {
                    name += indicator;
                    ss >> indicator;
                    if (indicator != "\"") {
                        name += " ";
                    }
                }
                ss >> indicator;
                year = stoi(indicator);
                ss >> indicator;
                ss >> indicator;
                while (indicator != "\"") {
                    major += indicator;
                    ss >> indicator;
                    if (indicator != "\"") {
                        major += " ";
                    }
                }
                if (getline(text_file, line)) {
                    if (line.empty()) {
                        temp = new Student(UFID, year, major, name);
                        student_list[UFID] = temp;
                    }
                    else {
                        stringstream ss(line);
                        ss >> indicator;
                        ss >> indicator;
                        while (indicator != ".") {
                            prev_courses.push_back(indicator);
                            ss >> indicator;
                        }
                        temp = new Student(UFID, year, major, name, prev_courses);
                        student_list[UFID] = temp;
                    }
                }
            }
        }
        text_file.close();
        return student_list;
    }
}

int main() {
    map<string, Course*> course_catalog = parseCourseData("/Users/catherinewu/Documents/Project3/course_data.txt");
    map<string, Student*> student_database = parseStudentData("/Users/catherinewu/Documents/Project3/student_data.txt");

    cout << "complete" << endl;
    return 0;
}
