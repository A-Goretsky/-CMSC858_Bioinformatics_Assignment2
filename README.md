# CMSC858_Bioinformatics_Assignment2

Implemented are the required suffix array construction and querying specs.

Some code was used and modified from: https://rosettacode.org/wiki/FASTA_format#C.2B.2B for the parsing of the FASTA file.

There exists a makefile with several commands premade.
Run `make` to compile `buildsa` and `querysa`
Run `make file` to build a SA with a k of 3.
Run `make query` to run all queries on said SA using the "naive" approach
Run `make query_accel` to run all queries on said SA using the "simpaccel" approach

To independently run said files, run in the following format:
`./buildsa [--preftab] [k] [input_fasta] [serialized_output]`

`./querysa [serialized_output] [query_file] [query_mode] [query_output]`

