/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cbrt, cbrtf, cbrtl - cube root functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the real cube root of their argument x.

   RETURN VALUE:

   Upon successful completion, these functions shall return the cube root of 
   x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.

   ALGORITHM:
   
   This is a Newton-Raphson-Horner iteration converging on the cube root.
*/

#include "xmath.h"

double (cbrt) (double x)
{
  double y, d;
  int e, s = _Getsign ((unsigned char *) &x, _Dbl);

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      frexp (x, &e);
      y = ldexp (x, -(e + e) / 3);
      do
	{
	  d = y;
	  y -= (y - (x / (y * y))) / 3.0;
	  d -= y;
	}
      while (_Fpclassify (d) != FP_ZERO);
      _Setsign ((unsigned char *) &y, _Dbl, s);
      return y;
    }
}

float (cbrtf) (float x)
{
  float y, d;
  int e, s = _Getsign ((unsigned char *) &x, _Flt);

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      _Setsign ((unsigned char *) &x, _Flt, 0);
      frexpf (x, &e);
      y = ldexpf (x, -(e + e) / 3);
      do
	{
	  d = y;
	  y -= (y - (x / (y * y))) / 3.0F;
	  d -= y;
	}
      while (_Fpclassifyf (d) != FP_ZERO);
      _Setsign ((unsigned char *) &y, _Flt, s);
      return y;
    }
}

long double (cbrtl) (long double x)
{
  long double y, d;
  int e, s = _Getsign ((unsigned char *) &x, _Ldbl);

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      frexp (x, &e);
      y = ldexp (x, -(e + e) / 3);
      do
	{
	  d = y;
	  y -= (y - (x / (y * y))) / 3.0L;
	  d -= y;
	}
      while (_Fpclassifyl (d) != FP_ZERO);
      _Setsign ((unsigned char *) &y, _Ldbl, s);
      return y;
    }
}

/* END OF FILE */
