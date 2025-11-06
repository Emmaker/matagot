/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* sqrt, sqrtf, sqrtl - square root function

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:
   
   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard. 

   These functions shall compute the square root of their argument x. 

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept (FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept (FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the square root 
   of x.

   For finite values of x < -0, a domain error shall occur, and either a NaN 
   (if supported), or an implementation-defined value shall be returned.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +Inf, x shall be returned.

   If x is -Inf, a domain error shall occur, and a NaN shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error

   The finite value of x is < -0, or x is -Inf. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   ALGORITHM:
   
   This version uses the Newton-Raphson-Horner method to close in on the
   square root.
*/

#include "xmath.h"

double (sqrt) (double x)
{
  double d, y;
  int s, e;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      s = _Getsign ((unsigned char *) &x, _Dbl);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      return x;
    default:
      s = _Getsign ((unsigned char *) &x, _Dbl);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Dbl->_Nan._D;
	}
      frexp (x, &e);
      y = ldexp (x, -e / 2);
      do
	{
	  d = y;
	  y = (y + x / y) / 2.0;
	  d -= y;
	}
      while (_Fpclassify (d) != FP_ZERO);
      return y;
    }
}

float (sqrtf) (float x)
{
  float d, y;
  int s, e;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      s = _Getsign ((unsigned char *) &x, _Flt);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      return x;
    default:
      s = _Getsign ((unsigned char *) &x, _Flt);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Flt->_Nan._F;
	}
      frexpf (x, &e);
      y = ldexpf (x, -e / 2);
      do
	{
	  d = y;
	  y = (y + x / y) / 2.0F;
	  d -= y;
	}
      while (_Fpclassifyf (d) != FP_ZERO);
      return y;
    }
}

long double (sqrtl) (long double x)
{
  long double d, y;
  int s, e;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      s = _Getsign ((unsigned char *) &x, _Ldbl);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      return x;
    default:
      s = _Getsign ((unsigned char *) &x, _Ldbl);
      if (s)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Ldbl->_Nan._L;
	}
      frexpl (x, &e);
      y = ldexpl (x, -e / 2);
      do
	{
	  d = y;
	  y = (y + x / y) / 2.0L;
	  d -= y;
	}
      while (_Fpclassifyl (d) != FP_ZERO);
      return y;
    }
}

/* END OF FILE */
