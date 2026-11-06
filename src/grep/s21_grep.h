#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;  // bonus
  int s;  // bonus
  int f;  // bonus
  int o;  // bonus
  char pattern[4096];
  int pattern_count;
} Flags;

void add_pattern(Flags* flags, const char* pat);
void add_pattern_from_file(Flags* flags, const char* filename);
void parse_args(int argc, char** argv, Flags* flags);
void print_matches(const char* filename, Flags* flags, regex_t* re,
                   const char* line, int line_num, int multiple_files);
void grep_file(const char* filename, Flags* flags, regex_t* re,
               int multiple_files);

#endif