
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>

using std::string;

#include "complex.h"

class Complex {
  private: 
    double real;
    double imaginary;
  
  public:
    Complex();
    Complex(double a, double b);
    
    double getReal() const;
    double getImaginary() const;
    void setReal(double new_real);
    void setImaginary(double new_imaginary);
    void setComplex(double new_real, double new_imaginary);

    double norm() const;
    Complex conjugate() const;
    Complex operator+(Complex const& other) const;
    void operator+=(Complex const& other);
    Complex operator-(Complex const& other) const;
    void operator-=(Complex const& other);
    Complex operator*(Complex other) const;
    Complex operator*(double scaler) const;
    Complex operator/(Complex const& other) const;
    Complex operator/(double scaler) const;
    bool operator==(Complex const& other) const;
    Complex exp(int exp);
    std::vector<Complex> nthRoots(int n);
    string toStringPolar();
    string toString();
};

#endif