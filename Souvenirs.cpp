#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h> // For console color on Windows
using namespace std;

// Named constants
const int MIN_QUANTITY = 1;
const double MIN_PRICE = 1.0;
const int BEGINNER_QUANTITY = 5;
const double MAX_BEGINNER_SPENDING = 20.0;
const int ADVANCED_QUANTITY = 10;
const double MAX_FILE_IGNORE = 1000;

// Function prototypes
void showBanner();
void setColor(int colorCode);
string getStringInput(const string& prompt);
int getIntInput(const string& prompt, int min);
double getDoubleInput(const string& prompt, double min);
double calculateTotal(int quantity, double price);
void saveToFile(const string& name, int quantity, double price, double total);
void viewReport();
void recommendLevel();

int main() {
    showBanner(); // Display introduction

    int choice;
    char continueMenu;

    do {
        setColor(3); // Default white
        cout << "\nMenu:\n";
        cout << "1 - Add a souvenir\n";
        cout << "2 - View souvenir report\n";
        cout << "3 - Recommend collecting level\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            setColor(11);
            int numToAdd = getIntInput("How many souvenirs do you want to add? ", 1);
            for (int i = 1; i <= numToAdd; i++) {
                cout << "\nSouvenir " << i << ":\n";
                string souvenirName = getStringInput("Enter the name of the souvenir: ");
                int quantity = getIntInput("Enter the quantity you bought: ", MIN_QUANTITY);
                double pricePerItem = getDoubleInput("Enter the price per item (USD): ", MIN_PRICE);

                double totalCost = calculateTotal(quantity, pricePerItem);

                // Display formatted summary
                setColor(11); // Light cyan
                cout << "\n===================== Souvenir Summary =====================\n";
                cout << left << setw(20) << "Souvenir Name" << right << setw(15) << "Quantity"
                    << right << setw(20) << "Price Each ($)" << right << setw(20) << "Total ($)" << endl;
                cout << "------------------------------------------------------------\n";
                cout << left << setw(20) << souvenirName << right << setw(15) << quantity
                    << right << setw(20) << fixed << setprecision(2) << pricePerItem
                    << right << setw(20) << fixed << setprecision(2) << totalCost << endl;

                saveToFile(souvenirName, quantity, pricePerItem, totalCost);
            }
            break;
        }
        case 2:
            setColor(14);
            viewReport();
            break;
        case 3:
            setColor(13);
            recommendLevel();
            break;
        default:
            setColor(12);
            cout << "Invalid menu choice.\n";
        }

        cout << "\nReturn to menu? (y/n): ";
        cin >> continueMenu;
        cin.ignore();
    } while (continueMenu == 'y' || continueMenu == 'Y');

    cout << "\nThank you for using Viktorija's Souvenir Tracker!\n";
    return 0;
}

// ===== FUNCTION DEFINITIONS =====

void showBanner() {
    setColor(10); // Green
    cout << "==================================================\n";
    cout << "     Welcome to Viktorija's Souvenir Tracker  \n";
    cout << "==================================================\n\n";
    setColor(7); // Reset
}

void setColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

string getStringInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty())
            cout << "Input cannot be empty.\n";
    } while (input.empty());
    return input;
}

int getIntInput(const string& prompt, int min) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min) break;
        cout << "Invalid input. Must be at least " << min << ".\n";
        cin.clear();
        cin.ignore(MAX_FILE_IGNORE, '\n');
    }
    cin.ignore();
    return value;
}

double getDoubleInput(const string& prompt, double min) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min) break;
        cout << "Invalid input. Must be at least " << min << ".\n";
        cin.clear();
        cin.ignore(MAX_FILE_IGNORE, '\n');
    }
    cin.ignore();
    return value;
}

double calculateTotal(int quantity, double price) {
    return quantity * price;
}

void saveToFile(const string& name, int quantity, double price, double total) {
    ofstream report("report.txt", ios::app);
    if (report.is_open()) {
        report << left << setw(20) << name << right << setw(15) << quantity
            << right << setw(20) << fixed << setprecision(2) << price
            << right << setw(20) << fixed << setprecision(2) << total << endl;
        report.close();
    }
}

void viewReport() {
    cout << "\nOpening report.txt...\n";
    ifstream file("report.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Report file not found.\n";
    }
}

void recommendLevel() {
    int quantity = getIntInput("Enter the total souvenirs collected today: ", 0);
    double spent = getDoubleInput("Enter total money spent: ", 0);

    if (quantity >= BEGINNER_QUANTITY && spent <= MAX_BEGINNER_SPENDING)
        cout << "You are a beginner collector. Keep exploring!\n";
    else if (quantity >= ADVANCED_QUANTITY || spent > MAX_BEGINNER_SPENDING * 2.5)
        cout << "You are an advanced collector!\n";
    else
        cout << "You are an intermediate collector.\n";
}
