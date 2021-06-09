#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#define maxbuf 100

int main(int argc,char** argv){

    char buf[maxbuf];
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
    int readcnt;
    while((readcnt=read(fd,buf,1))>0){
        if(isupper(buf[0]))buf[0]=tolower(buf[0]);
        //從current的位置移動-1
        lseek(fd,-1,SEEK_CUR);
        write(fd,buf,1);
    }
    close(fd);

    exit(0);
}