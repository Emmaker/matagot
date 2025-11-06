/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* csinh, csinhf, csinhl - complex hyperbolic sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex hyperbolic sine of z.

   RETURN VALUE:

   These functions shall return the complex hyperbolic sine value.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (csinh) (double _Complex z)
{
  double x, y;

  x = creal (z);
  y = cimag (z);
  return CMPLX (sinh (x) * cos (y), cosh (x) * sin (y));
}

float _Complex (csinhf) (float _Complex z)
{
  float x, y;

  x = crealf (z);
  y = cimagf (z);
  return CMPLXF (sinhf (x) * cosf (y), coshf (x) * sinf (y));
}

long double _Complex (csinhl) (long double _Complex z)
{
  long double x, y;

  x = creall (z);
  y = cimagl (z);
  return CMPLXL (sinhl (x) * cosl (y), coshl (x) * sinl (y));
}

/* END OF FILE */
