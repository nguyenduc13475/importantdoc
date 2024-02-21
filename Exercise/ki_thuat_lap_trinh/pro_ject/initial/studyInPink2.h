/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2022
    * Author: Tran Huy
    * Date: 06.01.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

//======================task 1==================================
int check(int n, int firstpoint, int lastpoint) {
    n = (n < firstpoint) ? firstpoint : (n > lastpoint) ? lastpoint : n;
    return n;
}

int firstMeet(int& EXP1, int& EXP2, const int& E1) {
    int firstpoint = 0, lastpoint = 900;
    //Complete this function to gain point on task 1

    //=========check the input=============
    if (E1 < 0 || E1 > 999) return -999;
    EXP1 = check(EXP1, firstpoint, lastpoint);
    EXP2 = check(EXP2, firstpoint, lastpoint);
    //=======================================

    //========= case 1 or 2 ??==============
    int in4;
    bool case1;
    if (E1 <= 399) {
        in4 = (E1 > 349) ? 7 : (E1 / 50 + 1);
        case1 = 1;
    }
    else {
        in4 = (E1 > 899) ? 5 : (E1 / 100 - 3);
        case1 = 0;
    }
    //=====================================================

    //==========some  var===========================
    const int inform1_1 = 25, inform1_2 = 50, inform1_3 = 85;
    float inform2_1, inform2_2, inform2_3;
    inform2_1 = E1 * 1.0000 / 7 + 9;
    inform2_2 = E1 * 1.0000 / 9 + 11;
    inform2_3 = E1 * 1.0000 / 5 + 6;
    float EXP1_test = EXP1; // use float var to caculate
    float EXP2_test = EXP2;

    //=====================solution======================
    if (case1) {
        // caculate EXP2 (dont need to round up)
        switch (in4)
        {
        case 1:
        {
            EXP2 += inform1_1;
            break;
        }
        case 2:
        {
            EXP2 += inform1_2;
            break;
        }
        case 3:
        {
            EXP2 += inform1_3;
            break;
        }
        case 4:
        {
            EXP2 = EXP2 + inform1_1 + inform1_2;
            break;
        }
        case 5:
        {
            EXP2 = EXP2 + inform1_1 + inform1_3;
            break;
        }
        case 6:
        {
            EXP2 = EXP2 + inform1_2 + inform1_3;
            break;
        }
        case 7:
        {
            EXP2 = EXP2 + inform1_1 + inform1_2 + inform1_3;
            break;
        }
        }
        //caculate EXP1  (need to round up)    
        if (E1 % 2) EXP1_test = ceil(EXP1_test + E1 * 1.0000 / 10);
        else EXP1_test = ceil(EXP1_test - E1 * 1.0000 / 5);
        EXP1 = EXP1_test;
    }
    // case 2
    else {
        //caculate EXP2 (need round up)
        switch (in4)
        {
        case 1:
        {
            EXP2_test += inform2_1;
            break;
        }
        case 2:
        {
            EXP2_test += inform2_2;
            break;
        }
        case 3:
        {
            EXP2_test += inform2_3;
            break;
        }
        case 4:
        {
            EXP2_test = ceil(EXP2_test + inform2_1); // add inform2_1 and roundup value and check value
            EXP2 = EXP2_test;                         // convert to int to check value
            EXP2 = check(EXP2, firstpoint, lastpoint);
            EXP2_test = EXP2; //return EXP2 to EXP2_test to continue caculate
            if (EXP2_test > 200) EXP2_test += inform2_2;
            break;
        }
        case 5:
        {
            /*EXP2_test = ceil(EXP2_test + inform2_1 + inform2_2); // inform 1 & 2
            EXP2 = EXP2_test;                         // convert to int to check value
            EXP2 = check(EXP2, firstpoint, lastpoint);
            EXP2_test = EXP2; //return EXP2 to EXP2_test to continue caculate*/
            EXP2 = EXP2 + ceil(inform2_1);
            EXP2 = check(EXP2, firstpoint, lastpoint);
            EXP2 = EXP2 + ceil(inform2_2);
            EXP2 = check(EXP2, firstpoint, lastpoint);
            EXP2_test = EXP2;
            if (EXP2_test > 600) {
                EXP2_test = ceil(EXP2_test + inform2_3);
                EXP2 = EXP2_test;                         // convert to int to check value
                EXP2 = check(EXP2, firstpoint, lastpoint);
                EXP2_test = EXP2; //return EXP2 to EXP2_test to continue caculate
                EXP2_test = EXP2_test * 1.1500;
            }
            break;
        }
        }
        // round up EXP2
        EXP2_test = ceil(EXP2_test);
        EXP2 = EXP2_test;
        //caculate EXP1 (need round up)
        EXP1_test = ceil(EXP1_test - 0.1000 * E1);
        EXP1 = EXP1_test;
    }
    //check the result
    EXP1 = check(EXP1, firstpoint, lastpoint);
    EXP2 = check(EXP2, firstpoint, lastpoint);
    return EXP1 + EXP2;
}

//======================Task 2==========================
void round_checkTask2_1(int& EXP1, int& EXP2, float inform) { // use address of EXP1 and 2
    float EXP1_test = EXP1;
    float EXP2_test = EXP2;
    //round
    EXP2_test = ceil(EXP2_test + inform);
    EXP1_test = ceil(EXP1_test + inform / 3);
    EXP1 = EXP1_test;
    EXP2 = EXP2_test;
    //check
    EXP1 = check(EXP1, 0, 900);
    EXP2 = check(EXP2, 0, 900);
}

int investigateScene(int& EXP1, int& EXP2, int& HP2, int& M2, const int& E2) {
    //========check input===========
    if (E2 < 0 || E2 > 999) return -999;
    EXP1 = check(EXP1, 0, 900);
    EXP2 = check(EXP2, 0, 900);
    HP2 = check(HP2, 0, 999);
    M2 = check(M2, 0, 2000);

    //======some var  to caculate======
    float inform1 = 1.0000 * E2 / 9 + 10;
    float inform2 = 0.3500 * E2;

    //=========state 1==========
    // check case
    int in4;
    if (E2 >= 0 && E2 < 300) in4 = 1;
    else if (E2 < 500) in4 = 2;
    else in4 = 3;
    //caculate EXP1 & 2
    switch (in4)
    {
    case 1:
    {
        round_checkTask2_1(EXP1, EXP2, inform1);
        break;
    }
    case 2:
    {
        round_checkTask2_1(EXP1, EXP2, inform1);
        round_checkTask2_1(EXP1, EXP2, inform2);
        break;
    }
    case 3:
    {
        round_checkTask2_1(EXP1, EXP2, inform1);
        round_checkTask2_1(EXP1, EXP2, inform2);
        round_checkTask2_1(EXP1, EXP2, 0.17 * inform1 + 0.17 * inform2);
        break;
    }
    }

    //===============state 2=================
    float HP2_test = HP2;
    HP2_test = ceil(1.0000 * HP2_test - 1.0000 * E2 * E2 * E2 / pow(2, 23));
    HP2 = HP2_test;
    HP2 = check(HP2, 0, 999);
    M2 = (E2 % 2) ? M2 : (M2 + ceil(1.0000 * E2 * E2 / 50));
    M2 = check(M2, 0, 2000);
    return EXP2 + EXP1 + HP2 + M2;
}

//======================task 3===========================

void updateM1(int& M1, int k, int n, int E3, int& founded) { //include checking
    if (k) M1 = M1 - floor(1.0000 * k * E3 / 9); // founded
    else { // no vali in this way
        M1 = M1 - floor(1.0000 * n * n * E3 / 9);
        founded--;
    }
    M1 = check(M1, 0, 2000);
}

int traceLuggage(int& HP1, int& EXP1, int& M1, const int& E3) {
    //Complete this function to gain point on task 3

    //============== check input=================
    if (E3 < 0 || E3 > 999) return -999;
    HP1 = check(HP1, 0, 999);
    EXP1 = check(EXP1, 0, 900);
    M1 = check(M1, 0, 2000);
    //======================================

    //==============var for 4 ways==============
    int founded = 4; // if u cant find vali, founded -- => 4 ways dont have vali, founded = 0
    int P1[9] = { 1,3,5,7,9,11,13,15,17 };
    int P2[7] = { 2,3,5,7,11,13,17 };
    int P3[20];
    for (int i = 0; i < 20; i++) P3[i] = 4 * (i + 1) * (i + 1);
    int P4[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int k = 0; //place of vali
    //========================================== (note : - use floor, + use ceil)

    //=========way 1====================(round up )
    for (int i = 0; i < 9; i++) {
        P1[i] = (P1[i] + E3) % 26 + 65;
        if (P1[i] == 80) {
            k = i + 1;
            HP1 = check(HP1 - (P1[i] * k * 2), 0, 999); //k = i+1
            EXP1 = check(EXP1 + ((1000 - P1[i] * k) % 101), 0, 900);
            break;
        }
    }
    updateM1(M1, k, 9, E3, founded);
    k = 0; // reset k
    //========================================

    //==============way 2======================
    // first change
    int sum = 0, aver = 0;
    for (int i = 0; i < 7; i++) {
        P2[i] = (P2[i] + E3) % 26;
        sum += P2[i];
    }
    aver = aver + ceil(1.0000 * sum / 7);
    // second change
    for (int i = 0; i < 7; i++) {
        P2[i] = (P2[i] + sum + aver) % 26 + 65;
        if (P2[i] == 80) {
            k = i + 1;
            HP1 = check(HP1 - (P2[i] * k * 2), 0, 999); //k = i+1
            EXP1 = check(EXP1 + ((1000 - P2[i] * k) % 101), 0, 900);
            break;
        }
    }
    updateM1(M1, k, 7, E3, founded);
    k = 0;
    //===========================================

    //================way 3======================
    // first change
    int max = P3[0];
    for (int i = 0; i < 20; i++) {
        P3[i] = (P3[i] + E3 * E3) % 113;
        if (P3[i] > max) max = P3[i];
    }
    //second change
    for (int i = 19; i >= 0; i--) {
        P3[i] = int(ceil((1.000 * P3[i] + E3) / max)) % 26 + 65;
        if (P3[i] == 80) {
            k = 20 - i;
            HP1 = check(HP1 - P3[i] * k * 3, 0, 999);
            EXP1 = check(EXP1 + ((3500 - P3[i] * k) % 300), 0, 900);
            break;
        }
    }
    updateM1(M1, k, 20, E3, founded);
    k = 0; //reset k
    //================================================

    //==================way 4=========================
    int min = P4[0];
    int PlaceOfMin = 1;
    //1st change
    for (int i = 0; i < 12; i++) {
        P4[i] = int(P4[i] + pow(ceil(1.0000 * E3 / 29), 3)) % 9;
        if (P4[i] < min) {
            min = P4[i];
            PlaceOfMin = i + 1;
        }
    }
    //2nd change
    for (int i = 11; i >= 0; i--) {
        P4[i] = int((P4[i] + E3) * ceil(1.0000 * min / PlaceOfMin)) % 26 + 65;
        if (P4[i] == 80) {
            k = 12 - i;
            HP1 = check(HP1 - P4[i] * k * 4, 0, 999);
            EXP1 = check(EXP1 + ((4500 - P4[i] * k) % 400), 0, 900);
            break;
        }
    }
    updateM1(M1, k, 12, E3, founded);
    //result
    if (founded) {
        return HP1 + M1 + EXP1;
    }
    else {
        HP1 = check(HP1 - ((59 * E3) % 900),0,999);
        EXP1 = check(EXP1 - ((79 * E3) % 300),0,900);
        return -1;
    }
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
