#include <iostream>
#include <vector>
using namespace std;

// Компонент - базовый класс для всех компонентов, включая дочерние компоненты (композиты)
class Component {
public:
    virtual void showDetails() const = 0;
};

// Чек - конечный компонент, не имеющий дочерних компонентов
class Receipt : public Component {
    float amount;
    string date;
public:
    Receipt(float amount, string date) : amount(amount), date(date) {}
    void showDetails() const override {
        cout << "Receipt Details - Items amount: " << amount << "\nDate: " << date << "\n";
    }
};

// Молоток - элемент заказа
class Hammer : public Component {
    string name;
public:
    Hammer(string name) : name(name) {}
    void showDetails() const override {
        cout << "Hammer - Name: " << name << "\n";
    }
};

// Класс Телефон - элемент заказа
class Phone : public Component {
    string name;
public:
    Phone(string name) : name(name) {}
    void showDetails() const override {
        cout << "Phone - Name: " << name << "\n";
    }
};

// Класс Зарядка - элемент заказа
class Charger : public Component {
    string description;
public:
    Charger(string description) : description(description) {}
    void showDetails() const override {
        cout << "Charger - Description: " << description << "\n";
    }
};

// Композит - компонент, содержащий другие компоненты (как листья, так и другие композиты-узлы)
class Box : public Component {
    vector<Component*> components;
public:
    void add(Component* component) {
        components.push_back(component);
    }

    void remove(Component* component) {
        components.erase(std::remove_if(components.begin(), components.end(),
            [component](Component* c) { return c == component; }), components.end());
    }

    void showDetails() const override {
        cout << "Box Components:\n";
        for (auto component : components) {
            component->showDetails();
        }
        cout << "\n";
    }
};

int main() {
    setlocale(0, "");

    // создаём молоток, кладём в первую коробку
    auto hammer = new Hammer("Молоток для мяса с топориком Tescoma 638728 PRESIDENT");
    auto firstSmallBox = new Box();
    firstSmallBox->add(hammer);

    // создаём телефон с зарядкой, кладём во вторую коробку
    auto phone = new Phone("Смартфон Samsung Galaxy S23 Ultra S918B 12GB/256GB Green");
    auto charger = new Charger("Сетевое зарядное устройство Samsung 25W Travel Adapter (w/o cable) Black (EP-TA800NBEGRU)");
    auto secondSmallBox = new Box();
    secondSmallBox->add(phone);
    secondSmallBox->add(charger);

    // в третью коробку кладём первые две коробки поменьше + чек
    auto receipt = new Receipt(3, "2023-03-24");
    auto bigBox = new Box();
    bigBox->add(firstSmallBox);
    bigBox->add(secondSmallBox);
    bigBox->add(receipt);

    // показываем общее содержимое большой коробки
    bigBox->showDetails();

    // чистим память
    delete bigBox;
    delete receipt;
    delete secondSmallBox;
    delete charger;
    delete phone;
    delete firstSmallBox;
    delete hammer;
}

/*
Код реализует паттерн "Компоновщик" (Composite pattern),
который позволяет обрабатывать объекты как единое целое
или как отдельные части в древовидной структуре.

В данном случае, базовый класс Component определяет
единый интерфейс для всех компонентов, а классы-наследники
реализуют этот интерфейс. Листовые компоненты (Hammer,
Phone, Charger, Receipt) представляют отдельные объекты,
а составные компоненты (Box) могут содержать в себе как
листовые, так и другие составные компоненты.

Класс Box имеет методы add() и remove(), которые
позволяют добавлять и удалять компоненты внутри себя.
Также класс Box имеет метод showDetails(), который
выводит информацию о всех компонентах внутри коробки.

В функции main() создаются объекты разных классов
(Hammer, Phone, Charger, Receipt), которые помещаются
в соответствующие коробки (Box), а затем большая коробка
(Box) содержит две маленькие коробки (Box) и
чек (Receipt).
*/

// https://refactoring.guru/ru/design-patterns/composite

/*
Компоновщик — это структурный паттерн проектирования,
который позволяет сгруппировать множество объектов
в древовидную структуру, а затем работать с ней так,
как будто это единичный объект.
*/