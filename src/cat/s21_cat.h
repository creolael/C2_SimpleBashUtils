#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
} Flags;

void parse_flags(int argc, char* argv[], Flags* flags);
void process_file(FILE* file, Flags flags);

#endif
