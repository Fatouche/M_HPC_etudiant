#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>

#include <mpi.h>

using namespace std;

// no comment
int FibonacciMod42(int N)
{
    int f_curr = 0;
    int f_prec = 1;
    for (int i=1; i<=N; i++)
    {
        int tmp = f_curr;
        f_curr = (f_curr + f_prec) % 42;
        f_prec = tmp;
    }
    return f_curr;
}

// compute the integral of this function over [0,1] to approximate pi
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double fPi(double x)
{
    return 4.0 / (1.0 + x*x) + FibonacciMod42(x*10000);
}

// compute numericaly the integral of the function f over the domain [a,b] using step s
// FibonacciMod42(x*10000) -> otherwise, it would be too easy
double computeIntegral(function<double(double)>f, double a, double b, double s)
{
    double r = 0.0;
    unsigned h = 0;
    for (double x=a; x<b; x+=s, h++)
    {
        r += f(x);
        r -= FibonacciMod42(x*10000);
    }
    return r*(b-a)/double(h);
}

int main(int argc, char ** argv)
{
  // parse command line arguments
  double step = 1e-6;

  double allResults;
  int worldRank;
  int worldSize;
  double deb;
  double fin;
  double rep;
  
  if (argc < 2)
    {
      cout << "no step specified; using " << step << endl;
    }
  else
    {
      step = stod(argv[1]);
    }

  // compute 
  chrono::time_point<chrono::system_clock> t0 = chrono::system_clock::now();

  // initialise MPI
  MPI_Init(&argc, &argv);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &worldRank); 
  MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
  
  
  deb = (double)worldRank/(double)worldSize;
  fin = deb+1/(double)worldSize;
  
  rep = computeIntegral(fPi, deb, fin, step);  
 
  MPI_Reduce(&rep, &allResults, worldSize, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); 
  // termine les instructions MPI
  MPI_Finalize();

  chrono::time_point<chrono::system_clock> t1 = chrono::system_clock::now();
  chrono::duration<double> computationTime = t1 - t0;
  
  if(worldRank == 0){
    // display number of computing thread, result, computation time
    cout << worldSize << ' ' << allResults << ' ' << computationTime.count() << endl;
  }
  
  return 0;
}
