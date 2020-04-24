#pragma once
#include <windows.h>
#include "Offsets.h"
#include "CSGOvector.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

//https://guidedhacking.com/threads/csgo-how-to-find-call-traceray-tutorial.14696/

typedef void* (__cdecl* tCreateInterface)(const char* name, int* pReturnCode);

void* GetInterface(tCreateInterface fn, const char* name)
{
    return (fn)(name, 0);
}

class Ent
{
public:
    union
    {
        DEFINE_MEMBER_N(vec3, origin, hazedumper::netvars::m_vecOrigin);
        DEFINE_MEMBER_N(int, clientId, 0x64);
        DEFINE_MEMBER_N(vec3, m_vecViewOffset, hazedumper::netvars::m_vecViewOffset);
    };
}; //Size: 0x0284

class EntListObj
{
public:
    class Ent* ent; //0x0000
    char pad_0004[12]; //0x0004
}; //Size: 0x0010

class EntList
{
public:
    EntListObj entListObjs[32]; //0x0000
}; //Size: 0x0200