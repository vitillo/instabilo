#define _GNU_SOURCE

#include <stdio.h>
#include <fenv.h>
#include <dlfcn.h>
#include <assert.h>

/* Unary Functions */

#define UNARY_FIXED_WRAPPER(rettype, name) \
  UNARY_SINGLE_MATH(rettype, name) \
  UNARY_DOUBLE_MATH(rettype, name) \
  UNARY_LONG_DOUBLE_MATH(rettype, name)

#define UNARY_WRAPPER(name) \
  UNARY_SINGLE_MATH(float, name) \
  UNARY_DOUBLE_MATH(double, name) \
  UNARY_LONG_DOUBLE_MATH(long double, name)

#define UNARY_SINGLE_MATH(rettype, name) \
  rettype name ## f(float x){ \
    UNARY_INSTRUMENTED_MATH(rettype, float, name ## f, x);\
  }

#define UNARY_DOUBLE_MATH(rettype, name) \
  rettype name(double x){ \
    UNARY_INSTRUMENTED_MATH(rettype, double, name, x);\
  }

#define UNARY_LONG_DOUBLE_MATH(rettype, name) \
  rettype name ## l(long double x){ \
    UNARY_INSTRUMENTED_MATH(rettype, long double, name, x); \
  }
	
#define UNARY_INSTRUMENTED_MATH(rettype, type, name, x) do{ \
    int round = fegetround();\
    rettype (*f)(type) = dlsym(RTLD_NEXT, #name); \
    assert(f); \
    rettype res = f(x); \
    fesetround(round); \
    return res; \
  }while(0)

/* Binary Functions */

#define BINARY_FIXED_WRAPPER(ptype, name) \
  BINARY_SINGLE_MATH(float, ptype, name) \
  BINARY_DOUBLE_MATH(double, ptype, name) \
  BINARY_LONG_DOUBLE_MATH(long double, ptype, name)

#define BINARY_WRAPPER(name) \
  BINARY_SINGLE_MATH(float, float, name) \
  BINARY_DOUBLE_MATH(double, double, name) \
  BINARY_LONG_DOUBLE_MATH(long double, long double, name)

#define BINARY_SINGLE_MATH(rettype, ptype, name) \
  rettype name ## f(float x, ptype y){ \
    BINARY_INSTRUMENTED_MATH(rettype, ptype, float, name ## f, x, y); \
  }

#define BINARY_DOUBLE_MATH(rettype, ptype, name) \
  rettype name(double x, ptype y){ \
    BINARY_INSTRUMENTED_MATH(rettype, ptype, double, name ## f, x, y); \
  }

#define BINARY_LONG_DOUBLE_MATH(rettype, ptype, name) \
  rettype name ## l(long double x, ptype y){ \
    BINARY_INSTRUMENTED_MATH(rettype, ptype, long double, name ## f, x, y); \
  }

#define BINARY_INSTRUMENTED_MATH(rettype, ptype, type, name, x, y) do{ \
    int round = fegetround();\
    rettype (*f)(type, ptype) = dlsym(RTLD_NEXT, #name); \
    assert(f); \
    rettype res = f(x, y); \
    fesetround(round); \
    return res; \
  }while(0)

/* Ternary Functions */

#define TERNARY_SINGLE_MATH(ptype, name) \
  float name ## f(float x, float y, ptype z){ \
    TERNARY_INSTRUMENTED_MATH(ptype, float, name ## f, x, y, z); \
  }

#define TERNARY_DOUBLE_MATH(ptype, name) \
  double name(double x, double y, ptype z){ \
    TERNARY_INSTRUMENTED_MATH(ptype, double, name ## f, x, y, z); \
  }

#define TERNARY_LONG_DOUBLE_MATH(ptype, name) \
  long double name ## l(long double x, long double y, ptype z){ \
    TERNARY_INSTRUMENTED_MATH(ptype, long double, name ## f, x, y, z); \
  }

#define TERNARY_INSTRUMENTED_MATH(ptype, type, name, x, y, z) do{ \
  int round = fegetround();\
  type (*f)(type, type, ptype) = dlsym(RTLD_NEXT, #name); \
  assert(f); \
  type res = f(x, y, z); \
  fesetround(round); \
  return res; \
}while(0)


UNARY_WRAPPER(acos)
UNARY_WRAPPER(asin)
UNARY_WRAPPER(atan)
BINARY_WRAPPER(atan2)
UNARY_WRAPPER(ceil)
UNARY_WRAPPER(cos)
UNARY_WRAPPER(cosh)
UNARY_WRAPPER(exp)
UNARY_WRAPPER(fabs)
UNARY_WRAPPER(floor)
BINARY_WRAPPER(fmod)
BINARY_FIXED_WRAPPER(int *, frexp)
BINARY_FIXED_WRAPPER(int, ldexp)
UNARY_WRAPPER(log)
UNARY_WRAPPER(log10)
BINARY_SINGLE_MATH(float, float *, modf)
BINARY_DOUBLE_MATH(double, double *, modf)
BINARY_LONG_DOUBLE_MATH(long double, long double *, modf)
BINARY_WRAPPER(pow)
UNARY_WRAPPER(sin)
UNARY_WRAPPER(sinh)
UNARY_WRAPPER(sqrt)
UNARY_WRAPPER(tan)
UNARY_WRAPPER(tanh)
UNARY_WRAPPER(acosh)
UNARY_WRAPPER(asinh)
UNARY_WRAPPER(atanh)
UNARY_WRAPPER(cbrt)
BINARY_WRAPPER(copysign)
UNARY_WRAPPER(erf)
UNARY_WRAPPER(erfc)
UNARY_WRAPPER(exp2)
UNARY_WRAPPER(expm1)
BINARY_WRAPPER(fdim)
TERNARY_SINGLE_MATH(float, fma)
TERNARY_DOUBLE_MATH(double, fma)
TERNARY_LONG_DOUBLE_MATH(long double, fma)
BINARY_WRAPPER(fmax)
BINARY_WRAPPER(fmin)
BINARY_WRAPPER(hypot)
UNARY_FIXED_WRAPPER(int, ilogb)
UNARY_WRAPPER(lgamma)
UNARY_FIXED_WRAPPER(long int, lrint)
UNARY_FIXED_WRAPPER(long long int, llround)
UNARY_WRAPPER(log1p)
UNARY_WRAPPER(log2)
UNARY_WRAPPER(logb)
UNARY_FIXED_WRAPPER(long long int, llrint)
UNARY_FIXED_WRAPPER(long int, lround)
UNARY_WRAPPER(nearbyint)
BINARY_WRAPPER(next_after)
BINARY_FIXED_WRAPPER(long double, nexttoward)
BINARY_WRAPPER(remainder)
TERNARY_SINGLE_MATH(int *, remquo)
TERNARY_DOUBLE_MATH(int *, remquo)
TERNARY_LONG_DOUBLE_MATH(int *, remquo)
UNARY_WRAPPER(rint)
UNARY_WRAPPER(round)
BINARY_FIXED_WRAPPER(long int, scalbln)
UNARY_WRAPPER(tgamma)
UNARY_WRAPPER(trunc)
