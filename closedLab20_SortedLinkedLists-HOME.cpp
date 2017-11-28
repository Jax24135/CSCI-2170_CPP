// fill in the blank area

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ListItemType;

struct Node {
    ListItemType data;
    Node * next;
};

typedef Node * NodePtr;

// Declare the function "BuildSortedList" here
void BuildSortedList(NodePtr &head);

// Declare the function "SortedListInsert" here
void SortedListInsert(NodePtr &head, ListItemType item);

// Declare the function "DisplayList" here
void DisplayList(NodePtr &head);

// Declare the function "DestroyList" here
void DestroyList(NodePtr &head);

int main() {
    
    NodePtr head = NULL;

    // call function "BuildSortedList" to read data from the data file and
    // construct the list
    BuildSortedList(head);

    // call function "DisplayList" to display the list
    DisplayList(head);
    
    // call function "DestroyList" here
    DestroyList(head);

return 0; }

// define the function "BuildSortedList" below
// Write a "while" loop to read position-item pairs from the data file.
// insert the item into the list at the specified position. Call "SortedListInsert" function for insertion.
// The loop terminates when the end of the data file is reached.

void BuildSortedList(NodePtr &head) {
    ifstream myIn;
    ListItemType item;
    int counter=0;
    
    NodePtr tmp, currPtr;
    
    myIn.open("produce.dat");
    assert(myIn);
    
    while (myIn >> item) {
        tmp = new Node;
        
        tmp->data = item;
        tmp->next = NULL;
        
        if (head == NULL)
            head = currPtr = tmp;
        else
            SortedListInsert(head, item);
            
    }
    myIn.close();
}

// define the function "SortedListInsert" below
void SortedListInsert(NodePtr &head, ListItemType item) {
    NodePtr newPtr, frontPtr, backPtr;
    
    
    newPtr = new Node;
    newPtr->data = item;
    newPtr->next = NULL;
    
    if (head == NULL) {
        head = frontPtr = newPtr;
    }
    else {
        
        frontPtr = head;
        backPtr = NULL;
        while (frontPtr != NULL && frontPtr->data < item) {
            backPtr = frontPtr;
            frontPtr = frontPtr->next;
        }
        
        // if an empty list, make the newNode the $head
        if (backPtr == NULL)
            head = newPtr;
        
        // otherwise, add newNode to the middle of the list
       else
           backPtr->next = newPtr;        
        
        newPtr->next = frontPtr;
       
        
        // if
        if (frontPtr == NULL)
            frontPtr = newPtr;
    }
}

// define the function "DisplayList" below
void DisplayList(NodePtr &head) {
    NodePtr currNode = head;
   
    while (currNode != NULL) {
        cout << currNode->data << endl;
        currNode = currNode->next;
    }
}


// define the function "DestroyList" below
void DestroyList(NodePtr &head) {
    NodePtr frontPtr, backPtr;
          
    //frontPtr = head;
    //backPtr = NULL;
        
    if (head == NULL) {
        delete head;
    } else {
        frontPtr = head;
        backPtr = NULL;
        
        while(frontPtr != NULL) {
            backPtr = frontPtr;
            frontPtr = frontPtr->next;
            delete backPtr;
            //cout << "item destroyed\n";
        }    
    }
}