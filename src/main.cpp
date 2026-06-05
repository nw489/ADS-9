// Copyright 2022 NNTU-CS
#include "tree.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

void printPermutation(const std::vector<char>& perm) {
  for (char c : perm) {
    std::cout << c;
  }
  std::cout << std::endl;
}

void printAllPermutations(const std::vector<std::vector<char>>& perms) {
  for (const auto& perm : perms) {
    printPermutation(perm);
  }
}

int getRandomPermNumber(int total) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, total);
  return dis(gen);
}

int64_t factorial(int n) {
  if (n <= 1) return 1;
  int64_t result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<char> createTestVector(int size) {
  std::vector<char> result;
  for (int i = 0; i < size; ++i) {
    result.push_back('0' + i);
  }
  return result;
}

int main() {
  std::cout << "=== Генерация перестановок с использованием дерева "
            << "вариантов ===" << std::endl << std::endl;

  std::cout << "--- Задание 1: Построение дерева перестановок ---"
            << std::endl;
  std::vector<char> input1 = {'1', '2', '3'};
  PMTree tree1(input1);
  std::cout << "Дерево построено для набора: ";
  for (char c : input1) {
    std::cout << c << " ";
  }
  std::cout << std::endl << std::endl;

  std::cout << "--- Задание 2: Получение всех перестановок (getAllPerms) ---"
            << std::endl;
  std::vector<std::vector<char>> allPerms = getAllPerms(tree1);
  std::cout << "Все перестановки для {1, 2, 3}:" << std::endl;
  printAllPermutations(allPerms);
  std::cout << "Всего перестановок: " << allPerms.size() << std::endl
            << std::endl;

  std::cout << "--- Задание 3: Получение перестановки по номеру ---"
            << std::endl;
  std::cout << "Перестановка №1 (getPerm1): ";
  printPermutation(getPerm1(tree1, 1));

  std::cout << "Перестановка №2 (getPerm2): ";
  printPermutation(getPerm2(tree1, 2));

  std::cout << "Перестановка №6 (getPerm1): ";
  printPermutation(getPerm1(tree1, 6));

  std::cout << "Перестановка №8 (getPerm2, не существует): ";
  std::vector<char> result = getPerm2(tree1, 8);
  if (result.empty()) {
    std::cout << "(пустой вектор)" << std::endl;
  } else {
    printPermutation(result);
  }
  std::cout << std::endl;

  std::cout << "--- Задание 4: Вычислительный эксперимент ---" << std::endl;
  std::cout << "Измерение времени работы функций в зависимости от размера "
            << "алфавита" << std::endl << std::endl;

  std::ofstream timingFile("result/timing_data.txt");
  timingFile << "# n\t\tgetAllPerms(мкс)\tgetPerm1(мкс)\tgetPerm2(мкс)"
             << std::endl;

  for (int n = 3; n <= 10; ++n) {
    std::cout << "Тестирование n=" << n << "... ";
    std::cout.flush();

    std::vector<char> testInput = createTestVector(n);

    PMTree treeAll(testInput);
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> allPermsResult = getAllPerms(treeAll);
    auto end = std::chrono::high_resolution_clock::now();
    auto timeAllPerms = std::chrono::duration_cast<std::chrono::microseconds>(
                        end - start).count();

    PMTree treePerm1(testInput);
    int randomNum1 = getRandomPermNumber(allPermsResult.size());
    start = std::chrono::high_resolution_clock::now();
    getPerm1(treePerm1, randomNum1);
    end = std::chrono::high_resolution_clock::now();
    auto timePerm1 = std::chrono::duration_cast<std::chrono::microseconds>(
                     end - start).count();

    PMTree treePerm2(testInput);
    int randomNum2 = getRandomPermNumber(allPermsResult.size());
    start = std::chrono::high_resolution_clock::now();
    getPerm2(treePerm2, randomNum2);
    end = std::chrono::high_resolution_clock::now();
    auto timePerm2 = std::chrono::duration_cast<std::chrono::microseconds>(
                     end - start).count();

    timingFile << n << "\t\t" << timeAllPerms << "\t\t"
               << timePerm1 << "\t\t" << timePerm2 << std::endl;

    std::cout << "OK (getAllPerms: " << timeAllPerms << " мкс)" << std::endl;
  }

  timingFile.close();
  std::cout << std::endl;
  std::cout << "Данные сохранены в result/timing_data.txt" << std::endl;

  return 0;
}
