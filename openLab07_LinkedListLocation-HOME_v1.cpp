#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

typedef string ItemType;

struct Node {
    ItemType data;
    Node * next;
};

typedef Node * NodePtr;

void InsertByLocation(NodePtr &head, ItemType fruit, int loc, int &length);
void PrintList(NodePtr &head);
void PrintLocation(const NodePtr &head,const int loc,const int length);


int main() {
    
    fstream myIn;   // DATA file OBJECT
    char command;   // type of operation to do
    string fruit;   // holds new fruit names
    int loc;        // location manipulation value
    int length = 0; // length of the LList
    
    NodePtr head = NULL;    // establish LList $head
    
    //open data file
    myIn.open("linkedlist.dat");
    assert(myIn);
    
    while(myIn >> command) {
        
        if (command == 'I') {
            myIn >> fruit >> loc;
            InsertByLocation(head, fruit, loc, length);
        } else if (command == 'P') {
            myIn >> loc;
            PrintLocation(head, loc,length);
            
            
            
        }
    }
    
    //PrintList(head);
    
    return 0;
}

void InsertByLocation(NodePtr &head, ItemType fruit, int loc, int &length) {
    
    NodePtr curPtr, prevPtr;    // setup 2 points for finding InsertionPt
    int currLoc = 1;            // set curPos to 1 since SOMETHING will be the ListHEAD
    
    NodePtr newNode = new Node; // create new Node
    newNode->data = fruit;      // assign data to $fruit
    newNode->next  = NULL;      // set next to $NULL
    
    // if the list is empty, make the newNode the head
    if (head == NULL) {
        head = curPtr = newNode;
    
    //otherwise, Insert newNode somwhere in the list
    } else {
            curPtr = head;      // reset curPtr to the ListHead
            prevPtr = NULL;     // reset to default placement
        
            // while the end of list isn't reached && loc doesn't match current cell
            // traverse the list
            while(curPtr != NULL && loc != currLoc) {
                prevPtr = curPtr;
                curPtr = curPtr->next;
                currLoc++;  // add 1 to keep track of which cell we're in
            }
        
        // if the 1st cell is the target location
        // move currentHEAD up 1 cell, relink head to ->next
        // and replace head with newNode
        if(prevPtr == NULL) {
            newNode->next = head;
            head = newNode;
        
        // if the intended location isn't found by the end of the list
        // add to the end of the List
        } else if (curPtr == NULL) {
                prevPtr->next = newNode;
        
        // otherwise, add in between 2 cell locations in the List
        } else {
            prevPtr->next = newNode;
            newNode->next = curPtr;
        }
    }
    //this should be right before this function ends//
    //*DEBUGGER::*/ PrintList(head);
    //*DEBUGGER:*/ cout << endl << endl;
}

void PrintLocation(const NodePtr &head,const int loc,const int length) {
    NodePtr prevPtr, curPtr;
    int finder = 1;
    
    if (head == NULL) {
        cerr << "this list is empty.\n";
    } else {
        curPtr = head;
        
        // find the location to start printing from
        while(curPtr != NULL && finder != loc) {
            prevPtr = curPtr;
            curPtr = curPtr->next;
        }
        
        //starting printing items
        cout << "The list is : ";
        while(curPtr != NULL) {
            cout << curPtr->data;
            curPtr = curPtr->next;
            
            if (curPtr != NULL)
                cout << "->";
            
        }
    }
    cout << endl;
}



void PrintList(NodePtr &head) {
    NodePtr cur = head;
    cout << "The list is: ";
    while(cur != NULL) {
        cout << cur->data << " -> ";
        cur = cur->next;
    }
}
