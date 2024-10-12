// Description: PDL (Printer Description Language) parser and interpreter
#ifndef PDL_H
#define PDL_H

// Enum for PDL commands
typedef enum {
  CMD_TEXT,
  CMD_NEWLINE,
  CMD_PAGE,
  CMD_PAGE_SIZE,
  CMD_SET_FONT,
  CMD_MARGINS,
  CMD_UNKNOWN
} CommandType;

// Enum for Page Size
typedef enum { A4, A5, LETTER, LEGAL, SIZE_UNKNOWN } PageSize;

// Enum for Font Type
typedef enum { ARIAL, SANS_SERIF, COMIC_SANS, FONT_UNKNOWN } FontType;

// Function pointer type for page size handlers
typedef void (*PageSizeHandler)(PageSize);

// Function pointer type for command handlers
typedef void (*CommandHandler)(const char *);

// Function pointer type for font handlers
typedef void (*FontHandler)(const char *);

// Struct to represent a PDL command
typedef struct {
  const char *name;
  CommandType type;
  CommandHandler handler;
} CommandMap;

// Struct to represent a page size
typedef struct {
  const char *name;
  PageSize size;
  PageSizeHandler handler;
} PageSizeMap;

// Struct to represent a font
typedef struct {
  const char *name;
  FontType type;
  FontHandler handler;
} FontMap;

void parse_pdl(const char *pdl);
void draw_text(const char *text, int x, int y);

#endif // !PDL_H
