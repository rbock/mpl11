HEADERS = -> (n) {
  MPL::List.headers(n) + ["<boost/mpl/fold.hpp>"]
}

FOLDL = -> (f, state, xs) {
  "boost::mpl::fold<#{MPL::List.new(xs)}, #{state}, #{f}>"
}