extern "C" {
#include "sort.h"
}

#include <errno.h>
#include <stdio.h>

#include "gtest/gtest.h"

void print_array(int64_t *arr, size_t len) {
  printf("[");
  for (size_t i = 0; i < len; ++i) {
    if (i < len - 1) {
      printf("%ld, ", arr[i]);
    } else {
      printf("%ld", arr[i]);
    }
  }
  printf("]\n");
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
