#include "render_settings.h"
#include <stdio.h>
#include <string.h>

void render_text(int x, int y, const char *text,
                 const RenderSettings *settings) {
  printf("Rendering text at (%d, %d): %s\n", x, y, text);
  printf("Font: %s %d\n", settings->font_name, settings->font_size);
  printf("Text: %s\n", text);
}

void render_pdl(const char *command, const char *args,
                const RenderSettings *settings) {
  printf("Rendering PDL command: %s\n", command);

  if (strcmp(command, "PageSize") == 0) {
    sscanf(args, "%9s", settings->page_size);
    printf("Set page size to: %s\n", settings->page_size);
  } else if (strcmp(command, "Margins") == 0) {
    sscanf(args, "%9s %9s %9s %9s", settings->margin_top,
           settings->margin_bottom, settings->margin_left,
           settings->margin_right);
    printf("Set margins to: %s %s %s %s\n", settings->margin_top,
           settings->margin_bottom, settings->margin_left,
           settings->margin_right);
  } else if (strcmp(command, "SetFont") == 0) {
    sscanf(args, "%49s %d", settings->font_name, &settings->font_size);
    printf("Set font to: %s %d\n", settings->font_name, settings->font_size);
  } else if (strcmp(command, "Text") == 0) {
    int x, y;
    char text[256];
    sscanf(args, "%d %d \"%[^\"]\"", &x, &y, text);
    render_text(x, y, text, settings);
  } else if (strcmp(command, "NewLine") == 0) {
    printf("New line\n");
  } else {
    printf("Unknown command: %s\n", command);
  }
}

int main() {
  RenderSettings *settings = init_render_settings();

  // Example PDL Commands
  render_pdl("PageSize", "A4", settings);
  render_pdl("Margins", "10 10 10 10", settings);
  render_pdl("SetFont", "Arial 12", settings);
  render_pdl("Text", "100 200 \"Hello, World!\"", settings);
  render_pdl("NewLine", "", settings);
  render_pdl("Text", "200 300 \"Goodbye, World!\"", settings);

  free_render_settings(settings);

  return 0;
}
