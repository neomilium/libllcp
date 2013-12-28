/*-
 * Free/Libre Near Field Communication (NFC) library
 *
 * Libnfc historical contributors:
 * Copyright (C) 2009      Roel Verdult
 * Copyright (C) 2009-2013 Romuald Conty
 * Copyright (C) 2010-2012 Romain Tartière
 * Copyright (C) 2010-2013 Philippe Teuwen
 * Copyright (C) 2012-2013 Ludovic Rousseau
 * See AUTHORS file for a more comprehensive list of contributors.
 * Additional contributors of this file:
 * Copyright (C) 2011      Glenn Ergeerts
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/**
 * @file windows.h
 * @brief Provide some windows related hacks due to lack of POSIX compat
 */

#ifndef __WINDOWS_H__
#define __WINDOWS_H__

#  include <winsock2.h>
#  include <ws2tcpip.h>
#  include <windows.h>
#  include <winerror.h>
#  include "win32/err.h"
#  include <stdio.h>
#  include <stdarg.h>
#  include <stdlib.h>

#  if defined (__MINGW32__)
/*
 * Cheating here on the snprintf to incorporate the format argument
 * into the VA_ARGS. Else we get MinGW errors regarding number of arguments
 * if doing a fixed string with no arguments.
*/
#    define snprintf(S, n, ...) sprintf(S, __VA_ARGS__)
#    define pipe(fds) _pipe(fds, 5000, _O_BINARY)

#	 ifndef ETIMEDOUT
#      define ETIMEDOUT     WSAETIMEDOUT
#	 endif

#    define ENOTSUP       WSAEOPNOTSUPP

#	 ifndef ECONNABORTED
#      define ECONNABORTED  WSAECONNABORTED
#	 endif

#  else
#    define snprintf sprintf_s
#    define strdup _strdup
#  endif

/*
 * setenv and unsetenv are not Windows compliant nor implemented in MinGW.
 * These declarations get rid of the "implicit declaration warning."
 */
int setenv(const char *name, const char *value, int overwrite);
void unsetenv(const char *name);

int asprintf( char **, char *, ... );
int vasprintf( char **, char *, va_list );

/*
 * define socketpair function which is not supported by MinGW
 */
int socketpair(int domain, int type, int protocol, SOCKET socks[2]);

#endif