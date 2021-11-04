#include "CLI11.hpp"

#include <iostream>
#include <ctime>

int N = 4;
void dgemm_blas(double** a, double** b, double** c)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void dgemm_opt1(double** a, double** b, double** c)
{
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

double** allocate_memory()
{
    double** ptr = new double*[N];
    for (int count = 0; count < N; count++)
        ptr[count] = new double[N];
    return ptr;
}

void free_memory(double** ptr)
{
    for (int count = 0; count < N; count++)
        delete [] ptr[count];
    delete ptr;
}

void init_matrices(double** a, double** b)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            a[i][j] = std::rand()%9+1;
            b[i][j] = std::rand()%9+1;
        }
    }    
}

void show_matrices(double** a, double** b, double** c)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cout << a[i][j] << " ";
        }

        if(i == N/2)
        {
            std::cout << std::setw(3) << "*" << std::setw(4);
        }
        else {
            std::cout << std::setw(7);
        }
        
        for(int j = 0; j < N; j++)
        {
            std::cout << b[i][j] << " ";
        }
        if(i == N/2)
        {
            std::cout << std::setw(3) << "=" << std::setw(4);
        }
        else {
            std::cout << std::setw(7);
        }
        for(int j = 0; j < N; j++)
        {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    } 
}

int main(int argc, char **argv)
{
    CLI::App app{"App description"};
    app.add_option("-n", N, "Parameter");
    CLI11_PARSE(app, argc, argv);
    std::srand(std::time(nullptr));

    /* Выделение памяти под матрицы */
    double** a = allocate_memory();
    double** b = allocate_memory();
    double** c = allocate_memory();

    /* Инициализация матриц значениями */
    init_matrices(a, b);

    /* Умножение матриц */
    //dgemm_opt1(a, b, c);

    unsigned int time;

    time = - clock ();

        dgemm_opt1 (a, b, c);

    time += clock ();

    printf ("%d\n", time);


    /* Вывод результата */
    //show_matrices(a, b, c);

    /* Освобождение памяти */
    free_memory(a);
    free_memory(b);
    free_memory(c);

    return 0;
}
