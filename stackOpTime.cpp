#include<iostream>
#include<time.h>
#include "myStack.h"
#include<chrono>

using namespace std;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

int main()
{
    auto begin = steady_clock::now(); //to time how fast the program compile

    //I use random number to fill up the stack because is more efficient rather than push it one by one
    srand(time(NULL));

    //The size of my stacks will be 1000, therefore any more than that will be overloaded. it ONLY mean my particular stack can only fit 1000 elements.
    //The stack will never be full
    stackType<int>originalStack(10);
    stackType<int>secondStack(10);
    stackType<int>sameStack(10);
    
    originalStack.initializeStack(); //Initialize the top of the stack to be 0 because the stack still empty
    secondStack.initializeStack(); //Initialize the top of the stack to be 0 because the stack still empty

    //This operator is to test if the stack is empty at the beginning or not.
    //since I initializse the stack, it should be empty
    if(originalStack.isEmptyStack())
    {
        cout << "Stack is empty at the begining";
    }
    else 
    {
        cout << "Stack is not empty";
    }
    
    //I use while loop to push the element in to the stack.

    while(!originalStack.isFullStack()) //As long as the stack is not full, it will keep adding random number to it
    {
        originalStack.push(rand()% 100); //this will generate number 1 to 100, randomly
    }
    cout << endl;

    //if loop, if the stack is not empty, I want to pop the top of the stack
    //if my stack is empty, this function will bypass itself, because there is nothing to pop
    if(!originalStack.isEmptyStack())
    cout << "The top of the stack is: " << originalStack.top();
    cout << endl; 
    
    //this function is use when I want to print out all the elements in the stack, starting from the top
    //The program will scan if the stack is empty or not, and then it will print out the top of the stack,
    //after it print out, it will pop/remove the top of the stack, and will keep doing the same thing
    //until the stack is empty.
    while(!originalStack.isEmptyStack())
    {
        cout << originalStack.top() << " ";
        originalStack.pop();
    }
    cout << "end of first stack";
    cout << endl;

    //To check if the stack is full, but since stack will never get fulled, only limited by the size.
    if(originalStack.isFullStack())
    {
        cout << "Stack is full";
    }
    else 
    {
        cout << "not full yet";
    }
    cout << endl;
    
    //This program is to test if the copy construction work or not
    //I use random number to fill up the stack to the secondStack
    //after that, I copy all the elements/stack to the sameStack
    while(!secondStack.isFullStack())
    {
        secondStack.push(rand() % 100); //to generate random numbers
    }
    sameStack = secondStack; //this is the copy assignment, no need for deep copy
    cout << endl;
    cout << "Copy of the secondStack to the sameStack";
    while(!sameStack.isEmptyStack())
    {
        cout << sameStack.top() << " ";
        sameStack.pop();
    }
    cout << endl;
    
    //the end of the program, the timer will stop here
    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - begin);

    cout << duration.count() << " milliseconds.";
    return 0;

}
