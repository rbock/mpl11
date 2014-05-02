HEADERS = proc {
  '<boost/mpl11/detail/left_folds/variadic_naive.hpp>'
}

FOLDL = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::left_folds::variadic_naive<
      #{f}::type::apply, #{state}, #{xs.join(', ')}
  >
  EOS
}
