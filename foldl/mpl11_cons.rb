HEADERS = proc {
  '<boost/mpl11/list.hpp>'
}

FOLDL = -> (f, state, xs) {
  cons = xs.foldr("boost::mpl11::list<>") { |x, tail|
    "boost::mpl11::cons<#{x}, #{tail}>"
  }

  return "boost::mpl11::foldl<#{f}, #{state}, #{cons}>"
}
