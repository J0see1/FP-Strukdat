#include <iostream>
#include <vector>
using namespace std;

// Abstract class
class Item {
protected:
    static int nextId;  // Static variable to hold the next ID
    string name;
    int id;
public:
    Item(const string& name) : name(name), id(nextId++) {}  // Increment nextId each time a new object is created
    virtual void display() = 0; // Pure virtual function
    
    int getId() const {
        return id;
    }

    void setName(const string& newName) {
        name = newName;
    }
};
int Item::nextId = 0;

// PhysicalItem class
class PhysicalItem : public Item {
public:
    PhysicalItem(string name) : Item(name) {}
    void display() override {
        cout << "Physical Item: " << name << ", ID: " << id << endl;
    }
};

// DigitalItem class
class DigitalItem : public Item {
public:
    DigitalItem(string name) : Item(name) {}
    void display() override {
        cout << "Digital Item: " << name << ", ID: " << id << endl;
    }
};

// Storage class
class Storage {
private:
    vector<Item*> items;
    vector<vector<bool>> adjacencyMatrix;
public:
    void addItem(Item* item) {
        items.push_back(item);
        // Add a new row and column to the adjacency matrix
        for (auto& row : adjacencyMatrix) {
            row.push_back(false);
        }
        adjacencyMatrix.push_back(vector<bool>(items.size(), false));
    }

    void addRelationship(int id1, int id2) {
        int index1 = -1, index2 = -1;
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getId() == id1) index1 = i;
            if (items[i]->getId() == id2) index2 = i;
        }
        if (index1 != -1 && index2 != -1) {
            adjacencyMatrix[index1][index2] = true;
            adjacencyMatrix[index2][index1] = true;
        }
    }

    int findIndexById(int id) {
        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getId() == id) {
                return i;
            }
        }
        return -1;  // Return -1 if no item with the given ID is found
    }

    void displayBundleItems(int id) {
        int index = findIndexById(id);
        if (index != -1) {
            cout << "Relationships for Item " << id << ":\n";
            for (int j = 0; j < adjacencyMatrix[index].size(); j++) {
                if (adjacencyMatrix[index][j]) {
                    cout << "Item " << id << " bundled with item " << items[j]->getId() << "\n";
                }
            }
        } else {
            cout << "No item with ID " << id << " found.\n";
        }
    }

    void displayItems() {
        for (Item* item : items) {
            item->display();
        }
    }

    void updateItem(int id, const string& newName) {
        for (Item* item : items) {
            if (item->getId() == id) {
                item->setName(newName);
                return;
            }
        }
        cout << "Item not found." << endl;
    }

    void deleteItem(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                items.erase(it);
                return;
            }
        }
        cout << "Item not found." << endl;
    }


};

int main() {
    int input, menuInput, itemId, itemId1, itemId2;
    string itemName;
    DigitalItem* digitalItem = nullptr;
    PhysicalItem* physicalItem = nullptr;
    Storage storage;
    do {
        cout << "===== Menu =====" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Delete Item" << endl;
        cout << "3. Update Item" << endl;
        cout << "4. Display Item" << endl;
        cout << "5. Search bundled Item" << endl;
        cout << "6. Add bundle" << endl;
        cout << "7. Exit" << endl;
        cin >> input;

        switch(input) {
            case 1:
                cout << endl;
                cout << "===== Select =====" << endl;
                cout << "1. Digital Item" << endl;
                cout << "2. Physical Item" << endl;
                cout << "Enter your selection . . ." << endl;
                cin >> menuInput;
                switch(menuInput) {
                    case 1:
                        cout << endl;
                        cout << "Enter item's name  . . ." << endl;
                        cin.ignore();
                        getline(cin, itemName);
                        digitalItem = new DigitalItem(itemName);
                        storage.addItem(digitalItem);
                        break;
                    case 2:
                        cout << endl;
                        cout << "Enter item's name  . . ." << endl;
                        cin.ignore();
                        getline(cin, itemName);
                        physicalItem = new PhysicalItem(itemName);    
                        storage.addItem(physicalItem);
                        break;
                    default:
                        cout << "Invalid selection." << endl;
                }
                break;
            case 2:
                cout << endl;
                cout << "Enter item's id . . ." << endl;
                cin >> itemId;
                storage.deleteItem(itemId);
                break;
            case 3:
                cout << endl;
                cout << "Enter item's id . . ." << endl;
                cin >> itemId;
                cout << "Enter new item's name  . . ." << endl;
                cin >> itemName;
                storage.updateItem(itemId, itemName);
                break;
            case 4:
                cout << "Displaying . . ." << endl;
                storage.displayItems();
                break;
            case 5:
                // Add your code here to handle searching an item
                cout << endl;
                cout << "Enter item's id . . ." << endl;
                cin >> itemId;
                storage.displayBundleItems(itemId);
                break;
            case 6:
                cout << endl;
                cout << "Enter item's id . . ." << endl;
                cin >> itemId1;
                cout << "Enter item's id . . ." << endl;
                cin >> itemId2;
                storage.addRelationship(itemId1, itemId2);
                break;
            case 7:
                cout << "Exiting . . ." << endl;
                return 0;
            default:
                cout << "Invalid input." << endl;
        }
    } while (input != 7);
    return 0;
}
