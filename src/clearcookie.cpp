
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

#include "clearcookie.h"

extern "C" int clearcookie()
{	
              	ofstream outf;

		outf.open("Cookie");
		outf.close();
	return 0;
}
