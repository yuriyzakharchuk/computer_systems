/*
 * Definition of some Linux system calls on AMD64
 * For parameter info see
 *   http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
 */
SYS_READ    =  0
SYS_WRITE   =  1
SYS_OPEN    =  2
SYS_CLOSE   =  3
SYS_LSEEK   =  8
SYS_MMAP    =  9
SYS_MUNMAP  = 11
SYS_DUP2    = 33
SYS_SOCKET  = 41
SYS_CONNECT = 42
SYS_ACCEPT  = 43
SYS_BIND    = 49
SYS_LISTEN  = 50
SYS_FORK    = 57
SYS_EXECVE  = 59
SYS_EXIT    = 60
SYS_WAIT4   = 61

/*
 * File descriptors
 */
STDIN  = 0
STDOUT = 1
STDERR = 2

/*
 * Open constants
 */
O_RDONLY = 0
O_WRONLY = 1
O_RDWR   = 2
O_TRUNC  = 0x00001000
O_APPEND = 0x00002000
O_DIRECT = 0x00040000

/*
 * Seek constants
 */
SEEK_SET = 0
SEEK_CUR = 1
SEEK_END = 2

/*
 * Memory mapping constants
 */
PROT_READ  = 1
PROT_WRITE = 2
PROT_EXEC  = 4

MAP_SHARED  = 1
MAP_PRIVATE = 2

/*
 * Socket constants
 */
AF_INET = 2
SOCK_STREAM = 1
IPPROTO_TCP = 6
