// CSE 374
// HW 7
// Luke Jiang
// MAY 31 2018

// This file implements the Rational class defined in Rational.h

#include <cmath>
#include "Rational.h"

int get_gcd(int a, int b);

namespace cse374 {

/* Replace this line with your implementation of the Rational type */
Rational::Rational() : Rational(0, 1) { }

Rational::Rational(int n) : Rational(n, 1) { }

Rational::Rational(int n, int d) {
  int pos = n * d >= 0 ? 1 : -1;
  int gcd = get_gcd(std::abs(n), std::abs(d));
  if (d == 0) {
    num_ = n;
    denom_ = d;
  } else if (gcd != 0) {
    num_ = pos * std::abs(n) / gcd;
    denom_ = std::abs(d) / gcd;
  } else {
    num_ = n;
    denom_ = d;
  }
}

int Rational::n() const {
  return num_;
}
int Rational::d() const {
  return denom_;
}

Rational Rational::plus(Rational other) const {
  int n = num_ * other.d() + denom_ * other.n();
  int d = denom_ * other.d();
  return Rational(n, d);
}

Rational Rational::minus(Rational other) const {
  int n = num_ * other.d() - denom_ * other.n();
  int d = denom_ * other.d();
  return Rational(n, d);
}

Rational Rational::times(Rational other) const {
  int n = num_ * other.n();
  int d = denom_ * other.d();
  return Rational(n, d);
}

Rational Rational::div(Rational other) const {
  int n = num_ * other.d();
  int d = denom_ * other.n();
  return Rational(n, d);
}

}  // namespace

int get_gcd(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}
