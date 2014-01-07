/*!
 * @file
 * Defines `boost::mpl11::Bitwise`.
 */

#ifndef BOOST_MPL11_BITWISE_HPP
#define BOOST_MPL11_BITWISE_HPP

#include <boost/mpl11/fwd/bitwise.hpp>

#include <boost/mpl11/detail/std_size_t.hpp>
#include <boost/mpl11/tag_of.hpp>


namespace boost { namespace mpl11 {
    template <typename T, typename Shift>
    struct shift_left : shift_left_c<T, Shift::value> {
#if defined(BOOST_MPL11_ENABLE_ASSERTIONS)
        static_assert(Shift::value >= 0,
        "Invalid usage of `shift_left` with a negative `Shift`.");
#endif
    };

    template <typename T, typename Shift>
    struct shift_right : shift_right_c<T, Shift::value> {
#if defined(BOOST_MPL11_ENABLE_ASSERTIONS)
        static_assert(Shift::value >= 0,
        "Invalid usage of `shift_right` with a negative `Shift`.");
#endif
    };

    template <typename T1, typename T2>
    struct bitand_impl
        : Bitwise<
            typename tag_of<T1>::type, typename tag_of<T2>::type
        >::template bitand_impl<T1, T2>
    { };

    template <typename T1, typename T2>
    struct bitor_impl
        : Bitwise<
            typename tag_of<T1>::type, typename tag_of<T2>::type
        >::template bitor_impl<T1, T2>
    { };

    template <typename T1, typename T2>
    struct bitxor_impl
        : Bitwise<
            typename tag_of<T1>::type, typename tag_of<T2>::type
        >::template bitxor_impl<T1, T2>
    { };

    template <typename T>
    struct compl_impl
        : Bitwise<typename tag_of<T>::type>::template compl_impl<T>
    { };

    template <typename T, typename Shift>
    struct shift_left_impl
        : shift_left_c<T, Shift::value>
    { };

    template <typename T, typename Shift>
    struct shift_right_impl
        : shift_right_c<T, Shift::value>
    { };

    template <typename T, detail::std_size_t Shift>
    struct shift_left_c_impl
        : Bitwise<typename tag_of<T>::type>::
          template shift_left_c_impl<T, Shift>
    { };

    template <typename T, detail::std_size_t Shift>
    struct shift_right_c_impl
        : Bitwise<typename tag_of<T>::type>::
          template shift_right_c_impl<T, Shift>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_BITWISE_HPP