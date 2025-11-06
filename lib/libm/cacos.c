/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cacos, cacosf, cacosl - complex arc cosine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex arc cosine of z, with branch 
   cuts outside the interval [-1, +1] along the real axis.

   RETURN VALUE:

   These functions shall return the complex arc cosine value, in the range of 
   a strip mathematically unbounded along the imaginary axis and in the 
   interval [0, pi] along the real axis.

   Appendix G of the C99 Standard lists the following special cases:

   cacos (conj (z)) = conj (cacos (z)).

   cacos(+/-0 + i0) returns pi/2 − i0.
   
   cacos(+/-0 + iNaN) returns pi/2 + iNaN.
   
   cacos(x + i(Inf)) returns pi/2 − i(Inf), for finite x.

   cacos(x + iNaN) returns NaN + iNaN and optionally raises the "invalid" 
   floating point exception, for nonzero finite x.

   cacos(−Inf + iy) returns pi − i(Inf), for positive-signed finite y.
   
   cacos(+Inf + iy) returns +0 − i(Inf), for positive-signed finite y.
   
   cacos(−Inf + i(Inf)) returns 3pi/4 − i(Inf).
   
   cacos(+Inf + i(Inf)) returns pi/4 − i(Inf).
   
   cacos(+/-Inf + iNaN) returns NaN +/- i(Inf) (where the sign of the 
   imaginary part of the result is unspecified).
   
   cacos(NaN + iy) returns NaN + iNaN and optionally raises the "invalid" 
   floating point exception, for finite y.

   cacos(NaN + i(Inf)) returns NaN − i(Inf).
   
   cacos(NaN + iNaN) returns NaN + iNaN.

   ERRORS:

   No errors are defined, except as above.
*/

#include <complex.h>
#include "xmath.h"

/* acos(z) = pi/2 - asin(z) */

double _Complex (cacos) (double _Complex z)
{
  int cr, ci, sr, si;
  double re, im;

  cr = _Fpclassify (creal (z));
  ci = _Fpclassify (cimag (z));
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  im = cimag (z);
	  si = _Getsign ((unsigned char *) &im, _Dbl);
	  return CMPLX (creal (z), si ? _Dbl->_Nan._D : -_Dbl->_Nan._D);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (creal (z), creal (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLX (cimag (z), creal (z));
	case FP_INFINITE:
	  re = creal (z);
	  sr = _Getsign ((unsigned char *) &re, _Dbl);
	  if (sr)
	    return CMPLX (M_PI_2 + M_PI_4, -_Dbl->_Inf._D);
	  else
	    return CMPLX (M_PI_4, -_Dbl->_Inf._D);
	default:
	  re = creal (z);
	  sr = _Getsign ((unsigned char *) &re, _Dbl);
	  im = cimag (z);
	  si = _Getsign ((unsigned char *) &im, _Dbl);
	  if (si == 0)
	    {
	      if (sr)
		return CMPLX (M_PI, -_Dbl->_Inf._D);
	      else
		return CMPLX (+0.0, -_Dbl->_Inf._D);
	    }
	  break;		/* what do we do about Inf - yi? */
	}
    case FP_ZERO:
      switch (ci)
	{
	case FP_NAN:
	  im = cimag (z);
	  _Setsign ((unsigned char *) &im, _Dbl, 0);
	  return CMPLX (M_PI_2, im);
	case FP_ZERO:
	  return CMPLX (M_PI_2, +0.0);
	default:
	  break;
	}
    default:
      switch (ci)
	{
	case FP_NAN:
	  im = cimag (z);
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (im, im);
	case FP_INFINITE:
	  return CMPLX (M_PI_2, -_Dbl->_Inf._D);
	case FP_ZERO:
	  re = creal (z);
	  return CMPLX (acos (re), +0.0);
	default:
	  break;
	}
    }

  z = casin (z);
  return CMPLX (M_PI_2 - creal (z), -cimag (z));
}

float _Complex (cacosf) (float _Complex z)
{
  int cr, ci, sr, si;
  float re, im;

  cr = _Fpclassifyf (crealf (z));
  ci = _Fpclassifyf (cimagf (z));
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  im = cimagf (z);
	  si = _Getsign ((unsigned char *) &im, _Flt);
	  return CMPLXF (crealf (z), si ? _Flt->_Nan._F : -_Flt->_Nan._F);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (crealf (z), crealf (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLXF (cimagf (z), crealf (z));
	case FP_INFINITE:
	  re = crealf (z);
	  sr = _Getsign ((unsigned char *) &re, _Flt);
	  if (sr)
	    return CMPLXF (_M_PI_2F + _M_PI_4F, -_Flt->_Inf._F);
	  else
	    return CMPLXF (_M_PI_4F, -_Flt->_Inf._F);
	default:
	  re = crealf (z);
	  sr = _Getsign ((unsigned char *) &re, _Flt);
	  im = cimagf (z);
	  si = _Getsign ((unsigned char *) &im, _Flt);
	  if (si == 0)
	    {
	      if (sr)
		return CMPLXF (_M_PIF, -_Flt->_Inf._F);
	      else
		return CMPLXF (+0.0, -_Flt->_Inf._F);
	    }
	  break;		/* what do we do about Inf - yi? */
	}
    case FP_ZERO:
      switch (ci)
	{
	case FP_NAN:
	  im = cimagf (z);
	  _Setsign ((unsigned char *) &im, _Flt, 0);
	  return CMPLXF (_M_PI_2F, im);
	case FP_ZERO:
	  return CMPLXF (_M_PI_2F, +0.0F);
	default:
	  break;
	}
    default:
      switch (ci)
	{
	case FP_NAN:
	  im = cimagf (z);
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (im, im);
	case FP_INFINITE:
	  return CMPLXF (_M_PI_2F, -_Flt->_Inf._F);
	case FP_ZERO:
	  re = crealf (z);
	  return CMPLXF (acosf (re), +0.0F);
	default:
	  break;
	}
    }

  z = casinf (z);
  return CMPLXF (_M_PI_2F - crealf (z), -cimagf (z));
}

long double _Complex (cacosl) (long double _Complex z)
{
  int cr, ci, sr, si;
  long double re, im;

  cr = _Fpclassifyl (creall (z));
  ci = _Fpclassifyl (cimagl (z));
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_NAN:
	  return z;
	case FP_INFINITE:
	  im = cimagl (z);
	  si = _Getsign ((unsigned char *) &im, _Ldbl);
	  return CMPLXL (creall (z), si ? _Ldbl->_Nan._L : -_Ldbl->_Nan._L);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (creall (z), creall (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLXL (cimagl (z), creall (z));
	case FP_INFINITE:
	  re = creall (z);
	  sr = _Getsign ((unsigned char *) &re, _Ldbl);
	  if (sr)
	    return CMPLXL (_M_PI_2L + _M_PI_4L, -_Ldbl->_Inf._L);
	  else
	    return CMPLXL (_M_PI_4L, -_Ldbl->_Inf._L);
	default:
	  re = creall (z);
	  sr = _Getsign ((unsigned char *) &re, _Ldbl);
	  im = cimag (z);
	  si = _Getsign ((unsigned char *) &im, _Ldbl);
	  if (si == 0)
	    {
	      if (sr)
		return CMPLXL (_M_PIL, -_Ldbl->_Inf._L);
	      else
		return CMPLXL (+0.0L, -_Ldbl->_Inf._L);
	    }
	  break;		/* what do we do about Inf - yi? */
	}
    case FP_ZERO:
      switch (ci)
	{
	case FP_NAN:
	  im = cimagl (z);
	  _Setsign ((unsigned char *) &im, _Ldbl, 0);
	  return CMPLXL (_M_PI_2L, im);
	case FP_ZERO:
	  return CMPLXL (_M_PI_2L, +0.0L);
	default:
	  break;
	}
    default:
      switch (ci)
	{
	case FP_NAN:
	  im = cimagl (z);
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (im, im);
	case FP_INFINITE:
	  return CMPLX (_M_PI_2L, -_Ldbl->_Inf._L);
	case FP_ZERO:
	  re = creall (z);
	  return CMPLXL (acosl (re), +0.0L);
	default:
	  break;
	}
    }

  z = casinl (z);
  return CMPLXL (_M_PI_2L - creall (z), -cimagl (z));
}

/* END OF FILE */
