#ifndef DEF_BASE64
#define DEF_BASE64

#include <vector>
#include <string>
#include <sstream>

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";
static inline bool is_base64(unsigned char c);
std::string base64_encode(char const* bytes_to_encode, int in_len);
std::string base64_decode(std::string const& encoded_string);
std::string vectorToString(std::vector<std::string> &v);
std::vector<std::string> stringToVector(std::string &str);

#endif
