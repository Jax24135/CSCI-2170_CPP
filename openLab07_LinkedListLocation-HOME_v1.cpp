/*
 * working on display
 * only printing last item in list

*.dat
I apple 1
I pear 2
I strawberry 1
I peach 2
I watermelon 3

*/

        
        
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

typedef string ItemType;

struct Node {
    ItemType data;
    Node * next;
};

typedef Node * NodePtr;

void InsertByLocation(NodePtr &head,string fruit, int targetLoc, int &length);
void PrintList(const NodePtr &head);

int main()
{

    fstream myIn;
    NodePtr head = NULL;        // create new list $head

    char targetOp = 'n';         // target operation (Insert, Delete, Print, Retrieve)
    string fruit = "None";
    int targetLoc = -1;                // location
    int length = 0;
    
    
    
    myIn.open("linkedlist.dat");
    assert(myIn);
    
    if(myIn >> targetOp) {
        
        
        if (targetOp == 'I') {
            fruit = "none"; // cleanse palette
            targetLoc = -1; // cleanse palette
            myIn >> fruit >> targetLoc;
            InsertByLocation(head, fruit, targetLoc, length);
        }
        
    }
    
    myIn.close();
    
    
    PrintList(head);
    
    
    return 0;
}

void InsertByLocation(NodePtr &head,string fruit, int targetLoc, int &length) {
    
    NodePtr prevPtr, curPtr;
    prevPtr = NULL;
    
    NodePtr newNode = new Node;
    newNode->data = fruit;
    newNode->next = NULL;
    
    if (head == NULL || length == 0) {
        head = curPtr = newNode;        // set $head && curPtr to 1st Node
    } else {
        
        // if target insertion destination isn't valid.. quit loop
        if (targetLoc < 1 || length < targetLoc) {
            cerr << "hmm... that's an invalid location.\n";
        } else {
 
            // otherwise, find the intedended
            int counter = 1;
            while (counter != targetLoc && targetLoc <= length) {    //
                prevPtr = curPtr;
                curPtr = curPtr->next;
                counter++;
            }
        
            // add newNode at intended location, between prevPtr && curPtr
            newNode->next = curPtr;
            prevPtr->next = newNode;
        
            prevPtr = NULL; // reset to default
            curPtr = head;  // reset to default

        }
    // either way, increase $length by +1
    length++;
    }
}
    
void PrintList(const NodePtr &head) {
    
    NodePtr tmpPtr = head;
    
    while (tmpPtr != NULL) {
        cout << tmpPtr->data << endl;
        tmpPtr = tmpPtr->next;
    }
}