/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* trunc, truncf, truncl - round to truncated integer value

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here 
   and the ISO C standard is unintentional. This volume of POSIX.1-2008 
   defers to the ISO C standard.

   These functions shall round their argument to the integer value, in 
   floating format, nearest to but no larger in magnitude than the argument.

   RETURN VALUE:

   Upon successful completion, these functions shall return the truncated 
   integer value.
   
   The result shall have the same sign as x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.
   
   ALGORITHM:
   
   Internally, the numbers are represented as a sign bit, biased exponent,
   and mantissa. Use the exponent to figure out how much of the mantissa to
   zero out.
*/

#include "xmath.h"

static void
_Trunc (unsigned char *x, const _FP_METRIC_T * const m)
{
  unsigned long bias, e, f;
  int sign, i;

  sign = _Getsign (x, m);
  bias = ~(~0UL << (m->_Ebits - 1));
  for (i = 0, e = 0UL; i < 3; ++i)
    e = (e << CHAR_BIT) | x[_BYTE (m->_Size, i)];
  e &= ~(~0UL << (CHAR_BIT * 3 - 1));
  e >>= (CHAR_BIT * 3 - 1 - m->_Ebits);
  if (e < bias)
    {
      /* all bits zero */
      for (i = 0; i < m->_Size; ++i)
	x[i] = 0;
      if (sign)
	_Setsign (x, m, 1);
    }
  else if (e < m->_Mant_dig - 1 - m->_Explicit1bit + bias)
    {
      /* some int, some frac */
      f = m->_Mant_dig + bias - e - m->_Explicit1bit;
      for (i = m->_Size - 1; f >= CHAR_BIT; --i, f -= CHAR_BIT)
	x[_BYTE (m->_Size, i)] = 0;
      if (f)
	x[_BYTE (m->_Size, i)] &= (~0 << f);
    }
}

double (trunc) (double x)
{
  int sign;

  switch (_Fpclassify (x))
    {
    case FP_INFINITE:
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_SUBNORMAL:
      sign = _Getsign ((unsigned char *) &x, _Dbl);
      return sign ? -0.0 : +0.0;
    default:
      _Trunc ((unsigned char *) &x, _Dbl);
      return x;
    }
}

float (truncf) (float x)
{
  int sign;

  switch (_Fpclassifyf (x))
    {
    case FP_INFINITE:
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_SUBNORMAL:
      sign = _Getsign ((unsigned char *) &x, _Flt);
      return sign ? -0.0F : +0.0F;
    default:
      _Trunc ((unsigned char *) &x, _Flt);
      return x;
    }
}

long double (truncl) (long double x)
{
  int sign;

  switch (_Fpclassifyl (x))
    {
    case FP_INFINITE:
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_SUBNORMAL:
      sign = _Getsign ((unsigned char *) &x, _Ldbl);
      return sign ? -0.0L : +0.0L;
    default:
      _Trunc ((unsigned char *) &x, _Ldbl);
      return x;
    }
}

/* END OF FILE */
