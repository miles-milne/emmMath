
#include <iostream>
#include "complex.cpp"
#include "complex.h"

using std::cout;

int main()
{
  Complex test = Complex(5,-7);
  Complex test2 = Complex(-5, 2);
  Complex test3 = Complex(); 
  
  Complex c3 = Complex(3, -2);
  Complex c4 = Complex(-2, 1);
  Complex c5 = Complex(1, -2);
  Complex c6 = Complex(3, 4);
  Complex c7 = Complex(5, -6);
  Complex c8 = Complex(2, 2);
  Complex c9 = Complex(0.5, sqrt(3)/2);
  Complex c10 = Complex(4, -4*sqrt(3));
  
  cout << (c3+c4).toString() << "\n" 
       << (c3-c4).toString() << "\n"
       << (c3 * c4).toString() << "\n"
       << (c3 / c4).toString() << "\n"
       << (c3*5).toString() << "\n"
       << (c4 / 2).toString() << "\n"
       << ((c5 - c6)/c7).toString() << "\n"
       << c8.exp(7).toString() << "\n"
       << c9.exp(0).toString() << "\n"
       << c10.toString();

  std::vector<Complex> fourthRoots = c10.nthRoots(3);
  
  for (int i = 0; i < 3; i++)
  {
    cout << i << ": " << fourthRoots[i].toString() << "\n";  
  }
  
  cout << ((Complex(1, -2) + Complex(2, 3)) / (Complex(5, -6) * Complex(-1, 1))).toString() << "\n";
  
  
}