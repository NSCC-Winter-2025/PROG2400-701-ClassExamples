#ifndef _SORTING_H
#define _SORTING_H

#include <span>

void bubble_sort(std::span<int> nums);

void selection_sort(std::span<int> nums);

void insertion_sort(std::span<int> nums);

void shell_sort(std::span<int> nums);

auto split(std::span<int> nums);

void quick_sort(std::span<int> nums);

void bst_sort(std::span<int> nums);

#endif
