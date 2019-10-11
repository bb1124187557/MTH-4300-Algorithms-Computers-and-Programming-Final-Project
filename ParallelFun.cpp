#include<omp.h>
typedef long int myint;

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
