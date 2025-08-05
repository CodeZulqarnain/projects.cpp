#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

// Structure for Menu Item
struct MenuItem {
    string name;
    double price;
};

// Function to fetch system time and determine menu type
string getTimeBasedMenu() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hour = ltm->tm_hour;

    if (hour >= 6 && hour <= 11)
        return "Breakfast";
    else if (hour >= 12 && hour < 16)
        return "Lunch";
    else if (hour >= 16 && hour < 22)
        return "Dinner";
    else
        return "Drinks , Desserts & snacks";
}

// Function to display menu based on time
void displayMenu(string menuType, vector<MenuItem> &menu) {
    cout << "\n---- " << menuType << " Menu ----\n";
    for (size_t i = 0; i < menu.size(); ++i)
        cout << i + 1 << ". " << menu[i].name << " - Rs." << menu[i].price << "\n";
}

// Function to take an order
void placeOrder(vector<MenuItem> &menu, vector<MenuItem> &order) {
    int choice;
    cout << "\nEnter item number to order (0 to stop): ";
    while (cin >> choice && choice != 0) {
        if (choice > 0 && choice <= menu.size()) {
            order.push_back(menu[choice - 1]);
            cout << menu[choice - 1].name << " added to your order.\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
        cout << "Enter item number to order (0 to stop): ";
    }
}

// Function to generate invoice
void generateInvoice(vector<MenuItem> &order) {
    if (order.empty()) {
        cout << "\nNo items ordered.\n";
        return;
    }
    double total = 0;
    cout << "\n---- Invoice ----\n";
    for (const auto &item : order) {
        cout << item.name << " - Rs." << fixed << setprecision(2) << item.price << "\n";
        total += item.price;
    }
    cout << "-------------------\nTotal Bill: Rs." << fixed << setprecision(2) << total << "\n";
}

int main() {
    vector<MenuItem> breakfast = {
        {"Sheermal", 200},{"Kashmiri kulcha", 20}, {"Kahwa", 160}, {"Girda", 120}, {"Bakarkhani", 240},
        {"Tsochvoru", 280}, {"Harisa", 400}, {"Lavasa", 160}, {"Noon Chai", 120},
        {"Kashmiri Naan", 200}, {"Butter Tea", 140}
    };

    vector<MenuItem> lunch = {
        {"Rogan Josh", 1000}, {"Yakhni", 800}, {"Gushtaba", 1200}, {"Rista", 1120},
        {"Dum Aloo", 720}, {"Kashmiri Pulao", 880}, {"Modur Pulao", 960},
        {"Nadru Yakhni", 800}, {"Kashmiri Rajma", 600}, {"Aab Gosht", 1040}
    };

    vector<MenuItem> snacks = {
        {"Kashmiri Pakora", 400}, {"Shirmal with Butter", 240}, {"Nadru Monje", 480},
        {"Kashmiri Samosa", 320}, {"Shab Deg", 600}, {"Lyodur Tschaman", 520},
        {"Kashmiri Kebabs", 560}, {"Phirni", 320}, {"Shufta", 480}, {"Kahwa", 160}
    };

    vector<MenuItem> dinner = lunch;  // Dinner has the same items as lunch

    vector<MenuItem> drinksDesserts = {
        {"Kahwa", 160}, {"Phirni", 320}, {"Shufta", 480}, {"Noon Chai", 120},
        {"Butter Tea", 140}, {"Kashmiri Kesar Tea", 200}, {"Sheer Chai", 160},
        {"Kashmiri Firni", 360}, {"Kashmiri Halwa", 280}, {"Dry Fruit Kheer", 400}
    };

    string menuType = getTimeBasedMenu();
    vector<MenuItem> selectedMenu;

    if (menuType == "Breakfast")
        selectedMenu = breakfast;
    else if (menuType == "Lunch")
        selectedMenu = lunch;
    else if (menuType == "Snacks")
        selectedMenu = snacks;
    else if (menuType == "Dinner")
        selectedMenu = dinner;
    else
        selectedMenu = drinksDesserts;

    vector<MenuItem> order;
    int choice;
    do {
        cout << "\n---- Welcome to Gash Daswwar ----\n";
        cout << "1. View Menu\n2. Place Order\n3. Generate Invoice\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                displayMenu(menuType, selectedMenu);
                break;
            case 2:
                placeOrder(selectedMenu, order);
                break;
            case 3:
                generateInvoice(order);
                break;
            case 4:
                cout << "\nThank you for dining with us!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}