#include <boost/mpl11/detail/left_folds/variadic_aliased.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::detail::left_folds::variadic_aliased<
    f::type::template apply, z, xs...
>;