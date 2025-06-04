#include <ctype.h>
#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

struct cat_flags_s {
  int number_nonblank;   // -b / --number-nonblank
  int show_ends;         // -E / -e
  int number;            // -n / --number
  int squeeze_blank;     // -s / --squeeze-blank
  int show_tabs;         // -T / -t
  int show_nonprinting;  // -v
};
typedef struct cat_flags_s cat_flags_t;

struct file_context_s {
  int line_number;
  int prev_char;
  int blank_lines;
  int new_line;
};
typedef struct file_context_s file_context_t;

void resolve_flag_conflicts(cat_flags_t *flags) {
  if (flags->number_nonblank) flags->number = 0;
}

int parse_arg(int argc, char *argv[], cat_flags_t *flags) {
  int flag = 1;
  opterr = 0;
  const struct option longopts[] = {{"number-nonblank", 0, NULL, 'b'},
                                    {"number", 0, NULL, 'n'},
                                    {"squeeze-blank", 0, NULL, 's'}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bveEnstT", longopts, NULL)) != -1 &&
         flag) {
    switch (opt) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'e':
        flags->show_ends = 1;
        flags->show_nonprinting = 1;
        break;
      case 'E':
        flags->show_ends = 1;
        break;
      case 'n':
        flags->number = 1;
        break;
      case 's':
        flags->squeeze_blank = 1;
        break;
      case 't':
        flags->show_tabs = 1;
        flags->show_nonprinting = 1;
        break;
      case 'T':
        flags->show_tabs = 1;
        break;
      case 'v':
        flags->show_nonprinting = 1;
        break;
      default:
        flag = 0;
        break;
    }
  }
  resolve_flag_conflicts(flags);
  return flag;
}

void print_nonprinting(int ch) {
  if (ch == 127)
    printf("^?");
  else if (ch < 32)
    printf("^%c", ch + 64);
  else if (ch >= 128) {
    printf("M-");
    print_nonprinting(ch & 0x7F);
  } else
    putchar(ch);
}

void print_line_number(file_context_t *ctx) {
  printf("%6d\t", ctx->line_number++);
}

void process_stream(FILE *file, cat_flags_t flags, file_context_t *ctx) {
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (flags.squeeze_blank) {
      if (ctx->prev_char == '\n' && ch == '\n') {
        ctx->blank_lines++;
        if (ctx->blank_lines > 1) {
          continue;
        }
      } else {
        ctx->blank_lines = 0;
      }
    }
    if (ctx->new_line &&
        (flags.number || (flags.number_nonblank && ch != '\n'))) {
      print_line_number(ctx);
      ctx->new_line = 0;
    }
    if (ch == '\t' && flags.show_tabs) {
      printf("^I");
    } else if ((ch < 32 || ch >= 127) && ch != '\n' && ch != '\t' &&
               flags.show_nonprinting) {
      print_nonprinting(ch);
    } else {
      if (ch == '\n' && flags.show_ends) {
        putchar('$');
      }
      putchar(ch);
    }
    ctx->prev_char = ch;
    if (ch == '\n') ctx->new_line = 1;
  }
}

int process_file(char *path, cat_flags_t flags, file_context_t *ctx) {
  int flag = 1;
  FILE *file = NULL;
  file = fopen(path, "r");
  if (file) {
    process_stream(file, flags, ctx);
    fclose(file);
  } else
    flag = 0;
  return flag;
}

void init_file_context(file_context_t *ctx) {
  ctx->line_number = 1;
  ctx->new_line = 1;
  ctx->prev_char = '\n';
  ctx->blank_lines = 0;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "ru_RU.UTF-8");
  cat_flags_t flags = {0};
  int flag = parse_arg(argc, argv, &flags);
  if (!flag) fprintf(stderr, "Unknown option\n");
  file_context_t ctx;
  init_file_context(&ctx);
  for (int i = 1; i < argc && flag; i++) {
    if (argv[i][0] != '-') {
      int result = process_file(argv[i], flags, &ctx);
      if (!result) fprintf(stderr, "Unknow file: %s", argv[i]);
    }
  }
  return 0;
}