#include "base64.h"



static const char base64_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                  'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                  '4', '5', '6', '7', '8', '9', '+', '/'};



char *read_file(const char* path, size_t *buffer_len)
{
    std::ifstream is(path);
    is.seekg(0, std::ios::end);
    *buffer_len = static_cast<size_t>(is.tellg());
    is.seekg(std::ios::beg);

    size_t encoded_len = *buffer_len / 3 * 4 + (*buffer_len % 3 > 0 ? 4 : 0 );
    auto buffer = new char[encoded_len];
    is.read(buffer, encoded_len);

    return buffer;
}



unsigned char *base64_encode(const char *source_text, const size_t buffer_len)
{
    assert(source_text != nullptr);
    assert(buffer_len > 0);

    size_t encoded_len = buffer_len / 3 * 4 + (buffer_len % 3 ? 4 : 0 ) + 1;  
    unsigned char *encoded = new unsigned char[encoded_len];
    unsigned char *encoded_iterator = encoded - 1;

    for(size_t i = 0, j = 0; i < buffer_len; ++i, ++j)
    {
        switch(j)
        {
            case 0: //first encoded byte
            {
                *(++encoded_iterator) = base64_map[(source_text[i] >> 2) & 0b111111];
                if(i + 1 == buffer_len)
                {
                    *(++encoded_iterator) = base64_map[(source_text[i] << 4) & 0b110000];
                }
                break;
            }
            case 1: //second encoded byte
            {      
                unsigned char left_part = (source_text[i - 1] << 4) & 0b110000,
                              right_part = (source_text[i] >> 4) & 0b1111;
                *(++encoded_iterator) = base64_map[left_part | right_part];

                left_part = (source_text[i] << 2) & 0b111100;
                *(++encoded_iterator) = left_part | ((i + 1 < buffer_len)? (source_text[i + 1] >> 6) & 0b11 : 0);
                *encoded_iterator = base64_map[*encoded_iterator];
                break;
            }
            case 2: //third encoded byte
            {
                *(++encoded_iterator) = base64_map[source_text[i] & 0b111111];
                j = -1;
                break;
            }
        }
    }
    while(++encoded_iterator < encoded + encoded_len - 1)
    {
        *encoded_iterator = '=';
    }
    *encoded_iterator = '\0';  
    return encoded;
}