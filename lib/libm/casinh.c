/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* casinh, casinhf, casinhl - complex arc hyperbolic sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex arc hyperbolic sine of z, with 
   branch cuts outside the interval [-i, +i] along the imaginary axis.

   RETURN VALUE

   These functions shall return the complex arc hyperbolic sine value, in the 
   range of a strip mathematically unbounded along the real axis and in the 
   interval [-(i * pi/2), +(i * pi/2)] along the imaginary axis.

   Appendix G of the C99 standard gives the following:
   
   casinh(conj(z)) = conj(casinh(z)) and casinh is odd.
 
   casinh(+0 + i0) returns 0 + i0.

   casinh(x + i(Inf)) returns +Inf + i(pi/2) for positive-signed finite x.

   casinh(x + iNaN) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for finite x.

   casinh(+Inf + iy) returns +Inf + i0 for positive-signed finite y.

   casinh(+Inf + i(Inf)) returns +Inf + i(pi/4).

   casinh(+Inf + iNaN) returns +Inf + iNaN.

   casinh(NaN + i0) returns NaN + i0.

   casinh(NaN + iy) returns NaN + iNaN and optionally raises the "invalid"
   floating-point exception, for finite nonzero y.

   casinh(NaN + i(Inf)) returns +/-Inf + iNaN (where the sign of the real 
   part of the result is unspecified).

   casinh(NaN + iNaN) returns NaN + iNaN.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

/* asinh(z) = -i asin(i z) */

double _Complex (casinh) (double _Complex z)
{
  int cr, ci, sr, si;
  double re, im;

  cr = _Fpclassify (creal (z));
  ci = _Fpclassify (cimag (z));

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else if (ci == FP_INFINITE)
	return CMPLX (cimag (z), creal (z));
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (creal (z), creal (z));
	}
    case FP_INFINITE:
      re = creal (z);
      sr = _Getsign ((unsigned char *) &re, _Dbl);
      im = cimag (z);
      si = _Getsign ((unsigned char *) &im, _Dbl);
      if (sr == 0)
	{
	  if (ci == FP_NAN)
	    return z;
	  else if (ci == FP_INFINITE && si == 0)
	    return CMPLX (re, M_PI_4);
	  else if (ci != FP_ZERO)
	    return CMPLX (re, +0.0);
	}
      break;
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return z;
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (cimag (z), cimag (z));
	}
      im = cimag (z);
      si = _Getsign ((unsigned char *) &im, _Dbl);
      if (ci == FP_INFINITE && si == 0)
	return CMPLX (_Dbl->_Inf._D, M_PI_2);
      if (ci == FP_ZERO)
	return CMPLX (asinh (creal (z)), +0.0);
    }
  z = casin (CMPLX (-cimag (z), creal (z)));
  return CMPLX (cimag (z), -creal (z));
}

float _Complex (casinhf) (float _Complex z)
{
  int cr, ci, sr, si;
  float re, im;

  cr = _Fpclassifyf (crealf (z));
  ci = _Fpclassifyf (cimagf (z));

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else if (ci == FP_INFINITE)
	return CMPLXF (cimagf (z), crealf (z));
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (crealf (z), crealf (z));
	}
    case FP_INFINITE:
      re = crealf (z);
      sr = _Getsign ((unsigned char *) &re, _Flt);
      im = cimagf (z);
      si = _Getsign ((unsigned char *) &im, _Flt);
      if (sr == 0)
	{
	  if (ci == FP_NAN)
	    return z;
	  else if (ci == FP_INFINITE && si == 0)
	    return CMPLXF (re, _M_PI_4F);
	  else if (ci != FP_ZERO)
	    return CMPLXF (re, +0.0F);
	}
      break;
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return z;
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (cimagf (z), cimagf (z));
	}
      im = cimagf (z);
      si = _Getsign ((unsigned char *) &im, _Flt);
      if (ci == FP_INFINITE && si == 0)
	return CMPLXF (_Flt->_Inf._F, _M_PI_2F);
      if (ci == FP_ZERO)
	return CMPLXF (asinhf (crealf (z)), +0.0F);
    }
  z = casinf (CMPLXF (-cimagf (z), crealf (z)));
  return CMPLXF (cimagf (z), -crealf (z));
}

long double _Complex (casinhl) (long double _Complex z)
{
  int cr, ci, sr, si;
  long double re, im;

  cr = _Fpclassifyl (creall (z));
  ci = _Fpclassifyl (cimagl (z));

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else if (ci == FP_INFINITE)
	return CMPLXL (cimagl (z), creall (z));
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (creall (z), creall (z));
	}
    case FP_INFINITE:
      re = creall (z);
      sr = _Getsign ((unsigned char *) &re, _Ldbl);
      im = cimagl (z);
      si = _Getsign ((unsigned char *) &im, _Ldbl);
      if (sr == 0)
	{
	  if (ci == FP_NAN)
	    return z;
	  else if (ci == FP_INFINITE && si == 0)
	    return CMPLXL (re, _M_PI_4L);
	  else if (ci != FP_ZERO)
	    return CMPLXL (re, +0.0L);
	}
      break;
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return z;
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (cimagl (z), cimagl (z));
	}
      im = cimag (z);
      si = _Getsign ((unsigned char *) &im, _Ldbl);
      if (ci == FP_INFINITE && si == 0)
	return CMPLXL (_Ldbl->_Inf._L, _M_PI_2L);
      if (ci == FP_ZERO)
	return CMPLXL (asinhl (creall (z)), +0.0);
    }
  z = casinl (CMPLXL (-cimagl (z), creall (z)));
  return CMPLXL (cimagl (z), -creall (z));
}

/* END OF FILE */
