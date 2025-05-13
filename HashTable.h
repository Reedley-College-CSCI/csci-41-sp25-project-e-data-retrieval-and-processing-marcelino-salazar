#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;

struct AllClientData;


//creating a struct to hold each clients sub status and last day contacted in each bucket.
struct ClientStatus {
    string subscription;
    int lastContacted;
};

//here I create a struct for bucket to store the key, client status, and whether the slot is occupied or deleted.
struct Bucket {
    int key;
    ClientStatus value;
    bool isOccupied;
    bool isDeleted;

    Bucket() {
        key = -1;
        isOccupied = false;
        isDeleted = false;
    }
};

//here I created a class with private members to set a table with 19 buckets and a function to place clients in buckets.
class HashTable {
    private:
        int TABLE_SIZE;
        Bucket* table;
    
        int hash(int key) const {
            return key % TABLE_SIZE;
        }
    public:
        HashTable();
        ~HashTable();
        bool insert(int key, const ClientStatus& value);
        void display() const;
        void unsubscribedClients(AllClientData* clientFile, int capacity);
        void searchPdays(int minDays);
        bool remove(int key); 
        int tableSize() {
            return TABLE_SIZE;
        }
    
    };    

#endif