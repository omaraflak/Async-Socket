#include "utils.h"

std::string getUid(size_t length){
    std::string allowed_chars = "0123456789ABCDFGHJKLMNPQRSTVWXZabcdfghjklmnpqrstvwxz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(allowed_chars)-1);
    std::string id(length ? length : 16, '\0');

    for (std::string::value_type& c : id) {
        c = allowed_chars[dis(gen)];
    }

    return id;
}
