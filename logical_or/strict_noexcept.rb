HEADERS = proc {
  '<boost/mpl11/detail/logical_or/strict_noexcept.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::strict_noexcept<#{xs.join(',')}>"
}
