#define BOOST_MPL11_NO_ASSERTIONS
<% max_size = sequences.map(&:size).max %>
<%= [*HEADERS.call(max_size)].map { |hdr| "#include #{hdr}" }.join("\n") %>

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

<% sequences.each_with_index do |xs, n| %>

    using <%= "go#{n}" %> = <%= FOLDR['f', 'state', xs] %>::type;

<% end %>
