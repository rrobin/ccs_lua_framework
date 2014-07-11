#pragma once

#include <algorithm>
#include <float.h>
#include <time.h>
#include <assert.h>
#include <string>
#include <math.h>

typedef signed char		int8;
typedef unsigned char	uint8;
typedef short			int16;
typedef unsigned short	uint16;
typedef int				int32;
typedef unsigned int	uint32;
#if defined(_WIN32) && !defined(SHP)
typedef __int64			   int64;
typedef unsigned __int64   uint64;
#elif defined(__linux__) || defined (__APPLE__)
typedef long long int		int64;
typedef unsigned long long int		uint64;
#endif
typedef unsigned char	byte;

#define  SAFE_DELETE(p)				{ if ( p ) { delete ( p );     ( p ) = NULL; } }
#define  SAFE_DELETE_ARRAY(p)		{ if ( p ) { delete[] ( p );   ( p ) = NULL; } }
#define  SAFE_RELEASE(p)			{ if ( p ) { ( p )->Release(); ( p ) = NULL; } }

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#ifndef M_PI_F
#define M_PI_F        float(M_PI)
#endif

#if defined(_WIN32) && !defined(SHP)
#  define finite(X) _finite(X)
inline float finiteAlways(float f) { return finite(f) ? f : 0.0f; }
#endif

enum TimeConstants
{
	MINUTE = 60,
	HOUR   = MINUTE*60,
	DAY    = HOUR*24,
	WEEK   = DAY*7,
	MONTH  = DAY*30,
	YEAR   = MONTH*12,
	IN_MILLISECONDS = 1000
};

enum AccountTypes
{
	SEC_PLAYER         = 0,
	SEC_MODERATOR      = 1,
	SEC_GAMEMASTER     = 2,
	SEC_ADMINISTRATOR  = 3,
	SEC_CONSOLE        = 4                                  // must be always last in list, accounts must have less security level always also
};

// Used in mangosd/realmd
enum RealmFlags
{
	REALM_FLAG_NONE         = 0x00,
	REALM_FLAG_INVALID      = 0x01,
	REALM_FLAG_OFFLINE      = 0x02,
	REALM_FLAG_SPECIFYBUILD = 0x04,                         // client will show realm version in RealmList screen in form "RealmName (major.minor.revision.build)"
	REALM_FLAG_UNK1         = 0x08,
	REALM_FLAG_UNK2         = 0x10,
	REALM_FLAG_NEW_PLAYERS  = 0x20,
	REALM_FLAG_RECOMMENDED  = 0x40,
	REALM_FLAG_FULL         = 0x80
};

enum LocaleConstant
{
	LOCALE_enUS = 0,                                        // also enGB
	LOCALE_koKR = 1,
	LOCALE_frFR = 2,
	LOCALE_deDE = 3,
	LOCALE_zhCN = 4,
	LOCALE_zhTW = 5,
	LOCALE_esES = 6,
	LOCALE_esMX = 7,
	LOCALE_ruRU = 8
};

#define MAX_LOCALE 9

LocaleConstant GetLocaleByName(const std::string& name);

extern char const* localeNames[MAX_LOCALE];

#define BIT(x) (1<<x)

struct LocaleNameStr
{
	char const* name;
	LocaleConstant locale;
};

// used for iterate all names including alternative
extern LocaleNameStr const fullLocaleNameList[];

#ifndef NULL
#define NULL 0
#endif

#ifndef countof
#define countof(array) (sizeof(array) / sizeof((array)[0]))
#endif

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

#include "Utility/gameVariables.h"
