#include <boost/mpl11/detail/left_folds/until.hpp>
#include <boost/mpl11/list.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::detail::left_folds::until<
    boost::mpl11::is_empty,
    f::type::template apply,
    z,
    boost::mpl11::list<xs...>
>;