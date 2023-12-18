#include <iostream>
#include <vector>
#include <string>

// 1. Створення продуктів

// Базовий клас для продуктів
class Product {
public:
    virtual void display() const = 0;
};

// Класи для конкретних продуктів: кава, чай, печиво
class Coffee : public Product {
public:
    void display() const override {
        std::cout << "Coffee" << std::endl;
    }
};

class Tea : public Product {
public:
    void display() const override {
        std::cout << "Tea" << std::endl;
    }
};

class Cookie : public Product {
public:
    void display() const override {
        std::cout << "Cookie" << std::endl;
    }
};

// Фабрика продуктів
class ProductFactory {
public:
    virtual Product* createProduct() const = 0;
};

// Фабрики для конкретних продуктів
class CoffeeFactory : public ProductFactory {
public:
    Product* createProduct() const override {
        return new Coffee();
    }
};

class TeaFactory : public ProductFactory {
public:
    Product* createProduct() const override {
        return new Tea();
    }
};

class CookieFactory : public ProductFactory {
public:
    Product* createProduct() const override {
        return new Cookie();
    }
};

// 2. Клієнти

// Клас для представлення клієнтів
class Client {
public:
    virtual void placeOrder() = 0;
    virtual void viewOrderHistory() const = 0;
};

// Клас, що реалізує клієнта
class ConcreteClient : public Client {
public:
    void placeOrder() override {
        // Логіка розміщення замовлення
        std::cout << "Order placed" << std::endl;
    }

    void viewOrderHistory() const override {
        // Логіка перегляду історії замовлень
        std::cout << "Order history viewed" << std::endl;
    }
};

// Посередник для взаємодії між клієнтами та замовленнями
class Mediator {
public:
    virtual void notify(Client* client, const std::string& message) const = 0;
};

// Реалізація посередника
class ConcreteMediator : public Mediator {
public:
    void notify(Client* client, const std::string& message) const override {
        std::cout << "Notification to client: " << message << std::endl;
    }
};

// 3. Замовлення

// Клас для представлення замовлення
class Order {
private:
    std::vector<Product*> products;
    Client* client;

public:
    Order(Client* client) : client(client) {}

    void addProduct(Product* product) {
        products.push_back(product);
    }

    void execute() const {
        // Логіка виконання замовлення
        std::cout << "Order executed" << std::endl;
    }
};

// Команда для імплементації замовлення
class OrderCommand {
private:
    Order* order;

public:
    OrderCommand(Order* order) : order(order) {}

    void execute() const {
        order->execute();
    }
};

// 4. Знижки та промокоди

// Ланцюжок відповідальностей для обробки знижок
class DiscountHandler {
private:
    DiscountHandler* nextHandler;

public:
    void setNextHandler(DiscountHandler* handler) {
        nextHandler = handler;
    }

    virtual void applyDiscount(Order* order) const {
        if (nextHandler) {
            nextHandler->applyDiscount(order);
        }
    }
};

// Конкретні обробники знижок
class EarlyBirdDiscount : public DiscountHandler {
public:
    void applyDiscount(Order* order) const override {
        // Логіка застосування знижки Early Bird
        std::cout << "Early Bird Discount Applied" << std::endl;
    }
};

class VIPDiscount : public DiscountHandler {
public:
    void applyDiscount(Order* order) const override {
        // Логіка застосування VIP знижки
        std::cout << "VIP Discount Applied" << std::endl;
    }
};

// 5. Сплачено та відправлено

// Клас для представлення стану замовлення
class OrderState {
public:
    virtual void markPaid(Order* order) const = 0;
    virtual void markShipped(Order* order) const = 0;
};

// Конкретний стан замовлення
class PaidShippedState : public OrderState {
public:
    void markPaid(Order* order) const override {
        // Логіка позначення замовлення як сплачене
        std::cout << "Order marked as paid" << std::endl;
    }

    void markShipped(Order* order) const override {
        // Логіка позначення замовлення як відправлене
        std::cout << "Order marked as shipped" << std::endl;
    }
};

int main() {
    // Приклад використання паттернів

    // 1. Створення продуктів
    ProductFactory* coffeeFactory = new CoffeeFactory();
    Product* coffee = coffeeFactory->createProduct();
    coffee->display();

    // 2. Клієнти
    Client* client = new ConcreteClient();
    client->placeOrder();
    client->viewOrderHistory();

    // 3. Замовлення
    Order* order = new Order(client);
    order->addProduct(coffee);
    OrderCommand orderCommand(order);
    orderCommand.execute();

    // 4. Знижки та промокоди
    DiscountHandler* earlyBirdDiscount = new EarlyBirdDiscount();
    DiscountHandler* vipDiscount = new VIPDiscount();
    earlyBirdDiscount->setNextHandler(vipDiscount);

    Order* discountedOrder = new Order(client);
    earlyBirdDiscount->applyDiscount(discountedOrder);

    // 5. Сплачено та відправлено
    OrderState* orderState = new PaidShippedState();
    orderState->markPaid(discountedOrder);
    orderState->markShipped(discountedOrder);

    // Звільнення пам'яті
    delete coffee;
    delete coffeeFactory;
    delete client;
    delete order;
    delete discountedOrder;
    delete earlyBirdDiscount;
    delete vipDiscount;
    delete orderState;

    return 0;
}
