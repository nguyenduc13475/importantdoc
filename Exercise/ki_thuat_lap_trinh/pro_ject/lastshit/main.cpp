/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink1.h"
#include <ctime>

using namespace std;

int randrange(int a, int b){
    return rand() / 32767. * (b - a) + a;
};

void sa_tc_01() {
    cout << "----- Sample Testcase 01 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    EXP1 = randrange(-200, 800);
    EXP2 = randrange(-200, 800);
    E1 = randrange(-10, 110);

    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E1: " << E1 << endl;
    int result = firstMeet(EXP1, EXP2, E1);
    cout << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", result: " << result << endl;
    cout << " --------------------------------------- " << endl;
}

void sa_tc_02() {
    cout << "----- Sample Testcase 01 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", E2: " << E2 << ", M1: " << M1 << endl;
    int result = traceLuggage(HP1, EXP1, M1, E2);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << endl;
}

void sa_tc_03() {
    cout << "----- Sample Testcase 01 -----" << endl;
    string input_file("sa_tc_01_input");
    int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
    if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3)) {
        return;
    }
    HP1 = randrange(-20, 686);
    EXP1 = randrange(-20, 620);
    HP2 = randrange(-20, 686);
    EXP2 = randrange(-20, 620);
    E3 = randrange(-8, 108);

    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", E3: " << E3 << endl;
    int result = chaseTaxi(HP1, EXP1, HP2, EXP2, E3);
    cout << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", result: " << result << endl;
    cout << "--------------------------------------------" << endl;
}

void sa_tc_04() {
    int result = checkPassword("012345ABC$67", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("01234567890123456789", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("abcpink123pink", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("abc123cccddde", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("abc123ccdde?", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("abc123ccdde@#$!%", "pink@gmail.com");
    cout << result << endl;
    result = checkPassword("abc123ccdde@#abccc", "pink@gmail.com");
    cout << result << endl;
}

void sa_tc_05() {
    const char* foo[6] = {"pink@123", "123!pink", "1234#xyz", "pink#pink", "pink#pink","pink@123"};
    int result = findCorrectPassword(foo, 6);
    cout << result;
}

int main(int argc, const char * argv[]) {
    sa_tc_05();
    system("pause"); // nho remove
    return 0;
}