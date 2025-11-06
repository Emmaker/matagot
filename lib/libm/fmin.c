/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fmin, fminf, fminl - determine minimum numeric value of two floating-point 
   numbers

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall determine the minimum numeric value of their 
   arguments. NaN arguments shall be treated as missing data: if one argument 
   is a NaN and the other numeric, then these functions shall choose the 
   numeric value.

   RETURN VALUE:

   Upon successful completion, these functions shall return the minimum 
   numeric value of their arguments.

   If just one argument is a NaN, the other argument shall be returned.

   If x and y are NaN, a NaN shall be returned.

   ERRORS

   No errors are defined.
*/

#include "xmath.h"

double (fmin) (double x, double y)
{
  int errx, erry;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);

  if (erry == FP_NAN)
    return x;
  if (errx == FP_NAN)
    return y;
  return (x < y) ? x : y;
}

float (fminf) (float x, float y)
{
  int errx, erry;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);

  if (erry == FP_NAN)
    return x;
  if (errx == FP_NAN)
    return y;
  return (x < y) ? x : y;
}

long double (fminl) (long double x, long double y)
{
  int errx, erry;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);

  if (erry == FP_NAN)
    return x;
  if (errx == FP_NAN)
    return y;
  return (x < y) ? x : y;
}

/* END OF FILE */
