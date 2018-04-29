#include <stdio.h>
#include "ipv4.h"

int main(int argc, char *argv[])
{
  switch (argc) {
    case 2: displayHostAddress(argv[1]);
            break;

    case 3: displayHostAddress(argv[1]);
            displaySubnetMask(argv[2]);
            displayNetworkAddress(argv[2]);
            displayBroadcastAddress(argv[2]);
            break;

    default: usage(); break;
  }
  putchar('\n');
  return 0;
}
