
#ifndef UNZIPPER_H_
#define UNZIPPER_H_

#include "Config.h"
#include "Zip.h"

namespace buf
{

class Unzipper
{
public:
    typedef std::vector<UInt8> container;
    typedef container::size_type size_type;
public:

    Unzipper(const char* data, size_type size)
    {
        Zip zip;
        m_size = zip.unzip(m_data, reinterpret_cast<Zip::const_pointer>(data), size);
    }

    Unzipper(const UInt8* data, size_type size)
    {
        Zip zip;
        m_size = zip.unzip(m_data, data, size);
    }

    inline const UInt8* operator & () const { return &m_data[0]; }
    inline size_type size() const { return m_size; }

private:
    container m_data;
    size_type m_size;
};

} // namespace buf

#endif // UNZIPPER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

