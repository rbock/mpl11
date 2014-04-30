#define BOOST_MPL11_NO_ASSERTIONS
#include <boost/mpl11/bool.hpp>
using boost::mpl11::true_;
using boost::mpl11::false_;


<%= implementation.includes.join("\n") %>

<% sequences.each do |xs| %>

    static_assert(<%= implementation.go[xs] %> ::value
                            ==
                        <%= xs.any? %>
    , "");

<% end %>
