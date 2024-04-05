#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 500000
#define MAX_COLUMNS 10000

int main() {
    FILE *input_file, *output_file;
    char input_filename[] = "freebayes_vcf/RECENT2024.vcf";
    char output_filename[] = "intermediate/RECENT2024.vcf";
    char line[MAX_LINE_LENGTH];
    char *token;
    int column_count = 0;
    int ref_index = -1, alt_index = -1;
    int i;

    input_file = fopen(input_filename, "r");
    output_file = fopen(output_filename, "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read input file line by line
    while (fgets(line, sizeof(line), input_file)) {
        // If the line starts with "##", skip processing (ignore comments)
        if (strncmp(line, "##", 2) == 0) {
            fputs(line, output_file);
            continue;
        }

        // If the line starts with "#", it's the column label row
        if (line[0] == '#') {
            fputs(line, output_file);
            continue;
        }

        // Tokenize the line based on tabs
        token = strtok(line, "\t");
        column_count = 0;
        while (token != NULL && column_count < MAX_COLUMNS) {
            if (column_count == 3) { // REF column
                if (strlen(token) > 1) {
                    fprintf(output_file, "\n");
                    break; // Skip this line if REF has more than one character
                }
                ref_index = column_count;
            }
            if (column_count == 4) { // ALT column
                if (strlen(token) > 1) {
                    fprintf(output_file, "\n");
                    break; // Skip this line if ALT has more than one character
                }
                alt_index = column_count;
            }
            if (column_count > 0) {
                fprintf(output_file, "\t");
            }
            fprintf(output_file, "%s", token);
            token = strtok(NULL, "\t");
            column_count++;
        }
        if (ref_index == -1 || alt_index == -1) {
            printf("Error: Missing REF or ALT column.\n");
            return 1;
        }
        //if (column_count > 0) {
            //fprintf(output_file, "\n");
        //}
    }

    fclose(input_file);
    fclose(output_file);

    printf("Processing complete.\n");

    return 0;
}
