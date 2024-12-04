#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

void generateStudents(int num, const string& output_addr) {
    vector<string> first_names = {"Jacob", "Emily", "Michael", "Madison", "Joshua", "Madison", "Emma", "Matthew",
                                  "Olivia", "Hannah", "Daniel", "Christopher", "Abigail", "Andrew", "Isabella",
                                  "Ethan", "Samantha", "Joseph", "Elizabeth", "William", "Ashley", "Anthony", "Alexis",
                                  "David", "Sarah", "Alexander", "Sophia", "Nicholas", "Alyssa", "Ryan", "Grace",
                                  "Tyler", "Ava", "James", "Taylor", "John", "Brianna", "Jonathan", "Lauren", "Noah",
                                  "Chloe", "Brandon", "Natalie", "Christian", "Kayla", "Dylan", "Jessica", "Samuel",
                                  "Anna", "Benjamin", "Victoria", "Nathan", "Mia", "Zachary", "Hailey", "Logan",
                                  "Sydney", "Justin", "Jasmine", "Gabriel", "Julia", "Jose", "Morgan", "Austin",
                                  "Destiny", "Kevin", "Rachel", "Elijah", "Ella", "Caleb", "Kaitlyn", "Robert", "Megan",
                                  "Thomas", "Katherine", "Jordan", "Savannah", "Cameron", "Jennifer", "Jack",
                                  "Alexandra", "Hunter", "Allison", "Jackson", "Haley", "Angel", "Maria", "Isaiah",
                                  "Kaylee", "Evan", "Lily", "Isaac", "Makayla", "Luke", "Brooke", "Mason", "Nicole",
                                  "Jayden", "Mackenzie", "Jason", "Addison"};
    vector<string> last_names = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore",
                                 "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson",
                                 "Garcia", "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee", "Walker",
                                 "Hall", "Allen", "Young", "Hernandez", "King", "Wright", "Lopez", "Hill", "Scott",
                                 "Green", "Adams", "Baker", "Gonzalez", "Nelson", "Carter", "Mitchell", "Perez",
                                 "Roberts", "Turner", "Phillips", "Campbell", "Parker", "Evans", "Edwards", "Collins",
                                 "Stewart", "Sanchez", "Morris", "Rogers", "Reed", "Cook", "Morgan", "Bell", "Murphy",
                                 "Bailey", "Rivera", "Cooper", "Richardson", "Cox", "Howard", "Ward", "Torres",
                                 "Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks", "Kelly", "Sanders",
                                 "Price", "Bennett", "Wood", "Barnes"};

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist_ID(0,99999999); // distribution in range [1, 6]
    uniform_int_distribution<std::mt19937::result_type> dist_first_name(0,first_names.size()-2);
    uniform_int_distribution<std::mt19937::result_type> dist_last_name(0,last_names.size()-2);
    uniform_int_distribution<std::mt19937::result_type> dist_year(1,4);
    uniform_int_distribution<std::mt19937::result_type> dist_major_spread(1,100);

    vector<string> UFIDs;
    vector<string> names;
    vector<int> years;
    vector<string> majors;
    vector<vector<string>> classes;

    if (num > 100000) {  // Limit of 100,000 students generated
        num = 100000;
    }

    for (int i=0; i<num; i++) {
        bool valid_ID = false;
        string str_ID;
        int int_ID;
        string name;
        int year;
        int major_spread;
        int cs;  // Class spread for rng
        vector<string> cc = {};

        while (!valid_ID) {
            // Generate random UFID
            int_ID = dist_ID(rng);

            // Convert to string and check if ID already exists
            str_ID = to_string(int_ID);

            while (str_ID.length() < 8) {
                str_ID = "0" + str_ID;
            }

            auto it = find(UFIDs.begin(), UFIDs.end(), str_ID);

            if (it == UFIDs.end()) {
                valid_ID = true;
            }
        }

        UFIDs.push_back(str_ID);

        // Generate random name
        names.push_back(first_names[dist_first_name(rng)] + " " + last_names[dist_last_name(rng)]);

        // Generate random year
        year = dist_year(rng);
        years.push_back(year);

        // Generate random major and classes based on year
        major_spread = dist_major_spread(rng);
        cs = dist_major_spread(rng);

        // Engineering college gen eds
        if (year == 1) {
            if (cs < 70) {
                cc.push_back("MAC2311");
                if (cs < 40) {
                    cc.push_back("MAC2312");
                }
                if (cs < 20) {
                    cc.push_back("MAC2313");
                }
            }
            if (cs < 50) {
                cc.push_back("PHY2048");
            }
        } else if (year == 2) {
            cc.push_back("MAC2311");
            cc.push_back("MAC2312");
            if (cs < 70) {
                cc.push_back("MAC2313");
                cc.push_back("PHY2048");
                if (cs < 50) {
                    cc.push_back("MAP2302");
                }
                if (cs < 40) {
                    cc.push_back("PHY2049");
                }
            }
        } else if (year == 3) {
            cc.push_back("MAC2311");
            cc.push_back("MAC2312");
            cc.push_back("MAC2313");
            cc.push_back("PHY2048");
            cc.push_back("MAP2302");
            if (cs < 80) {
                cc.push_back("PHY2049");
                if (cs < 50) {
                    cc.push_back("STA3032");
                }
            }
        } else {
            cc.push_back("MAC2311");
            cc.push_back("MAC2312");
            cc.push_back("MAC2313");
            cc.push_back("PHY2048");
            cc.push_back("MAP2302");
            cc.push_back("PHY2049");
            if (cs < 80) {
                cc.push_back("STA3032");
            }
        }

        // Major specific critical tracking classes
        if (major_spread <= 31) {
            majors.push_back("Computer Science");
            if (year == 1) {
                if (cs < 20) {
                    cc.push_back("COP3502C");
                }
            } else if (year == 2) {
                cc.push_back("COP3502C");
                if (cs < 90) {
                    cc.push_back("COP3503C");
                    if (cs < 40) {
                        cc.push_back("COP3530");
                    }
                }
                if (cs < 90) {
                    cc.push_back("COT3100");
                }
                if (cs < 10) {
                    cc.push_back("COP4600");
                }
            } else if (year == 3) {
                cc.push_back("COP3502C");
                cc.push_back("COP3503C");
                cc.push_back("COP3530");
                cc.push_back("COT3100");
                if (cs < 60) {
                    cc.push_back("COP4600");
                    if (cs < 20) {
                        cc.push_back("COP4020");
                    }
                }
            } else {
                cc.push_back("COP3502C");
                cc.push_back("COP3503C");
                cc.push_back("COP3530");
                cc.push_back("COT3100");
                cc.push_back("COP4600");
                if (cs < 80) {
                    cc.push_back("COP4020");
                }
            }
        } else if (major_spread <= 39) {
            majors.push_back("Computer Engineering");
            if (year == 1) {
            } else if (year == 2) {
                if (cs < 50) {
                    cc.push_back("CEN3031");
                }
                if (cs < 40) {
                    cc.push_back("EEL4744C");
                }
            } else if (year == 3) {
                cc.push_back("CEN3031");
                cc.push_back("EEL4744C");
                if (cs < 60) {
                    cc.push_back("EEL4712C");
                    if (cs < 10) {
                        cc.push_back("CEN4908C");
                    }
                }
            } else {
                cc.push_back("CEN3031");
                cc.push_back("EEL4744C");
                cc.push_back("EEL4712C");
                if (cs < 70) {
                    cc.push_back("EEL4712C");
                    if (cs < 40) {
                        cc.push_back("CEN4908C");
                    }
                }
            }
        } else if (major_spread <= 49) {
            majors.push_back("Electrical Engineering");
            if (year == 1) {
                if (cs < 20) {
                    cc.push_back("CHM2095");
                }
            } else if (year == 2) {
                cc.push_back("CHM2095");
            } else if (year == 3) {
                cc.push_back("CHM2095");
                if (cs < 10) {
                    cc.push_back("EEL3923C");
                }
            } else {
                cc.push_back("CHM2095");
                if (cs < 50) {
                    cc.push_back("EEL3923C");
                    if (cs < 20) {
                        cc.push_back("EEL4924C");
                    }
                }
            }
        } else if (major_spread <=60) {
            majors.push_back("Mechanical Engineering");
            if (year == 1) {
                if (cs < 20) {
                    cc.push_back("EML2023");
                }
                if (cs > 10 and cs < 30) {
                    cc.push_back("CHM2045");
                }
            } else if (year > 1) {
                cc.push_back("EML2023");
                cc.push_back("CHM2045");
            }
        } else if (major_spread <= 65) {
            majors.push_back("Biomedical Engineering");
            if (year == 1) {
                if (cs < 40) {
                    cc.push_back("CHM2095");
                    if (cs < 20) {
                        cc.push_back("CHM2096");
                    }
                }
                if (cs > 10 and cs < 60) {
                    cc.push_back("BSC2010");
                }
            } else if (year == 2) {
                cc.push_back("CHM2095");
                if (cs < 90) {
                    cc.push_back("CHM2096");
                }
                cc.push_back("BSC2010");
                if (cs < 30) {
                    cc.push_back("BME 3060");
                }
                if (cs > 10 and cs < 40) {
                    cc.push_back("PCB3713");
                }

            } else if (year == 3) {
                cc.push_back("CHM2095");
                cc.push_back("CHM2096");
                cc.push_back("BSC2010");
                cc.push_back("BME 3060");
                cc.push_back("PCB3713");
                if (cs < 40) {
                    cc.push_back("BME3508");
                    cc.push_back("BME4503");
                    cc.push_back("BME4503L");
                    cc.push_back("BME4311");
                } if (cs > 20 and cs < 60) {
                    cc.push_back("BME3012");
                    cc.push_back("BME3323L");
                    cc.push_back("BME4632");
                }
            } else {
                cc.push_back("CHM2095");
                cc.push_back("CHM2096");
                cc.push_back("BSC2010");
                cc.push_back("BME 3060");
                cc.push_back("PCB3713");
                cc.push_back("BME3508");
                cc.push_back("BME4503");
                cc.push_back("BME4503L");
                cc.push_back("BME4311");
                cc.push_back("BME3012");
                cc.push_back("BME3323L");
                cc.push_back("BME4632");
                if (cs < 40) {
                    cc.push_back("BME4409");
                    cc.push_back("BME4621");
                    cc.push_back("BME4882");
                } if (cs < 15) {
                    cc.push_back("BME4531");
                    cc.push_back("BME4883");
                }
            }
        } else if (major_spread <= 67) {
            majors.push_back("Biological/Agricultural Engineering");
            if (year == 1) {
                if (cs < 40) {
                    cc.push_back("CHM2045");
                    if (cs < 20) {
                        cc.push_back("CHM2046");
                    }
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                if (cs < 60) {
                    cc.push_back("ABE3000C");
                    if (cs < 30) {
                        cc.push_back("EGM3520");
                    }
                }
            } else {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("ABE3000C");
                cc.push_back("EGM3520");
                if (cs < 40) {
                    cc.push_back("ABE4042C");
                    if (cs < 20) {
                        cc.push_back("ABE4043C");
                    }
                }
            }
        } else if (major_spread <= 77) {
            majors.push_back("Civil Engineering");
            if (year == 1) {
                if (cs < 50) {
                    cc.push_back("CHM2045");
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                if (cs < 50) {
                    cc.push_back("COT3100");
                }
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("COT3100");
                if (cs < 40) {
                    cc.push_back("CGN3501C");
                    cc.push_back("EGM3520");
                    cc.push_back("CEG4011");
                } if (cs > 15 and cs < 50) {
                    cc.push_back("CES 3102");
                    cc.push_back("CWR3201");
                    cc.push_back("EGM3400");
                }
            } else {
                cc.push_back("CHM2045");
                cc.push_back("COT3100");
                cc.push_back("CGN3501C");
                cc.push_back("EGM3520");
                cc.push_back("CEG4011");
                cc.push_back("CES 3102");
                cc.push_back("CWR3201");
                cc.push_back("EGM3400");
                if (cs < 50) {
                    cc.push_back("CGN4806");
                }
            }
        } else if (major_spread <= 84) {
            majors.push_back("Industrial Engineering");
            if (year == 2) {
                if (cs < 50) {
                    cc.push_back("COT3100");
                    cc.push_back("COP2332C");
                }
            } else if (year == 3) {
                cc.push_back("COT3100");
                cc.push_back("COP2332C");
                if (cs < 50) {
                    cc.push_back("ESI4356");
                    cc.push_back("ESI4523");
                }
            } else {
                cc.push_back("COT3100");
                cc.push_back("COP2332C");
                cc.push_back("ESI4356");
                cc.push_back("ESI4523");
            }
        } else if (major_spread <= 89) {
            majors.push_back("Aerospace Engineering");
            if (year == 1) {
                if (cs < 50) {
                    cc.push_back("CHM2045");
                    cc.push_back("EML2023");
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                cc.push_back("EML2023");
                if (cs < 50) {
                    cc.push_back("COT3100");
                    cc.push_back("ESI4523");
                }
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("EML2023");
                cc.push_back("COT3100");
                cc.push_back("ESI4523");
                if (cs < 50) {
                    cc.push_back("EGM3344");
                    cc.push_back("EGM3401");
                    cc.push_back("EAS4101");
                    cc.push_back("EGM3520");
                    if (cs < 30) {
                        cc.push_back("EML3301C");
                    }
                }
            } else {
                cc.push_back("CHM2045");
                cc.push_back("EML2023");
                cc.push_back("COT3100");
                cc.push_back("ESI4523");
                cc.push_back("EGM3344");
                cc.push_back("EGM3401");
                cc.push_back("EAS4101");
                cc.push_back("EGM3520");
                if (cs < 50) {
                    cc.push_back("MAP4305");
                    cc.push_back("EML4312");
                    cc.push_back("EAS4132");
                    cc.push_back("EML3301C");
                    if (cs < 30) {
                        cc.push_back("EAS4510");
                        cc.push_back("EAS4400");
                        cc.push_back("EAS4200");
                    }
                }
            }
        } else if (major_spread <= 91) {
            majors.push_back("Materials Science");
            if (year == 1) {
                if (cs < 40) {
                    cc.push_back("CHM2045");
                    if (cs < 20) {
                        cc.push_back("CHM2046");
                    }
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                if (cs < 50) {
                    cc.push_back("EMA3010");
                }
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("EMA3010");
                if (cs < 50) {
                    cc.push_back("EMA4125");
                }
            } else {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("EMA3010");
                cc.push_back("EMA4125");
            }
        } else if (major_spread <= 96) {
            majors.push_back("Chemical Engineering");
            if (year == 1) {
                if (cs < 70) {
                    cc.push_back("CHM2045");
                    if (cs < 40) {
                        cc.push_back("CHM2046");
                    } if (cs < 25) {
                        cc.push_back("ECH2934");
                    }
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                if (cs < 40) {
                    cc.push_back("ECH2934");
                    cc.push_back("ECH3023");
                    cc.push_back("STA3032");
                } if (cs > 15 and cs < 55) {
                    cc.push_back("COT3502");
                    cc.push_back("ECH3101");
                    cc.push_back("ECH3264");
                }
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("ECH2934");
                cc.push_back("ECH3023");
                cc.push_back("STA3032");
                cc.push_back("COT3502");
                cc.push_back("ECH3101");
                cc.push_back("ECH3264");
                if (cs < 50) {
                    cc.push_back("ECH3203");
                    cc.push_back("ECH3223");
                    cc.push_back("ECH4123");
                    cc.push_back("ENC3246");
                } if (cs > 15 and cs < 55) {
                    cc.push_back("CHM2211");
                    cc.push_back("CHM2211L");
                    cc.push_back("ECH4224L");
                    cc.push_back("ECH4403");
                    cc.push_back("ECH4714");
                }
            } else {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("ECH2934");
                cc.push_back("ECH3023");
                cc.push_back("STA3032");
                cc.push_back("COT3502");
                cc.push_back("ECH3101");
                cc.push_back("ECH3264");
                cc.push_back("ECH3203");
                cc.push_back("ECH3223");
                cc.push_back("ECH4123");
                cc.push_back("ENC3246");
                cc.push_back("CHM2211");
                cc.push_back("CHM2211L");
                cc.push_back("ECH4224L");
                cc.push_back("ECH4403");
                cc.push_back("ECH4714");
                if (cs < 50) {
                    cc.push_back("CGN3710");
                    cc.push_back("ECH4504");
                    cc.push_back("ECH4604");
                    cc.push_back("ECH4824");
                }
            }
        } else if (major_spread <= 97) {
            majors.push_back("Nuclear Engineering");
            if (year == 1) {
                if (cs < 60) {
                    cc.push_back("CHM2045");
                    if (cs < 30) {
                        cc.push_back("CHM2046");
                    }
                }
            } else if (year == 2) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                if (cs < 50) {
                    cc.push_back("ENU4001");
                    cc.push_back("MAP2302");
                }
            } else if (year == 3) {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("ENU4001");
                cc.push_back("MAP2302");
            } else {
                cc.push_back("CHM2045");
                cc.push_back("CHM2046");
                cc.push_back("ENU4001");
                cc.push_back("MAP2302");
            }
        } else {
            majors.push_back("Digital Arts and Sciences");
            if (year == 2) {
                if (cs < 60) {
                    cc.push_back("ARH2051");
                    cc.push_back("COP3530");
                }
            } else if (year == 3) {
                cc.push_back("ARH2051");
                cc.push_back("COP3530");
                if (cs < 50) {
                    cc.push_back("CAP3020");
                }
            } else {
                cc.push_back("ARH2051");
                cc.push_back("COP3530");
                cc.push_back("CAP3020");
            }
        }

        // If there are no classes, fill vector w/ null class
        if (cc.size() == 0) {
            cc.push_back("null");
        }

        // Add all classes
        classes.push_back(cc);
    }

    // Write to text file
    ofstream output(output_addr);
    if (output.is_open()) {
        for (int i=0; i<UFIDs.size(); i++) {
            output << "# " << UFIDs[i] << " \" " << names[i] << " \" " << years[i] << " \" " << majors[i] << " \"" << endl;
            if (!classes[i].empty() and classes[i][0] != "null") {
                output << "- ";
                for (string cl : classes[i]) {
                    output << cl << " ";
                }
                output << "." << endl;
            }
            output << endl;
        }
        output.close();
        return;
    } else {
        cout << "Problem creating output file." << endl;
        return;
    }
}
