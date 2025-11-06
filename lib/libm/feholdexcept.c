/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* feholdexcept - save current floating-point environment

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The feholdexcept() function shall save the current floating-point 
   environment in the object pointed to by envp, clear the floating-point 
   status flags, and then install a non-stop (continue on floating-point 
   exceptions) mode, if available, for all floating-point exceptions.

   RETURN VALUE:

   The feholdexcept() function shall return zero if and only if non-stop 
   floating-point exception handling was successfully installed.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (feholdexcept) (fenv_t * envp)
{
  fegetenv (envp);
  feclearexcept (FE_ALL_EXCEPT);
  return 0;
}

/* END OF FILE */
