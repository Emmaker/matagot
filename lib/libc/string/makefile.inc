.PATH: ${.CURDIR}/string

SRCS+= strlcpy.c strlen.c memcpy.c
# a non-negligable portion of these functions depend on not currently existant headers,
# so just move files up to the SRCS line as we need them
#bcmp.c bcopy.c bzero.c ffs.c ffsl.c ffsll.c fls.c flsl.c flsll.c makefile memccpy.c memchr.c memcmp.c memcpy.c \
#memmem.c memmove.c mempcpy.c memrchr.c memset.c memset_explicit.c memset_s.c stpcpy.c stpncpy.c strcasecmp.c \
#strcasestr.c strcat.c strchr.c strchrnul.c strcmp.c strcoll.c strcpy.c strcspn.c strdup.c strerror.c strlcat.c \
#strlen.c strmode.c strncat.c strncmp.c strncpy.c strndup.c strnlen.c strnstr.c strpbrk.c strrchr.c \
#strsep.c strsignal.c strspn.c strstr.c strtok.c strverscmp.c strxfrm.c swab.c timingsafe_bcmp.c \
#timingsafe_memcmp.c wcpcpy.c wcpncpy.c wcscasecmp.c wcscat.c wcschr.c wcscmp.c wcscoll.c wcscpy.c wcscspn.c \
#wcsdup.c wcslcat.c wcslcpy.c wcslen.c wcsncasecmp.c wcsncat.c wcsncmp.c wcsncpy.c wcsnlen.c wcspbrk.c wcsrchr.c \
#wcsspn.c wcsstr.c wcstok.c wcswidth.c wcsxfrm.c wmemchr.c wmemcmp.c wmemcpy.c wmemmove.c wmempcpy.c wmemset.c
