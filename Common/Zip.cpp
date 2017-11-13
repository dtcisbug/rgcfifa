
#include "Config.h"
#include "Zip.h"

namespace buf
{

Zip::Zip(const_pointer dict, size_type len)
    : m_adler(0)
{
    if (dict && len) {
        m_dict.insert(m_dict.begin(), dict, dict+len);
    }
}

Zip::~Zip()
{}

Zip::size_type Zip::zip(std::vector<data_type>& dst,
        const_pointer src, size_type srclen, leveltype_e level)
{
    if (!src || !srclen)
        return 0;

    m_stream.zalloc = 0;
    m_stream.zfree = 0;
    m_stream.opaque = 0;

    int ret = Z_OK;
    if (level > LEVEL_BEST || level <= LEVEL_NO)
        ret = deflateInit(&m_stream, LEVEL_DEFAULT/*LEVEL_6*/);
    else
        ret = deflateInit(&m_stream, level);

    if (ret != Z_OK)
        return 0;

    if (m_dict.size()) {
        if (deflateSetDictionary(&m_stream,
                    &m_dict[0], m_dict.size()) != Z_OK)
            return 0;
        m_adler = m_stream.adler;
    }

    size_type size = deflateBound(&m_stream, srclen);
    dst.resize(size);

    m_stream.next_in = const_cast<pointer>(src);
    m_stream.avail_in = srclen;

    while (m_stream.avail_in) {
        m_stream.next_out = &dst[m_stream.total_out];
        m_stream.avail_out = dst.size()-m_stream.total_out;

        ret = deflate(&m_stream, Z_FINISH);
        if (ret == Z_STREAM_END || ret == Z_MEM_ERROR)
            break;

        if (ret == Z_BUF_ERROR || !m_stream.avail_out) {
            dst.resize(dst.size() << 1);
        } else if (ret == Z_ERRNO
                || ret == Z_STREAM_ERROR
                || ret == Z_DATA_ERROR
                || ret == Z_VERSION_ERROR) {
            deflateEnd(&m_stream);
            return 0;
        }
    }

    deflateEnd(&m_stream);
    dst.resize(m_stream.total_out);
    return m_stream.total_out;
}

Zip::size_type Zip::unzip(
        std::vector<data_type>& dst, const_pointer src, size_type srclen)
{
    if (!src || !srclen)
        return 0;

    m_stream.zalloc = 0;
    m_stream.zfree = 0;
    m_stream.opaque = 0;

    if (inflateInit(&m_stream) != Z_OK)
        return 0;

#ifndef NDEBUG
    dst.resize(srclen << 1);
#else
    dst.resize(srclen << 2);
#endif

    m_stream.next_in = const_cast<pointer>(src);
    m_stream.avail_in = srclen;

    int ret = Z_OK;
    while (m_stream.avail_in) {
        m_stream.next_out = &dst[m_stream.total_out];
        m_stream.avail_out = dst.size()-m_stream.total_out;

        ret = inflate(&m_stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_END || ret == Z_MEM_ERROR)
            break;

        if (ret == Z_BUF_ERROR || !m_stream.avail_out) {
#ifndef NDEBUG
            dst.resize(dst.size() << 1);
#else
            dst.resize(dst.size() << 2);
#endif
        } else if (ret == Z_NEED_DICT) {
            if (m_dict.size()) {
                if (inflateSetDictionary(&m_stream,
                            &m_dict[0], m_dict.size()) != Z_OK)
                    return 0;
                if (m_stream.adler != m_adler)
                    return 0;
            }
        } else if (ret == Z_ERRNO
                || ret == Z_STREAM_ERROR
                || ret == Z_DATA_ERROR
                || ret == Z_VERSION_ERROR) {
            inflateEnd(&m_stream);
            return 0;
        }
    }

    inflateEnd(&m_stream);
    dst.resize(m_stream.total_out);
    return m_stream.total_out;
}

Zip::size_type Zip::zip(pointer* dst, const_pointer src, size_type srclen, leveltype_e level)
{
    if (!dst || !src || !srclen)
        return 0;

    m_stream.zalloc = 0;
    m_stream.zfree = 0;
    m_stream.opaque = 0;

    int ret = Z_OK;
    if (level > LEVEL_BEST || level <= LEVEL_NO)
        ret = deflateInit(&m_stream, LEVEL_DEFAULT/*LEVEL_6*/);
    else
        ret = deflateInit(&m_stream, level);

    if (ret != Z_OK)
        return 0;

    if (m_dict.size()) {
        if (deflateSetDictionary(&m_stream,
                    &m_dict[0], m_dict.size()) != Z_OK) {
            deflateEnd(&m_stream);
            return 0;
        }
        m_adler = m_stream.adler;
    }

    size_type size = deflateBound(&m_stream, srclen);
    *dst = zipalloc(size);
    if (!*dst) {
        deflateEnd(&m_stream);
        return 0;
    }

    m_stream.next_in = const_cast<pointer>(src);
    m_stream.avail_in = srclen;

    while (m_stream.avail_in) {
        m_stream.next_out = &(*dst)[m_stream.total_out];
        m_stream.avail_out = size - m_stream.total_out;

        ret = deflate(&m_stream, Z_FINISH);
        if (ret == Z_STREAM_END || ret == Z_MEM_ERROR)
            break;

        if (ret == Z_BUF_ERROR || !m_stream.avail_out) {
#ifndef NDEBUG
            size <<= 1;
#else
            size <<= 2;
#endif
            pointer tmp = *dst;
            *dst = zipalloc(size);
            if (!*dst) {
                *dst = tmp;
                goto _error;
            }
            memcpy(*dst, tmp, m_stream.total_out);
            zipfree(tmp);
        } else if (ret == Z_ERRNO
                || ret == Z_STREAM_ERROR
                || ret == Z_DATA_ERROR
                || ret == Z_VERSION_ERROR) {
            goto _error;
        }
    }

    deflateEnd(&m_stream);
    return m_stream.total_out;

_error:
    deflateEnd(&m_stream);
    zipfree(*dst); *dst = 0;
    return 0;
}

Zip::size_type Zip::unzip(pointer* dst, const_pointer src, size_type srclen)
{

    if (!dst || !src || !srclen)
        return 0;

    m_stream.zalloc = 0;
    m_stream.zfree = 0;
    m_stream.opaque = 0;

    if (inflateInit(&m_stream) != Z_OK)
        return 0;

#ifndef NDEBUG
    size_type size = srclen << 1;
#else
    size_type size = srclen << 2;
#endif
    *dst = zipalloc(size);
    if (!*dst) {
        inflateEnd(&m_stream);
        return 0;
    }

    m_stream.next_in = const_cast<pointer>(src);
    m_stream.avail_in = srclen;

    int ret = Z_OK;
    while (m_stream.avail_in) {
        m_stream.next_out = &(*dst)[m_stream.total_out];
        m_stream.avail_out = size - m_stream.total_out;

        ret = inflate(&m_stream, Z_NO_FLUSH);
        if (ret == Z_STREAM_END || ret == Z_MEM_ERROR)
            break;

        if (ret == Z_BUF_ERROR || !m_stream.avail_out) {
#ifndef NDEBUG
            size <<= 1;
#else
            size <<= 2;
#endif
            pointer tmp = *dst;
            *dst = zipalloc(size);
            if (!*dst) {
                *dst = tmp;
                goto _error;
            }
            memcpy(*dst, tmp, m_stream.total_out*sizeof(data_type));
            zipfree(tmp);
        } else if (ret == Z_NEED_DICT) {
            if (m_dict.size()) {
                if (inflateSetDictionary(&m_stream,
                            &m_dict[0], m_dict.size()) != Z_OK)
                    goto _error; // return 0;
                if (m_stream.adler != m_adler)
                    goto _error; // return 0;
            }
        } else if (ret == Z_ERRNO
                || ret == Z_STREAM_ERROR
                || ret == Z_DATA_ERROR
                || ret == Z_VERSION_ERROR) {
            goto _error;
        }
    }

    inflateEnd(&m_stream);
    return m_stream.total_out;

_error:
    inflateEnd(&m_stream);
    zipfree(*dst); *dst = 0;
    return 0;
}

Zip::pointer Zip::zipalloc(size_type size)
{
    if (!size)
        return 0;
    size_type nsize = sizeof(data_type) * size + sizeof(zipmagic_t);
    char* tmp = new char[nsize];
    if (tmp) {
        *reinterpret_cast<zipmagic_t*>(tmp) = ZIP_MAGIC;
        return reinterpret_cast<pointer>(tmp + sizeof(zipmagic_t));
    }
    return 0;
}

void Zip::zipfree(pointer ptr)
{
    if (!ptr)
        return;
    pointer tmp = reinterpret_cast<pointer>(
            reinterpret_cast<char*>(ptr) - sizeof(zipmagic_t));
    if (*reinterpret_cast<zipmagic_t*>(tmp) == ZIP_MAGIC)
        delete [] tmp;
}

} // namespace buf

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

