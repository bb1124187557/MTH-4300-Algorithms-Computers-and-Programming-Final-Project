#include<iostream>
using namespace std;

class gnuplot{
public:
  gnuplot();
  ~gnuplot();
  void operator () (const string & command);
private:
  FILE *gnuplotpipe;
};
gnuplot::gnuplot(){
  gnuplotpipe=popen("gnuplot -persist","w");
  if(!gnuplotpipe)
  cerr<<("Gnuplot not found!");
}
gnuplot::~gnuplot(){
  fprintf(gnuplotpipe,"exit\n");
  pclose(gnuplotpipe);
}
void gnuplot::operator() (const string & command){
  fprintf(gnuplotpipe,"%s\n",command.c_str());
  fflush(gnuplotpipe);
}

void plot(){
	gnuplot p;
  p("set grid");
  p("set title \"Theoretical Expectation Vs. Simulation.\" ");
  p("set xlabel \"Number of Simulations\" ");
  p("set ylabel \"Expected Number of Tosses\" ");
  p("plot \'./result.txt\' using 1:2 with lines title "
	" \"Simulation Expection\",\'./result.txt\'using 1:3 with lines title "
	"\"Expected Value\" ");
}
