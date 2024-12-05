#pragma once
#include <iostream>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include "student.h"
#include "Course.h"
#include "sortingAlgs.h"
using namespace std;

#ifndef CAREERPLUS_CLI_H
#define CAREERPLUS_CLI_H

class User {
private:
    Student* user; // User data
    unordered_map<string, Course*> course_output; // Data of all courses after parsing data
    unordered_map<string, Student*> student_list; // Data of all students after parsing data
    vector<string> major_list; // List of all available majors

public:
    unordered_map<string, Course*> parseCourseData(const string& file_name) {
        ifstream text_file(file_name);
        if (text_file.is_open()) {
            string line;
            string indicator;
            int sections = 0;  // For parsing purposes only
            // Parsing variables

            string course_code;
            string course_name;
            string professor;
            string major;
            int seats;
            int enrolled;
            int credits;
            vector<string> prerequisites;
            vector<string> majors;
            // Storing course variables

            while (getline(text_file, line)) {
                if (line.empty()) continue;

                stringstream ss(line);
                ss >> indicator; // Determines what case to run based off symbol

                if (indicator == "#") {
                    course_name = "";
                    professor = "";
                    major = "";
                    sections = 0;
                    // Resetting variables

                    ss >> course_code;
                    //cout << course_code << endl;
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

                    while (indicator != ".") {
                        prerequisites.push_back(indicator);
                        ss >> indicator;
                    } // Checking for any prerequisites, and storing them

                    Course* temp = new Course(course_code, course_name, professor, credits, prerequisites);
                    course_output[course_code] = temp;
                    prerequisites.clear();
                    continue;
                }
                else if (indicator == "@") {
                    ss >> indicator;  // major(s) specific to course (if any)
                    while (indicator != ".") {
                        if (indicator == ",") {
                            majors.push_back(major);
                            major = "";

                            ss >> indicator;
                        } else {
                            major = major + indicator;
                            ss >> indicator;
                            if (indicator != "," and indicator != ".") {
                                major = major + " ";
                            }
                        }
                    }
                    majors.push_back(major);
                    major = "";
                    course_output[course_code]->addMajors(majors);
                    majors.clear();
                }
                else if (indicator == "*") {
                    ss >> indicator;
                    ss >> indicator; // Section number
                    ss >> indicator; // Seats
                    seats = stoi(indicator);
                    ss >> indicator; // Currently enrolled
                    enrolled = stoi(indicator);
                    sections += 1;
                    course_output[course_code]->addSection(seats, enrolled);
                    // cout << "- Seats: " << seats << endl;
                    // cout << "- Enrolled: " << enrolled << endl;
                    // cout << "--------- Section: " << sections << endl;
                    continue;
                    // Adds sections to each course
                } else if (indicator == "-") {
                    course_output[course_code]->addCourseTime(ss, sections);
                    continue;
                } // Adds course times with each section
            }
        }
        text_file.close();
        return course_output;
    }

    unordered_map<string, Student*> parseStudentData(const string& file_name) {
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
                            student_list[student_id] = temp;
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
                            student_list[student_id] = temp;
                            prev_courses.clear();
                        } // Creates new subject object AND adds previous courses taken (for existing students)
                    }
                }
            }
            text_file.close();
            return student_list;
        }
    }

    vector<string> obtainMajors() {
        return major_list = {"Computer Science", "Computer Engineering", "Electrical Engineering", "Mechanical Engineering", "Biomedical Engineering",
                             "Biological/Agricultural Engineering", "Civil Engineering", "Industrial Engineering", "Aerospace Engineering", "Materials Science",
                             "Chemical Engineering", "Nuclear Engineering", "Digital Arts and Sciences"};
    }

    void initializeData(const string& course_file_name, const string& student_file_name) {
        parseCourseData(course_file_name);
        parseStudentData(student_file_name);
        obtainMajors();
        cout << "Parsing successfully complete." << endl << endl;
        string user_name;
        string user_id;
        string user_major;
        string user_year; // 1 = freshman, 2 = sophomore, 3 = junior, 4 = senior, 5 = other
        bool correct = false;
        bool check = false;
        // Initializing data

        cout << "Welcome to CareerPlus! As a first time student, we must first register you in our system.\n" << "Please enter your name down below." << endl;
        while (!correct) {
            string correct_input;
            while (!check) {
                getline(cin, user_name);
                bool valid = true;
                for (char a : user_name) {
                    if (!isalpha(a) && a != ' ') {
                        valid = false;
                    }
                }
                if (valid) {check = true;}
                else {cout << "Invalid name type! Name must consist of letters. Please try again." << endl;}
            }
            check = false;
            cout << "Welcome " << user_name << "! Please enter your ID number below." << endl;
            while (!check) {
                getline(cin, user_id);
                bool valid = true;
                if(user_id.size() == 8){
                    for (char b : user_id) {
                        if (!isdigit(b)) {
                            valid = false;
                        }
                    }
                } else {valid = false;}
                if (valid) {check = true;}
                else {cout << "Invalid ID type! ID must consist of numbers and must be eight digits long. Please try again." << endl;}
            }
            check = false;
            cout << "What is your major? " << endl;
            while (!check) {
                getline(cin, user_major);
                bool valid = true;
                for (char c : user_major) {
                    if (!isalpha(c) && c != ' ') {
                        valid = false;
                    }
                }
                auto it = find(major_list.begin(), major_list.end(), user_major);
                if(it == major_list.end()) {
                    valid = false;
                }
                if (valid) {check = true;}
                else {cout << "Invalid major type! Please check you spelt your major correctly." << endl;}
            }
            check = false;
            cout << "What year are you? (1 for Freshman, 2 for Sophomore, etc.)" << endl;
            while (!check) {
                getline(cin, user_year);
                bool valid = true;
                if(user_year.size() == 1){
                    for (char d : user_year) {
                        if (!isdigit(d)) {
                            valid = false;
                        }
                    }
                } else {valid = false;}
                if (valid) {check = true;}
                else {cout << "Invalid year! Please type an appropriate input. (1 for Freshman, 2 for Sophomore, etc.)" << endl;}
            }
            check = false;
            cout << "Have you taken any prerequisite classes? If so, please enter the course code of ONE class below." <<
            "If you have not, please type \"N\"." << endl;
            string temp_input;
            while (!check) {
                getline(cin, temp_input);
                if (temp_input == "N" || temp_input == "n") {
                    check = true; // Exit function
                }
                // TODO: Add prerequisite function
                cout << "Class code " << temp_input << "successful. Do you have another class to add? If not, please type \"N\"." << endl;
            }
            cout << user_name << ", you entered that you are a " << user_major << " with an ID number of " << user_id << ". Is this correct? (Y/N)" << endl;
            getline(cin, correct_input);

            bool m = true;
            while(m) {
                if(correct_input == "Y" || correct_input == "y") {correct = true; m = false; continue;}
                else if(correct_input == "N" || correct_input == "n") {
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
        int year = stoi(user_year);
        user = new Student(user_id, year, user_major, user_name);
        student_list[user_id] = user;
    }

    void mainMenu(){
        cout << "Thank you for registering for CareerPlus!\nWhat would you like to do next? (Please select an option below.)" << endl;
        while(true) {
            string selected_option;
            cout << "1. View current schedule\n2. Register for a course\n3. Search for a student\n4. Show list of course codes\n5. Sort students for funzies\n6. Exit" << endl;
            getline(cin, selected_option);

            if(selected_option == "1") {
                if (user->getCourses().size() == 0) {
                    cout << "You are not registered in any courses!" << endl;
                } else {
                    cout << "These are your registered courses:\n--------------------" << endl;
                    user->displayStudentCourses();
                }
            } else if (selected_option == "2") {
                string input_course;
                cout << "Please enter the code of the course you would like to enroll in." << endl;
                getline(cin, input_course);

                auto it = course_output.find(input_course);
                if (it != course_output.end()) {
                    string input_section;
                    Course* selected = it->second;
                    cout << "Here are the available sections for " << input_course << ". Please type the number of the section you wish to enroll in." << endl;
                    selected->displaySections();
                    cout << "If you are not interested in registering for a course, please type \"E\" to exit." << endl;
                    while(true) {
                        string invalid = "Invalid section. Please type a valid section number or \"E\" to exit.";
                        getline(cin, input_section);
                        if (input_section.size() == 1) {
                            if (input_section == "E" || input_section == "e") {
                                break;
                            }
                            if (isdigit(input_section[0])) {
                                cout << user->Register(input_course, course_output, stoi(input_section)) << endl;
                                break;
                            } else {cout << invalid << endl;}
                        } else {cout << invalid << endl;}
                    }
                } else {
                    cout << "Course code " << input_course << " cannot be found. Returning to Main Menu..." << endl;
                }
            } else if(selected_option == "3") {
                string search_option;
                cout << "Please select your preferred search method:\n1. ID Number\n2. Student Name" << endl;

                while (true){
                    getline(cin, search_option);
                    if (search_option == "1") {
                        string input_id;
                        cout << "Please enter the ID of the student you'd like to search up:" << endl;
                        getline(cin, input_id);
                        if (!searchbyID(input_id)) {
                            cout << "Student ID number " + input_id + " not found." << endl;
                        }
                        break;
                    } else if(search_option == "2") {
                        string input_name;
                        cout << "Please enter the first and last name of the student you'd like to search up:" << endl;
                        getline(cin, input_name);
                        if(!searchbyName(input_name)) {
                            cout << "Student " + input_name + " not found." << endl;
                        }
                        break;
                    } else {
                        cout << "Invalid option! Please select one of the available options." << endl;
                        continue;
                    }
                }
            } else if(selected_option == "4"){
                cout << "Here is a list of all the courses offered, sorted in alphabetical order!\n" << endl;
                vector<string> courseCodes;
                for(const auto& cc: course_output){
                    courseCodes.push_back(cc.first);
                }
                useMergeSort(courseCodes);
            }
            else if(selected_option == "5"){
                cout << "Time for the fun part! Let's see which sorting algorithm can sort all your peers' names/ids the fastest!" << endl;
                cout << "Would you like to sort by name or student ID? (N / ID)" << endl;
                string option;
                while(true){
                    getline(cin, option);
                    if(option == "N" or option == "n"){
                        vector<string> students;
                        for(const auto& ids: student_list){
                            students.push_back(ids.second->getName());
                        }
                        measureAndSortStudents(students);
                        break;
                    }
                    else if(option == "ID" or option == "id"){
                        vector<string> students;
                        for(const auto& ids: student_list){
                            students.push_back(ids.first);
                        }
                        measureAndSortStudents(students);
                        break;
                    }
                    else{
                        cout << "Invalid option! Please select one of the available options." << endl;
                        continue;
                    }
                }

            }
            else if(selected_option == "6") {
                cout << "Thank you for using CareerPlus! Have a great day!" << endl;
                break;
            }
        }
    }

    bool searchbyID(const string& input_id) {
        auto it = student_list.find(input_id);
        if(it != student_list.end()) {
            cout << "found" << endl;
            printUserInfo(it->second->getUserInfo());
            return true;
        } else {
            return false;
        }
    }

    bool searchbyName(const string& input_name) {
        for (const auto& student : student_list) {
            if (student.second->getName() == input_name) {
                printUserInfo(student.second->getUserInfo());
                return true;
            }
        }
        return false;
    }

    void printUserInfo(const string& parse) {
        string temp;
        string temp_two;
        stringstream ss(parse);
        while(temp != ":") {
            temp_two += temp;
            ss >> temp;
            temp_two += " ";
        }
        cout << "--------------------\nName:" << temp_two << endl;
        ss >> temp;
        cout << "ID: " << temp << endl;
        ss >> temp;
        ss >> temp;
        temp_two = "";
        while(temp != ":") {
            temp_two += temp;
            ss >> temp;
            temp_two += " ";
        }
        cout << "Major: " << temp_two << endl;
        ss >> temp;
        cout << "Year: " << temp << "\n--------------------" << endl;
    }
};

#endif //CAREERPLUS_CLI_H