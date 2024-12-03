#pragma once
#include <iostream>
#include <map>
#include "student.h"
#include "Course.h"
using namespace std;

#ifndef CAREERPLUS_CLI_H
#define CAREERPLUS_CLI_H

class User {
private:
    string user_name;
    string user_id;
    string user_major;
    int user_year; // 1 = freshman, 2 = sophomore, 3 = junior, 4 = senior, 5 = other
    int user_credits; // Amount of credits taken
    int user_limit; // Maximum number of credits student can take
    vector<Course*> user_courses; // Current registered classes
    vector<int> user_sections; // Current registered sections of courses (index corresponds to courses)
    vector<string> user_prev;  // completed classes (pre-reqs)
    Student* user; // User data
    map<string, Course*> course_catalog; // Data of all courses after parsing data
    map<string, Student*> student_database; // Data of all students after parsing data

public:
    map<string, Course*> parseCourseData(const string& file_name) {
        ifstream text_file(file_name);
        if (text_file.is_open()) {
            string line;
            string indicator;
            int sections = 0;  // For parsing purposes only
            // Parsing variables

            string course_code;
            string course_name;
            string professor;
            int seats;
            int enrolled;
            int credits;
            vector<string> prerequisites;
            // Storing course variables

            while (getline(text_file, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                ss >> indicator; // Determines what case to run based off symbol

                if (indicator == "#") {
                    course_name = "";
                    professor = "";
                    sections = 0;
                    // Resetting variables

                    ss >> course_code;
                    ss >> indicator;
                    ss >> indicator;
                    while (indicator != "\"") {
                        course_name += indicator;
                        ss >> indicator;
                        if (indicator != "\"") {
                            course_name += " ";
                        }
                    } // Storing course name

                    ss >> indicator;
                    credits = stoi(indicator); // Storing course credits
                    ss >> indicator;
                    ss >> indicator;
                    while (indicator != "\"") {
                        professor += indicator;
                        ss >> indicator;
                        if (indicator != "\"") {
                            professor += " ";
                        }
                    } // Storing course professor's name

                    ss >> indicator;
                    ss >> indicator;
                    // cout << course_code << ", " << course_name << ", " << professor << ", " << credits << endl;
                    // cout << "Pre-reqs: ";
                    while (indicator != ".") {
                        // cout << indicator << " ";
                        prerequisites.push_back(indicator);
                        ss >> indicator;
                    } // Checking for any prerequisites, and storing them
                    // cout << endl;

                    Course* temp = new Course(course_code, course_name, professor, credits, prerequisites);
                    course_catalog[course_code] = temp;
                    continue;
                } else if (indicator == "*") {
                    ss >> indicator;
                    ss >> indicator; // Section number
                    ss >> indicator; // Seats
                    seats = stoi(indicator);
                    ss >> indicator; // Currently enrolled
                    enrolled = stoi(indicator);
                    sections += 1;
                    course_catalog[course_code]->addSection(seats, enrolled);
                    // cout << "- Seats: " << seats << endl;
                    // cout << "- Enrolled: " << enrolled << endl;
                    // cout << "--------- Section: " << sections << endl;
                    continue;
                    // Adds sections to each course
                } else if (indicator == "-") {
                    course_catalog[course_code]->addCourseTime(ss, sections);
                    continue;
                } // Adds course times with each section
            }
        }
        text_file.close();
        return course_catalog;
    }

    map<string, Student*> parseStudentData(const string& file_name) {
        ifstream text_file(file_name);
        if (text_file.is_open()) {
            string line;
            string indicator;
            // Parsing variables

            string student_name;
            string student_id;
            string major;
            int student_year;
            vector<string> prev_courses;
            Student* temp;
            // Storing course variables

            while(getline(text_file, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                ss >> indicator; // Determines what case to run based off symbol

                if (indicator == "#") {
                    student_name = "";
                    student_id = "";
                    major = "";
                    // Resetting variables

                    ss >> student_id;
                    ss >> indicator;
                    ss >> indicator;
                    while (indicator != "\"") {
                        student_name += indicator;
                        ss >> indicator;
                        if (indicator != "\"") {
                            student_name += " ";
                        }
                    } // Storing student name

                    ss >> indicator;
                    student_year = stoi(indicator); // Storing student year
                    ss >> indicator;
                    ss >> indicator;
                    while (indicator != "\"") {
                        major += indicator;
                        ss >> indicator;
                        if (indicator != "\"") {
                            major += " ";
                        }
                    } // Storing student major
                    // cout << student_name << ", " << student_id << endl;
                    // cout << "- Major: " << major << endl;
                    // cout << "- Year: " << student_year << endl;

                    if (getline(text_file, line)) {
                        if (line.empty()) {
                            temp = new Student(student_id, student_year, major, student_name);
                            student_database[student_id] = temp;
                        } // Creates new student object and adds it to list of students
                        else {
                            stringstream ss(line);
                            ss >> indicator;
                            ss >> indicator;
                            // cout << "- Previous Courses: ";
                            while (indicator != ".") {
                                // cout << indicator << " ";
                                prev_courses.push_back(indicator);
                                ss >> indicator;
                            }
                            // cout << endl;
                            temp = new Student(student_id, student_year, major, student_name, prev_courses);
                            student_database[student_id] = temp;
                        } // Creates new subject object AND adds previous courses taken (for existing students)
                    }
                }
            }
            text_file.close();
            return student_database;
        }
    }

    void initializeData() {
        parseCourseData("/Users/matti/CLionProjects/careerplus/course_data.txt");
        parseStudentData("/Users/matti/CLionProjects/careerplus/student_data.txt");
        user_year = 1;
        bool correct = false;
        // Initializing data

        cout << "Welcome to CareerPlus! As a first time student, we must first register you in our system.\n" << "Please enter your name down below." << endl;
        getline(cin, user_name);
        while(!correct){
            string correct_input;
            cout << "Welcome " << user_name << "! Please enter your ID number below." << endl;
            getline(cin, user_id);
            cout << "What is your major? " << endl;
            getline(cin, user_major);
            cout << user_name << ", you entered that you are a " << user_major << " with an ID number of " << user_id << ". Is this correct? (Y/N)" << endl;
            getline(cin, correct_input);

            bool m = true;
            while(m) {
                if(correct_input == "Y") {correct = true; m = false; continue;}
                else if(correct_input == "N") {
                    cout << "I'm sorry for the misinterpretation. Please enter your name down below." << endl;
                    getline(cin, user_name);
                    m = false;
                    continue;
                }
                else {
                    cout << "Invalid option. Please type your answer again." << endl;
                    getline(cin, correct_input);
                }
            }
        }
        user = new Student(user_id, user_year, user_major, user_name);
        student_database[user_id] = user;
    }
};

#endif //CAREERPLUS_CLI_H
