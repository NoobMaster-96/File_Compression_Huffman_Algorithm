/*
Creator : avinash 
Date : 2020-April-13
*/
#define MAX 16
// padding is done to ensure that the code generated for each charater will fit byte size.
// i.e : 4 bytes + 3bits will be consider as 5 bytes.
char padding;
unsigned char N;


// Code table regarding every character in the file
typedef struct codeTable
{
    char x;
    char code[MAX];
} codeTable;

char compressed_extension[]  = "avinash";
char decompressed_extension[] = "txt";
