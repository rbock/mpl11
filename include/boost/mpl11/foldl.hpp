/*!
 * @file
 * Defines `boost::mpl11::foldl`.
 */

#ifndef BOOST_MPL11_FOLDL_HPP
#define BOOST_MPL11_FOLDL_HPP

#include <boost/mpl11/fwd/foldl.hpp>

#include <boost/mpl11/apply.hpp>
#include <boost/mpl11/begin.hpp>
#include <boost/mpl11/deref.hpp>
#include <boost/mpl11/detail/conditional.hpp>
#include <boost/mpl11/end.hpp>
#include <boost/mpl11/equal.hpp>
#include <boost/mpl11/has_optimization.hpp>
#include <boost/mpl11/next.hpp>
#include <boost/mpl11/optimization.hpp>
#include <boost/mpl11/size.hpp>


namespace boost { namespace mpl11 {
    namespace foldl_detail {
        //! @todo Unroll this with a script.
        template <
            unsigned long long Size, typename Iter, typename State, typename F
        >
        struct unrolled_foldl_impl
            : unrolled_foldl_impl<
                Size - 1,
                typename next<Iter>::type,
                typename apply<F, State, typename deref<Iter>::type>::type,
                F
            >
        { };

        template <typename Iter, typename State, typename F>
        struct unrolled_foldl_impl<0, Iter, State, F> {
            using type = State;
        };

        template <typename Sequence, typename State, typename F>
        struct unrolled_foldl
            : unrolled_foldl_impl<
                size<Sequence>::value,
                typename begin<Sequence>::type,
                State, F
            >
        { };

        template <
            typename First, typename Last,
            typename State, typename F,
            bool = equal<First, Last>::value
        >
        struct normal_foldl_impl;

        template <typename First, typename Last, typename State, typename F>
        struct normal_foldl_impl<First, Last, State, F, false>
            : normal_foldl_impl<
                typename next<First>::type,
                Last,
                typename apply<F, State, typename deref<First>::type>::type,
                F
            >
        { };

        template <typename First, typename Last, typename State, typename F>
        struct normal_foldl_impl<First, Last, State, F, true> {
            using type = State;
        };

        template <typename Sequence, typename State, typename F>
        struct normal_foldl
            : normal_foldl_impl<
                typename begin<Sequence>::type,
                typename end<Sequence>::type,
                State, F
            >
        { };
    } // end namespace foldl_detail

    template <typename Sequence, typename State, typename F>
    struct foldl
        : detail::conditional<
            has_optimization<Sequence, optimization::O1_size>::value,
            foldl_detail::unrolled_foldl<Sequence, State, F>,
            foldl_detail::normal_foldl<Sequence, State, F>
        >::type
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FOLDL_HPP
