/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* catan, catanf, catanl - complex arc tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers 
   to the ISO C standard.

   These functions shall compute the complex arc tangent of z, with branch 
   cuts outside the interval [-i, +i] along the imaginary axis.

   RETURN VALUE

   These functions shall return the complex arc tangent value, in the range 
   of a strip mathematically unbounded along the imaginary axis and in the 
   interval [-pi/2, +pi/2] along the real axis.

   ERRORS

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (catan) (double _Complex z)
{
  double x = creal (z);
  double y = cimag (z);
  double x2 = x * x;
  double y2 = y * y;
  double denom = x2 + (1 - y) * (1 - y);
  double real = 0.5 * atan2 (2.0 * x, x2 + y2 - 1.0);
  double imag = -0.25 * log (denom);
  return CMPLX (real, imag);
}

float _Complex (catanf) (float _Complex z)
{
  float x = crealf (z);
  float y = cimagf (z);
  float x2 = x * x;
  float y2 = y * y;
  float denom = x2 + (1.0F - y) * (1.0F - y);
  float real = 0.5F * atan2f (2.0F * x, x2 + y2 - 1.0F);
  float imag = -0.25F * logf (denom);
  return CMPLXF (real, imag);
}

long double _Complex (catanl) (long double _Complex z)
{
  long double x = creall (z);
  long double y = cimagl (z);
  long double x2 = x * x;
  long double y2 = y * y;
  long double denom = x2 + (1.0L - y) * (1.0L - y);
  long double real = 0.5L * atan2 (2.0L * x, x2 + y2 - 1.0L);
  long double imag = -0.25L * logl (denom);
  return CMPLXL (real, imag);
}

/* END OF FILE */
