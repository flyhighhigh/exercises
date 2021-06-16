#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#define maxbuf 3

typedef unsigned char uchar;

void swapchar(int fd,int a,int b){

    uchar buf_a[maxbuf];
    uchar buf_b[maxbuf];

    //讀取左元素buf1
    lseek(fd,a,SEEK_SET);
    read(fd,buf_a,1);
        

    //讀取右元素buf2
    lseek(fd,b,SEEK_SET);
    read(fd,buf_b,1);

    //右元素貼到左元素
    lseek(fd,a,SEEK_SET);
    write(fd,buf_b,1);

    //左元素放到右元素
    lseek(fd,b,SEEK_SET);
    write(fd,buf_a,1);
}

int main(int argc,char** argv){

    uchar buf[maxbuf];
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
    
    for(int i=0;i<len;i++){
        lseek(fd,i,SEEK_SET);
        read(fd,buf,1);
        if(buf[0]>=224){
            swapchar(fd,i,i+2);
            i+=2;
        }
    }
    
    while(idx<len/2){//須注意read會自動將游標往前

        swapchar(fd,idx,len-idx-1);
        idx++;
    }
    close(fd);

    exit(0);
}
