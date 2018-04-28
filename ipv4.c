#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ipv4.h"

#define OCTET 4

static int dec_addr[OCTET];
static char bin_addr[OCTET][9];

static int dec_mask[OCTET];
static char bin_mask[OCTET][9];

void usage(void)
{
  puts("\n------------------ IPv4 Calculator ------------------");
  puts("FORMAT: ./ipac [IPv4 address] [prefix]");
  puts("\n# IPv4 address format is xxx.xxx.xxx.xxx (delimiter \".\")\n");
  puts("# If you do not input the prefix,");
  puts("# this outputs only the result converted IPv4 address from decimal to binary");
}

static void str2dec(char addr[])
{
  /* convert string to decimal */
  int i;
  int count = 0;
  int octet = OCTET - 1;
  int len = strlen(addr);

  for (i = len - 1; i >= 0; i--) {
    if (addr[i] == '.') {
      count = 0;
      octet--;
      continue;
    }

    if ((count > 2) ||(!isdigit(addr[i]))) {
      puts("Format Error !! Invalid input");
      usage();
      exit(EXIT_FAILURE);
    }

    dec_addr[octet] += (int)(addr[i] - 0x30) * pow(10, (count++));
  }

  if (octet > 0) {
    puts("Format Error !! Invalid input");
    usage();
    exit(EXIT_FAILURE);
  }
}

static void dec2bin(char bin[][9], int dec[])
{
  /* convert decimal to binary */
  int i, j;

  for (i = 0; i < OCTET; i++) {
    for (j = 7; j >= 0; j--) {
      bin[i][7-j] = ((dec[i] >> j) & 1) ? '1' : '0';
    }
  }
}

static int prefix(char argv[])
{
  /* calculate the prefix */
  int i;
  int p = 0;
  int len = strlen(argv);

  for (i = 0; i < len; i++) {
    p += (int)(argv[i] - 0x30) * pow(10, len-i-1);
  }
  return p;
}

static void mask(int prefix)
{
  /* calculate subnet mask */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = 0; i < OCTET; i++) {
    dec_mask[i] = (octet > i) ? 0xff : (octet < i) ? 0x00 : 0xff & ~(0xff >> bit);
  }
}

static void net(int prefix)
{
  /* calculate network address */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = octet; i < OCTET; i++) {
    dec_addr[i] &= (octet < i) ? 0x00 : ~(0xff >> bit);
  }
}

static void broad(int prefix)
{
  /* calculate broadcast address */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = octet; i < OCTET; i++) {
    dec_addr[i] |= (octet < i) ? 0xff : 0xff >> bit;
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

void host_addr(char argv[])
{
  str2dec(argv);
  dec2bin(bin_addr, dec_addr);

  puts("\n++++++++++++Host Address+++++++++++");
  print_dec(dec_addr);
  print_bin(bin_addr);
}

void subnet_mask(char argv[])
{
  mask(prefix(argv));
  dec2bin(bin_mask, dec_mask);

  puts("\n++++++++++++Subnet Mask++++++++++++");
  print_dec(dec_mask);
  print_bin(bin_mask);
}

void net_addr(char argv[])
{
  net(prefix(argv));
  dec2bin(bin_addr, dec_addr);

  puts("\n++++++++++Network Address++++++++++");
  print_dec(dec_addr);
  print_bin(bin_addr);
}

void broad_addr(char argv[])
{
  broad(prefix(argv));
  dec2bin(bin_addr, dec_addr);

  puts("\n+++++++++Broadcast Address+++++++++");
  print_dec(dec_addr);
  print_bin(bin_addr);
}
