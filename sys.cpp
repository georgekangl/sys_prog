
#include <iostream> // for std::cerr
#include <sys/stat.h> // for open()
#include <fcntl.h> // for open(), fcntl()
#include <setjmp.h> // for setjmp(), longjmp()
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

using namespace std;

extern char **environ;
static jmp_buf env;

static void f2() {
    longjmp(env, 2);
}

static void f1(int ac) {
    if(ac == 1)
        longjmp(env, 1);
    f2();
}

int main(int ac, char* av[])
{
    // first system call
//    pid_t mypid;
//    mypid = getpid();
//    printf("My PID is %ld\n", (long)mypid);
//---------------------------------------------------------------------------------------------------
    // functionality : simple copy command
    // system calls: open(), read(), write(), close()
//    int inputFd, outputFd, openFlags;
//    mode_t filePerms;
//    ssize_t numRead;
//    char buf[BUF_SIZE];
//
//    if(ac != 3 || strcmp(av[1], "--help") == 0) {
//        cerr << av[0] << "old_file new_file" << endl;
//    }
//
//    inputFd = open(av[1], O_RDONLY);
//    if(inputFd == -1) // always check open() return status
//        cerr << "old file not opened!" << endl;
//
//    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
//    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
//    outputFd = open(av[2], openFlags, filePerms);
//    if(outputFd == -1)
//        cerr << "new file not opened!" << endl;
//
//    while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
//        if(write(outputFd, buf, numRead) != numRead)
//            cerr << "write wrongly!" << endl;
//    if(numRead == -1)
//        cerr << "read wrongly!" << endl;
//
//    if(close(inputFd) == -1)
//        cerr << "close input error!" << endl;
//    if(close(outputFd) == -1)
//        cerr << "close output error!" << endl;
//-----------------------------------------------------------------------------------------------------
    // system call: creat()
    // In early UNIX, open() will not generate a new file if the file is not existed.
    // creat will be used to create a new file.
//    creat("created_file.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
//----------------------------------------------------------------------------------------------------------------------
    // system call: lseek()
    //Note : l means long
//    int fd = open("f1.txt", O_RDONLY | O_WRONLY);
//    if(fd == -1) cerr << "not open!" << endl;
//    off_t offset = lseek(fd, 0, SEEK_END);
//    cout << "offset : " << (int)offset << endl;
//----------------------------------------------------------------------------------------------------------------------
    // system call: fstat()
//    struct stat sb;
//    if(fstat(fd, &sb) == -1)
//        cerr << "no stat!" << endl;
//    cout << " blocks " << (int)sb.st_blocks << " size " << (int)sb.st_size << endl;
//----------------------------------------------------------------------------------------------------------------------
    // race condition & atomicity
//    int fd = open(av[1], O_WRONLY);
//    if(fd != -1) {
//        printf("[PID: %ld] File: \"%s\"\n", (long)getpid(), av[1]);
//        close(fd);
//    }
//    else {
//        if (errno != ENOENT) {
//            cerr << "Other error!\n" << endl;
//        } else {
//            printf("[PID: %ld] File \"%s\" doesn't exist!\n", (long) getpid(), av[1]);
//            if (ac > 2) { // format like: sysProgram filename sleep
//                sleep(5);
//                printf("[PID: %ld] Done Sleeping!\n", (long) getpid());
//            }
//
//            fd = open(av[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
////            fd = open(av[1], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR); // Using O_EXCL to avoid race condition
//            if (fd == -1)
//                cerr << "can not create!\n" << endl;
//            else
//                printf("[PID:%ld] Created File: \"%s\"\n", (long) getpid(), av[1]);
//        }
//    }
//----------------------------------------------------------------------------------------------------------------------
    // system call: fcntl()
//    int openFlags, filePerms, fd;
//    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
//    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
//    fd = open(av[1], openFlags, filePerms);
//    int flags = fcntl(fd, F_GETFL);
//    printf("original flags: %d, F_GETFL: %d\n", openFlags, flags);
//    if(flags & O_WRONLY)
//        printf("write only flag!\n");
//----------------------------------------------------------------------------------------------------------------------
    // system call: mkstemp()
//    int fd;
//    char t[] = "/tmp/somestringXXXXXX";
//    fd = mkstemp(t);
//    if (fd == -1) cerr << "mkstemp error!" << endl;
//    printf("Generated filename was: %s\n", t);
//    unlink(t);
//    if(close(fd) == -1) cerr << "close error!" << endl;

    // system call: tmpfile() and print the temp file name
//    int MAXSIZE = 1024;
//    char filename[MAXSIZE];
//    char proclnk[MAXSIZE];
//    FILE *fp = tmpfile();
//    //printf("fp%p\n", fp);
//    ssize_t r;
//    int fno;
//    if(fp != NULL) {
//        fno = fileno(fp);
//        sprintf(proclnk, "/proc/self/fd/%d\n", fno);
//        r = readlink(proclnk, filename, MAXSIZE);
//        if(r < 0) {
//            printf("failed to readlink\n");
//            exit(1);
//        }
//        filename[r] = '\0';
//        printf("fp->fno->filename: %p->%d->%s\n", fp, fno, filename);
//    }
//----------------------------------------------------------------------------------------------------------------------
    // access to global variable char **environ
//    char **ep;
//    for(ep = environ; ep != NULL; ep++) {
//        puts(*ep);
//    }
//    exit(EXIT_SUCCESS);
//----------------------------------------------------------------------------------------------------------------------
    // system call: setjmp() and longjmp()
   // switch(setjmp(env)) {
   //     case 0:
   //         printf("calling f1() after initial setjmp()\n");
   //         f1(ac);
   //         break;
   //     case 1:
   //         printf("we jumped back from f1()\n");
   //         break;
   //     case 2:
   //         printf("we jumped back from f2()\n");
   //         break;
   // }
//----------------------------------------------------------------------------------------------------------------------
    // 

}
