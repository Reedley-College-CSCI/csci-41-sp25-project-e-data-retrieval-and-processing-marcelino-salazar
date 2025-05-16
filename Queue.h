#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

using namespace std;

class AllClientData; //adding forward declaration

// Node to store an item in a linked-list-based queue
class QueueNode {
public:
   const AllClientData* data;
   QueueNode* next;
   
   QueueNode(const AllClientData* clientData, QueueNode* nextNode = nullptr) {
      data = clientData;
      next = nextNode;
   }
};

class Queue {
    private:
       QueueNode* front;
       QueueNode* end;
    
    public:
       Queue();
       ~Queue();

       void Enqueue(const AllClientData* newClient);
       bool Dequeue();
       void PrintQueueClients() const;
};
#endif