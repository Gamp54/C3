#include "s21_grep.h"

static int cflag, eflag, fflag, hflag = -1, iflag = 0, lflag = 0, nflag, oflag, sflag, vflag;
static char *cur_file;
static int patterns = 0;

static void usage() {
  printf("Usage: s21_grep [options] template [file_name]");
}

static int get_patterns(char *regex, char **pattern) {
  // printf("in get_patterns");
  if (patterns > 0) strncat(*pattern, "|", 1);
  // printf("in get_pattern2: %s.", pattern);
  strncat(*pattern, regex, strlen(regex));
  // printf("in get_pattern3: %s.", pattern);
  patterns++;
  return patterns;
}

static void file_patterns(char *filename, char **pattern) {
  // printf("in file_patterns");
  char *line = NULL;
  size_t len = 0;
  FILE *file;
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("grep1: %s: No such file or directory\n", filename);
  } else {
      int pat = 0;
      ssize_t read;
      while ((read = getline(&line, &len, file)) != -1) {
        // printf("in file_pattern2: %s.", pattern);
        if (pat > 0) strncat(*pattern, "|", 1);
        strncat(*pattern, line, strlen(line) - 1);
        // printf("in file_pattern2: %s.", pattern);
        pat++;
      }
    }
  fclose(file);
  if (line) free(line);
}

static void pcre_grep(FILE *file, char **pattern) {
  int n = 0, nf = 0;
  ssize_t read;
  char *line = NULL;
  size_t len = 0;
  pcre *re;
  const char *error;
  int erroffset;
  int ovector[30];
  re = pcre_compile(*pattern, iflag, &error, &erroffset, NULL);
  if (re == NULL)
    printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
  while ((read = getline(&line, &len, file)) != -1) {
    int count = 0;
    nf++;
    count = pcre_exec(re, NULL, line, strlen(line), 0, 0, ovector, 30);
    if (vflag) {
      if (count == -1) {
        if (hflag == 0) printf("%s:", cur_file);
        if (nflag) printf("%d:", nf);
        printf("%s", line);
      }
    } else {
      if (count > -1) n += count;
      if (!cflag && !lflag && !vflag) {
        for (int c = 0; c < count; c++) {
          if (hflag == 0) printf("%s:", cur_file);
          if (nflag) printf("%d:", nf);
          if (!oflag) {
            printf("%s", line);
          } else {
              for (int i = ovector[c]; i < ovector[c + 1]; i++)
                printf("%c", line[i]);
              printf("\n");
            }
          }
      }
    }
  }
  if (cflag) {
    if (hflag == 0)
      printf("%s:%d\n", cur_file, n);
    else
      printf("%d\n", n);
  }
  if (lflag)
    if (n > 0) printf("%s\n", cur_file);
  if (re) pcre_free(re);
  if (line) free(line);
}

int main(int argc, char *argv[]) {
  char *pattern;
  int c;
  extern char *optarg;
  extern int optind, optopt, opterr;
  pattern = calloc(256, sizeof(char));
  while ((c = getopt(argc, argv, "cefhilnosv")) != -1) switch (c) {
      case 'c':
        cflag = 1;
        break;
      case 'e':
        eflag = 1;
        patterns = get_patterns(argv[optind], &pattern);
        argv++;
        break;
      case 'f':
        fflag = 1;
        file_patterns(argv[optind], &pattern);
        patterns = 1;
        argv++;
        break;
      case 'h':
        hflag = 1;
        break;
      case 'i':
        iflag = 1;
        break;
      case 'l':
        lflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case 'o':
        oflag = 1;
        break;
      case 's':
        sflag = 1;
        break;
      case 'v':
        vflag = 1;
        break;
      default:
        break;
    }
  argv += optind;
  if (argc < 3) {
    usage();
    free(pattern);
    return 1;
  }
  if (!eflag && !fflag) {
    patterns = 1;
    strcpy(pattern, *argv);
    argv++;
  }
  if ((argc - 1) - (optind + patterns) > 0 && hflag != 1) hflag = 0;
  int i;
  for (i = 0; i < argc - optind - patterns; i++) {
    FILE *file;
    cur_file = argv[i];
    file = fopen(cur_file, "r");
    if (file == NULL) {
      if (!sflag) printf("grep: %s: No such file or directory\n", cur_file);
    } else {
      pcre_grep(file, &pattern);
      fclose(file);
    }
  }
  free(pattern);
  return 0;
}
