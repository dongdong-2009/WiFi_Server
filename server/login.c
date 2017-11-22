#include "protocol.h"

int login()
{
	int i,ret;
	char msgbuf[MSGBUF];
	
	char buf[SIZEBUF];
	char type;
	char name[DATALEN] = {0};
	char passwd[DATALEN] = {0};

	int ufd,pfd;	
	char namebuf[DATALEN] = {0};
	char passwdbuf[DATALEN] = {0};
	while(1)
	{
		// printf("fd = %d\n",fd);
		// printf("**********login***************\n");
		memset( buf, 0, SIZEBUF);
		ret = read( fd, &buf, SIZEBUF);
		if(ret == 0)
			continue; 
		
		type = buf[0];
		for( i = 0; i < DATALEN; i++)
		{
			name[i] = buf[1+i];
		}
		for( i = 0; i < DATALEN; i++)
		{
			passwd[i] = buf[9+i];
		}
		printf("cmd_type: %c, name :%s, passwd:%s\n", type, name, passwd);

		memset( namebuf, 0, DATALEN);
		memset( passwdbuf, 0, DATALEN);
		if((ufd=open( "name.txt", O_RDWR, 0666)) < 0)
		{
			perror("fail to open name.txt\n");
			exit(0);
		}
		if((pfd=open( "passwd.txt", O_RDWR, 0666)) < 0)
		{
			perror("fail to open passwd.txt\n");
			exit(0);
		}
		if((ret = read(ufd,namebuf,10)) > 0)
		{
			printf("name.txt : %s\n",namebuf);
		}
		if((ret = read(pfd,passwdbuf,10)) > 0)
		{
			printf("passwd.txt : %s\n",passwdbuf);
		}
		close(ufd);
		close(pfd);
		
		namebuf[strlen(namebuf) - 1] = '\0';
		/*
		namebuf[strlen(namebuf)] = '\0';
		passwdbuf[strlen(passwdbuf)] = '\0';
		name[strlen(name)] = '\0';
		passwd[strlen(passwd)] = '\0';
		*/
		//printf("namebuf=%d,name=%d,passwdbuf=%d,passwd=%d\n", strlen(namebuf), strlen(name), strlen(passwdbuf), strlen(passwd));
		if((strcmp(namebuf, name) == 0) && (strcmp(passwdbuf, passwd) == 0) && (type == '1'))
		{
			memset( msgbuf, 0, MSGBUF);
			strcpy( msgbuf, "login success!");
			write(fd, msgbuf, MSGBUF);
			return 1;
		}
		else{
			memset( msgbuf, 0, MSGBUF);
			strcpy( msgbuf, "login fail!");
			write(fd, msgbuf, MSGBUF);
			printf("login fail,try again\n");
			return 0;
		}
	}

}
