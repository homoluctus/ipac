#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ipv4.h"

#define OCTET 4
#define IDX 3

static int dec_addr[OCTET];
static char bin_addr[OCTET][9];

void usage(void)
{
  puts("\n------------------ IPv4 Calculator ------------------");
  puts("FORMAT: ./main [IPv4 address] [prefix]");
  puts("\n# IPv4 address format is xxx.xxx.xxx.xxx (delimiter \".\")\n");
  puts("# If you do not input prefix,");
  puts("# this outputs the result converted IPv4 address from decimal to binary\n");
}

static void str2dec(char *argv[])
{
  int i;
  int idx = 0;
  int count = OCTET - 1;
  int len = strlen(argv[1]);

  for (i = len - 1; i >= 0; i--) {
    if (argv[1][i] == '.') {
      idx = 0;
      count--;
      continue;
    }

    if ((idx > 2) || (!isdigit(argv[1][i]))) {
      puts("Error!! Invalid input");
      exit(EXIT_FAILURE);
    }

    dec_addr[count] += (int)(argv[1][i] - '0') * pow(10, (idx++));
  }
}

static void dec2bin(void)
{
  int i, j;

  for (i = 0; i < OCTET; i++) {
    for (j = 7; j >= 0; j--) {
      bin_addr[i][7-j] = ((dec_addr[i] >> j) & 1) ? '1' : '0';
    }
  }
}

static void print_dec(int addr[])
{
  int i;

  for (i = 0; i < OCTET; i++) {
    printf("%8d%s", addr[i], (i < 3) ? "." : "\n");
  }
}

static void print_bin(char addr[][9])
{
  int i;

  for (i = 0; i < OCTET; i++) {
    printf("%s%s", addr[i], (i < 3) ? "." : "\n");
  }
}

void ip_addr(char *argv[])
{
  str2dec(argv);
  dec2bin();

  print_dec(dec_addr);
  print_bin(bin_addr);
}
