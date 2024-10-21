#include "Header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>



string global_login;


string ProgrammChecks::checkSize(string s) {//проверка на размер строки
    const int SIZE = 8;
    do {
        cin >> s;
        if(s.size() > SIZE) {
            cout << "Введенная строка превышает заданный размер. Пожалуйста, повторите ввод. " << std::endl;
        }
        else {
            return s;
            break;
        }
    } while(s.size() > SIZE);

    return " ";

}

string ProgrammChecks::checkString(string s)//проверка на ввод строки
{
    while(1) {
        getline(cin, s);

        int x = 0;
        for(int i = 0; i < s.size(); i++) {
            if(isdigit(s[i])) {
                x = 1;
                break;
            }
        }
        if(x == 0) return s;
        cout << "Некорректный ввод. Повторите попытку." << endl;

    }
}

bool ProgrammChecks::isNumberNumeric()//проверка на ввод числа
{
    if(cin.get() == '\n')
        return true;
    else {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        return false;
    }
}

bool ProgrammChecks::isNumberRangeCorrect(int number, int left_range, int right_range)//проверка на выход за границы
{
    if((number >= left_range) && (number <= right_range)) return true;
    else return false;
}

int ProgrammChecks::inputNumber(int left_range, int right_range) {//ввод числа

    int number;
    while(true) {
        cin >> number;
        if(isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range)) {
            return number;
        }
        else {
            cout << "Некорректный ввод. Повторите попытку ";
        }

    }
}



void Menu::start_menu() {//начальное меню
    int choice;
    EnterSystem sObj;
    ProgrammChecks checker;
    do {
        cout << "-------Введите--------\n 1. Для регистрации \n 2. Для авторизации\n 3. Для выхода \n";
        cout << "Ваш выбор?" << endl;
        choice = checker.inputNumber(1, 3);
        switch(choice) {
        case 1:
        {
            sObj.registration();
            sleep(3);
            break;
        }
        case 2:
        {
            sObj.authorization();
            break;
        }
        case 3:
        {
            cout << "Совершен выход из программы.";
            break;

        }
        }
    } while(choice != 3);
}



void WorkWithFiles::writeUsersToFile(const vector<User>& users) {//запись пользователей в файл
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/users.txt";
    ofstream outputFile(filename);
    EnterSystem sObj;

    if(!outputFile.is_open()) {
        std::cerr << "Ошибка открытия файла " << filename << "для записи" << std::endl;
        return;
    }

    for(const User& user : users) {
        outputFile << user.getLogin() << " " << sObj.encrypt(user.getPassword()) << " " << user.getIsAdmin() << std::endl;
    }

    outputFile.close();
}

vector<User> WorkWithFiles::readUsersFromFile() {//достать пользователей из файла в вектор
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/users.txt";
    vector<User> users;
    EnterSystem sObj;
    ifstream inFile(fileName);
    if(inFile.is_open()) {
        string login, password, isAdminStr;
        while(inFile >> login >> password >> isAdminStr) {
            bool isAdmin = (isAdminStr == "1");
            User newUser;
            newUser.setLogin(login);
            newUser.setPassword(sObj.decrypt(password));
            newUser.setIsAdmin(isAdmin);
            users.push_back(newUser);
        }
        inFile.close();
    }
    else {
        cerr << "Невозможно открыть файл " << fileName << std::endl;
    }
    return users;
}

void WorkWithFiles::writeAccountsToFile(const vector<User>& accounts) {//Запись аккаунтов в файл
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/accounts.txt";
    ofstream outputFile(filename);
    EnterSystem sObj;
    if(!outputFile.is_open()) {
        cerr << "Ошибка открытия файла" << filename << " для записи" << std::endl;
        return;
    }

    for(const User& account : accounts) {
        outputFile << account.getLogin() << " " << sObj.encrypt(account.getPassword()) << " " << account.getIsAdmin() << endl;
    }
    outputFile.close();
}

vector<User> WorkWithFiles::readAccountsFromFile() {//достать пользователей из файла в вектор
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/accounts.txt";
    vector<User> accounts;
    EnterSystem sObj;
    ifstream inFile(fileName);
    if(inFile.is_open()) {
        string login, password, isAdminStr;
        while(inFile >> login >> password >> isAdminStr) {
            bool isAdmin = (isAdminStr == "1");
            User newUser;
            newUser.setLogin(login);
            newUser.setPassword(sObj.decrypt(password));
            newUser.setIsAdmin(isAdmin);
            accounts.push_back(newUser);
        }
        inFile.close();
    }
    else {
        cerr << "Невозможно открыть файл " << fileName << std::endl;
    }
    return accounts;
}


void WorkWithFiles::writeFurnitureToFile(const vector<Furniture>& furnitureProducts) {//запись товаров в файл
    string filename = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/jewelry.txt";
    ofstream outputFile(filename);
    if(!outputFile.is_open()) {
        cerr << "Ошибка открытия файла " << filename << " для записи." << std::endl;
        return;
    }
    for(const Furniture& furniture : furnitureProducts) {
        outputFile << furniture.getProductType() << " " << furniture.getMaterial() << " " << furniture.getColor() << " " << furniture.getPrice() << " "
            << furniture.getAmount() << " " << furniture.getBrand() << " " <<   furniture.getTotalSoldQuantity() << std::endl;

    }
    outputFile.close();
}



vector<Furniture> WorkWithFiles::readFurnitureFromFile() {//достать записи из файла в вектор
    string fileName = "/Users/ulanatozik/Материалы по учебе (БГУИР)/1 курс/Курсач 1 курс /tessst/tessst/jewelry.txt";
    vector<Furniture> furnitureProducts;
    ifstream inputFile(fileName);
    if(inputFile.is_open()) {
        int price, amount, totalSoldQuantity;
        string productType, material, brand, color;
        while(inputFile >> productType >> material >> brand >> color
            >> price >> amount >> totalSoldQuantity) {
            Furniture f;
            f.setProductType(productType);
            f.setMaterial(material);
            f.setPrice(price);
            f.setColor(color);
            f.setAmount(amount);
            f.setBrand(brand);
            f.setTotalSoldQuantity(totalSoldQuantity);
            furnitureProducts.push_back(f);
        }
        inputFile.close();
    }
    else {
        cerr << "Ошибка открытия файла " << fileName << endl;
        return furnitureProducts;
    }
    return furnitureProducts;
}


void Tables::printAccountsTable(const vector<User>& accounts) {//вывод таблицы аккаунтов
    // вывод заголовка таблицы
    EnterSystem sObj;
    cout << "\n|=============================================================================================|"
        << "\n|                                 ЗАЯВКИ НА РЕГИСТРАЦИЮ                                       |"
        << "\n|=============================================================================================|"
        << "\n|    №    |            Логин             |            Пароль            |         Админ       |"
        << "\n|=============================================================================================|\n";
    int i = 0;
    //вывод строк таблицы
    for(const auto& account : accounts) {
        cout << "|" << setw(9) << ++i << "|" << setw(16) << account.getLogin() << setw(16) << " | "
            << setw(16) << sObj.encrypt(account.getPassword()) << setw(15) << " | "
            << setw(13) << (account.getIsAdmin() ? "Да" : "Нет") << setw(10) << "|" << endl;
        cout << "|=============================================================================================|" << endl;
    }
}

void Tables::printUsersTable(const vector<User>& users) {//Вывод таблицы аккаунтов
    EnterSystem sObj;
    // Вывод заголовка таблицы

    cout << "\n|=============================================================================================|"
        << "\n|                                 АККАУНТЫ ПОЛЬЗОВАТЕЛЕЙ                                      |"
        << "\n|=============================================================================================|"
        << "\n|    №    |            Логин             |            Пароль            |        Админ        |"
        << "\n|=============================================================================================|\n";
    int i = 0;
    // Вывод строк таблицы
    for(const auto& user : users) {
        cout << "|" << setw(9) << ++i << "|" << setw(18) << user.getLogin() << setw(14) << " | "
            << setw(16) << sObj.encrypt(user.getPassword()) << setw(15) << " | "
            << setw(13) << (user.getIsAdmin() ? "Да" : "Нет") << setw(10) << "|" << endl;
        cout << "|=============================================================================================|" << endl;
    }

}

void Tables::printFurnitureTable(const vector<Furniture>& furnitureProducts) {//вывод таблицы товаров
    headTable();
    int i = 0;

    for(const auto& furniture : furnitureProducts) {
        cout << "| "
            << setw(3) << ++i << " | "
            << setw(20) << furniture.getProductType() << setw(8) << " | "
            << setw(13) << furniture.getMaterial() << setw(15) << " | "
        << setw(10) << furniture.getColor() << setw(5) << " | "
            << setw(6) << furniture.getPrice() << setw(8) << " | "
            << setw(8) << furniture.getAmount() << setw(10) << " | "
            << setw(10) << furniture.getBrand() << setw(3) << " |"
            << endl
            << "|=======================================================================================================================|" << endl;
    }

    i++;
}


void Tables::headTable() {//шапка таблицы товаров

    cout << "\n|=======================================================================================================================|"
        << "\n|                                        МЕБЕЛЬНЫЕ ТОВАРЫ                                                              |"
        << "\n|=======================================================================================================================|"
        << "\n|  №  |      Вид изделия     |     Материал     |   Цвет    |    Цена     |   Количество    |    Бренд    |"
        << "\n|=======================================================================================================================|\n";
}

void WorkWithAccounts::approve() {//одобрение заявки

    Tables tablesObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    vector<User> accounts = filesObj.readAccountsFromFile();
    vector<User> users = filesObj.readUsersFromFile();
    tablesObj.printAccountsTable(accounts);
    int number_for_add, choice;
    cout << "---Выберите---" << endl;
    cout << "1 - Для одобрения заявки" << endl;
    cout << "2 - Для выхода" << endl;
    choice = checker.inputNumber(1, 2);
    switch(choice) {
    case 1:
    {
        cout << "Выберите номер заявки, которую хотите одобрить" << endl;
        number_for_add = checker.inputNumber(1, accounts.size());
        User user;
        user.setLogin(accounts.at(number_for_add - 1).getLogin());
        user.setPassword(accounts.at(number_for_add - 1).getPassword());
        user.setIsAdmin(accounts.at(number_for_add - 1).getIsAdmin());
        users.push_back(user);
        filesObj.writeUsersToFile(users);
        cout << "Вы одобрили заявку" << endl;
        accounts.erase(accounts.begin() + number_for_add - 1);
        filesObj.writeAccountsToFile(accounts);
        break;
    }
    case 2:
    {
        return;
    }
    }
}


void WorkWithProducts::addFurniture() { // добавить товар
    auto checker = std::make_unique<ProgrammChecks>();
    auto filesObj = std::make_unique<WorkWithFiles>();
    auto tableObj = std::make_unique<Tables>();

    std::cout << "Добавить товар:" << std::endl;

    std::string productType;
    int typeIndex = 0;

 
    std::cout << "Введите вид товара (1. Стол, 2. Стул, 3. Кровать, 4. Шкаф, 5. Полка):" << std::endl;
    typeIndex = checker->inputNumber(1, 5);

    while(typeIndex < 1 || typeIndex > 5) {
        std::cout << "Выбранный вид товара недопустим. Пожалуйста, выберите снова:" << std::endl;
        typeIndex = checker->inputNumber(1, 5);
    }

    switch(typeIndex) {
        case 1: productType = "Стол"; break;
        case 2: productType = "Стул"; break;
        case 3: productType = "Кровать"; break;
        case 4: productType = "Шкаф"; break;
        case 5: productType = "Полка"; break;
    }

    
    std::string material = checker->checkString("Введите материал товара (например, Дерево, Металл, Пластик):");
    std::string brand = checker->checkString("Введите бренд товара:");
    std::string color = checker->checkString("Введите цвет товара:");
    int price = checker->inputNumber(1, 10000);
    int amount = checker->inputNumber(0, 100);

 
    Furniture furniture;
    furniture.setProductType(productType);
    furniture.setMaterial(material);
    furniture.setBrand(brand);
    furniture.setColor(color);
    furniture.setPrice(price);
    furniture.setAmount(amount);

 
    auto furnitureProducts = filesObj->readFurnitureFromFile();
    furnitureProducts.push_back(furniture);
    filesObj->writeFurnitureToFile(furnitureProducts);
    tableObj->printFurnitureTable(furnitureProducts);
}



void WorkWithAccounts::addaccount() {//Добавить аккаунт
    WorkWithFiles filesObj;
    EnterSystem sObj;
    ProgrammChecks checker;


    cout << "Добавить аккаунт" << endl;
    string login, password;
    bool isAdmin;
    vector<User> users = filesObj.readUsersFromFile();
    while(true) {
        cout << "Введите логин" << endl;
        cin >> login;
        cout << "Введите пароль" << endl;
        cin >> password;
        cout << "Является ли админом (1/0)" << endl;
        isAdmin = checker.inputNumber(0, 1);
        if(sObj.checkLoginAndPasswordRegist(users, login, password, isAdmin)) {
            break;
        }
    }
    User user;
    user.setLogin(login);
    user.setPassword(password);
    user.setIsAdmin(isAdmin);


    users.push_back(user);
    filesObj.writeUsersToFile(users);

}

void WorkWithProducts::deleteFurniture() {//удалить товар
    WorkWithFiles filesObj;
    Tables tableObj;
    ProgrammChecks checker;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    tableObj.printFurnitureTable(furnitureProducts);
    int number_for_delete;
    cout << "----Удаление товара---" << endl << endl;
    cout << "Введите номер товара, который хотите удалить" << endl;
    number_for_delete = checker.inputNumber(1, furnitureProducts.size());
    int yes_or_no;
    cout << "1. Да" << endl
        << "2. Нет" << endl
        << "Ваш выбор?" << endl;
    yes_or_no = checker.inputNumber(1, 2);
    if(yes_or_no == 1) {
        furnitureProducts.erase(furnitureProducts.begin() + number_for_delete - 1);
        cout << "----Товар успешно удален----" << endl;
        filesObj.writeFurnitureToFile(furnitureProducts);
    }
    else cout << "Вы отменили удаление" << endl;
}

void WorkWithAccounts::deleteAccount() {//удалить аккаунт
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    vector<User> users = filesObj.readUsersFromFile();
    tableObj.printUsersTable(users);
    int number_for_delete;
    cout << "----Удаление учетной записи----" << endl << endl;;
    cout << "Введите номер аккаунта, который хотите удалить" << endl;
    number_for_delete = checker.inputNumber(1, users.size());
    cout << "Вы уверены, что хотите удалить аккаунт?" << endl;
    int yes_or_no;
    cout << "1. Да" << endl
        << "2. Нет" << endl
        << "Ваш выбор:" << endl;
    yes_or_no = checker.inputNumber(1, 2);
    if(yes_or_no == 1) {
        if(users.at(number_for_delete - 1).getIsAdmin() == 1) {
            cout << "Удалить свой аккаунт невозможно" << endl;
        }
        else {
            users.erase(users.begin() + number_for_delete - 1);
            cout << "----Аккаунт успешно удален----" << endl;
            filesObj.writeUsersToFile(users);
        }
    }
    else {
        cout << "Вы отменили удаление" << endl;
    }
}


void WorkWithProducts::editFurniture() { // редактирование товара
    int choice;
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;

    do {
        vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
        tableObj.printFurnitureTable(furnitureProducts);
        
        int newPrice, newAmount, number_for_edit;
        cout << "Введите номер товара, который хотите изменить: " << endl;
        number_for_edit = checker.inputNumber(1, furnitureProducts.size());

        cout << "--------------Введите--------------" << endl;
        cout << "1 - Чтобы изменить вид товара" << endl;
        cout << "2 - Чтобы изменить количество товара в наличии" << endl;
        cout << "3 - Чтобы изменить бренд товара" << endl;
        cout << "4 - Чтобы изменить цену товара" << endl;
        cout << "5 - Чтобы выйти из режима редактирования" << endl;
        cout << "Ваш выбор: ";

        choice = checker.inputNumber(1, 5);
        switch(choice) {
        case 1: {
            cout << "--Изменение вида товара--" << endl;
            cout << setw(5) << "Новый вид товара (1. Стол, 2. Стул, 3. Кровать, 4. Шкаф, 5. Полка):" << endl;
            int typeIndex = checker.inputNumber(1, 5);
            string newProductType;
            switch(typeIndex) {
            case 1:
                newProductType = "Стол";
                break;
            case 2:
                newProductType = "Стул";
                break;
            case 3:
                newProductType = "Кровать";
                break;
            case 4:
                newProductType = "Шкаф";
                break;
            case 5:
                newProductType = "Полка";
                break;
            }
            furnitureProducts.at(number_for_edit - 1).setProductType(newProductType);
            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Вид товара изменен--" << endl;
            break;
        }
        case 2: {
            cout << "--Изменение количества товара в наличии--" << endl;
            cout << setw(5) << "Новое количество: " << endl;
            newAmount = checker.inputNumber(0, 100);
            furnitureProducts.at(number_for_edit - 1).setAmount(newAmount);
            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Количество товара изменено--" << endl;
            break;
        }
        case 3: {
            cout << "--Изменение бренда--" << endl;
            cout << setw(5) << "Новый бренд:" << endl;
            string newBrand = checker.checkString(newBrand);
            furnitureProducts.at(number_for_edit - 1).setBrand(newBrand);
            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Бренд изменен--" << endl;
            break;
        }
        case 4: {
            cout << "--Изменение цены товара--" << endl;
            newPrice = checker.inputNumber(1, 10000);
            furnitureProducts.at(number_for_edit - 1).setPrice(newPrice);
            filesObj.writeFurnitureToFile(furnitureProducts);
            cout << "--Цена товара изменена--" << endl;
            break;
        }
        case 5: {
            break;
        }
        }

    } while(choice != 5);
}


void WorkWithAccounts::editAccount() {//редактирование аккаунтов
    int choice;
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    do {
        vector<User> users = filesObj.readUsersFromFile();
        tableObj.printUsersTable(users);
        int i = 0;
        int number_for_edit;
        string newLogin;
        cout << "Введите номер аккаунта, который хотите изменить: " << endl;
        number_for_edit = checker.inputNumber(1, users.size());
        cout << "--------------Введите--------------" << endl;
        cout << "1 - Чтобы изменить логин" << endl;
        cout << "2 - Чтобы изменить роль пользователя" << endl;
        cout << "3 - Чтобы редактировать все данные аккаунта" << endl;
        cout << "4 - Чтобы выйти из режима редактирования" << endl;
        cout << "Ваш выбор: ";
        choice = checker.inputNumber(1, 4);
        switch(choice) {
        case 1:
        {
            cout << "--Новый логин--" << endl;
            cin >> newLogin;

            bool isLoginTaken = false;
            for(int i = 0; i < users.size(); ++i) {
                if(users.at(i).getLogin() == newLogin) {
                    isLoginTaken = true;
                    break;
                }
            }

            if(!isLoginTaken) {
                users.at(number_for_edit - 1).setLogin(newLogin);
                filesObj.writeUsersToFile(users);
                cout << "--Логин успешно заменен--" << endl;
            }
            else {
                cout << "Данный логин занят, повторите попытку" << endl;
                break;
            }
            break;
        }
        case 2:
        {
            cout << "--Новая роль пользователя--" << endl;
            cout << "1 - роль администратора" << endl;
            cout << "0 - роль пользователя" << endl;
            users.at(number_for_edit - 1).setIsAdmin(checker.inputNumber(0, 1));
            filesObj.writeUsersToFile(users);
            cout << "---Успешно отредактировано---" << endl;
            break;
        }
        case 3:
        {
            cout << "--Новый логин--" << endl;
            cin >> newLogin;
            while(i < users.size()) {
                if(users.at(i).getLogin() == newLogin) {
                    cout << "Данный логин занят, повторите попытку" << endl;
                    cin >> newLogin;
                    i = 0;
                }
                else i++;
            }
            users.at(number_for_edit - 1).setLogin(newLogin);
            cout << "--Новая роль пользователя--" << endl;
            cout << "1 - роль администратора" << endl;
            cout << "0 - роль пользователя" << endl;
            users.at(number_for_edit - 1).setIsAdmin(checker.inputNumber(0, 1));
            filesObj.writeUsersToFile(users);
            cout << "---Успешно отредактировано---" << endl;
            break;
        }
        case 4:
        {
            break;
        }
        }

    } while(choice != 4);
}



void Menu::menuWorkWithUser() { //меню для работы с учетными записями
    int choice;
    Tables tableObj;
    WorkWithAccounts accountObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    do {
        cout << "--------------Введите--------------" << endl;
        vector<User> users = filesObj.readUsersFromFile();
        cout << "1 - для вывода учетных записей" << endl;
        cout << "2 - для добавления учетных записей" << endl;
        cout << "3 - для редактирования учетных записей" << endl;
        cout << "4 - для удаления учетных записей" << endl;
        cout << "5 - для одобрения заявок на регистрацию" << endl;
        cout << "6 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 6);
        switch(choice) {
        case 1:
        {
            tableObj.printUsersTable(users);
            break;
        }
        case 2:
        {
            accountObj.addaccount();
            break;
        }
        case 3:
        {
            accountObj.editAccount();
            break;
        }
        case 4:
        {
            accountObj.deleteAccount();
            break;
        }
        case 5:
        {
            accountObj.approve();
        }
        case 6:
        {
            break;
        }
        default:cout << "Введено некорректное значение. Попробуйте снова.";
        }
    } while(choice != 6);
}

void WorkWithProducts::orderProduct() {
    Tables tableObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
 
    cout << "--Заказ товара--" << endl;
    cout << "Введите номер товара, который хотите заказать: " << endl;
    tableObj.printFurnitureTable(furnitureProducts);

    int choice = checker.inputNumber(1, furnitureProducts.size()) - 1;
    if(furnitureProducts[choice].getAmount() > 0) {
        int originalPrice = furnitureProducts[choice].getPrice();
        if(furnitureProducts[choice].getAmount() < 5 && furnitureProducts[choice].getAmount()>3)
        {
            
            int discountedPrice = originalPrice * 0.9;
            cout << "На товар действует скидка 10%. Цена товара изменена с " << originalPrice << " на " << discountedPrice << endl;
            furnitureProducts[choice].setPrice(discountedPrice);
        }
        
        if(furnitureProducts[choice].getAmount() <= 3)
        {
            
            int discountedPrice = originalPrice * 0.8;
            cout << "На товар действует скидка 20%. Цена товара изменена с " << originalPrice << " на " << discountedPrice << endl;
            furnitureProducts[choice].setPrice(discountedPrice);
        }
        
        cout << "Вы уверены, что хотите заказать этот товар?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор: ";

        int choice2;
        cin >> choice2;
        switch(choice2) {
        case 1:
        {
            cout << "Ожидайте ответа администратора для подтверждения вашего заказа." << endl;
            sleep(3);
            cout << "Заказ товара подтвержден." << endl;
            furnitureProducts[choice].setAmount(furnitureProducts[choice].getAmount() - 1);
            /*furnitureProducts[choice].sell();*/
            furnitureProducts[choice].setPrice(originalPrice);

            filesObj.writeFurnitureToFile(furnitureProducts); // Сохранение изменений
            break;
        }
        case 2:
        {
            cout << "Вы отменили заказ товара." << endl;
            return;
        }
        default:
        {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        }
    }
    else if(furnitureProducts[choice].getAmount() == 0) {
        cout << "Выбранного вами товара на данный момент нет в наличии. Желаете оформить предзаказ?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        cout << "Ваш выбор?" << endl;
        int choice3;
        cin >> choice3;
        switch(choice3) {
        case 1:
        {
            cout << "Ожидайте ответа администратора для подтверждения вашего предзаказа." << endl;
            sleep(3);
            cout << "Предзаказ оформлен. Вы получите свой товар, как только он появится в наличии." << endl;
            filesObj.writeFurnitureToFile(furnitureProducts);
            break;
        }
        case 2:
        {
            cout << "Вы отменили предзаказ товара." << endl;
            return;
        }
        default: cout << "Неверный выбор. Попробуйте снова";
        }
    }

}


void WorkWithProducts::printTotalRevenue() { //подсчёт общего числа выручки и количества проданных товаров

    int totalSoldQuantity = 0;
    int totalRevenue = 0;

    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();

    for(const auto& furniture : furnitureProducts) {
        if(furniture.getTotalSoldQuantity() > 0) {
            totalSoldQuantity += furniture.getTotalSoldQuantity();
            totalRevenue += furniture.getPrice() * furniture.getTotalSoldQuantity();
        }
    }

    cout << "Общее количество проданных товаров: " << totalSoldQuantity << endl;
    cout << "Общая выручка от всех проданных товаров: " << totalRevenue << endl;

}


void SearchProducts::searchProductType() { // поиск по виду изделия
    Tables tableObj;
    ProgrammChecks checker;
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    string productType;
    int count = 0;
    int a = 0;

    cout << "--Поиск по виду товара--" << endl;
    cout << "Введите вид товара: ";
    productType = checker.checkString(productType);
    
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if(furnitureProducts.at(i).getProductType().find(productType) != string::npos) { // ищем по виду товара
            count++;
            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(17) << furnitureProducts.at(i).getColor() << setw(7) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }
}


 

void SearchProducts::searchMaterial() { // поиск по материалу
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    Tables tableObj;
    ProgrammChecks checker;
    string material;
    int count = 0;
    int a = 0;

    cout << "--Поиск по материалу--" << endl;
    cout << "Введите материал: ";
    material = checker.checkString(material);
    
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if (furnitureProducts.at(i).getMaterial().find(material) != string::npos) { // ищем по материалу
            count++;
            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(17) << furnitureProducts.at(i).getColor() << setw(7) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }
}

void SearchProducts::searchPrice() {//поиск по цене
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    Tables tableObj;
    ProgrammChecks checker;
    int price;
    int count = 0;
    int a = 0;
    cout << "--Поиск по цене--" << endl;
    cout << "Введите цену: ";
    price = checker.inputNumber(0, 10000);
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if(furnitureProducts.at(i).getPrice() == price) {
            count++;

            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(13) << furnitureProducts.at(i).getColor() << setw(15) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }


}
void SearchProducts::searchAmount() {//поиск по количеству
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    ProgrammChecks checker;
    int amount;
    Tables tableObj;
    int count = 0;
    int a = 0;
    cout << "--Поиск по количеству товара в наличии--" << endl;
    cout << "Введите количество товара в наличии: ";
    amount = checker.inputNumber(0, 100);
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if(furnitureProducts.at(i).getAmount() == amount) {
            count++;

            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(13) << furnitureProducts.at(i).getColor() << setw(15) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }


}

void SearchProducts::searchColor() { // поиск по цвету
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    string color;
    Tables tableObj;
    ProgrammChecks checker;
    int count = 0;
    int a = 0;

    cout << "--Поиск по цвету--" << endl;
    cout << "Введите цвет: ";
    color = checker.checkString(color);
    
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if(furnitureProducts.at(i).getColor().find(color) != string::npos) { // ищем по цвету
            count++;

            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(17) << furnitureProducts.at(i).getColor() << setw(7) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }
}


void SearchProducts::searchBrand() {// поиск по коллекции
    WorkWithFiles filesObj;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    string brand;
    Tables tableObj;
    ProgrammChecks checker;
    int count = 0;
    int a = 0;
    cout << "--Поиск по названию бренда--" << endl;
    cout << "Введите название бренда: ";
    brand = checker.checkString(brand);
    tableObj.headTable();
    for(int i = 0; i < furnitureProducts.size(); i++) {
        if(furnitureProducts.at(i).getBrand().find(brand) == 0) {
            count++;
            cout << "| "
                << setw(3) << ++a << " | "
                << setw(20) << furnitureProducts.at(i).getProductType() << setw(8) << " | "
                << setw(17) << furnitureProducts.at(i).getMaterial() << setw(7) << " | "
                << setw(13) << furnitureProducts.at(i).getColor() << setw(15) << " | "
                << setw(6) << furnitureProducts.at(i).getPrice() << setw(8) << " | "
                << setw(8) << furnitureProducts.at(i).getAmount() << setw(10) << " | "
                << setw(10) << furnitureProducts.at(i).getBrand() << setw(3) << " |"
                << endl
                << "|=======================================================================================================================|" << endl;
        }
    }
    if(count == 0) {
        cout << "Ничего не найдено" << endl;
    }

}

void Menu::menuSearch() {//поиск товаров
    SearchProducts searchObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    cout << "--------------Введите--------------" << endl;
    int choice;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    cout << "1 - для поиска по цене" << endl;
    cout << "2 - для поиска по количеству" << endl;
    cout << "3 - для поиска по виду изделия" << endl;
    cout << "4 - для поиска по цвету" << endl;
    cout << "5 - для поиска по виду материала" << endl;
    cout << "6 - для поиска по названию бренда" << endl;
    cout << "Ваш выбор:  ";
    choice = checker.inputNumber(1, 6);
    switch(choice) {
    case 1:
    {
        searchObj.searchPrice();//поиск по цене
        break;

    }
    case 2:
    {
        searchObj.searchAmount(); //поиск по количеству
        break;
    }
    case 3:
    {
        searchObj.searchProductType(); //поиск по виду изделия
        break;
    }
    case 4:
    {
        searchObj.searchColor(); //поиск по цвету
        break;
    }
    case 5:
    {
        searchObj.searchMaterial(); //поиск по виду материала
        break;
    }
    case 6:
    {
        searchObj.searchBrand(); //поиск по бренду
        break;
    }
    }
}

void Menu::menuSort() {//меню сортировки
    Tables tableObj;
    SortProducts sortObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
    vector<Furniture> furniture_temp;
    furniture_temp = furnitureProducts;
    int choice;
    cout << "---—Введите---" << endl;
    cout << "1 - для сортировки по цене " << endl;
    cout << "2 - для сортировки по количеству товара в наличии " << endl;
    cout << "3 - для сортировки по пробе металла" << endl;
    cout << "4 - для сортировки по виду металла" << endl;
    cout << "Ваш выбор:" << endl;
    choice = checker.inputNumber(1, 4);
    switch(choice) {
    case 1:
    {
        sort(furniture_temp.begin(), furniture_temp.end(), bind(&SortProducts::isSortByPrice, &sortObj, placeholders::_1, placeholders::_2));
        break;
    }
    case 2:
    {
        sort(furniture_temp.begin(), furniture_temp.end(), bind(&SortProducts::isSortByAmount, &sortObj, placeholders::_1, placeholders::_2));
        break;
    }
    case 3:
    {
        sort(furniture_temp.begin(), furniture_temp.end(), bind(&SortProducts::isSortByMaterial, &sortObj, placeholders::_1, placeholders::_2));
        break;
    }
    case 4:
    {
        sort(furniture_temp.begin(), furniture_temp.end(), bind(&SortProducts::isSortByColor, &sortObj, placeholders::_1, placeholders::_2));
        break;
    }
    }
    cout << "--Успешно отсортировано--" << endl;
    tableObj.printFurnitureTable(furniture_temp);

}

bool SortProducts::isSortByPrice(Furniture price_a, Furniture price_b) {//сортировка по цене
    return price_a.getPrice() < price_b.getPrice();
}

bool SortProducts::isSortByAmount(Furniture amount_a, Furniture amount_b) {//сортировка по количеству в наличии
    return amount_a.getAmount() < amount_b.getAmount();
}

bool SortProducts::isSortByMaterial(Furniture material_a, Furniture material_b) {//сортировка по пробе металла
    return material_a.getMaterial() < material_b.getMaterial();
}

bool SortProducts::isSortByColor(Furniture color_a, Furniture color_b) {//сортировка по виду металла
    return color_a.getColor() < color_b.getColor();
}


void Menu::menuWorkWithFurniture() {//меню для работы с товарами
    Tables tableObj;
    WorkWithProducts prObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    while(1) {
        cout << "--------------Введите--------------" << endl;
        int choice;
        vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
        cout << "1 - для отображения перечня мебельных товаров" << endl;
        cout << "2 - для добавления товара" << endl;
        cout << "3 - для редактирования товара" << endl;
        cout << "4 - для удаления товара" << endl;
        cout << "5 - для поиска товара" << endl;
        cout << "6 - для сортировки товаров" << endl;
        cout << "7 - для вывода выручки и количества проданных товаров" << endl;
        cout << "8 - для вывода прибыли за все проданные товары и услуги" << endl;
        cout << "9 - для работы с услугами" << endl;
        cout << "10 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 8);
        switch(choice) {
        case 1:
        {
            tableObj.printFurnitureTable(furnitureProducts);
            break;
        }
        case 2:
        {
            prObj.addFurniture();
            break;
        }
        case 3:
        {
            prObj.editFurniture();
            break;
        }
        case 4:
        {
            prObj.deleteFurniture();
            break;
        }
        case 5:
        {
            menuSearch();
            break;
        }
        case 6:
        {
            menuSort();
            break;
        }
        case 7:
        {
            prObj.printTotalRevenue();
            break;
        }
        case 8:
        {
            
            break;
        }
        case 9:
        {
               
            break;
        }
                
        case 10:
        {
            return;
        }

        }
    }
}

void Menu::menuUser() {//меню пользователя
    Tables tableObj;
    WorkWithProducts prObj;
    WorkWithFiles filesObj;
    ProgrammChecks checker;
    int choice;
    cout<<"\n";
    cout << "----УВЕДОМЛЕНИЯ ДЛЯ ПОЛЬЗОВАТЕЛЯ----" << endl;
    prObj.salesNotification();
    do {

        vector<Furniture> furnitureProducts = filesObj.readFurnitureFromFile();
        cout<<"\n";
        cout << "--------------МЕНЮ ПОЛЬЗОВАТЕЛЯ--------------" << endl;
        cout << "Введите:" << endl;
        cout << "1 - для просмотра данных" << endl;
        cout << "2 - для поиска данных" << endl;
        cout << "3 - для сортировки данных" << endl;
        cout << "4 - для оформления заказа или предзаказа товара" << endl;
        cout << "4 - для оформления заказа услуги" << endl;
        cout << "5 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 5);
        switch(choice) {
        case 1:
        {
            tableObj.printFurnitureTable(furnitureProducts);
            break;
        }
        case 2:
        {
            menuSearch();
            break;
        }
        case 3:
        {
            menuSort();
            break;
        }
        case 4:
        {
            prObj.orderProduct();
            break;
        }
        case 5:
        {
            break;
        }
        }
    } while(choice != 5);
}

void WorkWithProducts::productNotification() {
    WorkWithFiles fileObj;
    vector<Furniture> furnitureProducts = fileObj.readFurnitureFromFile();
    int flag = 0;
    int i = 0;
    for(const auto& furniture : furnitureProducts) {
        if(furniture.getAmount() < 2) {
            cout << "На складе заканчиваются единицы товара " << ++i << " (Вид изделия: " << furniture.getProductType() << ", " << "вид материала: " << furniture.getMaterial() << ", бренд изделия: " << furniture.getBrand() << ", цвет: " << furniture.getColor()  << ", количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        }
        i++;
    }
    if(flag == 0) {
        cout << "Нет новых уведомлений." << endl;
    }

}

void WorkWithProducts::salesNotification() {
    WorkWithFiles fileObj;
    vector<Furniture> furnitureProducts = fileObj.readFurnitureFromFile();
    int flag = 0;
    int i = 0;

    for(const auto& furniture : furnitureProducts) {
        if(furniture.getAmount() < 5 && furniture.getAmount() > 2 && furniture.getAmount() > 0) {
            cout << "Действует скидка 10% на товар " << ++i << " (Вид изделия: " << furniture.getProductType()
                 << ", Материал: " << furniture.getMaterial()
                 << ", Цвет: " << furniture.getColor()
                 << ", Бренд: " << furniture.getBrand()
                 << ", Количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        } else if(furniture.getAmount() < 3 && furniture.getAmount() > 0) {
            cout << "Действует скидка 20% на товар " << ++i << " (Вид изделия: " << furniture.getProductType()
                 << ", Материал: " << furniture.getMaterial()
                 << ", Цвет: " << furniture.getColor()
                 << ", Бренд: " << furniture.getBrand()
                 << ", Количество товара в наличии: " << furniture.getAmount() << ")" << endl;
            flag = 1;
        }
    }

    if(flag == 0) {
        cout << "Нет новых уведомлений." << endl;
    }
}


void Menu::menuAdministrator() {//меню администратора
    ProgrammChecks checker;
    int choice;

    WorkWithProducts obj1;
    WorkWithFiles fileObj;
    vector<Furniture> furnitureProducts = fileObj.readFurnitureFromFile();
    cout << "\n";
    cout << "----УВЕДОМЛЕНИЯ ДЛЯ АДМИНИСТРАТОРА----" << endl;
    obj1.productNotification();
    cout<<"\n";

    do {
        cout << "\n";
        cout << "--------------МЕНЮ АДМИНИСТРАТОРА--------------" << endl;
        cout << "Введите:" << endl;
        cout << "1 - для работы с учетными записями" << endl;
        cout << "2 - для работы с данными" << endl;
        cout << "3 - для выхода" << endl;
        cout << "Ваш выбор:  ";
        choice = checker.inputNumber(1, 3);
        switch(choice) {
        case 1:
        {
            menuWorkWithUser();
            break;
        }
        case 2:
        {
            menuWorkWithFurniture();
            break;
        }
        case 3:
        {
            break;
        }
        }
    } while(choice != 3);
}

bool EnterSystem::checkLoginAndPassword(std::vector<User>& users, std::string login, std::string password) {//проверка логина и пароля
    Menu menuObj;
    WorkWithFiles fileObj;
    int found = 0;
    for(auto& user : users) {
        if(user.getLogin() == login && user.getPassword() == password) {
            found = 1;
            std::cout << "Добро пожаловать, " << user.getLogin() << "!" << std::endl;
            if(user.getIsAdmin() == 0) {
                menuObj.menuUser();
            }
            if(user.getIsAdmin() == 1) {
                menuObj.menuAdministrator();
            }
            return true;
        }
    }

    vector<User>accounts = fileObj.readAccountsFromFile();
    for(auto& account : accounts) {
        if(account.getLogin() == login && account.getPassword() == password) {
            found = 1;
            cout << "Ваша заявка на регистрацию еще не подтверждена." << endl;
            return false;
        }
    }

    if(found == 0) {
        cout << "Неверный логин или пароль. Попробуйте снова" << endl;
    }

    return false;
}

bool EnterSystem::checkLoginAndPasswordRegist(std::vector<User>& users, std::string login, std::string password, bool isAdmin) {//проверка на существование пользователя
    for(auto& user : users) {
        if(user.getLogin() == login && user.getPassword() == password && user.getIsAdmin() == isAdmin) {
            std::cout << "Такой пользователь уже существует" << endl;
            return false;
        }
        if(user.getLogin() == login) {
            std::cout << "Пользователь с таким логином уже существует" << endl;
            return false;
        }
    }
    return true;
}



void EnterSystem::authorization() {//авторизация
    WorkWithFiles filesObj;
    cout << "Авторизация:" << std::endl;
    string login, password;
    
    bool isLoggedIn = false;

    while(!isLoggedIn) {
        cout << "Введите логин:  ";
        cin >> login;

        cout << "Введите пароль: ";
        cin >> password;

        vector<User> users = filesObj.readUsersFromFile();
        if(checkLoginAndPassword(users, login, password)) {
            isLoggedIn = true;
        }
         
    }
}


void EnterSystem::registration() {//регистрация
    ProgrammChecks checker;
    WorkWithFiles filesObj;
    cout << "Регистрация:" << endl;
    string login, password;
    bool isAdmin;
    vector<User> accounts = filesObj.readAccountsFromFile();
    vector<User> users = filesObj.readUsersFromFile();
    while(true) {
        cout << "Введите логин" << endl;
        login = checker.checkSize(login);
        cout << "Введите пароль" << endl;
        password = checker.checkSize(password);
        cout << "Является ли админом (1/0)" << endl;
        isAdmin = checker.inputNumber(0, 1);
        if(checkLoginAndPasswordRegist(accounts, login, password, isAdmin) && checkLoginAndPasswordRegist(users, login, password, isAdmin)) {
            break;
        }
    }
    User account;
    account.setLogin(login);
    account.setPassword(password);
    account.setIsAdmin(isAdmin);
    accounts.push_back(account);
    filesObj.writeAccountsToFile(accounts);
    cout << "Ваша заявка на регистрацию отправлена, ожидайте ответ администратора" << endl;
}


string EnterSystem::encrypt(string input) {//шифровка
    string output(input.size(), ' ');
    for(int i = 0; i < input.size(); i++) {
        output[i] = (char)((int)input[i] + 3) % 256;
    }
    return output;
}

string EnterSystem::decrypt(string input) {//дешифровка
    string output(input.size(), ' ');
    for(int i = 0; i < input.size(); i++) {
        output[i] = (char)((int)input[i] - 3) % 256;
    }
    return output;
}
