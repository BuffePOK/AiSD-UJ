#include "functions.hpp"
#include <fstream>

void chooseMode(int mode)
{
    if (mode == 1)
    {
        userMode();
    }
    else if (mode == 2)
    {
        presentationMode();
    }
    else if (mode == 3)
    {
        showInfo();
    }
    else
    {
        throw CommandNotFoundException();
    }
}

void startProgram()
{

    int operaion_int = 0;
    std::string operation_str;

    std::cout << std::string(40, '-') << "\n\n"
              << "\tPolynomial calculator\n\n"
              << std::string(40, '-') << "\n";
    while (true)
    {
        std::cout << "\nChoose mode:\n1) User mode\n2) Presentation mode\n3) Show information\n4) Exit\n\n";
        std::cin >> operation_str;
        try
        {
            operaion_int = atoi(operation_str.c_str());
            if (operaion_int == 4)
            {
                break;
            }
            else
            {
                chooseMode(operaion_int);
            }
        }
        catch (CommandNotFoundException &e)
        {
            std::cout << e.what() << "\n";
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << "\n";
        }
    }
}

Polynomial createPoly(int &size)
{
    double *input_args = new double[size];
    std::cout << "Write all arguments for each element of polynomial -\n";
    std::string input;
    for (int i = 0; i < size; i++)
    {
        std::cout << i + 1 << ": ";
        std::cin >> input;
        if (check_number(input))
        {
            input_args[i] = atof(input.c_str());
        }
        else
        {
            throw WrongInputException();
        }
    }
    return Polynomial(size, input_args);
}

void userMode()
{
    std::cout << std::string(40, '-') << "\n\n"
              << "\tUser mode...\n\n"
              << std::string(40, '-') << "\n";

    std::cout << "\nNow you need to create a polynomial:\n";
    int size_int_first;
    std::string size_str_first;
    int size_int_second;
    std::string size_str_second;
    while (true)
    {
        std::cout << "*** Write size of your first polynomial: ";
        std::cin >> size_str_first;
        std::cout << "*** Write size of your second polynomial: ";
        std::cin >> size_str_second;
        try
        {
            if (check_number(size_str_first) && check_number(size_str_second))
            {
                size_int_first = atoi(size_str_first.c_str());
                size_int_second = atoi(size_str_second.c_str());
                Polynomial poly1 = createPoly(size_int_first);
                std::cout << "\n------------\n";
                Polynomial poly2 = createPoly(size_int_second);
                std::cout << "Now you have such polynomials:\n";
                std::cout << poly1.representation() << " - first\n";
                std::cout << poly2.representation() << " - second\n";

                try
                {
                    userTest(poly1, poly2);
                }
                catch(const WrongInputException& e)
                {
                    std::cout << e.what() << '\n';
                }
                catch(const std::exception& e)
                {
                    std::cout << e.what() << '\n';
                }
                
            }
            else
            {
                throw WrongInputException();
            }
        }
        catch (const WrongInputException &e)
        {
            std::cout << e.what() << '\n';
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
        }
    }
}

void presentationMode()
{
    std::cout << std::string(40, '-') << "\n\n"
              << "\tPresentation mode...\n\n"
              << std::string(40, '-') << "\n";

    double arr1[3] = {3.0, 2.0, 1.0};
    double arr2[3] = {1.0, 2.0, 3.0};

    Polynomial poly1(3, arr1);
    Polynomial poly2(3, arr2);

    Polynomial result;

    std::cout << "In presentation mode we have two polynomials:\n";
    std::cout << "1: " << poly1.representation() << '\n';
    std::cout << "2: " << poly2.representation() << '\n';

    testAdd(poly1, poly2, result);
    testSub(poly1, poly2, result);
    testMul(poly1, poly2, result);
    testMulN(poly1, result);
    testEq(poly1, poly2);
    testNEq(poly1, poly2);
    testEval(poly1, poly2);
    testExp(poly1, poly2, result);
    testDiff(poly1, poly2, result);
    testInt(poly1, poly2, result);
    testComb(poly1, poly2, result);
}

void testAdd(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    result = poly1 + poly2;
    std::cout << "\n### ADDITION ###\n";
    std::cout << result.representation() << '\n';
    std::cout << std::string(25, '-') << '\n';
}

void testSub(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    result = poly1 - poly2;
    std::cout << "\n### SUBTRACTION ###\n";
    std::cout << result.representation() << '\n';
    std::cout << std::string(25, '-') << '\n';
}

void testMul(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    result = poly1 * poly2;
    std::cout << "\n### MULTIPLICATION BY ANOTHER POLYNOMIAL ###\n";
    std::cout << result.representation() << '\n';
    std::cout << std::string(25, '-') << '\n';
}

void testMulN(Polynomial &poly1, Polynomial &result)
{
    result = poly1 * 4;
    std::cout << "\n### MULTIPLICATION BY A NUMBER ###\n";
    std::cout << result.representation() << '\n';
    std::cout << std::string(25, '-') << '\n';
}
void testEq(Polynomial &poly1, Polynomial &poly2)
{
    std::cout << "\n### EQUATION TO ANOTHER POLYNOMIAL ###\n";
    std::cout << (poly1 == poly2) << '\n';
    std::cout << std::string(25, '-') << '\n';
}
void testNEq(Polynomial &poly1, Polynomial &poly2)
{
    std::cout << "\n### NOTEQUATION TO ANOTHER POLYNOMIAL ###\n";
    std::cout << (poly1 != poly2) << '\n';
    std::cout << std::string(25, '-') << '\n';
}

void testEval(Polynomial &poly1, Polynomial &poly2)
{
    std::cout << "\n### EVALUATING BY HORNER ALGORYTHM ###\n";
    std::cout << poly1.eval_by_Horner(4) << "\t - first Polynomial\n";
    std::cout << poly2.eval_by_Horner(4) << "\t - second Polynomial\n";
    std::cout << std::string(25, '-') << '\n';
}

void testExp(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    std::cout << "\n### EXPONENTIATION ###\n";
    result = poly1.pow(2);
    std::cout << result.representation() << "\t - first Polynomial\n";
    result = poly2.pow(2);
    std::cout << result.representation() << "\t - second Polynomial\n";
    std::cout << std::string(25, '-') << '\n';
}
void testDiff(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    std::cout << "\n### DIFFERENTIATION ###\n";
    result = poly1.diff();
    std::cout << result.representation() << "\t - first Polynomial\n";
    result = poly2.diff();
    std::cout << result.representation() << "\t - second Polynomial\n";
    std::cout << std::string(25, '-') << '\n';
}
void testInt(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    std::cout << "\n### INTEGRATION ###\n";
    result = poly1.integrate();
    std::cout << result.representation() << "\t - first Polynomial\n";
    result = poly2.integrate();
    std::cout << result.representation() << "\t - second Polynomial\n";
    std::cout << std::string(25, '-') << '\n';
}
void testComb(Polynomial &poly1, Polynomial &poly2, Polynomial &result)
{
    std::cout << "\n### COMBINATION ###\n";
    result = poly1.combine(poly2);
    std::cout << result.representation() << " - first Polynomial with second Polynomial\n";
    std::cout << std::string(25, '-') << '\n';
}

void userTest(Polynomial &poly1, Polynomial &poly2)
{
    int operation_int;
    std::string operation_str;
    Polynomial result;
    while (true)
    {
        std::cout << "What operation do you want to do:\n";
        std::cout << "1)Add\n2)Substract\n3)Multiply\n4)Multiply by number\n"
                  << "5)Exponentiate\n6)Differentiate\n7)Integrate\n8)Combinate\n"
                  << "9)Evaluate by Horner algorythm\n10)Exit\n";
        std::cin >> operation_str;

        if (check_number(operation_str))
        {
            operation_int = atoi(operation_str.c_str());
            if (operation_int == 1)
            {
                testAdd(poly1, poly2, result);
            }
            else if (operation_int == 2)
            {
                testSub(poly1, poly2, result);
            }
            else if (operation_int == 3)
            {
                testMul(poly1, poly2, result);
            }
            else if (operation_int == 4)
            {
                testMulN(poly1, result);
            }
            else if (operation_int == 5)
            {
                testExp(poly1, poly2, result);
            }
            else if (operation_int == 6)
            {
                testDiff(poly1, poly2, result);
            }
            else if (operation_int == 7)
            {
                testInt(poly1, poly2, result);
            }
            else if (operation_int == 8)
            {
                testComb(poly1, poly2, result);
            }
            else if (operation_int == 9)
            {
                testEval(poly1, poly2);
            }
            else if (operation_int == 10)
            {
                break;
            }
            else 
            {
                std::cout << "Wrong input try again...\n";
            }
        }
    }
}

void showInfo()
{
    std::cout << "\nInformation:\n";
    // TODO: ADD TEXT TO THE INFO.TXT !!!!
    std::fstream fs;
    try
    {
        fs.open("info.txt", std::ios::in);
        if (fs.is_open())
        {
            std::string line;
            while (!fs.eof())
            {
                std::getline(fs, line);
                std::cout << line << "\n";
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool check_number(std::string str)
{
    int n = 1;
    if (str[0] == '-')
    {
        n++;
        for (int i = 1; i < str.length(); i++)
        {
            if (str[i] == '.')
            {
                continue;
            }
            if (isdigit(str[i]) == false)
            {
                n = n - 2;
            }
        }
    }
    else
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '.')
            {
                continue;
            }
            if (isdigit(str[i]) == false)
            {
                n = n - 2;
            }
        }
    }
    if (n <= 0)
    {
        return false;
    }
    return true;
}