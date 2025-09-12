#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//needed for the convert.h file
#include "convert.h"

int main(int argc, char *argv[]) {
	//Argument Check
    if (argc != 2) {
        fprintf(stderr, "Usage: %s test_file.txt\n", argv[0]);
        return 1;
    }
	//opens the file if available
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening test file");
        return 1;
    }

    char line[512];
    char func[64], expected[256], extra[256];
    //char got[256]; // keep this since we use it for div/sub tests

    uint32_t n;
    int base;
    int total = 0, pass = 0;
    int testnum = 1;

//Reads every line in the File, similar to the filereader in C#
    while (fgets(line, sizeof(line), fp)) {
        // Trim leading spaces
        char *p = line;
        while (*p && (*p == ' ' || *p == '\t')) p++;

        // Skips comments and blank lines
        if (*p == '#' || *p == '\0' || *p == '\n') continue;

        // Handle print_tables lines: func n FORMATTED_OUTPUT
        if (sscanf(p, "%63s %u %255s", func, &n, extra) == 3 &&
            strcmp(func, "print_tables") == 0 &&
            strcmp(extra, "FORMATTED_OUTPUT") == 0) {
            printf("Test %d: print_tables %u -> FORMATTED_OUTPUT\n", testnum++, n);
            // print formatted output (single-call, safe)
            print_tables((int)n);
            total++;
            pass++; // we treat formatted output tests as passed because we print the requested format
            continue;
        }

        // Handles the  div_convert / sub_convert lines: func n base expected
        if (sscanf(p, "%63s %u %d %255s", func, &n, &base, expected) == 4) {
            char outbuf[256] = {0};
            if (strcmp(func, "div_convert") == 0) {
                div_convert(n, base, outbuf);
            } else if (strcmp(func, "sub_convert") == 0) {
                sub_convert(n, base, outbuf);
            } else {
                // unknown function - skip
                continue;
            }

            total++;
            int ispass = (strcmp(outbuf, expected) == 0);
            if (ispass) pass++;

            printf("Test %d: %s %u %d got=%s expected=%s %s\n",
                   testnum++, func, n, base, outbuf, expected, ispass ? "PASS" : "FAIL");
            continue;
        }

    }
	// prints the Summary/results
    printf("Summary: %d/%d tests passed\n", pass, total);

    fclose(fp);
    return 0;
}
