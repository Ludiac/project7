#include <iostream>
#include "INTARRAY.h"

int main() {
    IntArray ARRAY(10);
    IntArray arr;

    try {
        IntArray a(-1);
    }
    catch (const char* e) {
        std::cout << e << '\n';
    }

    try {
        std::cout << ARRAY[15];
    }
    catch (const char* e) {
        std::cout << e << '\n';
    }

    try {
        for (int i{ 0 }; i<10; ++i)
            ARRAY[i] = i+1;

        ARRAY.resize(8);

        ARRAY.insertBefore(20, 5);

        ARRAY.remove(3);

        ARRAY.insertAtEnd(30);
    }
    catch (const char* e) {
        std::cout << e << '\n';
    }

    std::cout << "ARRAY length: " << ARRAY.getLength()
              << ", ARRAY size: " << ARRAY.getSize() << '\n';
    std::cout << "arr length: " << arr.getLength()
              << ", arr size: " << arr.getSize() << '\n';

    arr = std::move(ARRAY);

    std::cout << "\nmoved ARRAY to arr:\n";

    std::cout << "  ARRAY length: " << ARRAY.getLength()
              << ", ARRAY size: " << ARRAY.getSize() << '\n';
    std::cout << "  arr length: " << arr.getLength()
              << ", arr size: " << arr.getSize() << '\n';

    ARRAY = arr;

    std::cout << "\ncopied arr to ARRAY:\n";

    std::cout << "  ARRAY length: " << ARRAY.getLength()
              << ", ARRAY size: " << ARRAY.getSize() << '\n';
    std::cout << "  arr length: " << arr.getLength()
              << ", arr size: " << arr.getSize() << '\n';

    return 0;
}
