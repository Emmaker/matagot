/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fetestexcept - test floating-point exception flags

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fetestexcept() function shall determine which of a specified subset 
   of the floating-point exception flags are currently set. The excepts 
   argument specifies the floating-point status flags to be queried.

   RETURN VALUE:

   The fetestexcept() function shall return the value of the bitwise-
   inclusive OR of the floating-point exception macros corresponding to the 
   currently set floating-point exceptions included in excepts.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fetestexcept) (int excepts)
{
  return (_FEcurrent._FEexcepts & excepts);
}

/* END OF FILE */
