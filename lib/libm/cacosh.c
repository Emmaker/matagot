/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cacosh, cacoshf, cacoshl - complex arc hyperbolic cosine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex arc hyperbolic cosine of z, with 
   a branch cut at values less than 1 along the real axis.

   RETURN VALUE:

   These functions shall return the complex arc hyperbolic cosine value, in 
   the range of a half-strip of non-negative values along the real axis and 
   in the interval [-(i*pi), +(i*pi)] along the imaginary axis.

   Appendix G of the C99 standard states this:
   
   cacosh(conj(z)) = conj(cacosh(z)).

   cacosh(+/-0 + i0) returns +0 + i(pi/2).

   cacosh(x + i(Inf)) returns +(Inf) + i(pi/2), for finite x.

   cacosh(x + iNaN) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for finite x.

   cacosh(−Inf + iy) returns +Inf + i(pi), for positive-signed finite y.

   cacosh(+Inf + iy) returns +Inf + i0, for positive-signed finite y.

   cacosh(−Inf + i(Inf)) returns +Inf + i(3pi/4).
   
   cacosh(+Inf + i(Inf)) returns +Inf + i(pi/4).

   cacosh(+/-Inf + iNaN) returns +Inf + iNaN.
   
   cacosh(NaN + iy) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for finite y.
   
   cacosh(NaN + i(Inf)) returns +Inf + iNaN.

   cacosh(NaN + iNaN) returns NaN + iNaN.

   ERRORS:

   No errors are defined, except as above.
*/

#include <complex.h>
#include "xmath.h"

/* cacosh(z) = i * cacos(z) */

double _Complex (cacosh) (double _Complex z)
{
  double re, im;
  int cr, ci, sr, si;

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
	  return CMPLX (cimag (z), creal (z));
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (creal (z), creal (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLX (_Dbl->_Inf._D, cimag (z));
	case FP_INFINITE:
	  re = creal (z);
	  sr = _Getsign ((unsigned char *) &re, _Dbl);
	  if (sr)
	    return CMPLX (_Dbl->_Inf._D, M_PI_2 + M_PI_4);
	  else
	    return CMPLX (_Dbl->_Inf._D, M_PI_4);
	default:
	  if (cimag (z) > 0.0)
	    {
	      re = creal (z);
	      if (_Getsign ((unsigned char *) &re, _Dbl))
		return CMPLX (_Dbl->_Inf._D, M_PI);
	      else
		return CMPLX (_Dbl->_Inf._D, +0.0);
	    }
	  else
	    break;		/* don't know what to do here... */
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLX (+0.0, M_PI_2);
      if (ci == FP_ZERO)
	return CMPLX (acosh (creal (z)), +0.0);
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (cimag (z), cimag (z));
	}
      if (ci == FP_INFINITE)
	return CMPLX (_Dbl->_Inf._D, M_PI_2);
      break;
    }

  z = cacos (z);
  return CMPLX (-cimag (z), creal (z));
}

float _Complex (cacoshf) (float _Complex z)
{
  float re, im;
  int cr, ci, sr, si;

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
	  return CMPLX (cimagf (z), crealf (z));
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (crealf (z), crealf (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLXF (_Flt->_Inf._F, cimagf (z));
	case FP_INFINITE:
	  re = crealf (z);
	  sr = _Getsign ((unsigned char *) &re, _Flt);
	  if (sr)
	    return CMPLXF (_Flt->_Inf._F, _M_PI_2F + _M_PI_4F);
	  else
	    return CMPLXF (_Flt->_Inf._F, _M_PI_4F);
	default:
	  if (cimagf (z) > 0.0F)
	    {
	      re = crealf (z);
	      if (_Getsign ((unsigned char *) &re, _Flt))
		return CMPLXF (_Flt->_Inf._F, _M_PIF);
	      else
		return CMPLXF (_Flt->_Inf._F, +0.0F);
	    }
	  else
	    break;		/* don't know what to do here... */
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLXF (+0.0F, _M_PI_2F);
      if (ci == FP_ZERO)
	return CMPLXF (acoshf (crealf (z)), +0.0F);
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (cimagf (z), cimagf (z));
	}
      if (ci == FP_INFINITE)
	return CMPLXF (_Flt->_Inf._F, _M_PI_2F);
      break;
    }

  z = cacosf (z);
  return CMPLXF (-cimagf (z), crealf (z));
}

long double _Complex (cacoshl) (long double _Complex z)
{
  long double re, im;
  int cr, ci, sr, si;

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
	  return CMPLXL (cimagl (z), creall (z));
	default:
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (creall (z), creall (z));
	}
    case FP_INFINITE:
      switch (ci)
	{
	case FP_NAN:
	  return CMPLXL (_Ldbl->_Inf._L, cimagl (z));
	case FP_INFINITE:
	  re = creall (z);
	  sr = _Getsign ((unsigned char *) &re, _Ldbl);
	  if (sr)
	    return CMPLXL (_Ldbl->_Inf._L, _M_PI_2L + _M_PI_4L);
	  else
	    return CMPLXL (_Ldbl->_Inf._L, _M_PI_4L);
	default:
	  if (cimagl (z) > 0.0L)
	    {
	      re = creall (z);
	      if (_Getsign ((unsigned char *) &re, _Ldbl))
		return CMPLXL (_Ldbl->_Inf._L, _M_PIL);
	      else
		return CMPLXL (_Ldbl->_Inf._L, +0.0L);
	    }
	  else
	    break;		/* don't know what to do here... */
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLXL (+0.0L, _M_PI_2L);
      if (ci == FP_ZERO)
	return CMPLXL (acoshl (creall (z)), +0.0L);
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (cimagl (z), cimagl (z));
	}
      if (ci == FP_INFINITE)
	return CMPLXL (_Ldbl->_Inf._L, _M_PI_2L);
      break;
    }

  z = cacosl (z);
  return CMPLXL (-cimagl (z), creall (z));
}

/* END OF FILE */
