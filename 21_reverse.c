#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#define maxbuf 3

int main(int argc,char** argv){

    char buf1[maxbuf];
    char buf2[maxbuf];
    int fd;

    if(argc!=2){
        fprintf(stderr,"???\n");
        exit(1);
    }

    fd=open(argv[1],O_RDWR);
    
    if(fd<0){//open失敗 
        fprintf(stderr,"open err: %s\n",argv[1]);
        exit(1);
    }
    int idx=0;
    int len=lseek(fd,0,SEEK_END);
    printf("len=%d\n",len);
    while(idx<len/2){//須注意read會自動將游標往前

        //讀取左元素buf1
        lseek(fd,idx,SEEK_SET);
        read(fd,buf1,1);
        

        //讀取右元素buf2
        lseek(fd,-1*idx-1,SEEK_END);
        read(fd,buf2,1);

        //右元素貼到左元素
        lseek(fd,idx,SEEK_SET);
        write(fd,buf2,1);

        //左元素放到右元素
        lseek(fd,-1*idx-1,SEEK_END);
        write(fd,buf1,1);

        idx++;
    }
    close(fd);

    exit(0);
}