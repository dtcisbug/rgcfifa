#ifndef _TINF_H_
#define _TINF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TINF_OK             0
#define TINF_DATA_ERROR    (-3)

	/* function prototypes */

	void tinf_init();

	int tinf_uncompress(void *dest, unsigned int *destLen,
		const void *source, unsigned int sourceLen);
    int tinf_zlib_uncompress(void *dest, unsigned int *destLen,
                                    const void *source, unsigned int sourceLen);
	unsigned int tinf_adler32(const void *data, unsigned int length);

	unsigned int tinf_crc32(const void *data, unsigned int length);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // _TINF_H_
