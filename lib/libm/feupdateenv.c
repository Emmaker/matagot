/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* feupdateenv - update floating-point environment

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The feupdateenv() function shall attempt to save the currently raised 
   floating-point exceptions in its automatic storage, attempt to install the 
   floating-point environment represented by the object pointed to by envp, 
   and then attempt to raise the saved floating-point exceptions. The argument 
   envp shall point to an object set by a call to feholdexcept() or fegetenv(), 
   or equal a floating-point environment macro.

   RETURN VALUE:

   The feupdateenv() function shall return a zero value if and only if all the 
   required actions were successfully carried out.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (feupdateenv) (const fenv_t * envp)
{
  int ex = fetestexcept (FE_ALL_EXCEPT);
  if (fesetenv (envp))
    return 1;
  feraiseexcept (ex);
  return 0;
}

/* END OF FILE */
