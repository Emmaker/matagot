/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* catanh, catanhf, catanhl - complex hyperbolic arc tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers 
   to the ISO C standard.

   These functions shall compute the complex hyperbolic arc tangent of z, 
   with branch cuts outside the interval [-1, +1] along the real axis.

   RETURN VALUE

   These functions shall return the complex arc tangent value, in the range 
   of a strip mathematically unbounded along the real axis and in the 
   interval [-i(pi/2), +i(pi/2)] along the imaginary axis.

   Appendix G of the C99 standard gives this:
   
   catanh(conj(z)) = conj(catanh(z)) and catanh is odd.

   catanh(+0 + i0) returns +0 + i0.

   catanh(+0 + iNaN) returns +0 + iNaN.

   catanh(+1 + i0) returns +Inf + i0 and raises the "divide-by-zero" 
   floating-point exception.

   catanh(x + i(Inf)) returns +0 + i(pi/2), for finite positive-signed x.

   catanh(x + iNaN) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for nonzero finite x.

   catanh(+Inf + iy) returns +0 + i(pi/2), for finite positive-signed y.
   
   catanh(+Inf + i(Inf)) returns +0 + i(pi/2).
 
   catanh(+Inf + iNaN) returns +0 + iNaN.

   catanh(NaN + iy) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for finite y.

   catanh(NaN + i(Inf)) returns +/-0 + i(pi/2) (where the sign of the real 
   part of the result is unspecified).

   catanh(NaN + iNaN) returns NaN + iNaN. 

   ERRORS

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (catanh) (double _Complex z)
{
  double x, y, x2, y2, denom, real, imag;
  int cr, ci, sr, si;

  x = creal (z);
  y = cimag (z);
  cr = _Fpclassify (x);
  ci = _Fpclassify (y);

  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  return CMPLX (+0.0, M_PI_2);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (x, x);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLX (+0.0, y);
      else
	{
	  si = _Getsign ((unsigned char *) &y, _Dbl);
	  if (si == 0)
	    return CMPLX (+0.0, M_PI_2);
	}
    default:
      if (cr == FP_ZERO)
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	}
      else if (cr == FP_NORMAL && x == 1.0 && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  return CMPLX (_Dbl->_Inf._D, +0.0);
	}
      else if (ci == FP_INFINITE
	       && _Getsign ((unsigned char *) &x, _Dbl) == 0)
	return CMPLX (+0.0, M_PI_2);
      else if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (y, y);
	}
    }

  x2 = x * x;
  y2 = y * y;
  denom = (1.0 - x) * (1.0 - x) + y2;
  real = 0.5 * log ((1.0 + x) * (1.0 - x) + y2) - 0.5 * log (denom);
  imag = 0.5 * atan2 (2.0 * y, (1.0 - x) * (1.0 - x) - y2);
  return CMPLX (real, imag);
}

float _Complex (catanhf) (float _Complex z)
{
  float x, y, x2, y2, denom, real, imag;
  int cr, ci, sr, si;

  x = crealf (z);
  y = cimagf (z);
  cr = _Fpclassifyf (x);
  ci = _Fpclassifyf (y);

  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  return CMPLXF (+0.0F, _M_PI_2F);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (x, x);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLXF (+0.0F, y);
      else
	{
	  si = _Getsign ((unsigned char *) &y, _Flt);
	  if (si == 0)
	    return CMPLXF (+0.0F, _M_PI_2F);
	}
    default:
      if (cr == FP_ZERO)
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	}
      else if (cr == FP_NORMAL && x == 1.0F && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  return CMPLXF (_Flt->_Inf._F, +0.0F);
	}
      else if (ci == FP_INFINITE
	       && _Getsign ((unsigned char *) &x, _Flt) == 0)
	return CMPLXF (+0.0F, _M_PI_2F);
      else if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (y, y);
	}
    }

  x2 = x * x;
  y2 = y * y;
  denom = (1.0F - x) * (1.0F - x) + y2;
  real = 0.5F * logf ((1.0F + x) * (1.0F - x) + y2) - 0.5F * logf (denom);
  imag = 0.5F * atan2f (2.0F * y, (1.0F - x) * (1.0F - x) - y2);
  return CMPLXF (real, imag);
}

long double _Complex (catanhl) (long double _Complex z)
{
  long double x, y, x2, y2, denom, real, imag;
  int cr, ci, sr, si;

  x = creall (z);
  y = cimagl (z);
  cr = _Fpclassifyl (x);
  ci = _Fpclassifyl (y);

  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  return CMPLXL (+0.0L, _M_PI_2L);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (x, x);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLXL (+0.0L, y);
      else
	{
	  si = _Getsign ((unsigned char *) &y, _Ldbl);
	  if (si == 0)
	    return CMPLXL (+0.0L, _M_PI_2L);
	}
    default:
      if (cr == FP_ZERO)
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	}
      else if (cr == FP_NORMAL && x == 1.0L && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  return CMPLXL (_Ldbl->_Inf._L, +0.0L);
	}
      else if (ci == FP_INFINITE
	       && _Getsign ((unsigned char *) &x, _Ldbl) == 0)
	return CMPLXL (+0.0L, _M_PI_2L);
      else if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (y, y);
	}
    }

  x2 = x * x;
  y2 = y * y;
  denom = (1.0L - x) * (1.0L - x) + y2;
  real = 0.5L * log ((1.0L + x) * (1.0L - x) + y2) - 0.5L * logl (denom);
  imag = 0.5L * atan2l (2.0L * y, (1.0L - x) * (1.0L - x) - y2);
  return CMPLXL (real, imag);
}

/* END OF FILE */
