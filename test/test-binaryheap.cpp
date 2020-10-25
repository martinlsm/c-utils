extern "C" {
#include "binaryheap.h"
}

#include "gtest/gtest.h"

using namespace std;

static int compare_int(void *a, void *b) {
  return *((int*) b) - *((int*) a);
}

class BinaryHeapTest : public ::testing::Test {
protected:
  BinaryHeapTest() {
    int ret = binary_heap_create(&heap, &compare_int);
    if (ret) {
      cerr << "Failed to create heap" << endl;
      exit(1);
    }
  }

  ~BinaryHeapTest() {
    binary_heap_destroy(&heap);
  }

  BinaryHeap *heap;
  int a = 1;
  int b = 2;
  int c = 3;
};

TEST_F(BinaryHeapTest, SingleInsert) {
  int ret = binary_heap_insert(heap, &a);
  ASSERT_FALSE(ret);
}

TEST_F(BinaryHeapTest, InsertAndPeek) {
}
