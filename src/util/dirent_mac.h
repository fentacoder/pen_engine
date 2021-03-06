/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
 /*-
  * Copyright (c) 1989, 1993
  *	The Regents of the University of California.  All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions
  * are met:
  * 1. Redistributions of source code must retain the above copyright
  *    notice, this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright
  *    notice, this list of conditions and the following disclaimer in the
  *    documentation and/or other materials provided with the distribution.
  * 3. All advertising materials mentioning features or use of this software
  *    must display the following acknowledgement:
  *	This product includes software developed by the University of
  *	California, Berkeley and its contributors.
  * 4. Neither the name of the University nor the names of its contributors
  *    may be used to endorse or promote products derived from this software
  *    without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  * SUCH DAMAGE.
  *
  *	@(#)dirent.h	8.2 (Berkeley) 7/28/94
  */
#ifdef __APPLE__
#ifndef _DIRENT_H_
#define _DIRENT_H_

  /*
   * The kernel defines the format of directory entries returned by
   * the getdirentries(2) system call.
   */
#include <sys/types.h>
#include <sys/dirent.h>

#ifdef _POSIX_SOURCE
	typedef void* DIR;
#else

#define	d_ino		d_fileno	/* backward compatibility */

   /* definitions for library routines operating on directories. */
#define	DIRBLKSIZ	1024

	struct _telldir;		/* see telldir.h */

	/* structure describing an open directory. */
typedef struct _dirdesc {
	int	dd_fd;		/* file descriptor associated with directory */
	long	dd_loc;		/* offset in current buffer */
	long	dd_size;	/* amount of data returned by getdirentries */
	char* dd_buf;	/* data buffer */
	int	dd_len;		/* size of data buffer */
	long	dd_seek;	/* magic cookie returned by getdirentries */
	long	dd_rewind;	/* magic cookie for rewinding */
	int	dd_flags;	/* flags for readdir */
	pthread_mutex_t	dd_lock; /* for thread locking */
	struct _telldir* dd_td;	/* telldir position recording */
} DIR;

#define	dirfd(dirp)	((dirp)->dd_fd)

/* flags for opendir2 */
#define DTF_HIDEW	0x0001	/* hide whiteout entries */
#define DTF_NODUP	0x0002	/* don't return duplicate names */
#define DTF_REWIND	0x0004	/* rewind after reading union stack */
#define __DTF_READALL	0x0008	/* everything has been read */

#ifndef NULL
#define	NULL	0
#endif

#endif /* _POSIX_SOURCE */

#ifndef KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
DIR* opendir(const char*);
struct dirent* readdir(DIR*);
void rewinddir(DIR*);
int closedir(DIR*);
#ifndef _POSIX_SOURCE
DIR* __opendir2(const char*, int);
long telldir(DIR*);
void seekdir(DIR*, long);
int scandir(const char*, struct dirent***,
	int (*)(struct dirent*), int (*)(const void*, const void*));
int alphasort(const void*, const void*);
int getdirentries(int, char*, int, long*);
int readdir_r(DIR*, struct dirent*, struct dirent**);
#endif /* not POSIX */
__END_DECLS

#endif /* !KERNEL */

#endif /* !_DIRENT_H_ */
#endif /* __APPLE__ */