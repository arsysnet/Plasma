/*==LICENSE==*

CyanWorlds.com Engine - MMOG client, server and tools
Copyright (C) 2011  Cyan Worlds, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Additional permissions under GNU GPL version 3 section 7

If you modify this Program, or any covered work, by linking or
combining it with any of RAD Game Tools Bink SDK, Autodesk 3ds Max SDK,
NVIDIA PhysX SDK, Microsoft DirectX SDK, OpenSSL library, Independent
JPEG Group JPEG library, Microsoft Windows Media SDK, or Apple QuickTime SDK
(or a modified version of those libraries),
containing parts covered by the terms of the Bink SDK EULA, 3ds Max EULA,
PhysX SDK EULA, DirectX SDK EULA, OpenSSL and SSLeay licenses, IJG
JPEG Library README, Windows Media SDK EULA, or QuickTime SDK EULA, the
licensors of this Program grant you additional
permission to convey the resulting work. Corresponding Source for a
non-source form of such a combination shall include the source code for
the parts of OpenSSL and IJG JPEG Library used as well as that of the covered
work.

You can contact Cyan Worlds, Inc. by email legal@cyan.com
 or by snail mail at:
      Cyan Worlds, Inc.
      14617 N Newport Hwy
      Mead, WA   99021

*==LICENSE==*/
/*****************************************************************************
*
*   $/Plasma20/Sources/Plasma/NucleusLib/pnUtils/Private/pnUtSync.h
*   
***/

#ifndef PLASMA20_SOURCES_PLASMA_NUCLEUSLIB_PNUTILS_PRIVATE_PNUTSYNC_H
#define PLASMA20_SOURCES_PLASMA_NUCLEUSLIB_PNUTILS_PRIVATE_PNUTSYNC_H

#include "Pch.h"

/****************************************************************************
*
*   Atomic operations
*
***/

// *value += increment; return original value of *value; thread safe
long AtomicAdd (long * value, long increment);

// *value = value; return original value of *value; thread safe
long AtomicSet (long * value, long set);


#define ATOMIC_ONCE(code) {     \
    static long s_count = 1;    \
    if (AtomicSet(&s_count, 0)) \
        code;                   \
}                               //


/****************************************************************************
*
*   CLock
*   (reader/writer lock)
*
***/

class CLockWaitSet;

class CLock {
private:
    CLockWaitSet *  m_waitSet;
    long            m_spinLock;
    unsigned        m_readerCount;
    unsigned        m_writerCount;

public:
    CLock ();
    ~CLock ();
    void EnterRead ();
    void EnterWrite ();
    void LeaveRead ();
    void LeaveWrite ();
};


/*****************************************************************************
*
*   CEvent
*
***/

#ifdef HS_BUILD_FOR_WIN32
typedef HANDLE EventHandle;
//#else
//# error "CEvent: Not implemented on this platform"
//#endif

const unsigned  kEventWaitForever   = (unsigned)-1;

enum ECEventResetBehavior {
    kEventManualReset,
    kEventAutoReset,
};

class CEvent {
    EventHandle     m_handle;
public:
    CEvent (
        ECEventResetBehavior resetType,
        bool        initialSet = false
    );
    ~CEvent ();

    void Signal ();
    void Reset ();
    bool Wait (unsigned waitMs);
    
    const EventHandle & Handle () const { return m_handle; }
};
#endif // HS_BUILD_FOR_WIN32

#endif