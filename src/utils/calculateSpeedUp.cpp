#include "../../include/utils/calculateSpeedUp.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <numeric>

void saveScore(int score) {
    std::ofstream file("../../files/scores.txt", std::ios::app);
    if (file.is_open()) {
        file << score << '\n';
        std::cout << "Score saved\n";
        file.close();
    } else {
        std::cerr << "Error: Cannot open scores.txt\n";
    }
}

static void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> leftVec(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightVec(arr.begin() + mid + 1, arr.begin() + right + 1);

    size_t i = 0, j = 0;
    int k = left;

    while (i < leftVec.size() && j < rightVec.size()) {
        arr[k++] = (leftVec[i] <= rightVec[j]) ? leftVec[i++] : rightVec[j++];
    }

    while (i < leftVec.size()) arr[k++] = leftVec[i++];
    while (j < rightVec.size()) arr[k++] = rightVec[j++];
}

static void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSortParallel(std::vector<int>& arr, int numThreads) {
    if (numThreads <= 1) {
        mergeSort(arr, 0, arr.size() - 1);
        return;
    }

    std::vector<std::thread> threads;
    std::vector<int> boundaries;

    int chunkSize = arr.size() / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? arr.size() - 1 : (start + chunkSize - 1);
        boundaries.push_back(start);
        boundaries.push_back(end);
        threads.emplace_back(mergeSort, std::ref(arr), start, end);
    }

    for (auto& t : threads)
        t.join();

    // Merge sorted chunks sequentially
    int step = chunkSize;
    while (step < arr.size()) {
        for (int i = 0; i < arr.size(); i += 2 * step) {
            int mid = std::min(i + step - 1, (int)arr.size() - 1);
            int right = std::min(i + 2 * step - 1, (int)arr.size() - 1);
            if (mid < right)
                merge(arr, i, mid, right);
        }
        step *= 2;
    }
}

void testSpeedUp() {
    std::ifstream file("../../files/scores.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open scores.txt\n";
        return;
    }

    std::vector<int> scores;
    int num;
    while (file >> num) {
        scores.push_back(num);
    }
    file.close();

    if (scores.size() < 2) {
        std::cerr << "Not enough data for benchmarking.\n";
        return;
    }

    std::vector<int> scores1 = scores;
    std::vector<int> scores6 = scores;

    auto start1 = std::chrono::high_resolution_clock::now();
    mergeSortParallel(scores1, 1);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start6 = std::chrono::high_resolution_clock::now();
    mergeSortParallel(scores6, 6);
    auto end6 = std::chrono::high_resolution_clock::now();

    double t1 = std::chrono::duration<double>(end1 - start1).count();
    double t6 = std::chrono::duration<double>(end6 - start6).count();

    double speedup = t1 / t6;
    double efficiency = (speedup / 6) * 100;

    std::cout << "Tiempo con 1 hilo: " << t1 << "s\n";
    std::cout << "Tiempo con 6 hilos: " << t6 << "s\n";
    std::cout << "Speedup: " << speedup << "\n";
    std::cout << "Eficiencia: " << efficiency << "%\n";

    const double p = 0.80;
    double amdahl = 1 / ((1 - p) + (p / speedup));
    std::cout << "OverSpeedup estimado (Amdahl): " << amdahl << "\n";
}
