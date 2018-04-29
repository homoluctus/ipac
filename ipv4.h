#ifndef __IPV4_H
#define __IPV4_H

void usage(void);
static void str2dec(char argv[]);
static void dec2bin(char bin[][9], int dec[]);
static int calculatePrefix(char argv[]);
static void calculateSubnetMask(int prefix);
static void calculateNetworkAddress(int prefix);
static void calculateBroadcastAddress(int prefix);
static void displayInDecimalNotaion(int addr[]);
static void displayInBinaryNotaion(char addr[][9]);
void displayHostAddress(char argv[]);
void displaySubnetMask(char argv[]);
void displayNetworkAddress(char argv[]);
void displayBroadcastAddress(char argv[]);

#endif
