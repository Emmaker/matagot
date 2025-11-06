/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* ceil, ceilf, ceill - ceiling value function

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here 
   and the ISO C standard is unintentional. This volume of POSIX.1-2008 
   defers to the ISO C standard.

   These functions shall compute the smallest integral value not less 
   than x.

   RETURN VALUE:

   The result shall have the same sign as x.

   Upon successful completion, ceil(), ceilf(), and ceill() shall return 
   the smallest integral value not less than x, expressed as a type 
   double, float, or long double, respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   ERRORS:

   No errors are defined.
    
   ALGORITHM:
   
   Use trunc to chop off the frac bits, then adjust the value. 
*/

#include "xmath.h"

double (ceil) (double x)
{
  double y;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      y = trunc (x);
      return (y >= x) ? y : y + 1.0;
    }
}

float (ceilf) (float x)
{
  float y;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      y = truncf (x);
      return (y >= x) ? y : y + 1.0F;
    }
}

long double (ceill) (long double x)
{
  long double y;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return x;
    default:
      y = truncl (x);
      return (y >= x) ? y : y + 1.0L;
    }
}

/* END OF FILE */
