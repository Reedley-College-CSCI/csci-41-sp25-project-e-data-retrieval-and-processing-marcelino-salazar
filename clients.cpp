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

    cout << "Sort by Balance" << endl;
    cout << "1. Descending" << endl;
    cout << "2. Ascending" << endl;
    cout << "Enter an option" << endl;
    cin >> option;

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
        clientFile[i].clientInfo.age = stoi(temporaryLine);
        getline(parse, clientFile[i].clientInfo.job, ';');
        getline(parse, clientFile[i].clientInfo.marital, ';');
        getline(parse, clientFile[i].clientInfo.education, ';');
        getline(parse, clientFile[i].clientBankInfo.defaulted, ';');
        getline(parse, temporaryLine, ';');
        clientFile[i].clientBankInfo.balance = stoi(temporaryLine);
        getline(parse, clientFile[i].clientBankInfo.housing, ';');
        getline(parse, clientFile[i].clientBankInfo.loan, ';');
        getline(parse, clientFile[i].campaignInfo.contact, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.day = stoi(temporaryLine);
        getline(parse, clientFile[i].campaignInfo.month, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.duration = stoi(temporaryLine);
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.pdays = stoi(temporaryLine);
        getline(parse, clientFile[i].campaignInfo.y, ';');
        getline(parse, temporaryLine, ';'); 
        clientFile[i].campaignInfo.followups = stoi(temporaryLine);
    }
    file.close();
}

void Clients::search() { //function to search clients based of their id number.
    int idSearch;
    bool found = false;//here I intialize found variable to determine if a match was found or not.
    cout << "Enter ID Number (starts at 10000): ";
    cin >> idSearch;
    cout << "-----------------------" << endl;

    for (int i = 0; i < capacity; i++) {
        if (clientFile[i].clientInfo.id == idSearch) {
            clientFile[i].print();
            found = true;
            break;
        }
    }

    if (found != true) { //this second if statement lets user know if no matches were found.
        cout << "No matches found. Re-run program";
    }
    
}

void Clients::fullprint() const { //function to print clientFile
    for (int i = 0; i < capacity; i++) {
        clientFile[i].print(); 
    }
}

void Clients::addClient() {  //here I create a function to add a new client file
    AllClientData* newClientArray = new AllClientData[capacity + 1]; //this creates a new dynamic array with 1 space appended to store new client file.

    for (int i = 0; i < capacity; i++) {  //this for loop iterates through each existing client file and stores corresponding index to new array.
        newClientArray[i] = clientFile[i];  
    }

    cout << "Enter age: ";
    cin >> newClientArray[capacity].clientInfo.age;
    
    cout << "Enter job: ";
    cin >> newClientArray[capacity].clientInfo.job;
    cout << "-----------------------" << endl;

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
}
}

void Clients::removeClient() {
    int removeID;
    cout << "Enter ID Number to remove: ";
    cin >> removeID;

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

    cout << "Client with ID " << removeID << " has been removed.\n";

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
    cout << "Enter ID to restore: ";
    cin >> id;
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
    followUpQueue.PrintQueueClients();
}

void Clients::recentlyAdded() {
    while(true) {
        cout << "1. View Recently Added." << endl;
        cout << "2. Enqueue recently added client." << endl;
        cout << "3. Dequeue recently added client." << endl;
        cout << "4. Return to Main Menu." << endl;
        cout << "Enter option: ";
        int option;
        cin >> option;
        cout << "-----------------------" << endl;
        
        if (cin.fail()) {
            cout << "Invalid input. Enter valid input: 1,2,3" << endl;
            cout << "-----------------------" << endl;
            
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
        cout << "Trash bin Empty" << endl;
        return;
    }

    while (current) {
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
    cout << "Enter ID of client: ";
    cin >> id;
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please enter correct ID.";
        return;
    }

    if (id < 10000) {
        cout << "Invalid ID. Try again.\n";
        return;
    }

    for (int i = 0; i < capacity; ++i) {
        if (clientFile[i].clientInfo.id == id) {
            string input;
            cout << "Did you follow up? (yes/no): ";
            cin >> input;
            if (input != "yes" && input != "no") {
                cout << "Invalid input. Please enter 'yes' or 'no'.\n";
                return;
            }
            //if yes then increment followup and update day and month of contact
            if (input == "yes") {
                clientFile[i].campaignInfo.followups++;
                cout << "Day of contact: ";
                cin >> clientFile[i].campaignInfo.day;
                if (cin.fail() || clientFile[i].campaignInfo.day < 1 || clientFile[i].campaignInfo.day > 31) {
                    cin.clear();
                    cin.ignore();
                    cout << "Invalid day. Please enter a number between 1 and 31.\n";
                    return;
                }
                cout << "Month of contact: ";
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
                    cout << "Invalid input. Please enter 'yes' or 'no'.\n";
                    return;
                }
                clientFile[i].campaignInfo.y = "\"" + input + "\"";
                if (clientFile[i].campaignInfo.y == "\"yes\"") {
                    //need to create remove function
                    hashTable.remove(id);
                    cout << "Client removed from follow-up list.\n";
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
cout << "-----------------------" << endl;
return;
}



void Clients::followUps(HashTable& hashTable) {
    hashTable.unsubscribedClients(clientFile, capacity);

    while (true) {
        cout << "1. Display hash table contents" << endl;
        cout << "2. Search by days since last contact" << endl;
        cout << "3. Update follow-up" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter option (1-4): ";

        int followUpOption;
        cin >> followUpOption;
        cout << "-----------------------" << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter 1-4" << endl;
            cout << "-----------------------" << endl;
            return;
        }

        if (followUpOption == 1) {
            cout << "Displaying all clients in hash table:" << endl;
            hashTable.display();
        } else if (followUpOption == 2) {
            int minDays;
            cout << "Enter minimum days since last contact (1-60): ";
            cin >> minDays;
            if (minDays >= 1 && minDays <= 60) {
                hashTable.searchPdays(minDays);
            } else {
                cout << "Invalid input. Please enter a number between 1 and 60.\n";
            }
        
        } else if (followUpOption == 3) {
            updateFollowups(hashTable);

        } else if (followUpOption == 4) {
            cout << "Returning to Main Menu..." << endl;
            break;
        }
        else {
            cout << "Invalid option. Please enter 1-4" << endl;
        }
    }
}