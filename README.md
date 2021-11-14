# librspd

Simple header-only, arch-agnostic, RSP server library.

# What is it about, already ?

See https://sourceware.org/gdb/onlinedocs/gdb/Remote-Protocol.html

You can see usage of it here:
- https://github.com/nsauzede/xtem
- https://github.com/nsauzede/myrv

# Test it

Run the simple example, a fake x86 gdb stub that always returns 0 for everything,
and accepts RSP commands '?', 'g', 'm', 's', 'c' and 'k'.

```
$ make mrproper all && (./rspd &) && ./run_gdb.sh
rm -f rspd *.o
cc -Wall -Werror -Wextra -g -O0   -c -o rspd.o rspd.c
cc -o rspd rspd.o -pthread
Listening on port 1235..
Remote debugging using :1235
warning: No executable has been specified and target does not support
determining executable automatically.  Try using the "file" command.
0x00000000 in ?? ()
(gdb) si
0x00000000 in ?? ()
(gdb) c
Continuing.

Program received signal SIGTRAP, Trace/breakpoint trap.
0x00000000 in ?? ()
(gdb) info r
eax            0x0                 0
ecx            0x0                 0
edx            0x0                 0
ebx            0x0                 0
esp            0x0                 0x0
ebp            0x0                 0x0
esi            0x0                 0
edi            0x0                 0
eip            0x0                 0x0
eflags         0x0                 [ ]
cs             0x0                 0
ss             0x0                 0
ds             0x0                 0
es             0x0                 0
fs             0x0                 0
gs             0x0                 0
(gdb)

```
