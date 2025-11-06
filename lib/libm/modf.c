/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* modf, modff, modfl - decompose a floating-point number

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here 
   and the ISO C standard is unintentional. This volume of POSIX.1-2008 
   defers to the ISO C standard.

   These functions shall break the argument x into integral and fractional 
   parts, each of which has the same sign as the argument. It stores the 
   integral part as a double (for the modf() function), a float (for the 
   modff() function), or a long double (for the modfl() function), in the 
   object pointed to by iptr.

   RETURN VALUE:

   Upon successful completion, these functions shall return the signed 
   fractional part of x.

   If x is NaN, a NaN shall be returned, and *iptr shall be set to a NaN.

   If x is +/-Inf, +/-0 shall be returned, and *iptr shall be set to 
   +/-Inf.

   ERRORS:

   No errors are defined.

   ALGORITHM:
   
   Use trunc to do the dirty work.
*/

#include "xmath.h"

double (modf) (double x, double *iptr)
{
  int sign;

  switch (_Fpclassify (x))
    {
    case FP_INFINITE:
      sign = _Getsign ((unsigned char *) &x, _Dbl);
      *iptr = x;
      return sign ? -0.0 : +0.0;
    case FP_NAN:
    case FP_ZERO:
      *iptr = x;
      return x;
    default:
      *iptr = trunc (x);
      return x - *iptr;
    }
}

float (modff) (float x, float *iptr)
{
  int sign;

  switch (_Fpclassifyf (x))
    {
    case FP_INFINITE:
      sign = _Getsign ((unsigned char *) &x, _Flt);
      *iptr = x;
      return sign ? -0.0F : +0.0F;
    case FP_NAN:
    case FP_ZERO:
      *iptr = x;
      return x;
    default:
      *iptr = truncf (x);
      return x - *iptr;
    }
}

long double (modfl) (long double x, long double *iptr)
{
  int sign;

  switch (_Fpclassifyl (x))
    {
    case FP_INFINITE:
      sign = _Getsign ((unsigned char *) &x, _Ldbl);
      *iptr = x;
      return sign ? -0.0L : +0.0L;
    case FP_NAN:
    case FP_ZERO:
      *iptr = x;
      return x;
    default:
      *iptr = truncl (x);
      return x - *iptr;
    }
}

/* END OF FILE */
