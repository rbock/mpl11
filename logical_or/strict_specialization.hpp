#include <boost/mpl11/detail/logical_or/strict_specialization.hpp>
template <typename ...xs>
using or_ = boost::mpl11::detail::logical_or::strict_specialization<xs...>;