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
  CMD_UNKNOWN
} CommandType;

// Function pointer type for command handlers
typedef void (*CommandHandler)(const char *);

// Struct to represent a PDL command
typedef struct {
  const char *name;
  CommandType type;
  CommandHandler handler;
} CommandMap;

void parse_pdl(const char *pdl);
void draw_text(const char *text, int x, int y);

#endif // !PDL_H
