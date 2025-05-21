Project E: Final Project README Template https://docs.google.com/document/d/17Az_AHa-gM9LTTaxsluxZeOYsABpuxP7GCHUl9T-sOI/edit?usp=sharing
Important Instructions
Do not delete your previous README content.
First, copy and paste your existing README text into the section titled Prior README Content below.
Then, work through this template to add the required new sections for Project E.
Update your README so that it reflects your FINAL project, following the rubric and prompts.


Prior README Content
Paste your previous README here (from Project A/B/C/D) before making any changes.

Project A:
Dynamic Array Implementation & Ability to add items:

I created a class "Clients" that dynamically allocates an array of AllClientData objects (clientFile = new AllClientData[capacity];). I also implemented a destructor that deallocates memory from the dynnamic array to prevent memory leaks. Within the addClient() function I created a new dynamic array with 1 space appended to store new client file. I used a loop to iterate through each existing client file and copy it to the newCientArray. I had to make sure I deleted the memory that was previously allocated for client file and re-assign clientFile with the newClientArray created. Then I updated the array size for the next iteration.
Reading data from external file:

I declared a ifstream class named "file" to open the external file bank_full.csv and declared a string class object named "line" to store values extracted. I use the getline() function to store rows from the external file into "line" and used a for loop to read in capacity number of rows from the external file. I declared a stringstream class named "parse" which splits values from rows stored in "line" variable into individual strings.
Data Organization with Structs and Classes:

I created a class named "Clients" to encapsulate multiple structs where the last struct is nested with the previous 3. I did this after getting feedback to better organize the data members. I grouped related data members in seprate structs. I used int & string types. I used getline() and stringstream to parse and store CSV data into struct members.
User Interface:

I include a main menu interface in the main body to display 5 options/operations to the user. I made it very user friendly with simple prompts. I organized the output results for readability. I keep the main menu open using a while loop until the user exits the program by inputting 5.
Data Search Functionality:

I created search capabilities for a client by ID in the search() function. I used a for loop to iterate over the dynamic array and compare IDs (if (clientFile[i].clientInfo.id == idSearch)). I displayed full client details if a match is found and an error message if no match is found. I used a linear algorithm but will adjust to use a binary search since I am using a large data set
Data Validation and Error Handling:

Based on feedback from the stand up video, I implemented nested structures under struct "ClientRecord" to better organize my code and improve readability. To do this I created multiple structs that group related information rather than having all data members in one struct. I also renamed my variables to improve logic and readabilty. For example I changed pointer variable Client* clients to AllClientData* clientFile;

Project B:
None

Project C:
Queue Implementation: The purpose of it is to store recently added clients and create a follow up queue list. Queue is defined in Queue.h and Queue.cpp. The Queue class contains QueueNode, which stores a pointer to a AllClientData object. An object of the Queue class is declared in the Clients class as a private member (followupQueue)

Enqueue operation: The purpose of it is to add recently added client to followupQueue. Enqueue() is defined in Queue.cpp and called using enqueueClient(from the Clients class) defined in client.cpp. Enqueue() adds a node to the end of the linked list.

Dequeue operation: The purpose of it is to remove the client at the front of followupQueue. Dequeue() is defined in Queue.cpp and called using dequeueClient(from Clients Class) defined in client.cpp. Dequeue() updates the front pointer and deletes the node.

Display operation: The purpose of it is to display clients in followupQueue PrintQueueClients() is defined in Queue.cpp and called using printQueue(from Clients Class) defined in client.cpp. PrintQueueClients() traverses the linked list and prints each client 0(n).

Menu options for stack or queue management: (Includes options to add, remove, and display items in the queue.) in main() options 8,9,10. Uses Clients methods enqueueClient(), dequeueClient(), and printQueue() to call Enqueue(), Dequeue(), and PrintQueueClients().

Integration with previous functionalities: (UI seamlessly integrates stack or queue management with sorting, linked list, and other features.) The queue uses this same client object clientFile as addClient() and stores a pointer to (AllClientData*)

Project D:

(Clear explanation of hash table operations, hashing function, collision handling, and time complexities.)


1. Hash Table Implementation:

   - Correct hash table structure implementation:(Hash table is implemented correctly, and data is stored and retrieved efficiently.)
      The hash table is implemented in hashtable.cpp and HashTable.h. I used a struct for ClientStatus, Bucket, and HashTable. The hashtable dynamically resizes when full and supports insertion, search, display, and removing clients based on their ID and subscription follow-up status.
   
   - Hashing function implementation:(Uses a suitable hashing function to distribute keys effectively.)
      Inside the HashTable.h under HashTable class. The hash function I used is a simple modulus operation on the client's ID (key):

      int hash(int key) const {
         return key % TABLE_SIZE;
      }
      This ensures distribution of keys within the bounds of the current table size.

   - Collision handling:(Implements proper collision handling using chaining or open addressing.)
      I used quadratic probing to handle collisions. When a collision occurs the index is incremented using the following code:
      index = (hashNum + i * i) % TABLE_SIZE;
      This reduces clustering and spreads out entries more evenly.

2. User Interface
   - Menu options for hash table management:(Includes options for adding, searching, removing, and displaying items.)
      All menu options are found inside clients.cpp under, Clients::followUps(HashTable& hashTable) function.

3. Integration with previous functionalities:
   - (UI seamlessly integrates hash table management with functionalities from previous projects.)
      AllClientData* is used to insert clientInfo, clientBankInfo, & campaignInfo when needed and to overwrite external csv when updating values (day, month, subscription status, etc.)

   - (Hash table interacts meaningfully with other components, such as linked list or dynamic array.)
      The hashtable relies on dynamic array clientFile[] from AllClientData for inserting, removing, and updating

   - Time complexity reporting:(Accurate explanation of time complexities for hash table operations in README.mdLinks to an external site.)
                 Best:     Worst:
      Insert():	O(1)	   O(n) (due to collisions and resizing)
      Search():	O(1)	   O(n) (probing through filled or deleted slots)
      Remove():	O(1)	   O(n) (worst case search before marking as deleted)


   - Handling of edge cases:(Handles cases like collisions, searching/removing non-existent items, and edge scenarios robustly.)
      In the insert() when no empty slots are found, the table is resized (doubled) and all entries are rehashed to new positions. I use cin.fail() in most inputs, range checks for day input, and string validation for month input which all prevent crashes or incorrect data.


Project E
Student Info
Name: Marcelino Salazar
Repository: https://github.com/Reedley-College-CSCI/csci-41-sp25-project-e-data-retrieval-and-processing-marcelino-salazar.git


Project Summary
Brief overview of your application:
This application is a database that manages data from a marketing campaign. It stores personal, banking, and marketing information about each individual client. The purpose of the application is to track the performance of a marketing campaign and identify clients who have not subscribed to the service, which allows marketers to follow up with those specific clients and increase subscriptions.

What does your program do?
The program has adding, removing, restoring, sorting, 

What kind of data does it process?
The program processes the following:
Personal information (age, job, marital status, education)
Banking information (account balance, default history, loan status)
Marketing information (previous campaign contacts, subscription status, and follow-ups)

What problem does it solve or what functionality does it provide?
This program addresses the challenge of efficiently managing and analyzing large sets of client data from marketing campaigns. By organizing data and identifying clients who have not yet subscribed, it provides marketers with actionable insights to improve campaign effectiveness. Additionally, the program simplifies client data management through dynamic memory handling, efficient search algorithms, and structured data reporting, ultimately saving time and improving decision-making.




Requirements Checklist and Where They Are Met
Area
How Requirement Is Met
File/Class
Add/Remove
Used dynamic arrays to add/remove clients, trash bin implemented via a singly linked list, removed clients added to trash bin, restored clients returned to active list.
clients.cpp
Data Structures
Hash Table for fast client lookup, Queue for recently added clients, Singly Linked List for trash bin, Dynamic Array for primary storage.
HashTable.h, Queue.h, clients.h
Input Validation
Input validation added for numeric ranges (validIntInput), yes/no responses, and multi-word string inputs using getline().
clients.cpp
Security Checklist
Used input validation to prevent buffer overflows and invalid memory access, and proper deletion of dynamic arrays to prevent memory leaks.
clients.cpp
Ethics Checklist
Program prompts for clear and accurate user input, discourages invalid data entry, and ensures transparency in client data handling.
N/A
Advanced Techniques
Pointers for dynamic memory management, Custom hash table implementation, Queue and linked list structures.
clients.cpp, hashtable.cpp, queue.cpp
Searching and Sorting
Linear search by ID, Hash Table search for O(1) lookup, QuickSort for sorting clients by balance.
clients.cpp, hashtable.cpp
Algorithm Complexity
Hash Table search: O(1) average, O(n) worst case; QuickSort: O(n log n) average, O(n²) worst case; Linked List operations: O(n).
clients.cpp, hashtable.cpp
User Interface
Menu has clear prompts and options along with error messages guide correct input; follow-up and queue menus included.
project_e_marcelino_salazar.cpp, clients.cpp
Modularity
Separated by: clients, hash table, queue, sorting tracker, and main.
[Multiple files]
Readability
I provided consistent commenting, descriptive variable names, formatted output, and logical code grouping.
All files
README
[This document; covers all Project E requirements]
README.md



Changes from Previous Projects and Code Reviews
From Project C:
Extended hash table to store all clients, not just unsubscribed ones.


Added trash bin functionality using a singly linked list.

From Project D:
Integrated a working Queue for recently added clients.


Input validation and error handling significantly improved.

From most recent code review:
Improved user interface with clearer prompts.

Added multi-word input handling using getline().

Enhanced hash table display formatting.

Input validation for yes/no and numeric fields added.

Data Structures Used
Primary:

Hash Table (for fast client lookup).

Dynamic Array (for storing client records).

Secondary:

Singly Linked List (trash bin).

Queue (recently added clients).

Why Chosen: The hash table allows fast search by client ID. Queue models FIFO behavior for tracking recently added clients, and the linked list allows easy add/remove of deleted clients for restoration.
Alternatives Considered: [Optional]


Algorithm Time Complexities (include major algorithms--you might have multiple searches, etc.)
Operation
Algorithm Used
Big-O Complexity
Notes
Search
Hash Table (Quadratic Probing)
O(1)


Sort
QuickSort
O(n log n) 


Trash Bin
Linked List
O(n)





Ethics Checklist

Potential Harms to the Public:
Incorrect or incomplete data could lead to misinterpretation, which may lead to poor decision making and unfair targeting of certain client groups.
Prompt: What could go wrong if your data were wrong, misused, or misunderstood?

How Harms Were Addressed:
Input prompts were carefully designed to encourage correct and complete data entry, reducing errors during data collection.
Prompt: What measures did you add to avoid harming users?

Positive Contribution to the Public:
Provides actionable insights that can improve campaign success, saving time and financial resources.
Prompt: How does your project make people's lives better or more informed?

Who Exactly Is the Public:
Marketing professionals, campaign managers, CEO.
Prompt: Who benefits most from your program?


Security Checklist
Example Only:
The following is a sample format and summary depth expected.
You must create a checklist that matches your own project's fields and risks.

Data
Sensitivity
Impact
Confidentiality
Integrity
Availability
Client ID
Low
High
Medium
High
High
Age
Low
Low
Low
High
High
Job
Low
Low
Low
High
High
Marital Status
Low
Low
Low
Medium
High
Education
Low
Low
Low
Medium
High
Default History
High
Medium
High
High
Medium
Balance
High
Medium
High
High
Medium
Housing
High
Medium
High
High
Medium
Loan
High
Medium
HIgh
High
Medium
Contact Type
Low
Low
Low
Medium
Medium
Day of Contact
Low
Medium
Low
High
High
Month of Contact
Low
Medium
Low
High
High
Duration
Low
Low
Low
Low
Low
Pdays
Low
Medium
Low
High
High
Subscription Status
Low
High
Low
High
High
Follow-ups
Low
Medium
Low
Medium
Medium


Security Considerations Summary:

Client ID:
Public information, but can be linked with sensitive data (Bank Info). Ensure ID is only displayed when necessary.

Age:
Low sensitivity but should be protected to prevent profiling or bias in marketing strategies. Validate input for accuracy.

Job:
Could result in inaccurate profiling. Validate input for accuracy.

Marital Status:
Could result in inaccurate profiling. Store securely. Limit access. Avoid including in public reports.

Education Level:
Could result in inaccurate profiling. Validate input for accuracy.
.
Default HIstory:
Highly sensitive financial data. Encrypt or restrict access. Display only when necessary for analysis.

Balance:
High risk of financial profiling or fraud. Encrypt or restrict access. Display only when necessary for analysis.

Housing:
Can be used for financial profiling or scams. Store securely and limit access.

Loans:
Highly sensitive if included. Risk of financial harm. Encrypt or restrict access to authorized personnel only.
 
Contact Type:
Could reveal behavioral patterns. Store securely and limit access.

Day of Contact:
Could reveal behavioral patterns. Store securely and limit access.

Month of Contact:
Could reveal behavioral patterns. Store securely and limit access.

Duration of Call:
Could reveal behavioral patterns. Store securely and limit access.

Pdays:
Could reveal behavioral patterns. Store securely and limit access.

Subscription Status:
Reveals service preferences and risk of scams. Restrict access. Use only for targeted marketing efforts.

Follow-ups:
Could reveal behavioral patterns. Store securely and limit access.

Prompt: For each data type you collect, ask:

Could leaking this data hurt someone?
What steps protect the data's confidentiality, accuracy, and availability?


How to Compile and Run
g++ clients.cpp queue.cpp hashtable.cpp project_e_marcelino_salazar.cpp -o project_e && ./project_e


Known Issues or Future Enhancements
[e.g., Planned improvements or current limitations]



