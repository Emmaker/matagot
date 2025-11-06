/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cproj, cprojf, cprojl - complex projection functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers to 
   the ISO C standard.

   These functions shall compute a projection of z onto the Riemann sphere: 
   z projects to z, except that all complex infinities (even those with one 
   infinite part and one NaN part) project to positive infinity on the real 
   axis. If z has an infinite part, then cproj(z) shall be equivalent to:

   INFINITY + I * copysign(0.0, cimag(z))

   RETURN VALUE:

   These functions shall return the value of the projection onto the Riemann 
   sphere.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (cproj) (double _Complex z)
{
  double x, y;

  x = creal (z);
  y = cimag (z);
  if (_Fpclassify (x) == FP_INFINITE || _Fpclassify (y) == FP_INFINITE)
    return CMPLX (_Dbl->_Inf._D, copysign (0.0, y));
  return z;
}

float _Complex (cprojf) (float _Complex z)
{
  float x, y;

  x = crealf (z);
  y = cimagf (z);
  if (_Fpclassifyf (x) == FP_INFINITE || _Fpclassifyf (y) == FP_INFINITE)
    return CMPLXF (_Flt->_Inf._F, copysignf (0.0F, y));
  return z;
}

long double _Complex (cprojl) (long double _Complex z)
{
  long double x, y;

  x = creall (z);
  y = cimagl (z);
  if (_Fpclassifyl (x) == FP_INFINITE || _Fpclassifyl (y) == FP_INFINITE)
    return CMPLXL (_Ldbl->_Inf._L, copysignl (0.0L, y));
  return z;
}

/* END OF FILE */
