#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <uuid/uuid.h>
#include <openssl/sha.h>

class XUtils
{
public:
    static std::string generate_uuid()
    {
        uuid_t uuid;
        char uuid_str[37];

        // Generate UUID
        uuid_generate(uuid);

        // Convert UUID to string
        uuid_unparse(uuid, uuid_str);

        return std::string(uuid_str);
    }

    static std::string hash_string(const std::string& input)
    {
        unsigned char hash[SHA_DIGEST_LENGTH];
        char sha1_output[SHA_DIGEST_LENGTH * 2 + 1];

        SHA1((unsigned char*)input.c_str(), input.length(), hash);

        for(int i = 0; i < SHA_DIGEST_LENGTH; i++) 
        {
            sprintf(sha1_output + (i * 2), "%02x", hash[i]);
        }

        return std::string(sha1_output);
    }


};

#endif