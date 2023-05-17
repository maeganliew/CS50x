#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf ("Incorrect Usage.\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf ("Could not open file.\n");
        return 1;
    }

    FILE *outfile = NULL;
    BYTE buffer[512];
    char filename[8];
    int n = 0;

    while(fread(buffer, sizeof(BYTE)*512, 1, infile) == 1)
    {
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]&0xf0)==0xe0)
        {
            if (outfile != NULL)
                fclose(outfile);
            sprintf(filename, "%03i.jpg", n++);
            outfile = fopen(filename, "w");
        }
        if (outfile != NULL)
            fwrite(buffer, sizeof(BYTE)*512, 1, outfile);
    }
    if (outfile != NULL)
        fclose (outfile);
    fclose (infile);
}