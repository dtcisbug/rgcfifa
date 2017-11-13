
#ifndef ZIP_H_
#define ZIP_H_

#include <vector>
#include <zlib.h>

namespace buf
{

typedef unsigned int zipmagic_t;
static const zipmagic_t ZIP_MAGIC = 0x76336dc4;

/**
 * A wrapper of zlib
 */
class Zip
{
public:
    /// The data type of buffer
    typedef Bytef data_type;
    /// The pointer type of data
    typedef Bytef* pointer;
    ///
    typedef const Bytef* const_pointer;
    /// The size type of buffer
    typedef size_t size_type;

    /// Levels of compression
    typedef enum
    {
        // compress
        LEVEL_NO = -2,
        // compress2
        LEVEL_DEFAULT = Z_DEFAULT_COMPRESSION, // -1
        LEVEL_COPY = Z_NO_COMPRESSION,  // 0
        LEVEL_FAST = Z_BEST_SPEED,      // 1
        LEVEL_2 = 2,
        LEVEL_3 = 3,
        LEVEL_4 = 4,
        LEVEL_5 = 5,
        LEVEL_6 = 6,
        LEVEL_7 = 7,
        LEVEL_8 = 8,
        LEVEL_BEST = Z_BEST_COMPRESSION // 9
    } leveltype_e;

public:
    /**
     * @brief Creates a zip wrapper with dictionary
     *
     * @param dict - the compression dictionary
     * @param len  - the length of dictionary
     */
    explicit Zip(const_pointer dict = 0, size_type len = 0);

    ~Zip();

    /**
     * @brief Compress from src to dst with level. <br>
     * <br>
     * It will be compressed with dictionary if it has been set when <br>
     * the wrapper was created.
     *
     * @param dst - the destination std::vector
     * @param src - the source buffer
     * @param srclen - the length of source
     * @param level - the compress level
     *
     * @return  0  - compress error <br>
     *          >0 - the length of compressed data in dst
     */
    size_type zip(std::vector<data_type>& dst, const_pointer src, size_type srclen,
            leveltype_e level = LEVEL_NO);

    /**
     * @brief Compress from src to dst with level <br>
     * <br>
     * It will be compressed with dictionary if it has been set when <br>
     * the wrapper was created.
     * <br>
     * The src.size() must be the actual length of data which <br>
     * will be uncompressed.
     *
     * @param dst - the destination std::vector
     * @param src - the source std::vector
     * @param level - the compress level
     *
     * @return  0  - compress error <br>
     *          >0 - the length of compressed data in dst
     */
    size_type zip(std::vector<data_type>& dst, std::vector<data_type>& src,
            leveltype_e level = LEVEL_NO)
    {
        return zip(dst, &src[0], src.size(), level);
    }


    /**
     * @brief Uncompress from src to dst
     *
     * @param dst - the destination std::vector
     * @param src - the source buffer
     * @param srclen - the length of source
     *
     * @return  0  - uncompress error <br>
     *          >0 - the length of uncompressed data in dst
     */
    size_type unzip(std::vector<data_type>& dst, const_pointer src, size_type srclen);

    /**
     * @brief Uncompress from src to dst <br>
     * <br>
     * The src.size() must be the actual length of data which <br>
     * will be uncompressed.
     *
     * @param dst - the destination std::vector
     * @param src - the source std::vector
     *
     * @return  0  - uncompress error <br>
     *          >0 - the length of uncompressed data in dst
     */
    size_type unzip(std::vector<data_type>& dst, std::vector<data_type>& src)
    {
        return unzip(dst, &src[0], src.size());
    }

    /**
     * @brief Compress from src to *dst with level. <br>
     * <br>
     * It will be compressed with dictionary if it has been set when <br>
     * the wrapper was created. <br>
     * <br>
     * The *dst must be freed by zipfree()
     *
     * @param dst - the address of destination
     * @param src - the source buffer
     * @param srclen - the length of source
     * @param level - the compress level
     *
     * @return  0  - compress error <br>
     *          >0 - the length of compressed data in *dst
     */
    size_type zip(pointer* dst, const_pointer src, size_type srclen, leveltype_e level = LEVEL_NO);

    /**
     * @brief Uncompress from src to *dst <br>
     * The *dst must be freed by zipfree()
     *
     * @param dst - the destination std::vector
     * @param src - the source std::vector
     * @param srclen - the length of source
     *
     * @return  0  - uncompress error <br>
     *          >0 - the length of uncompressed data in *dst
     */
    size_type unzip(pointer* dst, const_pointer src, size_type srclen);

private:
    /**
     * @brief Free the memory allocated by zip or unzip
     *
     * @param ptr - the memory allocated by zip or unzip
     */
    void zipfree(pointer ptr);

    /**
     * @brief Memory allocator for Zip and put ZIP_MAGIC to the  <br>
     * front of memory
     *
     * @param size
     *
     * @return  NULL -
     *          pointer - the start address of memory
     */
    pointer zipalloc(size_type size);

private:
    /// the compression or uncompression stream state
    z_stream m_stream;
    /// the compression dictionary
    std::vector<data_type> m_dict;
    /// the adler32 value of the dictionary
    size_type m_adler;
};

} // namespace buf

#endif // ZIP_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

