
/*
TODO:
- Header file
- deconstructor?? --> delete coeff, 

- use Arrays library 

- add opperator overloads for +, -, *, /, by constants 
- create exception handlers for when the accessors and mutators read/write out of bounds 
- use the standard lib array for coeff instead of an array pointer 

- make it so that quadratic formula can return complex roots
  - Implement Complex, Rational
- make it so that toString() does not print coefficients equal to 1 (e.g. 1x^2 --> x^2, -1x^5 --> -x^5
- input function that accepts (istream &fin) as parameter, so you can change coeff using .txt file or cin 


NOTES:
- for the coeff array, element 0 is the coeff for the constant term, element 1 is for the x term, elements 2 is for the x^2 term, etc) 
- Remember, degree 0 just means its a constant polynomial 

*/

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using std::string;
using std::cout;

class Polynomial {
  
  private:
    int degree;
    double *coeff; 
  
  public:
    
   /* CONSTRUCTOS & DESTRUCTORS */ 
    
    Polynomial()
    {
      degree = 0;
      coeff = new double[100];
    }
    
    Polynomial(int n) // Creates zero polynomial of degree n
    {
      degree = n;
      coeff = new double[n+1];
      
      // Removes any garbage values when coeff array is initalized 
      for (int count = 0; count <= n; count++)
      {
        coeff[count] = 0;
      }
      
    }
    
    // There must be a better way to do this other than just copying the array into where the pointer's memory is allocated 
    Polynomial(double coeff_arr[], int n)
    {
      degree = n;     
      coeff = new double[n+1];
      
      for (int count = 0; count <= n; count++)
      {
        coeff[count] = coeff_arr[count]; 
      }
    }
    
    ~Polynomial()
    {
      delete[] coeff; 
    }
    
    
    
    /* MUTATORS & ACCESSORS */
    
    // returns polynomial degree 
    int getDegree() const {
      return degree; 
    }
    
    // returns pointer for coefficient array
    double* getCoeff() const {
      return coeff;
    }  
    
    // returns element from coefficient array
    double getCoeff(int n) const {
      return *(coeff + n);
    } 
    
    // Changes degree of polynomail, though it may or may not change the values within the coeff array, only its max size 
    void setDegree(int deg);  
    
    // changes pointer for coefficient array
    void setCoeff(int ptr); 
    
    // Changes coefficient 
    void setCoeff(int n, double val) {
      coeff[n] = val; 
    }
    
    
    /* METHODS */
    
    
    Polynomial operator+(const Polynomial& other)
    {
       int deg = std::max(degree, other.degree);
       
       double coeff_arr[deg + 1] = {};
       
       if (other.degree > degree)
       {
         for (int n = 0; n <= other.degree ; n++)
         {
            coeff_arr[n] = other.coeff[n];
         }
         
         for (int n = 0; n <= degree; n++)
         {
            coeff_arr[n] += coeff[n];
         }
       }
       else
       {
         for (int n = 0; n <= degree; n++)
         {
            coeff_arr[n] += coeff[n];
         }
         
         for (int n = 0; n <= other.degree ; n++)
         {
            coeff_arr[n] += other.coeff[n];
         }
       }

       
      return Polynomial (coeff_arr, deg);
    }
    
    Polynomial operator-(const Polynomial& other);
    Polynomial operator+=(Polynomial other); // mutates *this
    Polynomial operator-=(Polynomial other); // mutates *this 
    
    
    Polynomial operator*(const Polynomial& other) const
    {
      int new_deg = degree + other.degree;
      double coeff_arr[new_deg + 1] = {};
      
      for (int j = 0; j <= degree; j++)
      {
        for (int k = 0; k <= other.degree; k++)
        {
          coeff_arr[j+k] += coeff[j] * other.coeff[k];
        }
      }
    
      return Polynomial(coeff_arr, new_deg);
    }
    
    Polynomial operator*(double scaler) const
    {
      double coeff_arr[degree+1] = {};
      
      for (int n = 0; n <= degree; n++)
      {
        coeff_arr[n] = coeff[n] * scaler; 
      }
      
      
      return Polynomial(coeff_arr, degree);
    }
    
    // Uses power rule to return new Polynomial  
    Polynomial derivative() const
    {
      double coeff_arr[degree] = {};
      
      for (int n = 0; n < degree; n++)
      {
        coeff_arr[n] = coeff[n+1] * (n+1); 
      }
      
      return Polynomial(coeff_arr, degree-1);
    }
    
    // returns the output of the polynomial function
    double f(double x) const
    {
      
      double sum = 0;
      
      for (int n = 0; n <= degree; n++)
      {
        sum += coeff[n] * pow(x, n); 
      }
    
      return sum;
    } 
    
    // quadratic formula implementation
    std::vector<double> quadratic_form() const 
    {
      
      std::vector<double> roots;
      
      // zero or infinite roots: returns array containing NAN 
      if (degree == 0 || (degree == 2 && coeff[2] == 0 && coeff[1] == 0) || (degree == 1 && coeff[1] == 0))
      {
        return roots;
      }
      
      // first degree polynomial
      if (degree == 1 || coeff[2] == 0)
      {
        roots.push_back(-coeff[0] / coeff[1]);
        return roots;
      }
      
      
      
      double discriminant = pow(coeff[1], 2) - 4 * coeff[2] * coeff[0];
      
      // Second degree polynomial
      if (discriminant < 0)
      {
        return roots; 
      }
      else if (discriminant == 0)
      {
        roots.push_back(-coeff[1] / (2 * coeff[2]));
        return roots;
      }
      else 
      {
        roots.push_back((-coeff[1] + sqrt(discriminant)) / (2 * coeff[2]));
        roots.push_back((-coeff[1] - sqrt(discriminant)) / (2 * coeff[2]));
        return roots;
      }
    } 
    
    // The root finding algorithm for higher degree polynomials is by no means failproof or perfectly optimized
    // It utilises newton's method and Decarte's rule of signs to approximate roots 
    // It can fail for polynomials with large coefficients due do floating point arithmetic approximations, and with polynomials
    // with large roots. Since the algorithm first tries to find the leftmost and rightmost roots, by default it assumes that it is less than +/- 100.75
    std::vector<double> find_roots() const
    {
      if (degree <= 2)
      {
        return (*this).quadratic_form();
      }
      else
      {
        std:: vector<double> roots;
        const int NEG_PIVOT = -100.75, POS_PIVOT = 100.75;
        int num_neg = rule_of_signs(false), num_pos = rule_of_signs(true), count = 0;
        
        
        
        
        
        
        // if a new roots is found, then num_neg/num_pos is decremented 
        // first root pivot are the constants. then when a new roots is found, the inital pivot is the bisection between roots and x = 0)
        
        int max_pos_pivot = 0;
        
        // if root from neg pivot is positive, skip this step 
        while(num_neg > 0)
        {}
        
        
        
        
        // if root from pos pivot is negative, skip this step
        while (num_pos > 0)
        {}
        
        return roots;
      }
      
    }
    
    
    // Uses newton's method to appox a root and returns a root, with pivot being the inital value
    // Because this class only deals with polynomials, we won't have to worry about horizontal/vertical asymptotes
    double newton_approx(double pivot) {
      
      Polynomial ddx = (*this).derivative();
      double tolerance = 2e-7, numer = f(pivot), denom = ddx.f(pivot);
      
      double initial = pivot;
      
      int count = 1;
      
      while (!(numer < tolerance && numer > -tolerance) && count < 1000 )
      {
        
        if (count % 100 == 0 || denom == 0)
        { 
          cout << "Bad inital value";
          
          initial /= 2.1;
          pivot = initial;
        }
        
        pivot = pivot - (numer / denom);
        
        cout << pivot - (numer / denom) << "\n";
        count ++;
        numer = f(pivot);
        denom = ddx.f(pivot);
      }
    
      
      //cout << "count: " << count << "\n";
      return round(pivot * 1000)/ 1000.0; 
    } 
    
    
    // Implementation of Decartes' rule of signs 
    int rule_of_signs(bool pos_roots) const
    {
      int sum = 0, compare = degree+1;
      
      // to find the first term of the polynomial, so that its sign can be compared to the following terms
      for (int n = 0; n <= degree; n++)    
      {
        if (coeff[n] != 0)
        {
          compare = n;
          break;
        }
      }
      
      // If we want the max number of negative roots
      double coeff_arr[degree+1] = {};
      for (int n = 0; n <= degree; n++)    
      {
        coeff_arr[n] = coeff[n];
        
        if (!pos_roots)
          coeff_arr[n] *= pow(-1, n); 
      }
      
      for (int n = compare+1; n <= degree; n++)
      {
        if (coeff_arr[n] != 0)
        {
          
          if (coeff_arr[n] * coeff_arr[compare] < 0)
            sum++; 
      
          compare = n;
        } 
      }
    
      return sum;
    }
    
    string toString()
    {
      std::ostringstream oss;
      oss << std::setprecision(8) << std::noshowpoint;
      
      if (degree == 0)
      {
        oss << coeff[0];
        
        return oss.str(); 
      }
      
      for (int n = degree; n > 1; n--)
      {
        
        
        if (coeff[n] != 0)
        {
          oss << coeff[n] << "x^" << n << " + ";
        }
      }
    
      if (coeff[1] != 0)
      {
        oss << coeff[1] << "x"; 
        
        if (coeff[0] != 0)
          oss << " + ";
        else
          return oss.str();
      }


      oss << coeff[0];
      
      return oss.str();
    }
    
    // Factors a polynomial iff it has rational roots. Uses synthetic division. Returns an array of Polynomials 
    Polynomial factor();
  
};



int main() {
  
  double test1[] = {-0.5, -2, 3, 0.4, 0.5, 3, 0, 7.14, -M_PI};
  
  
  
  Polynomial test2 = Polynomial(test1, 8);
  
  Polynomial test3 = Polynomial(0);
  test3.setCoeff(0, 5);
  // cout << test3.toString() << "\n";
  
  Polynomial test4 = Polynomial(1);
  test4.setCoeff(0, -2);
  test4.setCoeff(1, 3); 
  // cout << test4.toString() << "\n";
  
  Polynomial test5 = Polynomial(2);
  test5.setCoeff(0, 15);
  test5.setCoeff(1, 0.35);
  test5.setCoeff(2, -1.1);  
  
 //  test3.quadratic_form(); cout << "\n";
 // test4.quadratic_form(); cout << "\n";
  // test5.quadratic_form(); cout << "\n";
  
  Polynomial test6 = test5.derivative();
  
  /*
  cout << test5.toString() << "\n";
  cout << test2.toString() << "\n";
  cout << (test2*-1.2).toString() << "\n";
  cout << test6.toString() << "\n";
  
  cout << (test5+test2+test6+(test2*-1.2)).toString();
  */
  
  /*
  test6.quadratic_form(); cout << "\n";
  cout << test6.toString() << "\n";
  
  cout << test2.f(-0.1947) << "\n"; 
  cout << test2.newton_approx(-0.4) << "\n"; 
  */
  
  /*
  Polynomial test7 = test5 * test4;
  
  cout << test4.toString() << "\n";
  cout << test5.toString() << "\n";
  cout << test7.toString() << "\n";
  
  Polynomial test8 = test5 * test7 * test4;
  cout << test8.toString() << "\n";
  
  
  
  cout << test8.newton_approx(0);
  */
 
  Polynomial test9 = Polynomial(3);
  test9.setCoeff(0, 2);
  test9.setCoeff(1, -3);
  test9.setCoeff(2, 0); 
  test9.setCoeff(3, 1);  
  
  cout << test9.toString() << "\n";
  
  // cout << "rule of signs: " << test9.rule_of_signs(true) << "\n";
  
  
  
  
  
  
  
  
  
  double degreeTwo[3] = {6, 4, 1};
  double degreeEight[9] = {-0.05, 0.6, 2, -4, -10, -1, -1, -1, 2};
  double degreeFive[6] = {1, 0, 0, -2, 0, 1};
  double WHAT_THE_FUCK[9] = {14368337, -6109671, -23320083, 6265541, 4345335, -1397103, 37795, 2398, 21};
  
  Polynomial test10 = Polynomial(degreeEight, 8);
  
  /*
  cout << test10.rule_of_signs(true) << " " << test10.rule_of_signs(false) << "\n";
  cout << test10.toString() << "\n" << test10.newton_approx(-100.75) << "\n"
       << test10.newton_approx(100.75) << "\n"
       << test10.newton_approx(-0.6005) << "\n"
       << test10.newton_approx(0.9205) << "\n"
       << test10.newton_approx(-0.2895) << "\n"
       << test10.newton_approx(0.1965) << "\n";
  */
       
  cout << "\n\n\n\n";
  
  /*
  Polynomial test11 = Polynomial(WHAT_THE_FUCK, 8);
  
  cout << test11.rule_of_signs(true) << " " << test10.rule_of_signs(false) << "\n"
       << test11.newton_approx(-100.75) << "\n"
       << test11.newton_approx(100.75) << "\n"
       << test11.toString() << "\n";
   */
   
   Polynomial test12 = Polynomial(degreeFive, 5);
   
   cout << "num neg roots: " << test12.rule_of_signs(false) << "\n"
        << "num pos roots: " << test12.rule_of_signs(true) << "\n"
        << test12.toString() << "\n"
        << test12.newton_approx(-100.75) << "\n"
        << test12.newton_approx(1.179/2) << "\n";
       
       
       
  /* 
  Polynomial test10 = Polynomial(degreeTwo, 2);
   
  double *roots;
  int num_roots = 0;
  roots = test10.find_roots(num_roots);
  
  
  if (num_roots == 0)
  {
    cout << "No real roots/Infinite roots"; 
  }
  else
  {
    cout << "Roots at [";
    for (int count = 0; count < num_roots-1; count++)
    {
      cout << roots[count] << ", ";
    }
    
    cout << roots[num_roots-1] << "]";
  }
 
  
  //cout << test9.newton_approx(-100.75) << "\n";
  //cout << test9.newton_approx(100.75); 
  
  */
  
  
   
  /*
  cout << test2.getDegree() << "\n";
  cout << test2.f(3) <<  "\n";
  cout << test2.toString() << "\n" << test2.getCoeff(1) << "\n";
  cout << test2.getCoeff();
  */
  
  return 0;
}