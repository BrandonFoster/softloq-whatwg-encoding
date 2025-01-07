/**
 * @file item.tpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Template implementation of the WHATWG encoding io queue item class.
 * @version 1.0.0 */

#include "softloq/whatwg/encoding/io_queue/item.hpp"

namespace softloq::whatwg
{
// constructors //

template <class T> io_queue_item<T>::io_queue_item() noexcept {}
template <class T> io_queue_item<T>::io_queue_item(const T& item) noexcept : item(item) {}
template <class T> io_queue_item<T>::io_queue_item(T&& item) noexcept : item(std::move(item)) {}
template <class T> io_queue_item<T>::io_queue_item(const io_queue_item& src) noexcept : item(src.item) {}
template <class T> io_queue_item<T>::io_queue_item(io_queue_item&& src) noexcept : item(std::move(src.item)) {}
template <class T> io_queue_item<T>::~io_queue_item() noexcept {}

//--------------//

// assignments //

template <class T> io_queue_item<T>& io_queue_item<T>::operator=(const T& item) noexcept { io_queue_item<T>::item = item; return *this; }
template <class T> io_queue_item<T>& io_queue_item<T>::operator=(T&& item) noexcept { io_queue_item<T>::item = std::move(item); return *this; }
template <class T> io_queue_item<T>& io_queue_item<T>::operator=(const io_queue_item& src) noexcept { item = src.item; return *this; }
template <class T> io_queue_item<T>& io_queue_item<T>::operator=(io_queue_item&& src) noexcept { item = std::move(src.item); return *this; }

//-------------//

// member functions //

template <class T> T& io_queue_item<T>::value() noexcept { return item.value(); }
template <class T> const T& io_queue_item<T>::value() const noexcept { return item.value(); }

template <class T> const bool io_queue_item<T>::is_end_of_queue() const noexcept { return !item.has_value(); }

//------------------//

// comparison functions //

template <class T> const bool io_queue_item<T>::operator<(const io_queue_item& b) const noexcept
{
    if (is_end_of_queue()) return false;
    else if (b.is_end_of_queue()) return true;
    else return value() < b.value();
}
template <class T> const bool io_queue_item<T>::operator>(const io_queue_item& b) const noexcept
{
    if (is_end_of_queue()) return false;
    else if (b.is_end_of_queue()) return true;
    else return value() > b.value();
}
template <class T> const bool io_queue_item<T>::operator==(const io_queue_item& b) const noexcept
{
    if (is_end_of_queue())
    {
        if (b.is_end_of_queue()) return true;
        else return false;
    }
    else if (b.is_end_of_queue()) return true;
    else return value() == b.value();
}

//----------------------//
}

// output functions //

template <class T> std::ostream& operator<<(std::ostream& out, const softloq::whatwg::io_queue_item<T>& item) noexcept { return item.is_end_of_queue() ? (out << "end-of-queue") : (out << item.value()); }

//------------------//