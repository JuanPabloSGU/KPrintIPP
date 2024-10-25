#include "render_settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RenderSettings *init_render_settings() {
  RenderSettings *settings = malloc(sizeof(RenderSettings));
  if (settings == NULL) {
    perror("Failed to allocate memory for RenderSettings");
    exit(EXIT_FAILURE);
  }

  // Allocate memory for the fields
  settings->font_name = malloc(50 * sizeof(char));
  settings->page_size = malloc(10 * sizeof(char));
  settings->margin_top = malloc(10 * sizeof(char));
  settings->margin_bottom = malloc(10 * sizeof(char));
  settings->margin_left = malloc(10 * sizeof(char));
  settings->margin_right = malloc(10 * sizeof(char));

  if (!settings->font_name || !settings->page_size || !settings->margin_top ||
      !settings->margin_bottom || !settings->margin_left ||
      !settings->margin_right) {
    perror("Failed to allocate memory for RenderSettings fields");
    free_render_settings(settings);
    exit(EXIT_FAILURE);
  }

  settings->font_size = 0;

  return settings;
}

void free_render_settings(RenderSettings *settings) {
  free(settings->font_name);
  free(settings->page_size);
  free(settings->margin_top);
  free(settings->margin_bottom);
  free(settings->margin_left);
  free(settings->margin_right);
  free(settings);
}
