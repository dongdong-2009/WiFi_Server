/****************************************************************
	-> file name : protocol.h
	-> author : fluency
	-> Created time : 2017-08-01 15:05
	-> function : all header file and function declaration
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <pthread.h> 
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include "spidev.h"
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdarg.h>  
#include <termios.h>  


#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#define debug_pos() printf("%s-%d\n", __FUNCTION__, __LINE__);
#define PI 3.1415926535897932384626433832795028841971
#define RX_BUF_SIZE_DIV4 1024
#define RX_BUF_SIZE_DIV2 (RX_BUF_SIZE_DIV4 *2)
#define RX_BUF_SIZE_DIV8 512

#define SIZEBUF 256 //接收信息buf的大小
#define DATALEN 8  //截取字段
#define MSGBUF 24  //发送信息buf大小
#define MSGSIZE 1024*11  //发送显示信息msg大小

#define DEBUG 0
#define UART_DEVICE "/dev/ttyS2" //uart设备文件名 
#define WIFI_DEVICE "/dev/ttyS1" //uart设备文件名 


int get_id();
int login();
void pthread_spi();
void pthread_read();

pthread_mutex_t mutex;

int fdFpga;
int fd;
int flag;   //error 标志
int flag1;  //状态信息
int flag2;  //网卡信息
int flag3;  //频谱
int flag4;  //星座图

int da_data;
int ad_data;
int wb_data;

struct Reg{
	char name[32];
	int addr_base;
	int addr_offset;
	int width;
	uint32_t mask;
}tmp;
//名称	                                    基地址  偏移地址  位宽   掩码mask



