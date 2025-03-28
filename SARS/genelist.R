# Install and load necessary packages
if (!requireNamespace("BiocManager", quietly = TRUE)) {
  install.packages("BiocManager")
}
BiocManager::install("biomaRt")

library(biomaRt)

# Connect to the Ensembl BioMart database
ensembl <- useMart("ensembl", dataset = "hsapiens_gene_ensembl")

listDatasets(ensembl, verbose = FALSE)

# Get gene information for SARS-CoV-2
genes <- getBM(attributes = c("chromosome_name", "start_position", "end_position"),
               filters = "refseq_mrna",
               values = "NC_045512.2",
               mart = ensembl)

# Write gene information to a tab-delimited text file
write.table(genes, file = "gene_list_NC_045512.2.txt", sep = "\t", quote = FALSE, row.names = FALSE)

print(genes)
