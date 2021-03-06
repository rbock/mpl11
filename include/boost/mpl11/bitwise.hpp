/*!
 * @file
 * Defines the @ref Bitwise typeclass.
 *
 *
 * @copyright Louis Dionne 2014
 * Distributed under the Boost Software License, Version 1.0.
 *         (See accompanying file LICENSE.md or copy at
 *             http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MPL11_BITWISE_HPP
#define BOOST_MPL11_BITWISE_HPP

#include <boost/mpl11/fwd/bitwise.hpp>

#include <boost/mpl11/bool.hpp>
#include <boost/mpl11/core.hpp>
#include <boost/mpl11/detail/config.hpp>
#include <boost/mpl11/detail/left_folds/variadic.hpp>
#include <boost/mpl11/integer.hpp> // required by fwd/bitwise.hpp


namespace boost { namespace mpl11 {
    template <typename Left, typename Right, typename>
    struct Bitwise : false_ { };

    template <typename x1, typename x2, typename ...xn>
    struct bitand_
        : detail::left_folds::variadic<bitand_, x1, x2, xn...>
    { };

    template <typename x, typename y>
    struct bitand_<x, y> :
        Bitwise<
            typename datatype<typename x::type>::type,
            typename datatype<typename y::type>::type
        >::template bitand_impl<typename x::type, typename y::type>
    { };


    template <typename x1, typename x2, typename ...xn>
    struct bitor_
        : detail::left_folds::variadic<bitor_, x1, x2, xn...>
    { };

    template <typename x, typename y>
    struct bitor_<x, y> :
        Bitwise<
            typename datatype<typename x::type>::type,
            typename datatype<typename y::type>::type
        >::template bitor_impl<typename x::type, typename y::type>
    { };


    template <typename x1, typename x2, typename ...xn>
    struct bitxor
        : detail::left_folds::variadic<bitxor, x1, x2, xn...>
    { };

    template <typename x, typename y>
    struct bitxor<x, y> :
        Bitwise<
            typename datatype<typename x::type>::type,
            typename datatype<typename y::type>::type
        >::template bitxor_impl<typename x::type, typename y::type>
    { };

    namespace bitwise_detail {
        template <typename x, typename n>
        struct lshift_checks {
            static_assert(n::type::value >= 0,
            "Invalid usage of `shift_left` with a negative shift.");
        };

        template <typename x, typename n>
        struct rshift_checks {
            static_assert(n::type::value >= 0,
            "Invalid usage of `shift_right` with a negative shift.");
        };
    }

    template <typename x, typename n>
    struct shift_left :
        BOOST_MPL11_IF_ASSERTIONS(bitwise_detail::lshift_checks<x, n>,)
        Bitwise<typename datatype<typename x::type>::type>::
        template shift_left_impl<typename x::type, n>
    { };

    template <typename x, typename n>
    struct shift_right :
        BOOST_MPL11_IF_ASSERTIONS(bitwise_detail::rshift_checks<x, n>,)
        Bitwise<typename datatype<typename x::type>::type>::
        template shift_right_impl<typename x::type, n>
    { };

    template <typename x>
    struct compl_ :
        Bitwise<typename datatype<typename x::type>::type>::
        template compl_impl<typename x::type>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_BITWISE_HPP
