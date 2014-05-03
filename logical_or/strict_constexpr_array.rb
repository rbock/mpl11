HEADERS = proc {
  '<boost/mpl11/detail/logical_or/strict_constexpr_array.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::strict_constexpr_array<#{xs.join(',')}>"
}
