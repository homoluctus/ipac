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

static int calculatePrefix(char argv[])
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

static void calculateSubnetMask(int prefix)
{
  /* calculate subnet mask */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = 0; i < OCTET; i++) {
    dec_mask[i] = (octet > i) ? 0xff : (octet < i) ? 0x00 : 0xff & ~(0xff >> bit);
  }
}

static void calculateNetworkAddress(int prefix)
{
  /* calculate network address */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = octet; i < OCTET; i++) {
    dec_addr[i] &= (octet < i) ? 0x00 : ~(0xff >> bit);
  }
}

static void calculateBroadcastAddress(int prefix)
{
  /* calculate broadcast address */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = octet; i < OCTET; i++) {
    dec_addr[i] |= (octet < i) ? 0xff : 0xff >> bit;
  }
}

static void displayInDecimalNotaion(int addr[])
{
  int i;

  for (i = 0; i < OCTET; i++) {
    printf("%8d%s", addr[i], (i < 3) ? "." : " |\n");
  }
}

static void displayInBinaryNotaion(char addr[][9])
{
  int i;

  for (i = 0; i < OCTET; i++) {
    printf("%s%s", addr[i], (i < 3) ? "." : " |\n");
  }
}

void displayAddress(char argv[], const short int address_number)
{
  char *address_name;

  switch (address_number) {
    case 0:
      address_name = "Host";
      str2dec(argv);
      dec2bin(bin_addr, dec_addr);
      puts(" ---------------------------------------------------");
      break;
    case 1:
      address_name = "Subnet Mask";
      calculateSubnetMask(calculatePrefix(argv));
      dec2bin(bin_mask, dec_mask);
      break;
    case 2:
      address_name = "Network";
      calculateNetworkAddress(calculatePrefix(argv));
      dec2bin(bin_addr, dec_addr);
      break;
    case 3:
      address_name = "Broadcast";
      calculateBroadcastAddress(calculatePrefix(argv));
      dec2bin(bin_addr, dec_addr);
      break;
    default:
      puts("[!] Unknown Error");
      exit(EXIT_FAILURE);
  }

  printf("| %-11s | ", address_name);
  if (address_number == 1) {
    displayInDecimalNotaion(dec_mask);
  } else {
    displayInDecimalNotaion(dec_addr);
  }
  printf("|%*s| ", 13, " ");
  if (address_number == 1) {
    displayInBinaryNotaion(bin_mask);
  } else {
    displayInBinaryNotaion(bin_addr);
  }
  puts(" ---------------------------------------------------");
}
