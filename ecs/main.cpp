#include "SparseArray.hpp"
#include <iostream>
#include <string>

void printSparseArray(const SparseArray<std::string>& array) {
    std::cout << "SparseArray contents:\n";
    for (std::size_t i = 0; i < array.size(); ++i) {
        if (array[i].has_value()) {
            std::cout << "Index " << i << ": " << array[i].value() << "\n";
        } else {
            std::cout << "Index " << i << ": nullopt\n";
        }
    }
    std::cout << "--------------------\n";
}

int main() {
    try {
        // Test default constructor
        SparseArray<std::string> sparseArray;

        // Test insert_at
        sparseArray.insert_at(0, "Start");
        sparseArray.insert_at(2, "Hello");
        sparseArray.insert_at(5, "World");
        sparseArray.insert_at(10, "SparseArray Test");
        printSparseArray(sparseArray);

        // Test emplace_at
        sparseArray.emplace_at(7, "Emplaced Value");
        printSparseArray(sparseArray);

        // Test erase
        sparseArray.erase(2);
        printSparseArray(sparseArray);

        // Test copy constructor
        SparseArray<std::string> copiedArray(sparseArray);
        std::cout << "After copying sparseArray to copiedArray:\n";
        printSparseArray(copiedArray);

        // Test move constructor
        std::cout << "CACA BOUDIN" << std::endl;
        SparseArray<std::string> movedArray(std::move(sparseArray));
        std::cout << "After moving sparseArray to movedArray:\n";
        printSparseArray(movedArray);
        std::cout << "Original sparseArray after move:\n";
        printSparseArray(sparseArray);

        // Test copy assignment operator
        SparseArray<std::string> anotherArray;
        std::cout << "CACA" << std::endl;
        anotherArray = copiedArray;
        std::cout << "After copying copiedArray to anotherArray:\n";
        printSparseArray(anotherArray);

        // Test move assignment operator
        SparseArray<std::string> yetAnotherArray;
        yetAnotherArray = std::move(anotherArray);
        std::cout << "After moving anotherArray to yetAnotherArray:\n";
        printSparseArray(yetAnotherArray);
        std::cout << "Original anotherArray after move:\n";
        printSparseArray(anotherArray);

        // Test iterators
        std::cout << "Iterating over elements in yetAnotherArray using begin() and end():\n";
        for (auto it = yetAnotherArray.begin(); it != yetAnotherArray.end(); ++it) {
            if (it->has_value()) {
                std::cout << it->value() << "\n";
            }
        }

        // Test const iterators
        std::cout << "Iterating over elements in yetAnotherArray using cbegin() and cend():\n";
        for (auto it = yetAnotherArray.cbegin(); it != yetAnotherArray.cend(); ++it) {
            if (it->has_value()) {
                std::cout << it->value() << "\n";
            }
        }

        // Test size
        std::cout << "Size of yetAnotherArray: " << yetAnotherArray.size() << "\n";

        // Test get_index
        auto index = yetAnotherArray.get_index(std::optional<std::string>("World"));
        if (index != static_cast<std::size_t>(-1)) {
            std::cout << "Index of 'World': " << index << "\n";
        } else {
            std::cout << "'World' not found in yetAnotherArray.\n";
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
