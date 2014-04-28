#include <boost/mpl11/detail/left_folds/bounded.hpp>
#include <boost/mpl11/list.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::detail::left_folds::bounded<
    sizeof...(xs), f::type::template apply, z, boost::mpl11::list<xs...>
>;