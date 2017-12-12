#include <stdio.h>
#include "ipv4.h"

int main(int argc, char *argv[])
{
  switch (argc) {
    case 2: host_addr(argv[1]);
            break;

    case 3: host_addr(argv[1]);
            subnet_mask(argv[2]);
            net_addr(argv[2]);
            broad_addr(argv[2]);
            break;

    default: usage(); break;
  }
  putchar('\n');
  return 0;
}
