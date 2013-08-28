//
//  Item.cpp
//  yamiHikariGame
//
//  Created by slightair on 2013/08/05.
//
//

#include "Item.h"

#define kFiguresOfInteger 10
#define kFiguresOfFloat 10

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
    char cpStamina[kFiguresOfInteger + 1], cpScore[kFiguresOfInteger + 1], cpScoreThreshold[kFiguresOfInteger + 1], cpDropRate[kFiguresOfFloat + 1], cpCount[kFiguresOfInteger + 1];
    sprintf(cpStamina, "%d", this->stamina);
    sprintf(cpScore, "%d", this->score);
    sprintf(cpScoreThreshold, "%d", this->score_threshold);
    sprintf(cpDropRate, "%.5f", this->drop_rate);
    sprintf(cpCount, "%d", this->count);

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