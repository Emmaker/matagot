/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* log2, log2f, log2l - compute base 2 logarithm functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the base 2 logarithm of their argument x, 
   log2(x).

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the base 2 
   logarithm of x.

   If x is +/-0, a pole error shall occur and log2(), log2f(), and log2l() 
   shall return -HUGE_VAL, -HUGE_VALF, and -HUGE_VALL, respectively.

   For finite values of x that are less than 0, or if x is -Inf, a domain 
   error shall occur, and either a NaN (if supported), or an implementation-
   defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is 1, +0 shall be returned.

   If x is +Inf, x shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error
   The finite value of x is less than zero, or x is -Inf. 
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
*/

#include "xmath.h"

double (log2) (double x)
{
  int e;
  double y;

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
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      if (x == 1.0)
	return +0.0;
      y = frexp (x, &e);
      if (y < M_SQRT1_2)
	{
	  y += y;
	  --e;
	}
      return (double) e + log (y) * M_LOG2E;
    }
}

float (log2f) (float x)
{
  int e;
  float y;

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
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALF;
    default:
      if (_Getsign ((unsigned char *) &x, _Flt))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      if (x == 1.0F)
	return +0.0F;
      y = frexpf (x, &e);
      if (y < _M_SQRT1_2F)
	{
	  y += y;
	  --e;
	}
      return (float) e + logf (y) * _M_LOG2EF;
    }
}

long double (log2l) (long double x)
{
  int e;
  long double y;

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
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALL;
    default:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      if (x == 1.0L)
	return +0.0L;
      y = frexpl (x, &e);
      if (y < _M_SQRT1_2L)
	{
	  y += y;
	  --e;
	}
      return (long double) e + logl (y) * _M_LOG2EL;
    }
}

/* END OF FILE */
