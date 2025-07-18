#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <limits>
using namespace std;

//--------------------------------------------------
// Console helpers
//--------------------------------------------------
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void pauseWithSpace() {
    Sleep(600);
    cout << "\n\n";
}

//--------------------------------------------------
// Rental‑queue data
//--------------------------------------------------
struct RentalEntry {
    string customer;
    int costumeID;
    string date;
};

static const int MAX_QUEUE = 5;
int qFront = -1, qRear = -1;
RentalEntry queueArr[MAX_QUEUE];

bool isEmpty() {
    return qFront == -1;
}
bool isFull() {
    return qRear == MAX_QUEUE - 1;
}

//--------------------------------------------------
// File‑display functions
//--------------------------------------------------
void displayCostumes() {
    setColor(11);
    ifstream in("Costumes.txt");
    string line;
    int idx = 1;
    while (getline(in, line)) {
        cout << idx++ << ". " << line << "\n";
    }
}

void displayRentals() {
    setColor(11);
    ifstream in("Rentals.txt");
    string line;
    int idx = 1;
    while (getline(in, line)) {
        cout << idx++ << ". " << line << "\n";
    }
}

//--------------------------------------------------
// Menus
//--------------------------------------------------
void showMainMenu() {
    setColor(14);
    cout << "\n=== BYTESTYLE COSTUME RENTAL ===\n";
    setColor(15);
    cout << "[1] Inventory (Add/Remove)\n"
            "[2] Rent Costume\n"
            "[3] Return Costume\n"
            "[4] View Active Rentals\n"
            "[5] Exit\n";
    setColor(13);
    cout << "Choose: ";
    setColor(15);
}

void inventoryMenu() {
    setColor(14);
    cout << "\n--- INVENTORY ---\n";
    setColor(11);
    displayCostumes();
    setColor(14);
    cout << "[1] Add Costume   [2] Remove Costume   [3] Back\n";
    setColor(13);
    cout << "Choice: ";
    setColor(15);
}

void rentalsMenu() {
    setColor(14);
    cout << "\n--- ACTIVE RENTALS ---\n";
    setColor(15);
    displayRentals();
    setColor(14);
    cout << "[1] Back\n";
    setColor(13);
    cout << "Choice: ";
    setColor(15);
}

void exitMessage() {
    setColor(14);
    cout << "\n=== Thank you for using ByteStyle! ===\n";
    setColor(15);
    pauseWithSpace();
}

//--------------------------------------------------
// Inventory operations
//--------------------------------------------------
void addCostume() {
    string name, category, size;
    int id;
    double price;

    setColor(14);
    cout << "\n--- ADD NEW COSTUME ---\n";
    setColor(15);

    cout << "Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Category: ";
    getline(cin, category);

    cout << "ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Size: ";
    getline(cin, size);

    cout << "Price per day: ";
    cin >> price;

    ofstream out("Costumes.txt", ios::app);
    out << "Name: " << name
        << " | Category: " << category
        << " | ID: " << id
        << " | Size: " << size
        << " | Price: $" << price
        << " | Available: Yes\n";

    setColor(11);
    cout << "Costume added!\n";
    setColor(15);
    pauseWithSpace();
}

void removeCostume() {
    displayCostumes();
    setColor(14);
    cout << "\n--- REMOVE COSTUME ---\n";
    setColor(13);
    cout << "Enter item number to remove: ";
    int n;
    cin >> n;

    // Read all lines
    ifstream in("Costumes.txt");
    vector<string> lines;
    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }

    if (n < 1 || n > (int)lines.size()) {
        setColor(12);
        cout << "Invalid number.\n";
        setColor(15);
    } else {
        // Rewrite without the removed line
        ofstream out("Costumes.txt");
        for (int i = 0; i < (int)lines.size(); ++i) {
            if (i != n - 1) out << lines[i] << "\n";
        }
        setColor(11);
        cout << "Costume removed!\n";
        setColor(15);
    }
    pauseWithSpace();
}

//--------------------------------------------------
// Rental / Return
//--------------------------------------------------
void handleUnavailable() {
    char c;
    setColor(12);
    cout << "That costume is already rented.\n";
    setColor(13);
    cout << "Try again? (Y/N): ";
    cin >> c;
    if (c == 'Y' || c == 'y') {
        // fall through to rent
    } else {
        pauseWithSpace();
        return;
    }
}

void rentCostume() {
    if (isFull()) {
        setColor(12);
        cout << "Rental queue is full—please return something first.\n";
        setColor(15);
        pauseWithSpace();
        return;
    }

    int slot = ++qRear;
    if (qFront == -1) qFront = 0;

    setColor(14);
    cout << "\n--- RENT COSTUME ---\n";
    setColor(15);

    cout << "Customer name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, queueArr[slot].customer);

    setColor(11);
    displayCostumes();
    setColor(15);

    cout << "Costume ID to rent: ";
    cin >> queueArr[slot].costumeID;

    // Check duplicate
    for (int i = qFront; i < slot; ++i) {
        if (queueArr[i].costumeID == queueArr[slot].costumeID) {
            handleUnavailable();
            // rollback
            --qRear;
            if (qRear < qFront) qFront = qRear = -1;
            return;
        }
    }

    cout << "Rental date (YYYY-MM-DD): ";
    cin >> queueArr[slot].date;

    ofstream out("Rentals.txt", ios::app);
    out << "Customer: " << queueArr[slot].customer
        << " | ID: " << queueArr[slot].costumeID
        << " | Date: " << queueArr[slot].date
        << "\n";

    setColor(11);
    cout << "Costume rented!\n";
    setColor(15);
    pauseWithSpace();
}

void returnCostume() {
    if (isEmpty()) {
        setColor(12);
        cout << "No active rentals to return.\n";
        setColor(15);
        pauseWithSpace();
        return;
    }

    setColor(14);
    cout << "\n--- RETURN COSTUME ---\n";
    setColor(15);
    cout << "Returning for: " << queueArr[qFront].customer
         << " (ID " << queueArr[qFront].costumeID << ")\n";

    // Dequeue
    ++qFront;
    if (qFront > qRear) {
        qFront = qRear = -1;
    }

    // Rewrite file
    ofstream out("Rentals.txt");
    if (!isEmpty()) {
        for (int i = qFront; i <= qRear; ++i) {
            out << "Customer: " << queueArr[i].customer
                << " | ID: " << queueArr[i].costumeID
                << " | Date: " << queueArr[i].date
                << "\n";
        }
    }

    setColor(11);
    cout << "Costume returned!\n";
    setColor(15);
    pauseWithSpace();
}

//--------------------------------------------------
// main()
//--------------------------------------------------
int main() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                inventoryMenu();
                int sub;
                cin >> sub;
                if (sub == 1) addCostume();
                else if (sub == 2) removeCostume();
                break;
            }
            case 2:
                rentCostume();
                break;
            case 3:
                returnCostume();
                break;
            case 4: {
                rentalsMenu();
                int sub;
                cin >> sub;
                pauseWithSpace();
                break;
            }
            case 5:
                exitMessage();
                running = false;
                break;
            default:
                setColor(12);
                cout << "Invalid option.\n";
                setColor(15);
                pauseWithSpace();
        }
    }
    return 0;
}
