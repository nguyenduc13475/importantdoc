#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Helper Functions

double dCeil(double n){
    if (abs(n - (int)n) < 1e-7) return round(n);
    else return ceil(n);
}

int clamp(int n, int lowerBound, int upperBound){
    return max(lowerBound, min(upperBound, n));
}

bool containSpecialChar(const char * s, const char * specialChars){
    uint8_t i = 0;
    while (specialChars[i] != '\0'){
        if (strchr(s, specialChars[i])) return true;
        i++;
    }

    return false;
}

int invalidCharIndex(const char * s){
    uint32_t i = 0;
    while (s[i] != '\0'){
        if (
            s[i] <= 32 || 
            s[i] == 34 || 
            s[i] >= 38 && s[i] <= 47 || 
            s[i] >= 58 && s[i] <= 63 || 
            s[i] >= 91 && s[i] <= 96 || 
            s[i] >= 123
        ) return i;
        i++;
    }

    return -1;
}

uint8_t recursiveSumOfDigits(uint32_t n) {
    if (n <= 9) return n;

    uint32_t sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }

    return recursiveSumOfDigits(sum);
}

uint32_t nearestSquareNumber(uint32_t n){
    return pow(round(sqrt(n)), 2);
}

uint8_t getProbability(uint16_t exp){
    uint16_t s = nearestSquareNumber(exp);
    if (exp >= s) return 100;
    else return round(exp / 1.23 / s + 80 / 1.23);
}

int getMaxOfTwoDiagonals(int (&matrix)[10][10], uint8_t iMeet, uint8_t jMeet){
    uint8_t offset = min(iMeet, jMeet);
    uint8_t i = iMeet - offset;
    uint8_t j = jMeet - offset;

    int diagonalMax = matrix[i][j];
    while (i < 9 && j < 9){
        i++;
        j++;
        diagonalMax = max(matrix[i][j], diagonalMax);
    }

    offset = min((uint8_t)(9 - iMeet), jMeet);
    i = iMeet + offset;
    j = jMeet - offset;
    while (i >= 0 && j <= 9){
        diagonalMax = max(matrix[i][j], diagonalMax);
        i--;
        j++;
    }

    return diagonalMax;
}

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    if (clamp(e1, 0, 99) != e1) return -99;

    if (e1 <= 3){
        if (e1 == 0) exp2 += 29;
        else if (e1 == 1) exp2 += 45;
        else if (e1 == 2) exp2 += 75;
        else exp2 += 149;

        int D = e1 * 3 + exp1 * 7;
        if (D % 2) exp1 = dCeil(exp1 - D / 100.);
        else exp1 = dCeil(exp1 + D / 200.);
    } else {
        if (e1 >= 4 && e1 <= 19) exp2 = dCeil(exp2 + e1 / 4. + 19);
        else if (e1 >= 20 && e1 <= 49) exp2 = dCeil(exp2 + e1 / 9. + 21);
        else if (e1 >= 50 && e1 <= 65) exp2 = dCeil(exp2 + e1 / 16. + 17);
        else if (e1 >= 66 && e1 <= 79) {
            exp2 = dCeil(exp2 + e1 / 4. + 19);
            if (exp2 > 200) exp2 = dCeil(exp2 + e1 / 9. + 21);
        } else {
            exp2 = dCeil(exp2 + e1 / 4. + 19);
            exp2 = dCeil(exp2 + e1 / 9. + 21);
            if (exp2 > 400) {
                exp2 = dCeil(exp2 + e1 / 16. + 17);
                exp2 = dCeil(1.15 * exp2);
            }
        }

        exp1 -= e1;
    }

    exp1 = clamp(exp1, 0, 600);
    exp2 = clamp(exp2, 0, 600);

    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    if (clamp(E2, 0, 99) != E2) return -99;

    // Route 1
    uint16_t P1 = getProbability(EXP1);

    // Route 2
    uint16_t moneySpent = 0;
    if (E2 % 2){
        while (true){
            if (HP1 < 200){
                HP1 = dCeil(HP1 * 1.3);
                moneySpent += 150;
            } else {
                HP1 = dCeil(HP1 * 1.1);
                moneySpent += 70;
            }
            if (moneySpent > 0.5 * M1) break;

            if (EXP1 < 400) moneySpent += 200;
            else moneySpent += 120;
            EXP1 = clamp(dCeil(EXP1 * 1.13), 0, 600);
            if (moneySpent > 0.5 * M1) break;

            if (EXP1 < 300) moneySpent += 100;
            else moneySpent += 120;
            EXP1 = dCeil(EXP1 * 0.9);
            if (moneySpent > 0.5 * M1) break;
        }
    } else {
        if (HP1 < 200){
            HP1 = dCeil(HP1 * 1.3);
            moneySpent += 150;
        } else {
            HP1 = dCeil(HP1 * 1.1);
            moneySpent += 70;
        }
        if (M1 > moneySpent){
            if (EXP1 < 400) moneySpent += 200;
            else moneySpent += 120;
            EXP1 = clamp(dCeil(EXP1 * 1.13), 0, 600);
            if (M1 > moneySpent){
                if (EXP1 < 300) moneySpent += 100;
                else moneySpent += 120;
                EXP1 = dCeil(EXP1 * 0.9);
            }
        }
    }

    M1 = clamp(M1 - moneySpent, 0, 3000);
    HP1 = dCeil(clamp(HP1, 0, 666) * 0.83);
    EXP1 = clamp(dCeil(EXP1 * 1.17), 0, 600);
    uint16_t P2 = getProbability(EXP1);

    // Route 3
    uint16_t P[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    uint16_t P3 = P[((E2 / 10) + (E2 % 10)) % 10];

    // All Route
    if (P1 == 100 && P2 == 100 && P3 == 100) EXP1 = dCeil(EXP1 * 0.75);
    else {
        uint16_t averageP = round((P1 + P2 + P3) / 3.);
        if (averageP < 50){
            HP1 = dCeil(HP1 * 0.85);
            EXP1 = clamp(dCeil(EXP1 * 1.15), 0, 600);
        } else {
            HP1 = dCeil(HP1 * 0.9);
            EXP1 = clamp(dCeil(EXP1 * 1.2), 0, 600);
        }
    }

    return HP1 + EXP1 + M1;
}

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    if (clamp(E3, 0, 99) != E3) return -99;

    int taxiMatrix[10][10];
    uint8_t iMeet = 0, jMeet = 0;

    for (uint8_t i = 0; i <= 9; i++)
        for (uint8_t j = 0; j <= 9; j++){
            taxiMatrix[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if (taxiMatrix[i][j] > E3 * 2) iMeet += 1;
            if (taxiMatrix[i][j] < -E3) jMeet += 1;
        }
    
    iMeet = recursiveSumOfDigits(iMeet);
    jMeet = recursiveSumOfDigits(jMeet);

    int SherlockWatsonScore = abs(getMaxOfTwoDiagonals(taxiMatrix, iMeet, jMeet));
    int taxiScore = taxiMatrix[iMeet][jMeet];

    if (SherlockWatsonScore < abs(taxiScore)){
        EXP1 = dCeil(EXP1 * 0.88);
        EXP2 = dCeil(EXP2 * 0.88);
        HP1 = dCeil(HP1 * 0.9);
        HP2 = dCeil(HP2 * 0.9);

        return taxiScore;
    } else {
        EXP1 = clamp(dCeil(EXP1 * 1.12), 0, 600);
        EXP2 = clamp(dCeil(EXP2 * 1.12), 0, 600);
        HP1 = clamp(dCeil(HP1 * 1.1), 0, 666);
        HP2 = clamp(dCeil(HP2 * 1.1), 0, 666);

        return SherlockWatsonScore;
    }
}

// Task 4
int checkPassword(const char * s, const char * email) {
    // TODO: Complete this function
    if (strlen(s) < 8) return -1;
    if (strlen(s) > 20) return -2;

    uint8_t delimiterIndex = strchr(email, '@') - email;
    char se[delimiterIndex + 1] = {};
    strncpy(se, email, delimiterIndex);
    char * sePointer = strstr(s, se);
    if (sePointer) return -(300 + (sePointer - s));
    
    for (uint32_t i = 0; i < strlen(s) - 1; i++)
        if (s[i] == s[i + 1]) return -(400 + i);

    if (!containSpecialChar(s, "@#%$!")) return -5;

    uint32_t invalidIndex = invalidCharIndex(s);
    if (invalidIndex != -1) return invalidIndex;

    return -10;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function
    uint8_t indices[num_pwds];
    for (uint8_t i = 0; i < num_pwds; i++) indices[i] = i;

    for (uint8_t i = 0; i < num_pwds; i++){
        uint8_t currentMinIndex = i;
        for (uint8_t j = i + 1; j < num_pwds; j++){
            int8_t cmp = strcmp(arr_pwds[currentMinIndex], arr_pwds[j]);
            if (cmp == 1) currentMinIndex = j;
        }

        const char * temp1 = arr_pwds[i];
        arr_pwds[i] = arr_pwds[currentMinIndex];
        arr_pwds[currentMinIndex] = temp1;

        uint8_t temp2 = indices[i];
        indices[i] = indices[currentMinIndex];
        indices[currentMinIndex] = temp2;
    }

    uint8_t frequencies[num_pwds] = {1}, currentIndex = 0;
    size_t lengths[num_pwds] = {strlen(arr_pwds[0])};

    for (uint8_t i = 1; i < num_pwds; i++){
        if (!strcmp(arr_pwds[i], arr_pwds[i - 1])) frequencies[currentIndex] += 1;
        else {
            currentIndex++;
            frequencies[currentIndex] = 1;
            lengths[currentIndex] = strlen(arr_pwds[i]);
            indices[currentIndex] = indices[i];
        }
    }

    uint8_t maxIndex = 0;
    for (uint8_t i = 1; i <= currentIndex; i++)
        if (frequencies[i] > frequencies[maxIndex]) maxIndex = i;
        else if (frequencies[i] == frequencies[maxIndex])
            if (lengths[i] > lengths[maxIndex]) maxIndex = i;
            else if (lengths[i] == lengths[maxIndex]) maxIndex = indices[i] > indices[maxIndex] ? maxIndex : i;

    return indices[maxIndex];
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////