/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* nearbyint, nearbyintf, nearbyintl - floating-point rounding functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall round their argument to an integer value in 
   floating-point format, using the current rounding direction and without 
   raising the inexact floating-point exception.

   RETURN VALUE:

   Upon successful completion, these functions shall return the rounded 
   integer value. The result shall have the same sign as x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, +/-0 shall be returned.

   If x is +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.
*/

#include "xmath.h"

double
nearbyint (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      switch (fegetround ())
	{
	case FE_DOWNWARD:
	  return floor (x);
	case FE_TONEAREST:
	  return round (x);
	case FE_TOWARDZERO:
	default:
	  return trunc (x);
	case FE_UPWARD:
	  return ceil (x);
	}
    }
}

float
nearbyintf (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      switch (fegetround ())
	{
	case FE_DOWNWARD:
	  return floorf (x);
	case FE_TONEAREST:
	  return roundf (x);
	case FE_TOWARDZERO:
	default:
	  return truncf (x);
	case FE_UPWARD:
	  return ceilf (x);
	}
    }
}

long double
nearbyintl (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      switch (fegetround ())
	{
	case FE_DOWNWARD:
	  return floorl (x);
	case FE_TONEAREST:
	  return roundl (x);
	case FE_TOWARDZERO:
	default:
	  return truncl (x);
	case FE_UPWARD:
	  return ceill (x);
	}
    }
}

/* END OF FILE */
