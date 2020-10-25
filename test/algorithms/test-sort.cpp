extern "C" {
#include "sort.h"
}

#include <errno.h>

#include "gtest/gtest.h"

static bool adjacent_numbers_sorted(int64_t* arr, int64_t low, int64_t high) {
  size_t i = 0;
  int64_t e = low;
  while (e <= high) {
    if (arr[i] != e) {
      return false;
    }

    i += 1;
    e += 1;
  }

  return true;
}

static bool is_sorted(int64_t* arr, size_t len) {
  for (size_t i = 1; i < len; ++i) {
    if (arr[i] < arr[i - 1]) {
      return false;
    }
  }

  return true;
}

TEST(Sort, NullPointerAsArray) {
  int ret = quicksort_in_place_int64(NULL, 10);
  ASSERT_EQ(ret, EINVAL);

  ret = quicksort_in_place_int64(NULL, 0);
  ASSERT_EQ(ret, 0);
}

TEST(Sort, SingleElement) {
  int64_t arr[] = {1};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_EQ(arr[0], 1);
}

TEST(Sort, TwoElements) {
  int64_t arr[] = {2, 1};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(adjacent_numbers_sorted(arr, 1, 2));
}

TEST(Sort, ThreeElements) {
  int64_t arr[] = {3, 1, 2};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(adjacent_numbers_sorted(arr, 1, 3));
}

TEST(Sort, FiveElements) {
  int64_t arr[] = {5, 2, 1, 3, 4};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(adjacent_numbers_sorted(arr, 1, 5));
}

TEST(Sort, TenElements) {
  int64_t arr[] = {5, 10, 4, 1, 2, 7, 6, 8, 3, 9};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(adjacent_numbers_sorted(arr, 1, 10));
}

TEST(Sort, AlreadySorted) {
  int64_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(adjacent_numbers_sorted(arr, 1, 8));
}

TEST(Sort, RandomElements) {
  size_t arr_len = 100000;
  srand(1);
  int64_t arr[arr_len];
  for (size_t i = 0; i < arr_len; ++i) {
    arr[i] = (int64_t) rand();
  }
  int ret = quicksort_in_place_int64(arr, arr_len);
  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(is_sorted(arr, arr_len));
}

TEST(Sort, DontWriteToAdjacentMemory) {
  size_t mem_len = 1024;
  int64_t p[mem_len];
  memset(p, 0, mem_len * sizeof(int64_t));

  for (size_t i = mem_len / 4; i < 3 * mem_len / 4; ++i) {
    p[i] = i * 7901 % 31; // Fill with arbitrary data.
  }

  quicksort_in_place_int64(p + mem_len / 4, mem_len / 2);

  size_t i = 0;
  size_t j = 3 * mem_len / 4;
  for (size_t k = 0; k < mem_len / 4; ++k) {
    ASSERT_EQ(p[i], 0);
    ASSERT_EQ(p[j], 0);
    i += 1;
    j += 1;
  }
}
