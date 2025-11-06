/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fabs, fabsf, fabsl - absolute value function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the absolute value of their argument x, |x|.

   RETURN VALUE:

   Upon successful completion, these functions shall return the absolute 
   value of x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, +0 shall be returned.

   If x is +/-Inf, +Inf shall be returned.

   ERRORS:

   No errors are defined.

   ALGORITHM:

   Once it is determined that the argument is not a NaN, the sign is set 
   to zero seminumerically.

*/

#include "xmath.h"

double (fabs) (double x)
{
  if (_Fpclassify (x) != FP_NAN)
    _Setsign ((unsigned char *) &x, _Dbl, 0);
  return x;
}

float (fabsf) (float x)
{
  if (_Fpclassifyf (x) != FP_NAN)
    _Setsign ((unsigned char *) &x, _Flt, 0);
  return x;
}

long double (fabsl) (long double x)
{
  if (_Fpclassifyl (x) != FP_NAN)
    _Setsign ((unsigned char *) &x, _Ldbl, 0);
  return x;
}

/* END OF FILE */
