 #include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <stdio.h>
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

void spravka()
{
cout<<"Авторы: Русманов Владислав ИВ-822, Крюков Илья ИВ-822, Сысоева Анастасия ИВ-822"<<endl;    
cout<<"Краткое описание проекта:"<<endl;
cout<<"Данная программа позволяет выполнять простые действия по работе с процессами Linux"<<endl;
cout<<"    Чтобы получить функционал по работе с файловой системой, нужно запустить программу с ключом -l"<<endl;
cout<<"    Чтобы запустить любую операцию сначала необходимо указать ключ данной операции, а затем режим фона "<<endl;
cout<<"    -d Запускает операцию в фоновом режиме" <<endl;
cout<<"    -n Запускает операцию в не фоновом режиме" <<endl;
cout<<"    -s Порождает новый процесс" <<endl;
cout<<"    -t Режим получения и обработки сигналов"<<endl;
cout<<"Все доступные аргументы:"<<endl;
cout<<"    -l"<<endl;
cout<<"    -d"<<endl;
cout<<"    -n"<<endl;
cout<<"    -s"<<endl;
cout<<"    -t"<<endl;
cout<<"Примеры запуска:"<<endl;
cout<<"    ./lab3 —l -h"<<endl;
cout<<"    ./lab3 -s -n proc"<<endl;
cout<<"    ./lab3 -s -d proc"<<endl;
cout<<"    ./lab3 -t"<<endl;
}





int main(int argc, char * argv[])
{
	
	if (strcmp(argv[1],"-h")==0) spravka();
    
  	if (strcmp(argv[1],"--help")==0) spravka();
  	
  	
  	
      int s = socket( AF_INET, SOCK_STREAM, 0 );
      if(s < 0)
      {
              perror( "Error calling socket" );
              return 0;
      }


      struct sockaddr_in peer;
      peer.sin_family = AF_INET;
      peer.sin_port = htons( 18666 );
      peer.sin_addr.s_addr = inet_addr( "127.0.0.1" );
      int result = connect( s, ( struct sockaddr * )&peer, sizeof( peer ) );
      if( result )
      {
              perror( "Error calling connect" );
              return 0;
      }
	
	
      result = send( s, argv[1], 2, 0);
      
      if (strcmp(argv[1],"-s")==0)
      {
      	send( s, argv[2], 29, 0);
        send( s, argv[3], 29, 0);
      }
      
      if (strcmp(argv[1],"-o")==0)
      {
      	send( s, argv[2], 29, 0);
        send( s, argv[3], 29, 0);
      	send( s, argv[4], 29, 0);
      }
      if( result <= 0 )
      {
              perror( "Error calling send" );
              return 0;
      }

      if( shutdown(s, 1) < 0)
      {
              perror("Error calling shutdown");
              return 0;
      }

    
      fd_set readmask;
      fd_set allreads;
      FD_ZERO( &allreads );
      FD_SET( 0, &allreads );
      FD_SET( s, &allreads );
      for(;;)
      {
              readmask = allreads;
              if( select(s + 1, &readmask, NULL, NULL, NULL ) <= 0 )
              {
                      perror("Error calling select");
                      return 0;
              }
              if( FD_ISSET( s, &readmask ) )
              {
                      char buffer[20];
                      memset(buffer, 0, 20*sizeof(char));
                      int result = recv( s, buffer, sizeof(buffer) - 1, 0 );
                      if( result < 0 )
                      {
                              perror("Error calling recv");
                              return 0;
                      }
                      if( result == 0 )
                      {
                              printf("Server disconnected\n");
                              return 0;
                      }
                      if(strncmp(buffer, "1", 1) == 0)
                              printf("Got answer. Success.\n");
                      else
                              perror("Wrong answer!");
              }
              if( FD_ISSET( 0, &readmask ) )
              {
                      printf( "No server response" );
                      return 0;
              }
      }
      return 0;
}
