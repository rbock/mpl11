HEADERS = proc {
  '<boost/mpl11/detail/right_folds/variadic_naive.hpp>'
}

FOLDR = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::right_folds::variadic_naive<
      #{f}::type::apply, #{state}, #{xs.join(', ')}
  >
  EOS
}
