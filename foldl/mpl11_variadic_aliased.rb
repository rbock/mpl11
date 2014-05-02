HEADERS = proc {
  '<boost/mpl11/detail/left_folds/variadic_aliased.hpp>'
}

FOLDL = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::left_folds::variadic_aliased<
      #{f}::type::apply, #{state}, #{xs.join(', ')}
  >
  EOS
}
