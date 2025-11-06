/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fpclassify.c - classify real floating type

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fpclassify() macro shall classify its argument value as NaN, infinite, 
   normal, subnormal, zero, or into another implementation-defined category. 
   First, an argument represented in a format wider than its semantic type 
   is converted to its semantic type. Then classification is based on the 
   type of the argument.

   RETURN VALUE:

   The fpclassify() macro shall return the value of the number classification 
   macro appropriate to the value of its argument.

   ERRORS:

   No errors are defined.
*/

#include "xmath.h"

/* _Classify - the function that does all the dirty work */
static int
_Classify (unsigned char *x, const _FP_METRIC_T * const m)
{
  unsigned long ex, ma;
  int i, mb, nz;

  for (ex = 0UL, i = 0; i < 3; ++i)
    ex = (ex << CHAR_BIT) | x[_BYTE (m->_Size, i)];
  ex &= ~(~0 << (CHAR_BIT * 3 - 1));
  ma = ex;
  mb = (CHAR_BIT * 3 - 1) - m->_Ebits;
  ex >>= mb;
  ma &= ~(~0 << mb);
  nz = (ex ? ((ex == ~(~0 << m->_Ebits)) ? 020 : 010) : 0);
  if (ma)
    nz |= 1;
  else
    {
      for (i = 3; i < m->_Size; ++i)
	{
	  if (x[_BYTE (m->_Size, i)])
	    {
	      nz |= 1;
	      break;
	    }
	}
    }
  switch (nz)
    {
    case 0:
      return FP_ZERO;
    case 1:
      return FP_SUBNORMAL;
    case 020:
      return FP_INFINITE;
    case 021:
      return FP_NAN;
    default:
      return FP_NORMAL;
    }
}

int
_Fpclassify (double d)
{
  return _Classify ((unsigned char *) &d, _Dbl);
}

int
_Fpclassifyf (float f)
{
  return _Classify ((unsigned char *) &f, _Flt);
}

int
_Fpclassifyl (long double l)
{
  return _Classify ((unsigned char *) &l, _Ldbl);
}

/* END OF FILE */
