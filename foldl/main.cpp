#define BOOST_MPL11_NO_ASSERTIONS

template <typename ...>
struct result { using type = result; };

struct f {
    using type = f;

    <% case strictness
        when 'lazy' %>

        template <typename state, typename x>
        struct apply
            : result<typename state::type, typename x::type>
        { };

    <% when 'strict' %>

        template <typename state, typename x>
        using apply = result<typename state::type, typename x::type>;

    <% end %>
};

struct state { using type = state; };

template <int ...>
struct x { using type = x; };

<%= implementation.includes(sequences.map(&:size).max).join("\n") %>
<% sequences.each_with_index do |xs, n| %>

    using <%= "go#{n}" %> = <%= implementation.go['f', 'state', xs] %>::type;

<% end %>
