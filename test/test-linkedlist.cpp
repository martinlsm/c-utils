extern "C" {
#include "linkedlist.h"
}

#include "gtest/gtest.h"

static int I1 = 1;
// static int I2 = 2;
// static int I3 = 3;
static void *DATA1 = &I1;
// static void *DATA2 = &I2;
// static void *DATA3 = &I3;

TEST(SinglyLinkedList, Create) {
  SinglyLinkedList *list = nullptr;
  ASSERT_FALSE(singly_linked_list_create(&list));
  ASSERT_NE(list, nullptr);
}

TEST(SinglyLinkedList, CreateAndDestroy) {
  SinglyLinkedList *list = nullptr;
  ASSERT_FALSE(singly_linked_list_create(&list));
  ASSERT_NE(list, nullptr);

  ASSERT_FALSE(singly_linked_list_destroy(&list));
  ASSERT_EQ(list, nullptr);
}

TEST(SinglyLinkedList, InitialLen) {
  SinglyLinkedList *list;
  singly_linked_list_create(&list);
  size_t len;
  ASSERT_FALSE(singly_linked_list_len(list, &len));
  ASSERT_EQ(len, 0);
}

TEST(SinglyLinkedList, PushBackOnce) {
  SinglyLinkedList *list;
  singly_linked_list_create(&list);

  ASSERT_FALSE(singly_linked_list_push_back(list, DATA1));
  size_t len;
  ASSERT_FALSE(singly_linked_list_len(list, &len));
  ASSERT_EQ(len, 1);

  void *data = nullptr;
  ASSERT_FALSE(singly_linked_list_get_first(list, &data));
  int elem = *((int*) data);
  ASSERT_EQ(elem, 1);
}
