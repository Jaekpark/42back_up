#ifndef _FT_LEXICOGRAPHICAL_COMPARE_HPP
#define _FT_LEXICOGRAPHICAL_COMPARE_HPP

#include "../config.hpp"

_BEGIN_NAMESPACE_FT

/**
 * @brief lexicographical_compare
 * 두 구간의 대응되는 요소를 차례대로 비교하는 객체
 * 첫 번째 요소가 두 번째 요소보다 작으면 참
 * 첫 번째 요소가 두 번째 요소보다 크면 거짓
 * @code {.cpp}
 * if(*first1 < *first2) return true;
 * if(*first2 < *first1) return false;
 * return (first1 == last1) && (first2 != last2);
 * @endcode
 * 만약 같다면 구간 끝까지 반복한다.
 * 기본 설정된 비교 함수가 less인 경우,
 * 첫 번째 구간이 두 번째 구간보다 작아야 true를 반환하고,
 * 같을 경우 작지 않으므로 false를 반환한다.
 * 만약 첫 구간이 먼저 끝나고 두 번째 구간 값은 남은 경우 true를 반환한다.
 *
 * @tparam InputIterator1 : 첫 번째 구간의 반복자
 * @tparam InputIterator2 : 두 번째 구간의 반복자
 * @param first1          : 첫 번째 구간의 시작 반복자
 * @param last1           : 첫 번째 구간의 마지막 반복자
 * @param first2          : 두 번째 구간의 시작 반복자
 * @param last2           : 두 번째 구간의 마지막 반복자
 */
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }
  return (first1 == last1) && (first2 != last2);
}
template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first2, *first1)) return false;
  }
  return (first1 == last1) && (first2 != last2);
}
_END_NAMESPACE_FT
#endif