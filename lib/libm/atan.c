/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* atan, atanf, atanl - arc tangent function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the principal value of the arc tangent of 
   their argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the arc tangent 
   of x in the range [-pi/2,pi/2] radians.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is +/-Inf, +/-pi/2 shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, atan(), atanf(), and atanl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS:

   These functions may fail if:
   
   Range Error
   
   The value of x is subnormal. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   ALGORITHM:
   
   1. Handle special cases.
   2. Pick off sign since atan(-x) == -atan(x).
   3. Reduce x to (0,1] since atan(1/x) == pi/2 - atan(x).
   4. Handle the rest with a series:
      atan(z) = z - z^3/3 + z^5/5 - z^7/7 ... if |z|<=1.0
*/

#include "xmath.h"

double (atan) (double x)
{
  double d, r, t, w;
  unsigned long i;
  unsigned int f = 0, s = 0;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? -M_PI_2 : M_PI_2;
    default:
      s = _Getsign ((unsigned char *) &x, _Dbl);
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      if (x == 1.0)
	r = M_PI_4;
      else
	{
	  if (x > 1.0)
	    {
	      x = 1.0 / x;
	      f = 1;
	    }
	  w = x * x;
	  r = t = x;
	  i = 3UL;
	  do
	    {
	      d = r;
	      t *= w;
	      r += (i & 2UL) ? t / i : -t / i;
	      i += 2UL;
	      d -= r;
	    }
	  while (d != 0.0);
	  if (f)
	    r = M_PI_2 - r;
	}
      _Setsign ((unsigned char *) &r, _Dbl, s);
      return r;
    }
}

float (atanf) (float x)
{
  float d, r, t, w;
  unsigned long i;
  unsigned int f = 0, s = 0;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? -_M_PI_2F : _M_PI_2F;
    default:
      s = _Getsign ((unsigned char *) &x, _Flt);
      _Setsign ((unsigned char *) &x, _Flt, 0);
      if (x == 1.0F)
	r = _M_PI_4F;
      else
	{
	  if (x > 1.0F)
	    {
	      x = 1.0F / x;
	      f = 1;
	    }
	  w = x * x;
	  r = t = x;
	  i = 3UL;
	  do
	    {
	      d = r;
	      t *= w;
	      r += (i & 2UL) ? t / i : -t / i;
	      i += 2UL;
	      d -= r;
	    }
	  while (d != 0.0F);
	  if (f)
	    r = _M_PI_2F - r;
	}
      _Setsign ((unsigned char *) &r, _Flt, s);
      return r;
    }
}

long double (atanl) (long double x)
{
  long double d, r, t, w;
  unsigned long i;
  unsigned int f = 0, s = 0;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_ZERO:
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -_M_PI_2L : _M_PI_2L;
    default:
      s = _Getsign ((unsigned char *) &x, _Ldbl);
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      if (x == 1.0L)
	r = _M_PI_4L;
      else
	{
	  if (x > 1.0L)
	    {
	      x = 1.0L / x;
	      f = 1;
	    }
	  w = x * x;
	  r = t = x;
	  i = 3UL;
	  do
	    {
	      d = r;
	      t *= w;
	      r += (i & 2UL) ? t / i : -t / i;
	      i += 2UL;
	      d -= r;
	    }
	  while (d != 0.0L);
	  if (f)
	    r = _M_PI_2L - r;
	}
      _Setsign ((unsigned char *) &r, _Ldbl, s);
      return r;
    }
}

/* END OF FILE */
