#ifndef __IPV4_H
#define __IPV4_H

void usage(void);
static void str2dec(char *argv[]);
static void dec2bin(void);
static void print_dec(int addr[]);
static void print_bin(char addr[][9]);
void ip_addr(char *argv[]);

#endif
