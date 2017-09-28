//
//  Freq.cpp
//  Datastr_Prog3
//
//  Created by Austin Tao on 4/20/17.
//  Copyright © 2017 Austin Tao. All rights reserved.
//

#include "Freq.hpp"
#include <ctype.h>

inline unsigned ord( char ch ) { return ch - 'A'; }
inline char chr( unsigned ui ) { return ui + 'A'; }

Freq:: Freq(char a, double b){  // Constructor with two parameters
    letter = a;
    percent = b;
    //cout << percent << endl; more testing stuff
}
//--------------------------------------------------------
void Freq:: print(ostream& out) {
    out << setw(7) << setprecision(3) << right << letter << "   " << percent << "%\n";
}
//--------------------------------------------------------
Solver:: Solver(string aFile, string bFile){
    //cout << fileName << endl; // Testing to see if file is there
    ifstream input1 (aFile);  // Opens the file
    if(input1.fail()) {
        fatal("You messed up."); // Gives error message if file is not found
    }
    while (input1.good()) {
        string line;
        getline(input1, line);
        for(int counter = 0; counter < line.length(); counter++) {
            line[counter] = toupper(line[counter]);     //Capitalize letters
            codeText.push_back(line[counter]);      //Add into codeText vector
            if (isalpha(line[counter])) {       //Check if character is a letter
                plainText.push_back('_');        // Change to underscore if it is
            }
            else {
                plainText.push_back(line[counter]);   //If not a letter, keep it as it is
            }
        }
    }
    input1.close();
//--------------------------------------------------------
    ifstream input2 (bFile);
    if(input2.fail()) {
        fatal("You messed up."); // Gives error message if file is not found
    }
    while (input2.good()) {             //Reading Frequency table, initializing english array
        for(int x = 0; x < 26; x++) {
            double numValue;
            input2 >> numValue;
            Freq Phreak = Freq( chr(x), numValue);  // Using given function for ASCI conversion
            english[x] = Phreak;
        }
    }
    input2.close();
    tally();
}
//--------------------------------------------------------
void Solver:: tally() {
    int tallyArray[26]; //For a=0, b=0, c=0, etc.
    for (int n = 0; n < 26; n++){
        tallyArray[n] = 0;
    }
    int letterCount = 0;
    for(int nletters = 0; nletters < codeText.size(); nletters++) { //Checking occurance of each letter in text
        if(isalpha(codeText[nletters])) {
            tallyArray[ord(codeText[nletters])]++;
            letterCount++;
            //cout << tallyArray[ord(codeText[nletters])] << endl; testing if this is normal cuz of big numbers
        }
    }
    scale(tallyArray, letterCount);
}
//--------------------------------------------------------
void Solver::scale(int* tally, int nnletters){
    // Sorted table, local vector use for scale() function
    for(int k = 0; k < 26; k++) {
        if(tally[k] == 0) { // Look for non-zero counter, skip code if it's zero
            continue;
        }
        Freq Scaler = Freq(chr(k), (double)(tally[k]*100.0)/ (double)(codeText.size()));    // Freq object using given function
        sTable.push_back(Scaler);   // Putting stuff in vector
    }
    sort(sTable.begin(), sTable.end(), Freq::descend);      // Using sort() with descend as parameter
}
//--------------------------------------------------------
void Solver::printFreq(ostream& out) {
    for(int h = 0; h < sTable.size(); h++) {
        sTable[h].print(out);
    }
}
//--------------------------------------------------------
void Solver::solve() {
    //Display menu to choose between Replace, Erase, ShowFreqs, and GiveUp
    for(int x = 0; x < codeText.size(); x++) {
        cout << codeText[x];
    }
    for (;;) {
    int ginteger;
    cout << "\nType 1 to REPLACE, Type 2 to ERASE, Type 3 to ShowFreqs, Type 4 to GIVEUP." << endl;
    cin >> ginteger;
    switch(ginteger) {
        case 1:
            char character1, character2;
            cout << "Enter 2 characters, no spaces:";
            cin >> character1 >> character2;
            Replacer(character1, character2);
            break;
        case 2:
            char character;
            cout << "Enter a character:";
            cin >> character;
            Eraser(character);
            break;
        case 3:
            printFreq(cout);
            break;
        case 4:
            cout << "You are a terrible scrub\n";
            printSol();
            exit(0);
        }
        
        bool whatever = true;   // Checks for underscores, prints out underscores and stuff
        for(int k = 0; k < plainText.size(); k++) {
            cout << plainText[k];
        }
        for(int m = 0; m < plainText.size(); m++) {
            if (plainText[m] == '_'){
                whatever = false;
            }
        }
        if (whatever == true) {
            break;
        }
        
        
    }
}
//--------------------------------------------------------
void Solver::Eraser(char random) {
    for(int u = 0; u < plainText.size(); u++){
        if(codeText[u] == random){
           codeText[u] = '_';
        }
    }
}
//--------------------------------------------------------
void Solver:: printSol() {
    for(int k = 0; k < codeText.size(); k++) {
        cout << codeText[k];
    }
}
//--------------------------------------------------------
void Solver::Replacer(char ce, char cp) {   // ce-encrypted message, cp-plaintext message
    for(int y = 0; y < plainText.size(); y++){
        if(codeText[y] == ce) {
            plainText[y] = cp;
        }
    }
}
//--------------------------------------------------------
