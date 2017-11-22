server : main.o get_id.o login.o pthread_spi.o pthread_read.o
	arm-linux-gcc main.o get_id.o login.o pthread_spi.o pthread_read.o -pthread -lm  -o wifis

main.o : main.c
	arm-linux-gcc main.c -c -o main.o

login.o : login.c
	arm-linux-gcc login.c -c -o login.o

get_id.o : get_id.c
	arm-linux-gcc get_id.c -c -o get_id.o
	
pthread_read.o : pthread_read.c
	arm-linux-gcc pthread_read.c -c -o pthread_read.o
	
pthread_spi.o : pthread_spi.c
	arm-linux-gcc pthread_spi.c -c -o pthread_spi.o

clean :
	@rm -rf ./*.o
