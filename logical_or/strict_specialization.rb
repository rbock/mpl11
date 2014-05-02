HEADERS = proc {
  '<boost/mpl11/detail/logical_or/strict_specialization.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::strict_specialization<#{xs.join(',')}>"
}
