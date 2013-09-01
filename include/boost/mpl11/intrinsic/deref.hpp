/*!
 * @file
 * Defines `boost::mpl11::intrinsic::deref`.
 */

#ifndef BOOST_MPL11_INTRINSIC_DEREF_HPP
#define BOOST_MPL11_INTRINSIC_DEREF_HPP

#include <boost/mpl11/detail/tag_dispatched.hpp>
#include <boost/mpl11/tags.hpp>


namespace boost { namespace mpl11 { namespace intrinsic {
    /*!
     * @ingroup intrinsic
     *
     * Dereferences an iterator.
     *
     *
     * @warning
     * Differences from the original MPL:
     * - No default implementation is provided.
     */
    template <typename Iterator>
    struct deref
        : detail::tag_dispatched<tag::deref, Iterator>::template
          with_default<>
    { };
}}} // end namespace boost::mpl11::intrinsic

#endif // !BOOST_MPL11_INTRINSIC_DEREF_HPP