#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define READ                  "r"
#define WRITE_BINARY          "wb"

int main (int argc, char *argv[]) {
    FILE *f_in, *f_out;

    if (argc < 3) {
        printf("Usage: %s <file_in> <file_out>\n", argv[0]);
        return -1;
    }

    const char *file_in  = argv[1];
    const char *file_out = argv[2];

    f_in  = fopen(file_in, READ);
    f_out = fopen(file_out, WRITE_BINARY);

    if (f_in == NULL || f_out == NULL) {
        printf("error opening files\n");
        return -1;
    }

    unsigned char content[2] = { 0 };
    int read = 0;

    while (1) {
        read = fscanf(f_in, "%2hhx", content);
        if (feof(f_in)) {
            fwrite((void *)content, sizeof(unsigned char), 1, f_out);
            fclose(f_in);
            fclose(f_out);
            return 0;
        } else if (read != 1 || ferror(f_in)) {
            printf("error reading file\n");
            fclose(f_in);
            fclose(f_out);
            return -1;
        }

        fwrite((void *)content, sizeof(unsigned char), 1, f_out);

        if (ferror(f_out)) {
            printf("error writing file %s\n", file_out);
            fclose(f_in);
            fclose(f_out);
            return -1;
        }
    }

    return 0;
}
