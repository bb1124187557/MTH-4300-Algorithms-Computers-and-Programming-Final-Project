#include<iostream>
#include<vector>
#include<random>
#include<iomanip>
#include "timer4300.cpp"
#include "Gunplot.cpp"
#include "Simulation.cpp"
#include<omp.h>
#include<math.h>
#include<fstream>
typedef long int myint;
using namespace std;


bool isMatch(const vector<int>& mainV, const vector<int>& vec)
{
	for(int i=0; i<vec.size(); i++)
	{
		if(vec[i]!=mainV[i])
			return false;
	}
	return true;
}

double exactExpectedValue(double p,int n,vector<int>tempV){
	vector< vector<int> > v;

	double toss=0;
	int input;
	v.push_back(tempV);
	for(int i=0; i<n-1; i++)
	{
		tempV.erase(tempV.begin());
		v.push_back(tempV);
	}

	for(int i=0; i<v.size(); i++)
	{
		if(isMatch(v[0], v[i]))
		{
			int h=0;
			for(int j=0; j<v[i].size(); j++)
			{
				if(v[i][j]==1)
					h++;
			}
			toss+=(pow(1/p, h)*pow(1/(1-p), v[i].size()-h));
		}
	}
	return toss;
}

int coinValue(int p){
  std::random_device device;
  std::mt19937 generator(device());
  std::uniform_int_distribution<int> distribution(1,100);
  int n;
  n=distribution(generator);
  if(n<=p){
    return 1;
  }
  else{
    return 0;
  }
}

int countLen(int* seq,int p,int n){
  int newn;
  vector<int> vec;
  for(int i=0;i<n;++i){
    newn=coinValue(p);
    vec.push_back(newn);
  }
  int indicator=0;
  while(indicator==0){
    int size=vec.size();
    for(int j=0;j<n;++j){
      if(seq[j]!=vec[size-n+j]){
				//int total=0;
        indicator=1;
      }
    }
    if(indicator==1){
      newn=coinValue(p);
      vec.push_back(newn);
      indicator=0;
    }
    else{
      indicator=1;
    }

  }
  return vec.size();
}

double parallelfun(int n,double p,int simulationTimes, int*seq){
  int nTh;
  #pragma omp parallel
  {
    if(omp_get_thread_num()==0){
      nTh=omp_get_num_threads();
    }
  }
  double *newseq;
  newseq=new double[nTh];

  for(int i=0;i<nTh;++i){
    newseq[i]=0;
  }
  #pragma omp parallel num_threads(nTh)
  {
    int myId=omp_get_thread_num();
    int result;
    for(int i=0;i<simulationTimes/nTh;++i){
      result=countLen(seq,p*100,n);
      newseq[myId]=result+newseq[myId];
    }
    newseq[myId]=newseq[myId]*nTh/simulationTimes;
  }
  #pragma omp barrier
  double total=0;
  for(int j=0;j<nTh;++j){
    total+=newseq[j];
  }
	delete[] newseq;
  total=total/nTh;
  return total;
}

void printToFile(std::string filename, long double *s, myint l,long double E){
 std::ofstream mfile;
 mfile.open(filename);
 for(myint i=0;i<l;++i){
 mfile<<i+1<<" "<<s[i]<<" "<<E<<std::endl;
 }
 mfile<<std::endl;
 mfile.close();
}

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
/*
void simulation(int&n,double&a,double &p,int **seq){
	Timer4300 tm;
	int parallelResult;
	//double nonParaResult;
	std::cout<<"\nWe will now approximate the solution through repeated "
	         <<"simulations. \nHow many simulations would you like? ";
	int simulationTimes=0;
	std::cin >> simulationTimes;
	while(simulationTimes<=0){
		std::cout <<"Please re-enter the number of simulations."
							<<"It must be a positive integer.\n";
		std::cin >> simulationTimes;
	}
	int result=0;
	long double total=0.0;
	long double* t;
	t=new long double[simulationTimes];
// Non-Parallel Method
	std::cout<<"\n1) The simulations will first be produced through a "
					 <<"non-parallel method.\n";
  tm.start();
  for(int i=0;i<simulationTimes;++i){
    result=countLen(*seq,p*100,n);
    total=total+result;
		t[i]=total/(i+1);
  }
	tm.end();

	std::cout<<"\tExpected number of coin tosses: ";
	std::cout<<fixed<<setprecision(6)<<total/simulationTimes<<endl;
	//collect result from non-parallel;
	printToFile("result.txt",t,simulationTimes,a);
	//calculate error from simualtion;
  std::cout<<"\tError "<<fixed<<setprecision(6)<<a-total/simulationTimes<<endl;
  std::cout<<"\tTime taken: "<<fixed<<setprecision(3)<<tm.getTime()/1000
						<<" seconds."<<std::endl;

// Parallel Method
  std::cout<<"\n2) The simulations will now be produced through a "
					 <<"parallel method.\n";
  tm.start();
  parallelResult=parallelfun(n,p,simulationTimes,*seq);
	tm.end();
	std::cout<<"\tExpected number of coin tosses: ";
	std::cout<<fixed<<setprecision(6)<<parallelResult<<endl;

  std::cout<<"\tError: "<<fixed<<setprecision(6)<<(a-parallelResult)<<endl;
  std::cout<<"\tTime taken: "<<fixed<<setprecision(3)<<tm.getTime()/1000
					 <<" seconds."<<std::endl;
	delete[] t;

}
*/
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
