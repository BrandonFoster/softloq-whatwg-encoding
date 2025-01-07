/**
 * @file stream.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declaration of the WHATWG encoding io queue stream class.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_STREAM_HPP
#define SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_STREAM_HPP

#include "softloq/whatwg/encoding/io_queue/base.hpp"

namespace softloq::whatwg
{
template <class T> class io_queue_stream final: public io_queue_base<T>
{
public:
    // constructors //

    /** @brief Constructs an empty WHATWG io queue stream. */
    io_queue_stream() noexcept;
    /** 
     * @brief Constructs a WHATWG io queue stream with an initializer list of values.
     * @param values The initializer list for the io queue stream. */
    io_queue_stream(const std::initializer_list<T>& values) noexcept;
    /** 
     * @brief Constructs a WHATWG io queue stream from another io queue stream.
     * @param values The io queue stream that will be copied. */
    io_queue_stream(const io_queue_stream& src) noexcept;
    /** 
     * @brief Constructs a WHATWG io queue stream from another io queue stream.
     * @param values The io queue stream that will be moved. */
    io_queue_stream(io_queue_stream&& src) noexcept;
    /** @brief Default destructor. */
    ~io_queue_stream() noexcept;

    //--------------//

    // assignments //

    /** 
     * @brief Assigns the WHATWG io queue stream from another io queue stream.
     * @param values The io queue stream that will be copied. */
    io_queue_stream& operator=(const io_queue_stream& src) noexcept;
    /** 
     * @brief Assigns the WHATWG io queue stream from another io queue stream.
     * @param values The io queue stream that will be moved. */
    io_queue_stream& operator=(io_queue_stream&& src) noexcept;

    //-------------//
};
}

#include "softloq/whatwg/encoding/io_queue/stream.tpp"

#endif