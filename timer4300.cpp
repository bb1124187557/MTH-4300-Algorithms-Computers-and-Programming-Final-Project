
#include<chrono>
typedef long int myint;
typedef double mydouble;

class Timer4300{
private:
  myint timerStart;
  myint timerEnd;
  myint timerInProgress;
public:
  Timer4300(const myint & =0);
  void start();
  void end();
  mydouble getTime();
};
Timer4300::Timer4300(const myint & _inProgress){
  timerInProgress=_inProgress;
  if(timerInProgress==1){
    timerStart=std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
}
void Timer4300::start(){
  timerInProgress=1;
  timerStart=std::chrono::high_resolution_clock::now().time_since_epoch().count();
}
void Timer4300::end(){
  timerInProgress=2;
  timerEnd=std::chrono::high_resolution_clock::now().time_since_epoch().count();
}
mydouble Timer4300::getTime(){
  if(timerInProgress!=2){
    return -1.0;
  }
  mydouble fR= mydouble(timerEnd)-mydouble(timerStart);
  fR/= 1000000.0;
  return fR;
}
