#include <stdio.h>
#include "ipv4.h"

int main(int argc, char *argv[])
{
  switch (argc) {
    case 1 : usage(); break;
    case 2 : ip_addr(argv);
             break;
    //case 3 : ipv4(argv[2]);
  }
  return 0;
}
