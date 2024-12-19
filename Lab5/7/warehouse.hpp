#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <memory>


class Product {
public:
    Product(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life);
    Product(const Product& other); 
    Product& operator=(const Product& other); 
    virtual ~Product(); 

    virtual double calculateStorageFee() const; 
    virtual void displayInfo() const; 

    unsigned int getId() const; 
    const std::string& getName() const;

protected:
    std::string name;
    unsigned int id;
    double weight;
    double price;
    unsigned int shelf_life;
};

class PerishableProduct : public Product {
public:
    PerishableProduct(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, const std::string& expirationDate);

    double calculateStorageFee() const override;
    void displayInfo() const override;

    bool isExpiringSoon(int days) const; 

private:
    std::string expirationDate;
};


class ElectronicProduct : public Product {
public:
    ElectronicProduct(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, unsigned int warrantyPeriod, double powerRating);

    void displayInfo() const override;

private:
    unsigned int warrantyPeriod;
    double powerRating;
};

class BuildingMaterial : public Product {
public:
    BuildingMaterial(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, bool flammability);

    double calculateStorageFee() const override;
    void displayInfo() const override;

private:
    bool flammability;
};


class Warehouse final {
private:
    std::vector<std::unique_ptr<Product>> inventory;

public:
    void addProduct(std::unique_ptr<Product> product); 
    void deleteProductById(unsigned int id); 
    void displayInventory() const; 
    double calculateEntireCost() const; 
    std::unique_ptr<Product> getProductsByCategory(const std::string& category) const;

    Warehouse& operator+=(std::unique_ptr<Product> product);
    Warehouse& operator-=(unsigned int id);
    std::unique_ptr<Product>& operator[](unsigned int id); 

    friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse);
};

#endif // WAREHOUSE_HPP
