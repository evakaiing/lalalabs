#include "warehouse.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>


Product::Product(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life)
    : name(name), id(id), weight(weight), price(price), shelf_life(shelf_life) {}

Product::Product(const Product& other)
    : name(other.name), id(other.id), weight(other.weight), price(other.price), shelf_life(other.shelf_life) {}

Product& Product::operator=(const Product& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    id = other.id;
    weight = other.weight;
    price = other.price;
    shelf_life = other.shelf_life;
    
    return *this;
}

Product::~Product() = default;

double Product::calculateStorageFee() const {
    return weight * 0.1;
}

void Product::displayInfo() const {
    std::cout << "name: " << name << ", iD: " << id << ", weight: " << weight
              << ", price: " << price << ", shelf Life: " << shelf_life << '\n';
}

unsigned int Product::getId() const {
    return id;
}

const std::string& Product::getName() const {
    return name;
}

PerishableProduct::PerishableProduct(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, const std::string& expirationDate)
    : Product(name, id, weight, price, shelf_life), expirationDate(expirationDate) {}

double PerishableProduct::calculateStorageFee() const {
    if (PerishableProduct::isExpiringSoon(3)) {
        return Product::calculateStorageFee() * 1.5;
    }
    return Product::calculateStorageFee();
}

void PerishableProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "expiration date: " << expirationDate << "\n";
}


bool PerishableProduct::isExpiringSoon(int days) const {
    struct tm expiration_tm = {};
    struct tm current_tm = {};

    const char* format = "%Y-%m-%d"; 
    if (strptime(expirationDate.c_str(), format, &expiration_tm) == nullptr) {
        throw std::runtime_error("invalid date format for product");
    }

    time_t now = time(nullptr);
    localtime_r(&now, &current_tm);

    time_t expiration_time = mktime(&expiration_tm);
    time_t current_time = mktime(&current_tm);

    if (expiration_time == -1 || current_time == -1) {
        throw std::runtime_error("failed to process date for product");
    }

    double diff_in_seconds = difftime(expiration_time, current_time);
    int diff_in_days = static_cast<int>(diff_in_seconds / (60 * 60 * 24));

    if (diff_in_days > days) {
        return true;
    } else {
        return false;
    }
}


ElectronicProduct::ElectronicProduct(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, unsigned int warrantyPeriod, double powerRating)
    : Product(name, id, weight, price, shelf_life), warrantyPeriod(warrantyPeriod), powerRating(powerRating) {}

void ElectronicProduct::displayInfo() const {
    Product::displayInfo();
    std::cout << "warranty period: " << warrantyPeriod << " months, power rating: " << powerRating << "\n";
}


BuildingMaterial::BuildingMaterial(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, bool flammability)
    : Product(name, id, weight, price, shelf_life), flammability(flammability) {}

double BuildingMaterial::calculateStorageFee() const {
    return Product::calculateStorageFee() * (flammability ? 2.0 : 1.0);
}

void BuildingMaterial::displayInfo() const {
    Product::displayInfo();
    std::cout << "flammability: " << (flammability ? "1" : "0") << "\n";
}

Warehouse::~Warehouse() {
    for (auto product : inventory) {
        delete product;
    }
}

void Warehouse::addProduct(Product* product) {
    inventory.push_back(product);
}

void Warehouse::deleteProductById(unsigned int id) {
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i]->getId() == id) {
            delete inventory[i]; 
            inventory.erase(inventory.begin() + i); 
            return; 
        }
    }
}


void Warehouse::displayInventory() const {
    std::cout << "inventory:\n";

    std::vector<Product*> perishableProducts;
    std::vector<Product*> electronicProducts;
    std::vector<Product*> buildingMaterials;

    for (const auto& product : inventory) {
        if (dynamic_cast<PerishableProduct*>(product)) {
            perishableProducts.push_back(product);
        } else if (dynamic_cast<ElectronicProduct*>(product)) {
            electronicProducts.push_back(product);
        } else if (dynamic_cast<BuildingMaterial*>(product)) {
            buildingMaterials.push_back(product);
        }
    }

    if (!perishableProducts.empty()) {
        std::cout << "perishable products:\n";
        for (const auto& product : perishableProducts) {
            product->displayInfo();
        }
    }
    if (!electronicProducts.empty()) {
        std::cout << "electronic products:\n";
        for (const auto& product : electronicProducts) {
            product->displayInfo();
        }
    }
    if (!buildingMaterials.empty()) {
        std::cout << "building materials:\n";
        for (const auto& product : buildingMaterials) {
            product->displayInfo();
        }
    }
}


double Warehouse::calculateEntireCost() const {
    double totalCost = 0.0;
    for (const auto& product : inventory) {
        totalCost += product->calculateStorageFee();
    }
    return totalCost;
}

std::vector<Product*> Warehouse::getProductsByCategory(const std::string& category) const {
    std::vector<Product*> products;
    for (const auto& product : inventory) {
        if ((category == "Perishable" && dynamic_cast<PerishableProduct*>(product)) ||
            (category == "Electronic" && dynamic_cast<ElectronicProduct*>(product)) ||
            (category == "BuildingMaterial" && dynamic_cast<BuildingMaterial*>(product))) {
            products.push_back(product);
        }
    }
    return products;
}


Warehouse& Warehouse::operator+=(Product* product) {
    addProduct(product);
    return *this;
}

Warehouse& Warehouse::operator-=(unsigned int id) {
    deleteProductById(id);
    return *this;
}

Product* Warehouse::operator[](unsigned int id) const {
    for (const auto& product : inventory) {
        if (product->getId() == id) {
            return product;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse) {
    os << "warehouse:\n";
    for (const auto& product : warehouse.inventory) {
        product->displayInfo();
    }
    return os;
}
