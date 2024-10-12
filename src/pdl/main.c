#include "pdl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to read a file into a string
char *read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }

  // Seek to the end of the file to get the file size
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  // Allocate memory for file content
  char *buffer = (char *)malloc(file_size + 1);
  if (!buffer) {
    perror("Failed to allocate memory");
    fclose(file);
    return NULL;
  }

  // Read file content into buffer
  fread(buffer, 1, file_size, file);
  buffer[file_size] = '\0'; // Null-terminate the string

  fclose(file);
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pdl_file.pdl>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Read the PDL file
  char *pdl_data = read_file(argv[1]);
  if (pdl_data == NULL) {
    fprintf(stderr, "Error reading PDL file\n");
    return EXIT_FAILURE;
  }

  // Parse the PDL data
  printf("Parsing PDL from file: %s\n", argv[1]);
  parse_pdl(pdl_data);

  free(pdl_data);
  return EXIT_SUCCESS;
}
