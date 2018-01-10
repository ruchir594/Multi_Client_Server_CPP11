#include <iostream>

int main() {
    const int i=42;
    const int *const p = &i;
    std::cout << *p <<std::endl;
    *p = 45;
    std::cout << *p <<std::endl;
    std::cout << i <<std::endl;
    return 0;
}
