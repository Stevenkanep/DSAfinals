// Refactored ByteStyle Rental Shop with added structures and classes
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void pauseWithSpace() {
    Sleep(600);
    cout << "\n\n";
}

////////////////////////////////////////////////////////////////////////////////////////
// STRUCTS & CLASSES

// Represents a costume in the inventory
struct Costume {
    string name;
    string category;
    int ID;
    string size;
    float price;
    bool available;
};

// Manages costume inventory operations
class CostumeManager {
private:
    vector<Costume> costumes;
    const string filename = "Costumes.txt";
public:
    CostumeManager() { loadFromFile(); }

    void loadFromFile() {
        costumes.clear();
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            // parsing assuming same format as saved
            Costume c;
            // naive parsing; could improve with stringstream
            size_t pos;
            c.available = (line.find("Available: Yes") != string::npos);
            // extract fields
            pos = line.find("Name: ");
            c.name = line.substr(pos + 6, line.find("\t", pos) - (pos + 6));
            pos = line.find("Category: ");
            c.category = line.substr(pos + 10, line.find("\t", pos) - (pos + 10));
            pos = line.find("ID: ");
            c.ID = stoi(line.substr(pos + 4, line.find(" |", pos) - (pos + 4)));
            pos = line.find("Size: ");
            c.size = line.substr(pos + 6, line.find(" |", pos) - (pos + 6));
            pos = line.find("Price: $");
            c.price = stof(line.substr(pos + 8, line.find("/day", pos) - (pos + 8)));
            costumes.push_back(c);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) return;
        for (auto &c : costumes) {
            file << ": | Name: " << c.name << "\t | Category: " << c.category
                 << "\t | ID: " << c.ID << " | Size: " << c.size
                 << " | Price: $" << c.price << "/day | Available: "
                 << (c.available ? "Yes" : "No") << endl;
        }
        file.close();
    }

    void displayCostume() {
        setColor(11);
        int count = 1;
        for (auto &c : costumes) {
            cout << count++ << ": Name: " << c.name
                 << " | Category: " << c.category
                 << " | ID: " << c.ID
                 << " | Size: " << c.size
                 << " | Price: $" << c.price << "/day"
                 << " | Available: " << (c.available ? "Yes" : "No")
                 << endl;
        }
    }

    void addCostume(const Costume &c) {
        costumes.push_back(c);
        saveToFile();
    }

    void removeCostume(int index) {
        if (index >= 0 && index < (int)costumes.size()) {
            costumes.erase(costumes.begin() + index);
            saveToFile();
        }
    }

    bool isAvailable(int id) {
        for (auto &c : costumes)
            if (c.ID == id)
                return c.available;
        return false;
    }

    void setAvailability(int id, bool av) {
        for (auto &c : costumes)
            if (c.ID == id)
                c.available = av;
        saveToFile();
    }
};

// Represents a rental entry
struct RentalEntry {
    string customer;
    int costumeID;
    string date;
};

// Manages rental queue operations
class RentalManager {
private:
    vector<RentalEntry> rentals;
    const string filename = "Rentals.txt";
public:
    RentalManager() { loadFromFile(); }

    void loadFromFile() {
        rentals.clear();
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            RentalEntry r;
            size_t pos;
            pos = line.find("Customer: ");
            r.customer = line.substr(pos + 10, line.find("\t", pos) - (pos + 10));
            pos = line.find("Costume: ");
            r.costumeID = stoi(line.substr(pos + 10, line.find("\t", pos) - (pos + 10)));
            pos = line.find("Rental Date: ");
            r.date = line.substr(pos + 13);
            rentals.push_back(r);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) return;
        for (auto &r : rentals) {
            file << ": | Customer: " << r.customer << "\t | Costume: " << r.costumeID
                 << "\t | Rental Date: " << r.date << endl;
        }
        file.close();
    }

    void displayRentals() {
        setColor(11);
        int count = 1;
        for (auto &r : rentals) {
            cout << count++ << ": Customer: " << r.customer
                 << " | Costume: " << r.costumeID
                 << " | Rental Date: " << r.date << endl;
        }
    }

    void addRental(const RentalEntry &r) {
        rentals.push_back(r);
        saveToFile();
    }

    void removeRental(int index) {
        if (index >= 0 && index < (int)rentals.size()) {
            rentals.erase(rentals.begin() + index);
            saveToFile();
        }
    }

    bool isRented(int id) {
        for (auto &r : rentals)
            if (r.costumeID == id) return true;
        return false;
    }
};

// Global managers
CostumeManager costumeMgr;
RentalManager rentalMgr;

////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY COSTUMES: OKAY
// (now handled by CostumeManager)

////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY RENTALS: OKAY
// (now handled by RentalManager)

////////////////////////////////////////////////////////////////////////////////////////
// COSTUME MAIN MENU: OKAY

void CostumeList() {
    setColor(14);
    cout << "\n===============+ COSTUME INVENTORY +===============\n";

    costumeMgr.displayCostume();

    setColor(14);
    cout << "---------------------------------------------------\n";
    setColor(15);
    cout << "[1] Add a new costume\n";
    cout << "[2] Remove a costume\n";
    cout << "[3] Back to main menu\n";
    setColor(13);
    cout << ">> Enter your choice: ";
    setColor(15);
}

////////////////////////////////////////////////////////////////////////////////////////
// ADD COSTUME: OKAY (via manager)

void AddCostume() {
    Costume c;
    setColor(14);
    cout << "\n===============+ ADD NEW COSTUME +===============\n";
    setColor(15);
    cout << "Enter costume details:\n";
    setColor(13);
    cout << "Costume Name: "; cin.ignore(); getline(cin, c.name);
    cout << "Category: "; getline(cin, c.category);
    cout << "Costume ID: "; cin >> c.ID;
    cout << "Size: "; cin.ignore(); getline(cin, c.size);
    cout << "Rental Price per day: "; cin >> c.price;
    c.available = true;
    costumeMgr.addCostume(c);
    setColor(11);
    cout << "\n++ Costume added successfully! ++\n";
    setColor(15);
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// REMOVE COSTUME: OKAY (via manager)

void RemoveCostume() {
    costumeMgr.displayCostume();
    setColor(14);
    cout << "\n==============+ REMOVE A COSTUME +==============\n";
    setColor(15);
    cout << "Enter list number of costume to remove: ";
    int idx; cin >> idx;
    costumeMgr.removeCostume(idx - 1);
    setColor(11);
    cout << "\n++ Costume removed successfully! ++\n";
    setColor(15);
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// RENT COSTUME with class logic

void CostumeUnavailable() {
    char choice;

    setColor(12);
    cout << "\n!! Sorry, the selected costume is currently rented out. !!\n";
    setColor(14);
    cout << ">> Next available date: 2025-11-01\n";
    setColor(13);
    cout << ">> Would you like to pick another costume? (Y/N): ";
    setColor(15);
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        pauseWithSpace();
        RentCostume();
    }
    pauseWithSpace();
}

void RentCostume() {
    setColor(14);
    cout << "\n===============+ RENT A COSTUME +===============\n";
    setColor(15);
    RentalEntry r;
    cout << "Enter Customer Name: ";
    setColor(13);
    cin.ignore(); getline(cin, r.customer);

    setColor(15);
    cout << "\nAvailable Costumes:\n";
    costumeMgr.displayCostume();

    setColor(15);
    cout << "\nEnter Costume ID to rent: ";
    setColor(11);
    cin >> r.costumeID;

    if (!costumeMgr.isAvailable(r.costumeID) || rentalMgr.isRented(r.costumeID)) {
        CostumeUnavailable();
        return;
    }

    setColor(15);
    cout << "Enter rental date (YYYY-MM-DD): ";
    setColor(13);
    cin >> r.date;

    rentalMgr.addRental(r);
    costumeMgr.setAvailability(r.costumeID, false);

    setColor(11);
    cout << "\n++ Costume rented successfully! ++\n";
    setColor(10);
    cout << ">> Costume will be added to rental queue.\n";
    setColor(15);
    cout << ">> Thank you, enjoy your costume!\n";
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// RETURN COSTUME: OKAY (via manager)

void ReturnCostume() {
    rentalMgr.displayRentals();
    setColor(14);
    cout << "\n==============+ RETURN A COSTUME +==============\n";
    setColor(15);
    cout << "Enter list number of rental to return: ";
    int idx; cin >> idx;
    int cid = rentalMgr.rentals[idx-1].costumeID;  // access to struct
    rentalMgr.removeRental(idx-1);
    costumeMgr.setAvailability(cid, true);

    setColor(11);
    cout << "\n++ Costume returned successfully! ++\n";
    setColor(10);
    cout << ">> Thank you for using ByteStyle Rental Shop!\n";
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// RENTALS LIST: OKAY

void RentalList() {
    setColor(14);
    cout << "\n==============+ CURRENT RENTALS +===============\n";

    setColor(15);
    rentalMgr.displayRentals();

    setColor(14);
    cout << "---------------------------------------------------\n";
    setColor(15);
    cout << "[1] Back to main menu\n";
    setColor(13);
    cout << ">> Enter your choice: ";
    setColor(15);
}

////////////////////////////////////////////////////////////////////////////////////////

void ExitMessage() {
    setColor(14);
    cout << "\n==================================================\n";
    setColor(10);
    cout << "      Thank you for visiting ByteStyle Rental!     \n";
    cout << "        We hope you enjoyed our costumes.          \n";
    cout << "               See you next time!                  \n";
    setColor(14);
    cout << "==================================================\n";
    setColor(15);
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////

void showMainMenu() {
    setColor(14);
    cout << "==================================================\n";
    cout << "            WELCOME TO BYTESTYLE RENTAL           \n";
    cout << "==================================================\n";
    setColor(15);
    cout << "[1] COSTUME FOR RENT LIST (Add/Remove)\n";
    cout << "[2] RENT COSTUME\n";
    cout << "[3] RETURN COSTUME\n";
    cout << "[4] CHECK RENTAL LIST\n";
    cout << "[5] EXIT\n";
    setColor(14);
    cout << "--------------------------------------------------\n";
    setColor(13);
    cout << ">> Enter your choice: ";
    setColor(15);
}

////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int choice, subChoice;
    bool run = true;

    while(run) {
        showMainMenu();
        cin >> choice;

        if (choice == 1) {
            CostumeList();
            cin >> subChoice;
            if(subChoice == 1) AddCostume();
            else if(subChoice == 2) RemoveCostume();
            else if(subChoice == 3) continue;
            else {
                setColor(12);
                cout << "!! Invalid option. Try again. !!\n";
                setColor(15);
            }
        }
        else if (choice == 2) {
            RentCostume();
        }
        else if (choice == 3) {
            ReturnCostume();
        }
        else if (choice == 4) {
            RentalList();
            cin >> subChoice;
            pauseWithSpace();
        }
        else if (choice == 5) {
            ExitMessage();
            run = false;
        }
        else {
            setColor(12);
            cout << "!! Invalid choice! Please try again. !!\n";
            setColor(15);
        }
        cout << endl;
    }
    return 0;
}
