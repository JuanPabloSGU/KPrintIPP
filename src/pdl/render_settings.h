#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

typedef struct {
  char *font_name;
  int font_size;
  char *page_size;
  char *margin_top;
  char *margin_bottom;
  char *margin_left;
  char *margin_right;
} RenderSettings;

RenderSettings *init_render_settings();

void free_render_settings(RenderSettings *settings);

void render_text(int x, int y, const char *text,
                 const RenderSettings *settings);

void render_pdl(const char *command, const char *args,
                const RenderSettings *settings);

#endif // !RENDER_SETTINGS_H
