/*!
 * @file
 * Forward declares `boost::mpl11::key_of`.
 */

#ifndef BOOST_MPL11_FWD_KEY_OF_HPP
#define BOOST_MPL11_FWD_KEY_OF_HPP

#include <boost/mpl11/dispatch.hpp>


namespace boost { namespace mpl11 {
    namespace tag { struct key_of; }

    /*!
     * @ingroup intrinsics
     *
     * Returns the key that _would_ be used for an element
     * in an @ref AssociativeSequence.
     */
    template <typename Sequence, typename Element>
    struct key_of
        : dispatch<tag::key_of, Sequence, Element>
    { };
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_KEY_OF_HPP