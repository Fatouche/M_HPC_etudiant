
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

// calcule le Nieme terme de la suite de "Fibonacci modulo 42"
// precondition : N >= 0
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

void calculeThread(std::vector<int> & data, int N, int N1){
   for (int i = N; i < N1; i=i+2)
    {
      data[i] = FibonacciMod42(i);
    }
}

int main(int argc, char ** argv)
{
    // verifie les arguments de la ligne de commande
    if (argc != 2)
    {
        std::cout << "usage: " << argv[0] << " <nbData>" << std::endl;
        return -1;
    }

    // cree le tableau de donnees a calculer
    int nbData = std::stoi(argv[1]);
    std::vector<int> data(nbData);

    std::chrono::time_point<std::chrono::system_clock> startTime
        = std::chrono::system_clock::now();

    // creation 2 threads
    std::thread thread1(calculeThread,std::ref(data), 0, nbData);
    std::thread thread2(calculeThread,std::ref(data), 1, nbData);
    
    // calcule le tableau de donnees 
	// TODO
   
    thread1.join();
    thread2.join();

    std::chrono::time_point<std::chrono::system_clock> endTime
        = std::chrono::system_clock::now();

    std::chrono::duration<double> nbSeconds = endTime - startTime;

    std::cout << "temps de calcul = " << nbSeconds.count() << std::endl;
    
    // ecrit les donnees calculees dans un fichier
    std::ofstream ofs("output.txt");
    for (int x : data)
    {
        ofs << x << ' ';
    }

    return 0;
}

