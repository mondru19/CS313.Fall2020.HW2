#include<iostream>
#include<chrono>
#include<time.h>
#include "linkedStack.h"

using namespace std;
//needed for chrono, to calculate how much that this program takes to compile the whole code
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
int main()
{
    auto begin = steady_clock::now();

    srand(time(NULL));
    //We can't initialize the size of the stack for the linked list unlike the array based stack
    linkedStackType<int>originalStack; 
    

    originalStack.initializeStack(); //Initialize the stack to an empty stack before we can throw anything in
    //to check if I initialized the stack or not, at first we should be checking it before we add elements in the stack
    if(originalStack.isEmptyStack())
    {
        cout<< "The linked list stack should be empty at first because we initialize it to 0";
    }
    else
    {
        "I did something wrong if this comes out.";
    }
    cout << endl;
    // I added 10 elements to this stack to compare it with array based stack
    originalStack.push(1);
    originalStack.push(2);
    originalStack.push(3);
    originalStack.push(4);
    originalStack.push(5);
    originalStack.push(6);
    originalStack.push(7);
    originalStack.push(8);
    originalStack.push(9);
    originalStack.push(10);
    
    //This is to check what is the top of the stack is, the lastest element that is added to the stack
    if(!originalStack.isEmptyStack())
    cout << "The top of the stack is: " << originalStack.top();
    cout << endl;
    
    //to print out all the elements of the stack.
    //First we do while loop,as long as the stack is not empty
    //we keep popping the stack from the top to the bottom of the stack
    //and print them
    while(!originalStack.isEmptyStack())
    {
        cout << originalStack.top() << " ";
        originalStack.pop(); //Pop the stack
        cout << endl;
    }
    cout << "end of first stack";
    cout << endl;

    //to check if the stack if the stack is full or not
    //since linked list stack will never be full, it only full when we have memory shortage, but when we do so, the program will not even compile
    if(originalStack.isFullStack())
    {
        cout << "Stack is full";
    }
    else 
    {
        cout << "my stack will never be full!";
    }
    cout << endl;
    
    //the end of the stack    
    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - begin);

    cout << duration.count() << " milliseconds.";
    return 0;

}
