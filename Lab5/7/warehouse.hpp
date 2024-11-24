#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

// Базовый класс Product
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

// Производный класс PerishableProduct
class PerishableProduct : public Product {
public:
    PerishableProduct(const std::string& name, unsigned int id, double weight, double price, unsigned int shelf_life, const std::string& expirationDate);

    double calculateStorageFee() const override;
    void displayInfo() const override;

    bool isExpiringSoon(int days) const; // Проверяет, истекает ли срок годности

private:
    std::string expirationDate;
};

// Производный класс ElectronicProduct
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

// Класс Warehouse
class Warehouse {
private:
    std::vector<Product*> inventory; // Вектор указателей на продукты

public:
    ~Warehouse(); // Деструктор для очистки памяти

    void addProduct(Product* product); // Добавляет продукт в склад
    void deleteProductById(unsigned int id); // Удаляет продукт по ID
    void displayInventory() const; // Выводит все товары в складе
    double calculateEntireCost() const; // Считает общую стоимость хранения
    std::vector<Product*> getProductsByCategory(const std::string& category) const; // Возвращает товары по категории

    Warehouse& operator+=(Product* product); // Перегрузка оператора +=
    Warehouse& operator-=(unsigned int id); // Перегрузка оператора -=
    Product* operator[](unsigned int id) const; // Перегрузка оператора [] для поиска по ID

    friend std::ostream& operator<<(std::ostream& os, const Warehouse& warehouse); // Перегрузка оператора вывода
};

#endif // WAREHOUSE_HPP
