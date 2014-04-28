#include <boost/mpl11/detail/left_folds/variadic.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::detail::left_folds::variadic<
    f::type::template apply, z, xs...
>;