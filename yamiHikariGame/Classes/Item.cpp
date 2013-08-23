//
//  Item.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/05.
//
//

#include "Item.h"
#include "cocos2d.h"

void _Item::updateCount(int count)
{
    this->count = count;
    this->checksum = generateChecksum();
}

bool _Item::validate()
{
    return this->checksum == generateChecksum();
}

string _Item::generateChecksum()
{
    char cpStamina[8], cpScore[8], cpScoreThreshold[8], cpDropRate[8], cpCount[8];
    std::sprintf(cpStamina, "%d", this->stamina);
    std::sprintf(cpScore, "%d", this->score);
    std::sprintf(cpScoreThreshold, "%d", this->score_threshold);
    std::sprintf(cpDropRate, "%.5f", this->drop_rate);
    std::sprintf(cpCount, "%d", this->count);

    string os = this->name + ':';
    os += this->desc + ':';
    os += this->image + ':';
    os += string(cpStamina) + ':';
    os += string(cpScore) + ':';
    os += string(cpScoreThreshold) + ':';
    os += string(cpDropRate) + ':';
    os += string(cpCount) + ':';
    os += string(SaveDataChecksumSalt);
    const char *input = os.c_str();

    unsigned char digest[kSHA1DigestLength];
    char buf[kChecksumLength];

    SHA1 sha1;
    sha1.addBytes((unsigned char *)input, strlen(input));
    sha1.getDigest(digest, kSHA1DigestLength);
    sprintf(buf, "%02x%02x%02x%02x", digest[0], digest[1], digest[2], digest[3]);

    return string(buf);
}

namespace hiberlite {
    template<>
    std::string Database::getClassName<_Item>()
    {
        return "Item";
    }
}