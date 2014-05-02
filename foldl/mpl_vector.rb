HEADERS = -> (n) {
  MPL::Vector.headers(n) + ["<boost/mpl/fold.hpp>"]
}

FOLDL = -> (f, state, xs) {
  "boost::mpl::fold<#{MPL::Vector.new(xs)}, #{state}, #{f}>"
}