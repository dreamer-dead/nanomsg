/*
    Copyright (c) 2012 Martin Sustrik  All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef NN_WIN_INCLUDED
#define NN_WIN_INCLUDED

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <mswsock.h>
#include <process.h>
#include <ws2tcpip.h>

/* This structure does not exist on Windows platform. Let's fake it. */
struct sockaddr_un {
    short sun_family;
    char sun_path [sizeof (struct sockaddr_storage) -
        sizeof (short)];
};

#define ssize_t int

#ifdef NN_HAVE_MINGW
/* Mingw doesn't have this stuff */
#ifndef WSAID_CONNECTEX
#define WSAID_CONNECTEX \
    {0x25a207b9, 0xddf3, 0x4660, {0x8e,0xe9,0x76,0xe5,0x8c,0x74,0x06,0x3e}}
#endif

typedef BOOL WINAPI (*LPFN_CONNECTEX)(SOCKET s,
                                      const struct sockaddr* name,
                                      int namelen,
                                      PVOID lpSendBuffer,
                                      DWORD dwSendDataLength,
                                      LPDWORD lpdwBytesSent,
                                      LPOVERLAPPED lpOverlapped);

typedef BOOL WINAPI (*LPFN_DISCONNECTEX)(SOCKET hSocket,
                                         LPOVERLAPPED lpOverlapped,
                                         DWORD dwFlags,
                                         DWORD reserved);

#ifndef MSG_WAITALL
#define MSG_WAITALL 0x8 /* do not complete until packet is completely filled */
#endif

#if (_WIN32_WINNT >= 0x0600)
#ifndef PIPE_ACCEPT_REMOTE_CLIENTS
#define PIPE_ACCEPT_REMOTE_CLIENTS 0x0
#endif

#ifndef PIPE_REJECT_REMOTE_CLIENTS
#define PIPE_REJECT_REMOTE_CLIENTS 0x8
#endif

typedef struct _OVERLAPPED_ENTRY {
    ULONG_PTR lpCompletionKey;
    LPOVERLAPPED lpOverlapped;
    ULONG_PTR Internal;
    DWORD dwNumberOfBytesTransferred;
} OVERLAPPED_ENTRY, *LPOVERLAPPED_ENTRY;

WINBASEAPI WINBOOL WINAPI GetQueuedCompletionStatusEx(
    HANDLE hCompletionPort,
    LPOVERLAPPED_ENTRY lpCompletionPortEntries,
    ULONG ulCount,
    PULONG ulNumEntriesRemoved,
    DWORD dwMilliseconds,
    WINBOOL fAlertable);

WINBASEAPI WINBOOL WINAPI CancelIoEx(HANDLE hFile, LPOVERLAPPED lpOverlapped);
#endif  /* if (_WIN32_WINNT >= 0x0600) */
#endif  /* if defined NN_HAVE_MINGW */

#endif
