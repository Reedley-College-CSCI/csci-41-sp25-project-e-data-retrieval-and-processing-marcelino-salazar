/* TO RUN USE:
g++ clients.cpp queue.cpp hashtable.cpp project_e_marcelino_salazar.cpp -o project_e && ./project_e
*/

#include <iostream>
#include "clients.h"
#include "SortTracker.h"
#include "Queue.h"
#include "HashTable.h"

using namespace std;

int main() {
    Clients viewClients; //this class pushes capacity to constructor
    HashTable hashTable; //this object is for the followUps function
   
    while(true) {
    cout << "\n|-------------------MAIN MENU-------------------|" << endl;
    cout << "\n1. View all clients" << endl;
    cout << "2. Search ID" << endl;
    cout << "3. Add new client" << endl;
    cout << "4. Remove client" << endl;
    cout << "5. Sort by balance" << endl;
    cout << "6. View Trash bin" << endl;
    cout << "7. Restore client" << endl;
    cout << "8. Recently added clients" << endl;
    cout << "9. Follow Ups (manage unsubscribed clients)" << endl;
    cout << "10. Exit Program" << endl;
    cout << "\nEnter option (1-10): ";
    int option;
    cin >> option;

    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Enter valid input: 1-10" << endl;
        
    } else if (option == 1) {
        viewClients.fullprint();

    } else if (option == 2) {
        viewClients.search();

    } else if (option == 3) {
        viewClients.addClient();
    
    } else if (option == 4) {
        viewClients.removeClient();
    
    } else if (option == 5) {
        viewClients.sortClients();
        cout << "Clients sorted:\n";
        viewClients.fullprint();
    
    } else if (option == 6) {
        viewClients.printTrash();

    } else if (option == 7) {
        viewClients.restoreClient();

    } else if (option == 8) {
        viewClients.recentlyAdded();

    } else if (option == 9) {
        viewClients.followUps();

    } else if (option == 10) {
        cout << "Closing...";
        break;
    
    } else {
            cout << "Invalid input. Enter valid input: 1-10" << endl;
            cout << "-----------------------" << endl;
    }
}

    return 0;

}
