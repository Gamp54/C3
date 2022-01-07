#include "s21_cat.h"
static int bflag, eflag, nflag, sflag, tflag, vflag;

static void usage() { printf("Usage: s21_cat [OPTION] [FILE]..."); }

static int scanfiles(const char **argv, FILE **files) {
  int i = 0, a = 0;
  while ((argv[a]) != NULL || a == 0) {
    if (argv[a] == NULL) {
      usage();
      break;
    } else if ((files[i] = fopen(argv[a], "r")) == NULL) {
        printf("%s: No such file or directory\n", argv[a]);
        usage();
        i--;
      }
    ++i;
    a++;
  }
  return i;
}

static void direct_cat(FILE **files, int f) {
  char *line = NULL;
  size_t len = 0;
  for (int i = 0; i < f; i++) {
    ssize_t read;
    while ((read = getline(&line, &len, files[i])) != -1)
      write(1, line, strlen(line));
  }
  if (line) free(line);
}

static void cat_cooking(FILE **files, int f) {
  int ch, cut, line = 0, prev;
  for (int i = 0; i < f; i++)
    for (prev = '\n'; (ch = getc(files[i])) != EOF; prev = ch) {
      if (prev == '\n') {
        if (sflag) {
          if (ch == '\n') {
            if (cut) continue;
            cut = 1;
            } else {
              cut = 0;
            }
        }
        if (nflag && (!bflag || ch != '\n')) printf("%6d\t", ++line);
      }
      if (ch == '\n') {
        if (eflag && putchar('$') == EOF) break;
      } else if (ch == '\t') {
        if (tflag) {
          if (putchar('^') == EOF || putchar('I') == EOF) break;
          continue;
        }
      }
      if (putchar(ch) == EOF) break;
    }
}

int main(int argc, char *argv[]) {
  int c;
  while ((c = getopt_long(argc, argv, "benstuvAET", long_options, NULL)) != -1)
    switch (c) {
      case 'b':
        bflag = nflag = 1;
        break;
      case 'e':
        eflag = vflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case 's':
        sflag = 1;
        break;
      case 't':
        tflag = vflag = 1;
        break;
      case 'u':
        break;
      case 'v':
        vflag = 1;
        break;
      case 'A':
        eflag = vflag = tflag = 1;
        break;
      case 'E':
        eflag = 1;
        break;
      case 'T':
        tflag = 1;
        break;
      default:
        break;
    }
  argv += optind;
  if (argc < 2) usage();
  FILE **files = calloc(argc, sizeof(FILE));
  int i = scanfiles((const char**)argv, files);
  if (bflag || eflag || nflag || sflag || tflag || vflag)
    cat_cooking(files, i);
  else
    direct_cat(files, i);
  free(files);
  return 0;
}
