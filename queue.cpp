#include "Queue.h"
#include "clients.h"

Queue::Queue() {
    front = nullptr;
    end = nullptr;
}

Queue::~Queue() {
    while (front != nullptr) {
        QueueNode* nodeToDelete = front;
        front = front->next;
        delete nodeToDelete;
    }
}

void Queue::Enqueue(const AllClientData* newClient) {
    QueueNode* newNode;
    newNode = new QueueNode(newClient);
    if (nullptr == front) {
       front = newNode;
    }
    else {
       end->next = newNode;
    }
    end = newNode;
 }
 
 bool Queue::Dequeue() {
    if (front == nullptr) {
        return false;
     }
     QueueNode* nodeToDelete = front;
     front = front->next;
 
    if (front == nullptr) {
       end = nullptr;
    }
    
    delete nodeToDelete;
    return true;
 }

 //adding a method to display the queue. using logic from printdeletedclients().
 void Queue::PrintQueueClients() const {
    QueueNode* current = front;

    if (!front) {
        cout << "Queue is Empty" << endl;
        return;
    }

    while (current) {
        current->data->print();
        current = current->next;
    }
}
