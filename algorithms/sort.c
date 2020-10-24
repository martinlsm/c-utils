#include "sort.h"

#include <assert.h>
#include <errno.h>

static void quicksort_in_place_int64_helper(int64_t *arr_read,
                                            int64_t *arr_write, size_t len);

int quicksort_in_place_int64(int64_t *arr, size_t len) {
  if (arr == NULL && len > 0) {
    return EINVAL;
  }

  int64_t *sort_space = malloc(len * sizeof(int64_t));
  if (sort_space == NULL) {
    return ENOMEM;
  }

  quicksort_in_place_int64_helper(arr, sort_space, len);
  free(sort_space);

  return 0;
}

static void quicksort_in_place_int64_helper(int64_t *arr_read,
                                            int64_t *arr_write, size_t len) {
  if (len == 0) {
    return;
  }

  size_t lt_count = 0;
  size_t gt_count = 0;

  int64_t pivot = arr_read[0];
  for (size_t i = 1; i < len; ++i) {
    int64_t v = arr_read[i];

    if (v < pivot) {
      arr_write[lt_count] = v;
      lt_count += 1;
    } else {
      arr_write[len - 1 - gt_count] = v;
      gt_count += 1;
    }
  }

  assert(lt_count == len - 1 - gt_count);
  arr_write[lt_count] = pivot;

  quicksort_in_place_int64_helper(arr_write, arr_read, lt_count);
  quicksort_in_place_int64_helper(arr_write + lt_count + 1,
                                  arr_read + lt_count + 1, gt_count);
}
