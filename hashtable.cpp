#include "HashTable.h"
#include "clients.h"
#include <iostream>

using namespace std;

//initialzing table size in constructor
HashTable::HashTable() {
    TABLE_SIZE = 19;
    table = new Bucket[TABLE_SIZE];
}

HashTable::~HashTable() {
    delete[] table;
}

int collisionCount = 0;
//here I create an insert function
bool HashTable::insert(int key, const ClientStatus& value) {
    int hashNum = hash(key);

for (int i = 0; i < TABLE_SIZE; ++i) {
    int index = (hashNum + i * i) % TABLE_SIZE;
    
    if (!table[index].isOccupied) {
        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;

        return true;
    } else {
        collisionCount++;
    }
}
//here I will resize the table
int tempSize = TABLE_SIZE;
int newSize = tempSize * 2;

//create a temp pointer equivalent to table pointer.
Bucket* tempTable = table;
table = new Bucket[newSize];
//here I generate a new hash number
for (int i = 0; i < tempSize; ++i) {
    if (tempTable[i].isOccupied && !tempTable[i].isDeleted) {
        int newhashNum = tempTable[i].key % newSize;
        //repeat quadratic probing
        for (int j = 0; j < newSize; ++j) {
            int newIndex = (newhashNum + j * j) % newSize;
            if (!table[newIndex].isOccupied) {
                table[newIndex] = tempTable[i];
                break;
            }
        }
    }
}
//free memory and update table size
delete[] tempTable;
TABLE_SIZE = newSize;
//recall insert function
return insert(key, value);
}

//I create a display function with client status
void HashTable::display() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        cout << "[" << i << "]     ";

        if (table[i].isOccupied) {
            cout << "ID: " << table[i].key 
                 << " | Subscription: " << table[i].value.subscription
                 << " | Days Since Last Contact: " << table[i].value.lastContacted 
                 << endl;
        }
       
        else {
            cout << "EMPTY" << endl;
        }
    }
    cout << "Total Collisions: " << collisionCount << endl;
    cout << "-----------------------" << endl;
}

//I will create a function to gathher only unsubscribed clients and insert them into the hash table.
void HashTable::unsubscribedClients(AllClientData* clientFile, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        if (clientFile[i].campaignInfo.y == "\"no\"") {
            ClientStatus status;
            status.subscription = clientFile[i].campaignInfo.y;
            status.lastContacted = clientFile[i].campaignInfo.pdays;
            //call the insert function and pass in these client ids and status info
            insert(clientFile[i].clientInfo.id, status);
        }
    }
}
//here I will create a function to search by pdays with a threshold of 60 days.
void HashTable::searchPdays(int minDays) {
    cout << "Searching..." << endl;
    cout << "\nClients with " << minDays << " or more: \n";

    bool dayFound = false;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].isOccupied && !table[i].isDeleted) {
            ClientStatus client = table[i].value;
            if (client.lastContacted < minDays) continue;

            cout << "\nID: " << table[i].key;
            cout << " | Subscription: " << client.subscription;
            cout << " | Days since last contact: " << client.lastContacted << endl;
            cout << "-------------------------------------------------------------";

            dayFound = true;
        }
    }

    if (!dayFound) {
        cout << "No matches";
    }
    cout << "" << endl;
}

//here i create a remove function that labels a slot as isDeleted
bool HashTable::remove(int key) {
    int hashCode = hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = (hashCode + i * i) % TABLE_SIZE;
        //stop if slot is not in use
        if (!table[index].isOccupied && !table[index].isDeleted) {
            cout << "Client ID " << key << " not found.\n";
            return false;
        }
        //update bucket values if key matches
        if (table[index].isOccupied && table[index].key == key) {
            table[index].isOccupied = false;
            table[index].isDeleted = true;
            return true;
        }
    }
    cout << "Client ID " << key << " not found.\n";
    return false;
}


