/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* tanh, tanhf, tanhl - hyperbolic tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the hyperbolic tangent of their argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the hyperbolic 
   tangent of x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is +/-Inf, +/-1 shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, tanh(), tanhf(), and tanhl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS

   These functions may fail if:
   Range Error
   The value of x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

/* approximation for |x| < 0.625 */
static long double
_Tanh (long double x)
{
  long double p, q, s, z;

  s = x * x;
  z = x;
  _Setsign ((unsigned char *) &z, _Ldbl, 0);
  switch (_Ldbl->_Size)
    {
    case 16:
      p = ((((-6.505693197948351084912624750702492767503E-6L * s +
	      -9.804083860188429726356968570322356183383E-1L) * s +
	     -5.055287638900473250703725789725376004355E2L) * s +
	    -7.307477148073823966594990496301416814519E4L) * s +
	   -3.531606586182691280701462523692471322688E6L) * s +
	-4.551377146142783468144190926206842300707E7L;
      q = ((((s +
	      5.334865598460027935735737253027154828002E2L) * s +
	     8.058475607422391042912151298751537172870E4L) * s +
	    4.197073523796142343374222405869721575491E6L) * s +
	   6.521134551226147545983467868553677881771E7L) * s +
	1.365413143842835040443257277862054198329E8L;
      break;
    case 10:
      p =
	((-6.8473739392677100872869E-5L * s +
	  -9.5658283111794641589011E-1L) * s +
	 -8.4053568599672284488465E1L) * s + -1.3080425704712825945553E3L;
      q =
	((s + 9.6259501838840336946872E1L) * s +
	 1.8218117903645559060232E3L) * s + 3.9241277114138477845780E3L;
      break;
    case 8:
    default:
      p =
	(-9.64399179425052238628E-1L * s + -9.92877231001918586564E1L) * s +
	-1.61468768441708447952E3;
      q =
	((s + 1.12811678491632931402E2L) * s +
	 2.23548839060100448583E3L) * s + 4.84406305325125486048E3L;
      break;
    }
  z *= x * s;
  z += x;
  return z;
}

double (tanh) (double x)
{
  double z;
  int sign;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? -1.0 : +1.0;
    default:
      z = x;
      sign = _Getsign ((unsigned char *) &x, _Dbl);
      _Setsign ((unsigned char *) &z, _Dbl, 0);
      if (z >= 0.625)
	{
          /* do it the old-fashioned way */
	  z = 1.0 - 2.0 / (exp (z + z) + 1.0);
	  if (sign)
	    z = -z;
	}
      else
	z = _Tanh (x);
      return z;
    }
}

float (tanhf) (float x)
{
  float z;
  int sign;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? -1.0F : +1.0F;
    default:
      z = x;
      sign = _Getsign ((unsigned char *) &x, _Flt);
      _Setsign ((unsigned char *) &z, _Flt, 0);
      if (z >= 0.625F)
	{
          /* do it the old-fashioned way */
	  z = 1.0F - 2.0F / (expf (z + z) + 1.0F);
	  if (sign)
	    z = -z;
	}
      else
	z = _Tanh (x);
      return z;
    }
}

long double (tanhl) (long double x)
{
  long double z;
  int sign;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -1.0L : +1.0L;
    default:
      z = x;
      sign = _Getsign ((unsigned char *) &x, _Ldbl);
      _Setsign ((unsigned char *) &z, _Ldbl, 0);
      if (z >= 0.625L)
	{
          /* do it the old-fashioned way */
	  z = 1.0L - 2.0L / (expl (z + z) + 1.0L);
	  if (sign)
	    z = -z;
	}
      else
	z = _Tanh (x);
      return z;
    }
}

/* END OF FILE */
