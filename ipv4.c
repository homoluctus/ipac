#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipv4.h"

#define OCTET 4

static int dec_addr[OCTET];
static char bin_addr[OCTET][9];

static int dec_mask[OCTET];
static char bin_mask[OCTET][9];

void usage(void)
{
  puts("\n---------------- IPv4 Address Calculator ----------------");
  puts("FORMAT: ./ipac ADDRESS [PREFIX]");
  puts("\n# ADDRESS format is xxx.xxx.xxx.xxx (delimiter \".\")\n");
  puts("# If you do not input the PREFIX,");
  puts("# this outputs only the result converted ADDRESS from decimal to binary");
}

/* convert string to number in decimal notation */
static void str2dec(char argv[])
{
  int i;
  int len = strlen(argv);
  int digit = 0, octet = 0;
  char temp[4];

  for (i = 0; i <= len; i++) {
    if ((argv[i] == '.') || (i == len)) {
      dec_addr[octet] = atoi(temp);
      if ((dec_addr[octet] < 0) || (dec_addr[octet] > 254) || (octet > 3)) {
        puts("[!] Invalid address");
        exit(EXIT_FAILURE);
      }
      octet++;
      digit = 0;
      memset(temp, '\0', 4);
    } else {
      if (digit > 2) {
        puts("[!] Invalid address");
        exit(EXIT_FAILURE);
      }
      temp[digit++] = argv[i];
    }
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

/* calculate the prefix */
static unsigned int calculatePrefix(char argv[])
{
  unsigned int p = (unsigned int)atoi(argv);

  if ((p < 1) || (p > 32)) {
    puts("[!] Please enter 1 <= PREFIX <= 32");
    exit(EXIT_FAILURE);
  }

  return p;
}

static void calculateSubnetMask(unsigned int prefix)
{
  /* calculate subnet mask */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = 0; i < OCTET; i++) {
    dec_mask[i] = (octet > i) ? 0xff : (octet < i) ? 0x00 : 0xff & ~(0xff >> bit);
  }
}

static void calculateNetworkAddress(unsigned int prefix)
{
  /* calculate network address */
  int i;
  int octet = prefix / 8;
  int bit = prefix % 8;

  for (i = octet; i < OCTET; i++) {
    dec_addr[i] &= (octet < i) ? 0x00 : ~(0xff >> bit);
  }
}

static void calculateBroadcastAddress(unsigned int prefix)
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
