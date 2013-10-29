/*!
 * @file
 * Forward declares `boost::mpl11::multiply`.
 */

#ifndef BOOST_MPL11_FWD_MULTIPLY_HPP
#define BOOST_MPL11_FWD_MULTIPLY_HPP

namespace boost { namespace mpl11 {
    /*!
     * @ingroup arithmetic_operators
     *
     * Returns `T1 * T2 * ...Tn`.
     */
    template <typename T1, typename T2, typename ...Tn>
    struct multiply;
}} // end namespace boost::mpl11

#endif // !BOOST_MPL11_FWD_MULTIPLY_HPP