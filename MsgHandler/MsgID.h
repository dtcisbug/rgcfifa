#ifndef _MSGID_H_
#define _MSGID_H_

#include "Common/Config.h"

namespace REQ
{
    //聊天

    const UInt8 CHAT                 = 0x06;
}

namespace REP
{
    const UInt8 CHAT                = 0x06;
}

namespace SPEQ
{
    const UInt8 SOCK_ADDR           = 0x02;
    const UInt8 PLAYERIDAUTH        = 0xFC;// 0xFD
}

namespace SPEP
{
    const UInt8 LOCKUSER            = 0x00;
    const UInt8 UNLOCKUSER          = 0x01;
}

#endif // __MSGID_H_

