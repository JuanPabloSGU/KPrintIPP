#include "pdl.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Helper function to trim spaces
char *trim_whitespace(char *str) {
  while (*str == ' ' || *str == '\t')
    str++;
  return str;
}

// Handlers for font command
void handle_arial(const char *args) { printf("Font: Arial, Size: %s\n", args); }
void handle_sans_serif(const char *args) {
  printf("Font: Sans Serif, Size: %s\n", args);
}
void handle_comic_sans(const char *args) {
  printf("Font: Comic Sans, Size: %s\n", args);
}
void handle_unknown_font(const char *args) {
  printf("Unknown font, Size: %s\n", args);
}

// Font lookup table
static const FontMap font_table[] = {
    {"Arial", ARIAL, handle_arial},
    {"SansSerif", SANS_SERIF, handle_sans_serif},
    {"ComicSans", COMIC_SANS, handle_comic_sans},
    {NULL, FONT_UNKNOWN, handle_unknown_font},
};

// Handlers for page size commands
void handle_a4() { printf("Page size: A4\n"); }
void handle_a5() { printf("page size: A5\n"); }
void handle_letter() { printf("Page size: Letter\n"); }
void handle_legal() { printf("Page size: Legal\n"); }
void handle_unknown_page_size() { printf("Unknown page size\n"); }

// Page size lookup table
static const PageSizeMap page_size_table[] = {
    {"A4", A4, handle_a4},
    {"A5", A5, handle_a5},
    {"Letter", LETTER, handle_letter},
    {"Legal", LEGAL, handle_legal},
    {NULL, SIZE_UNKNOWN, handle_unknown_page_size},
};

// Handlers for PDL commands
void handle_text(const char *args) {
  int x, y;
  char text[256]; // Buffer for the text

  if (sscanf(args, "%d %d \"%[^\"]\"", &x, &y, text) == 3) {
    printf("Text at (%d, %d): %s\n", x, y, text);
  } else {
    printf("Invalid Text command: %s\n", args);
  }
}

void handle_newline() { printf("Newline\n"); }
void handle_page() { printf("Page\n"); }

void handle_page_size(const char *args) {
  PageSize size = SIZE_UNKNOWN;

  // Find the page size in the lookup table
  const PageSizeMap *page_size = page_size_table;
  while (page_size->name) {
    if (strcmp(page_size->name, args) == 0) {
      size = page_size->size;
      break;
    }
    page_size++;
  }

  page_size->handler(size);
}
void handle_set_font(const char *args) {
  FontType type = FONT_UNKNOWN;

  // Split the arguments into font name and size
  char *font_name = strtok((char *)args, " ");

  // NULL is passed to strtok to continue from the last token
  char *font_size = strtok(NULL, " ");

  // Find the font in the lookup table
  const FontMap *font = font_table;
  while (font->name) {
    if (strcmp(font->name, font_name) == 0) {
      type = font->type;
      break;
    }
    font++;
  }

  font->handler(font_size);
}
void handle_margins(const char *args) { printf("Margins: %s\n", args); }
void handle_unknown(const char *args) { printf("Unknown command: %s\n", args); }
// Command lookup table
static const CommandMap command_table[] = {
    {"Text", CMD_TEXT, handle_text},
    {"NewLine", CMD_NEWLINE, handle_newline},
    {"Page", CMD_PAGE, handle_page},
    {"PageSize", CMD_PAGE_SIZE, handle_page_size},
    {"Margins", CMD_MARGINS, handle_margins},
    {"SetFont", CMD_SET_FONT, handle_set_font},
    {NULL, CMD_UNKNOWN, handle_unknown},
};

void parse_pdl(const char *pdl) {
  char command_buffer[256];
  const char *pos = pdl;

  while (*pos) {
    char *command_start = command_buffer;
    while (*pos && *pos != '\n') {
      *command_start++ = *pos++;
    }

    *command_start = '\0';

    // Split the command into name and arguments
    char *args = strchr(command_buffer, ' ');
    if (args) {
      *args++ = '\0';
    } else {
      args = "";
    }

    // Find the command in the lookup table
    const CommandMap *cmd = command_table;
    while (cmd->name) {
      if (strcmp(cmd->name, command_buffer) == 0) {
        cmd->handler(args);
        break;
      }
      cmd++;
    }

    if (!cmd->name) {
      handle_unknown(command_buffer);
    }

    if (*pos == '\n')
      pos++;
  }
}
