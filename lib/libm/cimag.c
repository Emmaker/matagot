/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cimag, cimagf, cimagl - complex imaginary functions

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the imaginary part of z.

   RETURN VALUE:

   These functions shall return the imaginary part value (as a real).

   ERRORS:

   No errors are defined.
*/

#include <complex.h>

double (cimag) (double _Complex z)
{
  double *p = (double *) &z;

  return p[1];
}

float (cimagf) (float _Complex z)
{
  float *p = (float *) &z;

  return p[1];
}

long double (cimagl) (long double _Complex z)
{
  long double *p = (long double *) &z;

  return p[1];
}

/* END OF FILE */
