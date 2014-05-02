HEADERS = proc {
  ['<boost/mpl11/detail/left_folds/bounded.hpp>',
    '<boost/mpl11/list.hpp>']
}

FOLDL = -> (f, state, xs) {
  <<-EOS
  boost::mpl11::detail::left_folds::bounded<
      #{xs.size}, #{f}::type::apply, #{state}, boost::mpl11::list<#{xs.join(', ')}>
  >
  EOS
}
