#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <cstdlib> // for exit()

using namespace std;

class product {
private:
    int code, qty;
    char name[20];
    float price;

public:
    int getCode() { return code; }
    char* getName() { return name; }

    void Input() {
        cout << "Input Code  = ";
        cin >> code;
        cout << "Input Name  = ";
        cin.ignore();
        cin.getline(name, 20);
        cout << "Input Qty   = ";
        cin >> qty;
        cout << "Input Price = ";
        cin >> price;
    }

    double Total() {
        return price * qty;
    }

    int Discount() {
        double total = Total();
        if (total >= 1 && total <= 10) return 10;
        else if (total > 10 && total <= 20) return 20;
        else if (total > 20 && total <= 30) return 30;
        else return 40;
    }

    double Payment() {
        return Total() - (Total() * Discount()) / 100;
    }

    void Output() {
        cout << setw(14) << code
             << setw(14) << name
             << setw(13) << qty
             << setw(14) << price << "$"
             << setw(14) << Total() << "$"
             << setw(16) << Discount() << "%"
             << setw(16) << Payment() << "$" << endl;
        cout << "|--------------|-------------|------------|--------------|--------------|----------------|--------------------------|" << endl;
    }
};

void Head_List() {
    cout << "|-------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << setw(14) << "Code"
         << setw(14) << "Name"
         << setw(13) << "Qty"
         << setw(15) << "Price"
         << setw(15) << "Total"
         << setw(17) << "Discount"
         << setw(17) << "Payment"
         << endl;
    cout << "|--------------|-------------|------------|--------------|--------------|----------------|--------------------------|" << endl;
}

void Option() {
    cout << "\n__________________|Group-10|__________________" << endl;
    cout << "| 1,  Write (Add New Products)               |" << endl;
    cout << "| 2,  Read (Display All Products)            |" << endl;
    cout << "| 3,  Search Product by Name                 |" << endl;
    cout << "| 4,  Update Product by Code                 |" << endl;
    cout << "| 5,  Remove Product by Code                 |" << endl;
    cout << "| 6,  Clear All Products                     |" << endl;
    cout << "| 7,  Clear Screen                           |" << endl;
    cout << "| 8,  Information                            |" << endl;
    cout << "| 9,  Exit                                   |" << endl;
    cout << "|____________________________________________|" << endl;
}

void Information() {
    cout << "|-----------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|=========================Information Technology of Engineering (ITE)-M2-Group:10===========================|" << endl;
    cout << "|      Member-Group: 1, ...............                                                                     |" << endl;
    cout << "|                    2, ...............                                                                     |" << endl;
    cout << "|                    3, ...............                                                                     |" << endl;
    cout << "|                    4, ...............                                                                     |" << endl;
    cout << "|                    5, ...............                                                                     |" << endl;
    cout << "|===========================================================================================================|" << endl;
}

class store {
public:
    void addGoods() {
        fstream group10("book_store.bin", ios::out | ios::binary | ios::app);
        product pro;
        int n;
        if (!group10) {
            cout << "Error creating file!" << endl;
            exit(0);
        }
        cout << "Input number of products = ";
        cin >> n;
        for (int i = 0; i < n; i++) {
            cout << "\n___________Product #" << i + 1 << "___________" << endl;
            pro.Input();
            group10.write((char*)&pro, sizeof(pro));
        }
        group10.close();
    }

    void displayGoods() {
        fstream group10("book_store.bin", ios::in | ios::binary);
        product pro;
        if (!group10) {
            cout << "Error opening file!" << endl;
            return;
        }
        Head_List();
        while (group10.read((char*)&pro, sizeof(pro))) {
            pro.Output();
        }
        group10.close();
    }

    void searchedGoods() {
        fstream group10("book_store.bin", ios::in | ios::binary);
        product pro;
        if (!group10) {
            cout << "Error opening file!" << endl;
            return;
        }
        char sname[20];
        bool found = false;
        cout << "Input product's name to search = ";
        cin.ignore();
        cin.getline(sname, 20);
        while (group10.read((char*)&pro, sizeof(pro))) {
            if (strcmp(sname, pro.getName()) == 0) {
                Head_List();
                pro.Output();
                found = true;
            }
        }
        if (!found) {
            cout << "Product not found!" << endl;
        }
        group10.close();
    }

    void updateGoods() {
        fstream group10("book_store.bin", ios::in | ios::binary);
        fstream temp("temp.bin", ios::out | ios::binary);
        product pro;
        if (!group10 || !temp) {
            cout << "File error!" << endl;
            return;
        }

        int scode;
        bool found = false;
        cout << "Input product code to update: ";
        cin >> scode;

        while (group10.read((char*)&pro, sizeof(pro))) {
            if (pro.getCode() == scode) {
                cout << "Enter new details:" << endl;
                pro.Input();
                found = true;
            }
            temp.write((char*)&pro, sizeof(pro));
        }

        group10.close();
        temp.close();

        remove("book_store.bin");
        rename("temp.bin", "book_store.bin");

        if (found) cout << "Product updated successfully.\n";
        else cout << "Product not found.\n";
    }

    void deletedGoods() {
        fstream group10("book_store.bin", ios::in | ios::binary);
        fstream temp("temp.bin", ios::out | ios::binary);
        product pro;
        if (!group10 || !temp) {
            cout << "File error!" << endl;
            return;
        }

        int scode;
        bool found = false;
        cout << "Input product code to delete: ";
        cin >> scode;

        while (group10.read((char*)&pro, sizeof(pro))) {
            if (pro.getCode() == scode) {
                found = true;
                cout << "Product deleted.\n";
                continue;
            }
            temp.write((char*)&pro, sizeof(pro));
        }

        group10.close();
        temp.close();

        remove("book_store.bin");
        rename("temp.bin", "book_store.bin");

        if (!found) cout << "Product not found.\n";
    }

    void clearGoods() {
        fstream group10("book_store.bin", ios::out | ios::binary);
        if (!group10) {
            cout << "Error clearing file!" << endl;
            return;
        }
        cout << "All products cleared.\n";
        group10.close();
    }
};

int main() {
    store storeOpen;
    int op;
    while (true) {
        Option();
        cout << "\nChoose option: ";
        cin >> op;
        switch (op) {
            case 1: storeOpen.addGoods(); break;
            case 2: storeOpen.displayGoods(); break;
            case 3: storeOpen.searchedGoods(); break;
            case 4: storeOpen.updateGoods(); break;
            case 5: storeOpen.deletedGoods(); break;
            case 6: storeOpen.clearGoods(); break;
            case 7: system("clear"); break; // or system("cls"); for Windows
            case 8: Information(); break;
            case 9: exit(0);
            default: cout << "Invalid option. Try again.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}

