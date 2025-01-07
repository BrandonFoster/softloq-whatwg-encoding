/**
 * @file item.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declaration of the WHATWG encoding io queue item class.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_ITEM_HPP
#define SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_ITEM_HPP

#include "softloq/whatwg/encoding/lib_macro.hpp"

#include <optional>
#include <ostream>

namespace softloq::whatwg
{
template <class T> class io_queue_item final
{
public:
    // constructors //

    io_queue_item() noexcept;
    io_queue_item(const T& item) noexcept;
    io_queue_item(T&& item) noexcept;
    io_queue_item(const io_queue_item& src) noexcept;
    io_queue_item(io_queue_item&& src) noexcept;
    ~io_queue_item() noexcept;

    //--------------//

    // assignments //

    io_queue_item& operator=(const T& item) noexcept;
    io_queue_item& operator=(T&& item) noexcept;
    io_queue_item& operator=(const io_queue_item& src) noexcept;
    io_queue_item& operator=(io_queue_item&& src) noexcept;

    //-------------//

    // item member functions //

    T& value() noexcept;
    const T& value() const noexcept;

    const bool is_end_of_queue() const noexcept;

    //-----------------------//

    // comparison functions //

    const bool operator<(const io_queue_item& b) const noexcept;
    const bool operator>(const io_queue_item& b) const noexcept;
    const bool operator==(const io_queue_item& b) const noexcept;

    //----------------------//

private:
    std::optional<T> item;
};
}

// output functions //

template <class T> std::ostream& operator<<(std::ostream& out, const softloq::whatwg::io_queue_item<T>& item) noexcept;

//------------------//

#include "softloq/whatwg/encoding/io_queue/item.tpp"

#endif