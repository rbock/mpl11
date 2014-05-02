HEADERS = proc {
  '<boost/mpl11/detail/logical_or/lazy_naive_struct.hpp>'
}

OR = -> (xs) {
  "boost::mpl11::detail::logical_or::lazy_naive_struct<#{xs.join(',')}>"
}
