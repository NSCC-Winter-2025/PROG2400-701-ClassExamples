#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>

using clk = std::chrono::high_resolution_clock;

void track_time(auto desc, void (*f)(std::span<int>), std::span<int> nums) {
    auto start = clk::now();
    f(nums);
    const std::chrono::duration<double> elapsed = clk::now() - start;
    std::cout << std::setw(15) << desc << ": ";
    std::cout << "time " << elapsed.count() << "s\n";
}

void fill_array(std::span<int> nums) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<size_t> dist(1, nums.size());
    std::generate(nums.begin(), nums.end(), [&]() {
        return dist(rng);
    });
}

bool check_sort(std::span<int> nums) {
    for (size_t i = 0; i < nums.size() - 1; i++) {
        if (nums[i] > nums[i + 1]) return false;
    }
    return true;
}

void dump_array(const std::span<int> nums) {
    for (const auto num : nums) {
        std::cout << std::setw(3) << num;
    }
    std::cout << std::endl;
}

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

int main() {
    // int nums[] = {3, 6, 8, 10, 5, 9, 4, 7, 1, 2};
    // const int size = sizeof(nums) / sizeof(int);

    for (size_t len = 10; len <= 100000; len *= 10) {
        // std::cout << "Before sorting" << std::endl;
        // dump_array({nums, size});

        std::cout << "len: " << len << std::endl;
        auto nums = new int[len];

        //bubble_sort({nums, size});
        fill_array({nums, len});
        track_time("bubble_sort", bubble_sort, {nums, len});

        fill_array({nums, len});
        track_time("selection_sort", selection_sort, {nums, len});

        fill_array({nums, len});
        track_time("insertion_sort", insertion_sort, {nums, len});

        if (check_sort({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }
        // std::cout << "After sorting" << std::endl;
        // dump_array({nums, size});

        delete[] nums;
    }

    return 0;
}
