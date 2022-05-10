#include <iostream>
#ifndef CONTEST
#include "babyratio.hpp"
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

rational rational::add(rational r)
{
  int n, d, g;
  n = r.nom * den + r.den * nom;
  d = r.den * den;
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

rational rational::sub(rational r)
{
  int n, d, g;
  n = r.den * nom - r.nom * den;
  d = r.den * den;
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

rational rational::mul(rational r)
{
  int n, d, g;
  n = r.nom * nom;
  d = r.den * den;
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

rational rational::div(rational r)
{
  int n, d, g;
  n = nom * r.den;
  d = den * r.nom;
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

void rational::print()
{
  cout << nom << "/" << den;
}