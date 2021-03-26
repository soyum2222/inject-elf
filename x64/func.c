#define SYS_memfd_create 319
#define SYS_write 1
#define SYS_execve 59

char* itoa(int num,char* str,int radix);
void append(char *s1, char *s2, int n);
int syscall(unsigned long long callNumber,unsigned long long arg1 ,unsigned long long arg2,unsigned long long arg3);

int entry(unsigned long long filePoint, unsigned long long fileSize,unsigned long long base) {

    char fdName[] = "";

    int fd = syscall(SYS_memfd_create, &fdName, 0x0001, 0);
    if (fd == 0) {
        return 0;
    }

    int n = syscall(SYS_write, fd, filePoint, fileSize);
    if (n == 0) {
        return 0;
    }

    char fdPath[25] = "/proc/self/fd/";

    char fdStr[6];

    itoa(fd,fdStr,10);

    append(fdPath,fdStr,25);

    char tmpName[10] = "fuck name";
    int err = syscall(SYS_execve, fdPath, 0, 0);
    if (err != 0) {
        return 0;
    }

    return 0;
}

void append(char *s1, char *s2, int n) {
    for (int i = 0; i < n; ++i) {
        if (*s1 == 0) {
            *s1 = *s2;

            if (s2 == 0) {
                return;
            }
            s1++;
            s2++;

        } else {
            s1++;
        }
    }
    return;
}

char* itoa(int num,char* str,int radix){
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum;
    int i=0,j,k;

    if(radix==10&&num<0)
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;

    do
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;

    }while(unum);

    str[i]='\0';

    if(str[0]=='-') k=1;
    else k=0;

    char temp;
    for(j=k;j<=(i-1)/2;j++)
    {
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }

    return str;
}
int syscall(unsigned long long callNumber,unsigned long long arg1 ,unsigned long long arg2,unsigned long long arg3){

    unsigned long long ret ;
    __asm__(
    "movq %1,%%rdx;\n\t"
    "movq %2,%%rsi;\n\t"
    "movq %3,%%rdi;\n\t"
    "movq %4,%%rax;\n\t"
    "syscall;\n\t"
    "movq %%rax,%0;\n\t"
    :"=g"(ret)
    :"m"(arg3),"m"(arg2),"m"(arg1),"m"(callNumber)
    );
    return ret;
}
