#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
using namespace std;
void hex_string(char str[], int length){
  //hexadecimal characters
	char hex_characters[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  	int i;
  	for(i=0;i<length;i++){
    str[i]=hex_characters[rand()%16];
  }
  	str[length]=0;
}

int main(){
	int x=0x0;
	printf("%04x\n",x);
	//x++;
	//printf("%04x\n",x);
//	getchar();
	FILE *fptr;
	fptr=fopen("hex.txt","w");
	int n,length;
  	char hex[1000];
    //cout<<"Enter number of random hexadecimal strings you want."<<endl;
    //cin>>n;
    //cout<<"Enter length of the hexadecimal strings."<<endl;
    //cin>>length;
    srand(time(0));
    //for(int i=0;i<n;i++)
      //
       // cout << "Hexadecimal String "<<i+1<<": " << hex<<endl;
  	int i;
  	i=0;
  	while(i<1000){
  		hex_string(hex,2);
  		fprintf(fptr,"%04X:%s\n",x,hex);
  		x++;
  		i++;
  }
  	fclose(fptr);
	return 0;
}

