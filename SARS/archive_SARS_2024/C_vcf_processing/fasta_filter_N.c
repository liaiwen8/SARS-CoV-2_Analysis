#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    bool skip_sequence = false;

    // Open input FASTA file
    input_file = fopen("fasta_N/us2023.fasta", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open output FASTA file
    output_file = fopen("fasta_N/USA_2023.fasta", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    // Read input FASTA file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        // Check if line starts with '>'
        if (line[0] == '>') {
            // If previous sequence passed the check, write its header to output
            if (!skip_sequence) {
                fprintf(output_file, "%s", line);
            }
            // Reset skip flag for the next sequence
            skip_sequence = false;
        } else {
            // Check if the line contains 'N' character
            if (strchr(line, 'N') != NULL) {
                // Set skip flag if 'N' is found
                skip_sequence = true;
            }
            // If not skipping, write the sequence line to output
            if (!skip_sequence) {
                fprintf(output_file, "%s", line);
            }
        }
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Sequences without 'N' characters have been written to output.fasta successfully.\n");

    return 0;
}
