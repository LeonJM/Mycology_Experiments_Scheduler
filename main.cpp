#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>


std::ofstream outFile("results.csv", std::ios::out | std::ios::app);


int testCount;
std::vector<std::vector<char>> sequences;
char lastID;


void saveSequence(char arr[], int n) {
    std::vector<char> tempSequence;
    for (int i = 0; i < n; i ++) {
        tempSequence.push_back(arr[i]);
    }
    sequences.push_back(tempSequence);
}


void findPermutations(char arr[], int n) {
    std::sort(arr, arr + n);
    do {
        saveSequence(arr, n);
    } while (std::next_permutation(arr, arr + n));
}


void processSequence(std::vector<char> sequence, char lastID) {
    int indexOfLastID;
    for (int i = 0; i < testCount; i ++) {
        if (sequence.at(i) == lastID) {
            indexOfLastID = i;
            break;
        }
    }

    for (int i = 0; i < testCount - 1 - indexOfLastID; i ++) {
        outFile << ",";
    }
    for (char i : sequence) {
        outFile << i << ",";
    }
    outFile << "\n" << std::flush;
}


bool comparitor (std::vector<char> p1, std::vector<char> p2) {
    int indexOfLastID1;
    for (int i = 0; i < testCount; i ++) {
        if (p1.at(i) == lastID) {
            indexOfLastID1 = i;
            break;
        }
    }

    int indexOfLastID2;
    for (int i = 0; i < testCount; i ++) {
        if (p2.at(i) == lastID) {
            indexOfLastID2 = i;
            break;
        }
    }

    return indexOfLastID1 > indexOfLastID2;
}


int main() {

    std::cout << "Input quantity of test: ";
    std::cin >> testCount;


    char arr [testCount];
    char alphabetID = 'a';
    for (int i = 0; i < testCount; i ++) {
        arr[i] = alphabetID;
        lastID = alphabetID;
        alphabetID ++;
    }

    int n = sizeof(arr)/sizeof(arr[0]);

    findPermutations(arr, n);

    std::sort(sequences.begin(), sequences.end(), comparitor);

    for (std::vector<char> sequence : sequences) {
        processSequence(sequence, lastID);
    }


    // debug
    // for (std::vector<char> vec : sequences) {
    //     for (char a : vec) {
    //         std::cout << a;
    //     }
    //     std::cout << std::endl;
    // }


    return 0;
}