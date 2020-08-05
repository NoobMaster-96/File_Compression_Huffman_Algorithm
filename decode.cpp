/*
Team : Inferno DTU
Creator : avinash 
Date : 2019-April-13
*/
#include <bits/stdc++.h>
#include "compression.h"
using namespace std;

codeTable *codelist;

int n;
char *decodeBuffer(char buffer);
char *int2string(int n);
int match(char a[],char b[],int limit);
int fileError(FILE *fp);

void replaceExt(string& s, const string& newExt){
    string::size_type i = s.rfind('.', s.length());
    if(i != string::npos){
        s.replace(i+1, newExt.length(), newExt);
    }
    s.resize(s.length()-4);
    string pre = "recovered_";
    s = pre+s;
}

int main(int argc, char** argv){
    FILE *fp,*outfile;
    char buffer;
    char *decoded;
    int i;

    if(argc<=2){
        cout<<"***Huffman Decoding***\n";
        if(argc==2){
            argv[2]=(char *)malloc(sizeof(char)*(strlen(argv[1])));
            string file = argv[1];
            string ext = decompressed_extension;
            replaceExt(file,ext);
            strcpy(argv[2], file.c_str());
            argc++;
        }
        else{
            return 0;
        } 
    }
    if((fp=fopen(argv[1],"rb"))==NULL){
        cout<<"[!]Input file cannot be opened.\n";
        return -1;
    }

    cout<<"\n[Reading File Header]";
    if(fread(&buffer,sizeof(unsigned char),1,fp)==0){
        return (fileError(fp));
    }
    N=buffer;		//No. of structures(mapping table records) to read
    if(N==0){
        n=256;
    }
    else{
        n=N;
    }
    cout<<"\nDetected: "<<n<<" different characters.";

    //allocate memory for mapping table
    codelist=(codeTable *)malloc(sizeof(codeTable)*n);

    cout<<"\nReading character to Codeword Mapping Table";
    if(fread(codelist,sizeof(codeTable),n,fp)==0){
        return (fileError(fp));
    }
    //Read mapping table
    if(fread(&buffer,sizeof(char),1,fp)==0){
        return (fileError(fp));
    }
    padding=buffer;		//No. of bits to discard
    cout<<"\nDetected: "<<padding<<" bit padding.";

    if((outfile=fopen(argv[2],"wb"))==NULL){
        cout<<"[!]Output file cannot be opened.\n";
        fclose(fp);
        return -2;
    }

    cout<<"\n\n[Reading data]\nReplacing codewords with actual characters";
    while(fread(&buffer,sizeof(char),1,fp)!=0){//Read 1 byte at a time
        decoded=decodeBuffer(buffer);	//decoded is pointer to array of characters read from buffer byte
        i=0;
        while(decoded[i++]!='\0');	//i-1 characters read into decoded array
        fwrite(decoded,sizeof(char),i-1,outfile);
    }
    fclose(fp);
    fclose(outfile);
    cout<<"\nEverything fine..\nOutput file "<<argv[2]<<" written successfully.\n"; 
    return 0;
}

char *decodeBuffer(char b){
    int i=0,j=0,t;
    static int k;  
    static int buffer;                      // buffer larger enough to hold two b's
    char *decoded=(char *)malloc(MAX*sizeof(char));
    t = (int)b;
    t = t & 0x00FF;                         //mask high byte
    t = t<<(8-k);                           //shift bits keeping zeroes for old buffer 
    buffer = buffer | t;                    //joined b to buffer
    k = k+8;                                //first useless bit index +8 , new byte added

    if(padding!=0){                         // on first call
        buffer=buffer<<padding; 
        k=8-padding;                        //k points to first useless bit index
        padding=0;
    }
                                            //loop to find matching codewords
    while(i<n){
        if(!match(codelist[i].code, int2string(buffer),k)){	
            decoded[j++]=codelist[i].x;	    //match found inserted decoded
            t=strlen(codelist[i].code);	    //matched bits
            buffer=buffer<<t;               //throw out matched bits
            k=k-t;                          //k will be less
            i=0;                            //match from initial record
            if(k==0){
                break;
            }
            continue;
        }
        i++;
    }

    decoded[j]='\0';
    return decoded;

}

int match(char a[],char b[],int limit){
    b[strlen(a)]='\0';
    b[limit]='\0';
    return strcmp(a,b);
}

char *int2string(int n){
    int i,k,andd,j;
    char *temp=(char *)malloc(16*sizeof(char));
    j=0;

    for(i=15;i>=0;i--){
        andd=1<<i;
        k=n & andd;
        if(k==0){
            temp[j++]='0';
        }
        else{
            temp[j++]='1';
        }
    }
    temp[j]='\0';
    return temp;
}

int fileError(FILE *fp){
    cout<<"[!]File read Error.\n[ ]File is not compressed using huffman.\n";
    fclose(fp);
    return -3;
}
