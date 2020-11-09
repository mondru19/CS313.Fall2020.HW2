//Header File: linkedStack.h 

#ifndef H_StackType
#define H_StackType
 
#include <iostream>
#include <cassert> 
 
#include "stackADT.h"

using namespace std;

//Definition of the node 
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedStackType: public stackADT<Type>
{
public:
    const linkedStackType<Type>& operator=
                              (const linkedStackType<Type>&);
      //Overload the assignment operator.

    bool isEmptyStack() const;
      //Function to determine whether the stack is empty.
      //Postcondition: Returns true if the stack is empty;
      //               otherwise returns false.

    bool isFullStack() const;
      //Function to determine whether the stack is full.
      //Postcondition: Returns false.

    void initializeStack();
      //Function to initialize the stack to an empty state. 
      //Postcondition: The stack elements are removed; 
      //               stackTop = nullptr;

    void push(const Type& newItem);
      //Function to add newItem to the stack.
      //Precondition: The stack exists and is not full.
      //Postcondition: The stack is changed and newItem 
      //               is added to the top of the stack.

    Type top() const;
      //Function to return the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: If the stack is empty, the program 
      //               terminates; otherwise, the top 
      //               element of the stack is returned.

    void pop();
      //Function to remove the top element of the stack.
      //Precondition: The stack exists and is not empty.
      //Postcondition: The stack is changed and the top 
      //               element is removed from the stack.

    linkedStackType(); 
      //Default constructor
      //Postcondition: stackTop = nullptr;

    linkedStackType(const linkedStackType<Type>& otherStack); 
      //Copy constructor

    ~linkedStackType();
      //Destructor
      //Postcondition: All the elements of the stack are 
      //               removed from the stack.

private:
    nodeType<Type> *stackTop; //pointer to the stack

    void copyStack(const linkedStackType<Type>& otherStack); 
      //Function to make a copy of otherStack.
      //Postcondition: A copy of otherStack is created and
      //               assigned to this stack.
};


//Default constructor

//First we initialize the stackTop to nullptr or an empty place.
template <class Type> 
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr; //assign stackTop to nullptr
}

//we check if the stack isEmpty. The stack only empty when the stackTop pointing to nullptr, otherwise is not
template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr); //because the function is boolean,we have to have return and it is stackTop == nullptr
} //end isEmptyStack

//The stack will never be full, unless we have memory shortage, therefore the stack will be full.
//We deallocated and allocated the stack dynamically
template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    return false; //the value always false becasue it will never be full
} //end isFullStack

//This class function is used for re-initializing the stack to an empty stack, so that we dont have a memory leak in the program by deallocating after reinitalize the stack
//we first assign temp to stackTop
//we then point the stackTop to the next node
//and deallocate the memory that is now empty , that was used by stackTop earlier/temp
template <class Type>
void linkedStackType<Type>:: initializeStack()
{
    nodeType<Type> *temp; //pointer to delete the node

    while (stackTop != nullptr)  //while there are elements in 
                              //the stack
    {
        temp = stackTop;    //set temp to point to the 
                            //current node
        stackTop = stackTop->link;  //advance stackTop to the
                                    //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack

//This class is function is use when we want to add a new element to the stack, by making a new node and we point the stackTop to the new top,
//so that the new element will be at the top of the stack
template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type> *newNode;  //pointer to create the new node

    newNode = new nodeType<Type>; //create the node

    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the 
                              //top node
} //end push

//This function is use when we want to find the value of the top of the stack. Not the address of the memory
template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr); //if stack is empty,
                              //terminate the program
    return stackTop->info;    //return the top element 
}//end top

//pop class function is used when we want to retrieve/pop/remove the top of the stack element.
//first we assign a tempt value to the top of the stack and point the top of the stack to the next node
//after that we delete the top of the stack, therefore the element in the next node becomes the new top of the stack
template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type> *temp;   //pointer to deallocate memory

    if (stackTop != nullptr)
    {
        temp = stackTop;  //set temp to point to the top node

        stackTop = stackTop->link;  //advance stackTop to the 
                                    //next node
        delete temp;    //delete the top node
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

//copyStack function is use when we want to copy all the elements in that stack to a new stack
//the function uses 3 parameters, newNode, *current, and *last
template <class Type> 
void linkedStackType<Type>::copyStack
                     (const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;

    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();

    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;  //set current to point
                                   //to the stack to be copied

            //copy the stackTop element of the stack 
        stackTop = new nodeType<Type>;  //create the node

        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
                                //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
                                    //the next node

            //copy the remaining stack
        while (current != nullptr)
        {
            newNode = new nodeType<Type>; //create new node for the other stack

            newNode->info = current->info; //copy the node info/value
            newNode->link = nullptr; //point it to the NULL/nullptr
            last->link = newNode; //the last link becomes the new node
            last = newNode; // last node is the new node
            current = current->link; //the current variable is pointing to the new node
        }//end while
    }//end else
} //end copyStack

    //copy constructor
    //we do not need a deep copy for this copy constructor, therefore just by copying the value is enough for us to get it.
template <class Type>   
linkedStackType<Type>::linkedStackType(
                      const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}//end copy constructor

//destructor
//destructor so that we do not have any memory leak, therefore we always delete the memory after we used it
template <class Type> 
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}//end destructor

//overloading the assignment operator
template <class Type>   
const linkedStackType<Type>& linkedStackType<Type>::operator=
    			  (const linkedStackType<Type>& otherStack)
{ 
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);

    return *this; 
}//end operator=

#endif