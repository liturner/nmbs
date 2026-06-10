#include <nmbs/nmbs.h>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 3)
    {
        std::cerr << "This program requires two arguments, some other number was supplied. Please submit a Policy Identifier and a Classification." << std::endl;
        return 1;
    }

    std::cout << nmbs::confidentiality_label(argv[1], argv[2]);

    return 0;
}