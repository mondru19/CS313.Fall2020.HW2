//***********************************************************
// Author: D.S. Malik
//
// Program: Postfix Calculator  
// This program evaluates postfix expressions.
//***********************************************************
  
#include <iostream>  
#include <iomanip>
#include <fstream>
#include "myStack.h" // include myStack header because we are going to use some functions from there.
 
//Declaring functions header that would be use on the main programs.

//There are four functions in this program. 

//evaluateExpression function is use to scan/read the expression thorougly from left to right until it finds symbol '=', which means
//it is at the end of the expression.
void evaluateExpression(ifstream& inpF, ofstream& outF, 
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);

//evaluateOpr function is to evaluate the expression.
void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
//This function has only one job, it will discard an expression that has an error in to the text file along with the message.
void discardExp(ifstream& in, ofstream& out, char& ch);
//To print the result of the expression along with the original expression
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

//Main function, where we read the value from
int main()
{
    bool expressionOk; //we use boolean for expressionOk because we want the value to be true of false.
    char ch; //we use char for ch because we are using symbols 
    stackType<double> stack(100);  //the size of the stack 
    ifstream infile; //ifstream to read the textfile
    ofstream outfile;// to output/write the file to the another textfile (it will create a new textfile automatically)
 
    infile.open("RpnData.txt"); //to read the text file RpnData that we created with some value in it

    if (!infile) //The RpnData needs to be in the same file as the program code and the name of the file should be exactly the same, otherwise it cant be open and the program will then terminted
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
     
    outfile.open("RpnOutput.txt"); //this is where the result will be printed and output it to
    // this code is to make the result of the operators (if any) to only have 2 decimals point only
    outfile << fixed << showpoint;
    outfile << setprecision(2); 
    
    //this while loop is reading the whole expression, if the expression is error free or not, it will still be in the text file
    infile >> ch;
    while (infile)//first it geos through the whole expression from left to right
    {
        stack.initializeStack(); //initialize the stack, the limit we set to 100
        expressionOk = true; //if there is no error in the expression, it will come out as true
        outfile << ch; // write the symbol in to other textfile
        //scan the expression
        evaluateExpression(infile, outfile, stack, ch, 
                           expressionOk);
        printResult(outfile, stack, expressionOk); //printing the result
        infile >> ch; //begin processing the next expression
    } //end while 

    infile.close(); //close the infile
    outfile.close(); // close the outfile

    return 0;

} //end main



//There are 5 parameters on this functions.
//ifstream, to read or access the input file. usually from "*.txt" from text file
//ofstream, to write or output the file. usually to text file also.
//stackType<double>& to access the stack code that we were written in another file. thats where #include "myStack.h" comes in.
//bool isExpOk to check whether theres any illegal expression/symbols or not, if so, we will terminate the program.
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num; // using double to get more precision out of the value, since the value might comes out with decimals.

    while (ch != '=') //Go through each expression from left to right, as long the expression/symbol is not '=', it will keep doping the while loop. '=' means the end of the loop
    {
        switch (ch) //inside the while loop we have switch statement.
        {
        case '#': //if the the program reads '#' symbol,  
            inpF >> num; //it will read/input the number next to that symbol
            outF << num << " ";// and output the number into different text file (thats what ofstream does)
            if (!stack.isFullStack()) //we check if the stack is full or not, if not then we push that number in to our stack
                stack.push(num); //we push the number to stack.
            else
            {
                cout << "Stack overflow. " // else if the stack is full, it will terminate the program because the quantity of the number is more than our stack limit. 
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }
            break; // to move to the next statement.
        default: // the default statement will run if we encounter any illegal symbols, division by 0(when 0 on the bottom) or the stack is overflow.
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        if (isExpOk) //if we do not encounter any errors,
        {
            inpF >> ch; // to read the next symbol from the text file
            outF << ch; // to output/write to the text file

            if (ch != '#') //if we the program reads operator instead of operand,
                outF << " "; 
        }
        else
            discardExp(inpF, outF, ch); // else, if none above, we discard the expression
    } //end while (!= '=')
} //end evaluateExpression

//This function is to evaluate an expression. If there are two numbers(operands) in the stack, this function will then perform the operation.
//If there is less than 2 operands in the stack when the program reads an operator, then there will be an error.
//If there is any illegal symbols, the expression will then be throw and any of the messages will then be printed according to which the error is.
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2; //set op1 and op2 double, which they will be our operand number 1 and number 2 (the number that will do the operation)

    //check to see whether the stack is empty or not
    //if the stack is empty, then it will print the message not enough operands
    if (stack.isEmptyStack()) 
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else //else if there are 2 element/operands in the stack,
    {
        op2 = stack.top(); // first we pop(take out the top of the stack(which is an operand) to be the second operand)
        stack.pop();
        //second, we check again if the stack is empty or not(because we need 2 operands in order to do operation)
        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else //if not, we pop the top of the stack, which is an operand, to be our first operand. 
            //it is important to know which is op1 and op2 because when we do operation such as '-' and '/', you cant flip the number around.
        {
            op1 = stack.top();  //make op1 to be the top of the stack (after we pop the privous number in the stack)
            stack.pop(); // and pop op1 from the stack 
            //the switch statement to choose which operator is the program reading from the text file
            switch (ch)
            {
            case '+': //if the program read '+' plus sign, it will then add op1 and op2 and push the value from it to the stack
                stack.push(op1 + op2);
                break;
            case '-': //if the program read '-' minus sign, it will then subract op1 and op2 and push the value back to the stack
                stack.push(op1 - op2);
                break;
            case '*': //if the program read '*'multiplication sign, it will then multiply op1 and op2 and push the value back to the stack
                stack.push(op1 * op2);
                break;
            case '/': //if the program read '/'division sign, it will then divide op1 and op2 and push the value back to the stack, however if op2 is 0, it will give an error message
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)"; //cannot divide anything by 0
                    isExpOk = false;
                }
                break;
            default: //if the program read none of the symbols/operators above, it will then print out an error message saying that it has an illegal operator
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//This function has only one job, it will discard an expression that has an error in to the text file along with the message.
//first, this function read the whole expression from left to right (expression that has an error, whether it will be an illegal expression or fewer operands)
//and output the expression in to the textfile
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=') //read the expression from left to right until it reads '=', meaning it is at the end of the expression
    {
        in.get(ch); // get the expression
        out << ch; // and output the expression in to the textfile
    }
} //end discardExp

//The print result is to print all of the expression and output it to the other text file, which in this case will be in "RpnOutput.txt"
//If the expression has no error, then this function will print out the whole expression with the result,
//otherwise it will print out the whole expression with an appropriate message next to the expression
//If the stack ends with only one operand, then it means the expression has no error in it
//If the stack has no operands or operator left by the end of evaluation, then there is an error, therefore it will print out error message
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;  //set the result value to double because it might comes out with decimals, therefore needed more precision

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack()) //check if the stack is emtpy or not empty, if not, continue to the next line, othwerise, it is an error
        {
            result = stack.top(); //assign the value of stack.top into result
            stack.pop(); //pop out the stack

            if (stack.isEmptyStack())//do a check again, if the stack is empty, then its good to go(because it should, we poped out the stack already)
                outF << result << endl; //we print the result
            else
                outF << " (Error: Too many operands)" << endl; //if there is still more element in the stack, it is an error because we should only have one element at the end
        } //end if
        else //if the stack is empty after the second loop of if, then this message will be print out
            outF << " (Error in the expression)" << endl;
    }
    else //if there is an error in the first check, then this message will be print out
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________" 
         << endl << endl;
} //end printResult
