#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

// -------------------------------------Structure for Menu Items---------------------------------------------------

struct MenuItem {
    string name;
    double price = 0.0;
    string descripition;
    void input();
	void displayData();
};



//-------------------------------------------Function declarations-------------------------------------------------
//Fuctions for User
void myLogo();
void displayMenu(MenuItem menu[], int size, const string& menuType, int quantities[], int counter);
double calculateBill(MenuItem menu[], int size, int quantities[]);
void displayBill(MenuItem menu[], int size, int quantities[]);
double pay(double total, double payment);
void userMenu(
    const string& userName,
    MenuItem burgerMenu[], int burgerSize,
    MenuItem pizzaMenu[], int pizzaSize,
    MenuItem sideOrderMenu[], int sideOrderSize
);
//Fuctions for Admin

bool authenticateAdmin();
void adminMenu(MenuItem burgerMenu[], int& burgerSize, MenuItem pizzaMenu[], int& pizzaSize, MenuItem sideOrderMenu[], int& sideOrderSize, int maxSize);
void addItem(MenuItem burgerMenu[], int& burgerSize, MenuItem pizzaMenu[], int& pizzaSize, MenuItem sideOrderMenu[], int& sideOrderSize, int maxSize);
void updateItem(MenuItem menu[], int size);
void deleteItem(MenuItem menu[], int& size);

// -------------------------------------Global Variables-----------------------------------------------------------
const int maxMenuSize = 50;
const int burgerSize = 50;
const int pizzaSize = 30;
const int sideOrderSize = 20;
MenuItem burgerMenu[burgerSize] = {
{"Reggy Burger", 390.00,"."}, // menu items
{"Bazinga Burger", 560.00,"."},
{"Bazooka", 630.00,"."},
{"Beef Burger", 300.00,"."},
{"Grilled Burger", 220.00,"."}
};
int burgerCounter = 5;


MenuItem pizzaMenu[pizzaSize] = {
{"Regular Pizza", 750.00,"."},
{"Small Pizza", 1450.00,"."},
{"Crown Crust", 1550.00,"."},
{"Stuff Crust Pizza", 1600.00,"."},
{"Chicken Extreme", 1550.00,"."}
};
int pizzaCounter = 5;

MenuItem sideOrderMenu[sideOrderSize] = {
{"Fries", 220.00,"."},
{"Nuggets", 450.00,"5 pcs"},
{"Chicken piece", 300.00,"."}
};
int sideOrderCounter = 3;

//---------------------------------------------Main Function-------------------------------------------------------
int main() {
    int mainChoice;
    do {
		system("cls");
		myLogo();
        cout << "Who are you? \n 1.Manager \n 2.Customer \n 3.Exit" << endl;
		cout << "Enter your choice: ";
		cin >> mainChoice;
        
        if (mainChoice == 1) {
                if (authenticateAdmin()) {
					cout << "Admin Authenticated" << endl;
                }
				else {
					cout << "Access denied. Returning to main menu." << endl;
					system("pause");
					continue;
				}
            
            adminMenu(burgerMenu, burgerCounter, pizzaMenu, pizzaCounter, sideOrderMenu, sideOrderCounter, maxMenuSize);

      
        } 

        else if (mainChoice == 2) {
            string userName;
            cout << "Enter Username: ";
            cin.ignore();
            getline(cin, userName);
            
            userMenu(userName, burgerMenu, burgerSize, pizzaMenu, pizzaSize, sideOrderMenu, sideOrderSize);
        }
        else if (mainChoice == 3) {
            cout << "Thank you for using our system. Goodbye!" << endl;
        }
        else {
            cout << "Invalid Choice. Please try again." << endl;
        }
	} while (mainChoice!=3);
	return 0;
}

// -----------------------------------------functions definitions------------------------------------------------
void myLogo() {

    cout << R"(
___  ___           _   _____         _           _               _____           _                 
|  \/  |          | | |  _  |       | |         (_)             /  ___|         | |                
| .  . | ___  __ _| | | | | |_ __ __| | ___ _ __ _ _ __   __ _  \ `--. _   _ ___| |_ ___ _ __ ___  
| |\/| |/ _ \/ _` | | | | | | '__/ _` |/ _ \ '__| | '_ \ / _` |  `--. \ | | / __| __/ _ \ '_ ` _ \ 
| |  | |  __/ (_| | | \ \_/ / | | (_| |  __/ |  | | | | | (_| | /\__/ / |_| \__ \ ||  __/ | | | | |
\_|  |_/\___|\__,_|_|  \___/|_|  \__,_|\___|_|  |_|_| |_|\__, | \____/ \__, |___/\__\___|_| |_| |_|
                                                          __/ |         __/ |                      
                                                         |___/         |___/                       
                                                                            
                                                                                )" << endl;

	cout << "A Project by Hanan Hamza" << endl;
	cout << "=====================================================================" << endl;
}
// display menu
void displayMenu(MenuItem menu[], int size, const string& menuType, int quantities[], int counter) {
    int choice;
    system("cls");
    cout << "\nSelect what you want in " << menuType << endl;
    cout << "=====================================================================" << endl;
    cout << setw(15) << "PRODUCT NUMBER" << setw(20) << "PRODUCT" << setw(10) << "PRICE" << "\tDESCRIPTION" << endl;
    cout << "=====================================================================" << endl;

    // Display menu items up to the `counter` value
    for (int i = 0; i < counter; ++i) {
        cout << setw(15) << (i + 1) << setw(5);
        menu[i].displayData(); // Use the `displayData()` method to display details
    }

    
    while (true) {
        cout << "\nEnter the product number to select or 0 to return to the main menu: ";
        cin >> choice;
        if (choice == 0) {
            return;
        }
        else if (choice > 0 && choice <= counter) {
            cout << "Enter quantity for " << menu[choice - 1].name << ": ";
            cin >> quantities[choice - 1];
        }
        else {
            cout << "Invalid choice, try again." << endl;
        }
    }
}

// display bill
void displayBill(MenuItem menu[], int size, int quantities[]) {
    cout << "\nYour Order Summary:" << endl;
    cout << "===============================================================================" << endl;
    cout << setw(20) << "PRODUCT NUMBER" << setw(20) << "PRODUCT" << setw(10) << "PRICE" << setw(10) << "QUANTITY" << setw(10) << "TOTAL" << endl;
    cout << "===============================================================================" << endl;

    for (int i = 0; i < size; ++i) {
        if (quantities[i] > 0) {
            double total = menu[i].price * quantities[i];
            cout << setw(18) << (i + 1) << setw(20) << menu[i].name << setw(10) << "Rs." << menu[i].price
                << setw(8) << quantities[i] << setw(10) << "Rs." << total << endl;
        }
    }
    cout << "===============================================================================" << endl;

    
}

// calculate bill
double calculateBill(MenuItem menu[], int size, int quantities[]) {
    double total = 0.0;
    for (int i = 0; i < size; i++) {
        total += menu[i].price * quantities[i];
    }
    return total;
}

double pay(double total, double payment) {
        double change = payment - total;
        return change;
}
// user menu
void userMenu(
    const string& userName,
    MenuItem burgerMenu[], int burgerSize,
    MenuItem pizzaMenu[], int pizzaSize,
    MenuItem sideOrderMenu[], int sideOrderSize
) {
    system("cls");
    cout << "\t   __      __        __\n";
    cout << "\t  /  \\    /  \\ ____ |  | ____  ____    _____   ____ \n"; // Greet the user
    cout << "\t  \\   \\/\\/   // __ \\|  |/ ___\\/  _ \\  /     \\ / __ \\\n";
    cout << "\t   \\        /|  ___/|  |  \\__(  <_> )|  Y Y  | ___ /  \n";
    cout << "\t    \\__/\\__/  \\____\\|__|\\_____>____/ |__|_|__|\\____\\\n";
    cout << " ----------------------------------------------------------------- " << endl;
    system("pause");
    system("cls");
    int burgerQuantities[maxMenuSize] = {0};
    int pizzaQuantities[maxMenuSize] = {0};
    int sideOrderQuantities[maxMenuSize] = {0};
    double total = 0.0;
    int choice;
    // main loop
    while (true) {
		system("cls");
        cout << " \t\t\t=====>>>>PICK YOUR ORDER<<<<=====" << endl;
        cout << "1.Burgerz" << endl;
        cout << "2.Pizzas" << endl;
        cout << "3.Side Orders" << endl;
        cout << "4.Display total" << endl;
        cout << "5.Exit" << endl;
        cout << "Enter Your Choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            displayMenu(burgerMenu, burgerSize, " Burger.", burgerQuantities, burgerCounter);
            break;
        case 2:
            displayMenu(pizzaMenu, pizzaSize, " Pizza.", pizzaQuantities, pizzaCounter);
            break;
        case 3:
            displayMenu(sideOrderMenu, sideOrderSize, " side Orders.", sideOrderQuantities,sideOrderCounter);
            break;
        case 4:
            total += calculateBill(burgerMenu, burgerSize, burgerQuantities);
            total += calculateBill(pizzaMenu, pizzaSize, pizzaQuantities);
            total += calculateBill(sideOrderMenu, sideOrderSize, sideOrderQuantities);
            displayBill(burgerMenu, burgerSize, burgerQuantities);
            displayBill(pizzaMenu, pizzaSize, pizzaQuantities);
            displayBill(sideOrderMenu, sideOrderSize, sideOrderQuantities);
            //displaying bill
            cout << "Total Bill: Rs." << total << endl;
            //payment
			if (total == 0) {
				cout << "You haven't ordered anything yet." << endl;
			}
            else {
                double payment = 0.0;
                cout << "Enter Payment: ";
                cin >> payment;
                if (payment > 0 && payment >= total) {
                    double change = pay(total, payment);
                    cout << "your change: " << change << endl;
                    cout << "Thank you for ordering.\nYour order will be ready in 30 minutes " << userName << "!" << endl;
                }
                else {
                    cout << "Insufficient amount. Your order has been cancelled. "<<endl;
                }
            }
			system("pause");
            return;
            break;
        case 5:
            cout << "Exiting without order" << endl;
			system("pause");
            return;
           
        default:
            cout << "Invalid Choice. Please try again.";
            break;
        }
    }
}

// authenticate admin
bool authenticateAdmin() {
	string password;
	cout << "Enter Admin Password: ";
	cin >> password;
	if (password == "admin") {
		cout << "Admin Authenticated" << endl;
		return true;
	}
	else {
		cout << "Invalid Password" << endl;
		return false;
	}
}

//adding items
void addItem(MenuItem burgerMenu[], int& burgerSize, MenuItem pizzaMenu[], int& pizzaSize, MenuItem sideOrderMenu[], int& sideOrderSize, int maxSize) {
    int categoryChoice;
    cout << "Select menu category to add item:" << endl;
    cout << "1. Burgers" << endl;
    cout << "2. Pizzas" << endl;
    cout << "3. Side Orders" << endl;
    cout << "Enter choice: ";
    cin >> categoryChoice;

    switch (categoryChoice) {
    case 1:
        if (burgerSize < maxSize) {
            burgerMenu[burgerSize].input();
            burgerCounter++;
            cout << "Item added to Burgers successfully." << endl;
        }
        else {
            cout << "Burger menu is full, can't add more items." << endl;
        }
        break;
    case 2:
        if (pizzaSize < maxSize) {
            pizzaMenu[pizzaSize].input();
            pizzaCounter++;
            cout << "Item added to Pizzas successfully." << endl;
        }
        else {
            cout << "Pizza menu is full, can't add more items." << endl;
        }
        break;
    case 3:
        if (sideOrderSize < maxSize) {
            sideOrderMenu[sideOrderSize].input();
            sideOrderCounter++;
            cout << "Item added to Side Orders successfully." << endl;
        }
        else {
            cout << "Side Orders menu is full, can't add more items." << endl;
        }
        break;
    default:
        cout << "Invalid category choice!" << endl;
        break;
    }
}
//updating items
void updateItem(MenuItem menu[], int size) {
    int choice;
    cout << "Enter item number to update: ";
    cin >> choice;
    if (choice <= 0 || choice > size) {
        cout << "Invalid item number!" << endl;
        return;
    }
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, menu[choice - 1].name);
    cout << "Enter new price: ";
    cin >> menu[choice - 1].price;
	cout << "Enter new descripition: ";
	cin.ignore();
	getline(cin, menu[choice - 1].descripition);
	cout << "Item updated successfully." << endl;
}

//deletion of items
void deleteItem(MenuItem menu[], int& size) {
    int choice;
    cout << "Enter Item Number to Delete: ";
    cin >> choice;
    if (choice > 0 && choice <= size) {
        for (int i = choice - 1; i < size - 1; ++i) {
            menu[i] = menu[i + 1];
        }
        size--;
    }
    else {
        cout << "Invalid choice, try again." << endl;
    }
}
//admin menu
void adminMenu(MenuItem burgerMenu[], int& burgerSize, MenuItem pizzaMenu[], int& pizzaSize, MenuItem sideOrderMenu[], int& sideOrderSize, int maxSize) {
	system("cls");
    int choice;
    while (true) {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Update Item" << endl;
        cout << "3. Delete Item" << endl;
        cout << "4. View Menu" << endl;
        cout << "5. Exit Admin Mode" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
        case 1:
            addItem(burgerMenu, burgerSize, pizzaMenu, pizzaSize, sideOrderMenu, sideOrderSize, maxSize);
            break;

        case 2: {
            int category;
            cout << "Select category to update item:" << endl;
            cout << "1. Burgers" << endl;
            cout << "2. Pizzas" << endl;
            cout << "3. Side Orders" << endl;
            cout << "Enter choice: ";
            cin >> category;

            switch (category) {
            case 1:
                updateItem(burgerMenu, burgerSize);
                break;
            case 2:
                updateItem(pizzaMenu, pizzaSize);
                break;
            case 3:
                updateItem(sideOrderMenu, sideOrderSize);
                break;
            default:
                cout << "Invalid category choice!" << endl;
                break;
            }
            break;
        }

        case 3: {
            int category;
            cout << "Select category to delete item:" << endl;
            cout << "1. Burgers" << endl;
            cout << "2. Pizzas" << endl;
            cout << "3. Side Orders" << endl;
            cout << "Enter choice: ";
            cin >> category;

            switch (category) {
            case 1:
                deleteItem(burgerMenu, burgerSize);
                break;
            case 2:
                deleteItem(pizzaMenu, pizzaSize);
                break;
            case 3:
                deleteItem(sideOrderMenu, sideOrderSize);
                break;
            default:
                cout << "Invalid category choice!" << endl;
                break;
            }
            break;
        }

        case 4:
            cout << "\nBurger Menu:" << endl;
            for (int i = 0; i < burgerSize; ++i) {
                cout << i + 1 << ". " << burgerMenu[i].name << " - Rs." << burgerMenu[i].price << " - " << burgerMenu[i].descripition << endl;
            }

            cout << "\nPizza Menu:" << endl;
            for (int i = 0; i < pizzaSize; ++i) {
                cout << i + 1 << ". " << pizzaMenu[i].name << " - Rs." << pizzaMenu[i].price << " - " << pizzaMenu[i].descripition << endl;
            }

            cout << "\nSide Orders Menu:" << endl;
            for (int i = 0; i < sideOrderSize; ++i) {
                cout << i + 1 << ". " << sideOrderMenu[i].name << " - Rs." << sideOrderMenu[i].price << " - " << sideOrderMenu[i].descripition << endl;
            }
            break;

        case 5:
            cout << "Exiting Admin Mode." << endl;
            return;

        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    }
}

void MenuItem::input() {
	cout << "Enter Item Name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter Item Price: ";
	cin >> price;
	cout << "Enter descripition for this Item: ";
	cin.ignore();
	getline(cin, descripition);
}
void MenuItem::displayData() {
    cout << setw(20) << name << setw(10) << "Rs." << price << "\t" << descripition << endl;

}

// -----------------------------------------functions definitions------------------------------------------------
