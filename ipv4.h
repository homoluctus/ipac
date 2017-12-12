#ifndef __IPV4_H
#define __IPV4_H

void usage(void);
static void str2dec(char argv[]);
static void dec2bin(char bin[][9], int dec[]);
static int prefix(char argv[]);
static void net(int prefix);
static void broad(int prefix);
static void print_dec(int addr[]);
static void print_bin(char addr[][9]);
void host_addr(char argv[]);
void subnet_mask(char argv[]);
void net_addr(char argv[]);
void broad_addr(char argv[]);

#endif
