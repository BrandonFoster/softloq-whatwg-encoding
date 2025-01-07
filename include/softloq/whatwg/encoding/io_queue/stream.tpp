/**
 * @file stream.tpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Template implementation of the WHATWG encoding io queue streamclass.
 * @version 1.0.0 */

#include "softloq/whatwg/encoding/io_queue/stream.hpp"

namespace softloq::whatwg
{
// constructors //

template <class T> io_queue_stream<T>::io_queue_stream() noexcept
{
}
template <class T> io_queue_stream<T>::io_queue_stream(const std::initializer_list<T>& values) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    for (const auto& item: values) this->data.push_back(item);
}
template <class T> io_queue_stream<T>::io_queue_stream(const io_queue_stream& src) noexcept
: infra_list<io_queue_item<T>>(src)
{
}
template <class T> io_queue_stream<T>::io_queue_stream(io_queue_stream&& src) noexcept
: infra_list<io_queue_item<T>>(std::move(src))
{
}
template <class T> io_queue_stream<T>::~io_queue_stream() noexcept
{
}

//--------------//

// assignments //

template <class T> io_queue_stream<T>& io_queue_stream<T>::operator=(const io_queue_stream& src) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    std::lock_guard<std::mutex> src_lock(src.mtx);
    this->data = src.data;
    return *this;
}
template <class T> io_queue_stream<T>& io_queue_stream<T>::operator=(io_queue_stream&& src) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    std::lock_guard<std::mutex> src_lock(src.mtx);
    this->data = std::move(src.data);
    return *this;
}

//-------------//
}