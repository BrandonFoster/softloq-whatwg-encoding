/**
 * @file io_queue.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Declaration of the WHATWG encoding io queue class.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_HPP
#define SOFTLOQ_WHATWG_ENCODING_IO_QUEUE_HPP

#include "softloq/whatwg/encoding/lib_macro.hpp"

#include <softloq/whatwg/infra/structure/list.hpp>

#include <optional>

namespace softloq::whatwg
{
template <class T> class io_queue_item
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
    const bool operator==(const io_queue_item& b) const noexcept;

    //----------------------//

private:
    std::optional<T> item;
};
}

// output functions //

template <class T> std::ostream& operator<<(std::ostream& out, const softloq::whatwg::io_queue_item<T>& item) noexcept;

//------------------//

namespace softloq::whatwg
{
template <class T> class io_queue : public infra_list<io_queue_item<T>>
{
public:
    // constructors //

    virtual ~io_queue() noexcept = 0;

    //--------------//

    // WHATWG list member function overrides and deletes //

    T& front() noexcept = delete;
    const T& front() const noexcept = delete;
    T& back() noexcept = delete;
    const T& back() const noexcept = delete;

    void append(const T& item) noexcept;
    void append(T&& item) noexcept;
    void pop_back() noexcept;

    void prepend(const T& item) noexcept;
    void prepend(T&& item) noexcept;
    void pop_front() noexcept;

    void extend(const infra_list& list) noexcept;
    void extend(infra_list&& list) noexcept;

    void replace(const T& item, const std::function<const bool (const T& item)>& cond) noexcept;

    void insert(const size_type index, const T& item) noexcept;
    void insert(const size_type index, T&& item) noexcept;

    void remove(const T& item) noexcept;
    void remove_if(const std::function<const bool (const T& item)>& cond) noexcept;
    
    void clear() noexcept;

    const bool contains(const T& item) const noexcept;

    void sort_ascending() noexcept;
    void sort_descending() noexcept;
    
    //------------------//
};

template <class T> class io_queue_immediate : public io_queue<T>
{
public:
    // constructors //

    io_queue_immediate() noexcept;
    io_queue_immediate(const std::initializer_list<T>& values) noexcept;
    io_queue_immediate(const io_queue_immediate& src) noexcept;
    io_queue_immediate(io_queue_immediate&& src) noexcept;
    ~io_queue_immediate() noexcept;

    //--------------//

    // assignments //

    io_queue_immediate& operator=(const io_queue_immediate& src) noexcept;
    io_queue_immediate& operator=(io_queue_immediate&& src) noexcept;

    //-------------//
};

template <class T> class io_queue_stream : public io_queue<T>
{
public:
    // constructors //

    io_queue_stream() noexcept;
    io_queue_stream(const std::initializer_list<T>& values) noexcept;
    io_queue_stream(const io_queue_stream& src) noexcept;
    io_queue_stream(io_queue_stream&& src) noexcept;
    ~io_queue_stream() noexcept;

    //--------------//

    // assignments //

    io_queue_stream& operator=(const io_queue_stream& src) noexcept;
    io_queue_stream& operator=(io_queue_stream&& src) noexcept;

    //-------------//
};
}

#include "softloq/whatwg/encoding/io_queue.tpp"

#endif