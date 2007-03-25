/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set expandtab shiftwidth=4 tabstop=4: */

/**
 * \file
 * <PRE>
 * High Performance URL Encoder/Decoder
 * Version 1.0 -- 27-Mar-2006
 *
 * Copyright &copy; 2006, Nick Galbreath -- nickg [at] modp [dot] com
 * All rights reserved.
 *
 * http://modp.com/release/base64
 *
 * Released under bsd license.  See bfast64.c for details.
 * </PRE>
 */

#ifndef MODP_BURL
#define MODP_BURL

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Url encode a string.  This uses a very strict definition of url encoding.
 * The only characters NOT encoded are A-Z, a-z, 0-9, "-", "_", ".", along with
 * the space char getting mapped to "+".  Everything else is escaped using
 * "%HEXHEX" format.  This is identical to the implementation of php's urlencode
 * and nearly identical to Java's UrlEncoder class (they do not escape '*' for
 * some reason).
 *
 * \param[out] dest output string.  Must
 * \param[in] str The input string
 * \param[in] len  The length of the input string, excluding any
 *   final null byte.
 */
int modp_burl_encode(char* dest, const char* str, int len);

/**
 * Url encode a string.  This uses a minimal definition of url encoding.
 * This works similar to the previous function except '~', '!', '$', '\'',
 * '(', ')', '*', ',', ';', ':', '@', '/', '?' are NOT escaped.  This will
 * allow decoding by standard url-decoders and make the encoded urls more
 * readable.
 *
 * \param[out] dest output string.  Must
 * \param[in] str The input string
 * \param[in] len  The length of the input string, excluding any
 *   final null byte.
 */
int modp_burl_min_encode(char* dest, const char* str, int len);

/**
 * Provides the maximum size for output string given
 * and input size of A bytes.
 */
#define modp_burl_encode_len(A) (3*A + 1)

/**
 * Given the exact size of output string.
 *
 * Can be used to allocate the right amount of memory for
 * modp_burl_encode.  Be sure to add 1 byte for final null.
 *
 * This is somewhat expensive since it examines every character
 *  in the input string
 *
 * \param[in] str  The input string
 * \param[in] len  THe length of the input string, excluding any
 *   final null byte (i.e. strlen(str))
 * \return the size of the output string, excluding the final
 *   null byte.
 */
int modp_burl_encode_strlen(const char* str, const int len);

/**
 * URL Decode a string
 *
 * \param[out] dest  The output string.  Must be at least (len + 1)
 *  bytes allocated.  This may be the same as the input buffer.
 * \param[in] str The input string that is URL encoded.
 * \param[in] len The length of the input string (excluding final
 *   null byte)
 * \return the strlen of the output string.
 */
int modp_burl_decode(char* dest, const char* str, int len);

/**
 * Returns memory required to decoded a url-encoded
 * string of length A.
 *
 */
#define modp_burl_decode_len(A) (A + 1)

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include <string>

namespace modp {

/**
 * Standard (maximal) url encoding.
 *
 * \param[in,out] s the string to be encoded
 * \return a reference to the input string
 */
inline std::string& url_encode(std::string& s)
{
    std::string x(modp_burl_encode_len(s.size()), '\0');
    int d = modp_burl_encode(const_cast<char*>(x.data()), s.data(), s.size());
    x.erase(d, std::string::npos);
    s.swap(x);
    return s;
}

/**
 * Minimal Url Encoding
 *
 * \param[in,out] s the string to be encoded
 * \return a reference to the input string
 */
inline std::string& url_min_encode(std::string& s)
{
    std::string x(modp_burl_encode_len(s.size()), '\0');
    int d = modp_burl_min_encode(const_cast<char*>(x.data()), s.data(), s.size());
    x.erase(d, std::string::npos);
    s.swap(x);
    return s;
}

/**
 * Url decode a string.
 * This function does not allocate memory.
 *
 * \param[in,out] s the string to be decoded
 * \return a reference to the input string.
 *      On error, the string is empty.
 */
inline std::string& url_decode(std::string& s)
{
    int d = modp_burl_decode(const_cast<char*>(s.data()), s.data(), s.size());
    if (d < 0) {
        s.clear();
    } else {
        s.erase(d, std::string::npos);
    }
    return s;
}

}
#endif

#endif