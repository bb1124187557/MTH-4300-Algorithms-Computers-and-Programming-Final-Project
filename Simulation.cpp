#include "timer4300.cpp"
#include "MartingaleAlgo.cpp"
#include "ParallelFun.cpp"
#include<fstream>
#include<iostream>
typedef long int myint;

void printToFile(std::string filename, long double *s, myint l,long double E){
 std::ofstream mfile;
 mfile.open(filename);
 for(myint i=0;i<l;++i){
 mfile<<i+1<<" "<<s[i]<<" "<<E<<std::endl;
 }
 mfile<<std::endl;
 mfile.close();
}

void simulation(int&n,double&a,double &p,int **seq){

	Timer4300 tm;
	int parallelResult;

	//double nonParaResult;
	std::cout<<"\nWe will now approximate the solution through repeated "
	         <<"simulations. \nHow many simulations would you like? ";

  int simulationTimes=0;

  // ask user for te simulations input
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

  //result of Non-Parallel Method
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
