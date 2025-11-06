/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* lround, lroundf, lroundl - round to the nearest integer value

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall round their argument to the nearest integer value in 
   floating-point format, rounding halfway cases away from zero, regardless of 
   the current rounding direction.

   RETURN VALUE:

   Upon successful completion, these functions shall return the rounded 
   integer value.

   If x is NaN, a domain error shall occur and an unspecified value is 
   returned.

   If x is +Inf, a domain error shall occur and an unspecified value is 
   returned.

   If x is -Inf, a domain error shall occur and an unspecified value is 
   returned.

   If the correct value is positive and too large to represent as a long, an 
   unspecified value shall be returned. On systems that support the IEC 
   60559 Floating-Point option, a domain error shall occur; otherwise, a 
   domain error may occur.

   If the correct value is negative and too large to represent as a long, an 
   unspecified value shall be returned. On systems that support the IEC 
   60559 Floating-Point option, a domain error shall occur; otherwise, a 
   domain error may occur.

   ERRORS:

   These functions shall fail if:
   Domain Error
   The x argument is NaN or +/-Inf, or the correct value is not representable 
   as an integer. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   These functions may fail if:
   Domain Error
   The correct value is not representable as an integer. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.
*/

#include "xmath.h"

long (lround) (double x)
{
  double y;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return 0L;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Dbl) ? LONG_MIN : LONG_MAX;
    case FP_ZERO:
      return 0L;
    default:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	y = trunc (x - 0.5);
      else
	y = trunc (x + 0.5);
      if (y < LONG_MIN || y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Getsign ((unsigned char *) &x, _Dbl) ? LONG_MIN : LONG_MAX;
	}
      else
	return (long) y;
    }
}

long (lroundf) (float x)
{
  float y;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return 0L;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Flt) ? LONG_MIN : LONG_MAX;
    case FP_ZERO:
      return 0L;
    default:
      if (_Getsign ((unsigned char *) &x, _Flt))
	y = truncf (x - 0.5F);
      else
	y = truncf (x + 0.5F);
      if (y < LONG_MIN || y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Getsign ((unsigned char *) &x, _Flt) ? LONG_MIN : LONG_MAX;
	}
      else
	return (long) y;
    }
}

long (lroundl) (long double x)
{
  long double y;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return 0L;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Getsign ((unsigned char *) &x, _Ldbl) ? LONG_MIN : LONG_MAX;
    case FP_ZERO:
      return 0L;
    default:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	y = truncl (x - 0.5L);
      else
	y = truncl (x + 0.5L);
      if (y < LONG_MIN || y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return _Getsign ((unsigned char *) &x, _Ldbl) ? LONG_MIN : LONG_MAX;
	}
      else
	return (long) y;
    }
}

/* END OF FILE */
