/**
 * @file base.tpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Template implementation of the WHATWG encoding io queue base class.
 * @version 1.0.0 */

#include "softloq/whatwg/encoding/io_queue/base.hpp"

namespace softloq::whatwg
{
// constructors //

template <class T> io_queue_base<T>::~io_queue_base() noexcept
{
}

//--------------//

// WHATWG io queue base member functions //

template <class T> io_queue_base<T>::value_type io_queue_base<T>::read_item() noexcept
{
    std::unique_lock<std::mutex> lock(this->mtx);
    read_cv.wait(lock, [&] { return !this->data.empty(); });
    auto item = this->data.front();
    if (!item.is_end_of_queue()) this->data.pop_front();
    return item;
}
template <class T> io_queue_base<T>::list_type io_queue_base<T>::read_items(const size_type count) noexcept
{
    list_type items;
    for (size_type i = 0; i < count; ++i)
    {
        const auto item = read_item();
        if (item.is_end_of_queue()) break;
        items.append(item);
    }
    return items;
}
template <class T> io_queue_base<T>::list_type io_queue_base<T>::peek_items(const size_type count) const noexcept
{
    std::unique_lock<std::mutex> lock(this->mtx);
    read_cv.wait(lock, [&] { return this->data.size() >= count || (!this->data.empty() && this->data.back().is_end_of_queue()); });
    list_type prefix;
    auto it = this->data.cbegin();
    for (size_type i = 0; i < count; ++i)
    {
        if (it->is_end_of_queue()) break;
        prefix.append(*it);
        ++it;
    }
    return prefix;
}

template <class T> void io_queue_base<T>::push_item(const value_type& item) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    if (!this->data.empty() && this->data.back().is_end_of_queue())
    {
        if (item.is_end_of_queue()) return;
        this->data.insert(--(this->data.cend()), item);
    }
    else this->data.push_back(item);
    read_cv.notify_one();
}
template <class T> void io_queue_base<T>::push_item(value_type&& item) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    if (!this->data.empty() && this->data.back().is_end_of_queue())
    {
        if (item.is_end_of_queue()) return;
        this->data.insert(--(this->data.cend()), std::move(item));
    }
    else this->data.push_back(std::move(item));
    read_cv.notify_one();
}
template <class T> void io_queue_base<T>::push_items(const infra_sequence<value_type>& items) noexcept
{
    for (const auto& item: items) push_item(item);
}
template <class T> void io_queue_base<T>::push_items(const infra_list<value_type>& items) noexcept
{
    for (const auto& item: items) push_item(item);
}

template <class T> void io_queue_base<T>::restore_item(const value_type& item) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    if (item.is_end_of_queue()) return;
    this->data.push_front(item);
    read_cv.notify_one();
}
template <class T> void io_queue_base<T>::restore_item(value_type&& item) noexcept
{
    std::lock_guard<std::mutex> lock(this->mtx);
    if (item.is_end_of_queue()) return;
    this->data.push_front(std::move(item));
    read_cv.notify_one();
}
template <class T> void io_queue_base<T>::restore_items(const infra_sequence<value_type>& items) noexcept
{
    for (auto it = items.crbegin(); it != items.crend(); ++it) restore_item(*it);
}
template <class T> void io_queue_base<T>::restore_items(const infra_list<value_type>& items) noexcept
{
    for (auto it = items.crbegin(); it != items.crend(); ++it) restore_item(*it);
}

//---------------------------------------//

// WHATWG list member function overrides //

template <class T> io_queue_base<T>::value_type& io_queue_base<T>::front() noexcept
{
    return list_type::front();
}
template <class T> const io_queue_base<T>::value_type& io_queue_base<T>::front() const noexcept
{
    return list_type::front();
}
template <class T> io_queue_base<T>::value_type& io_queue_base<T>::back() noexcept
{
    return list_type::back();
}
template <class T> const io_queue_base<T>::value_type& io_queue_base<T>::back() const noexcept
{
    return list_type::back();
}

template <class T> void io_queue_base<T>::append(const value_type& item) noexcept
{
    list_type::append(item);
}
template <class T> void io_queue_base<T>::append(value_type&& item) noexcept
{
    list_type::append(std::move(item));
}
template <class T> void io_queue_base<T>::pop_back() noexcept
{
    list_type::pop_back();
}

template <class T> void io_queue_base<T>::prepend(const value_type& item) noexcept
{
    list_type::prepend(item);
}
template <class T> void io_queue_base<T>::prepend(value_type&& item) noexcept
{
    list_type::prepend(std::move(item));
}
template <class T> void io_queue_base<T>::pop_front() noexcept
{
    list_type::pop_front();
}

template <class T> void io_queue_base<T>::extend(const infra_list<value_type>& list) noexcept
{
    list_type::extend(list);
}
template <class T> void io_queue_base<T>::extend(infra_list<value_type>&& list) noexcept
{
    list_type::extend(std::move(list));
}

template <class T> void io_queue_base<T>::replace(const value_type& item, const std::function<const bool (const value_type& item)>& cond) noexcept
{
    list_type::replace(item, cond);
}

template <class T> void io_queue_base<T>::insert(const size_type index, const value_type& item) noexcept
{
    list_type::insert(index, item);
}
template <class T> void io_queue_base<T>::insert(const size_type index, value_type&& item) noexcept
{
    list_type::insert(index, std::move(item));
}

template <class T> void io_queue_base<T>::remove(const value_type& item) noexcept
{
    list_type::remove(item);
}
template <class T> void io_queue_base<T>::remove_if(const std::function<const bool (const value_type& item)>& cond) noexcept
{
    list_type::remove_if(cond);
}

template <class T> void io_queue_base<T>::clear() noexcept
{
    list_type::clear();
}

template <class T> const bool io_queue_base<T>::contains(const value_type& item) const noexcept
{
    return list_type::contains(item);
}

//---------------------------------------//
}