//
//  Freq.hpp
//  Datastr_Prog3
//
//  Created by Austin Tao on 4/20/17.
//  Copyright © 2017 Austin Tao. All rights reserved.
//

#ifndef Freq_hpp
#define Freq_hpp

#include "tools.hpp"

class Freq {
public:
    Freq() = default;
    Freq(char a, double b);
    void print(ostream& out);   // Print function
    static bool descend (const Freq& f1, const Freq& f2) { return f1.percent > f2.percent; }
    
private:
    char letter;
    double percent;
};

inline ostream& operator<< (ostream& out, Freq fr){ fr.print(out); return out; }
//--------------------------------------------------------
class Solver {      // 2 input streams, 2 vectors, 2 simple arrays
public:
    Solver(string aFile, string bFile);
    void tally();   // tally function counts letters
    void printFreq(ostream& out);
    void solve();
private:
    vector<char> codeText;   //codeText - encoded message
    vector<char> plainText;  //plainText - solution user builds
    Freq coded[26];
    Freq english[26];
    void scale(int* tally, int nnletters);
    vector<Freq> sTable;    // Sorted table, local vector use for scale() function
    void Eraser(char random);
    void printSol();
    void Replacer(char ce, char cp);
    
};

#endif /* Freq_hpp */
