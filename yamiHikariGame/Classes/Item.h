//
//  Item.h
//  yamiHikariGame
//
//  Created by slightair on 2013/08/04.
//
//

#ifndef __yamiHikariGame__Item__
#define __yamiHikariGame__Item__

#include "hiberlite.h"
#include "Constants.h"
#include "sha1.h"

#define kChecksumLength 8
#define kSHA1DigestLength 20

using namespace std;

class Item
{
    friend class hiberlite::access;
    template<class Archive>
    void hibernate(Archive &ar)
    {
        ar & HIBERLITE_NVP(name);
        ar & HIBERLITE_NVP(desc);
        ar & HIBERLITE_NVP(image);
        ar & HIBERLITE_NVP(stamina);
        ar & HIBERLITE_NVP(score);
        ar & HIBERLITE_NVP(count);
        ar & HIBERLITE_NVP(checksum);
    }

public:
    string name;
    string desc;
    string image;
    int stamina;
    int score;
    int count;
    string checksum;

    void updateCount(int count)
    {
        this->count = count;
        this->checksum = generateChecksum();
    }

    bool validate()
    {
        return this->checksum == generateChecksum();
    }

    string generateChecksum()
    {
        ostringstream os;
        os << this->name << ':'
           << this->desc << ':'
           << this->image << ':'
           << this->stamina << ':'
           << this->score << ':'
           << count << ':'
           << SaveDataChecksumSalt;
        const char *input = os.str().c_str();

        unsigned char digest[kSHA1DigestLength];
        char buf[kChecksumLength];

        SHA1 sha1;
        sha1.addBytes((unsigned char *)input, strlen(input));
        sha1.getDigest(digest, kSHA1DigestLength);
        sprintf(buf, "%02x%02x%02x%02x", digest[0], digest[1], digest[2], digest[3]);

        return string(buf);
    }
};
HIBERLITE_EXPORT_CLASS(Item)

#endif /* defined(__yamiHikariGame__Item__) */
