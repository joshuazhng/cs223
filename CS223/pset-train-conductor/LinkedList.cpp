/*
 * LinkedList.cpp
 * Joshua Zhang
 * CPSC 223 PSET 4
 * 4/6/23
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList(){
    length = 0;
    head = NULL;
    currPos = NULL;
}

// Destructor
LinkedList::~LinkedList() {
    makeEmpty();
}

// Assignment operator overloading
// Don't change anything here. This is needed for copying objects.
LinkedList & LinkedList::operator = (const LinkedList &l){
    NodeType *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    currPos = NULL;
    if (l.head == NULL)
        head = NULL;
    else{
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL){
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::getLength() const{
    return length;
}

// Input: nothing
// Returns: true if currPos is NULL
// Does: determines if currPos is NULL or not
bool LinkedList::isCurrPosNull() const{
    return currPos == NULL;    
}

// Input: a Station s
// Returns: void
// Does: inserts the given station into the head of the list
void LinkedList::insertStation(Station s){
    struct NodeType *newNode = new NodeType();
    newNode->info = s;
    newNode->next = head;
    head = newNode;
    length++;
}

// Input: a Station s
// Returns: void
// Does: deletes the first instance of a station that is in the list
//       and isEqual to the one given as part of the input
void LinkedList::removeStation(Station s){
    struct NodeType *temp = head;
    struct NodeType *prev = NULL;

    if (temp != NULL && temp->info.isEqual(s)) {
        head = temp->next;
        delete temp;
        length--;
        return;
    }

    while (temp != NULL) {
        if (temp->info.isEqual(s)) {
            if (temp == currPos) {
                currPos = NULL;
            }
            prev->next = temp->next;
            delete temp;
            length--;
            return;
        }

        prev = temp;
        temp = temp->next;
    }

}


// Input: none
// Returns: a Station
// Does: return the next station in the list, using the private 
//       variable currPos to determine which station to return
Station LinkedList::getNextStation(){

    if (currPos == NULL) {
        if (head != NULL) {
            currPos = head->next;
            return head->info;
        }
        else {
            return Station();
        }
    } else {
        Station temp = currPos->info;
        if (currPos->next == NULL) {
            currPos = NULL;
        } else {
            currPos = currPos->next;
        }
        return temp;

    }
}

// Input: none
// Returns: void
// Does: reset the private variable currPos
void LinkedList::resetCurrPos(){
   currPos = NULL;
}

// Input: none
// Returns: void
// Does: delete all elements in the list and deallocate any allocated memory
void LinkedList::makeEmpty(){
    currPos = head;
    while (currPos != NULL) {
        NodeType *tmp = currPos->next;
	    delete currPos;
	    currPos = tmp;
    }
    length = 0;
    currPos = NULL;
    head = NULL;
}

// Input: a reference to an ostream object
// Returns: void
// Does: prints all the stations in the list in order from
//       front to the end in format specified by the spec
void LinkedList::print(ostream &out){
    if (length == 0) {
        out << endl;
    }

    currPos = head;
    for (int i = 0; i < length; i++) {
        currPos->info.print(out);
        out << " ";
        out << length - i - 1;
        if (i != length - 1) {
            out << " == ";
        }
        else {
            out << endl;
        }
        currPos = currPos->next;
    }
}



