/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* carg, cargf, cargl - complex argument functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the argument (also called phase angle) of 
   z, with a branch cut along the negative real axis.

   RETURN VALUE:

   These functions shall return the value of the argument in the interval 
   [-pi, +pi].

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double (carg) (double _Complex z)
{
  return atan2 (cimag (z), creal (z));
}

float (cargf) (float _Complex z)
{
  return atan2f (cimagf (z), crealf (z));
}

long double (cargl) (long double _Complex z)
{
  return atan2l (cimagl (z), creall (z));
}

/* END OF FILE */
