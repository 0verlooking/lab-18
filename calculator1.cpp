#include <iostream>
#include <vector>
#include <memory>

class Product {
public:
    std::string name;
    double price;

    Product(const std::string& n, double p) : name(n), price(p) {}
};

class Order {
public:
    std::vector<std::unique_ptr<Product>> products;

    void addProduct(std::unique_ptr<Product> product) {
        products.push_back(std::move(product));
    }

    void removeProduct(const std::string& productName) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if ((*it)->name == productName) {
                products.erase(it);
                break;  // Виходимо з циклу після видалення елемента
            }
        }
    }

    double getTotal() {
        double total = 0.0;
        for (const auto& product : products) {
            total += product->price;
        }
        return total;
    }
};

int main() {
    Order order;
    order.addProduct(std::make_unique<Product>("Product1", 10.0));
    order.addProduct(std::make_unique<Product>("Product2", 20.0));

    std::cout << "Total: " << order.getTotal() << "\n";  // Виводить "Total: 30"

    order.removeProduct("Product1");

    std::cout << "Total: " << order.getTotal() << "\n";  // Виводить "Total: 20"

    return 0;
}