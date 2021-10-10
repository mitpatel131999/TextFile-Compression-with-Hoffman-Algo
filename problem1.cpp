/* 
     PATEL MITKUMAR RAJESHBHAI

     2020CSM1016
     
     PRACTICAL LAB ASSIGNMENT-8
     
     PROBLEM 1 
 */

#include <bits/stdc++.h> 
using namespace std; 
int ctr=0;
int ctx=0;

map <char,string> mp;         /* this map used to find character to binary code */
map <string,char> mp_1;       /* this map used to find binary code to character */
map <char,int> mp_2;          /* this map used to find character to Frequency   */

int size;

struct MinHeapNode             /* structure of min_heap */
 {  char data;                                  /* data contain value of character*/
    unsigned freq;                              /* freq frequency of respactive character */
    MinHeapNode *left, *right;                  /* left and right child of node */
  
    MinHeapNode(char data, unsigned freq)       /* constractor to set value of node*/
        { 
          left = right = NULL; 
          this->data = data; 
          this->freq = freq; 
        } 
}; 

struct compare { 
  
    bool operator()(MinHeapNode* left, MinHeapNode* right)  /* this function just compair their frequency 
                                                               and return largest structure */
    { 
        return (left->freq > right->freq); 
    } 
}; 
  
void compute_Codes(struct MinHeapNode* root, string str)    /* this function compute Huffman code from Huffman tree */
{ 
   if (!root)                                           /*base case root is null return*/
        return;                                            
  
    if (root->data != '$')                              /* if root is not '$' then it has character leaf node so we store Huffman code */
       { mp[root->data]=str;
         mp_1[str]=root->data;                          
       } 
  
    compute_Codes(root->left, str + "0");               /* call function recursively for lest child and right child */
    compute_Codes(root->right, str + "1"); 
} 
  

void HuffmanCodes_2()                                   /* this function create  Huffman tree*/
{ 
    struct MinHeapNode *left, *right, *top; 
  
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;    /* declear priority queue of structure minHeapNode*/
  
    for (auto itr = mp_2.begin(); itr !=mp_2.end(); itr++) 
        minHeap.push(new MinHeapNode(itr->first, itr->second));             /* load leaf node to Huffman tree (character and their Frequency)*/  
  
    while (minHeap.size() != 1) { 
        left = minHeap.top(); 
        minHeap.pop(); 
  
        right = minHeap.top(); 
        minHeap.pop(); 
  
        top = new MinHeapNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        minHeap.push(top); 
    } 
  
    compute_Codes(minHeap.top(), "");             /* call compute_Codes function to create Huffman code from tree */
} 
void print_data(vector<char> ch)
  {
                                                 /* this function just print character and huffman code */
    for(int j=0;j<size;j++)
    {
        cout<<ch[j]<<"      "<<mp[ch[j]]<<endl;
    }
  }
void  Frequency_Data()
    {                                            /* this function reads cheracter and their frequency
                                                    and write to the file "FrequencyData.txt"  */
       ofstream myfile;
       myfile.open ("FrequencyData.txt");
       myfile<<"|-----------------------------------|\n";
       myfile<<"| character  |      Frequency       |\n";
       myfile<<"|-----------------------------------|\n";
       for (auto itr = mp_2.begin(); itr !=mp_2.end(); itr++) 
         {  if(itr->first=='\n') {  myfile<<"|     "<<"\\n"<<"     |    "<<itr->second<<endl; } /* spcial condition for "\n" */
          else{  myfile<<"|      "<<itr->first<<"     |    "<<itr->second<<endl; }
         }
      myfile<<"|-----------------------------------|\n";
      
      myfile.close();
  
    }
void HuffmanCodes_data()
  {                                               /* this function reads cheracter and their huffman code
                                                     and write to the file "HuffmanCodeData.txt"  */

      ofstream myfile;
      myfile.open ("HuffmanCodeData.txt");
       myfile<<"|-----------------------------------|\n";
       myfile<<"| character  |     HuffmanCode      |\n";
       myfile<<"|-----------------------------------|\n";
       for (auto itr = mp.begin(); itr !=mp.end(); itr++) 
         { if(itr->first=='\n') {  myfile<<"|     "<<"\\n"<<"     |    "<<itr->second<<endl; } /* spcial condition for "\n" */
          else{  myfile<<"|      "<<itr->first<<"     |    "<<itr->second<<endl; }
         }
      myfile<<"|-----------------------------------|\n";
      
      myfile.close();
  
   }
  
 void encodeing()
   {     FILE *filePointer;                      /* this fuunction read character from "data.txt" and
                                                    write respactive huffman code to "EncodedData.txt" */
         filePointer = fopen("data.txt", "r");
         if (filePointer == NULL)
          {
                printf("File is not available \n");
          }
          else
          {
              ofstream myfile;
              myfile.open ("EncodedData.txt",ios::trunc | ios::binary);
              char ch;
              int count=7;
              char z=0;                          /* z is buffer which store 8 bit */
              while ((ch = fgetc(filePointer)) != EOF)
                {
                  // myfile<<mp[ch];    /* read character from "data.txt" and write Huffman code to "EncodedData.txt" */
                    for(int i=0;i<mp[ch].size();i++)
                     {
                      z=z|(mp[ch][i]-'0')<<count;        /*we will add all huffman code bit into z buffer*/   
                      count--;                            /* decrement count*/
                      if(count==-1)                          /* if buffer is full*/
                      { //myfile<<z;
                       myfile.write((char *)&z, sizeof(z));   /* we write buffer to the "EncodedData.txt" file*/
                       ctr++;
                       z=0;                                   /* make buffer empty */
                       count=7;                               /* set count as 7*/
                       } 
                     }
                     
                }
               if(count>=0 && count< 7){ myfile<<z; ctr++;}     /* condition for last byte buffer */
              myfile.close();  
          }
          fclose(filePointer);
   
   }  
 void decodeing()
   {
         FILE *filePointer;                       /* this fuunction read huffman code from "EncodedData.txt" and
                                                     write respactive  character to  "DecodedData.txt"  */

         filePointer = fopen("EncodedData.txt", "r");
         if (filePointer == NULL)
          {
                printf("File is not available \n");
          }
          else
          {    char ch;
              ofstream myfile;
              myfile.open ("DecodedData.txt",ios::binary);
              string s="";
              while ((ch = fgetc(filePointer)) != EOF|| ctx<ctr)
                {
                  // s=s+ch;
                  // if(mp_1.count(s)>0)           /* condition of huffman code is exist or not */
                  // { myfile<<mp_1[s]; s="";      /* write character of reapactive huffman code to "DecodedData.txt"  */
                  // }
                  ctx++;
                  int count=7;
                  char xi=ch;                       /* xi is tmaparary buffer*/
                  while (count>=0)
                   { xi=ch;
                     int k=(xi>>count)&1;           /* we read each bit of buffer */ 
                     s=s+(char)(k+'0');             /* add bit to the string s*/
                   
                   if(mp_1.count(s)>0)              /* condition for given string is huffmancode*/
                    {   myfile<<mp_1[s];            /* write character according to the huffmancode into "DecodedData.txt" */
                        s="";                       /* make s empty*/
                    }
                   count--;
                  }
                }
              myfile.close();  
          }
          fclose(filePointer);
   
   }   
// Driver program to test above functions 
int main() 
{ 
     int i=0;
  
     cout<<"Enter 1 or 2:";
   int choice;
   cin>>choice;
 switch( choice)
 { 
 case 1: 
  { cout<<"You entered a 1:\n";
    cout<<"Enter character-frequency table:\n";
     vector<int> fre;         /* vector of Frequency */
     vector<char> ch;         /* vector of Character */
    while(!cin.eof())                           /* condition of EOF */
    {    char chr; int t;
         cin>>chr>>t;
         ch.push_back(chr);
         fre.push_back(t);
         mp_2[chr]=t;                           /* read character from user and set  map Frequency of that character */
         i++;
        if(cin.eof()){ break;}
    }
     size=i-1;
     HuffmanCodes_2();                           /* call function HuffmanCodes_2() to create Huffman tree */         
     cout<<"Huffman code table is as follows:"<<endl;
     cout<<"Char codeword"<<endl;
     print_data(ch);                             /* call function print_data to print Huffman code table*/ 
     return 0;
   }
  case 2:
    {
          FILE *filePointer;
          char ch;
          filePointer = fopen("data.txt", "r");
    
          if (filePointer == NULL)
          {
                printf("File is not available \n");
          }
          else
          {
            while ((ch = fgetc(filePointer)) != EOF)
                {
                    mp_2[ch]++;               /* read character from data.txt and increased map Frequency of that character */
                }
          }
          fclose(filePointer);
          Frequency_Data();                   /* call function Frenquency_data() to Frequency write in txt file */
          cout<<" FrequencyData.txt is created \n";
          HuffmanCodes_2();                   /* call function HuffmanCodes_2() to create Huffman tree */
          HuffmanCodes_data();                /* call function HuffmanCodes_data() to write Huffman Code in txt file */
          cout<<" HuffmanCodeData.txt is created \n";
          encodeing();                        /* to encode text data into hoffman code form*/
          cout<<" EncodedData.txt is created \n";
          decodeing();                        /* to decode hoffman code into text data form*/
          cout<<" DecodedData.txt is created \n";
    }
 } 
   
   
   
    return 0; 
} 


