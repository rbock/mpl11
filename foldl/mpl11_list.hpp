#include <boost/mpl11/list.hpp>
template <typename f, typename z, typename ...xs>
using foldl = boost::mpl11::foldl<
    f, z, boost::mpl11::list<xs...>
>;