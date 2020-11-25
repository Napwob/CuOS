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
#include <ctime>

using namespace std;

#include "cookie.h"

extern "C" int cookie()
{	
              	ofstream outf;

		outf.open("Cookie", ios::app);
		time_t rawtime;
  struct tm * timeinfo;

  time( &rawtime );                         
  timeinfo = localtime ( &rawtime );   

		outf<<"Ilya: "<<asctime (timeinfo)<<endl;
		return 0;
}
