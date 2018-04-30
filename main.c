#include <stdio.h>
#include "ipv4.h"

int main(int argc, char *argv[])
{
  switch (argc) {
    case 2: displayAddress(argv[1], 0);
            break;

    case 3: displayAddress(argv[1], 0);
            displayAddress(argv[2], 1);
            displayAddress(argv[2], 2);
            displayAddress(argv[2], 3);
            break;

    default: usage(); break;
  }
  putchar('\n');
  return 0;
}
