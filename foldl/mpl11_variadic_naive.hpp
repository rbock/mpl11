#include <boost/mpl11/detail/left_folds/variadic_naive.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::detail::left_folds::variadic_naive<
    f::type::template apply, z, xs...
>;