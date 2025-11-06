/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cexp, cexpf, cexpl - complex exponential functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex exponent of z, defined as e^z.

   RETURN VALUE:

   These functions shall return the complex exponential value of z.

   ERRORS

   No errors are defined.

   Appendix G of the 1999 ANSI/ISO C standard lists this behavior:

   cexp(conj(z)) = conj(cexp(z)).

   cexp(+/-0 + i0) returns 1 + i0.
   
   cexp(x + i(Inf)) returns NaN + iNaN and raises the "invalid" floating-point
   exception, for finite x.
   
   cexp(x + iNaN) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for finite x.

   cexp(+Inf + i0) returns +Inf + i0.
   
   cexp(−Inf + iy) returns +0 cis(y), for finite y.

   cexp(+Inf + iy) returns +Inf cis(y), for finite nonzero y.

   cexp(−Inf + i(Inf)) returns +/-0 +/-i0 (where the signs of the real and 
   imaginary parts of the result are unspecified).
   
   cexp(+Inf + i(Inf)) returns +/-Inf + iNaN and raises the "invalid" 
   floating-point exception (where the sign of the real part of the result 
   is unspecified).

   cexp(−Inf + iNaN) returns +/-0 +/-i0 (where the signs of the real and 
   imaginary parts of the result are unspecified).

   cexp(+Inf + iNaN) returns +/-∞ + iNaN (where the sign of the real part of 
   the result is unspecified).

   cexp(NaN + i0) returns NaN + i0.

   cexp(NaN + iy) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for all nonzero numbers y.

   cexp(NaN + iNaN) returns NaN + iNaN.

*/

#include <complex.h>
#include "xmath.h"

double _Complex 
(cexp) (double _Complex z)
{
  double x, zr, zi;
  int cr, ci, sr, si;

  zr = creal (z);
  zi = cimag (z);
  cr = _Fpclassify (zr);
  ci = _Fpclassify (zi);

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (zr, zr);
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) (&zr), _Dbl);
      si = _Getsign ((unsigned char *) (&zi), _Dbl);
      if (sr)
	{
	  /* negative */
	  return CMPLX (+0.0, +0.0);
	}
      else
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	  if (ci == FP_INFINITE)
	    {
	      _Matherr (EDOM, FE_INVALID);
	      return CMPLX (zr, _Dbl->_Nan._D);
	    }
	  if (si)
	    return CMPLX (zr, -zr);
	  else
	    return CMPLX (zr, zr);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLX (+1.0, +0.0);
      if (ci == FP_INFINITE && ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (_Dbl->_Nan._D, _Dbl->_Nan._D);
	}
      x = exp (zr);
      return CMPLX (x * cos (zi), x * sin (zi));
    }
}

float _Complex (cexpf) (float _Complex z)
{
  float x, zr, zi;
  int cr, ci, sr, si;

  zr = crealf (z);
  zi = cimagf (z);
  cr = _Fpclassifyf (zr);
  ci = _Fpclassifyf (zi);

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (zr, zr);
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) (&zr), _Flt);
      si = _Getsign ((unsigned char *) (&zi), _Flt);
      if (sr)
	{
	  /* negative */
	  return CMPLXF (+0.0F, +0.0F);
	}
      else
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	  if (ci == FP_INFINITE)
	    {
	      _Matherr (EDOM, FE_INVALID);
	      return CMPLXF (zr, _Flt->_Nan._F);
	    }
	  if (si)
	    return CMPLXF (zr, -zr);
	  else
	    return CMPLXF (zr, zr);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLXF (+1.0F, +0.0F);
      if (ci == FP_INFINITE && ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (_Flt->_Nan._F, _Flt->_Nan._F);
	}
      x = expf (zr);
      return CMPLXF (x * cosf (zi), x * sinf (zi));
    }
}

long double _Complex (cexpl) (long double _Complex z)
{
  long double x, zr, zi;
  int cr, ci, sr, si;

  zr = creall (z);
  zi = cimagl (z);
  cr = _Fpclassifyl (zr);
  ci = _Fpclassifyl (zi);

  switch (cr)
    {
    case FP_NAN:
      if (ci == FP_ZERO || ci == FP_NAN)
	return z;
      else
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (zr, zr);
	}
    case FP_INFINITE:
      sr = _Getsign ((unsigned char *) (&zr), _Ldbl);
      si = _Getsign ((unsigned char *) (&zi), _Ldbl);
      if (sr)
	{
	  /* negative */
	  return CMPLXL (+0.0L, +0.0L);
	}
      else
	{
	  if (ci == FP_ZERO || ci == FP_NAN)
	    return z;
	  if (ci == FP_INFINITE)
	    {
	      _Matherr (EDOM, FE_INVALID);
	      return CMPLXL (zr, _Ldbl->_Nan._L);
	    }
	  if (si)
	    return CMPLX (zr, -zr);
	  else
	    return CMPLX (zr, zr);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	return CMPLXL (+1.0L, +0.0L);
      if (ci == FP_INFINITE && ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (_Ldbl->_Nan._L, _Ldbl->_Nan._L);
	}
      x = expl (zr);
      return CMPLX (x * cosl (zi), x * sinl (zi));
    }
}

/* END OF FILE */
