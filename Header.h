//
#pragma once
//
//  Header.h
//  mycoursework
//
//  Created by Ульяна Тозик on 13.04.24.
//

#ifndef Header_h
#define Header_h
#define service_hpp

#include <stdio.h>
#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <termios.h>
#include <functional>
#include <locale.h>
#include <curses.h>

using namespace std;

class User {
private:
    string login;
    string password;
    bool isAdmin;
public:
    User() {}

    User(const std::string& login, const std::string& password, bool isAdmin)
        : login(login), password(password), isAdmin(isAdmin) {
    }

    const std::string& getLogin() const {
        return login;
    }

    const std::string& getPassword() const {
        return password;
    }

    bool getIsAdmin() const {
        return isAdmin;
    }

    void setLogin(const string& newLogin) {
        login = newLogin;
    }

    void setPassword(const string& newPassword) {
        password = newPassword;
    }

    void setIsAdmin(bool newIsAdmin) {
        isAdmin = newIsAdmin;
    }
};


 

class Furniture {
private:
    string productType;
    string material;
    string brand;
    string color;
    int orderNumber;
    double price;
    int amount;
    int totalSoldQuantity;

public:
    
    Furniture(){}
    
    Furniture(const string& type, const string& mat, const string& br, const string& col, int order, double pr, int amt)
    : productType(type), material(mat), brand(br), color(col), orderNumber(order), price(pr), amount(amt), totalSoldQuantity(0) {}

 
    string getProductType() const { return productType; }
    string getMaterial() const { return material; }
    string getBrand() const { return brand; }
    string getColor() const {return color;}
    double getPrice() const { return price; }
    int getAmount() const { return amount; }
    int getTotalSoldQuantity() const { return totalSoldQuantity; }
    
    void setProductType(const string& newProductType) {
        productType = newProductType;
    }

    void setMaterial(const string& newMaterial) {
        material = newMaterial;
    }

    void setPrice(int newPrice) {
        price = newPrice;
    }

    void setOrderNumber(int newOrderNumber) {
        orderNumber = newOrderNumber;
    }

    void setAmount(int newAmount) {
        amount = newAmount;
    }
    
    void setColor(const string& newColor)
    {
        color=newColor;
    }


    void setBrand(const string& newBrand) {
        brand = newBrand;
    }

    void setTotalSoldQuantity(int totalSoldQuantity1) {
        totalSoldQuantity = totalSoldQuantity1;
    }


  
    void sell(int quantity) {
        if (quantity <= amount) {
            amount -= quantity;
            totalSoldQuantity += quantity;
        }
    }
};



class ProgrammChecks {//класс для хранения функций проверок
public:
    bool isNumberNumeric();//проверка на ввод числа
    bool isNumberRangeCorrect(int number, int left_range, int right_range);//проверка на ввод промежутка
    string checkSize(string s);//проверка на размер строки
    string checkString(string s);//проверка на ввод строки
    int inputNumber(int left_range, int right_range);//проверка на ввод числа в промежутке
};

class Menu {
public:
    void start_menu();//стартовое меню
    void menuWorkWithUser();//меню работы с аккаунтами
    void menuWorkWithFurniture();//меню работы с товарами
    void menuSort();//меню сортировок
    void menuSearch();//меню поиска
    void menuUser();//меню пользователя
    void menuAdministrator();//меню администратора
};

class WorkWithFiles {//класс для работы с файлами
public:
    void writeUsersToFile(const vector<User>& users);//запись информации о пользователях в файл
    vector<User> readUsersFromFile();//чтение информации о пользователях из файла
    void writeFurnitureToFile(const vector<Furniture>& furnitureProducts);//запись информации о ювелирных изделий в файл
    vector<Furniture> readFurnitureFromFile();//чтение информации о ювелирных изделиях из файла
    void writeAccountsToFile(const vector<User>& accounts);//запись аккаунтов в файл
    vector<User> readAccountsFromFile();//чтение аккаунтов из файла
};

class Tables {//класс для хранения функций, которые выводят таблицы
public:
    void headTable();//шапка таблицы товаров
    void printAccountsTable(const std::vector<User>& accounts); //вывод таблицы аккаунтов
    void printUsersTable(const std::vector<User>& users);//вывод таблицы пользователей
    void printFurnitureTable(const std::vector<Furniture>& furnitureProducts);//отображение перечня ювелирных изделий
};

class WorkWithProducts : public Furniture {
public:
    void addFurniture();//добавление товара
    void deleteFurniture();//удаление товара
    void editFurniture();//редактирование товара
    void printTotalRevenue(); //подсчёт общего числа выручки и количества проданных товаров
    void printProfit();//подсчёт прибыли от продаж
    void orderProduct();//индивидуальное задание (оформление заказа или предзаказа)
    void productNotification();//уведомления для администратора
    void salesNotification();//уведомления для пользователя
};

class WorkWithAccounts : public User {
public:
    void addaccount(); //добавление аккаунта
    void deleteAccount();//удаление аккаунта
    void editAccount();//редактирование аккаунта
    void approve(); //одобрение заявки на регистрацию
};

class EnterSystem {
public:
    bool checkLoginAndPassword(vector<User>& users, string login, string password);//проверка на ввод логина и пароля
    bool checkLoginAndPasswordRegist(vector<User>& users, string login, string password, bool isAdmin);//проверка на существование аккаунта
    void authorization();//авторизация
    void registration();//регистрация
    string encrypt(string input);//зашифровка
    string decrypt(string input);//расшифровка
};

class SortProducts {
public:
    bool isSortByPrice(Furniture price_a, Furniture price_b);//сортировка по цене
    bool isSortByAmount(Furniture amount_a, Furniture amounth_b);//сортировка по количеству товара в наличии
    bool isSortByBrand(Furniture brand_a, Furniture brand_b);//сортировка по брендк
    bool isSortByMaterial(Furniture material_a, Furniture material_b);//сортировка по материалу товара
    bool isSortByColor(Furniture color_a, Furniture color_b);
};

class SearchProducts {
public:
    void searchPrice();//поиск по цене
    void searchAmount(); //поиск по количеству товара в наличии
    void searchProductType(); //поиск по виду изделия
    void searchMaterial(); //поиск по виду материала
    void searchBrand();//поиск по названию бренда
    void searchColor();//поиск по цвету
};


 
#endif /* Header_h */
