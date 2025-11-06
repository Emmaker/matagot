/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* clog, clogf, clogl - complex natural logarithm functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers to 
   the ISO C standard.

   These functions shall compute the complex natural (base e) logarithm of z, 
   with a branch cut along the negative real axis.

   RETURN VALUE:

   These functions shall return the complex natural logarithm value, in the 
   range of a strip mathematically unbounded along the real axis and in the 
   interval [-(i * pi), +(i * pi)] along the imaginary axis.

   ERRORS

   No errors are defined.

   Appendix G of the C99 standard defines this behavior:
   
   clog(conj(z)) = conj(clog(z)).

   clog(−0 + i0) returns −Inf + i(pi) and raises the "divide-by-zero" 
   floating-point exception.
   
   clog(+0 + i0) returns −Inf + i0 and raises the "divide-by-zero" 
   floating-point exception.

   clog(x + i(Inf)) returns +Inf + ipi/2, for finite x.

   clog(x + iNaN) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for finite x.

   clog(−Inf + iy) returns +Inf + i(pi), for finite positive-signed y.

   clog(+Inf + iy) returns +Inf + i0, for finite positive-signed y.

   clog(−Inf + i(Inf)) returns +Inf + i3pi/4.

   clog(+Inf + i(Inf)) returns +Inf + ipi/4.

   clog(+/-Inf + iNaN) returns +Inf + iNaN.

   clog(NaN + iy) returns NaN + iNaN and optionally raises the "invalid" 
   floating-point exception, for finite y.

   clog(NaN + i(Inf)) returns +Inf + iNaN.
   
   clog(NaN + iNaN) returns NaN + iNaN.

*/

#include <complex.h>
#include "xmath.h"

double _Complex (clog) (double _Complex z)
{
  double r, f, zr, zi;
  int cr, ci, sr, si;

  zr = creal (z);
  zi = cimag (z);
  cr = _Fpclassify (zr);
  ci = _Fpclassify (zi);
  sr = _Getsign ((unsigned char *) &zr, _Dbl);
  si = _Getsign ((unsigned char *) &zi, _Dbl);
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_INFINITE:
	  return CMPLX (_Dbl->_Inf._D, _Dbl->_Nan._D);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return (zr, zr);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLX (_Dbl->_Inf._D, zi);
      else if (ci == FP_INFINITE)
	{
	  if (sr)
	    return CMPLX (_Dbl->_Inf._D, M_PI_2 + M_PI_4);
	  else
	    return CMPLX (_Dbl->_Inf._D, M_PI_4);
	}
      else if (si == 0)
	{
	  if (sr)
	    return CMPLX (_Dbl->_Inf._D, M_PI);
	  else
	    return CMPLX (_Dbl->_Inf._D, +0.0);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  if (sr)
	    return CMPLX (-_Dbl->_Inf._D, M_PI);
	  else
	    return CMPLX (-_Dbl->_Inf._D, +0.0);
	}
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLX (zi, zi);
	}
      if (ci == FP_INFINITE)
	return CMPLX (_Dbl->_Inf._D, M_PI_2);
      r = cabs (z);
      f = carg (z);
      return CMPLX (log (r), f);
    }
}

float _Complex (clogf) (float _Complex z)
{
  float r, f, zr, zi;
  int cr, ci, sr, si;

  zr = crealf (z);
  zi = cimagf (z);
  cr = _Fpclassifyf (zr);
  ci = _Fpclassifyf (zi);
  sr = _Getsign ((unsigned char *) &zr, _Flt);
  si = _Getsign ((unsigned char *) &zi, _Flt);
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_INFINITE:
	  return CMPLXF (_Flt->_Inf._F, _Flt->_Nan._F);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return (zr, zr);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLXF (_Flt->_Inf._F, ci);
      else if (ci == FP_INFINITE)
	{
	  if (sr)
	    return CMPLXF (_Flt->_Inf._F, _M_PI_2F + _M_PI_4F);
	  else
	    return CMPLXF (_Flt->_Inf._F, _M_PI_4F);
	}
      else if (si == 0)
	{
	  if (sr)
	    return CMPLXF (_Flt->_Inf._F, _M_PIF);
	  else
	    return CMPLXF (_Flt->_Inf._F, +0.0F);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  if (sr)
	    return CMPLXF (-_Flt->_Inf._F, _M_PIF);
	  else
	    return CMPLXF (-_Flt->_Inf._F, +0.0F);
	}
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXF (zi, zi);
	}
      if (ci == FP_INFINITE)
	return CMPLXF (_Flt->_Inf._F, _M_PI_2F);
      r = cabsf (z);
      f = cargf (z);
      return CMPLXF (logf (r), f);
    }
}

long double _Complex (clogl) (long double _Complex z)
{
  long double r, f, zr, zi;
  int cr, ci, sr, si;

  zr = creall (z);
  zi = cimagl (z);
  cr = _Fpclassifyl (zr);
  ci = _Fpclassifyl (zi);
  sr = _Getsign ((unsigned char *) &zr, _Ldbl);
  si = _Getsign ((unsigned char *) &zi, _Ldbl);
  switch (cr)
    {
    case FP_NAN:
      switch (ci)
	{
	case FP_INFINITE:
	  return CMPLXL (_Ldbl->_Inf._L, _Ldbl->_Nan._L);
	default:
	  _Matherr (EDOM, FE_INVALID);
	  /* FALL THROUGH */
	case FP_NAN:
	  return (zr, zr);
	}
    case FP_INFINITE:
      if (ci == FP_NAN)
	return CMPLXL (_Ldbl->_Inf._L, zi);
      else if (ci == FP_INFINITE)
	{
	  if (sr)
	    return CMPLXL (_Ldbl->_Inf._L, _M_PI_2L + _M_PI_4L);
	  else
	    return CMPLXL (_Ldbl->_Inf._L, _M_PI_4L);
	}
      else if (si == 0)
	{
	  if (sr)
	    return CMPLXL (_Ldbl->_Inf._L, _M_PIL);
	  else
	    return CMPLXL (_Ldbl->_Inf._L, +0.0L);
	}
    default:
      if (cr == FP_ZERO && ci == FP_ZERO)
	{
	  _Matherr (EDOM, FE_DIVBYZERO);
	  if (sr)
	    return CMPLXL (-_Ldbl->_Inf._L, _M_PIL);
	  else
	    return CMPLXL (-_Ldbl->_Inf._L, +0.0L);
	}
      if (ci == FP_NAN)
	{
	  _Matherr (EDOM, FE_INVALID);
	  return CMPLXL (zi, zi);
	}
      if (ci == FP_INFINITE)
	return CMPLX (_Ldbl->_Inf._L, _M_PI_2L);
      r = cabsl (z);
      f = cargl (z);
      return CMPLXL (logl (r), f);
    }
}

/* END OF FILE */
