/****************************************************************
	-> file name : get_id.c
	-> author : fluency
	-> Created time : 2017-08-01 15:05
	-> function : Network initialization
****************************************************************/
#include "protocol.h"

int get_id()
{ 
    struct termios  oldtio, newtio;  
  
//-----------打开uart设备文件------------------  
    fd = open(WIFI_DEVICE, O_RDWR|O_NOCTTY);//没有设置 O_NONBLOCK，所以这里 read 和 write 是阻塞操作  
    if (fd < 0) {  
        perror(WIFI_DEVICE);  
        exit(-1);  
    }  
    else  
        printf("Open %s successfully\n", WIFI_DEVICE);  
      
//-----------设置操作参数-----------------------    
    tcgetattr(fd, &oldtio);//获取当前操作模式参数  
    memset( &newtio, 0, sizeof(newtio));  
	
    //波特率=115200 数据位=8 使能数据接收   
    newtio.c_cflag = B115200|CS8|CLOCAL|CREAD;  
    newtio.c_iflag = IGNPAR;   
    //newtio.c_oflag = OPOST | OLCUC; //  
    /* 设定为正规模式 */  
    //newtio.c_lflag = ICANON;  
  
    tcflush(fd, TCIFLUSH);//清空输入缓冲区和输出缓冲区  
    tcsetattr(fd, TCSANOW, &newtio);//设置新的操作参数  
	
	return 0;
}
