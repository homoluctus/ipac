#ifndef __IPV4_H
#define __IPV4_H

void usage(void);
static void str2dec(char argv[]);
static void dec2bin(char bin[][9], int dec[]);
static unsigned int calculatePrefix(char argv[]);
static void calculateSubnetMask(unsigned int prefix);
static void calculateNetworkAddress(unsigned int prefix);
static void calculateBroadcastAddress(unsigned int prefix);
static void displayInDecimalNotaion(int addr[]);
static void displayInBinaryNotaion(char addr[][9]);
void displayAddress(char argv[], const short int address_number);

#endif
