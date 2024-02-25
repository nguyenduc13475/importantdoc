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

// More accurate ceiling function due to precision loss
// Example: ceil(400 * 1.1) will return 441 not 440, but dCeil(400 * 1.1) will return 440
int dCeil(double n){
    return n + 0.999999;
}

// Bound the value
int clamp(int n, int lowerBound, int upperBound){
    return max(lowerBound, min(upperBound, n));
}

// Check whether or not String s contains any character in specialChars
bool containSpecialChar(const char * s, const char * specialChars){
    uint8_t i = 0;
    while (specialChars[i] != '\0'){
        if (strchr(s, specialChars[i])) return true;
        i++;
    }

    return false;
}

// Return the Index of first invalid character in password
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

// Calculate the sum of all digits of a number until it is reduced to 1 digit
// Example: 78 -> 7 + 8 = 15 -> 1 + 5 = 6
uint8_t recursiveSumOfDigits(uint32_t n) {
    if (n <= 9) return n;

    uint32_t sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }

    return recursiveSumOfDigits(sum);
}

// Find the nearest square number of a non negative integer
uint32_t nearestSquareNumber(uint32_t n){
    return pow(round(sqrt(n)), 2);
}

// Calculate the probability of finding luggage, range from 0 to 100
double getProbability(uint16_t exp){
    uint16_t s = nearestSquareNumber(exp);
    if (exp >= s) return 100.;
    else return exp / 1.23 / s + 80 / 1.23;
}

// Find the maximum in both the left and right diagonals at a specific point in a 10 x 10 matrix
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
    // Clamp the inputs
    if (clamp(e1, 0, 99) != e1) return -99;
    exp1 = clamp(exp1, 0, 600);
    exp2 = clamp(exp2, 0, 600);

    // Define value of each inform
    const uint16_t inform_1_1 = 29, inform_1_2 = 45, inform_1_3 = 75;
    const double inform_2_1 = e1 / 4. + 19, inform_2_2 = e1 / 9. + 21, inform_2_3 = e1 / 16. + 17;

    if (e1 <= 3){
        // Case 1
        switch (e1){
            case 0: exp2 += inform_1_1; break;
            case 1: exp2 += inform_1_2; break;
            case 2: exp2 += inform_1_3; break;
            case 3: exp2 += inform_1_1 + inform_1_2 + inform_1_3; break;
        }
        int D = e1 * 3 + exp1 * 7;
        if (D % 2) exp1 = dCeil(exp1 - D / 100.);
        else exp1 = dCeil(exp1 + D / 200.);
    } else {
        // Case 2
        if (e1 >= 4 && e1 <= 19) exp2 = dCeil(exp2 + inform_2_1);
        else if (e1 >= 20 && e1 <= 49) exp2 = dCeil(exp2 + inform_2_2);
        else if (e1 >= 50 && e1 <= 65) exp2 = dCeil(exp2 + inform_2_3);
        else if (e1 >= 66 && e1 <= 79) {
            exp2 = dCeil(exp2 + inform_2_1);
            if (exp2 > 200) exp2 = dCeil(exp2 + inform_2_2);
        } else {
            exp2 = dCeil(exp2 + inform_2_1);
            exp2 = dCeil(exp2 + inform_2_2);
            if (exp2 > 400) {
                exp2 = dCeil(exp2 + inform_2_3);
                exp2 = dCeil(1.15 * exp2);
            }
        }

        exp1 -= e1;
    }

    // Clamp the results
    exp1 = clamp(exp1, 0, 600);
    exp2 = clamp(exp2, 0, 600);

    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2) {
    // TODO: Complete this function
    // Clamp the inputs
    if (clamp(E2, 0, 99) != E2) return -99;
    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    M1 = clamp(M1, 0, 3000);

    // Calculate the probability of finding luggage in route 1
    double P1 = getProbability(EXP1);

    // Route 2
    uint16_t moneySpent = 0;
    if (M1){
        if (E2 % 2){
            // Case 1, loop until money spent greater than half of the initial amount of money
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
            // Case 2, only implement each action once, also stop when all the money is spent
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
    }

    // Clamp the result
    M1 = clamp(M1 - moneySpent, 0, 3000);
    HP1 = dCeil(clamp(HP1, 0, 666) * 0.83);
    EXP1 = clamp(dCeil(EXP1 * 1.17), 0, 600);

    // Calculate the probability of finding luggage in route 2
    double P2 = getProbability(EXP1);

    // Define the array of probabities
    double P[10] = {32., 47., 28., 79., 100., 50., 22., 83., 64., 11.};
    // Get the probability of finding luggage in route 3 from the array above
    double P3 = P[((E2 / 10) + (E2 % 10)) % 10];

    // Calculate final results
    if (P1 == 100. && P2 == 100. && P3 == 100.) EXP1 = dCeil(EXP1 * 0.75);
    else {
        double averageP = (P1 + P2 + P3) / 3.;
        if (averageP < 50.){
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
    // Clamp the inputs
    if (clamp(E3, 0, 99) != E3) return -99;
    HP1 = clamp(HP1, 0, 666);
    EXP1 = clamp(EXP1, 0, 600);
    HP2 = clamp(HP2, 0, 666);
    EXP2 = clamp(EXP2, 0, 600);

    // Define the score matrix for the taxi
    int taxiMatrix[10][10];
    uint8_t iMeet = 0, jMeet = 0;

    // Calculate scores for the score matrix
    for (uint8_t i = 0; i <= 9; i++)
        for (uint8_t j = 0; j <= 9; j++){
            taxiMatrix[i][j] = ((E3 * j) + (i * 2)) * (i - j);
            if (taxiMatrix[i][j] > E3 * 2) iMeet += 1;
            if (taxiMatrix[i][j] < -E3) jMeet += 1;
        }
    
    // Calculate the meeting location
    iMeet = recursiveSumOfDigits(iMeet);
    jMeet = recursiveSumOfDigits(jMeet);

    // Calculate score for Sherlock and Watson
    int SherlockWatsonScore = abs(getMaxOfTwoDiagonals(taxiMatrix, iMeet, jMeet));
    // Get the score of the taxi
    int taxiScore = taxiMatrix[iMeet][jMeet];

    if (SherlockWatsonScore < abs(taxiScore)){
        // Case 1, Sherlock and Watson missed the taxi
        EXP1 = dCeil(EXP1 * 0.88);
        EXP2 = dCeil(EXP2 * 0.88);
        HP1 = dCeil(HP1 * 0.9);
        HP2 = dCeil(HP2 * 0.9);

        return taxiScore;
    } else {
        // Case 2, Sherlock and Watson caught the taxi
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
    // Case 1, password length is too short
    if (strlen(s) < 8) return -1;
    // Case 2, password length is too long
    if (strlen(s) > 20) return -2;

    // Get se, that is the part in the left of '@' in the email
    uint8_t delimiterIndex = strchr(email, '@') - email;
    char se[delimiterIndex + 1] = {};
    strncpy(se, email, delimiterIndex);
    const char * sePointer = strstr(s, se);
    // Case 3, password contains se
    if (sePointer) return -(300 + (sePointer - s));
    
    // Case 4, password contains more than two consecutive identical characters
    for (uint32_t i = 0; i < strlen(s) - 2; i++)
        if (s[i] == s[i + 1] && s[i + 1] == s[i + 2]) return -(400 + i);

    // Case 5, password doesn't contain any special character
    if (!containSpecialChar(s, "@#%$!")) return -5;

    // Case 6, password contains invalid character
    uint32_t invalidIndex = invalidCharIndex(s);
    if (invalidIndex != -1) return invalidIndex;

    // Case 7, password is valid
    return -10;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function
    // Define the array that contains the index of each password
    uint8_t indices[num_pwds];
    for (uint8_t i = 0; i < num_pwds; i++) indices[i] = i;

    // Implement the selection sort on the array of passwords
    for (uint8_t i = 0; i < num_pwds; i++){
        uint8_t currentMinIndex = i;
        for (uint8_t j = i + 1; j < num_pwds; j++){
            int8_t cmp = strcmp(arr_pwds[currentMinIndex], arr_pwds[j]);
            if (cmp > 0) currentMinIndex = j;
        }
        
        // Swap positions
        const char * temp1 = arr_pwds[i];
        arr_pwds[i] = arr_pwds[currentMinIndex];
        arr_pwds[currentMinIndex] = temp1;

        uint8_t temp2 = indices[i];
        indices[i] = indices[currentMinIndex];
        indices[currentMinIndex] = temp2;
    }

    // Define the array that contains the number of occurrences of each password in the sorted array of passwords
    uint8_t frequencies[num_pwds] = {1}, currentIndex = 0;
    // Define the array that contains the length of each distinct password in the sorted array of passwords
    size_t lengths[num_pwds] = {strlen(arr_pwds[0])};

    // Calculate values for the two arrays above
    for (uint8_t i = 1; i < num_pwds; i++){
        if (!strcmp(arr_pwds[i], arr_pwds[i - 1])) frequencies[currentIndex] += 1;
        else {
            currentIndex++;
            frequencies[currentIndex] = 1;
            lengths[currentIndex] = strlen(arr_pwds[i]);
            // Index of the first password in the group of identical passwords
            indices[currentIndex] = indices[i];
        }
    }

    // Find the password that appears the most, using the frequencies array
    // If two distinct passwords have the same frequency, choose the longer password
    // If two distinct passwords have the same frequency and length, choose the password that appears earlier
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