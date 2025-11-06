/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* lrint, lrintf, lrintl - round to the nearest integer value using current 
   rounding direction
   
   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall round their argument to the nearest integer value, 
   rounding according to the current rounding direction.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the rounded 
   integer value.

   If x is NaN, a domain error shall occur, and an unspecified value is 
   returned.

   If x is +Inf, a domain error shall occur and an unspecified value is 
   returned.

   If x is -Inf, a domain error shall occur and an unspecified value is 
   returned.

   If the correct value is positive and too large to represent as a long long, 
   an unspecified value shall be returned.  On systems that support the 
   IEC 60559 Floating-Point option, a domain error shall occur; otherwise, a 
   domain error may occur.

   If the correct value is negative and too large to represent as a long long, 
   an unspecified value shall be returned.  On systems that support the 
   IEC 60559 Floating-Point option, a domain error shall occur; otherwise, a
   domain error may occur.

   ERRORS:

   These functions shall fail if:

   Domain Error
   The x argument is NaN or +/-Inf, or the correct value is not representable 
   as an integer. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to EDOM. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the invalid floating-point exception shall 
   be raised.

   These functions may fail if:
   Domain Error
   The correct value is not representable as an integer. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then
   errno shall be set to EDOM. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the invalid floating-point exception shall
   be raised.
*/

#include "xmath.h"
#include <limits.h>

long (lrint) (double x)
{
  double y = 0.0, z = 0.0;
  long r;

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
      z = modf (x, &y);
      if (z >= 0.5)
	y += 1.0;
      else if (z <= -0.5)
	y -= 1.0;
      if (y < LONG_MIN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MIN;
	}
      else if (y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MAX;
	}
      else
	{
	  r = y;
	  return r;
	}
    }
}

long (lrintf) (float x)
{
  float y = 0.0F, z = 0.0F;
  long r;

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
      z = modff (x, &y);
      if (z >= 0.5F)
	y += 1.0F;
      else if (z <= -0.5F)
	y -= 1.0F;
      if (y < LONG_MIN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MIN;
	}
      else if (y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MAX;
	}
      else
	{
	  r = y;
	  return r;
	}
    }
}

long (lrintl) (long double x)
{
  long double y = 0.0L, z = 0.0L;
  long r;

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
      z = modfl (x, &y);
      if (z >= 0.5L)
	y += 1.0L;
      else if (z <= -0.5L)
	y -= 1.0L;
      if (y < LONG_MIN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MIN;
	}
      else if (y > LONG_MAX)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return LONG_MAX;
	}
      else
	{
	  r = y;
	  return r;
	}
    }
}

/* END OF FILE */
