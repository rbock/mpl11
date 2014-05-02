HEADERS = proc {
  '<boost/mpl11/detail/logical_or/strict_is_same.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::strict_is_same<#{xs.join(',')}>"
}
