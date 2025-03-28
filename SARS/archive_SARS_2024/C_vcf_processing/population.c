#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 500000

int main() {
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    char *token;
    int num_samples = 0;

    // Open input VCF file
    input_file = fopen("RESULTS/RECENT_2024_GLOBAL.vcf", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open output text file
    output_file = fopen("population/recent_POPULATION.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    fprintf(output_file, "Sample_ID\tPopulation\n");

    // Read input VCF file line by line
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        // Check if line starts with '#'
        if (line[0] == '#') {
            // Skip header lines other than the one containing sample names
            if (strncmp(line, "#CHROM", 6) == 0) {
                // Tokenize the header line to extract sample names
                token = strtok(line, "\t");
                int column_index = 0;
                while (token != NULL) {
                    if (column_index >= 9) {
                        // Write sample name to output file
                        fprintf(output_file, "%s\tNEW\n", token);
                        num_samples++;
                    }
                    token = strtok(NULL, "\t");
                    column_index++;
                }
                // Stop reading after processing the header line
                break;
            }
        }
    }

    // Close files
    fclose(input_file);
    fclose(output_file);

    printf("Sample names extracted and written to output.txt successfully.\n");
    printf("Number of samples: %d\n", num_samples);

    return 0;
}
