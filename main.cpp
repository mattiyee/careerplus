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
    ifstream text_file(file_name);
    map<string, Course*> course_output;
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
                course_output[course_code] = temp;
                continue;
            } else if (indicator == "*") {
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

map<string, Student*> parseStudentData(const string& file_name) {
    ifstream text_file(file_name);
    map<string, Student*> student_list;
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
                    } // Creates new subject object AND adds previous courses taken (for existing students)
                }
            }
        }
        text_file.close();
        return student_list;
    }
}

int main() {
    map<string, Course*> course_catalog = parseCourseData("/Users/matti/CLionProjects/careerplus/course_data.txt");
    map<string, Student*> student_database = parseStudentData("/Users/matti/CLionProjects/careerplus/student_data.txt");
    cout << "complete" << endl;
    return 0;
}
