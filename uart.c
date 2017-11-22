#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <termios.h>  
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>


#define UART_DEVICE "/dev/ttyS1" //uart设备文件名  
  
int main(int argc, char *argv[])  
{  
  
    int    fd, res;  
    struct termios  oldtio, newtio;  
    char  ch;  
    char buf[256] = {0}; 
  
//-----------打开uart设备文件------------------  
    fd = open(UART_DEVICE, O_RDWR|O_NOCTTY);//没有设置 O_NONBLOCK，所以这里 read 和 write 是阻塞操作  
    if (fd < 0) {  
        perror(UART_DEVICE);  
        exit(-1);  
    }  
    else  
        printf("Open %s successfully\n", UART_DEVICE);  
      
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
    
	pid_t pid=fork();
	if(pid < 0)
	{
		printf("fork erreo\n");
	}
	if(pid == 0) //子进程
	{
		//------------向urat发送数据-------------------
		res = write(fd, "\r\nBegin Uart tx", 16); 
		printf("write\n");
		while(1) {  
			//从控制台终端获取数据，然后通过uart发送出去，直到接收到！字符  
			while((ch = getchar()) != '!') {  
				buf[0] = ch;  
				res = write( fd, buf, 1);  
			}  
			
			buf[0] = ch;  
			buf[1] = '\n';  
			res = write(fd, buf, 2);
			break;			
		}
	}
	else{  //父进程
		//-------------从uart接收数据-------------------  
		while(1) {  
			res = read(fd, buf, 255);//程序将在这里挂起，直到从uart接收到数据（阻塞操作）  
			if (res == 0)   
				continue;  
			  
			buf[res] = '\0';  
			printf("res = %d, buf = %s\n", res, buf);//将uart接收到的字符打印出来  
			if (buf[0] == '!')//uart接收到！字符后退出while  
				break;  
		}
	}	
//------------关闭uart设备文件，恢复原先参数--------  
    close(fd);  
    printf("Close %s\n", UART_DEVICE);  
    tcsetattr(fd, TCSANOW, &oldtio); //恢复原先的设置  
  
    return 0;  
}
