/****************************************************************
	-> file name : main.c
	-> author : fluency
	-> Created time : 2017-08-01 15:05
	-> function : Main function program entry
****************************************************************/
#include "protocol.h"

int main(int argc, char *argv[])
{
	int ret;

	pthread_t spi_thread; 
	pthread_t read_thread;	
	
	while(1)
	{
		usleep(1000);
		pthread_mutex_init (&mutex, NULL);

		//打开UART通信句柄
		get_id();
		//login登录函数
		while(1)
		{
			usleep(1000);
			ret = login();
			if(ret == 1)
			{
				printf("login success\n");
				break;
			}
			if(ret == 0)
				continue;
		}
		printf("******start**pthread_read**pthread_write******\n");

		//写线程
		if(pthread_create( &spi_thread, NULL, pthread_spi, NULL) < 0)  
		{  
			perror("fail to pthread_create");  
			//exit(-1);  
		}	

		//读线程
		if(pthread_create( &read_thread, NULL, pthread_read, NULL) < 0)  
		{  
			perror("fail to pthread_create"); 
			//exit(-1);  
		}
		
		pthread_join(spi_thread, NULL);
		printf("pthread_join\n");
		pthread_join(read_thread, NULL);
		printf("pthread_join\n");
		pthread_mutex_destroy (&mutex);
		printf("clent quit!\n");
		
		close(fd);  
		printf("Close %s\n", WIFI_DEVICE);  
	}
	
	return 0;
}
