#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "polynomial.hpp"
#include <string>

void startProgram();

// Mode that shows what you can do with polynomials without user input.
void presentationMode();

// Mode that shows what you can do with polynomials with user input.
void userMode();

// Function to choose mode (presentation or user).
void chooseMode(int mode);

// Function to show information about use of program.
void showInfo();

// Checks if given string is a number.
bool check_number(std::string str);

// Function to create polynomial.
Polynomial createPoly(int &size);

// Function to perform user test.
void userTest(Polynomial &p1, Polynomial &p2);

// Series of test for different functions of polynomials.
void testAdd(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testSub(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testMul(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testMulN(Polynomial &p1, Polynomial &result);
void testEq(Polynomial &p1, Polynomial &p2);
void testNEq(Polynomial &p1, Polynomial &p2);
void testEval(Polynomial &p1, Polynomial &p2);
void testExp(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testDiff(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testInt(Polynomial &p1, Polynomial &p2, Polynomial &result);
void testComb(Polynomial &p1, Polynomial &p2, Polynomial &result);

class CommandNotFoundException : std::exception
{
public:
    const char *what() const throw()
    {
        return "No command with this number, try again...";
    }
};

class WrongInputException : std::exception
{
public:
    const char *what() const throw()
    {
        return "Wrong input, try again...";
    }
};

#endif // FUNCTIONS_H