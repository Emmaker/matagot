/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* rint, rintf, rintl - round-to-nearest integral value

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall return the integral value (represented as a double) 
   nearest x in the direction of the current rounding mode. The current 
   rounding mode is implementation-defined.

   If the current rounding mode rounds toward negative infinity, then rint() 
   shall be equivalent to floor. If the current rounding mode rounds toward 
   positive infinity, then rint() shall be equivalent to ceil. If the current 
   rounding mode rounds towards zero, then rint() shall be equivalent to trunc.
   If the current rounding mode rounds towards nearest, then rint() differs 
   from round in that halfway cases are rounded to even rather than away from 
   zero.

   These functions differ from the nearbyint(), nearbyintf(), and nearbyintl() 
   functions only in that they may raise the inexact floating-point exception 
   if the result differs in value from the argument.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the integer 
   (represented as a double precision number) nearest x in the direction of 
   the current rounding mode.  The result shall have the same sign as x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.
*/

#include "xmath.h"

double (rint) (double x)
{
  double y = 0.0, z = 0.0;
  int s, odd;

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
	case FE_UPWARD:
	  return ceil (x);
	case FE_TOWARDZERO:
	  return trunc (x);
	case FE_TONEAREST:
	default:
	  z = modf (x, &y);
	  if (z == 0.5 || z == -0.5)
	    {
	      /* round towards even */
	      s = _Getsign ((unsigned char *) &x, _Dbl);
	      odd = ldexp (trunc (ldexp (y, -1)), 1) != y;
	      if (odd)
		y += (s ? -1.0 : 1.0);
	    }
          else if (z > 0.5)
            y += 1.0;
          else if (z < -0.5)
            y -= 1.0;
	  return y;
	}
    }
}

float (rintf) (float x)
{
  float y = 0.0F, z = 0.0F;
  int s, odd;

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
	case FE_UPWARD:
	  return ceilf (x);
	case FE_TOWARDZERO:
	  return truncf (x);
	case FE_TONEAREST:
	default:
	  z = modff (x, &y);
	  if (z == 0.5F || z == -0.5F)
	    {
	      /* round towards even */
	      s = _Getsign ((unsigned char *) &x, _Flt);
	      odd = ldexpf (truncf (ldexpf (y, -1)), 1) != y;
	      if (odd)
		y += (s ? -1.0F : 1.0F);
	    }
          else if (z > 0.5F)
            y += 1.0F;
          else if (z < -0.5F)
            y -= 1.0F;
	  return y;
	}
    }
}

long double (rintl) (long double x)
{
  long double y = 0.0L, z = 0.0L;
  int s, odd;

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
	case FE_UPWARD:
	  return ceill (x);
	case FE_TOWARDZERO:
	  return truncl (x);
	case FE_TONEAREST:
	default:
	  z = modfl (x, &y);
	  if (z == 0.5L || z == -0.5L)
	    {
	      /* round towards even */
	      s = _Getsign ((unsigned char *) &x, _Ldbl);
	      odd = ldexpl (truncl (ldexpl (y, -1)), 1) != y;
	      if (odd)
		y += (s ? -1.0L : 1.0L);
	    }
          else if (z > 0.5L)
            y += 1.0L;
          else if (z < -0.5L)
            y -= 1.0L;
	  return y;
	}
    }
}

/* END OF FILE */
