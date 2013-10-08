/*!
 * @file
 * Defines `boost::mpl11::apply_wrap`.
 */

#ifndef BOOST_MPL11_FUNCTIONAL_APPLY_WRAP_HPP
#define BOOST_MPL11_FUNCTIONAL_APPLY_WRAP_HPP

#include <boost/mpl11/detail/nested_apply.hpp>
#include <boost/mpl11/empty_base.hpp>
#include <boost/mpl11/functional/apply_wrap_fwd.hpp>


namespace boost { namespace mpl11 {
namespace apply_wrap_detail {
    // We check that both `F::apply<Args...>` _and_ `F::apply<Args...>::type`
    // exist. This is necessary to make sure that we don't cause a hard error
    // in `apply_wrap` by inheriting from an incomplete type.
    //
    // Note that we don't instantiate `F::apply<Args...>::type` too early
    // because the signature is only instantiated when `apply_wrap` is
    // instantiated, which causes its nested `type` to be instantiated
    // anyway.
    template <typename F, typename ...Args>
    typename detail::nested_apply<F, Args...>::type pick(
        typename detail::nested_apply<F, Args...>::type::type*
    );

    // Otherwise, `apply_wrap` does not have a nested type `type`.
    template <typename F, typename ...Args>
    empty_base pick(...);
} // end namespace apply_wrap_detail

template <typename F, typename ...Args>
struct apply_wrap
    : decltype(apply_wrap_detail::pick<F, Args...>(nullptr))
{ };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FUNCTIONAL_APPLY_WRAP_HPP
