/**
 * @file immediate.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declaration of the WHATWG encoding io queue immediate class.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_IMMEDIATE_HPP
#define SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_IMMEDIATE_HPP

#include "softloq/whatwg/encoding/io_queue/base.hpp"

namespace softloq::whatwg
{
template <class T> class io_queue_immediate final: public io_queue_base<T>
{
public:
    // constructors //

    /** @brief Constructs an empty WHATWG io queue immediate. */
    io_queue_immediate() noexcept;
    /** 
     * @brief Constructs a WHATWG io queue immediate with an initializer list of values.
     * @param values The initializer list for the io queue immediate. */
    io_queue_immediate(const std::initializer_list<T>& values) noexcept;
    /** 
     * @brief Constructs a WHATWG io queue immediate from another io queue immediate.
     * @param values The io queue immediate that will be copied. */
    io_queue_immediate(const io_queue_immediate& src) noexcept;
    /** 
     * @brief Constructs a WHATWG io queue immediate from another io queue immediate.
     * @param values The io queue immediate that will be moved. */
    io_queue_immediate(io_queue_immediate&& src) noexcept;
    /** @brief Default destructor. */
    ~io_queue_immediate() noexcept;

    //--------------//

    // assignments //

    /** 
     * @brief Assigns the WHATWG io queue immediate from another io queue immediate.
     * @param values The io queue immediate that will be copied. */
    io_queue_immediate& operator=(const io_queue_immediate& src) noexcept;
    /** 
     * @brief Assigns the WHATWG io queue immediate from another io queue immediate.
     * @param values The io queue immediate that will be moved. */
    io_queue_immediate& operator=(io_queue_immediate&& src) noexcept;

    //-------------//
};
}

#include "softloq/whatwg/encoding/io_queue/immediate.tpp"

#endif