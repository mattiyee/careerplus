#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "course.h"
#include "student.h"
#include "generate_students.h"
#include "cli.h"
using namespace std;

int main() {
    // Generate random students ----------------------------------------------------------------------------------------
    //  - Max of 100,000
    //  - May need to change to absolute path of generate_students.txt on your device
    // generateStudents(100000, "generate_students.txt");  // UNCOMMENT
    // -----------------------------------------------------------------------------------------------------------------

    // Main program body -----------------------------------------------------------------------------------------------
    User new_user;
    // !! Update paths to reflect your computer
    new_user.initializeData("/Users/catherinewu/Downloads/careerplus-main 2/course_data.txt", "/Users/catherinewu/Downloads/careerplus-main 2/generate_students.txt");
    new_user.mainMenu();
    // -----------------------------------------------------------------------------------------------------------------

    return 0;
}
