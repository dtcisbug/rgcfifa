
#ifndef ZIPPER_H_
#define ZIPPER_H_

#include "Zip.h"

namespace buf
{

class Zipper
{
public:
    typedef std::vector<UInt8> container;
    typedef container::size_type size_type;

public:
    Zipper(const char* data, size_type size)
    {
        Zip zip;
        m_size = zip.zip(m_data, reinterpret_cast<Zip::const_pointer>(data), size, Zip::LEVEL_BEST);
    }

    Zipper(const UInt8* data, size_type size)
    {
        Zip zip;
        m_size = zip.zip(m_data, data, size, Zip::LEVEL_BEST);
    }

    ~Zipper()
    {
        if (m_size)
            m_data.clear();
    }

    inline const UInt8* operator&() const { return &m_data[0]; }
    inline size_type size() const { return m_size; }

private:
    container m_data;
    size_type m_size;
};

} // namespace buf

#endif // ZIPPER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

