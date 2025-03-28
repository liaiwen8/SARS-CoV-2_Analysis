#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 500000

int main() {
    FILE *input_file, *output_file;
    char input_filename[] = "intermediate/2025_GLOBAL.vcf";
    char output_filename[] = "RESULTS/2025_GLOBAL.vcf";
    char line[MAX_LINE_LENGTH];

    // Open input file for reading
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file for writing
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Read input file line by line
    while (fgets(line, sizeof(line), input_file)) {
        // Check if line starts with "##", if so, skip processing (ignore comments)
        if (strncmp(line, "##", 2) == 0) {
            fputs(line, output_file);
            continue;
        }

        // Check if line is shorter than 50 characters
        if (strlen(line) < 50) {
            continue;
        }

        // Write the line to the output file
        fputs(line, output_file);
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Processing complete. Filtered file saved as %s\n", output_filename);

    return 0;
}
