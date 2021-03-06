/* asgn BY Jonathan Jackson,  CSCI 2170-001, Due: Midnight, Wednesday, 12/06/2017
 * PROGRAM ID:  linkedlistlocation.cpp / Linked List by Location
 * AUTHOR:  Jonathan Jackson
 * INSTALLATION:  MTSU
 * REMARKS:  This automated program reads in a DATA file and adds items
 * to a Linked List (hereby called "LList", ya know - less typing..)
 * 
 * The data file can do 4 functions, Insertion, Deletion, Retreiving (display 1 item)
 * or Printing (display all items in remaining list).
 * 
 * Error messages print if a function is invalid or value is invalid.
 * 
 * Program ends by releasing all RAM from program control.
 */

#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

typedef string ItemType;    //alias $TYPE later on

struct Node {
    ItemType data;      // contains data
    Node * next;        // contains ->next Node or NULL
};

typedef Node * NodePtr; // alias pointer 

void InsertByLocation(NodePtr &head, const ItemType &fruit, const int &loc, int &length);
void RetrieveByLocation(const NodePtr &head,const int &loc, const int &length);
void DeleteByLocation(NodePtr &head, const int &loc, int &length);
void PrintLocation(const NodePtr &head, const int &loc,const int &length);
void DestroyList(NodePtr &head);
void PrintList(NodePtr &head);

int main() {
    
    fstream myIn;   // DATA file OBJECT
    char command;   // operation to implement in program run
    string fruit;   // holds new fruit names
    int loc;        // location manipulation value
    int length = 0; // length of the LList
    
    NodePtr head = NULL;    // establish LList $head as declared NULL
    
    //open data file
    myIn.open("linkedlist.dat");
    assert(myIn);
    
    // read in all lines from data file
    // start with the $command to implement
    while(myIn >> command) {
    
        // if 'I' - Insert new fruit into LList
        // do +1 to length
        if (command == 'I') {
            myIn >> fruit >> loc;
                InsertByLocation(head, fruit, loc, length);
        
        // if 'D' - delete item from list
        // do -1 from length
        } else if (command == 'D') {
            myIn >> loc;
            DeleteByLocation(head, loc, length); 
        
        // if 'R' - print one item based on location
        // no change to $length
        } else if (command == 'R') {
            myIn >> loc;
            RetrieveByLocation(head,loc, length);
        
        // if 'P' - print from location to end of list
        // no change to $length
        } else if (command == 'P') {
            myIn >> loc;
            PrintLocation(head, loc, length);
        
        // anything other than these commands should get a HAL ERROR message
        } else {
            cerr << "uh.. I can't do that Dave.\n\n";
        }
    }
    
    myIn.close();   // close DATA file cleanly
    
    DestroyList(head);
    return 0;       // exit program cleanly
}

// Insert new Item into the LList location, add 1 to length if successful
void InsertByLocation(NodePtr &head, const ItemType &fruit,const int &loc, int &length) {
    
    NodePtr curPtr, prevPtr;    // setup 2 points for finding InsertionPt
    int currLoc = 1;            // set curPos to 1 since this list with a position of 1
    
    NodePtr newNode = new Node; // create new Node to INSERT
    newNode->data = fruit;      // assign $fruite to data-cell
    newNode->next  = NULL;      // set $next to $NULL
    
    // if the list is empty, make the newNode the $head
    if (head == NULL) {
        head = curPtr = newNode;
    
    //otherwise, Insert newNode somewhere in the list
    } else {
        
        if (loc > length+1) {
            cerr << "Invalid insertion location.\n";
            return;
        
        } else {
            curPtr = head;      // reset curPtr to the ListHead
            prevPtr = NULL;     // reset to default placement
        
            // while the end of list isn't reached && loc doesn't match current cell
            // traverse the list
            while(curPtr != NULL && loc <= length+1 && loc != currLoc) {
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
            // add $newNode to the end of the List
            } else if (curPtr == NULL) {
                prevPtr->next = newNode;
        
            // otherwise, add in between 2 cell locations in the List
            } else {
                prevPtr->next = newNode;
                newNode->next = curPtr;
            }
        }
    }
    length++; // +1 to $length last
}

// Remove an Item from LList (based on location), delete 1 from $length if successful
void DeleteByLocation(NodePtr &head, const int &loc, int &length) {
    
    NodePtr frontPtr, backPtr; // traverse the List
    int curLoc;    // tracks current Node location in List
    
    // if the list is empty
    // print ERROR message and return back to main program
    if (head == NULL) {
        cerr << "This list is empty. There's nothing to delete.\n";
        return;

    } else {
        curLoc = 1;         // set default location to 1
        frontPtr = head;    // set frontPtr back to $head // (*this).Reset()
        backPtr = NULL;     // set backPtr to catch if head is intended deletion
        
        // while the end of LList isn't reached, keep moving through it
        while (frontPtr != NULL && loc <= length+1 && curLoc != loc) {
            backPtr = frontPtr;
            frontPtr = frontPtr->next;
            curLoc++;   // add +1 to counter to keep track of current Node #
        }
        
        // 1st Node (head) is the targetDeletion
        if(backPtr == NULL) {
            head = head->next;  // move head to ->next position
            delete frontPtr;    // release memory
            frontPtr = NULL;    // reset to 0
        
            // item isn't in list, print ERROR message
        } else if (frontPtr == NULL) {
            cerr << "Value wasn't in the list.\n";
        
            // or delete from middle of list and shift pointers to fix.
        } else {
            backPtr->next = frontPtr->next;
            delete frontPtr;
            frontPtr = NULL;
        }
    }
    length--;   // decrease $length by 1 last.
}

// Print 1 $item based on location in LList
void RetrieveByLocation(const NodePtr &head,const int &loc, const int &length) {
    
    NodePtr frontPtr, backPtr;      // NodePtrs to travel list or check for targetValue
    int curLoc;                     // current location in Node #s
    
    // if list is empty, print ERROR message
    if (head == NULL) {
        cerr << "Nothing to retrieve, list is empty.\n";
        return;
    
    } else {
        curLoc = 1;         // set default location to 1
        frontPtr = head;    // set frontPtr default location to $head
        backPtr = NULL;     // set backPtr to NULL, check is $head is targetValue
        
        
        // move frontPtr forward while finding the target location
        while (frontPtr != NULL && loc <= length && curLoc != loc) {
            backPtr = frontPtr;         // save old position, in case frontPtr exceeds list
            frontPtr = frontPtr->next;  // move frontPtr to next cell
            curLoc++;                   // increment the counter to track Node #
        }
        
        // on the off-chance the $loc value isn't valid.. prep an ERROR message
        if (frontPtr == NULL) {
            cerr << "Location isn't valid. :(\n";
        
        // show current $fruit in Node-data cell
        } else {
            cout << "Retrieved: " << frontPtr->data << endl;
        }
    }
}

// Find a $targetLocation in the LList
// Once found, print a header and all remaining $items in the LList
// use "->" to separate items.
void PrintLocation(const NodePtr &head,const int &loc,const int &length) {

    NodePtr frontPtr, backPtr;    // NodePtrs to travel list or check for targetValue
    int curLoc = 1;             // current location in Node #s
    
    // if LList is empty, print ERROR
    if (head == NULL) {
        cerr << "This list is empty.\n";
    
    } else {
        frontPtr = head;  // set firs
        backPtr = NULL;
        
        // find the location to start printing from
        while(frontPtr != NULL && loc <= length && curLoc != loc) {
            backPtr = frontPtr;         // set backPtr to old Ptr location
            frontPtr = frontPtr->next;  // move frontPtr ahead by 1-cell
            curLoc++;       // increament Node #
        }
        
        // print header
        cout << "The list is : ";
        
            // print remaining items in list
            while(frontPtr != NULL) {
                cout << frontPtr->data;     // print item in list
                frontPtr = frontPtr->next;  //keep traveling to end of LList
                
                // print "->" while there ARE more $items to print.
                if (frontPtr != NULL)
                    cout << "->";
            }
    }
    cout << endl;       // new line for readability
}

// Destroy the LList and release memory back to system
void DestroyList(NodePtr &head) {

    NodePtr delPtr; // holds onto Node pre-deletion
    
    // go through entire list
    while (head != NULL) {
        delPtr = head;      // assign $oldHEAD to delPtr for target deletion
        head = head->next;  // move head safety up one cell
        
        delete delPtr;      // release memory
        delPtr = NULL;      // set old memory to NULL
    }
    
    delete head;            // release last head node memory
    head = NULL;            // set old memory to NULL
}

// DEBUGGING function - LEGACY
// Confirms/Debugs current LList items/order
void PrintList(NodePtr &head) {
    NodePtr cur = head;     // create new pointer for travling the LList
    
    cout << "The list is: ";    // header
    
    // while there are valid Nodes in the list, travel through them
    while(cur != NULL) {
        cout << cur->data << " -> ";    // print $cur data
        cur = cur->next;                // move $cur on to the next cell
    }
    cout << endl;
}
