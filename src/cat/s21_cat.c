#include "s21_cat.h"

void parse_flags(int argc, char* argv[], Flags* flags) {
  int opt;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "beEtTnvs", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flags->b = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->E = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->T = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        fprintf(stderr, "usage: s21_cat [-benstuv] [file ...]\n");
        exit(1);
    }
  }
  if (flags->b) flags->n = 0;
}

void process_file(FILE* file, Flags flags) {
  int ch;
  int prev_ch = '\n';
  int line_count = 1;
  int squeeze = 0;

  while ((ch = fgetc(file)) != EOF) {
    if (flags.s && prev_ch == '\n' && ch == '\n') {
      if (squeeze) continue;
      squeeze = 1;
    } else {
      squeeze = 0;
    }

    if (prev_ch == '\n') {
      if (flags.b && ch != '\n') {
        printf("%6d\t", line_count++);
      } else if (flags.n && !flags.b) {
        printf("%6d\t", line_count++);
      }
    }
    if (ch == '\n' && (flags.e || flags.E)) {
      putchar('$');
    }
    if ((flags.t || flags.T) && ch == '\t') {
      printf("^I");
      prev_ch = ch;
      continue;
    }
    if (flags.v) {
      if (ch < 32 && ch != '\n' && ch != '\t') {
        printf("^%c", ch + 64);
      } else if (ch == 127) {
        printf("^?");
      } else if (ch > 127 && ch < 160) {
        printf("M-^%c", ch - 64);
      } else {
        putchar(ch);
      }
    } else {
      putchar(ch);
    }
    prev_ch = ch;
  }
}

int main(int argc, char* argv[]) {
  Flags flags = {0};
  parse_flags(argc, argv, &flags);

  if (optind == argc) {
    process_file(stdin, flags);
  } else {
    for (int i = optind; i < argc; i++) {
      FILE* file = fopen(argv[i], "r");
      if (!file) {
        perror(argv[i]);
        continue;
      }
      process_file(file, flags);
      fclose(file);
    }
  }
  return 0;
}