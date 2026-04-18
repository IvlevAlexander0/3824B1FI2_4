#include <iostream>
#include <string>
#include <limits>
#include "polynomial.h"
#include "UnorderedTable.h"
#include "OrderedTable.h"
#include "AVLTreeTable.h"
#include "HashTable.h"
#include "Logs.h"

using namespace std;

UnorderedTable<Polynom> unordTab;
OrderedTable<Polynom> ordTab;
AVLTreeTable<Polynom> avlTab;
HashTable<Polynom> hashTab(101);
Logger logger("lab_log.txt");

void ResetAllStats() {
    unordTab.ResetStats();
    ordTab.ResetStats();
    avlTab.ResetStats();
    hashTab.ResetStats();
}

void SyncInsert(const string& key, const Polynom& p) {
    ResetAllStats();

    unordTab.Insert(key, p);
    ordTab.Insert(key, p);
    avlTab.Insert(key, p);
    hashTab.Insert(key, p);

    logger.LogOperation("INSERT", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());
}

Polynom* SyncFind(const string& key) {
    ResetAllStats();

    Polynom* res = unordTab.Find(key);
    ordTab.Find(key);
    avlTab.Find(key);
    hashTab.Find(key);

    logger.LogOperation("FIND", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());

    return res;
}

void SyncRemove(const string& key) {
    ResetAllStats();

    bool r1 = unordTab.Remove(key);
    bool r2 = ordTab.Remove(key);
    bool r3 = avlTab.Remove(key);
    bool r4 = hashTab.Remove(key);

    if (r1) {
        logger.LogOperation("REMOVE", key, unordTab.GetStats(), ordTab.GetStats(), avlTab.GetStats(), hashTab.GetStats());
        cout << "[System] Key '" << key << "' removed from all tables.\n";
    }
    else {
        cout << "[Error] Key not found.\n";
    }
}

int main() {
    int choice;
    string key;

    while (true) {
        cout << "\n========= TABLE CONTROLLER =========\n";
        cout << "1. Insert Polynomial\n";
        cout << "2. Find Polynomial\n";
        cout << "3. Remove Polynomial\n";
        cout << "4. Exit and Save Log\n";
        cout << "====================================\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 4) break;

        switch (choice) {
        case 1: {
            cout << "Enter unique key (for example 'A' or 'Poly1'): ";
            cin >> key;

            Polynom p;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            p.read();

            SyncInsert(key, p);
            cout << "[System] Inserted successfully.\n";
            break;
        }
        case 2: {
            cout << "Enter key to find: ";
            cin >> key;

            Polynom* result = SyncFind(key);
            if (result) {
                cout << "[Found] " << key << " = ";
                result->print();
                cout << endl;
            }
            else {
                cout << "[Error] Key '" << key << "' not found.\n";
            }
            break;
        }
        case 3: {
            cout << "Enter key to remove: ";
            cin >> key;
            SyncRemove(key);
            break;
        }
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    cout << "Exiting. Stats saved to 'lab_log.txt'\n";
    return 0;
}