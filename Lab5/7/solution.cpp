#include <iostream>
#include <vector>

#include "warehouse.hpp"

int main() {
    Warehouse warehouse;

    Product* milk = new PerishableProduct("Milk", 101, 1.0, 2.5, 7, "2024-12-10");
    milk->displayInfo();
    std::cout << "storage fee: " << milk->calculateStorageFee() << " per day\n\n";
    Product* milk2 = new PerishableProduct("milk", 101, 1.0, 2.5, 7, "2024-11-25");
    std::cout << "storage fee: " << milk2->calculateStorageFee() << " per day\n\n";

    Product* laptop = new ElectronicProduct("Laptop", 201, 2.5, 1500.0, 365, 24, 65.0);
    std::cout << "electronic product:\n";
    laptop->displayInfo();
    std::cout << "storage fee: " << laptop->calculateStorageFee() << " per day\n\n";

    Product* bricks = new BuildingMaterial("Bricks", 301, 100.0, 500.0, 180, true);
    std::cout << "building material:\n";
    bricks->displayInfo();
    std::cout << "storage fee: " << bricks->calculateStorageFee() << " per day\n\n";
    Product* bricks2 = new BuildingMaterial("bricks", 301, 100.0, 500.0, 180, false);
    std::cout << "storage fee: " << bricks2->calculateStorageFee() << " per day\n\n";

    warehouse += milk;
    warehouse += laptop;
    warehouse += bricks;

    warehouse.displayInventory();
    std::cout << '\n';
    std::cout << warehouse;
    std::cout << '\n';
    Product* found = warehouse[101];
    if (found) {
        std::cout << "founded product: ";
        found->displayInfo();
    } else {
        std::cout << "doesn't exist.\n";
    }

    warehouse -= 101;

    std::cout << "after removing\n\n";
    std::cout << warehouse;
    std::cout << '\n';
    std::vector<Product*> founded = warehouse.getProductsByCategory("Electronic");
    for (const auto& elem : founded) {
        elem->displayInfo();
    }
    std::cout << warehouse.calculateEntireCost() << '\n';
}
