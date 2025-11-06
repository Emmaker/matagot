/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* frexp, frexpf, frexpl - extract mantissa and exponent from a double 
   precision number

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall break a floating-point number num into a normalized 
   fraction and an integral power of 2. The integer exponent shall be stored 
   in the int object pointed to by exp.

   RETURN VALUE:

   For finite arguments, these functions shall return the value x, such that 
   x has a magnitude in the interval [1/2,1) or 0, and num equals x times 2 
   raised to the power *ex.

   If num is NaN, a NaN shall be returned, and the value of *ex is unspecified.

   If num is +/-0, +/-0 shall be returned, and the value of *ex shall be 0.

   If num is +/-Inf, num shall be returned, and the value of *ex is unspecified.

   ERRORS:

   No errors are defined.

   ALGORITHM:
   
   Normalize any subnormals by multiplying by a large power of 2, remembering
   how much has been offset. Pick off the exponent seminumerically and add it
   to the offset. 

*/

#include "xmath.h"

static void
_Frexp (unsigned char *x, int *ex, const _FP_METRIC_T * const m)
{
  unsigned long e, es, bias;
  int i, sign, sh;

  sign = _Getsign (x, m);
  for (e = 0UL, i = 0; i < 3; ++i)
    e = (e << CHAR_BIT) | x[_BYTE (m->_Size, i)];
  e &= ~(~0UL << (CHAR_BIT * 3 - 1));
  sh = CHAR_BIT * 3 - 1 - m->_Ebits;
  es = e >> sh;
  bias = ~(~0UL << m->_Ebits) - 1;
  *ex += es - bias;
  e &= (~0UL << sh);
  e |= (bias << sh);
  for (i = 2; i >= 0; --i)
    {
      x[_BYTE (m->_Size, i)] = (e & ~(~0UL << CHAR_BIT));
      e >>= CHAR_BIT;
    }
  _Setsign (x, m, sign);
}

double (frexp) (double num, int *ex)
{
  *ex = 0;
  switch (_Fpclassify (num))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return num;
    case FP_SUBNORMAL:
      while (_Fpclassify (num) == FP_SUBNORMAL)
	{
	  *ex -= 30;
	  num *= (1L << 30);
	}			/* FALL THROUGH */
    default:
      _Frexp ((unsigned char *) (&num), ex, _Dbl);
      return num;
    }
}

float (frexpf) (float num, int *ex)
{
  *ex = 0;
  switch (_Fpclassifyf (num))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return num;
    case FP_SUBNORMAL:
      while (_Fpclassifyf (num) == FP_SUBNORMAL)
	{
	  *ex -= 30;
	  num *= (1L << 30);
	}			/* FALL THROUGH */
    default:
      _Frexp ((unsigned char *) (&num), ex, _Flt);
      return num;
    }
}

long double (frexpl) (long double num, int *ex)
{
  *ex = 0;
  switch (_Fpclassifyl (num))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return num;
    case FP_SUBNORMAL:
      while (_Fpclassifyl (num) == FP_SUBNORMAL)
	{
	  *ex -= 30;
	  num *= (1L << 30);
	}			/* FALL THROUGH */
    default:
      _Frexp ((unsigned char *) (&num), ex, _Ldbl);
      return num;
    }
}

/* END OF FILE */
