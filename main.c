#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *pfile;
  FILE *pmaxfile;
  pfile = fopen("/sys/class/backlight/intel_backlight/brightness", "w+");
  pmaxfile = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");

  int value, maxvalue;
  fscanf(pmaxfile, "%d", &maxvalue);
  fscanf(pfile, "%d", &value);

  if (argc > 1) {
    if (strcmp(argv[1], "add") == 0) {
      value += 10;
    }
    if (strcmp(argv[1], "reduce") == 0) {
      value -= 10;
    }
  }

  if (value < 0)
    value = 0;
  if (value > maxvalue)
    value = maxvalue;

  fprintf(pfile, "%d", value);
  fclose(pfile);
  fclose(pmaxfile);

  return 0;
}
