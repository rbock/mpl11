HEADERS = proc {
  '<boost/mpl11/detail/logical_or/strict_overload.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::strict_overload<#{xs.join(',')}>"
}
