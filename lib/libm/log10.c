/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* log10, log10f, log10l - base 10 logarithm function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the base 10 logarithm of their argument x. 

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the base 10 
   logarithm of x.

   If x is +/-0, a pole error shall occur and log10(), log10f(), and 
   log10l() shall return -HUGE_VAL, -HUGE_VALF, and -HUGE_VALL, respectively.

   For finite values of x that are less than 0, or if x is -Inf, a domain 
   error shall occur, and either a NaN (if supported), or an implementation-
   defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is 1, +0 shall be returned.

   If x is +Inf, +Inf shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error
   The finite value of x is negative, or x is -Inf.
    
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

double (log10) (double x)
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
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      return (x == 1.0) ? +0.0 : log (x) * M_LOG10E;
    }
}

float (log10f) (float x)
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
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALF;
    default:
      return (x == 1.0F) ? +0.0F : logf (x) * _M_LOG10EF;
    }
}

long double (log10l) (long double x)
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
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALL;
    default:
      return (x == 1.0L) ? +0.0L : logl (x) * _M_LOG10EL;
    }
}

/* END OF FILE */
