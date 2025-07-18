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
// STRUCT

struct NodeQueue{
	char name[20];
	int ID;
	char date[20];
};

int front = -1;
int rear = -1;

NodeQueue Rental[5];
int size = 5;

bool isEmpty(){
	if(front == -1){
		return true;
	} else return false;
};

bool isFull(){
	if(rear >= size -1){
		return true;
	} else return false;
};

////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY COSTUMES: OKAY

void displayCostume() {
	setColor(11);
    ifstream file("Costumes.txt");
    string line;
    int count = 1;
    while(getline(file,line)){
        cout << count << line << endl;
        count++;
    }
    file.close();
}

void displayRentals() {
	setColor(11);
    ifstream file("Rentals.txt");
    string line;
    int count = 1;
    while(getline(file,line)){
        cout << count << line << endl;
        count++;
    }
    file.close();
}

////////////////////////////////////////////////////////////////////////////////////////
// COSTUME MAIN MENU: OKAY

void CostumeList() {
    setColor(14);
    cout << "\n===============+ COSTUME INVENTORY +===============\n";

    setColor(11);
    displayCostume();

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
// ADD COSTUME: OKAY

void AddCostume(){
	char costume[20], category[20], size[20];
	int ID;
	float price;
	
	setColor(14);
    cout << "\n===============+ ADD NEW COSTUME +===============\n";
    setColor(15);
    cout << "Enter costume details:\n";
    setColor(13);
    
    cout << "Costume Name: ";
    cin.ignore();
	cin.getline(costume, 20);
	
    cout << "Category: ";
	cin.getline(category, 20);
	
	cout << "Costume ID: ";
	cin >> ID;
	
    cout << "Size: ";
    cin.ignore();
	cin.getline(size, 20);
	
    cout << "Rental Price per day: ";
	cin >> price;
	
    setColor(11);
    cout << "\n++ Costume added successfully! ++\n";
    setColor(15);
	
    ofstream file;
    file.open("Costumes.txt", fstream::app);
    if (file.is_open()){
        file << ": | " << "Name: " << costume << "\t | ";
        file << "Category: " << category << "\t | ";
        file << "ID: " << ID << " | ";
        file << "Size: " << size << " | ";
        file << "Price: $" << price << "/day | Available: Yes" << endl;
        file.close();
    }
    else {
        cout << "\n";
    }
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// REMOVE COSTUME: OKAY

void RemoveCostume(){
    string filename;
    int line_number;
    
    displayCostume();
    setColor(14);
    cout << "\n==============+ REMOVE A COSTUME +==============\n";
    setColor(15);
    cout << "Remove a costume by list number.\n";
    cout << "Enter list number of costume to remove: ";
    cin >> line_number;
    line_number;
  
    fstream read_file;
    read_file.open("Costumes.txt");
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
    }
    vector<string> lines;
    string line;
    while (getline(read_file, line))
        lines.push_back(line);
    read_file.close();
    if (line_number > (int)lines.size())
    {
        cout << "Line " << line_number;
        cout << " not in file." << endl;
        cout << "File has " << lines.size();
        cout << " lines." << endl;
    } else {
         setColor(11);
	    cout << "\n++ Costume returned successfully! ++\n";
	    setColor(10);
	    cout << ">> Thank you for using ByteStyle Rental Shop!\n";
    	pauseWithSpace();
    }
    ofstream write_file;
    write_file.open("Costumes.txt");
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
    }
    line_number--;
    for (int i = 0; i < (int)lines.size(); i++)
        if (i != line_number)
            write_file << lines[i] << endl;
    write_file.close();
}


////////////////////////////////////////////////////////////////////////////////////////
// RENT COSTUME (QUEUE) Status: Okay

void RentCostume() {
	if(front == -1){
		front++;
	    setColor(14);
	    cout << "\n===============+ RENT A COSTUME +===============\n";
	    setColor(15);
	    cout << "Enter Customer Name: ";
	    setColor(13);
	    cin.ignore();
		cin.getline(Rental[front].name, 20);
	
	    setColor(15);
	    cout << "\nAvailable Costumes:\n";
	    setColor(11);
	    displayCostume();
	
	    setColor(15);
	    cout << "\nEnter Costume ID to rent: "; setColor(11); cin >> Rental[front].ID;
	    setColor(15);
		cout << "Enter rental date (YYYY-MM-DD): "; setColor(13); cin >> Rental[front].date;
	
	    setColor(11);
	    cout << "\n++ Costume rented successfully! ++\n";
	    setColor(10);
	    cout << ">> Costume will be added to rental queue.\n";
	    setColor(15);
	    cout << ">> Thank you, enjoy your costume!\n";
	    pauseWithSpace();
	    
	    ofstream file;
		file.open("Rentals.txt", fstream::app);
	    if (file.is_open()){
	        file << ": | " << "Customer: " << Rental[front].name << "\t | ";
	        file << "Costume: " << Rental[front].ID << "\t | ";
	        file << "Rental Date: " << Rental[front].date << endl;
	        file.close();
	    } else {
	        cout << "\n";
	    }
	} else {
		rear++;
		setColor(14);
	    cout << "\n===============+ RENT A COSTUME +===============\n";
	    setColor(15);
	    cout << "Enter Customer Name: ";
	    setColor(13);
		cin >> Rental[rear].name;
	
	    setColor(15);
	    cout << "\nAvailable Costumes:\n";
	    setColor(11);
	
	    setColor(15);
	    cout << "\nEnter Costume ID to rent: "; setColor(11); cin >> Rental[rear].ID;
	    setColor(15);
		cout << "Enter rental date (YYYY-MM-DD): "; setColor(13); cin >> Rental[rear].date;
	
	    setColor(11);
	    cout << "\n++ Costume rented successfully! ++\n";
	    setColor(10);
	    cout << ">> Costume will be added to rental queue.\n";
	    setColor(15);
	    cout << ">> Thank you, enjoy your costume!\n";
	    pauseWithSpace();
		
		ofstream file;
    	file.open("Rentals.txt", fstream::app);
		if (file.is_open()){
	        file << ": | " << "Customer: " << Rental[front].name << "\t | ";
	        file << "Costume: " << Rental[front].ID << "\t | ";
	        file << "Rental Date: " << Rental[front].date << endl;
	        file.close();
	    } else {
	        cout << "\n";
	    }
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////
// RENT COSTUME (QUEUE) Status: Okay

void CostumeUnavailable() {
    setColor(12);
    cout << "\n!! Sorry, the selected costume is currently rented out. !!\n";
    setColor(14);
    cout << ">> Next available date: 2025-11-01\n";
    setColor(13);
    cout << ">> Would you like to pick another date or costume? (Y/N): ";
    setColor(15);
    pauseWithSpace();
}

////////////////////////////////////////////////////////////////////////////////////////
// RETURN COSTUME (DEQUEUE) Status: NOT OKAY

void ReturnCostume(){
    string filename;
    int line_number;
    
    setColor(14);
    cout << "\n==============+ RETURN A COSTUME +==============\n";
    setColor(15);
    cout << "Return a costume by list number.";
    cout << "Enter list number of customer who would like to return a costume:";
    cin >> line_number;
    line_number;
  
    fstream read_file;
    read_file.open("Rentals.txt");
    if (read_file.fail())
    {
        cout << "Error opening file." << endl;
    }
    vector<string> lines;
    string line;
    while (getline(read_file, line))
        lines.push_back(line);
    read_file.close();
    if (line_number > (int)lines.size())
    {
        cout << "Line " << line_number;
        cout << " not in file." << endl;
        cout << "File has " << lines.size();
        cout << " lines." << endl;
    } else {
         setColor(11);
	    cout << "\n++ Costume returned successfully! ++\n";
	    setColor(10);
	    cout << ">> Thank you for using ByteStyle Rental Shop!\n";
    	pauseWithSpace();
    }
    ofstream write_file;
    write_file.open("Rentals.txt");
    if (write_file.fail())
    {
        cout << "Error opening file." << endl;
    }
    line_number--;
    for (int i = 0; i < (int)lines.size(); i++)
        if (i != line_number)
            write_file << lines[i] << endl;
    write_file.close();
}

////////////////////////////////////////////////////////////////////////////////////////
// RENTALS LIST: OKAY

void RentalList() {
    setColor(14);
    cout << "\n==============+ CURRENT RENTALS +===============\n";

    setColor(15);
    displayRentals();

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
