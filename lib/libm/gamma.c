/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* gamma.c - lgamma and tgamma functions

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:
   
   tgamma, tgammaf, tgammal - compute gamma() function

   SYNOPSIS

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute Gamma(x) where Gamma(x) is defined as
   
               INF
               --
     _        |  |  
    |         |      -t   x-1
    |(x) = |  |     e   t     dt
            -- 
             0  

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the gamma of x.

   If x is a negative integer, a domain error may occur and either a NaN 
   (if supported) or an implementation-defined value shall be returned. 
   On systems that support the IEC 60559 Floating-Point option, a domain 
   error shall occur and a NaN shall be returned. 

   If x is +/-0, tgamma(), tgammaf(), and tgammal() shall return +/-HUGE_VAL, 
   +/-HUGE_VALF, and +/-HUGE_VALL, respectively.  On systems that support the 
   IEC 60559 Floating-Point option, a pole error shall occur; otherwise, a 
   pole error may occur.

   If the correct value would cause overflow, a range error shall occur and 
   tgamma(), tgammaf(), and tgammal() shall return +/-HUGE_VAL, +/-HUGE_VALF, 
   or +/-HUGE_VALL, respectively, with the same sign as the correct value of 
   the function.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and tgamma(), tgammaf(), and tgammal() shall 
   return 0.0, or (if IEC 60559 Floating-Point is not supported) an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

   If x is subnormal and 1/x is representable, 1/x should be returned.

   If x is NaN, a NaN shall be returned.

   If x is +Inf, x shall be returned.

   If x is -Inf, a domain error shall occur, and a NaN shall be returned.

   ERRORS

   These functions shall fail if:

   Domain Error 
   The value of x is a negative integer, or x is -Inf. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error
   The value of x is zero. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error
   The value overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:
   
   Domain Error
   The value of x is a negative integer. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error
   The value of x is zero. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error
   The result underflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   lgamma, lgammaf, lgammal, signgam - log gamma function

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the natural logarithm of |Gamma(x)| where 
   Gamma(x) is defined as above.
  
   The argument x need not be a non-positive integer (Gamma(x) is defined over 
   the reals, except the non-positive integers).

   If x is NaN, -Inf, or a negative integer, the value of signgam is 
   unspecified. 

   These functions need not be thread-safe.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions.
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO | 
   FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the logarithmic 
   gamma of x.

   If x is a non-positive integer, a pole error shall occur and lgamma(), 
   lgammaf(), and lgammal() shall return +HUGE_VAL, +HUGE_VALF, and +HUGE_VALL, 
   respectively.

   If the correct value would cause overflow, a range error shall occur and 
   lgamma(), lgammaf(), and lgammal() shall return +/-HUGE_VAL, +/-HUGE_VALF, 
   and +/-HUGE_VALL (having the same sign as the correct value), respectively.

   If x is NaN, a NaN shall be returned.

   If x is 1 or 2, +0 shall be returned.

   If x is +/-Inf, +Inf shall be returned.

   ERRORS

   These functions shall fail if:
   Pole Error
   The x argument is a negative integer or zero. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error
   The result overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

int signgam = 0;

static long double
_Lgamma (long double x, int *signgam)
{
  long double t, y, z, r, w;
  int i;

  *signgam = 1;

  if (x < 0.0L)
    {
      *signgam = -1;
      x = -x;
    }

  if (x < 10.0L)
    {
      return _Lgamma (x + 1.0L, signgam) - logl (x);
    }

  w = 1.0L / (x * x);
  t = logl (x);
  y =
    0.5L * logl (2.0L * _M_PIL) + (x - 0.5L) * t - x + logl (1.0L +
							     1.0L / (12.0L *
								     x));
  z = t * t;
  r =
    w * (1.0L / 12.0L -
	 w * (1.0L / 120.0L - w * (1.0L / 252.0L - w * (1.0L / 240.0L))));
  y += r - 0.5L * z;
  return y;
}

static long double
_Tgamma (long double x, int *signgam)
{
  long double t, y, z, r, w;
  int i;

  *signgam = 1;

  if (x < 0.0L)
    {
      *signgam = -1;
      x = -x;
    }

  if (x < 10.0L)
    return _Tgamma (x + 1.0L, signgam) / x;

  w = 1.0L / (x * x);
  t = logl (x);
  y =
    0.5L * logl (_M_PIL * _M_PIL) + (x - 0.5L) * t - x + logl (1.0L +
							       1.0L / (12.0L *
								       x));
  z = t * t;
  r =
    w * (1.0L / 12.0L -
	 w * (1.0L / 120.0L - w * (1.0L / 252.0L - w * (1.0L / 240.0L))));
  y += r - 0.5L * z;
  return *signgam * expl (y);
}

double
(lgamma) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return +HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *) &x, _Dbl) && x == trunc (x))
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VAL;
	}
      if (x == 1.0 || x == 2.0)
	return +0.0;
      return (double) _Lgamma (x, &signgam);
    }
}

float
(lgammaf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Setsign ((unsigned char *) &x, _Flt, 0);
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return +HUGE_VALF;
    default:
      if (_Getsign ((unsigned char *) &x, _Flt) && x == truncf (x))
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VALF;
	}
      if (x == 1.0F || x == 2.0F)
	return +0.0F;
      return (float) _Lgamma (x, &signgam);
    }
}

long double
(lgammal) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return +HUGE_VALL;
    default:
      if (_Getsign ((unsigned char *) &x, _Ldbl) && x == truncl (x))
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return +HUGE_VALL;
	}
      if (x == 1.0L || x == 2.0L)
	return +0.0L;
      return _Lgamma (x, &signgam);
    }
}

double
(tgamma) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      else
	return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Dbl) ? -HUGE_VAL : +HUGE_VAL;
    case FP_SUBNORMAL:
      return 1.0 / x;
    default:
      return (double) _Tgamma (x, &signgam);
    }
}

float
(tgammaf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Flt))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      else
	return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Flt) ? -HUGE_VALF : +HUGE_VALF;
    case FP_SUBNORMAL:
      return 1.0F / x;
    default:
      return (float) _Tgamma (x, &signgam);
    }
}

long double
(tgammal) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      else
	return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -HUGE_VALL : +HUGE_VALL;
    case FP_SUBNORMAL:
      return 1.0L / x;
    default:
      return _Tgamma (x, &signgam);
    }
}

/* END OF FILE */
