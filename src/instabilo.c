#define _GNU_SOURCE

#include <stdio.h>
#include <fenv.h>
#include <dlfcn.h>
#include <assert.h>

#define UNARY_WRAPPER(name) \
  SINGLE_MATH(name) \
  DOUBLE_MATH(name) \
  LONG_DOUBLE_MATH(name)

#define WRAPPER(name) 

#define SINGLE_MATH(name) \
  float name ## f(float x){ \
    INSTRUMENTED_MATH(float, name ## f, x);\
  }

#define DOUBLE_MATH(name) \
  double name(double x){ \
    INSTRUMENTED_MATH(double, name, x);\
  }

#define LONG_DOUBLE_MATH(name) \
  long double name ## l(long double x){ \
    return 0; \
  }
	
#define INSTRUMENTED_MATH(type, name, x) do{ \
    int round = fegetround();\
    type (*f)(type) = dlsym(RTLD_NEXT, #name); \
    assert(f); \
    type res = f(x); \
    fesetround(round); \
    return res; \
  }while(0)

UNARY_WRAPPER(fabs)
UNARY_WRAPPER(exp)
UNARY_WRAPPER(exp2)
UNARY_WRAPPER(expm1)
UNARY_WRAPPER(log)
UNARY_WRAPPER(log2)
UNARY_WRAPPER(log10)
UNARY_WRAPPER(log1p)
UNARY_WRAPPER(logb)
UNARY_WRAPPER(sqrt)
UNARY_WRAPPER(cbrt)
UNARY_WRAPPER(sin)
UNARY_WRAPPER(cos)
UNARY_WRAPPER(tan)
UNARY_WRAPPER(asin)
UNARY_WRAPPER(acos)
UNARY_WRAPPER(sinh)
UNARY_WRAPPER(cosh)
UNARY_WRAPPER(tanh)
UNARY_WRAPPER(asinh)
UNARY_WRAPPER(acosh)
UNARY_WRAPPER(atanh)
UNARY_WRAPPER(erf)
UNARY_WRAPPER(erfc)
UNARY_WRAPPER(lgamma)
UNARY_WRAPPER(tgamma)
UNARY_WRAPPER(ceil)
UNARY_WRAPPER(floor)
UNARY_WRAPPER(trunc)
UNARY_WRAPPER(round)
UNARY_WRAPPER(nearbyint)
UNARY_WRAPPER(rint)
