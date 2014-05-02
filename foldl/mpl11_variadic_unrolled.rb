HEADERS = proc {
  '<boost/mpl11/detail/left_folds/variadic_unrolled.hpp>'
}

FOLDL = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::left_folds::variadic_unrolled<
      #{f}::type::apply, #{state}, #{xs.join(', ')}
  >
  EOS
}
