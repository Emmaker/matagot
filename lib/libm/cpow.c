/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cpow, cpowf, cpowl - complex power functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex power function x^y, with a 
   branch cut for the first parameter along the negative real axis.

   RETURN VALUE

   These functions shall return the complex power function value.

   ERRORS
   
   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (cpow) (double _Complex x, double _Complex y)
{
  double r = cabs (x), theta = atan2 (cimag (x), creal (x)),
    c = creal (y), d = cimag (y), z, w;

  z = pow (r, c) * exp (d * theta);
  w = d * log (r) + c * theta;
  return CMPLX (z * cos (w), z * sin (w));
}

float _Complex (cpowf) (float _Complex x, float _Complex y)
{
  float r = cabsf (x), theta = atan2f (cimagf (x), crealf (x)),
    c = crealf (y), d = cimagf (y), z, w;

  z = powf (r, c) * expf (d * theta);
  w = d * logf (r) + c * theta;
  return CMPLXF (z * cosf (w), z * sinf (w));
}

long double _Complex (cpowl) (long double _Complex x, long double _Complex y)
{
  long double r = cabsl (x), theta = atan2l (cimagl (x), creall (x)),
    c = creall (y), d = cimagl (y), z, w;

  z = powl (r, c) * expl (d * theta);
  w = d * logl (r) + c * theta;
  return CMPLXL (z * cosl (w), z * sinl (w));
}

/* END OF FILE */
