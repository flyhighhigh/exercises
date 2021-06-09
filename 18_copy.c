#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#define maxbuf 100

int main(int argc,char** argv){

    char buf[maxbuf];
    int fd_in,fd_out;//兩個檔案的指標

    if(argc!=3){
        fprintf(stderr,"???\n");
        exit(1);
    }

    fd_in=open(argv[1],O_RDONLY);

    fd_out=open(argv[2],O_WRONLY|O_CREAT,0600);
    //0600 可區分成四個位數
    //0    第一位數代表user id
    // 6   第二位數代表owner權限
    //  0  第三位數代表group權限
    //   0 第四位數代表other權限

    //解讀方式：
    // 6 (十進位) = 110 (二進位) => rwx (read 讀, write 寫, execute 執行)
    //所以 owner=6 就是owner有讀寫的權限，沒有執行的權限
    
    if(fd_in<0){//open失敗
        fprintf(stderr,"open err: %s\n",argv[1]);
        exit(1);
    }
    if(fd_out<0){
        fprintf(stderr,"open err: %s\n",argv[2]);
        exit(1);
    }
    int readcnt;
    while((readcnt=read(fd_in,buf,maxbuf))>0){
        //printf("readcnt %d\n",readcnt);
        write(fd_out,buf,readcnt);
    }

    exit(0);
}