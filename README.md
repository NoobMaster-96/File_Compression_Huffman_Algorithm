# File Compression Using Huffman's Algorithm
# About
This is a CLI application for compressing .txt files using Huffman's algorithm.
Huffman Algorithm is an efficient way for file Compression and Decompression. This program exactly follows huffman algorithm. It reads frequent characters from input text file and replace it with shorter binary codeword. The original file can be produced again without loosing any bit.

# Usage
Download or clone this directory on your system. Open terminal and use the following commands.
## For Compression:
./encode "filename"

An output file with ".avinash" extension will be created.
## For Decompression:
./decode "filename"

An output file named recovered_"filename" with ".txt" extension will be created

# Testing
It is noticed that with increase in file size there's an increase in compression ratio.

sample1 before compression - 7.9kB

sample1 after compression - 5.6kB

sample1 compression ratio = 7.9/5.6 = 1.41

sample2 before compression - 22kB

sample2 after compression - 13.9kB

sample2 compression ratio = 22/5.6 = 1.58
