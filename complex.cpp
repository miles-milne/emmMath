
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>

using std::string;

#include "complex.h"

/* * * * * * * * *
 CONSTRUCTORS
* * * * * * * * */

    Complex:: Complex() 
    {
      real = 0;
      imaginary = 0;
    }
    
    // Standard form
    Complex:: Complex(double a, double b) 
    {
      real = a;
      imaginary = b;
    }
    
    
/* * * * * * * * *
 ACCESSORS & MUTATORS  
* * * * * * * * */
    
    double Complex:: getReal() const 
    {
      return real;
    }
      
      
    double Complex:: getImaginary() const 
    {
      return imaginary;
    }
    
    
    void Complex:: setReal(double new_real) 
    {
      real = new_real;
    }
    
    void Complex:: setImaginary(double new_imaginary) 
    {
      imaginary = new_imaginary; 
    }
    
    void Complex:: setComplex(double new_real, double new_imaginary)
    {
      real = new_real;
      imaginary = new_imaginary; 
    }
    
/* * * * * * * *
  MEMBER METHODS
* * * * * * * */
    
    double Complex:: norm() const 
    {
      return sqrt(pow(real,2) + pow(imaginary,2));
    }
    
    Complex Complex:: conjugate() const 
    {
      return Complex(real, -imaginary);
    }
    
    Complex Complex:: operator+(Complex const& other) const
    {
      return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    void Complex:: operator+=(Complex const& other)
    {
      real += other.real;
      imaginary += other.imaginary;  
    }
    
    Complex Complex:: operator-(Complex const& other) const
    {
      return Complex(real - other.real, imaginary - other.imaginary); 
    }
    
    void Complex:: operator-=(Complex const& other)
    {
      real -= other.real;
      imaginary -= other.imaginary;  
    }
    
    Complex Complex:: operator*(Complex other) const
    {
      return Complex(real * other.real - imaginary * other.imaginary, real * other.imaginary + imaginary * other.real);  
    }
    
    Complex Complex:: operator*(double scaler) const
    {
      return Complex(real * scaler, imaginary * scaler);
    }
    
    Complex Complex:: operator/(Complex const& other) const
    {
      return (((*this) * other.conjugate()) / (pow(other.real, 2) + pow(other.imaginary, 2)));
    }
    
    Complex Complex:: operator/(double scaler) const
    {
      return Complex(real / scaler, imaginary / scaler);  
    }
    
    bool Complex:: operator==(Complex const& other) const 
    {
      return (real == other.real && imaginary == other.imaginary);
    }
    
    Complex Complex:: exp(int exp)
    {
      // De movire's theorem 
      double magnitude = pow(norm(), exp);
      double angle = acos(real / norm());
      Complex power = Complex(magnitude * cos(angle*exp), magnitude * sin(angle*exp));
    
      return power; 
    } 
    
    std::vector<Complex> Complex:: nthRoots(int n)
    {
      std::vector<Complex> roots;
      double magnitude = pow(norm(), 1.0/n);
      double angle = acos(real / norm());
      
      for (int k = 0; k < n; k++)
      {
          roots.push_back(Complex(magnitude * cos((angle + 2*k*M_PI)/n) , magnitude*sin((angle + 2*k*M_PI)/n)));
      }
      
      return roots;
    }
  
    // I will finish this later (not)
    string Complex:: toStringPolar()
    {
      return "";
    }

    string Complex:: toString() 
    {
      
      // opens a stream for a string, where you can interact with it via operators like cin, cout, iomanip, etc
      std::ostringstream oss; 
      
      if (real == 0 && imaginary == 0)
        return "0";
      
      // Makes it so that doubles do not show trailing zeros 
      oss << std::setprecision(8) << std::noshowpoint;
      
      if (real != 0)
      {
        oss << real;
      }
      
      
      if (imaginary != 0)
      {
        if (imaginary > 0 && real != 0)
          oss << "+";
        
        if (imaginary == 1)
          oss << "i"; 
        else if (imaginary == -1)
          oss << "-i";
        else if (imaginary > 0)
          oss << imaginary << "i";
        else 
          oss << imaginary << "i";
      }
       
      return oss.str();
    }


