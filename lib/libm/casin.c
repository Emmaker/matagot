/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* casin, casinf, casinl - complex arc sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex arc sine of z, with branch cuts 
   outside the interval [-1, +1] along the real axis.

   RETURN VALUE:

   These functions shall return the complex arc sine value, in the range of a 
   strip mathematically unbounded along the imaginary axis and in the interval 
   [-pi/2, +pi/2] along the real axis.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

/* casin(z) = -i clog(i z + csqrt(1 - z*z)) */

double _Complex (casin) (double _Complex z)
{
  double x, y;
  double _Complex w;

  x = creal (z);
  y = cimag (z);
  w = CMPLX (1.0 - (x - y) * (x + y), -2.0 * x * y);
  return clog (CMPLX (-y, x) + csqrt (w));
}

float _Complex (casinf) (float _Complex z)
{
  float x, y;
  float _Complex w;

  x = crealf (z);
  y = cimagf (z);
  w = CMPLXF (1.0F - (x - y) * (x + y), -2.0F * x * y);
  return clogf (CMPLXF (-y, x) + csqrtf (w));
}

long double _Complex (casinl) (long double _Complex z)
{
  long double x, y;
  long double _Complex w;

  x = creall (z);
  y = cimagl (z);
  w = CMPLXL (1.0L - (x - y) * (x + y), -2.0L * x * y);
  return clogl (CMPLXL (-y, x) + csqrtl (w));
}

/* END OF FILE */
