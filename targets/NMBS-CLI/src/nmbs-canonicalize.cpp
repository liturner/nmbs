//
// Created by luke on 6/6/26.
//
#include <nmbs/nmbs.h>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 2)
    {
        std::cerr << "This program requires one argument, some other number was supplied. Please submit a single string" << std::endl;
        return 1;
    }

    std::cout << nmbs::canonicalize(argv[1]);

    return 0;
}