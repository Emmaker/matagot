/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* round, roundf, roundl - round to the nearest integer value in a 
   floating-point format 

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall round their argument to the nearest integer value in 
   floating-point format, rounding halfway cases away from zero, regardless of 
   the current rounding direction.

   RETURN VALUE:

   Upon successful completion, these functions shall return the rounded 
   integer value.  The result shall have the same sign as x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.
*/

#include "xmath.h"

double (round) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (_Getsign ((unsigned char *) &x, _Dbl))
	return trunc (x - 0.5);
      else
	return trunc (x + 0.5);
    }
}

float (roundf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (_Getsign ((unsigned char *) &x, _Flt))
	return truncf (x - 0.5F);
      else
	return truncf (x + 0.5F);
    }
}

long double (roundl) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      if (_Getsign ((unsigned char *) &x, _Ldbl))
	return truncl (x - 0.5L);
      else
	return truncl (x + 0.5L);
    }
}

/* END OF FILE */
