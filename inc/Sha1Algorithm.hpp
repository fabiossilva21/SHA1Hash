// Include Guard
#ifndef SHA1ALGORITHM_HPP
#define SHA1ALGORITHM_HPP

#include <vector>
#include <string>

namespace Sha1Algorithm {

    /**
     * This library implements the SHA1 Hash encoding
     * described in [RFC3174](https://tools.ietf.org/html/rfc3174)
     */
    
    std::string Sha1Hash(const std::vector<char>& data);
    std::string Sha1Hash(const std::string& data);

}

#endif // SHA1ALGORITHM_HPP