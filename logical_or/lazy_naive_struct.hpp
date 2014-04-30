#include <boost/mpl11/detail/logical_or/lazy_naive_struct.hpp>
template <typename ...xs>
using or_ = boost::mpl11::detail::logical_or::lazy_naive_struct<xs...>;