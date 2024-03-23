#include "matrix.h"
#include "test-helpers.h"

#include <gtest/gtest.h>

#define EXPECT_TRAIT(...) EXPECT_TRUE((__VA_ARGS__))

TEST(traits_test, member_types) {
  EXPECT_TRAIT(std::is_same_v<element, matrix<element>::value_type>);

  EXPECT_TRAIT(std::is_same_v<element&, matrix<element>::reference>);
  EXPECT_TRAIT(std::is_same_v<const element&, matrix<element>::const_reference>);

  EXPECT_TRAIT(std::is_same_v<element*, matrix<element>::pointer>);
  EXPECT_TRAIT(std::is_same_v<const element*, matrix<element>::const_pointer>);

  EXPECT_TRAIT(std::is_same_v<element*, matrix<element>::iterator>);
  EXPECT_TRAIT(std::is_same_v<const element*, matrix<element>::const_iterator>);

  EXPECT_TRAIT(std::is_same_v<element*, matrix<element>::row_iterator>);
  EXPECT_TRAIT(std::is_same_v<const element*, matrix<element>::const_row_iterator>);
}

TEST(traits_test, iterator_categories) {
  EXPECT_TRAIT(std::contiguous_iterator<matrix<element>::iterator>);
  EXPECT_TRAIT(std::contiguous_iterator<matrix<element>::const_iterator>);

  EXPECT_TRAIT(std::contiguous_iterator<matrix<element>::row_iterator>);
  EXPECT_TRAIT(std::contiguous_iterator<matrix<element>::const_row_iterator>);

  EXPECT_TRAIT(std::random_access_iterator<matrix<element>::col_iterator>);
  EXPECT_TRAIT(std::random_access_iterator<matrix<element>::const_col_iterator>);
}

TEST(traits_test, range_categories) {
  EXPECT_TRAIT(std::ranges::contiguous_range<matrix<element>>);
  EXPECT_TRAIT(std::ranges::contiguous_range<const matrix<element>>);
}

TEST(traits_test, col_iterator_member_types) {
  using col_iterator = matrix<element>::col_iterator;
  using const_col_iterator = matrix<element>::const_col_iterator;

  EXPECT_TRAIT(std::is_same_v<element, col_iterator::value_type>);
  EXPECT_TRAIT(std::is_same_v<element&, col_iterator::reference>);
  EXPECT_TRAIT(std::is_same_v<element*, col_iterator::pointer>);
  EXPECT_TRAIT(std::is_same_v<std::ptrdiff_t, col_iterator::difference_type>);
  EXPECT_TRAIT(std::is_same_v<std::random_access_iterator_tag, col_iterator::iterator_category>);

  EXPECT_TRAIT(std::is_same_v<element, const_col_iterator::value_type>);
  EXPECT_TRAIT(std::is_same_v<const element&, const_col_iterator::reference>);
  EXPECT_TRAIT(std::is_same_v<const element*, const_col_iterator::pointer>);
  EXPECT_TRAIT(std::is_same_v<std::ptrdiff_t, const_col_iterator::difference_type>);
  EXPECT_TRAIT(std::is_same_v<std::random_access_iterator_tag, const_col_iterator::iterator_category>);
}

TEST(traits_test, iterator_triviality) {
  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::iterator>);
  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::const_iterator>);

  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::row_iterator>);
  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::const_row_iterator>);

  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::col_iterator>);
  EXPECT_TRAIT(std::is_trivial_v<matrix<element>::const_col_iterator>);
}
