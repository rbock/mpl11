#define BOOST_MPL11_NO_ASSERTIONS
#include <boost/mpl11/bool.hpp>
using boost::mpl11::true_;
using boost::mpl11::false_;


<% max_size = sequences.map(&:size).max %>
<%= [*HEADERS.call(max_size)].map { |hdr| "#include #{hdr}" }.join("\n") %>
<% sequences.each do |xs| %>

    static_assert(<%= OR[xs] %>::value == <%= xs.any? %>, "");

<% end %>
