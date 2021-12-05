#include <iostream>
#include "binary.h"
#include "task.h"

int main()
{
    std::cout << "Enter the binary function: ";
    bits_t b{binary::getFromCmd()};

    std::cout << "\nTruth table: \n";
    task::printTruthTable(b);
    std::cout << '\n';
    
    bits_t dvoista{ task::getDvoista(b) };

    std::cout << "Dvoista: ";
    binary::print(task::getDvoista(b), 8);

    std::cout << "\n\n";

    task::printDDNF(b);

    std::cout << '\n';

    task::printDKNF(b);

    std::cout << '\n';

    std::cout << task::getJigalkinsPolynom(b);

    std::cout << '\n';

    std::cout << "Is self-dvoista: " << std::boolalpha << (dvoista == b) << '\n';
    std::cout << "Contains the 0 constant: " << ((b & 1) == 0) << '\n';
    std::cout << "Contains the 1 constant: " << ((b & (1 << 7)) != 0) << '\n';
    std::cout << "Is monotonous: " << task::isMonotonous(b) << '\n';
    std::cout << "Is linear: " << task::isLinear(b) << '\n';

    getchar();
}