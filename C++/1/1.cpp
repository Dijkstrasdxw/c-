#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH 1024  // 定义最大路径长度

// 获取文件的大小和最后修改时间
static int get_file_size_time(const char *filename) {
    struct stat statbuf;  // 定义一个结构体，用于保存文件状态信息

    // 获取文件的状态信息
    if(stat(filename, &statbuf) == -1) {  
        // 获取文件信息失败，输出错误信息
        printf("Get stat on %s Error: %s\n", filename, strerror(errno));  
        return -1;  // 返回错误
    }

    // 判断是否为目录
    if(S_ISDIR(statbuf.st_mode))  
        return 1;  // 如果是目录，返回1

    // 判断是否为普通文件
    if(S_ISREG(statbuf.st_mode)) {  
        // 输出文件的大小和最后修改时间
        printf("%s size: %ld bytes\t modified at: %s", filename, statbuf.st_size, ctime(&statbuf.st_mtime));
    }

    return 0;  // 如果是普通文件，返回0
}

// 深度优先遍历目录
void dfs(char *dirpath) {
    DIR *dirp;
    struct dirent *direntp;
    char path[MAX_PATH];

    // 打开目录
    if((dirp = opendir(dirpath)) == NULL) {
        // 打开目录失败，输出错误信息
        printf("open directory error!\n");
        return;
    }

    // 逐个读取目录中的项
    while((direntp = readdir(dirp)) != NULL) {
        // 跳过当前目录（"."）和父目录（".."）
        if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
            continue;

        // 构建当前项的完整路径
        memset(path, 0, 1024);
        strcpy(path, dirpath);
        strcat(path, "/");
        strcat(path, direntp->d_name);

        // 如果是目录，递归调用 dfs 继续遍历
        if(get_file_size_time(path) == 1)
            dfs(path);
    }

    // 关闭目录
    closedir(dirp);
}

// 广度优先遍历目录
void bfs(char *dirpath) {
    DIR *dirp;
    struct dirent *direntp;
    char *q[MAX_PATH];  // 目录队列
    char path[1024];
    int hh = 0;  // 队列头
    int tt = 0;  // 队列尾

    // 将根目录加入队列
    q[0]=(char*)malloc(1024);
    sprintf(q[0],dirpath);

    // 队列不为空时继续遍历
    while(hh <= tt) {
        char *curpath;
        curpath = q[hh++];  // 获取当前目录路径

        // 打开当前目录
        if((dirp = opendir(curpath)) == NULL) {
            printf("open directory error!\n");
            continue;
        }

        // 遍历当前目录中的项
        while((direntp = readdir(dirp)) != NULL) {
            // 跳过当前目录（"."）和父目录（".."）
            if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
               continue;

            // 构建当前项的完整路径
            memset(path, 0, 1024);
            strcpy(path, curpath);
            strcat(path, "/");
            strcat(path, direntp->d_name);

            // 如果是目录，将目录路径加入队列继续遍历
            if(get_file_size_time(path) == 1)
                q[++tt] =strdup(path);
        }

        // 关闭当前目录
        closedir(dirp);
    }
   for (int i = 1;i <= tt; i++) {
        free(q[i]);  // 释放每个通过 strdup 分配的内存
    }
}

// 主函数
int main(int argc, char **argv) {
    // 检查输入参数数量
    if(argc != 2) {  
        // 输入参数个数错误，提示用户如何使用程序
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);  // 参数错误，退出程序
    }

    // 调用 get_file_size_time 获取文件或目录信息
    int stats = get_file_size_time(argv[1]);
    if(stats == 0 || stats == -1)  // 如果是普通文件或出现错误，则退出程序
        exit(1);

    // 如果是目录，进行深度优先遍历
    printf("\n深度优先遍历：\n");
    dfs(argv[1]);

    // 进行广度优先遍历
    printf("\n广度优先遍历\n");
    bfs(argv[1]);

    // 正常退出程序
    exit(0);
}
