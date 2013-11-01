/*!
 * @file
 * Forward declares `boost::mpl11::push_front`.
 */

#ifndef BOOST_MPL11_FWD_PUSH_FRONT_HPP
#define BOOST_MPL11_FWD_PUSH_FRONT_HPP

namespace boost { namespace mpl11 {
    /*!
     * @ingroup container_intrinsics
     *
     * Prepends an element at the beginning of a container.
     */
    template <typename Seq, typename Element>
    struct push_front;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_PUSH_FRONT_HPP
