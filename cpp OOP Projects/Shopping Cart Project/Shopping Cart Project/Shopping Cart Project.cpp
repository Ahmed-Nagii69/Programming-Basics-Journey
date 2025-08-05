#include <iostream>
#include <vector>
using namespace std;

class clsProduct {
private:
    int _ProductID;
    string _ProductName;
    float _ProductPrice;

public:
    clsProduct() {}
    clsProduct(int id, string name, float price) {
        _ProductID = id;
        _ProductName = name;
        _ProductPrice = price;
    }

    int getID() {
        return _ProductID;
    }

    string getName() {
        return _ProductName;
    }

    float getPrice() {
        return _ProductPrice;
    }

    void display() {
        cout << _ProductID << ". " << _ProductName << " - " << _ProductPrice << " EGP" << endl;
    }
};

class clsUser {
protected:
    string _UserName;
    vector<clsProduct> _CartItems;

public:
    clsUser(string userName) {
        _UserName = userName;
    }

    virtual void viewProductList(vector<clsProduct>& productList) {
        cout << "\nAvailable Products:\n";
        for (int i = 0; i < productList.size(); i++) {
            productList[i].display();
        }
    }

    void addToCart(clsProduct product) {
        _CartItems.push_back(product);
        cout << product.getName() << " added to cart.\n";
    }

    virtual void viewCart() {
        cout << "\n" << _UserName << "'s Cart:\n";
        float totalPrice = 0;
        for (int i = 0; i < _CartItems.size(); i++) {
            cout << _CartItems[i].getName() << " - " << _CartItems[i].getPrice() << " EGP\n";
            totalPrice += _CartItems[i].getPrice();
        }
        cout << "Total = " << totalPrice << " EGP\n";
    }

    void placeOrder() {
        cout << "\nOrder Placed. Thank you!\n";
        _CartItems.clear();
    }
};

class clsAdminUser : public clsUser {
public:
    clsAdminUser(string adminName) : clsUser(adminName) {
    }

    void addProductToCatalog(vector<clsProduct>& productList, clsProduct product) {
        productList.push_back(product);
        cout << "Admin added: " << product.getName() << endl;
    }

    void viewCart() override {
        cout << "Admin does not have any carts.\n";
    }
};

int main() {
    vector<clsProduct> productList;
    productList.push_back(clsProduct(1, "Laptop", 10000));
    productList.push_back(clsProduct(2, "Phone", 5000));
    productList.push_back(clsProduct(3, "Book", 100));

    clsUser client("Ahmed");
    clsAdminUser admin("Admin");

    admin.addProductToCatalog(productList, clsProduct(4, "Tablet", 3000));

    client.viewProductList(productList);
    client.addToCart(productList[0]);
    client.addToCart(productList[2]);
    client.viewCart();
    client.placeOrder();

    admin.viewCart();

    return 0;
}
