/**
 * @file immediate.tpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Template implementation of the WHATWG encoding io queue immediate class.
 * @version 1.0.0 */

#include "softloq/whatwg/encoding/io_queue/immediate.hpp"

namespace softloq::whatwg
{
// constructors //

template <class T> io_queue_immediate<T>::io_queue_immediate() noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    this->data.push_back({});
}
template <class T> io_queue_immediate<T>::io_queue_immediate(const std::initializer_list<T>& values) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    for (const auto& item: values) this->data.push_back(item);
    this->data.push_back({});
}
template <class T> io_queue_immediate<T>::io_queue_immediate(const io_queue_immediate& src) noexcept
: infra_list<io_queue_item<T>>(src)
{
}
template <class T> io_queue_immediate<T>::io_queue_immediate(io_queue_immediate&& src) noexcept
: infra_list<io_queue_item<T>>(std::move(src))
{
}
template <class T> io_queue_immediate<T>::~io_queue_immediate() noexcept
{
}

//--------------//

// assignments //

template <class T> io_queue_immediate<T>& io_queue_immediate<T>::operator=(const io_queue_immediate& src) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    std::lock_guard<std::mutex> src_lock(src.mtx);
    this->data = src.data;
    return *this;
}
template <class T> io_queue_immediate<T>& io_queue_immediate<T>::operator=(io_queue_immediate&& src) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    std::lock_guard<std::mutex> src_lock(src.mtx);
    this->data = std::move(src.data);
    return *this;
}

//-------------//
}