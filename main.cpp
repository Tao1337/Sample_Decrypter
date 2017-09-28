//
//  main.cpp
//  Datastr_Prog3
//
//  Created by Austin Tao on 3/3/17.
//  Copyright © 2017 Austin Tao. All rights reserved.
//

#include "tools.hpp"
#include "Freq.hpp"


int main(int argc, const char * argv[]) {
    //Freq test = Freq('a', 1.75666); for testing
    //cout << test;
    Solver test = Solver("InputTest.txt", "FreqTable.txt");
    //test.printFreq(cout);     Prints out frequencies in 2 columns
    test.solve();
}
