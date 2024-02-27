#include <vector>
#include <thread>
#include <fstream>
#include <chrono>
#include <iostream>

void saveScore(int score)
{
    std::ofstream fileScore("../files/scores.txt", std::ios::app);
    fileScore << score << std::endl;
    printf("Score saved\n");
    fileScore.close();
}

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSortPorPartes(std::vector<int> &arr, int inf, int sup)
{
    if (inf < sup)
    {
        int mid = inf + (sup - inf) / 2;
        mergeSortPorPartes(arr, inf, mid);
        mergeSortPorPartes(arr, mid + 1, sup);
        merge(arr, inf, mid, sup);
    }
}

void mergeSortConHilos(std::vector<int> &arr, int numThreads)
{
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i)
    {
        threads.push_back(std::thread(mergeSortPorPartes, ref(arr), i * (arr.size() / numThreads), (i + 1) * (arr.size() / numThreads) - 1));
    }
    for (auto &t : threads)
    {
        t.join();
    }
}

void testSpeedUp()
{
    std::vector<int> arr;
    std::ifstream file("../files/scores.txt");
    int num;
    while (file >> num)
    {
        arr.push_back(num);
    }
    file.close();

    auto startSecuential = std::chrono::high_resolution_clock::now();
    int numThreads = 1;
    mergeSortConHilos(arr, numThreads);
    auto stopSecuential = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_1_thread = std::chrono::duration_cast<std::chrono::duration<double>>(stopSecuential - startSecuential);
    std::cout << "Tiempo de ejecución con 1 hilo: " << duration_1_thread.count() << " segundos" << std::endl;

    auto startParallel = std::chrono::high_resolution_clock::now();
    numThreads = 6;
    mergeSortConHilos(arr, numThreads);
    auto stopParallel = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_6_threads = std::chrono::duration_cast<std::chrono::duration<double>>(stopParallel - startParallel);
    std::cout << "Tiempo de ejecución con 6 hilos: " << duration_6_threads.count() << " segundos" << std::endl;
    // Speedup
    float speedup = duration_1_thread.count() / duration_6_threads.count();
    std::cout << "Speedup: " << speedup << std::endl;
    // Eficiencia
    std::cout << "Eficiencia: " << 100 * (speedup / numThreads) << std::endl;
    // OverSpeedup
    float overSpeedup = 1 / ((1 - 0.20) - (0.20 / speedup));
    std::cout << "OverSpeedup: " << overSpeedup << std::endl;
}