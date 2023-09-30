#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *pfile;
  FILE *pmaxfile;
  char path[256];
  char maxpath[256];
  strcpy(path, "/sys/class/backlight/");

  int value, maxvalue;
  fscanf(pmaxfile, "%d", &maxvalue);
  fscanf(pfile, "%d", &value);

  if (argc > 3) {
    strcat(path, argv[1]);
    strcpy(maxpath, path);
    strcat(path, "/brightness");
    strcat(maxpath, "/max_brightness");

    pfile = fopen(path, "w+");
    pmaxfile = fopen(maxpath, "r");

    if (pfile == NULL || pmaxfile == NULL)
    {
      fclose(pfile);
      fclose(pmaxfile);
      return 1;
    }  

    int step;
    sscanf(argv[3], "%d", &step);

    if (strcmp(argv[2], "add") == 0) {
      value += step;
    }
    if (strcmp(argv[2], "reduce") == 0) {
      value -= step;
    }
  }

  if (value < 0)
    value = 0;
  else if (value > maxvalue)
    value = maxvalue;

  fprintf(pfile, "%d", value);
  fclose(pfile);
  fclose(pmaxfile);

  return 0;
}
