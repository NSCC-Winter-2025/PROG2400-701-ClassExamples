#include "sorting.h"
#include "binary_search_tree.h"

void bubble_sort(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 2; i++) {
        for (auto j = 0; j < nums.size() - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                std::swap(nums[j], nums[j + 1]);
            }
        }
    }
}

void selection_sort(std::span<int> nums) {
    for (auto i = 0; i < nums.size() - 1; i++) {
        // find the smallest number
        auto lowest = i;
        for (auto j = i + 1; j < nums.size(); j++) {
            if (nums[j] < nums[lowest]) {
                lowest = j;
            }
        }

        if (nums[lowest] < nums[i]) {
            // put the lowest number where it should go
            std::swap(nums[lowest], nums[i]);
        }
    }
}

void insertion_sort(std::span<int> nums) {
    for (auto i = 1; i < nums.size(); i++) {
        // take the current value
        auto temp = nums[i];

        // shuffle values greater than ahead of this value
        auto j = i;
        for (; j > 0 && temp < nums[j - 1]; j--) {
            nums[j] = nums[j - 1];
        }

        // insert the value in the correct location
        nums[j] = temp;
    }
}

void shell_sort(std::span<int> nums) {
    // create gaps between elements
    for (auto gap = nums.size() / 2; gap > 0; gap /= 2) {
        // for each gap, perform the insertion sort on a subset
        for (auto start = 0; start < gap; start++) {
            // perform the insertion sort
            for (auto i = start + gap; i < nums.size(); i += gap) {
                // take the current value
                const auto temp = nums[i];

                // shuffle elements greater than ahead of the value
                auto j = i;
                for (; j >= gap && temp < nums[j - gap]; j -= gap) {
                    nums[j] = nums[j - gap];
                }

                // insert the current value
                nums[j] = temp;
            }
        }
    }
}

auto split(std::span<int> nums) {
    // choose the pivot point (could be any element)
    auto pivot = nums[0];

    // start searching for numbers less than and greater than the pivot
    auto left = 0;
    auto right = nums.size() - 1;

    while (left < right) {
        // search for element less than the pivot
        while (right > 0 && pivot < nums[right]) right--;

        // search for element greater than the pivot
        while (left < right && pivot >= nums[left]) left++;

        // if two were found out of place, swap them
        if (left < right && nums[left] != nums[right]) {
            std::swap(nums[left], nums[right]);
        }
    }

    // now move the pivot point to its location
    nums[0] = nums[right];
    nums[right] = pivot;

    return right;
}

void quick_sort(std::span<int> nums) {
    // assume the array sorted when there are 0 or 1 element in the array
    if (nums.size() <= 1) return;

    // choose a pivot point
    auto pivot = split(nums);

    // sort the left side of the pivot point
    quick_sort(nums.subspan(0, pivot));

    // sort the right side of the pivot point
    quick_sort(nums.subspan(pivot + 1, nums.size() - pivot - 1));
}

void bst_sort(std::span<int> nums) {
    BST bst;

    for (const auto num : nums) {
        bst.insert(num);
    }

    bst.save_array(nums);
}