#include <gtest.h>
#include "../lib_table_hash_list/hash_list.h"

TEST(THashList, can_create_hash_list) {
	ASSERT_NO_THROW(CHashTableList list);
}

TEST(THashList, can_insert_into_hash_list) {
	CHashTableList list;
	CPolynomial polynomial;
	ASSERT_NO_THROW(list.insert(polynomial));
	
}

TEST(THashList, can_find_in_hash_list) {
	CHashTableList list;
	CPolynomial polynomial;
	list.insert(polynomial);
	EXPECT_TRUE(list.contains(polynomial));
}

TEST(THashList, can_delete_from_hash_list) {
	CHashTableList list;
	CPolynomial polynomial;
	list.insert(polynomial);
	ASSERT_NO_THROW(list.remove(polynomial));
	EXPECT_FALSE(list.contains(polynomial));
}
