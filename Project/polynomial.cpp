#include "polynomial.hpp"
#include <string>
// Basic constructor
Polynomial::Polynomial()
{
    this->array = nullptr;
    this->size = 0;
}
// Constructor with arguments
Polynomial::Polynomial(double arg, int number)
{
    this->size = number + 1;
    this->array = new double[number + 1];
    for (int i = 0; i < number + 1; i++)
    {
        array[i] = 0;
    }
    array[number] = arg;
}

// Method to return an array with arguments of the each element of polynomial.
std::string Polynomial::toString()
{
    std::string result = "";
    for (int i = 0; i < size; i++)
    {
        result += std::to_string(array[i]);
        if (i != size - 1)
        {
            result += ", ";
        }
    }

    result = "{ " + result + " }";
    return result;
}

// Method to return a representation of polynomial.
std::string Polynomial::representation()
{
    if (is_zero())
    {
        throw EmptyPolynomialException();
    }
    std::string result = "";
    result += std::to_string(array[0]);
    for (int i = 1; i < size; i++)
    {
        if (array[i] == 0.0)
        {
            continue;
        }
        if (i < 2)
        {
            result += " + " + std::to_string(array[i]) + "x";
        }
        else
        {
            result += " + " + std::to_string(array[i]) + "x^" + std::to_string(i);
        }
    }
    return result;
}

bool Polynomial::operator==(const Polynomial &other)
{
    if (this->size != other.size)
    {
        return false;
    }
    for (int i = 0; i < this->size; i++)
    {
        if (this->array[i] != other.array[i])
        {
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!=(const Polynomial &other)
{
    return !(*this == other);
}

Polynomial Polynomial::operator+(const Polynomial &other)
{

    Polynomial newPoly;

    if (other.size == 0)
    {
        newPoly.array = this->array;
        newPoly.size = this->size;
        return newPoly;
    }

    if (this->size >= other.size)
    {
        newPoly.array = new double[this->size];
        newPoly.size = this->size;
    }
    else
    {
        newPoly.array = new double[other.size];
        newPoly.size = other.size;
    }
    for (int i = 0; i < size; i++)
    {
        newPoly.array[i] = array[i];
    }
    for (int i = 0; i < other.size; i++)
    {
        newPoly.array[i] += other.array[i];
    }

    return newPoly;
}

Polynomial Polynomial::operator-(const Polynomial &other)
{

    Polynomial newPoly;

    if (other.size == 0)
    {
        double *temp = newPoly.array;
        newPoly.array = this->array;
        delete[] temp;
        newPoly.size = this->size;
        return newPoly;
    }

    if (this->size >= other.size)
    {
        double *temp = newPoly.array;
        newPoly.array = new double[this->size];
        delete[] temp;
        newPoly.size = this->size;
    }
    else
    {
        double *temp = newPoly.array;
        newPoly.array = new double[other.size];
        delete[] temp;
        newPoly.size = other.size;
    }
    for (int i = 0; i < newPoly.size; i++)
    {
        newPoly.array[i] = 0;
    }
    for (int i = 0; i < this->size; i++)
    {
        newPoly.array[i] = array[i];
    }
    for (int i = 0; i < other.size; i++)
    {
        newPoly.array[i] -= other.array[i];
    }
    return newPoly;
}

Polynomial Polynomial::operator=(const Polynomial &other)
{ 
    if (this != &other)
    {
        delete []array;

        this->size = other.size;
        this->array = new double[size];
        for(unsigned i = 0; i < size; i++)
            array[i] = other.array[i];
    }



    return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &right)
{
    if (this->array == nullptr)
    {
        // this->array = right.array;
        this->size = right.size;
        return *this;
    }

    *this = this->operator+(right);
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &right)                                                       /////////////////////
{
    if (this->array == nullptr)
    {
        // this->array = right.array;
        this->size = right.size;
        return *this;
    }
    *this = this->operator-(right);
    return *this;
}

Polynomial Polynomial::operator*(const int &number)
{
    double *result;
    if (!is_zero())
    {
        result = new double[this->size];
        for (int i = 0; i < this->size; i++)
        {
            result[i] = this->array[i] * number;
        }
        return Polynomial(this->size, result);
    }
    return Polynomial();
}

Polynomial Polynomial::operator*(const Polynomial &other)
{

    Polynomial result;
    if (this->size == 0 || other.size == 0)
    {
        return result;
    }

    int new_size = this->size + other.size - 1;

    double *temp = result.array;
    result.array = new double[new_size];
    result.size = new_size;
    delete[] temp;

    for (int i = 0; i < new_size; i++)
    {
        result.array[i] = 0;
    }

    for (int i = 0; i < this->size; i++)
    {
        for (int j = 0; j < other.size; j++)
        {
            result.array[i + j] += this->array[i] * other.array[j];
        }
    }

    return result;
}

// Method to exponent the polynomial by a number;
Polynomial Polynomial::pow(int n)
{
    if (n == 0)
    {
        double result[1] = {1.0};
        return Polynomial(1, result);
    }
    if (n == 1)
    {
        return *this;
    }
    return *this * pow(--n);
}

// Method to defferentiate th polynomial.
Polynomial Polynomial::diff()
{
    if (size != 0)
    {
        double *newArray = new double[size];

        for (int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }

        newArray[0] += newArray[1];
        newArray[1] = 0;
        for (int i = 1; i < size - 1; i++)
        {
            newArray[i] = (i + 1) * newArray[i + 1];
            newArray[i + 1] = 0;
        }

        return Polynomial(size, newArray);
    }
    else
    {
        throw EmptyPolynomialException();
    }
}

bool Polynomial::is_zero()
{
    return size == 0;
}

// Method to integrate polynomial.
Polynomial Polynomial::integrate()
{
    if (!is_zero())
    {
        double *newArray = new double[size + 1];
        for (int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
        // size;
        for (int i = size+1; i > 0; i--)
        {
            newArray[i] = newArray[i - 1] / i;
        }
        newArray[0] = 0;

        return Polynomial(size+1, newArray);
    }
    else
    {
        throw EmptyPolynomialException();
    }
}

// Method to evaluate polynomial using horner algorithm.
double Polynomial::eval_by_Horner(const double &x)
{
    if (!is_zero())
    {
        double result = 0.0;
        for (int i = size - 1; i >= 0; i--)
        {
            result = array[i] + (x * result);
        }
        return result;
    }
    else
    {
        throw EmptyPolynomialException();
    }
}

// Method to make a negative polynomial.
void Polynomial::negation()
{
    if (!is_zero())
    {
        for (int i = 0; i < size; i++)
        {
            array[i] *= -1;
        }
    }
    else
    {
        throw EmptyPolynomialException();
    }
}

int Polynomial::getSize()
{
    return size;
}

// Method to combine two polynomials into one.
Polynomial Polynomial::combine(const Polynomial &_other)
{
    if (!is_zero())
    {
        if (_other.size == 0)
        {
            Polynomial result(this->array[0], 1);
            return result;
        }

        Polynomial result(0, (this->size - 1) * (_other.size - 1));
        Polynomial other;
        other = _other;
        for (int i = this->size - 1; i >= 0; i--)
        {
            result += other.pow(i) * this->array[i];
        }
        result.array[0] = this->array[0];

        return result;
    }
    else
    {
        throw EmptyPolynomialException();
    }
}