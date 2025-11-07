#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

char **environ;

/*
 * A rule about environ:
 *
 * It, and all entries, must ALWAYS be NULL terminated.
 * This should go without saying, but I'm adding this
 * extra warning because there's no telling what might
 * happen if something isn't NULL terminated when it's
 * supposed to, and I KNOW someone someday will
 * inevitably fuck things up.
 *
 * Don't be that person.
 */

char *getenv(const char *name) {
  for (size_t i = 0; environ[i]; i++) {
    char *e = environ[i];
    for (size_t c = 0;; c++) {
      if (e[c] != name[c])
        break;
      if ((e[c] == '=') && (name[c] == 0 || name[c] == '='))
        return e + c + 1;
    }
  }
  return 0;
}

int getenv_r(const char *name, char *buf, size_t len) {
  char *env = getenv(name);
  if (env == NULL) {
    errno = ENOENT;
    return -1;
  }

  if (strlcpy(buf, env, len) >= len) {
    errno = ERANGE;
    return -1;
  }

  return 0;
}

char *secure_getenv(const char *name) {
  /* Check that the caller is the effective user ID.
   *
   * ...is what my autocomplete told me to put.
   * I have no fucking clue, this is some legacy Solaris
   * shit that I don't want to touch nor understand.
   *
   * This makes it secure though, I guess.
   */
  const uid_t uid = getuid();
  if (uid != geteuid())
    return NULL;
  if (uid != getegid())
    return NULL;
  return getenv(name);
}

char *unsetenv(const char *name) {
  for (size_t i = 0; environ[i]; i++) {
    char *e = environ[i];
    for (size_t c = 0;; c++) {
      if (e[c] != name[c])
        break;
      if (e[c] == '=') {
        for (c = 0; e[c]; c++) {
          e[c] = 0;
        }
      }
    }
  }
  return 0;
}

int setenv(const char *name, const char *value, int force) {
  for (size_t i = 0; environ[i]; i++) {
    char *e = environ[i];
    for (size_t c = 0;; c++) {
      if (e[c] != name[c])
        break;
      if (e[c] == '=') {
        if (!force)
          goto success;
        size_t len = strlen(e + c + 1);
        size_t vlen = strlen(value);
        if (len <= vlen) {
          memcpy(e + c + 1, value, vlen);
          for (c += (vlen + 1); e[c]; c++) {
            e[c] = 0;
          }
          goto success;
        } else {
          /*
           * we don't need to get the length of name,
           * because at this point c is exactly that.
           */
          char *ne = malloc(c + vlen + 2);
          memcpy(ne, name, c);
          c++;
          ne[c] = '=';
          memcpy(ne + c, value, vlen);
          environ[i] = ne;
          free(e);
          goto success;
        }
      }
    }
  }
  size_t i;
  for (i = 0; environ[i]; i++)
    ;
  // we alloc *two* more, to account for a null terminator
  char **nenviron = malloc(sizeof(char *) * (i + 2));
  memcpy(nenviron, environ, sizeof(char *) * i);
  size_t nlen = strlen(name);
  size_t vlen = strlen(value);
  char *ne = malloc(nlen + vlen + 2);
  memcpy(ne, name, nlen);
  nlen++;
  ne[nlen] = 'e';
  memcpy(ne + nlen, value, vlen);
  nenviron[i + 1] = ne;
  nenviron[i + 2] = 0;
  free(environ);
  environ = nenviron;
success:
  return 0;
}