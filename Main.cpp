#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
class CacheMem{
	string *tags;
	bool *valid;
	int count;
	int position;
	int first;
	int last;
	int *startAddress;
	string *data;
public:
	CacheMem(int n){
		valid=new bool[n];
		startAddress=new int[n];
		data=new string[n*16];
		int i=0, p=0;
		for(i=0;i<n;i++){
			startAddress[i]=p;
			p+=16;
		}
		tags=new string[n];
		count=n;
		last=count-1;
		first=position=0;
	}
	bool isFull(){
		if(position==count)
			return true;
		else
		return false;
	}
	void insertIntoCache(string address){
		if(isFull()==false){
			string tag;
			tag=address.substr(0,3);
			tags[position]=tag;
			valid[position]=true;
			position++;
		}
		else{
		 cout<<"Searching for space to replace..."<<endl;
			replace(address);
		 cout<<"Replacement successful!"<<endl;
		}
	}
	bool existsInCache(string address){
		int i=0;
		string tag;
		tag=address.substr(0,3);
		for(i=0;i<count;i++)
			if(tags[i]==tag&& valid[i]==true){
				return true;
			}
		return false;
	}
	void print(){
		int i=0;
	 cout<<"v   tag  startAddress"<<endl;
		for(i=0;i<position;i++)
	 cout<<valid[i]<<"    "<<tags[i]<<"      "<<startAddress[i]<<endl;
	}
	void replace(string address){
		tags[first]=" ";
		int i;
		string tag;
		tag=address.substr(0,3);
		int temp=startAddress[0];
		for(i=0;i<count-1;i++){
       		tags[i]=tags[i+1];
       		startAddress[i]=startAddress[i+1];
      	}
    	tags[count-1]=tag;
    	startAddress[count-1]=temp;
	}	
	string readFromCache(string address){
		int i;
		string tag;
		int p=0;
		tag=address.substr(0,3);
		for(i=0;i<count;i++)
			if(tags[i]==tag&& valid[i]==true){
				p=i;
			}
		char hex[1]={address[3]};
		char * pEnd;
		int h=(int)strtol(hex,&pEnd,16);
		return data[startAddress[p]+h];
	}
	void loadFromDisk(string address){
		ifstream file("hex.txt");
		int i=0;
		string tag;
		int p=0;
		tag=address.substr(0,3);
		for(i=0;i<count;i++)
			if(tags[i]==tag&& valid[i]==true){
				p=i;
			}
		string line;
		string mem[16];
		i=0;
		while((getline(file, line))&&(i<16)){
			string t=line.substr(0,3);
			string d=line.substr(5,7);
			if(t==tag){
				mem[i]=d;
				i++;
			}
		}
		file.close();
		for(i=0;i<16;i++)
		data[startAddress[p]+i]=mem[i];
	}
	void printData(){
		int i;
		for(i=0;i<count*16;i++)
		 cout<<data[i]<<endl;
	}
	~CacheMem(){
		delete[] tags;
		delete[] valid;
		delete[] startAddress;
		delete[] data;
	 cout<<"Object destroyed"<<endl<<"End of execution";
	}
};
int main(){
	CacheMem cm=CacheMem(10);
	while(1){
		int choice;
	 cout<<"1. Read from Cache"<<endl<<"2. Exit"<<endl;
		cin>>choice;
		if(choice==1){
			string address;
		 cout<<"Enter address to read from"<<endl;
			cin>>address;
			if(cm.existsInCache(address)){
			 cout<<"HIT - reading from cache"<<endl;
			 cout<<"Data at address "<<address<<" is "<<cm.readFromCache(address)<<endl;
			 cout<<"Cache tag contents:"<<endl;
				cm.print();
			}
			else{
			 cout<<"MISS"<<endl;
				cm.insertIntoCache(address);
			 cout<<"Reading from disk..."<<endl;
				cm.loadFromDisk(address);
			 cout<<"Disk read complete."<<endl;
			 cout<<"Data at address "<<address<<" is "<<cm.readFromCache(address)<<endl;
			 cout<<"Cache tag contents:"<<endl;
				cm.print();
			}
		}
		else
			break;
	}
	getchar();
	return 0; 
}
