#include <stdio.h>  
#include <stdlib.h>
#include "../network/ServiceHTTP.h"
  
int main()  
{  
    daemon(0,0);
    APSUTIL::ServiceHTTP server;
    server.Run();
} 