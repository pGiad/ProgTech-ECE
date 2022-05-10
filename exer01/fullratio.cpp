#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int rational::gcd(int a, int b)
{
  a = abs(a);
  b = abs(b);
  while (a > 0 && b > 0)
  {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }
  return a + b;
}

rational::rational(int n, int d)
{
  int k, a = n, b = d;
  a = abs(a);
  b = abs(b);
  while (a > 0 && b > 0)
  {
    if (a > b)
      a = a % b;
    else
      b = b % a;
  }
  k = a + b;
  nom = n / k;
  den = d / k;
  if (den < 0)
  {
    nom = -nom;
    den = -den;
  }
}

rational operator+(const rational &x, const rational &y)
{
  int n, d, g;
  n = x.nom * y.den + x.den * y.nom;
  d = x.den * y.den;
  rational t(n, d);
  g = t.gcd(n, d);
  t.nom = n / g;
  t.den = d / g;
  if (t.den < 0)
  {
    t.nom = -t.nom;
    t.den = -t.den;
  }
  return t;
}

rational operator-(const rational &x, const rational &y)
{
  int n, d, g;
  n = x.nom * y.den - x.den * y.nom;
  d = x.den * y.den;
  rational t(n, d);
  g = t.gcd(n, d);
  t.nom = n / g;
  t.den = d / g;
  if (t.den < 0)
  {
    t.nom = -t.nom;
    t.den = -t.den;
  }
  return t;
}

rational operator*(const rational &x, const rational &y)
{
  int n, d, g;
  n = x.nom * y.nom;
  d = x.den * y.den;
  rational t(n, d);
  g = t.gcd(n, d);
  t.nom = n / g;
  t.den = d / g;
  if (t.den < 0)
  {
    t.nom = -t.nom;
    t.den = -t.den;
  }
  return t;
}

rational operator/(const rational &x, const rational &y)
{
  int n, d, g;
  n = x.nom * y.den;
  d = x.den * y.nom;
  rational t(n, d);
  g = t.gcd(n, d);
  t.nom = n / g;
  t.den = d / g;
  if (t.den < 0)
  {
    t.nom = -t.nom;
    t.den = -t.den;
  }
  return t;
}

std::ostream &operator<<(std::ostream &out, const rational &x)
{
  return out << x.nom << "/" << x.den;
}