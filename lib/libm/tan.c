/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* tan, tanf, tanl - tangent function

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the tangent of their argument x, measured 
   in radians.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the tangent of x.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and tan(), tanf(), and tanl() shall return 
   0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
   defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, tan(), tanf(), and tanl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   If x is +/-Inf, a domain error shall occur, and either a NaN (if 
   supported), or an implementation-defined value shall be returned. 

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

   If the correct value would cause overflow, a range error shall occur and 
   tan(), tanf(), and tanl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and 
   +/-HUGE_VALL, respectively, with the same sign as the correct value of the 
   function.

   ERRORS

   These functions shall fail if:
   Domain Error
   The value of x is +/-Inf. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Range Error
   The result overflows. 
   
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:
   Range Error
   The result underflows, or the value of x is subnormal.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

static long double
_Tan (long double x)
{
  long double z = x * x, t = x, sum = x, n = 1.0L, y;

  do
    {
      y = sum;
      n += 2.0;
      t *= -z / (n * (n - 1.0L));
      sum += t;
    }
  while (y != sum);
  return sum;
}

double (tan) (double x)
{
  double y;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    default:
      y = (double) _Tan (x);
      switch (_Fpclassify (y))
	{
	case FP_INFINITE:
	  _Matherr (ERANGE, FE_OVERFLOW);
	  return _Getsign ((unsigned char *) &y,
			   _Dbl) ? -HUGE_VAL : +HUGE_VAL;
	case FP_SUBNORMAL:
	  _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
	}
      return y;
    }
}

float (tanf) (float x)
{
  float y;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    default:
      y = (float) _Tan (x);
      switch (_Fpclassifyf (y))
	{
	case FP_INFINITE:
	  _Matherr (ERANGE, FE_OVERFLOW);
	  return _Getsign ((unsigned char *) &y,
			   _Flt) ? -HUGE_VALF : +HUGE_VALF;
	case FP_SUBNORMAL:
	  _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
	}
      return y;
    }
}

long double (tanl) (long double x)
{
  long double y;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    default:
      y = _Tan (x);
      switch (_Fpclassifyl (y))
	{
	case FP_INFINITE:
	  _Matherr (ERANGE, FE_OVERFLOW);
	  return _Getsign ((unsigned char *) &y,
			   _Ldbl) ? -HUGE_VALL : +HUGE_VALL;
	case FP_SUBNORMAL:
	  _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
	}
      return y;
    }
}

/* END OF FILE */
