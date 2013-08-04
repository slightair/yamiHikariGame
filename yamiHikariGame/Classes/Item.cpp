//
//  Item.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/05.
//
//

#include "Item.h"

void Item::updateCount(int count)
{
    this->count = count;
    this->checksum = generateChecksum();
}

bool Item::validate()
{
    return this->checksum == generateChecksum();
}

string Item::generateChecksum()
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

HIBERLITE_EXPORT_CLASS(Item)
