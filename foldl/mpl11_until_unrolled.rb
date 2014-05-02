HEADERS = proc {
  ['<boost/mpl11/detail/left_folds/until_unrolled.hpp>',
   '<boost/mpl11/list.hpp>']
}

FOLDL = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::left_folds::until_unrolled<
      boost::mpl11::is_empty, #{f}::type::apply, #{state},
      boost::mpl11::list<#{xs.join(', ')}>
  >
  EOS
}
