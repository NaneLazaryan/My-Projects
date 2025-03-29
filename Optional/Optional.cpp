#include "Optional.h"

Optional<std::string> findUser(int id) {
    if (id == 1) {
        return Optional<std::string>("Elina");
    }
    return nullopt; 
}

int main() {
    Optional<std::string> opt1 = findUser(9);
    std::cout << "Value: " << opt1.value_or("(no value)") << std::endl;

    double a = 6;
    Optional<double> opt2(a);
    if (opt2.has_value()) {
        std::cout << "Value: " << *opt2 << std::endl;
    }

    // Example of copy assignment
    Optional<double> opt3;
    opt3 = opt2;
    if (opt3.has_value()) {
        std::cout << "\nCopy Assigned Value: " << opt3.value() << std::endl;
    }
  
    // Example of move assignment
    Optional<double> opt4;
    opt4 = std::move(opt3);
    std::cout << "Move Assigned Value: " << opt4.value_or(-1) << std::endl;

    // Example of move constructor
    Optional <double> opt6 = std::move(opt2);
    if (opt6.has_value()) {
        std::cout << "\nMove Constructed Value: " << opt6.value() << std::endl;
    }

    // Example of copy constructor
    Optional <double> opt7 = opt6;
    if (opt7.has_value()) {
        std::cout << "Copy Constructed Value: " << opt7.value() << std::endl;
    }

    struct NonTrivial {
        NonTrivial() { std::cout << "\nNonTrivial Created\n"; }
        ~NonTrivial() { std::cout << "Destroying NonTrivial\n"; }
    };

    NonTrivial ob;
    Optional<NonTrivial> opt5(ob);

    return 0;
}
