#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "Course.h"
using namespace std;

map<string, Course*> parseTextData(const string& file_name) {
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
                sections += 1;
                course_output[code]->addSection();
                continue;
            } else if (indicator == "-") {
                course_output[code]->addCourseTime(ss, sections);
                continue;
            }
        }
    }
    return course_output;
}

int main() {
    map<string, Course*> testing = parseTextData("/Users/catherinewu/Documents/Project3/course_data.txt");
    return 0;
}
