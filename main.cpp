#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iterator>
#include <ctime>

/*
Compile with C++14
> g++ -std=c++14 '/path/main.cpp' -o '/path/main'

You can fnid missing functions in 
Project "Function" on > https://github.com/i5heu/ttest/projects/1



*/
using namespace std;
using namespace std::chrono;

string lastcomand; // The last comand in the File
string lastwirte;  // Variable to wirte the lsat Comand by running



string choice(string tmp){

	string pre;
	
	
	if (tmp == "1"){
		pre = "time -f'%Uuser %Ssystem %Eelapsed %PCPU (%Xtext+%Ddata %Mmax)k%Iinputs+%Ooutputs (%Fmajor+%Rminor)pagefaults %Wswaps' " ;
	}
	else if (tmp == "2"){
		pre = "python ";
	}
	else if (tmp == "3"){
		pre = "python3 ";
	}
	else if (tmp == "4"){
		pre = "sh ";
	}
	else if(tmp == "5"){
		pre = "grep ";
	}
	else if(tmp == "6"){
		pre = "~/CODE/tmp/main ";
	}
	else if(tmp == "7"){
		pre = "python ~/CODE/tmp/main.py ";
	}
	else if(tmp == "8"){
		pre = "g++ -std=c++14 '~/CODE/tmp/main.cpp' -o '~/CODE/tmp/main'";
	}
	else if(tmp == "9"){
		
		  time_t rawtime;
		  struct tm * timeinfo;
		  char buffer[80];

		  time (&rawtime);
		  timeinfo = localtime(&rawtime);

		  strftime(buffer,80,"%dd-%mm-%Yy-%Ih%Mm%Ss",timeinfo);
		  string str(buffer);

		string pretmp;
		
		pre = "tar -czf '~/CODE/tmp-backup/tmp-backup-" + str + ".tar.gz'  '~/CODE/tmp/'  ";
	}
	else{
		cout << "\nFAIL\n";
		exit(0);
	}
	
	return pre;
}

void lastcomandread(){
	  
      istream_iterator<char> end_of_file;
      ifstream file("~/lastcomand.txt");
      string tmp (istream_iterator<char>(file>>noskipws), end_of_file) ;
      file.close();
      
      lastcomand = tmp;
      
	//strcpy(tmpc, tmp.c_str());

	}


void lastcomandwrite(){
	
	if (lastwirte == ""){
		cout << "nothing has changed" << endl;
	}
	else{
		ofstream out("~/lastcomand.txt");
		out << lastwirte;
		out.close();
		}
	}

int main(){
	lastcomandread();
	cout << "\033[0;36mlast command >>" << lastcomand << "\033[0m " << endl;
	
	string userinput;
	cout << "\033[95m[1]time [2]python [3]python3 [4]sh [5]grep [6]CODE/tmp C++ [7]CODE/tmp python [8]CODE/tmp C++ compile [9]CODE/tmp Backup\n>>\033[0m";
	string tmp1;
	getline(cin,tmp1);
	
	
	char tmpp[800]; 
	if ( tmp1 == "1" || tmp1 == "2" || tmp1 == "3" || tmp1 == "4" || tmp1 == "5" || tmp1 == "6" || tmp1 == "7" || tmp1 == "8" ){
		string tmp;
		tmp = choice(tmp1);
		cout << "\033[95mPlease enter the command you wont massure\n>>\033[0m";
		
		getline(cin,userinput);
		
		tmp += userinput;
		strcpy(tmpp, tmp.c_str());
	}
	else if ( tmp1 == "" ){
		strcpy(tmpp, lastcomand.c_str());
	}
	else if ( tmp1 == "9" ){
		cout << "ok";
		string tmp;
		tmp = choice(tmp1);
		tmp += userinput;
		strcpy(tmpp, tmp.c_str());
		}
	else{
		strcpy(tmpp, tmp1.c_str());
	}
	
	cout << "\033[95m\n\nBenchmark for:\n"<< tmpp << "\n\n";
	cout << "\nXXXXX program START XXXXX\033[0m\n ";
	
		// START CLOCK
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		system(tmpp);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		// ENDE CLOCK
	
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
	
	if ( tmp1 == "1" || tmp1 == "2" || tmp1 == "3" || tmp1 == "4" || tmp1 == "5" || tmp1 == "6" || tmp1 == "7" || tmp1 == "8" || tmp1 == "9"  ){
		
		cout << "Nothing has changed in LastComand";
	}
	else{
		lastwirte = string(tmpp);
		lastcomandwrite();
	}
	
	cout << "\033[95m\nXXXXX program  FINISH XXXXX";
    cout << "\n" << duration << " microseconds\n"; 
    cout << (duration/1000) << " miliseconds\n" ;
    cout << (duration/1000000) << " seconds\n\033[0m" ;
    return 0;
}
