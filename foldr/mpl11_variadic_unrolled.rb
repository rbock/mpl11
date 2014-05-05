HEADERS = proc {
  '<boost/mpl11/detail/right_folds/variadic_unrolled.hpp>'
}

FOLDR = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::right_folds::variadic_unrolled<
      #{f}::type::apply, #{state}, #{xs.join(', ')}
  >
  EOS
}
