/**
 * @file base.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declaration of the WHATWG encoding io queue base class.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_BASE_HPP
#define SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_BASE_HPP

#include "softloq/whatwg/encoding/io_queue/item.hpp"
#include "softloq/whatwg/infra/structure/list.hpp"
#include "softloq/whatwg/infra/structure/sequence.hpp"

namespace softloq::whatwg
{
template <class T> class io_queue_base: public infra_list<io_queue_item<T>>
{
public:
    // common member types //

    using list_type = infra_list<io_queue_item<T>>;
    using value_type = io_queue_item<T>;
    using size_type	= infra_list<io_queue_item<T>>::size_type;

    //---------------------//

    // constructors //

    virtual ~io_queue_base() noexcept = 0;

    //--------------//

    // WHATWG io queue base member functions //

    value_type read_item() noexcept;
    list_type read_items(const size_type count = 1) noexcept;
    list_type peek_items(const size_type count = 1) const noexcept;

    void push_item(const value_type& item) noexcept;
    void push_item(value_type&& item) noexcept;
    void push_items(const infra_sequence<value_type>& items) noexcept;
    void push_items(const infra_list<value_type>& items) noexcept;

    void restore_item(const value_type& item) noexcept;
    void restore_item(value_type&& item) noexcept;
    void restore_items(const infra_sequence<value_type>& items) noexcept;
    void restore_items(const infra_list<value_type>& items) noexcept;

    //---------------------------------------//

    // Conversions //

    // operator infra_list<value_type>() const noexcept;
    // operator infra_string() const noexcept;
    // operator infra_byte_sequence() const noexcept;

    //-------------//

private:
    mutable std::condition_variable read_cv;

    // WHATWG list member function overrides //

    value_type& front() noexcept override;
    const value_type& front() const noexcept override;
    value_type& back() noexcept override;
    const value_type& back() const noexcept override;

    void append(const value_type& item) noexcept override;
    void append(value_type&& item) noexcept override;
    void pop_back() noexcept override;

    void prepend(const value_type& item) noexcept override;
    void prepend(value_type&& item) noexcept override;
    void pop_front() noexcept override;

    void extend(const infra_list<value_type>& list) noexcept override;
    void extend(infra_list<value_type>&& list) noexcept override;

    void replace(const value_type& item, const std::function<const bool (const value_type& item)>& cond) noexcept override;

    void insert(const size_type index, const value_type& item) noexcept override;
    void insert(const size_type index, value_type&& item) noexcept override;

    void remove(const value_type& item) noexcept override;
    void remove_if(const std::function<const bool (const value_type& item)>& cond) noexcept override;

    void clear() noexcept override;

    const bool contains(const value_type& item) const noexcept override;
    
    //---------------------------------------//
};
}

#include "softloq/whatwg/encoding/io_queue/base.tpp"

#endif