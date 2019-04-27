//
//  main.cpp
//  Test
//
//  Created by Diogo Guimarães on 26/04/2019.
//  Copyright © 2019 Diogo Guimarães. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

// #1 Esta é a forma mais "old school" de converter é C puro.
void option1() {
    int dummyInt = 123;
    char outputString [100];

    // Injetam o inteiro na string aqui.
    sprintf(outputString, "%d", dummyInt);
    // Imprimem a string com o inteiro convertido aqui.
    printf("outputString = %s\n\n", outputString);

    return;
}

// #2 Aqui usamos stringstreams que é uma lib standard de C++.
void option2() {
    int anotherDummyInt = 123;
    std::string anotherOutputString;
    std::stringstream stream;

    stream << anotherDummyInt;
    anotherOutputString = stream.str();

    // Imprimem a string com o inteiro convertido aqui.
    std::cout << "outputString = " << anotherOutputString << "\n\n";
}

// #3 Aqui usamos to_string() que só existe a partir de C++ 11.
void option3() {
    int yetAnotherDummyInt = 123;
    std::string yetAnotherOutputString = std::to_string(yetAnotherDummyInt);
    std::cout << "outputString = " << yetAnotherOutputString << "\n\n";
}

int main(int argc, const char * argv[]) {
    option1();
    option2();
    option3();

    return 0;
}
