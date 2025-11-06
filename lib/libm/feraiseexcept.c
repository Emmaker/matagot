/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* feraiseexcept - raise floating-point exception

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The feraiseexcept() function shall attempt to raise the supported floating-
   point exceptions represented by the argument excepts. The order in which 
   these floating-point exceptions are raised is unspecified. Whether the 
   feraiseexcept() function additionally raises the inexact floating-point 
   exception whenever it raises the overflow or underflow floating-point 
   exception is implementation-defined.

   RETURN VALUE:

   If the argument is zero or if all the specified exceptions were successfully 
   raised, feraiseexcept() shall return zero. Otherwise, it shall return a 
   non-zero value.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (feraiseexcept) (int excepts)
{
  _FEcurrent._FEexcepts |= (excepts & FE_ALL_EXCEPT);
  return 0;
}

/* END OF FILE */
