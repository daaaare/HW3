#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include "linkedStack.h"

std::string infixToPostfix(const std::string& infix);
double evaluatePostfix(const std::string& postfix);
int precedence(char op);
bool isOperator(char ch);
std::vector<std::string> tokenize(const std::string& expression);

int main() {
    std::string infix;
    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, infix);

    try {
        std::string postfix = infixToPostfix(infix);
        double result = evaluatePostfix(postfix);

        std::cout << "Postfix expression: " << postfix << std::endl;
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

//tokenize the expression into a vector of tokens
std::vector<std::string> tokenize(const std::string& expression) {
    std::vector<std::string> tokens;
    size_t i = 0; //index to traverse the input string
    while (i < expression.length()) {
        //ignore any whitespace characters
        if (std::isspace(expression[i])) {
            ++i;
        // capture number tokens
        } else if (std::isdigit(expression[i]) || expression[i] == '.') {
            size_t start = i; //marks the start of the number
            //contrinue while we see digits or a decimal pointer
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.'))
                ++i;
            //add the number string from start to current position to tokens
            tokens.push_back(expression.substr(start, i - start));
        //handle operators and parentheses
        } else if (isOperator(expression[i]) || expression[i] == '(' || expression[i] == ')') {
            //add operator or parenthesis as a tsingle character token
            tokens.push_back(std::string(1, expression[i]));
            ++i;
        //throw error for any character not recognized
        } else {
            throw std::runtime_error(std::string("Invalid character in expression: ") + expression[i]);
        }
    }
    return tokens;
}

std::string infixToPostfix(const std::string& infix) {
    LinkedStack<std::string> opStack;
    std::string postfix;
    std::vector<std::string> tokens = tokenize(infix);
    for (const std::string& token : tokens) {
        //if token is a number add it directly to postifx expression
        if (std::isdigit(token[0]) || token[0] == '.') {
            postfix += token + " ";
        } else if (token == "(") {
            opStack.push(token);
        //process all operators until th emaching ( when ) is encountered
        } else if (token == ")") {
            while (!opStack.isEmpty() && opStack.peek() != "(") {
                postfix += opStack.pop() + " ";
            }
            if (opStack.isEmpty())
                throw std::runtime_error("Mismatched parentheses");
            opStack.pop(); //remove '(' from stack
        //handle operators by precendence
        } else if (isOperator(token[0])) {
            //pop operators from the stack to the postfix expression while they have higher or equal precedence
            while (!opStack.isEmpty() && precedence(opStack.peek()[0]) >= precedence(token[0])) {
                postfix += opStack.pop() + " ";
            }
            //push current operator onto the stack
            opStack.push(token);
        } else {
            throw std::runtime_error("Invalid token in infix expression: " + token);
        }
    }// pop all remaining operators in the stack
    while (!opStack.isEmpty()) {
        std::string op = opStack.pop();
        if (op == "(" || op == ")")
            throw std::runtime_error("Mismatched parentheses");
        postfix += op + " ";
    }
    return postfix; //return the converted expression
}

double evaluatePostfix(const std::string& postfix) {
    LinkedStack<double> evalStack;
    std::istringstream iss(postfix);
    std::string token;
    //process each token
    while (iss >> token) {
        //if number is a token push onto stack
        if (std::isdigit(token[0]) || token[0] == '.') {
            evalStack.push(std::stod(token)); //convert string to double and push
        //process operators
        } else if (isOperator(token[0])) {
            if (evalStack.isEmpty())
                throw std::runtime_error("Insufficient operands");
            double y = evalStack.pop();
            if (evalStack.isEmpty())
                throw std::runtime_error("Insufficient operands");
            double x = evalStack.pop();
            switch (token[0]) {
                case '+': evalStack.push(x + y); break;
                case '-': evalStack.push(x - y); break;
                case '*': evalStack.push(x * y); break;
                case '/':
                    if (y == 0)
                        throw std::runtime_error("Division by zero");
                    evalStack.push(x / y);
                    break;
                default:
                    throw std::runtime_error("Unknown operator: " + token);
            }
        } else {
            throw std::runtime_error("Invalid token in postfix expression: " + token);
        }
    }// final result should be the only item in the stack
    if (evalStack.isEmpty())
        throw std::runtime_error("No result on the stack");
    double result = evalStack.pop();//pop result
    if (!evalStack.isEmpty())
        throw std::runtime_error("Multiple items left on the stack");
    return result;
}

//returns the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default:  return 0;  // Should never happen
    }
}

//helper function to check if a character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}
