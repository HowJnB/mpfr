/*
Copyright 2005, 2006, 2007, 2008, 2009 Free Software Foundation, Inc.
Contributed by Patrick Pelissier, INRIA.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include "mfv5.h"
#include "mpfr.h"
#include "timp.h"

using namespace std;

/* Register New Test */
template <class T>
class mpfr_test : public registered_test {
private:
  unsigned long size;
  mpfr_t *table;
  mpfr_t a, b, c;
  timming *tim;
public:
  mpfr_test (const char *n) : registered_test (n), size (0) {}
  ~mpfr_test () {
    if (size != 0) {
      unsigned long i;
      delete tim;
      mpfr_clears (a, b, c, NULL);
      for (i = 0 ; i < size ; i++)
	mpfr_clear (table[i]);
      delete[] table;
    }
  }
  bool test (const vector<string> &base, const option_test &opt);
};

class mpfr_add_test {
public:
  int func(mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_add (a,b,c,r);
  }
};

class mpfr_sub_test {
public:
  int func(mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_sub (a,b,c,r);
  }
};

class mpfr_mul_test {
public:
  int func(mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_mul (a,b,c,r);
  }
};
class mpfr_div_test {
public:
  int func(mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_div (a,b,c,r);
  }
};
class mpfr_set_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_set (a,b,r);
  }
};
class mpfr_sqrt_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_sqrt (a,b,r);
  }
};
class mpfr_exp_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_exp (a,b,r);
  }
};
class mpfr_log_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_log (a,b,r);
  }
};
class mpfr_erf_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_erf (a,b,r);
  }
};
class mpfr_cos_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_cos (a,b,r);
  }
};
class mpfr_sin_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_sin (a,b,r);
  }
};
class mpfr_tan_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_tan (a,b,r);
  }
};
class mpfr_acos_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_acos (a,b,r);
  }
};
class mpfr_asin_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_asin (a,b,r);
  }
};
class mpfr_atan_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_atan (a,b,r);
  }
};
class mpfr_cosh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_cosh (a,b,r);
  }
};
class mpfr_sinh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_sinh (a,b,r);
  }
};
class mpfr_tanh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_tanh (a,b,r);
  }
};
class mpfr_acosh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_acosh (a,b,r);
  }
};
class mpfr_asinh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_asinh (a,b,r);
  }
};
class mpfr_atanh_test {
public:
  int func (mpfr_ptr a, mpfr_srcptr b, mpfr_srcptr c, mp_rnd_t r) {
    return mpfr_atanh (a,b,r);
  }
};


static mpfr_test<mpfr_add_test> test1 ("mpfr_add");
static mpfr_test<mpfr_sub_test> test2 ("mpfr_sub");
static mpfr_test<mpfr_mul_test> test3 ("mpfr_mul");
static mpfr_test<mpfr_div_test> test4 ("mpfr_div");
static mpfr_test<mpfr_set_test> test5 ("mpfr_set");

static mpfr_test<mpfr_sqrt_test> test6 ("mpfr_sqrt");
static mpfr_test<mpfr_exp_test>  test7 ("mpfr_exp");
static mpfr_test<mpfr_log_test>  test8 ("mpfr_log");
static mpfr_test<mpfr_log_test>  test9 ("mpfr_erf");

static mpfr_test<mpfr_cos_test>  testA ("mpfr_cos");
static mpfr_test<mpfr_sin_test>  testB ("mpfr_sin");
static mpfr_test<mpfr_tan_test>  testC ("mpfr_tan");
static mpfr_test<mpfr_acos_test> testD ("mpfr_acos");
static mpfr_test<mpfr_asin_test> testE ("mpfr_asin");
static mpfr_test<mpfr_atan_test> testF ("mpfr_atan");

static mpfr_test<mpfr_cosh_test>  testAh ("mpfr_cosh");
static mpfr_test<mpfr_sinh_test>  testBh ("mpfr_sinh");
static mpfr_test<mpfr_tanh_test>  testCh ("mpfr_tanh");
static mpfr_test<mpfr_acosh_test> testDh ("mpfr_acosh");
static mpfr_test<mpfr_asinh_test> testEh ("mpfr_asinh");
static mpfr_test<mpfr_atanh_test> testFh ("mpfr_atanh");

/* Do the test */
template <class T>
bool mpfr_test<T>::test (const vector<string> &base, const option_test &opt) {
  unsigned long i;
  unsigned long long m;
  T f;
  bool cont = false;

  /* Init and set tables if first call */
  if (size == 0) {
    size = base.size ();
    tim = new timming (size);
    table = new mpfr_t[size];
    for (i = 0 ; i < size ; i++) {
      mpfr_init2 (table[i], opt.prec);
      mpfr_set_str (table[i], base[i].c_str(), 10, GMP_RNDN);
    }
    mpfr_inits2 (opt.prec, a, b, c, NULL);
  }

  /* Do Measure */
  for(i = 0 ; i < (size-1) ; i++) {
    mpfr_set (b, table[i], GMP_RNDN);
    mpfr_set (c, table[i+1], GMP_RNDN);
    TIMP_OVERHEAD ();
    m = TIMP_MEASURE (f.func (a, b, c, GMP_RNDN) ); 
    cont = tim->update (i, m) || cont;
  }

  tim->print (get_name(), opt);
  return cont;
}
