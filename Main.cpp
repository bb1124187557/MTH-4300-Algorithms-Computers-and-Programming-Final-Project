#include<iostream>
#include<vector>
#include<random>
#include<iomanip>
//#include "timer4300.cpp"
#include "Gunplot.cpp"
#include "Simulation.cpp"

#include<math.h>

typedef long int myint;
using namespace std;

void outputResult(int&n,double&a,double &p,vector<int> &v){
	// Finding and printing theoretical expected number of tosses
	a=exactExpectedValue(p,n,v);
	std::cout <<"\n\n-----------------------------------------"
						<<"----------------------" << '\n';
	std::cout<<"The theoretical expected number of tosses is: ";
	std::cout<<fixed<<setprecision(6)<<a<<" tosses"<<endl;
	std::cout <<"----------------------------------------------"
						<<"-----------------" << '\n';
}

int main(){
// Set up and user inputs
  vector<int> tempV;
	int* seq;
  int n=-1;
  double p=-1.0;
	double ExpectedValue;
	char choice;
	do{
	std::cout<<"\n  - Menu Options - \n"
	         <<"\nY:Automatically generate inputs"
					 <<"\nN:User Self Inputs"
					 <<"\nT:Terminate Program"<<endl;

	std::cin>>choice;
	choice|=0x20;

	if(choice=='y'){
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<int> distribution(1,99);
		p=distribution(generator)/100.0;
		std::cout <<"\nProbability of Heads: "<< p << '\n';
		distribution.param(std::uniform_int_distribution<int>::param_type(1,10));
		n=distribution(generator);
		std::cout << "Length of sequence: "<< n << " tosses\n";
		distribution.param(std::uniform_int_distribution<int>::param_type(0,1));
	  seq=new int[n];
		std::cout << "Sequence(H=1, T=0): ";
		for(int i=0; i<n; ++i){
			seq[i] = distribution(generator);
			tempV.push_back(seq[i]);
			std::cout << seq[i] << ' ';
		}
		outputResult(n,ExpectedValue,p,tempV);
		simulation(n,ExpectedValue,p,&seq);
		delete[] seq;
		// Plotting the results;
		plot();

	}else if(choice=='n'){
		int n=-1;
		double p=-1.0;
	  std::cout<<"\nPlease enter the probability of obtaining heads:\n";
		std::cin>>p;
		while((p<=0)||(p>=1)){
			std::cout <<"Please re-enter the probability. "
								<<"It must be a number between 0 and 1,"
								<<"non-inclusive:\n";
			std::cin>>p;
		}
		std::cout<<"\nPlease enter the length of sequence:\n";
		std::cin>>n;
		while(n<0){
			std::cout <<"Please re-enter the length of sequence."
								<<"It must be a positive integer.\n";
			std::cin>>n;
		}
	  seq=new int[n];
		std::cout << '\n';
	  std::cout<<"Please enter the sequence (1 = Heads, 0 = Tails, "
						 <<"insert spaces in between tosses):\n";
	  for(int i=0;i<n;++i){
	    std::cin>>seq[i];
	    tempV.push_back(seq[i]);
	  }
		outputResult(n,ExpectedValue,p,tempV);
		simulation(n,ExpectedValue,p,&seq);
		delete[] seq;

		// Plotting the results;
		plot();

	}else if(choice =='t'){
		std::cout << "\nProgram terminating\n" << endl;
		//std::exit;
	}

}while(choice!='t');

	return 0;
}
