#include <iostream>
#include "Registry.hpp"
#include "SparseArray.hpp"

void printSparseArray(const SparseArray<int>& array) {
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
    Registry registry;

    auto &array = registry.register_component<int>();
    //auto &array2 = registry.register_component<std::string>();
    auto &array3 = registry.register_component<char>();

    array.insert_at(0, 42);
    array.insert_at(2, 84);
    //array2.insert_at(0, "Hello");
    //array2.insert_at(1, "World");
    array3.insert_at(0, 84);
    array3.insert_at(1, 84);

    try {
        SparseArray<std::string> &retrievedArray = registry.get_components<std::string>();
        //printSparseArray(retrievedArray);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
