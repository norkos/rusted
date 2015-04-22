#pragma once

#include <stdexcept>
#include <vector>

#include "Networking/Bytes.hpp"

namespace Cake
{
namespace Networking
{
namespace Protocol
{

class Integer
{
public:
    using UnderlayingType = int;
    static const size_t size = sizeof(UnderlayingType);

    Integer()
    {
    }

    Integer(UnderlayingType value) : m_value(value)
    {
    }

    Integer & operator = (UnderlayingType value)
    {
        m_value = value;
        return *this;
    }

    int operator * () const
    {
        return m_value;
    }

    bool operator == (Integer other) const
    {
        return **this == *other;
    }

    bool operator != (Integer other) const
    {
        return **this != *other;
    }

    auto encode() -> Bytes
    {
        return Bytes::from(m_value);
    }

    auto decode(const Bytes & bytes) -> size_t
    {
        if (bytes.size() == size)
        {
            m_value = bytes.as<UnderlayingType>();
            return 0;
        }
        else if (bytes.size() == 0)
        {
            return size;
        }
        else
        {
            throw std::runtime_error("");
        }
    }

private:
    UnderlayingType m_value = {};
};

inline std::ostream & operator << (std::ostream & os, const Integer & value)
{
    return os << *value;
}

template<class T>
class Sequence
{
public:
    using UnderlayingContainer = std::vector<T>;

    Sequence()
    {
    }

    Sequence(std::initializer_list<T> value) : m_value(value)
    {
    }

    bool operator == (const Sequence<T> & other) const
    {
        return m_value == other.m_value;
    }

    bool operator != (const Sequence<T> & other) const
    {
        return m_value != other.m_value;
    }

    auto encode() -> Bytes
    {
        return Integer(m_value.size()).encode();
    }

    auto decode(const Bytes & bytes) -> size_t
    {
        T dummyItem;
        const auto expectedSizeByItem = dummyItem.decode(Bytes{});

        if (m_itemsToDecode == 0)
        {
            Integer size;
            size.decode(bytes);
            m_itemsToDecode = *size;

            return expectedSizeByItem;
        }
        else
        {
            m_itemsToDecode--;
            T item;
            auto sizeLeft = item.decode(bytes);
            m_value.push_back(item);

            if (sizeLeft > 0)
            {
                return sizeLeft;
            }
            else if (m_itemsToDecode > 0)
            {
                return expectedSizeByItem;
            }
            else
            {
                return 0;
            }
        }
    }

    auto begin() -> typename UnderlayingContainer::iterator
    {
        return m_value.begin();
    }

    auto begin() const -> typename UnderlayingContainer::const_iterator
    {
        return m_value.begin();
    }

    auto end() -> typename UnderlayingContainer::iterator
    {
        return m_value.end();
    }

    auto end() const -> typename UnderlayingContainer::const_iterator
    {
        return m_value.end();
    }

    auto empty() const -> bool
    {
        return m_value.empty();
    }

private:
    size_t m_itemsToDecode = 0;
    UnderlayingContainer m_value;
};

template<class T>
inline std::ostream & operator << (std::ostream & os, const Sequence<T> & value)
{
    if (value.empty())
    {
        os << "(empty)";
    }
    else for (const auto & item : value)
    {
        os << item << " ";
    }

    return os;
}

} // namespace Protocol
} // namespace Networking
} // namespace Cake