#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void kill (const char* message)
{
  perror(message);
  exit(1);
}

int main(int argc, char **argv) 
{
  if (argc < 2) kill("no device name given");

  FILE *pfile;
  FILE *pmaxfile;

  char path[256];
  char maxpath[256];

  char* base_path = "/sys/class/backlight/";
  char* device_name = argv[1];

  strcpy(path, base_path);
  strcat(path, device_name);
  strcpy(maxpath, path);
  strcat(path, "/brightness");
  strcat(maxpath, "/max_brightness");

  pfile = fopen(path, "w+");
  pmaxfile = fopen(maxpath, "r");

  if (pfile == NULL)
  {
    fclose(pfile);
    fclose(pmaxfile);
    kill("unable to open brightness file");
  }


  if (pmaxfile == NULL) 
  {
    fclose(pmaxfile);
    fclose(pfile);
    kill("unable to open max_brightness file");
  }

  int value, maxvalue;
  fscanf(pmaxfile, "%d", &maxvalue);
  fscanf(pfile, "%d", &value);

  int step;
  if (sscanf(argv[3], "%d", &step) == -1)
  {
    fclose(pfile);
    fclose(pmaxfile);
    kill("invalid argument");
  }

  if (strcmp(argv[2], "add") == 0) 
  {
    value += step;
  }
  else if (strcmp(argv[2], "reduce") == 0) 
  {
    value -= step;
  }
  else
  {
    fclose(pfile);
    fclose(pmaxfile);
    kill("invalid argument");
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
