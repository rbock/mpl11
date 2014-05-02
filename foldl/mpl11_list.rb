HEADERS = proc { '<boost/mpl11/list.hpp>' }

FOLDL = -> (f, state, xs) {
  "boost::mpl11::foldl<#{f}, #{state}, boost::mpl11::list<#{xs.join(', ')}>>"
}
