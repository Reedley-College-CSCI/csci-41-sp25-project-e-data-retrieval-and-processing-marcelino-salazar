#include <iostream>
#include "clients.h"
#include "SortTracker.h"
#include "Queue.h"
#include "HashTable.h"

Clients::Clients() {
    clientFile = nullptr;
    capacity = 0;
    loadfile();
}

Clients::~Clients() { //
    if (clientFile) {
    delete[] clientFile;
    clientFile = nullptr;
    }
}

//creating new function for valid int inputs
int validIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (!cin.fail() && value >= min && value <= max) {
            break;
        }
        cout << "Invalid input. Enter a value between " << min << " and " << max << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return value;
}
//this function divides the array into low and high
int Clients::Partition(AllClientData* clientBalance, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending) {
    int pivot = clientBalance[lowIndex + (highIndex - lowIndex) / 2].clientBankInfo.balance;

    while (true) {
        if (isAscending) { //sorts in ascending order.
            while (tracker.IsLT(clientBalance[lowIndex].clientBankInfo.balance, pivot)) {
                lowIndex++;
            }
            while (tracker.IsLT(pivot, clientBalance[highIndex].clientBankInfo.balance)) {
                highIndex--;
            }
        } else { //sorts in descending order.
            while (tracker.IsLT(pivot, clientBalance[lowIndex].clientBankInfo.balance)) {
                lowIndex++;
            }
            while (tracker.IsLT(clientBalance[highIndex].clientBankInfo.balance, pivot)) {
                highIndex--;
            }
        }

        if (lowIndex >= highIndex) {
            return highIndex;
        }

        swap(clientBalance[lowIndex], clientBalance[highIndex]);
        lowIndex++;
        highIndex--;
    }
}

//this function impllments the partition function and recursively sorts the array by balance
void Clients::QuickSort(AllClientData* clients, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending) {
    if (lowIndex >= highIndex) return;

    int partitionIndex = Partition(clients, lowIndex, highIndex, tracker, isAscending);
    QuickSort(clients, lowIndex, partitionIndex, tracker, isAscending);
    QuickSort(clients, partitionIndex + 1, highIndex, tracker, isAscending);
}

void Clients::sortClients() {
    int option;

    cout << "\n[Sort by balance options]" << endl;
    cout << "\n1. Descending" << endl;
    cout << "2. Ascending" << endl;
    cout << "\nEnter an option: ";
    cin >> option;
    if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter 1-2\n" << endl;
            return;
        }
    cout << "" << endl;


    SortTracker tracker;
    bool isAscending = (option == 2); //this assigns isAscending if option is 2

    if(option == 1 || option == 2) {
    QuickSort(clientFile, 0, capacity - 1, tracker, isAscending);
    cout << "Result: " << endl;
    fullprint();
    } else {
        cout << "Invalid option. Enter 1 or 2" << endl;
    }
}

//this function checks if a string contains only numeric characters. Will use in loadfile()
bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

void Clients::loadfile() {
    ifstream file("bank_full.csv"); //this declares a ifstream class named "file" to open the external file bank_full.csv.
    if (!file) {
        cout << "Error. Could not open file." << endl;
        return;
    }
    
    string line; //this declares a string class object named "line" to store values.
    getline(file, line); //here I use the getline() function to store rows from the external file into "line". It's placement here is meant to skip the header before executing the for loop.
    int totalClients = 0; //this counts the number of clients in the file.
    while (getline(file, line)) {
        totalClients++;
    }

    file.clear(); //this resets the reading position
    file.seekg(0);
    getline(file, line);

    if (clientFile != nullptr) { 
        delete[] clientFile;
        clientFile = nullptr;
    }

    clientFile = new AllClientData[totalClients];
    capacity = totalClients;

    int idNumber = 10000; //6 digit id number declared.

    for (int i = 0; i < capacity && getline(file, line); i++) { //this declares a for loop to read in capacity number rows from the external file.
        stringstream parse(line); //this declares a stringstream class named "parse" which splits values from rows stored in "line" variable into individual strings.
        string temporaryLine; //here I declare a string class object named "temporaryLine" to convert strings into integers.
        
        clientFile[i].clientInfo.id = idNumber++; //this assigns unique 6 digit id number to each client.
        //here I use the getline() function to extract data from "parse" and store it into data members accordingly. I used stoi() function to convert strings into integers where needed.
        getline(parse, temporaryLine, ';'); 
        clientFile[i].clientInfo.age = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;
        getline(parse, clientFile[i].clientInfo.job, ';');
        getline(parse, clientFile[i].clientInfo.marital, ';');
        getline(parse, clientFile[i].clientInfo.education, ';');
        getline(parse, clientFile[i].clientBankInfo.defaulted, ';');
        getline(parse, temporaryLine, ';');
        clientFile[i].clientBankInfo.balance = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;
        getline(parse, clientFile[i].clientBankInfo.housing, ';');
        getline(parse, clientFile[i].clientBankInfo.loan, ';');
        getline(parse, clientFile[i].campaignInfo.contact, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.day = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;
        getline(parse, clientFile[i].campaignInfo.month, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.duration = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.pdays = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;
        getline(parse, clientFile[i].campaignInfo.y, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.followups = isNumber(temporaryLine) ? stoi(temporaryLine) : 0;

        //used the insert function for the hashtable
        clientHashTable.insert(clientFile[i].clientInfo.id, &clientFile[i]);

    }
    
    file.close();
}

void Clients::search() { //function to search clients based of their id number.
    while(true) {
        int idSearch;
        bool found = false;//here I intialize found variable to determine if a match was found or not.
        cout << "Enter 5 digit ID Number (10000-10100): ";
        cin >> idSearch;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid ID. Please enter 5 digit ID (10000-10100)\n" << endl;
            return;
        }
        cout << "" << endl;

        for (int i = 0; i < capacity; i++) {
            if (clientFile[i].clientInfo.id == idSearch) {
                clientFile[i].print();
                found = true;
                break;
            }
        }

        if (!found) { //this second if statement lets user know if no matches were found.
            cout << "No matches found for ID " << idSearch << "." << endl;
        }

        //adding option to search again
        string choice;
        cout << "Would you like to search for another ID? (yes/no): ";
        cin >> choice;

        if (choice != "yes") {
            cout << "Returning to main menu...\n";
            break;
        }
    }
    
}

void Clients::fullprint() const { //function to print clientFile
    for (int i = 0; i < capacity; i++) {
        clientFile[i].print(); 
    }
}

//updating input validation for each input.
void Clients::addClient() {  //here I create a function to add a new client file
    AllClientData* newClientArray = new AllClientData[capacity + 1]; //this creates a new dynamic array with 1 space appended to store new client file.
    string months[12] = {"jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"};
    string yesNoInput;

    for (int i = 0; i < capacity; i++) {  //this for loop iterates through each existing client file and stores corresponding index to new array.
        newClientArray[i] = clientFile[i];  
    }

    newClientArray[capacity].clientInfo.age = validIntInput("Enter age: ", 18, 100);
    cin.ignore();
    
    cout << "Enter job: ";
    getline(cin, newClientArray[capacity].clientInfo.job);
    newClientArray[capacity].clientInfo.job = "\"" + newClientArray[capacity].clientInfo.job + "\"";

    cout << "Enter marital status: ";
    getline(cin, newClientArray[capacity].clientInfo.marital);
    newClientArray[capacity].clientInfo.marital = "\"" + newClientArray[capacity].clientInfo.marital + "\"";

    cout << "Enter education level: ";
    getline(cin, newClientArray[capacity].clientInfo.education);
    newClientArray[capacity].clientInfo.education = "\"" + newClientArray[capacity].clientInfo.education + "\"";

    do {
        cout << "Does client have default history? (yes/no): ";
        getline(cin, yesNoInput);
        if (yesNoInput != "yes" && yesNoInput != "no")
            cout << "Invalid input. Please enter yes/no.\n";
    } while (yesNoInput != "yes" && yesNoInput != "no");
    newClientArray[capacity].clientBankInfo.defaulted = "\"" + yesNoInput + "\"";

    newClientArray[capacity].clientBankInfo.balance = validIntInput("Enter bank balance: ", 0, 10000000);

    do {
        cout << "Does client possess housing? (yes/no): ";
        getline(cin, yesNoInput);
        if (yesNoInput != "yes" && yesNoInput != "no")
            cout << "Invalid input. Please enter yes/no.\n";
    } while (yesNoInput != "yes" && yesNoInput != "no");
    newClientArray[capacity].clientBankInfo.housing = "\"" + yesNoInput + "\"";

    do {
        cout << "Does client have any loan? (yes/no): ";
        getline(cin, yesNoInput);
        if (yesNoInput != "yes" && yesNoInput != "no")
            cout << "Invalid input. Please enter yes/no.\n";
    } while (yesNoInput != "yes" && yesNoInput != "no");
    newClientArray[capacity].clientBankInfo.loan = "\"" + yesNoInput + "\"";

    cout << "Enter contact type (phone, email, mail): ";
    getline(cin, newClientArray[capacity].campaignInfo.contact);
    newClientArray[capacity].campaignInfo.contact = "\"" + newClientArray[capacity].campaignInfo.contact + "\"";

    newClientArray[capacity].campaignInfo.day = validIntInput("Enter date of contact (1-31): ", 1, 31);

    cout << "Enter month of contact (e.g., jan, feb, mar): ";
    getline(cin, newClientArray[capacity].campaignInfo.month);
    newClientArray[capacity].campaignInfo.month = "\"" + newClientArray[capacity].campaignInfo.month + "\"";

    newClientArray[capacity].campaignInfo.duration = validIntInput("Enter duration of call (sec): ", 0, 10000000);

    newClientArray[capacity].campaignInfo.pdays = validIntInput("Enter days since last contact (0-365): ", 0, 365);

    do {
        cout << "Did the client subscribe? (yes/no): ";
        getline(cin, yesNoInput);
        if (yesNoInput != "yes" && yesNoInput != "no")
            cout << "Invalid input. Please enter yes/no.\n";
    } while (yesNoInput != "yes" && yesNoInput != "no");
    newClientArray[capacity].campaignInfo.y = "\"" + yesNoInput + "\"";

    newClientArray[capacity].campaignInfo.followups = validIntInput("Enter number of follow-ups completed: ", 0, 100);

    newClientArray[capacity].clientInfo.id = 10000 + capacity; //this assigns new id based off the capacity number.

    
    delete[] clientFile; //this deletes the memory that was previously allocated for client file.
    clientFile = newClientArray; //this re-assigns clientFile with the new array created.
    capacity++; //this updates the array size for the next iteration

    ofstream outfile("bank_full.csv", ios::app);
    if (outfile.is_open()) {
        outfile << clientFile[capacity - 1].clientInfo.age << ";"
                << clientFile[capacity - 1].clientInfo.job << ";"
                << clientFile[capacity - 1].clientInfo.marital << ";"
                << clientFile[capacity - 1].clientInfo.education << ";"
                << clientFile[capacity - 1].clientBankInfo.defaulted << ";"
                << clientFile[capacity - 1].clientBankInfo.balance << ";"
                << clientFile[capacity - 1].clientBankInfo.housing << ";"
                << clientFile[capacity - 1].clientBankInfo.loan << ";"
                << clientFile[capacity - 1].campaignInfo.contact << ";"
                << clientFile[capacity - 1].campaignInfo.day << ";"
                << clientFile[capacity - 1].campaignInfo.month << ";"
                << clientFile[capacity - 1].campaignInfo.duration << ";"
                << clientFile[capacity - 1].campaignInfo.pdays << ";"
                << clientFile[capacity - 1].campaignInfo.y << ";"
                << clientFile[capacity - 1].campaignInfo.followups << "\n";
        outfile.close();
    
        clientFile[capacity - 1].print();

        clientHashTable.insert(clientFile[capacity - 1].clientInfo.id, &clientFile[capacity - 1]);
    }
}

void Clients::removeClient() {
    int removeID;
    cout << "\nEnter 5 digit ID Number to remove: ";
    cin >> removeID;
    if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid ID. Please enter 5 digit ID (10000-10100)\n" << endl;
            return;
    }

    bool found = false;
    int removeIndex = -1;

    //search for index to remove using id number
    for (int i = 0; i < capacity; i++) {
        if (clientFile[i].clientInfo.id == removeID) {
            found = true;
            removeIndex = i;
            break;
        }
    }

    if (!found) {
        cout << "No client found with ID " << removeID << ".\n";
        return;
    }

    //dynamic array with size reduced.
    AllClientData* newClientArray = new AllClientData[capacity - 1];

    //copy everything except the client removed.
    for (int i = 0, j = 0; i < capacity; i++) {
        if (i != removeIndex) { //this skips the clients being removed
            newClientArray[j++] = clientFile[i];
        }
    }

    trashbin.Append(clientFile[removeIndex]); //append the removed file to the trashlist before deleting.
    delete[] clientFile;
    clientFile = newClientArray;
    capacity--;

    cout << "\nClient with ID " << removeID << " has been removed.\n";

    ofstream outfile("bank_full.csv");
    if (outfile.is_open()) {
        outfile << "age;job;marital;education;default;balance;housing;loan;contact;day;month;duration;pdays;y;followUps\n"; // CSV header

        for (int i = 0; i < capacity; i++) {
            outfile << clientFile[i].clientInfo.age << ";"
                    << clientFile[i].clientInfo.job << ";"
                    << clientFile[i].clientInfo.marital << ";"
                    << clientFile[i].clientInfo.education << ";"
                    << clientFile[i].clientBankInfo.defaulted << ";"
                    << clientFile[i].clientBankInfo.balance << ";"
                    << clientFile[i].clientBankInfo.housing << ";"
                    << clientFile[i].clientBankInfo.loan << ";"
                    << clientFile[i].campaignInfo.contact << ";"
                    << clientFile[i].campaignInfo.day << ";"
                    << clientFile[i].campaignInfo.month << ";"
                    << clientFile[i].campaignInfo.duration << ";"
                    << clientFile[i].campaignInfo.pdays << ";"
                    << clientFile[i].campaignInfo.y << ";"
                    << clientFile[i].campaignInfo.followups << "\n";
        }
        outfile.close();
    } else {
        cout << "Error: Could not update the file after removing the client" << endl;
    }
};

void Clients::restoreClient() {
    int id;
    cout << "\nEnter 5 digit ID to restore: ";
    cin >> id;
    if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid ID. Please enter 5 digit ID (10000-10100)\n" << endl;
            return;
    }
    trashbin.Restore(*this, id);

    ofstream outfile("bank_full.csv");
if (outfile.is_open()) {
    outfile << "age;job;marital;education;default;balance;housing;loan;contact;day;month;duration;;pdays;y;followUps\n";

    for (int i = 0; i < capacity; i++) {
        outfile << clientFile[i].clientInfo.age << ";"
                << clientFile[i].clientInfo.job << ";"
                << clientFile[i].clientInfo.marital << ";"
                << clientFile[i].clientInfo.education << ";"
                << clientFile[i].clientBankInfo.defaulted << ";"
                << clientFile[i].clientBankInfo.balance << ";"
                << clientFile[i].clientBankInfo.housing << ";"
                << clientFile[i].clientBankInfo.loan << ";"
                << clientFile[i].campaignInfo.contact << ";"
                << clientFile[i].campaignInfo.day << ";"
                << clientFile[i].campaignInfo.month << ";"
                << clientFile[i].campaignInfo.duration << ";"
                << clientFile[i].campaignInfo.pdays << ";"
                << clientFile[i].campaignInfo.y << ";"
                << clientFile[i].campaignInfo.followups << "\n";
    }
    outfile.close();
}

}

void Clients::printTrash() const {
    trashbin.PrintDeletedClients();
}

//adding function that adds a recently added client to followupqueue
void Clients::enqueueClient() {
    followUpQueue.Enqueue(&clientFile[capacity -1]);
}

//adding function to remove the front
void Clients::dequeueClient() {
    followUpQueue.Dequeue();
}

//adding function to display folowupqueue
void Clients::printQueue() const {
    cout << "\nLoading recently added clients..\n";
    cout << "" << endl;
    followUpQueue.PrintQueueClients();
}

void Clients::recentlyAdded() {
    while(true) {
        cout << "\n1. View Recently Added." << endl;
        cout << "2. Enqueue recently added client." << endl;
        cout << "3. Dequeue recently added client." << endl;
        cout << "4. Return to Main Menu." << endl;
        cout << "\nEnter option: ";
        int option;
        cin >> option;
        
        if (cin.fail()) {
            cout << "Invalid input. Enter valid input: 1-4" << endl;
            
        } else if (option == 1) {
            Clients::printQueue();
        } else if (option == 2) {
            Clients::enqueueClient();
        } else if (option == 3) {
            Clients::dequeueClient();
        } else if (option == 4) {
            break;
    }
}
}

//creating function to append deleted clients to the end of the list
void SinglyLinkedNode::TrashList::Append(const AllClientData& deletedClient) {
    Node* newNode = new Node(deletedClient);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

//this function will prepend a deleted client to the beginning of the list.
void SinglyLinkedNode::TrashList::Prepend(const AllClientData& deletedClient) {
    Node* newNode = new Node(deletedClient);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
}

//created a function that uses linear search by id in the trash bin.
bool SinglyLinkedNode::TrashList::Search(int id) const {
    Node* current = head;
    
    while (current) {
        if (current->clientInfo.clientInfo.id == id) {
            cout << "Deleted client found in trash bin: " <<endl;
            current->clientInfo.print();
            return true;
        }
        current = current->next;
    }
    cout << "Client not found in trash bin." << endl;
    return false;
}

//creating a restore function that will allow users to restore deleted files
bool SinglyLinkedNode::TrashList::Restore(Clients& clients, int id) { // restore function that was declared inside TrashList class which is nested inside SinglyLinkedNode class.
    //parameter passes a reference from the Clients class in order to directly make changes and anid number.
    Node* current = head; //current points either to nullptr or the first node
    Node* prev = nullptr;

    while (current) { //while current does not point to nullptr
        if (current->clientInfo.clientInfo.id == id) { //access first node's data which is an object of the AllClientData struct and accesses clientData struct object clientInfo to access id.
            int updatedCapacity = clients.capacity + 1; //updates capacity stored in Client class through the clients reference object
            AllClientData* updatedClients = new AllClientData[updatedCapacity]; //a new array of AllClientData struct and stores first element into updatedClients pointer.

            for (int i = 0; i < clients.capacity; ++i) { //copy each element from old array into new array updatedClients.
                updatedClients[i] = clients.clientFile[i];
            }

            updatedClients[clients.capacity] = current->clientInfo; //adds matched id element to the end of the new array

            delete[] clients.clientFile; //delete old data array
            clients.clientFile = updatedClients; //re-assign old array to updated data array
            clients.capacity = updatedCapacity; //directly update capacity in the Clients class using the clients reference

            //here I will need to remove the node restored from the trash.
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            
            if (current == tail) {
                tail = prev;
            }

            delete current; //delete node from the trash list
            cout << "\nClient " << id << " restored." << endl;
            return true; //ends function operations
        }
        //if the first node did not match traveerse to the next node.
        prev = current;
        current = current->next;
    }
    
    cout << "No matches found." << endl; 
    return false; //no matches
}

void SinglyLinkedNode::TrashList::PrintDeletedClients() const {
    Node* current = head;
    
    if (!current) {
        cout << "\nTrash bin Empty" << endl;
        return;
    }

    while (current) {
        cout << "\nDisplaying trash bin contents...\n";
        cout << "" << endl;
        current->clientInfo.print();
        current = current->next;
    }
}

//creating function that updates clients follow up information and only removes from table if client subscribes. MOVE TO HASH.CPP
void Clients::updateFollowups(HashTable& hashTable) {
    int id;
    int size = hashTable.tableSize();
    string months[12] = {"jan", "feb", "mar", "apr", "may", "jun",
    "jul", "aug", "sep", "oct", "nov", "dec"
};
    cout << "Enter 5 digit ID of client (10000-10100): ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Invalid ID. Please enter 5 digit ID (10000-10100).\n";
        return;
    }

    if (id < 10000) {
        cout << "Invalid ID. Please enter 5 digit ID (10000-10100).\n";
        return;
    }

    for (int i = 0; i < capacity; ++i) {
        if (clientFile[i].clientInfo.id == id) {
            string input;
            cout << "Did you follow up? (yes/no): ";
            cin >> input;
            if (input != "yes" && input != "no") {
                cout << "Invalid input. Please enter yes/no.\n";
                return;
            }
            //if yes then increment followup and update day and month of contact
            if (input == "yes") {
                clientFile[i].campaignInfo.followups++;
                cout << "Day of contact (1-31): ";
                cin >> clientFile[i].campaignInfo.day;
                if (cin.fail() || clientFile[i].campaignInfo.day < 1 || clientFile[i].campaignInfo.day > 31) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid day. Please enter a number between 1 and 31.\n";
                    return;
                }
                cout << "Month of contact (jan-dec): ";
                cin >> input;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid input. Please enter abbreviated month (jan, feb, etc).\n";
                    return; 
                }
                //chech for correct month input as abbreviations
                bool validMonth = false;
                for (int m = 0; m < 12; ++m) {
                    if (input == months[m]) {
                        validMonth = true;
                        break;
                    }
                }

                if (!validMonth) {
                    cout << "Invalid input. Please enter abbreviated month (jan, feb, etc).\n";
                    return;
                }

                clientFile[i].campaignInfo.month = "\"" + input + "\"";
                //only allow user to remove subscribed clients    
                cout << "Has the client subscribed? (yes/no): ";
                cin >> input;
                if (input != "yes" && input != "no") {
                    cout << "Invalid input. Please enter yes/no.\n";
                    return;
                }
                clientFile[i].campaignInfo.y = "\"" + input + "\"";
                if (clientFile[i].campaignInfo.y == "\"yes\"") {
                    //need to create remove function
                    hashTable.remove(id);
                    cout << "\nClient removed from follow-up list.\n";
                } else {
                    cout << "Follow-up with client again in no more than 30 days.\n";
                }
                //update csv file accordingly
                ofstream outfile("bank_full.csv");
                if (outfile.is_open()) {
                    outfile << "age;job;marital;education;default;balance;housing;loan;contact;day;month;duration;pdays;y;followUps\n";
                    for (int j = 0; j < capacity; j++) {
                        outfile << clientFile[j].clientInfo.age << ";"
                                << clientFile[j].clientInfo.job << ";"
                                << clientFile[j].clientInfo.marital << ";"
                                << clientFile[j].clientInfo.education << ";"
                                << clientFile[j].clientBankInfo.defaulted << ";"
                                << clientFile[j].clientBankInfo.balance << ";"
                                << clientFile[j].clientBankInfo.housing << ";"
                                << clientFile[j].clientBankInfo.loan << ";"
                                << clientFile[j].campaignInfo.contact << ";"
                                << clientFile[j].campaignInfo.day << ";"
                                << clientFile[j].campaignInfo.month << ";"
                                << clientFile[j].campaignInfo.duration << ";"
                                << clientFile[j].campaignInfo.pdays << ";"
                                << clientFile[j].campaignInfo.y << ";"
                                << clientFile[j].campaignInfo.followups << "\n";
                    }
                    outfile.close();
                }
        }
    }
}
return;
}



void Clients::followUps() {
    //hashTable.unsubscribedClients(clientFile, capacity);

    while (true) {
        cout << "\n[-----------------HASH TABLE MENU----------------]\n";
        cout << "\n1. Display hash table contents" << endl;
        cout << "2. Search by days since last contact" << endl;
        cout << "3. Update follow-up" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "\nEnter option (1-4): ";

        int followUpOption;
        cin >> followUpOption;
        cout << "" << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter 1-4\n" << endl;
            return;
        }

        if (followUpOption == 1) {
            cout << "Displaying all clients in hash table...\n" << endl;
            clientHashTable.display();
        } else if (followUpOption == 2) {
            int minDays;
            cout << "Enter minimum days since last contact (1-60): ";
            cin >> minDays;
            if (minDays >= 1 && minDays <= 60) {
                clientHashTable.searchPdays(minDays);
            } else {
                cout << "Invalid input. Please enter a number between 1 and 60.\n";
            }
        
        } else if (followUpOption == 3) {
            updateFollowups(clientHashTable);

        } else if (followUpOption == 4) {
            cout << "Returning to Main Menu..." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please enter 1-4" << endl;
        }
    }
}