#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
  if (argc != 3) {
    printf("usage: byteswap <input filename> <output filename>\n");
    return 0;
  }
  FILE *in = fopen(argv[1], "rb");
  if (!in) {
    printf("Cannot open input file: %s\n", argv[1]);
    return 1;
  }
  FILE *out = fopen(argv[2], "wb");
  if (!out) {
    printf("Cannot open output file: %s\n", argv[2]);
    return 1;
  }

  while (!feof(in)) {
    uint16_t w;
    if (fread(&w, 2, 1, in) != 1) {
      break;
    }
    w = ((w & 0xff) << 8) | (w >> 8);
    if (fwrite(&w, 2, 1, out) != 1) {
      printf("File write error\n");
      return 1;
    }
  }
  
  fclose(in);
  fclose(out);
}
