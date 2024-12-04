#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "Course.h"
#include "student.h"
#include "generate_students.h"
#include "cli.h"
using namespace std;

int main() {
    // Generate random students ----------------------------------------------------------------------------------------
    //  - Max of 100,000
    //  - May need to change to absolute path of generate_students.txt on your device
    generateStudents(100000, "generate_students.txt");
    // -----------------------------------------------------------------------------------------------------------------
    // cout << "complete" << endl;
    // student_database["00008015"]->Register("MAC2311", course_catalog, 1);
    // map<string, Course*> course_catalog = parseCourseData("/Users/catherinewu/Downloads/careerplus-main/course_data.txt");
    // map<string, Student*> student_database = parseStudentData("/Users/catherinewu/Downloads/careerplus-main/generate_students.txt");

    // User new_user;
    // new_user.initializeData("/Users/catherinewu/Downloads/careerplus-main/course_data.txt", "/Users/catherinewu/Downloads/careerplus-main/student_data.txt");
    // new_user.mainMenu();

    // cout << student_database["00008015"]->Register("MAC2311", course_catalog, 1) << endl;  // should fail due to missing prereq
    // cout << student_database["00008015"]->Register("MAC2312", course_catalog, 1) << endl;  // should fail due to missing prereq
    // cout << student_database["00008015"]->Register("PHY2048", course_catalog, 3) << endl;  // should fail due to overlap in times
    // cout << student_database["00008015"]->Unenroll("MAC2311", course_catalog) << endl;

    return 0;
}
