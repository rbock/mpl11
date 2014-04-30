#include <boost/mpl11/detail/logical_or/strict_noexcept.hpp>
template <typename ...xs>
using or_ = boost::mpl11::detail::logical_or::strict_noexcept<xs...>;