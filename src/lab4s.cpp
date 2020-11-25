#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <dlfcn.h>
 #include <cmath>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <fcntl.h> 
#include <pwd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>   
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <csignal>
#include <signal.h>

using namespace std;

int slt(char *arv1, char *arv2, char *arv3) {
    const char *path = "lab2";//поменять на другую папку
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        execl(path, path, arv1,arv2,arv3, NULL);
        _exit (EXIT_FAILURE);
    } else if (pid < 0)
        status = -1;
    else if (waitpid (pid, &status, 0) != pid)
        status = -1;
    return status;
}

int sp(char *d ,char *path) {
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	if(strcmp(d,"-d")==0) daemon (1, 0);
        execl(path, path, NULL);
        while (1) {
            if (waitpid(pid, &status, 0) == pid)
                _exit (EXIT_FAILURE);
        }
    } else if (pid < 0)
        status = -1;
    else if (waitpid(pid, &status, 0) != pid)
        status = -1;

    return status;
}





int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();
    daemon (1, 0);
      int s = socket(AF_INET, SOCK_STREAM, 0);
      if(s < 0)
      {
              perror("Error calling socket");
              return 0;
      }

      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(18666);
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      if( bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0 )
      {
              return 0;
      }

      if( listen(s, 5) )
      {
              perror("Error calling listen");
              return 0;
      }

      int s1 = accept(s, NULL, NULL);
      if( s1 < 0 )
      {
              perror("Error calling accept");
              return 0;
      }

      char buffer[31];
      char buffer1[31];
      char buffer2[31];
      char buffer3[31];
      int counter = 0;
      for(;;)
      {
              memset(buffer, 0, sizeof(char)*31);
              int rc = recv(s1, buffer, 30, 0);
              if (strcmp(buffer,"-s")==0)
              {
              	recv(s1, buffer1, 30, 0);
              	recv(s1, buffer2, 30, 0);
              }
              if (strcmp(buffer,"-o")==0)
              {
              	recv(s1, buffer1, 30, 0);
              	recv(s1, buffer2, 30, 0);
              	recv(s1, buffer3, 30, 0);
              }
              if( rc < 0 )
              {
                      if( errno == EINTR )
                              continue;
                      perror("Can't receive data.");
                      return 0;
              }
              if( rc == 0 )
                      break;
              printf("%s\n", buffer);
              
              
              
              if (strcmp(buffer,"-l")==0) 
              {
              		void *handle = dlopen("./libcookie.so",RTLD_LAZY);
              		if (!handle) 
             		 {
              			fputs(dlerror(), stderr);
	     			 //return 5;
	      		}
			int (*fun)();
			fun = (int (*)())dlsym(handle,"cookie");
			int x = (*fun)();
			dlclose(handle);					
              }
              
              if (strcmp(buffer,"-d")==0) 
              {
              		  void *handle = dlopen("./libclearcookie.so",RTLD_LAZY);
               		 if (!handle) 
                	{
				fputs(dlerror(), stderr);
				//return 5;
			}
			int (*fun)();
			fun = (int (*)())dlsym(handle,"clearcookie");
			int x = (*fun)();
			dlclose(handle);					
              }
              
              if (strcmp(buffer,"-o")==0) slt(buffer1, buffer2, buffer3);
             
              if ((strcmp(buffer,"-s")==0) && ((strcmp(buffer1,"-d")==0) || (strcmp(buffer1,"-n")==0))) sp(buffer1, buffer2);//-d для демонофикации -nd для без демонофикации
	
	      if (strcmp(buffer,"-h")==0) printf("Client want to see our names...");	
    
  	      if (strcmp(buffer,"--help")==0) printf("Client want to see our names...");	
      }
      char response[] = "1";
      if( sendto( s1, response, sizeof(response), 0, (struct sockaddr *)&addr, sizeof(addr) ) < 0 )
              perror("Error sending response");
      return 0;
}










