/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* csqrt, csqrtf, csqrtl - complex square root functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex square root of z, with a branch 
   cut along the negative real axis.

   RETURN VALUE:

   These functions shall return the complex square root value, in the range 
   of the right half-plane (including the imaginary axis).

   ERRORS:

   No errors are defined.

   Appendix G of the C99 Standard mandates this behavior:
   
   csqrt(conj(z)) = conj(csqrt(z)).

   csqrt(+/-0 + i0) returns +0 + i0.
   
   csqrt(x + i(Inf)) returns +Inf + i(Inf), for all x (including NaN).

   csqrt(x + iNaN) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for finite x.

   csqrt(−Inf + iy) returns +0 + i(Inf), for finite positive-signed y.

   csqrt(+Inf + iy) returns +Inf + i0, for finite positive-signed y.
   
   csqrt(−Inf + iNaN) returns NaN +/- i(Inf) (where the sign of the imaginary 
   part of the result is unspecified).

   csqrt(+Inf + iNaN) returns +Inf + iNaN.

   csqrt(NaN + iy) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for finite y.

   csqrt(NaN + iNaN) returns NaN + iNaN.

*/

#include <complex.h>
#include "xmath.h"

double _Complex (csqrt) (double _Complex z)
{
  double mag, x, y, q;
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
	case FP_INFINITE:
	  return CMPLX (_Dbl->_Inf._D, _Dbl->_Inf._D);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return z;
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) &x, _Dbl);
      if (sr)
	{
	  /* -Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return CMPLX (y, _Dbl->_Inf._D);
	    case FP_INFINITE:
	      return CMPLX (_Dbl->_Inf._D, _Dbl->_Inf._D);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Dbl);
	      if (si == 0)
		return CMPLX (+0.0, _Dbl->_Inf._D);
	    }
	}
      else
	{
	  /* +Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return z;
	    case FP_INFINITE:
	      return CMPLX (_Dbl->_Inf._D, _Dbl->_Inf._D);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Dbl);
	      if (si == 0)
		return CMPLX (_Dbl->_Inf._D, +0.0);
	    }
	}
    default:
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (y, y);
	}
      else if (ci == FP_INFINITE)
	return CMPLX (_Dbl->_Inf._D, _Dbl->_Inf._D);
      else
	{
	  mag = cabs (z);
	  if (mag == 0.0)
	    return CMPLX (0.0, 0.0);
	  else if (x > 0.0)
	    {
	      q = sqrt (0.5 * (mag + x));
	      return CMPLX (q, y / q / 2.0);
	    }
	  else
	    {
	      q = sqrt (0.5 * (mag - x));
	      if (y < 0.0)
		q = -q;
	      return CMPLX (y / q / 2.0, q);
	    }
	}
    }
}

float _Complex (csqrtf) (float _Complex z)
{
  float mag, x, y, q;
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
	case FP_INFINITE:
	  return CMPLXF (_Flt->_Inf._F, _Flt->_Inf._F);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return z;
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) &x, _Flt);
      if (sr)
	{
	  /* -Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return CMPLX (y, _Flt->_Inf._F);
	    case FP_INFINITE:
	      return CMPLXF (_Flt->_Inf._F, _Flt->_Inf._F);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Flt);
	      if (si == 0)
		return CMPLXF (+0.0F, _Flt->_Inf._F);
	    }
	}
      else
	{
	  /* +Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return z;
	    case FP_INFINITE:
	      return CMPLXF (_Flt->_Inf._F, _Flt->_Inf._F);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Flt);
	      if (si == 0)
		return CMPLXF (_Flt->_Inf._F, +0.0F);
	    }
	}
    default:
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (y, y);
	}
      else if (ci == FP_INFINITE)
	return CMPLXF (_Flt->_Inf._F, _Flt->_Inf._F);
      else
	{
	  mag = cabsf (z);
	  if (mag == 0.0F)
	    return CMPLXF (0.0F, 0.0F);
	  else if (x > 0.0F)
	    {
	      q = sqrtf (0.5F * (mag + x));
	      return CMPLXF (q, y / q / 2.0F);
	    }
	  else
	    {
	      q = sqrt (0.5F * (mag - x));
	      if (y < 0.0F)
		q = -q;
	      return CMPLXF (y / q / 2.0F, q);
	    }
	}
    }
}

long double _Complex (csqrtl) (long double _Complex z)
{
  long double mag, x, y, q;
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
	case FP_INFINITE:
	  return CMPLXL (_Ldbl->_Inf._L, _Ldbl->_Inf._L);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return z;
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) &x, _Ldbl);
      if (sr)
	{
	  /* -Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return CMPLXL (y, _Ldbl->_Inf._L);
	    case FP_INFINITE:
	      return CMPLXL (_Ldbl->_Inf._L, _Ldbl->_Inf._L);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Ldbl);
	      if (si == 0)
		return CMPLXL (+0.0, _Ldbl->_Inf._L);
	    }
	}
      else
	{
	  /* +Inf */
	  switch (ci)
	    {
	    case FP_NAN:
	      return z;
	    case FP_INFINITE:
	      return CMPLXL (_Ldbl->_Inf._L, _Ldbl->_Inf._L);
	    default:
	      si = _Getsign ((unsigned char *) &y, _Ldbl);
	      if (si == 0)
		return CMPLXL (_Ldbl->_Inf._L, +0.0);
	    }
	}
    default:
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (y, y);
	}
      else if (ci == FP_INFINITE)
	return CMPLXL (_Ldbl->_Inf._L, _Ldbl->_Inf._L);
      else
	{
	  mag = cabsl (z);
	  if (mag == 0.0L)
	    return CMPLXL (0.0L, 0.0L);
	  else if (x > 0.0L)
	    {
	      q = sqrtl (0.5L * (mag + x));
	      return CMPLXL (q, y / q / 2.0);
	    }
	  else
	    {
	      q = sqrtl (0.5L * (mag - x));
	      if (y < 0.0L)
		q = -q;
	      return CMPLXL (y / q / 2.0L, q);
	    }
	}
    }
}

/* END OF FILE */
