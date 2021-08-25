#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;
class KesMem{
	string *s;
	bool *v;
	int count;
	int poz;
	int first;
	int last;
	int *w;
	string *data;
public:
	KesMem(int n){
		v=new bool[n];
		w=new int[n];
		data=new string[n*16];
		int i=0, p=0;
		for(i=0;i<n;i++){
			w[i]=p;
			p+=16;
		}
		s=new string[n];
		count=n;
		last=count-1;
		first=poz=0;
	}
	bool isFull(){
		if(poz==count)
			return true;
		else
		return false;
	}
	void staviUkes(string adresa){
		if(isFull()==false){
			string tag;
			tag=adresa.substr(0,3);
			s[poz]=tag;
			v[poz]=true;
			poz++;
		}
		else{
			cout<<"Trazi se mesto za zamenu..."<<endl;
			zamena(adresa);
			cout<<"Zamena uspela!"<<endl;
		}
	}
	bool vecPostoji(string adresa){
		int i=0;
		string tag;
		tag=adresa.substr(0,3);
		for(i=0;i<count;i++)
			if(s[i]==tag&& v[i]==true){
				return true;
			}
		return false;
	}
	void stampa(){
		int i=0;
		cout<<"v   tag  startAdress"<<endl;
		for(i=0;i<poz;i++)
		cout<<v[i]<<"    "<<s[i]<<"      "<<w[i]<<endl;
	}
	void zamena(string adresa){
		s[first]=" ";
		int i;
		string tag;
		tag=adresa.substr(0,3);
		int pom=w[0];
		for(i=0;i<count-1;i++){
       		s[i]=s[i+1];
       		w[i]=w[i+1];
     	}
    	s[count-1]=tag;
    	w[count-1]=pom;
	}	
	string citanjeIzKesa(string adresa){
		int i;
		string tag;
		int p=0;
		tag=adresa.substr(0,3);
		for(i=0;i<count;i++)
			if(s[i]==tag&& v[i]==true){
				p=i;
			}
		char hex[1]={adresa[3]};
		char * pEnd;
		int h=(int)strtol(hex,&pEnd,16);
		//int t=w[p]+h;
		//cout<<w[p]<<"+"<<h<<"="<<t<<endl;
		return data[w[p]+h];
	}
	void puniMemoriju(string adresa){
		ifstream file("hex.txt");
		int i=0;
		string tag;
		int p=0;
		tag=adresa.substr(0,3);
		for(i=0;i<count;i++)
			if(s[i]==tag&& v[i]==true){
				p=i;
			}
		string s;
		string mem[16];
		i=0;
		while((getline(file, s))&&(i<16)){
			string t=s.substr(0,3);
			string d=s.substr(5,7);
			if(t==tag){
				mem[i]=d;
				i++;
			}
		}
		//cout<<t<<endl<<d<<endl<<s<<endl;
		file.close();
		for(i=0;i<16;i++)
		data[w[p]+i]=mem[i];
	}
	void printArray(){
		int i;
		for(i=0;i<count*16;i++)
			cout<<data[i]<<endl;
	}
	~KesMem(){
		delete[] s;
		delete[] v;
		delete[] w;
		delete[] data;
		cout<<"Objekat unisten"<<endl<<"Kraj rada";
	}
};
int main(){
	KesMem km=KesMem(10);
	while(1){
		int m;
		cout<<"1. Citanje iz Kes memorije"<<endl<<"2. Izlaz"<<endl;
		cin>>m;
		if(m==1){
			string adresa;
			cout<<"Unesite adresu sa koje hocete da citate"<<endl;
			cin>>adresa;
			if(km.vecPostoji(adresa)){
				cout<<"HIT citanje iz kes memorije"<<endl;
				cout<<"Podatak koji se nalazi na adresi "<<adresa<<" je "<<km.citanjeIzKesa(adresa)<<endl;
				cout<<"Sadrzaj tag dela kes memorije"<<endl;
				km.stampa();
			}
			else{
				cout<<"MISS"<<endl;
				km.staviUkes(adresa);
				cout<<"Citanje sa diska..."<<endl;
				km.puniMemoriju(adresa);
				cout<<"Citanje sa diska zavrseno."<<endl;
				cout<<"Podatak koji se nalazi na adresi "<<adresa<<" je "<<km.citanjeIzKesa(adresa)<<endl;
				cout<<"Sadrzaj tag dela kes memorije"<<endl;
				km.stampa();
			}
		}
		else
			break;
	}
	getchar();
	return 0; 
}
