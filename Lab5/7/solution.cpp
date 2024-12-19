#include <iostream>
#include <vector>

#include "warehouse.hpp"

int main() {
    Warehouse warehouse;

    auto milk = std::make_unique<PerishableProduct>("Milk", 1, 1.0, 2.50, 10, "2024-01-15");
    warehouse += std::move(milk);

    auto tv = std::make_unique<ElectronicProduct>("TV", 2, 8.0, 799.99, 730, 24, 150);
    warehouse += std::move(tv);

    auto brick = std::make_unique<BuildingMaterial>("Brick", 3, 3.0, 0.50, 3650, true);
    warehouse += std::move(brick);

    std::cout << "initial inventory status:" << std::endl;
    warehouse.displayInventory();

    std::cout << "total storage cost: " << warehouse.calculateEntireCost() << std::endl;

    warehouse -= 2;
    std::cout << "inventory after removing the TV:" << std::endl;
    warehouse.displayInventory();

    try {
        auto& product = warehouse[1];
        std::cout << "accessing milk by ID (1):" << std::endl;
        product->displayInfo();
    } catch (const std::out_of_range& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    std::cout << warehouse << std::endl;


    std::vector<std::unique_ptr<Product>> products;
    products.push_back(std::make_unique<PerishableProduct>("Milk", 1, 1.0, 2.50, 10, "2024-01-15"));
    products.push_back(std::make_unique<ElectronicProduct>("TV", 2, 8.0, 799.99, 730, 24, 150));
    products.push_back(std::make_unique<BuildingMaterial>("Brick", 3, 3.0, 0.50, 3650, true));

    for (const auto& product : products) {
        product->displayInfo();  
        std::cout << "storage fee: " << product->calculateStorageFee() << "\n\n"; 
    }
}
