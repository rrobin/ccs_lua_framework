#ifndef POCKETHERO_SHAREDDEFINES_H
#define POCKETHERO_SHAREDDEFINES_H

#include "common.h"
#include "../Spell/SpellDefine.h"

enum Stats
{
	STAT_STRENGTH                      = 0,
	STAT_AGILITY                       = 1,
	STAT_STAMINA                       = 2,
	STAT_INTELLECT                     = 3,
	STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

// CreatureType.dbc
enum CreatureType
{
	CREATURE_TYPE_BEAST            = 1,
	CREATURE_TYPE_DRAGONKIN        = 2,
	CREATURE_TYPE_DEMON            = 3,
	CREATURE_TYPE_ELEMENTAL        = 4,
	CREATURE_TYPE_GIANT            = 5,
	CREATURE_TYPE_UNDEAD           = 6,
	CREATURE_TYPE_HUMANOID         = 7,
	CREATURE_TYPE_CRITTER          = 8,
	CREATURE_TYPE_MECHANICAL       = 9,
	CREATURE_TYPE_NOT_SPECIFIED    = 10,
	CREATURE_TYPE_TOTEM            = 11,
	CREATURE_TYPE_NON_COMBAT_PET   = 12,
	CREATURE_TYPE_GAS_CLOUD        = 13
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL-1)) | (1 << (CREATURE_TYPE_ELEMENTAL-1));


enum CreatureEliteType
{
	CREATURE_ELITE_NORMAL          = 0,		// 普通怪
	CREATURE_ELITE_ELITE           = 1,		// 精英怪
	CREATURE_ELITE_RAREELITE       = 2,		// 稀有精英
	CREATURE_ELITE_WORLDBOSS       = 3,		// 世界boss
	CREATURE_ELITE_RARE            = 4,		// 稀有
	CREATURE_UNKNOWN               = 5  // found in 2.2.3 for 2 mobs
};

enum SpellSchools
{
	SPELL_SCHOOL_NORMAL                 = 0,		// 物理
	SPELL_SCHOOL_HOLY                   = 1,		// 神圣
	SPELL_SCHOOL_FIRE                   = 2,		// 火
	SPELL_SCHOOL_NATURE                 = 3,		// 自然		用作电系
	SPELL_SCHOOL_FROST                  = 4,		// 冰
	SPELL_SCHOOL_SHADOW                 = 5,		// 暗
	SPELL_SCHOOL_ARCANE                 = 6			// 奥术
};

#define MAX_SPELL_SCHOOL                  7

enum SpellSchoolMask
{
	SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
	SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
	SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY),
	SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE),
	SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
	SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST),
	SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
	SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

	// unions

	// 124, not include normal and holy damage
	SPELL_SCHOOL_MASK_SPELL   = (SPELL_SCHOOL_MASK_FIRE   |
	SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
	SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE),
	// 126
	SPELL_SCHOOL_MASK_MAGIC   = (SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL),

	// 127
	SPELL_SCHOOL_MASK_ALL     = (SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC)
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
	for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
		if (mask & (1 << i))
			return SpellSchools(i);

	return SPELL_SCHOOL_NORMAL;
}

enum Emote
{
	EMOTE_ONESHOT_NONE                 = 0,
	EMOTE_ONESHOT_TALK                 = 1,
	EMOTE_ONESHOT_BOW                  = 2,
	EMOTE_ONESHOT_WAVE                 = 3,
	EMOTE_ONESHOT_CHEER                = 4,
	EMOTE_ONESHOT_EXCLAMATION          = 5,
	EMOTE_ONESHOT_QUESTION             = 6,
	EMOTE_ONESHOT_EAT                  = 7,
	EMOTE_STATE_DANCE                  = 10,
	EMOTE_ONESHOT_LAUGH                = 11,
	EMOTE_STATE_SLEEP                  = 12,
	EMOTE_STATE_SIT                    = 13,
	EMOTE_ONESHOT_RUDE                 = 14,
	EMOTE_ONESHOT_ROAR                 = 15,
	EMOTE_ONESHOT_KNEEL                = 16,
	EMOTE_ONESHOT_KISS                 = 17,
	EMOTE_ONESHOT_CRY                  = 18,
	EMOTE_ONESHOT_CHICKEN              = 19,
	EMOTE_ONESHOT_BEG                  = 20,
	EMOTE_ONESHOT_APPLAUD              = 21,
	EMOTE_ONESHOT_SHOUT                = 22,
	EMOTE_ONESHOT_FLEX                 = 23,
	EMOTE_ONESHOT_SHY                  = 24,
	EMOTE_ONESHOT_POINT                = 25,
	EMOTE_STATE_STAND                  = 26,
	EMOTE_STATE_READYUNARMED           = 27,
	EMOTE_STATE_WORK                   = 28,
	EMOTE_STATE_POINT                  = 29,
	EMOTE_STATE_NONE                   = 30,
	EMOTE_ONESHOT_WOUND                = 33,
	EMOTE_ONESHOT_WOUNDCRITICAL        = 34,
	EMOTE_ONESHOT_ATTACKUNARMED        = 35,
	EMOTE_ONESHOT_ATTACK1H             = 36,
	EMOTE_ONESHOT_ATTACK2HTIGHT        = 37,
	EMOTE_ONESHOT_ATTACK2HLOOSE        = 38,
	EMOTE_ONESHOT_PARRYUNARMED         = 39,
	EMOTE_ONESHOT_PARRYSHIELD          = 43,
	EMOTE_ONESHOT_READYUNARMED         = 44,
	EMOTE_ONESHOT_READY1H              = 45,
	EMOTE_ONESHOT_READYBOW             = 48,
	EMOTE_ONESHOT_SPELLPRECAST         = 50,
	EMOTE_ONESHOT_SPELLCAST            = 51,
	EMOTE_ONESHOT_BATTLEROAR           = 53,
	EMOTE_ONESHOT_SPECIALATTACK1H      = 54,
	EMOTE_ONESHOT_KICK                 = 60,
	EMOTE_ONESHOT_ATTACKTHROWN         = 61,
	EMOTE_STATE_STUN                   = 64,
	EMOTE_STATE_DEAD                   = 65,
	EMOTE_ONESHOT_SALUTE               = 66,
	EMOTE_STATE_KNEEL                  = 68,
	EMOTE_STATE_USESTANDING            = 69,
	EMOTE_ONESHOT_WAVE_NOSHEATHE       = 70,
	EMOTE_ONESHOT_CHEER_NOSHEATHE      = 71,
	EMOTE_ONESHOT_EAT_NOSHEATHE        = 92,
	EMOTE_STATE_STUN_NOSHEATHE         = 93,
	EMOTE_ONESHOT_DANCE                = 94,
	EMOTE_ONESHOT_SALUTE_NOSHEATH      = 113,
	EMOTE_STATE_USESTANDING_NOSHEATHE  = 133,
	EMOTE_ONESHOT_LAUGH_NOSHEATHE      = 153,
	EMOTE_STATE_WORK_NOSHEATHE         = 173,
	EMOTE_STATE_SPELLPRECAST           = 193,
	EMOTE_ONESHOT_READYRIFLE           = 213,
	EMOTE_STATE_READYRIFLE             = 214,
	EMOTE_STATE_WORK_NOSHEATHE_MINING  = 233,
	EMOTE_STATE_WORK_NOSHEATHE_CHOPWOOD= 234,
	EMOTE_zzOLDONESHOT_LIFTOFF         = 253,
	EMOTE_ONESHOT_LIFTOFF              = 254,
	EMOTE_ONESHOT_YES                  = 273,
	EMOTE_ONESHOT_NO                   = 274,
	EMOTE_ONESHOT_TRAIN                = 275,
	EMOTE_ONESHOT_LAND                 = 293,
	EMOTE_STATE_AT_EASE                = 313,
	EMOTE_STATE_READY1H                = 333,
	EMOTE_STATE_SPELLKNEELSTART        = 353,
	EMOTE_STATE_SUBMERGED              = 373,
	EMOTE_ONESHOT_SUBMERGE             = 374,
	EMOTE_STATE_READY2H                = 375,
	EMOTE_STATE_READYBOW               = 376,
	EMOTE_ONESHOT_MOUNTSPECIAL         = 377,
	EMOTE_STATE_TALK                   = 378,
	EMOTE_STATE_FISHING                = 379,
	EMOTE_ONESHOT_FISHING              = 380,
	EMOTE_ONESHOT_LOOT                 = 381,
	EMOTE_STATE_WHIRLWIND              = 382,
	EMOTE_STATE_DROWNED                = 383,
	EMOTE_STATE_HOLD_BOW               = 384,
	EMOTE_STATE_HOLD_RIFLE             = 385,
	EMOTE_STATE_HOLD_THROWN            = 386,
	EMOTE_ONESHOT_DROWN                = 387,
	EMOTE_ONESHOT_STOMP                = 388,
	EMOTE_ONESHOT_ATTACKOFF            = 389,
	EMOTE_ONESHOT_ATTACKOFFPIERCE      = 390,
	EMOTE_STATE_ROAR                   = 391,
	EMOTE_STATE_LAUGH                  = 392,
	EMOTE_ONESHOT_CREATURE_SPECIAL     = 393
};

enum Gender
{
	GENDER_MALE                        = 0,
	GENDER_FEMALE                      = 1,
	GENDER_NONE                        = 2
};

enum Races
{
	RACE_HUMAN          = 1,			// 暂时无种族概念,即所有种族都为人类
	MAX_RACES           = 2,
	/*RACE_ORC            = 2,
	RACE_DWARF          = 3,
	RACE_NIGHTELF       = 4,
	RACE_UNDEAD_PLAYER  = 5,
	RACE_TAUREN         = 6,
	RACE_GNOME          = 7,
	RACE_TROLL          = 8,
	RACE_GOBLIN         = 9,
	RACE_BLOODELF       = 10,
	RACE_DRAENEI        = 11,
	RACE_FEL_ORC        = 12,
	RACE_NAGA           = 13,
	RACE_BROKEN         = 14,
	RACE_SKELETON       = 15,*/
};

enum Classes
{
	CLASS_WARRIOR       = 1,			// 战士
	CLASS_PALADIN       = 2,			// 骑士
	CLASS_HUNTER        = 3,			// 弓手
	CLASS_ROGUE         = 4,			// 刺客
	CLASS_PRIEST        = 5,			// 牧师
	CLASS_DRUID			= 6,			//德鲁伊
	CLASS_SHAMAN        = 7,			// 萨满
	CLASS_MAGE          = 8,			// 法师
	CLASS_WARLOCK       = 9,			// 术士
	// CLASS_UNK2       = 10,unused
	CLASS_DEATH_KNIGHT  = 11,			// 用于英雄的职业
	MAX_CLASSES			= 12,
};

#define CLASSMASK_ALL_PLAYABLE \
	((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
	(1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
	(1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))/*|(1<<(CLASS_DRUID-1)) | \
	(1<<(CLASS_DEATH_KNIGHT-1))*/ )

#define	IS_RANGECLASS(c) (c==CLASS_HUNTER || c==CLASS_PRIEST || c==CLASS_MAGE || c==CLASS_WARLOCK)

#define CLASSMASK_ALL_CREATURES ((1<<(CLASS_WARRIOR-1)) | (1<<(CLASS_PALADIN-1)) | (1<<(CLASS_ROGUE-1)) | (1<<(CLASS_MAGE-1)) )

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

enum SkillType
{
	SKILL_NONE                     = 0,

	SKILL_FROST                    = 6,
	SKILL_FIRE                     = 8,
	SKILL_ARMS                     = 26,
	SKILL_COMBAT                   = 38,
	SKILL_SUBTLETY                 = 39,
	SKILL_SWORDS                   = 43,
	SKILL_AXES                     = 44,
	SKILL_BOWS                     = 45,
	SKILL_GUNS                     = 46,
	SKILL_BEAST_MASTERY            = 50,
	SKILL_SURVIVAL                 = 51,
	SKILL_MACES                    = 54,
	SKILL_2H_SWORDS                = 55,
	SKILL_HOLY                     = 56,
	SKILL_SHADOW                   = 78,
	SKILL_DEFENSE                  = 95,
	SKILL_LANG_COMMON              = 98,
	SKILL_RACIAL_DWARVEN           = 101,
	SKILL_LANG_ORCISH              = 109,
	SKILL_LANG_DWARVEN             = 111,
	SKILL_LANG_DARNASSIAN          = 113,
	SKILL_LANG_TAURAHE             = 115,
	SKILL_DUAL_WIELD               = 118,
	SKILL_RACIAL_TAUREN            = 124,
	SKILL_ORC_RACIAL               = 125,
	SKILL_RACIAL_NIGHT_ELF         = 126,
	SKILL_FIRST_AID                = 129,
	SKILL_FERAL_COMBAT             = 134,
	SKILL_STAVES                   = 136,
	SKILL_LANG_THALASSIAN          = 137,
	SKILL_LANG_DRACONIC            = 138,
	SKILL_LANG_DEMON_TONGUE        = 139,
	SKILL_LANG_TITAN               = 140,
	SKILL_LANG_OLD_TONGUE          = 141,
	SKILL_SURVIVAL2                = 142,
	SKILL_RIDING_HORSE             = 148,
	SKILL_RIDING_WOLF              = 149,
	SKILL_RIDING_RAM               = 152,
	SKILL_RIDING_TIGER             = 150,
	SKILL_SWIMING                  = 155,
	SKILL_2H_MACES                 = 160,
	SKILL_UNARMED                  = 162,
	SKILL_MARKSMANSHIP             = 163,
	SKILL_BLACKSMITHING            = 164,
	SKILL_LEATHERWORKING           = 165,
	SKILL_ALCHEMY                  = 171,
	SKILL_2H_AXES                  = 172,
	SKILL_DAGGERS                  = 173,
	SKILL_THROWN                   = 176,
	SKILL_HERBALISM                = 182,
	SKILL_GENERIC_DND              = 183,
	SKILL_RETRIBUTION              = 184,
	SKILL_COOKING                  = 185,
	SKILL_MINING                   = 186,
	SKILL_PET_IMP                  = 188,
	SKILL_PET_FELHUNTER            = 189,
	SKILL_TAILORING                = 197,
	SKILL_ENGINEERING              = 202,
	SKILL_PET_SPIDER               = 203,
	SKILL_PET_VOIDWALKER           = 204,
	SKILL_PET_SUCCUBUS             = 205,
	SKILL_PET_INFERNAL             = 206,
	SKILL_PET_DOOMGUARD            = 207,
	SKILL_PET_WOLF                 = 208,
	SKILL_PET_CAT                  = 209,
	SKILL_PET_BEAR                 = 210,
	SKILL_PET_BOAR                 = 211,
	SKILL_PET_CROCILISK            = 212,
	SKILL_PET_CARRION_BIRD         = 213,
	SKILL_PET_CRAB                 = 214,
	SKILL_PET_GORILLA              = 215,
	SKILL_PET_RAPTOR               = 217,
	SKILL_PET_TALLSTRIDER          = 218,
	SKILL_RACIAL_UNDED             = 220,
	SKILL_CROSSBOWS                = 226,
	SKILL_WANDS                    = 228,
	SKILL_POLEARMS                 = 229,
	SKILL_PET_SCORPID              = 236,
	SKILL_ARCANE                   = 237,
	SKILL_PET_TURTLE               = 251,
	SKILL_ASSASSINATION            = 253,
	SKILL_FURY                     = 256,
	SKILL_PROTECTION               = 257,
	SKILL_PROTECTION2              = 267,
	SKILL_PET_TALENTS              = 270,
	SKILL_PLATE_MAIL               = 293,
	SKILL_LANG_GNOMISH             = 313,
	SKILL_LANG_TROLL               = 315,
	SKILL_ENCHANTING               = 333,
	SKILL_DEMONOLOGY               = 354,
	SKILL_AFFLICTION               = 355,
	SKILL_FISHING                  = 356,
	SKILL_ENHANCEMENT              = 373,
	SKILL_RESTORATION              = 374,
	SKILL_ELEMENTAL_COMBAT         = 375,
	SKILL_SKINNING                 = 393,
	SKILL_MAIL                     = 413,
	SKILL_LEATHER                  = 414,
	SKILL_CLOTH                    = 415,
	SKILL_SHIELD                   = 433,
	SKILL_FIST_WEAPONS             = 473,
	SKILL_RIDING_RAPTOR            = 533,
	SKILL_RIDING_MECHANOSTRIDER    = 553,
	SKILL_RIDING_UNDEAD_HORSE      = 554,
	SKILL_RESTORATION2             = 573,
	SKILL_BALANCE                  = 574,
	SKILL_DESTRUCTION              = 593,
	SKILL_HOLY2                    = 594,
	SKILL_DISCIPLINE               = 613,
	SKILL_LOCKPICKING              = 633,
	SKILL_PET_BAT                  = 653,
	SKILL_PET_HYENA                = 654,
	SKILL_PET_BIRD_OF_PREY         = 655,
	SKILL_PET_WIND_SERPENT         = 656,
	SKILL_LANG_GUTTERSPEAK         = 673,
	SKILL_RIDING_KODO              = 713,
	SKILL_RACIAL_TROLL             = 733,
	SKILL_RACIAL_GNOME             = 753,
	SKILL_RACIAL_HUMAN             = 754,
	SKILL_JEWELCRAFTING            = 755,
	SKILL_RACIAL_BLOODELF          = 756,
	SKILL_PET_EVENT_RC             = 758,
	SKILL_LANG_DRAENEI             = 759,
	SKILL_RACIAL_DRAENEI           = 760,
	SKILL_PET_FELGUARD             = 761,
	SKILL_RIDING                   = 762,
	SKILL_PET_DRAGONHAWK           = 763,
	SKILL_PET_NETHER_RAY           = 764,
	SKILL_PET_SPOREBAT             = 765,
	SKILL_PET_WARP_STALKER         = 766,
	SKILL_PET_RAVAGER              = 767,
	SKILL_PET_SERPENT              = 768,
	SKILL_INTERNAL                 = 769,
	SKILL_DK_BLOOD                 = 770,
	SKILL_DK_FROST                 = 771,
	SKILL_DK_UNHOLY                = 772,
	SKILL_INSCRIPTION              = 773,
	SKILL_PET_MOTH                 = 775,
	SKILL_RUNEFORGING              = 776,
	SKILL_MOUNTS                   = 777,
	SKILL_COMPANIONS               = 778,
	SKILL_PET_EXOTIC_CHIMAERA      = 780,
	SKILL_PET_EXOTIC_DEVILSAUR     = 781,
	SKILL_PET_GHOUL                = 782,
	SKILL_PET_EXOTIC_SILITHID      = 783,
	SKILL_PET_EXOTIC_WORM          = 784,
	SKILL_PET_WASP                 = 785,
	SKILL_PET_EXOTIC_RHINO         = 786,
	SKILL_PET_EXOTIC_CORE_HOUND    = 787,
	SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788
};

enum SkillCategory
{
	SKILL_CATEGORY_ATTRIBUTES =  5,
	SKILL_CATEGORY_WEAPON     =  6,
	SKILL_CATEGORY_CLASS      =  7,
	SKILL_CATEGORY_ARMOR      =  8,
	SKILL_CATEGORY_SECONDARY  =  9,                         // secondary professions
	SKILL_CATEGORY_LANGUAGES  = 10,
	SKILL_CATEGORY_PROFESSION = 11                          // primary professions
};

enum ItemQualities
{
	ITEM_QUALITY_POOR                  = 0,                 //GREY
	ITEM_QUALITY_NORMAL                = 1,                 //WHITE
	ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
	ITEM_QUALITY_RARE                  = 3,                 //BLUE
	ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
	ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
	ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
};

#define MAX_ITEM_QUALITY                 7

enum ResponseCodes
{
	RESPONSE_SUCCESS                       = 0x00,
	RESPONSE_FAILURE                       = 0x01,
	RESPONSE_CANCELLED                     = 0x02,
	RESPONSE_DISCONNECTED                  = 0x03,
	RESPONSE_FAILED_TO_CONNECT             = 0x04,
	RESPONSE_CONNECTED                     = 0x05,
	RESPONSE_VERSION_MISMATCH              = 0x06,

	CSTATUS_CONNECTING                     = 0x07,
	CSTATUS_NEGOTIATING_SECURITY           = 0x08,
	CSTATUS_NEGOTIATION_COMPLETE           = 0x09,
	CSTATUS_NEGOTIATION_FAILED             = 0x0A,
	CSTATUS_AUTHENTICATING                 = 0x0B,

	AUTH_OK                                = 0x0C,
	AUTH_FAILED                            = 0x0D,
	AUTH_REJECT                            = 0x0E,
	AUTH_BAD_SERVER_PROOF                  = 0x0F,
	AUTH_UNAVAILABLE                       = 0x10,
	AUTH_SYSTEM_ERROR                      = 0x11,
	AUTH_BILLING_ERROR                     = 0x12,
	AUTH_BILLING_EXPIRED                   = 0x13,
	AUTH_VERSION_MISMATCH                  = 0x14,
	AUTH_UNKNOWN_ACCOUNT                   = 0x15,
	AUTH_INCORRECT_PASSWORD                = 0x16,
	AUTH_SESSION_EXPIRED                   = 0x17,
	AUTH_SERVER_SHUTTING_DOWN              = 0x18,
	AUTH_ALREADY_LOGGING_IN                = 0x19,
	AUTH_LOGIN_SERVER_NOT_FOUND            = 0x1A,
	AUTH_WAIT_QUEUE                        = 0x1B,
	AUTH_BANNED                            = 0x1C,
	AUTH_ALREADY_ONLINE                    = 0x1D,
	AUTH_NO_TIME                           = 0x1E,
	AUTH_DB_BUSY                           = 0x1F,
	AUTH_SUSPENDED                         = 0x20,
	AUTH_PARENTAL_CONTROL                  = 0x21,

	REALM_LIST_IN_PROGRESS                 = 0x22,
	REALM_LIST_SUCCESS                     = 0x23,
	REALM_LIST_FAILED                      = 0x24,
	REALM_LIST_INVALID                     = 0x25,
	REALM_LIST_REALM_NOT_FOUND             = 0x26,

	ACCOUNT_CREATE_IN_PROGRESS             = 0x27,
	ACCOUNT_CREATE_SUCCESS                 = 0x28,
	ACCOUNT_CREATE_FAILED                  = 0x29,

	CHAR_LIST_RETRIEVING                   = 0x2A,
	CHAR_LIST_RETRIEVED                    = 0x2B,
	CHAR_LIST_FAILED                       = 0x2C,

	CHAR_CREATE_IN_PROGRESS                = 0x2D,
	CHAR_CREATE_SUCCESS                    = 0x2E,
	CHAR_CREATE_ERROR                      = 0x2F,
	CHAR_CREATE_FAILED                     = 0x30,
	CHAR_CREATE_NAME_IN_USE                = 0x31,
	CHAR_CREATE_DISABLED                   = 0x32,
	CHAR_CREATE_PVP_TEAMS_VIOLATION        = 0x33,
	CHAR_CREATE_SERVER_LIMIT               = 0x34,
	CHAR_CREATE_ACCOUNT_LIMIT              = 0x35,
	CHAR_CREATE_SERVER_QUEUE               = 0x36,
	CHAR_CREATE_ONLY_EXISTING              = 0x37,
	CHAR_CREATE_EXPANSION                  = 0x38,

	CHAR_DELETE_IN_PROGRESS                = 0x39,
	CHAR_DELETE_SUCCESS                    = 0x3A,
	CHAR_DELETE_FAILED                     = 0x3B,
	CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER = 0x3C,

	CHAR_LOGIN_IN_PROGRESS                 = 0x3D,
	CHAR_LOGIN_SUCCESS                     = 0x3E,
	CHAR_LOGIN_NO_WORLD                    = 0x3F,
	CHAR_LOGIN_DUPLICATE_CHARACTER         = 0x40,
	CHAR_LOGIN_NO_INSTANCES                = 0x41,
	CHAR_LOGIN_FAILED                      = 0x42,
	CHAR_LOGIN_DISABLED                    = 0x43,
	CHAR_LOGIN_NO_CHARACTER                = 0x44,
	CHAR_LOGIN_LOCKED_FOR_TRANSFER         = 0x45,
	CHAR_LOGIN_LOCKED_BY_BILLING           = 0x46,

	CHAR_NAME_NO_NAME                      = 0x47,
	CHAR_NAME_TOO_SHORT                    = 0x48,
	CHAR_NAME_TOO_LONG                     = 0x49,
	CHAR_NAME_INVALID_CHARACTER            = 0x4A,
	CHAR_NAME_MIXED_LANGUAGES              = 0x4B,
	CHAR_NAME_PROFANE                      = 0x4C,
	CHAR_NAME_RESERVED                     = 0x4D,
	CHAR_NAME_INVALID_APOSTROPHE           = 0x4E,
	CHAR_NAME_MULTIPLE_APOSTROPHES         = 0x4F,
	CHAR_NAME_THREE_CONSECUTIVE            = 0x50,
	CHAR_NAME_INVALID_SPACE                = 0x51,
	CHAR_NAME_CONSECUTIVE_SPACES           = 0x52,
	CHAR_NAME_FAILURE                      = 0x53,
	CHAR_NAME_SUCCESS                      = 0x54,

	CHAR_HIRE_NO_MORE						= 0x55,
	CHAR_HIRE_NOT_ENOUGH_MONEY				= 0x56,
	BUY_PHYSICAL_POWER_MAX_COUNT			= 0x57,
	BUY_PHYSICAL_POWER_FULL					= 0x58,
	BUY_PHYSICAL_NOT_ENOUGH_YUANBAO			= 0x59,
	BUY_PHYSICAL_SUCCESSFUL					= 0x5A,
	NET_CONNECT_SUCCESSFUL					= 0x5B,
	NET_CONNECT_NEED_CREATE					= 0x5C,
	NET_CONNECT_FAIL						= 0x5D,
	NET_NOT_IN_NET							= 0x5E,
	BUY_MONEY_MAX_COUNT						= 0x5F,
	BUY_MONEY_NOT_ENOUGH_YUANBAO			= 0x60,
	BUY_MONEY_SUCCESSFUL					= 0x61,
	CHAR_HIRE_INVALID_TYPE					= 0x62,
	CHAR_HIRE_NOT_ENOUGH_YUNBAO				= 0x63,
	CHAR_HIRE_NOT_ENOUGH_HONOR				= 0x64,
	CHAR_UPGRADE_SUCCESS					= 0x65,
	CHAR_UPGRADE_FAILED						= 0x66,
	CHAR_UPGRADE_ERROR_TARGET				= 0x67,
	CHAR_UPGRADE_MAX_TYPE					= 0x68,
	CHAR_UPGRADE_NOT_ENOUGH_COIN			= 0x69,
	CHAR_UPGRADE_NOT_ENOUGH_YUANBAO			= 0x6A,
	CHAR_UPGRADE_NOT_ENOUGH_HONOR			= 0x6B,
	CHAR_UPGRADE_NOT_ENOUGH_ITEM			= 0x6C,
};

enum AccountOpResult
{
	AOR_OK,
	AOR_NAME_TOO_LONG,
	AOR_PASS_TOO_LONG,
	AOR_NAME_ALREDY_EXIST,
	AOR_NAME_NOT_EXIST,
	AOR_DB_INTERNAL_ERROR,
	AOR_INVALID_REALM_ID,
	AOR_INVALID_CHARACTER,
};

enum Language
{
	LANG_GLOBAL         = 0,
	LANG_UNIVERSAL      = 0,
	LANG_ORCISH         = 1,
	LANG_DARNASSIAN     = 2,
	LANG_TAURAHE        = 3,
	LANG_DWARVISH       = 6,
	LANG_COMMON         = 7,
	LANG_DEMONIC        = 8,
	LANG_TITAN          = 9,
	LANG_THALASSIAN     = 10,
	LANG_DRACONIC       = 11,
	LANG_KALIMAG        = 12,
	LANG_GNOMISH        = 13,
	LANG_TROLL          = 14,
	LANG_GUTTERSPEAK    = 33,
	LANG_DRAENEI        = 35,
	LANG_ADDON          = 0xFFFFFFFF                        // used by addons
};

#define LANGUAGES_COUNT 17

enum ChatMsg
{
	CHAT_MSG_ADDON                  = 0xFFFFFFFF,
	CHAT_MSG_SYSTEM                 = 0x00,
	CHAT_MSG_SAY                    = 0x01,
	CHAT_MSG_PARTY                  = 0x02,
	CHAT_MSG_RAID                   = 0x03,
	CHAT_MSG_GUILD                  = 0x04,
	CHAT_MSG_OFFICER                = 0x05,
	CHAT_MSG_YELL                   = 0x06,
	CHAT_MSG_WHISPER                = 0x07,
	CHAT_MSG_WHISPER_FOREIGN        = 0x08,
	CHAT_MSG_WHISPER_INFORM         = 0x09,
	CHAT_MSG_EMOTE                  = 0x0A,
	CHAT_MSG_TEXT_EMOTE             = 0x0B,
	CHAT_MSG_MONSTER_SAY            = 0x0C,
	CHAT_MSG_MONSTER_PARTY          = 0x0D,
	CHAT_MSG_MONSTER_YELL           = 0x0E,
	CHAT_MSG_MONSTER_WHISPER        = 0x0F,
	CHAT_MSG_MONSTER_EMOTE          = 0x10,
	CHAT_MSG_CHANNEL                = 0x11,
	CHAT_MSG_CHANNEL_JOIN           = 0x12,
	CHAT_MSG_CHANNEL_LEAVE          = 0x13,
	CHAT_MSG_CHANNEL_LIST           = 0x14,
	CHAT_MSG_CHANNEL_NOTICE         = 0x15,
	CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
	CHAT_MSG_AFK                    = 0x17,
	CHAT_MSG_DND                    = 0x18,
	CHAT_MSG_IGNORED                = 0x19,
	CHAT_MSG_SKILL                  = 0x1A,
	CHAT_MSG_LOOT                   = 0x1B,
	CHAT_MSG_MONEY                  = 0x1C,
	CHAT_MSG_OPENING                = 0x1D,
	CHAT_MSG_TRADESKILLS            = 0x1E,
	CHAT_MSG_PET_INFO               = 0x1F,
	CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
	CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
	CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
	CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
	CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
	CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
	CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
	CHAT_MSG_RAID_LEADER            = 0x27,
	CHAT_MSG_RAID_WARNING           = 0x28,
	CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
	CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
	CHAT_MSG_FILTERED               = 0x2B,
	CHAT_MSG_BATTLEGROUND           = 0x2C,
	CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
	CHAT_MSG_RESTRICTED             = 0x2E,
	CHAT_MSG_BATTLENET              = 0x2F,
	CHAT_MSG_ACHIEVEMENT            = 0x30,
	CHAT_MSG_GUILD_ACHIEVEMENT      = 0x31,
	CHAT_MSG_ARENA_POINTS           = 0x32,
	CHAT_MSG_PARTY_LEADER           = 0x33
};

/// Player state
enum SessionStatus
{
	STATUS_AUTHED = 0,                                      ///< Player authenticated
	STATUS_LOGGEDIN                                         ///< Player in game
};

enum UnitDynFlags
{
	UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
	UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
	UNIT_DYNFLAG_DEAD                       = 0x0020,
	UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
	UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

#define SAFEDELETE(p) {if(p){delete p; p = NULL;}}
#define SAFEARRAYDELETE(p) {if(p){delete p; p = NULL}}

enum DiminishingGroup
{
	// Common Groups
	DIMINISHING_NONE,
	DIMINISHING_CONTROL_STUN,                               // Player Controlled stuns
	DIMINISHING_TRIGGER_STUN,                               // By aura proced stuns, usualy chance on hit talents
	DIMINISHING_CONTROL_ROOT,                               // Immobilizing effects from casted spells
	DIMINISHING_TRIGGER_ROOT,                               // Immobilizing effects from triggered spells like Frostbite
	// Shared Class Specific
	DIMINISHING_FEAR_CHARM_BLIND,                           // Fears & charm and Blind
	DIMINISHING_DISORIENT,
	DIMINISHING_HORROR,
	// Druid Specific
	DIMINISHING_CYCLONE,
	DIMINISHING_CHEAPSHOT_POUNCE,
	DIMINISHING_DISARM,                                     // From 2.3.0
	DIMINISHING_SILENCE,                                    // From 2.3.0
	DIMINISHING_FREEZE_SLEEP,                               // Hunter's Freezing Trap
	DIMINISHING_BANISH,
	// Other
	// Don't Diminish, but limit duration to 10s
	DIMINISHING_LIMITONLY
};

enum DiminishingReturnsType
{
	DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
	DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
	DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

enum SpellAttributes
{
	SPELL_ATTR_UNK0                            = 0x00000001,            // 0
	SPELL_ATTR_RANGED                          = 0x00000002,            // 1 All ranged abilites have this flag
	SPELL_ATTR_ON_NEXT_SWING_1                 = 0x00000004,            // 2 on next swing
	SPELL_ATTR_MAGIC_SPELL                     = 0x00000008,            // 3 法术
	SPELL_ATTR_UNK4                            = 0x00000010,            // 4 isAbility
	SPELL_ATTR_TRADESPELL                      = 0x00000020,            // 5 trade spells, will be added by client to a sublist of profession spell
	SPELL_ATTR_PASSIVE                         = 0x00000040,            // 6 Passive spell
	SPELL_ATTR_SERVANT_SPELL                   = 0x00000080,            // 7 仆从技能 128
	SPELL_ATTR_UNK8                            = 0x00000100,            // 8 hide created item in tooltip (for effect=24)
	SPELL_ATTR_TRIGGER_SPELL                   = 0x00000200,            // 9 触发技能 512
	SPELL_ATTR_ON_NEXT_SWING_2                 = 0x00000400,            // 10 on next swing 2
	SPELL_ATTR_CANT_DISPEL                     = 0x00000800,            // 11 不可被沉默
	SPELL_ATTR_ONLY_AFFECT_PLAYER              = 0x00001000,            // 12 区域光环只影响PLAYER
	SPELL_ATTR_NIGHT_ONLY                      = 0x00002000,            // 13 only useable at night, not set in 2.4.2
	SPELL_ATTR_INDOORS_ONLY                    = 0x00004000,            // 14 only useable indoors, not set in 2.4.2
	SPELL_ATTR_OUTDOORS_ONLY                   = 0x00008000,            // 15 Only useable outdoors.
	SPELL_ATTR_NOT_SHAPESHIFT                  = 0x00010000,            // 16 Not while shapeshifted
	SPELL_ATTR_ONLY_STEALTHED                  = 0x00020000,            // 17 Must be in stealth
	SPELL_ATTR_UNK18                           = 0x00040000,            // 18
	SPELL_ATTR_LEVEL_DAMAGE_CALCULATION        = 0x00080000,            // 19 spelldamage depends on caster level
	SPELL_ATTR_STOP_ATTACK_TARGET              = 0x00100000,            // 20 Stop attack after use this spell (and not begin attack if use)
	SPELL_ATTR_IMPOSSIBLE_DODGE_PARRY_BLOCK    = 0x00200000,            // 21 Cannot be dodged/parried/blocked
	SPELL_ATTR_SET_TRACKING_TARGET             = 0x00400000,            // 22 SetTrackingTarget
	SPELL_ATTR_UNK23                           = 0x00800000,            // 23 castable while dead?
	SPELL_ATTR_CASTABLE_WHILE_MOUNTED          = 0x01000000,            // 24 castable while mounted
	SPELL_ATTR_DISABLED_WHILE_ACTIVE           = 0x02000000,            // 25 Activate and start cooldown after aura fade or remove summoned creature or go
	SPELL_ATTR_UNK26                           = 0x04000000,            // 26
	SPELL_ATTR_CASTABLE_WHILE_SITTING          = 0x08000000,            // 27 castable while sitting
	SPELL_ATTR_CANT_USED_IN_COMBAT             = 0x10000000,            // 28 Cannot be used in combat
	SPELL_ATTR_UNAFFECTED_BY_INVULNERABILITY   = 0x20000000,            // 29 unaffected by invulnerability (hmm possible not...)
	SPELL_ATTR_UNK30                           = 0x40000000,            // 30 breakable by damage?
	SPELL_ATTR_CANT_CANCEL                     = 0x80000000,            // 31 positive aura can't be canceled
};

enum SpellAttributesEx
{
	SPELL_ATTR_EX_PERCENT                      = 0x00000001,            // 倍数
	SPELL_ATTR_EX_DRAIN_ALL_POWER              = 0x00000002,            // 1 use all power (Only paladin Lay of Hands and Bunyanize)
	SPELL_ATTR_EX_CHANNELED_1                  = 0x00000004,            // 2 channeled 1
	SPELL_ATTR_EX_ARCNAE                       = 0x00000008,            // 秘能
	SPELL_ATTR_EX_AREA_AURA_HAND               = 0x00000010,            // 区域光环影响手牌
	SPELL_ATTR_EX_NOT_BREAK_STEALTH            = 0x00000020,            // 5 Not break stealth
	SPELL_ATTR_EX_CHANNELED_2                  = 0x00000040,            // 6 channeled 2
	SPELL_ATTR_EX_NEGATIVE                     = 0x00000080,            // 7
	SPELL_ATTR_EX_NOT_IN_COMBAT_TARGET         = 0x00000100,            // 8 Spell req target not to be in combat state
	SPELL_ATTR_EX_UNK9                         = 0x00000200,            // 9
	SPELL_ATTR_EX_NO_THREAT                    = 0x00000400,            // 10 no generates threat on cast 100%
	SPELL_ATTR_EX_PLAYER_SPELL                 = 0x00000800,            // 11 英雄技能
	SPELL_ATTR_EX_UNK12                        = 0x00001000,            // 12
	SPELL_ATTR_EX_FARSIGHT                     = 0x00002000,            // 13 related to farsight
	SPELL_ATTR_EX_UNK14                        = 0x00004000,            // 14
	SPELL_ATTR_EX_DISPEL_AURAS_ON_IMMUNITY     = 0x00008000,            // 15 remove auras on immunity
	SPELL_ATTR_EX_UNAFFECTED_BY_SCHOOL_IMMUNE  = 0x00010000,            // 16 unaffected by school immunity
	SPELL_ATTR_EX_UNK17                        = 0x00020000,            // 17 for auras SPELL_AURA_TRACK_CREATURES, SPELL_AURA_TRACK_RESOURCES and SPELL_AURA_TRACK_STEALTHED select non-stacking tracking spells
	SPELL_ATTR_EX_UNK18                        = 0x00040000,            // 18
	SPELL_ATTR_EX_UNK19                        = 0x00080000,            // 19
	SPELL_ATTR_EX_REQ_TARGET_COMBO_POINTS      = 0x00100000,            // 20 Req combo points on target
	SPELL_ATTR_EX_UNK21                        = 0x00200000,            // 21
	SPELL_ATTR_EX_REQ_COMBO_POINTS             = 0x00400000,            // 22 Use combo points (in 4.x not required combo point target selected)
	SPELL_ATTR_EX_UNK23                        = 0x00800000,            // 23
	SPELL_ATTR_EX_UNK24                        = 0x01000000,            // 24 Req fishing pole??
	SPELL_ATTR_EX_UNK25                        = 0x02000000,            // 25
	SPELL_ATTR_EX_UNK26                        = 0x04000000,            // 26
	SPELL_ATTR_EX_UNK27                        = 0x08000000,            // 27
	SPELL_ATTR_EX_UNK28                        = 0x10000000,            // 28
	SPELL_ATTR_EX_UNK29                        = 0x20000000,            // 29
	SPELL_ATTR_EX_UNK30                        = 0x40000000,            // 30 overpower
	SPELL_ATTR_EX_UNK31                        = 0x80000000,            // 31
};

enum SpellAttributesEx2
{
	SPELL_ATTR_EX2_UNK0                        = 0x00000001,            // 0
	SPELL_ATTR_EX2_UNK1                        = 0x00000002,            // 1
	SPELL_ATTR_EX2_CANT_REFLECTED              = 0x00000004,            // 2 ? used for detect can or not spell reflected // do not need LOS (e.g. 18220 since 3.3.3)
	SPELL_ATTR_EX2_UNK3                        = 0x00000008,            // 3 auto targeting? (e.g. fishing skill enhancement items since 3.3.3)
	SPELL_ATTR_EX2_UNK4                        = 0x00000010,            // 4
	SPELL_ATTR_EX2_AUTOREPEAT_FLAG             = 0x00000020,            // 5
	SPELL_ATTR_EX2_UNK6                        = 0x00000040,            // 6 only usable on tabbed by yourself
	SPELL_ATTR_EX2_UNK7                        = 0x00000080,            // 7
	SPELL_ATTR_EX2_UNK8                        = 0x00000100,            // 8 not set in 3.0.3
	SPELL_ATTR_EX2_UNK9                        = 0x00000200,            // 9
	SPELL_ATTR_EX2_UNK10                       = 0x00000400,            // 10
	SPELL_ATTR_EX2_HEALTH_FUNNEL               = 0x00000800,            // 11
	SPELL_ATTR_EX2_UNK12                       = 0x00001000,            // 12
	SPELL_ATTR_EX2_UNK13                       = 0x00002000,            // 13
	SPELL_ATTR_EX2_UNK14                       = 0x00004000,            // 14
	SPELL_ATTR_EX2_UNK15                       = 0x00008000,            // 15 not set in 3.0.3
	SPELL_ATTR_EX2_UNK16                       = 0x00010000,            // 16
	SPELL_ATTR_EX2_UNK17                       = 0x00020000,            // 17 suspend weapon timer instead of resetting it, (?Hunters Shot and Stings only have this flag?)
	SPELL_ATTR_EX2_UNK18                       = 0x00040000,            // 18 Only Revive pet - possible req dead pet
	SPELL_ATTR_EX2_NOT_NEED_SHAPESHIFT         = 0x00080000,            // 19 does not necessarly need shapeshift
	SPELL_ATTR_EX2_UNK20                       = 0x00100000,            // 20
	SPELL_ATTR_EX2_DAMAGE_REDUCED_SHIELD       = 0x00200000,            // 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
	SPELL_ATTR_EX2_UNK22                       = 0x00400000,            // 22
	SPELL_ATTR_EX2_UNK23                       = 0x00800000,            // 23 Only mage Arcane Concentration have this flag
	SPELL_ATTR_EX2_UNK24                       = 0x01000000,            // 24
	SPELL_ATTR_EX2_UNK25                       = 0x02000000,            // 25
	SPELL_ATTR_EX2_UNK26                       = 0x04000000,            // 26 unaffected by school immunity
	SPELL_ATTR_EX2_UNK27                       = 0x08000000,            // 27
	SPELL_ATTR_EX2_UNK28                       = 0x10000000,            // 28 no breaks stealth if it fails??
	SPELL_ATTR_EX2_CANT_CRIT                   = 0x20000000,            // 29 Spell can't crit
	SPELL_ATTR_EX2_UNK30                       = 0x40000000,            // 30
	SPELL_ATTR_EX2_FOOD_BUFF                   = 0x80000000,            // 31 Food or Drink Buff (like Well Fed)
};

enum SpellAttributesEx3
{
	SPELL_ATTR_EX3_UNK0                        = 0x00000001,            // 0
	SPELL_ATTR_EX3_UNK1                        = 0x00000002,            // 1
	SPELL_ATTR_EX3_UNK2                        = 0x00000004,            // 2
	SPELL_ATTR_EX3_UNK3                        = 0x00000008,            // 3
	SPELL_ATTR_EX3_UNK4                        = 0x00000010,            // 4 Druid Rebirth only this spell have this flag
	SPELL_ATTR_EX3_UNK5                        = 0x00000020,            // 5
	SPELL_ATTR_EX3_UNK6                        = 0x00000040,            // 6
	SPELL_ATTR_EX3_UNK7                        = 0x00000080,            // 7 create a separate (de)buff stack for each caster
	SPELL_ATTR_EX3_UNK8                        = 0x00000100,            // 8
	SPELL_ATTR_EX3_UNK9                        = 0x00000200,            // 9
	SPELL_ATTR_EX3_MAIN_HAND                   = 0x00000400,            // 10 Main hand weapon required
	SPELL_ATTR_EX3_BATTLEGROUND                = 0x00000800,            // 11 Can casted only on battleground
	SPELL_ATTR_EX3_CAST_ON_DEAD                = 0x00001000,            // 12 target is a dead player (not every spell has this flag)
	SPELL_ATTR_EX3_UNK13                       = 0x00002000,            // 13
	SPELL_ATTR_EX3_UNK14                       = 0x00004000,            // 14 "Honorless Target" only this spells have this flag
	SPELL_ATTR_EX3_UNK15                       = 0x00008000,            // 15 Auto Shoot, Shoot, Throw,  - this is autoshot flag
	SPELL_ATTR_EX3_UNK16                       = 0x00010000,            // 16 no triggers effects that trigger on casting a spell??
	SPELL_ATTR_EX3_NO_INITIAL_AGGRO            = 0x00020000,            // 17 Causes no aggro if not missed
	SPELL_ATTR_EX3_CANT_MISS                   = 0x00040000,            // 18 Spell should always hit its target
	SPELL_ATTR_EX3_UNK19                       = 0x00080000,            // 19
	SPELL_ATTR_EX3_DEATH_PERSISTENT            = 0x00100000,            // 20 Death persistent spells
	SPELL_ATTR_EX3_UNK21                       = 0x00200000,            // 21
	SPELL_ATTR_EX3_REQ_WAND                    = 0x00400000,            // 22 Req wand
	SPELL_ATTR_EX3_UNK23                       = 0x00800000,            // 23
	SPELL_ATTR_EX3_REQ_OFFHAND                 = 0x01000000,            // 24 Req offhand weapon
	SPELL_ATTR_EX3_UNK25                       = 0x02000000,            // 25 no cause spell pushback ?
	SPELL_ATTR_EX3_UNK26                       = 0x04000000,            // 26
	SPELL_ATTR_EX3_UNK27                       = 0x08000000,            // 27
	SPELL_ATTR_EX3_UNK28                       = 0x10000000,            // 28
	SPELL_ATTR_EX3_UNK29                       = 0x20000000,            // 29
	SPELL_ATTR_EX3_UNK30                       = 0x40000000,            // 30
	SPELL_ATTR_EX3_UNK31                       = 0x80000000,            // 31
};

enum SpellAttributesEx4
{
	SPELL_ATTR_EX4_UNK0                        = 0x00000001,            // 0
	SPELL_ATTR_EX4_UNK1                        = 0x00000002,            // 1 proc on finishing move?
	SPELL_ATTR_EX4_UNK2                        = 0x00000004,            // 2
	SPELL_ATTR_EX4_UNK3                        = 0x00000008,            // 3
	SPELL_ATTR_EX4_UNK4                        = 0x00000010,            // 4 This will no longer cause guards to attack on use??
	SPELL_ATTR_EX4_UNK5                        = 0x00000020,            // 5
	SPELL_ATTR_EX4_NOT_STEALABLE               = 0x00000040,            // 6 although such auras might be dispellable, they cannot be stolen
	SPELL_ATTR_EX4_UNK7                        = 0x00000080,            // 7
	SPELL_ATTR_EX4_STACK_DOT_MODIFIER          = 0x00000100,            // 8 no effect on non DoTs?
	SPELL_ATTR_EX4_UNK9                        = 0x00000200,            // 9
	SPELL_ATTR_EX4_SPELL_VS_EXTEND_COST        = 0x00000400,            // 10 Rogue Shiv have this flag
	SPELL_ATTR_EX4_UNK11                       = 0x00000800,            // 11
	SPELL_ATTR_EX4_UNK12                       = 0x00001000,            // 12
	SPELL_ATTR_EX4_UNK13                       = 0x00002000,            // 13
	SPELL_ATTR_EX4_UNK14                       = 0x00004000,            // 14
	SPELL_ATTR_EX4_UNK15                       = 0x00008000,            // 15
	SPELL_ATTR_EX4_NOT_USABLE_IN_ARENA         = 0x00010000,            // 16 not usable in arena
	SPELL_ATTR_EX4_USABLE_IN_ARENA             = 0x00020000,            // 17 usable in arena
	SPELL_ATTR_EX4_UNK18                       = 0x00040000,            // 18
	SPELL_ATTR_EX4_UNK19                       = 0x00080000,            // 19
	SPELL_ATTR_EX4_UNK20                       = 0x00100000,            // 20 do not give "more powerful spell" error message
	SPELL_ATTR_EX4_UNK21                       = 0x00200000,            // 21
	SPELL_ATTR_EX4_UNK22                       = 0x00400000,            // 22
	SPELL_ATTR_EX4_UNK23                       = 0x00800000,            // 23
	SPELL_ATTR_EX4_UNK24                       = 0x01000000,            // 24
	SPELL_ATTR_EX4_UNK25                       = 0x02000000,            // 25 pet scaling auras
	SPELL_ATTR_EX4_CAST_ONLY_IN_OUTLAND        = 0x04000000,            // 26 Can only be used in Outland.
	SPELL_ATTR_EX4_UNK27                       = 0x08000000,            // 27
	SPELL_ATTR_EX4_UNK28                       = 0x10000000,            // 28
	SPELL_ATTR_EX4_UNK29                       = 0x20000000,            // 29
	SPELL_ATTR_EX4_UNK30                       = 0x40000000,            // 30
	SPELL_ATTR_EX4_UNK31                       = 0x80000000,            // 31
};

enum SpellAttributesEx5
{
	SPELL_ATTR_EX5_UNK0                        = 0x00000001,            // 0
	SPELL_ATTR_EX5_NO_REAGENT_WHILE_PREP       = 0x00000002,            // 1 not need reagents if Unit_FLAG_PREPARATION
	SPELL_ATTR_EX5_UNK2                        = 0x00000004,            // 2 removed at enter arena (e.g. 31850 since 3.3.3)
	SPELL_ATTR_EX5_USABLE_WHILE_STUNNED        = 0x00000008,            // 3 usable while stunned
	SPELL_ATTR_EX5_UNK4                        = 0x00000010,            // 4
	SPELL_ATTR_EX5_SINGLE_TARGET_SPELL         = 0x00000020,            // 5 Only one target can be apply at a time
	SPELL_ATTR_EX5_UNK6                        = 0x00000040,            // 6
	SPELL_ATTR_EX5_UNK7                        = 0x00000080,            // 7
	SPELL_ATTR_EX5_UNK8                        = 0x00000100,            // 8
	SPELL_ATTR_EX5_START_PERIODIC_AT_APPLY     = 0x00000200,            // 9  begin periodic tick at aura apply
	SPELL_ATTR_EX5_UNK10                       = 0x00000400,            // 10
	SPELL_ATTR_EX5_UNK11                       = 0x00000800,            // 11
	SPELL_ATTR_EX5_UNK12                       = 0x00001000,            // 12
	SPELL_ATTR_EX5_UNK13                       = 0x00002000,            // 13 haste affects duration (e.g. 8050 since 3.3.3)
	SPELL_ATTR_EX5_UNK14                       = 0x00004000,            // 14
	SPELL_ATTR_EX5_UNK15                       = 0x00008000,            // 15
	SPELL_ATTR_EX5_UNK16                       = 0x00010000,            // 16
	SPELL_ATTR_EX5_USABLE_WHILE_FEARED         = 0x00020000,            // 17 usable while feared
	SPELL_ATTR_EX5_USABLE_WHILE_CONFUSED       = 0x00040000,            // 18 usable while confused
	SPELL_ATTR_EX5_UNK19                       = 0x00080000,            // 19
	SPELL_ATTR_EX5_UNK20                       = 0x00100000,            // 20
	SPELL_ATTR_EX5_UNK21                       = 0x00200000,            // 21
	SPELL_ATTR_EX5_UNK22                       = 0x00400000,            // 22
	SPELL_ATTR_EX5_UNK23                       = 0x00800000,            // 23
	SPELL_ATTR_EX5_UNK24                       = 0x01000000,            // 24
	SPELL_ATTR_EX5_UNK25                       = 0x02000000,            // 25
	SPELL_ATTR_EX5_UNK26                       = 0x04000000,            // 26
	SPELL_ATTR_EX5_UNK27                       = 0x08000000,            // 27
	SPELL_ATTR_EX5_UNK28                       = 0x10000000,            // 28
	SPELL_ATTR_EX5_UNK29                       = 0x20000000,            // 29
	SPELL_ATTR_EX5_UNK30                       = 0x40000000,            // 30
	SPELL_ATTR_EX5_UNK31                       = 0x80000000,            // 31 Forces all nearby enemies to focus attacks caster
};

enum SpellAttributesEx6
{
	SPELL_ATTR_EX6_UNK0                        = 0x00000001,            // 0 Only Move spell have this flag
	SPELL_ATTR_EX6_ONLY_IN_ARENA               = 0x00000002,            // 1 only usable in arena, not used in 3.2.0a and early
	SPELL_ATTR_EX6_AUTO_REPEAT_IN_CLIENT       = 0x00000004,            // 2 add by zhoujy 客户端自动释放
	SPELL_ATTR_EX6_HIDE_IN_CLIENT              = 0x00000008,            // 3 add by zhoujy 客户端隐藏
	SPELL_ATTR_EX6_DOT_PERCENT                 = 0x00000010,            // 4 add by zhoujy 百分比dot
	SPELL_ATTR_EX6_KILL_PROC_FLAG              = 0x00000020,            // 5 add by zhangyuejin 杀死目标触发标志
	SPELL_ATTR_EX6_CHANNEL_SPEEL_TRIGGER       = 0x00000040,            // 6 add by zhangyuejin 引导技能需要触发
	SPELL_ATTR_EX6_CANT_USED_IN_CLIENT         = 0x00000080,            // 7 add by zhangyuejin 客户端不可用
	SPELL_ATTR_EX6_UNK8                        = 0x00000100,            // 8
	SPELL_ATTR_EX6_UNK9                        = 0x00000200,            // 9
	SPELL_ATTR_EX6_UNK10                       = 0x00000400,            // 10
	SPELL_ATTR_EX6_NOT_IN_RAID_INSTANCE        = 0x00000800,            // 11 not usable in raid instance
	SPELL_ATTR_EX6_UNK12                       = 0x00001000,            // 12 for auras SPELL_AURA_TRACK_CREATURES, SPELL_AURA_TRACK_RESOURCES and SPELL_AURA_TRACK_STEALTHED select non-stacking tracking spells
	SPELL_ATTR_EX6_UNK13                       = 0x00002000,            // 13
	SPELL_ATTR_EX6_UNK14                       = 0x00004000,            // 14
	SPELL_ATTR_EX6_UNK15                       = 0x00008000,            // 15 not set in 3.0.3
	SPELL_ATTR_EX6_UNK16                       = 0x00010000,            // 16
	SPELL_ATTR_EX6_UNK17                       = 0x00020000,            // 17
	SPELL_ATTR_EX6_UNK18                       = 0x00040000,            // 18
	SPELL_ATTR_EX6_UNK19                       = 0x00080000,            // 19
	SPELL_ATTR_EX6_UNK20                       = 0x00100000,            // 20
	SPELL_ATTR_EX6_UNK21                       = 0x00200000,            // 21
	SPELL_ATTR_EX6_UNK22                       = 0x00400000,            // 22
	SPELL_ATTR_EX6_UNK23                       = 0x00800000,            // 23 not set in 3.0.3
	SPELL_ATTR_EX6_UNK24                       = 0x01000000,            // 24 not set in 3.0.3
	SPELL_ATTR_EX6_UNK25                       = 0x02000000,            // 25 not set in 3.0.3
	SPELL_ATTR_EX6_UNK26                       = 0x04000000,            // 26 not set in 3.0.3
	SPELL_ATTR_EX6_UNK27                       = 0x08000000,            // 27 not set in 3.0.3
	SPELL_ATTR_EX6_UNK28                       = 0x10000000,            // 28 not set in 3.0.3
	SPELL_ATTR_EX6_NO_DMG_MODS                 = 0x20000000,            // 29 do not apply damage mods (usually in cases where it has already been applied)
	SPELL_ATTR_EX6_UNK30                       = 0x40000000,            // 30 not set in 3.0.3
	SPELL_ATTR_EX6_UNK31                       = 0x80000000,            // 31 not set in 3.0.3
};

enum SpellAttributesEx7
{
	SPELL_ATTR_EX7_UNK0                        = 0x00000001,            // 0
	SPELL_ATTR_EX7_UNK1                        = 0x00000002,            // 1
	SPELL_ATTR_EX7_PALADIN_AURA                = 0x00000004,            // 2
	SPELL_ATTR_EX7_UNK3                        = 0x00000008,            // 3
	SPELL_ATTR_EX7_UNK4                        = 0x00000010,            // 4
	SPELL_ATTR_EX7_TOTEM_SPELL                 = 0x00000020,            // 5  shaman summon totem spells
	SPELL_ATTR_EX7_UNK6                        = 0x00000040,            // 6
	SPELL_ATTR_EX7_UNK7                        = 0x00000080,            // 7
	SPELL_ATTR_EX7_UNK8                        = 0x00000100,            // 8
	SPELL_ATTR_EX7_UNK9                        = 0x00000200,            // 9
	SPELL_ATTR_EX7_UNK10                       = 0x00000400,            // 10
	SPELL_ATTR_EX7_UNK11                       = 0x00000800,            // 11
	SPELL_ATTR_EX7_UNK12                       = 0x00001000,            // 12
	SPELL_ATTR_EX7_UNK13                       = 0x00002000,            // 13
	SPELL_ATTR_EX7_UNK14                       = 0x00004000,            // 14
	SPELL_ATTR_EX7_UNK15                       = 0x00008000,            // 15
	SPELL_ATTR_EX7_UNK16                       = 0x00010000,            // 16
	SPELL_ATTR_EX7_UNK17                       = 0x00020000,            // 17
	SPELL_ATTR_EX7_UNK18                       = 0x00040000,            // 18
	SPELL_ATTR_EX7_UNK19                       = 0x00080000,            // 19
	SPELL_ATTR_EX7_UNK20                       = 0x00100000,            // 20
	SPELL_ATTR_EX7_UNK21                       = 0x00200000,            // 21
	SPELL_ATTR_EX7_UNK22                       = 0x00400000,            // 22
	SPELL_ATTR_EX7_UNK23                       = 0x00800000,            // 23
	SPELL_ATTR_EX7_UNK24                       = 0x01000000,            // 24
	SPELL_ATTR_EX7_UNK25                       = 0x02000000,            // 25
	SPELL_ATTR_EX7_UNK26                       = 0x04000000,            // 26
	SPELL_ATTR_EX7_UNK27                       = 0x08000000,            // 27
	SPELL_ATTR_EX7_UNK28                       = 0x10000000,            // 28
	SPELL_ATTR_EX7_UNK29                       = 0x20000000,            // 29
	SPELL_ATTR_EX7_UNK30                       = 0x40000000,            // 30
	SPELL_ATTR_EX7_UNK31                       = 0x80000000,            // 31
};

enum DamageEffectType
{
	DIRECT_DAMAGE           = 0,                            // used for normal weapon damage (not for class abilities or spells)
	SPELL_DIRECT_DAMAGE     = 1,                            // spell/class abilities damage
	DOT                     = 2,
	HEAL                    = 3,
	NODAMAGE                = 4,                            // used also in case when damage applied to health but not applied to spell channelInterruptFlags/etc
	SELF_DAMAGE             = 5
};

enum WeaponAttackType
{
	BASE_ATTACK   = 0,
	OFF_ATTACK    = 1,
	RANGED_ATTACK = 2
};

#define MAX_ATTACK  3

enum SpellImmunity
{
	IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
	IMMUNITY_STATE                 = 1,                     // enum AuraType
	IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
	IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
	IMMUNITY_DISPEL                = 4,                     // enum DispelType
	IMMUNITY_MECHANIC              = 5                      // enum Mechanics
};

#define MAX_SPELL_IMMUNITY           6

enum GameobjectTypes
{
	GAMEOBJECT_TYPE_DOOR                   = 0,
	GAMEOBJECT_TYPE_BUTTON                 = 1,
	GAMEOBJECT_TYPE_QUESTGIVER             = 2,
	GAMEOBJECT_TYPE_CHEST                  = 3,
	GAMEOBJECT_TYPE_BINDER                 = 4,
	GAMEOBJECT_TYPE_GENERIC                = 5,
	GAMEOBJECT_TYPE_TRAP                   = 6,
	GAMEOBJECT_TYPE_CHAIR                  = 7,
	GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
	GAMEOBJECT_TYPE_TEXT                   = 9,
	GAMEOBJECT_TYPE_GOOBER                 = 10,
	GAMEOBJECT_TYPE_TRANSPORT              = 11,
	GAMEOBJECT_TYPE_AREADAMAGE             = 12,
	GAMEOBJECT_TYPE_CAMERA                 = 13,
	GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
	GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
	GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
	GAMEOBJECT_TYPE_FISHINGNODE            = 17,
	GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
	GAMEOBJECT_TYPE_MAILBOX                = 19,
	GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
	GAMEOBJECT_TYPE_GUARDPOST              = 21,
	GAMEOBJECT_TYPE_SPELLCASTER            = 22,
	GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
	GAMEOBJECT_TYPE_FLAGSTAND              = 24,
	GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
	GAMEOBJECT_TYPE_FLAGDROP               = 26,
	GAMEOBJECT_TYPE_MINI_GAME              = 27,
	GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
	GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
	GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
	GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
	GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
	GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
	GAMEOBJECT_TYPE_GUILD_BANK             = 34,
	GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

#define MAX_GAMEOBJECT_TYPE                  36             // sending to client this or greater value can crash client.

enum GameObjectFlags
{
	GO_FLAG_IN_USE          = 0x00000001,                   //disables interaction while animated
	GO_FLAG_LOCKED          = 0x00000002,                   //require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
	GO_FLAG_INTERACT_COND   = 0x00000004,                   //cannot interact (condition to interact)
	GO_FLAG_TRANSPORT       = 0x00000008,                   //any kind of transport? Object can transport (elevator, boat, car)
	GO_FLAG_NO_INTERACT     = 0x00000010,                   //players cannot interact with this go (often need to remove flag in event)
	GO_FLAG_NODESPAWN       = 0x00000020,                   //never despawn, typically for doors, they just change state
	GO_FLAG_TRIGGERED       = 0x00000040,                   //typically, summoned objects. Triggered by spell or other events
	GO_FLAG_UNK_8           = 0x00000080,
	GO_FLAG_UNK_9           = 0x00000100,                   //? Seen on type 33, possible meaning "destruct in progress"
	GO_FLAG_UNK_10          = 0x00000200,                   //? Seen on type 33
	GO_FLAG_UNK_11          = 0x00000400                    //? Seen on type 33, possibly meaning "destructed"
};

enum GameObjectDynamicLowFlags
{
	GO_DYNFLAG_LO_ACTIVATE          = 0x01,                 // enables interaction with GO
	GO_DYNFLAG_LO_ANIMATE           = 0x02,                 // possibly more distinct animation of GO
	GO_DYNFLAG_LO_NO_INTERACT       = 0x04,                 // appears to disable interaction (not fully verified)
	GO_DYNFLAG_LO_SPARKLE           = 0x08,                 // makes GO sparkle
};

// CreatureFamily.dbc
enum CreatureFamily
{
	CREATURE_FAMILY_WOLF           = 1,
	CREATURE_FAMILY_CAT            = 2,
	CREATURE_FAMILY_SPIDER         = 3,
	CREATURE_FAMILY_BEAR           = 4,
	CREATURE_FAMILY_BOAR           = 5,
	CREATURE_FAMILY_CROCOLISK      = 6,
	CREATURE_FAMILY_CARRION_BIRD   = 7,
	CREATURE_FAMILY_CRAB           = 8,
	CREATURE_FAMILY_GORILLA        = 9,
	CREATURE_FAMILY_HORSE_CUSTOM   = 10,                    // not exist in DBC but used for horse like beasts in DB
	CREATURE_FAMILY_RAPTOR         = 11,
	CREATURE_FAMILY_TALLSTRIDER    = 12,
	CREATURE_FAMILY_FELHUNTER      = 15,
	CREATURE_FAMILY_VOIDWALKER     = 16,
	CREATURE_FAMILY_SUCCUBUS       = 17,
	CREATURE_FAMILY_DOOMGUARD      = 19,
	CREATURE_FAMILY_SCORPID        = 20,
	CREATURE_FAMILY_TURTLE         = 21,
	CREATURE_FAMILY_IMP            = 23,
	CREATURE_FAMILY_BAT            = 24,
	CREATURE_FAMILY_HYENA          = 25,
	CREATURE_FAMILY_BIRD_OF_PREY   = 26,
	CREATURE_FAMILY_WIND_SERPENT   = 27,
	CREATURE_FAMILY_REMOTE_CONTROL = 28,
	CREATURE_FAMILY_FELGUARD       = 29,
	CREATURE_FAMILY_DRAGONHAWK     = 30,
	CREATURE_FAMILY_RAVAGER        = 31,
	CREATURE_FAMILY_WARP_STALKER   = 32,
	CREATURE_FAMILY_SPOREBAT       = 33,
	CREATURE_FAMILY_NETHER_RAY     = 34,
	CREATURE_FAMILY_SERPENT        = 35,
	CREATURE_FAMILY_MOTH           = 37,
	CREATURE_FAMILY_CHIMAERA       = 38,
	CREATURE_FAMILY_DEVILSAUR      = 39,
	CREATURE_FAMILY_GHOUL          = 40,
	CREATURE_FAMILY_SILITHID       = 41,
	CREATURE_FAMILY_WORM           = 42,
	CREATURE_FAMILY_RHINO          = 43,
	CREATURE_FAMILY_WASP           = 44,
	CREATURE_FAMILY_CORE_HOUND     = 45,
	CREATURE_FAMILY_SPIRIT_BEAST   = 46
};

enum CreatureTypeFlags
{
	CREATURE_TYPEFLAGS_TAMEABLE         = 0x00000001,       // Tameable by any hunter
	CREATURE_TYPEFLAGS_GHOST_VISIBLE    = 0x00000002,       // Creatures which can _also_ be seen when player is a ghost, used in CanInteract function by client, can't be attacked
	CREATURE_TYPEFLAGS_UNK3             = 0x00000004,       // "BOSS" flag for tooltips
	CREATURE_TYPEFLAGS_UNK4             = 0x00000008,
	CREATURE_TYPEFLAGS_UNK5             = 0x00000010,       // controls something in client tooltip related to creature faction
	CREATURE_TYPEFLAGS_UNK6             = 0x00000020,       // may be sound related
	CREATURE_TYPEFLAGS_UNK7             = 0x00000040,       // may be related to attackable / not attackable creatures with spells, used together with lua_IsHelpfulSpell/lua_IsHarmfulSpell
	CREATURE_TYPEFLAGS_UNK8             = 0x00000080,       // has something to do with unit interaction / quest status requests
	CREATURE_TYPEFLAGS_HERBLOOT         = 0x00000100,       // Can be looted by herbalist
	CREATURE_TYPEFLAGS_MININGLOOT       = 0x00000200,       // Can be looted by miner
	CREATURE_TYPEFLAGS_UNK11            = 0x00000400,       // no idea, but it used by client
	CREATURE_TYPEFLAGS_UNK12            = 0x00000800,       // related to possibility to cast spells while mounted
	CREATURE_TYPEFLAGS_CAN_ASSIST       = 0x00001000,       // Can aid any player (and group) in combat. Typically seen for escorting NPC's
	CREATURE_TYPEFLAGS_UNK14            = 0x00002000,       // checked from calls in Lua_PetHasActionBar
	CREATURE_TYPEFLAGS_UNK15            = 0x00004000,       // Lua_UnitGUID, client does guid_low &= 0xFF000000 if this flag is set
	CREATURE_TYPEFLAGS_ENGINEERLOOT     = 0x00008000,       // Can be looted by engineer
	CREATURE_TYPEFLAGS_EXOTIC           = 0x00010000,       // Can be tamed by hunter as exotic pet
	CREATURE_TYPEFLAGS_UNK18            = 0x00020000,       // related to CreatureDisplayInfo and scaling in some way
	CREATURE_TYPEFLAGS_UNK19            = 0x00040000,       // ? Related to vehicle/siege weapons?
	CREATURE_TYPEFLAGS_UNK20            = 0x00080000,       // may be has something to do with missiles
	CREATURE_TYPEFLAGS_UNK21            = 0x00100000,       // no idea, but it used by client, may be related to rendering
	CREATURE_TYPEFLAGS_UNK22            = 0x00200000,       // may be has something to do with animation (disable animation?)
	CREATURE_TYPEFLAGS_UNK23            = 0x00400000,       // this one probably controls some creature visual
	CREATURE_TYPEFLAGS_SQUIRE           = 0x00800000,       // First seen in 3.2.2. Related to banner/backpack of creature/companion, used in CanInteract function by client
	CREATURE_TYPEFLAGS_UNK25            = 0x01000000,       // pet sounds related?
	CREATURE_TYPEFLAGS_UNK26            = 0x02000000,       // this one probably controls some creature visual
	CREATURE_TYPEFLAGS_UNK27            = 0x04000000,       // creature has no type, or forces creature to be considered as in party, may be related to creature assistance
	CREATURE_TYPEFLAGS_UNK28            = 0x08000000,       // used in Lua_ForceGossip
	CREATURE_TYPEFLAGS_UNK29            = 0x10000000,       // no idea, but it used by client
	CREATURE_TYPEFLAGS_UNK30            = 0x20000000,
	CREATURE_TYPEFLAGS_UNK31            = 0x40000000,
	CREATURE_TYPEFLAGS_QUEST_BOSS       = 0x80000000,       // Lua_UnitIsQuestBoss
};

enum TempSummonType
{
	TEMPSUMMON_TIMED_OR_DEAD_DESPAWN       = 1,             // despawns after a specified time OR when the creature disappears
	TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN     = 2,             // despawns after a specified time OR when the creature dies
	TEMPSUMMON_TIMED_DESPAWN               = 3,             // despawns after a specified time
	TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT = 4,             // despawns after a specified time after the creature is out of combat
	TEMPSUMMON_CORPSE_DESPAWN              = 5,             // despawns instantly after death
	TEMPSUMMON_CORPSE_TIMED_DESPAWN        = 6,             // despawns after a specified time after death
	TEMPSUMMON_DEAD_DESPAWN                = 7,             // despawns when the creature disappears
	TEMPSUMMON_MANUAL_DESPAWN              = 8              // despawns when UnSummon() is called

};

enum AiReaction
{
	AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
	AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
	AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
	AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
	AI_REACTION_DESTROY  = 4,                               // used on object destroy (NOT used in client packet handler)
};

enum AbilytyLearnType
{
	ABILITY_LEARNED_ON_GET_PROFESSION_SKILL     = 1,
	ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL  = 2
};

enum AbilitySkillFlags
{
	ABILITY_SKILL_NONTRAINABLE = 0x100
};

enum ItemEnchantmentType
{
	ITEM_ENCHANTMENT_TYPE_NONE             = 0,
	ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL     = 1,
	ITEM_ENCHANTMENT_TYPE_DAMAGE           = 2,
	ITEM_ENCHANTMENT_TYPE_EQUIP_SPELL      = 3,
	ITEM_ENCHANTMENT_TYPE_RESISTANCE       = 4,
	ITEM_ENCHANTMENT_TYPE_STAT             = 5,
	ITEM_ENCHANTMENT_TYPE_TOTEM            = 6,
	ITEM_ENCHANTMENT_TYPE_USE_SPELL        = 7,
	ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET = 8
};

enum ItemLimitCategoryMode
{
	ITEM_LIMIT_CATEGORY_MODE_HAVE  = 0,                      // limit applied to amount items in inventory/bank
	ITEM_LIMIT_CATEGORY_MODE_EQUIP = 1,                      // limit applied to amount equipped items (including used gems)
};

// some used in code cases
enum ItemLimitCategory
{
	ITEM_LIMIT_CATEGORY_MANA_GEM   = 4,
};

enum TotemCategoryType
{
	TOTEM_CATEGORY_TYPE_KNIFE   = 1,
	TOTEM_CATEGORY_TYPE_TOTEM   = 2,
	TOTEM_CATEGORY_TYPE_ROD     = 3,
	TOTEM_CATEGORY_TYPE_PICK    = 21,
	TOTEM_CATEGORY_TYPE_STONE   = 22,
	TOTEM_CATEGORY_TYPE_HAMMER  = 23,
	TOTEM_CATEGORY_TYPE_SPANNER = 24
};

enum SummonPropGroup
{
	SUMMON_PROP_GROUP_WILD              = 0,
	SUMMON_PROP_GROUP_FRIENDLY          = 1,
	SUMMON_PROP_GROUP_PETS              = 2,
	SUMMON_PROP_GROUP_CONTROLLABLE      = 3,
	SUMMON_PROP_GROUP_VEHICLE           = 4
};


// SummonProperties.dbc, col 2          == FactionId        (m_faction)
// SummonProperties.dbc, col 3          == Title            (m_title)
enum UnitNameSummonTitle
{
	UNITNAME_SUMMON_TITLE_NONE          = 0,                // no default title, different summons, 1330 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_PET           = 1,                // 's Pet,           generic summons, 49 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_GUARDIAN      = 2,                // 's Guardian,      summon guardian, 393 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_MINION        = 3,                // 's Minion,        summon army, 5 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_TOTEM         = 4,                // 's Totem,         summon totem, 169 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_COMPANION     = 5,                // 's Companion,     critter/minipet, 195 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_RUNEBLADE     = 6,                // 's Runeblade,     summon DRW/Ghoul, 2 spells in 3.0.3"
	UNITNAME_SUMMON_TITLE_CONSTRUCT     = 7,                // 's Construct,     summon bot/bomb, 4 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_OPPONENT      = 8,                // 's Opponent,      something todo with DK prequest line, 2 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_VEHICLE       = 9,                // 's Vehicle,       summon different vehicles, 14 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_MOUNT         = 10,               // 's Mount,         summon drake (vehicle), 3 spells
	UNITNAME_SUMMON_TITLE_LIGHTWELL     = 11,               // 's Lightwell,     summon lightwell, 6 spells in 3.0.3
	UNITNAME_SUMMON_TITLE_BUTLER        = 12                // 's Butler,        summon repair bot, 1 spells in 3.2.2a
};

// SummonProperties.dbc, col 4          == Slot             (m_slot)
// SummonProperties.dbc, col 5          == Flags            (m_flags)
enum SummonPropFlags
{
	SUMMON_PROP_FLAG_NONE               = 0x0000,           // 1342 spells in 3.0.3
	SUMMON_PROP_FLAG_UNK1               = 0x0001,           // 75 spells in 3.0.3, something unfriendly
	SUMMON_PROP_FLAG_UNK2               = 0x0002,           // 616 spells in 3.0.3, something friendly
	SUMMON_PROP_FLAG_UNK3               = 0x0004,           // 22 spells in 3.0.3, no idea...
	SUMMON_PROP_FLAG_UNK4               = 0x0008,           // 49 spells in 3.0.3, some mounts
	SUMMON_PROP_FLAG_UNK5               = 0x0010,           // 25 spells in 3.0.3, quest related?
	SUMMON_PROP_FLAG_CANT_BE_DISMISSED  = 0x0020,           // 0 spells in 3.0.3, unused
	SUMMON_PROP_FLAG_UNK7               = 0x0040,           // 12 spells in 3.0.3, no idea
	SUMMON_PROP_FLAG_UNK8               = 0x0080,           // 4 spells in 3.0.3, no idea
	SUMMON_PROP_FLAG_UNK9               = 0x0100,           // 51 spells in 3.0.3, no idea, many quest related
	SUMMON_PROP_FLAG_UNK10              = 0x0200,           // 51 spells in 3.0.3, something defensive
	SUMMON_PROP_FLAG_UNK11              = 0x0400,           // 3 spells, requires something near?
	SUMMON_PROP_FLAG_UNK12              = 0x0800,           // 30 spells in 3.0.3, no idea
	SUMMON_PROP_FLAG_UNK13              = 0x1000,           // 8 spells in 3.0.3, siege vehicle
	SUMMON_PROP_FLAG_UNK14              = 0x2000,           // 2 spells in 3.0.3, escort?
};

// In fact !=0 values is alliance/horde root faction ids
enum Team
{
	TEAM_NONE           = 0,                                // used when team value unknown or not set, 0 is also meaning that can be used !team check
	TEAM_BOTH_ALLOWED   = 0,                                // used when a check should evaluate true for both teams
	TEAM_INVALID        = 1,                                // used to invalidate some team depending checks (means not for both teams)
	HORDE               = 67,
	ALLIANCE            = 469,
};

// values based at Holidays.dbc
enum HolidayIds
{
	HOLIDAY_NONE                     = 0,

	HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
	HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
	HOLIDAY_NOBLEGARDEN              = 181,
	HOLIDAY_CHILDRENS_WEEK           = 201,
	HOLIDAY_CALL_TO_ARMS_AV          = 283,
	HOLIDAY_CALL_TO_ARMS_WS          = 284,
	HOLIDAY_CALL_TO_ARMS_AB          = 285,
	HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
	HOLIDAY_HARVEST_FESTIVAL         = 321,
	HOLIDAY_HALLOWS_END              = 324,
	HOLIDAY_LUNAR_FESTIVAL           = 327,
	HOLIDAY_LOVE_IS_IN_THE_AIR       = 335,
	HOLIDAY_FIRE_FESTIVAL            = 341,
	HOLIDAY_CALL_TO_ARMS_EY          = 353,
	HOLIDAY_BREWFEST                 = 372,
	HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
	HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
	HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
	HOLIDAY_PIRATES_DAY              = 398,
	HOLIDAY_CALL_TO_ARMS_SA          = 400,
	HOLIDAY_PILGRIMS_BOUNTY          = 404,
	HOLIDAY_WOTLK_LAUNCH             = 406,
	HOLIDAY_DAY_OF_DEAD              = 409,
	HOLIDAY_CALL_TO_ARMS_ISLE_OF_C   = 420
};

// GameEvent stat 
enum GameEventOp
{
	GAME_EVENT_OP_START = 1,
	GAME_EVENT_OP_STOP = 2 ,
	GAME_EVENT_OP_RUNNING = 3,
	GAME_EVENT_OP_MAX = 4
};

enum GameEventType
{
	GAME_EVENTTYPE_NONE = 0,
	GAME_EVENTTYPE_BUY_BOUNS = 1,
	GAME_EVENTTYPE_EXTRA_ITEM = 2,
	GAME_EVENTTYPE_EXTRA_SCENE = 3,
	GAME_EVENTTYPE_EXTRA_ARENA = 4,
	GAME_EVENTTYPE_MAX
};

enum ProductType  //对应ProductShowInfo的flag
{
	GAME_PRODUCT_YUANBAO = 0, //钻石
	GAME_PRODUCT_MONTHCARD = 1, //月卡
};

enum MonthCardProperty
{
	MONTH_CARD_TYPE_VISIBLE       = 0,
	MONTH_CARD_TYPE_CANT_VISIBLE  = 1,
	MONTH_CARD_TYPE_CAN_REWARD    = 2,
	MONTH_CARD_TYPE_NEED_BUY      = 3,
};

#define MAX_TALENT_SPEC_COUNT   2
#define MAX_GLYPH_SLOT_INDEX    6

enum SheathTypes
{
	SHEATHETYPE_NONE                   = 0,
	SHEATHETYPE_MAINHAND               = 1,
	SHEATHETYPE_OFFHAND                = 2,
	SHEATHETYPE_LARGEWEAPONLEFT        = 3,
	SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
	SHEATHETYPE_HIPWEAPONLEFT          = 5,
	SHEATHETYPE_HIPWEAPONRIGHT         = 6,
	SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum TradeStatus
{
	TRADE_STATUS_BUSY           = 0,
	TRADE_STATUS_BEGIN_TRADE    = 1,
	TRADE_STATUS_OPEN_WINDOW    = 2,
	TRADE_STATUS_TRADE_CANCELED = 3,
	TRADE_STATUS_TRADE_ACCEPT   = 4,
	TRADE_STATUS_BUSY_2         = 5,
	TRADE_STATUS_NO_TARGET      = 6,
	TRADE_STATUS_BACK_TO_TRADE  = 7,
	TRADE_STATUS_TRADE_COMPLETE = 8,
	// 9?
	TRADE_STATUS_TARGET_TO_FAR  = 10,
	TRADE_STATUS_WRONG_FACTION  = 11,
	TRADE_STATUS_CLOSE_WINDOW   = 12,
	// 13?
	TRADE_STATUS_IGNORE_YOU     = 14,
	TRADE_STATUS_YOU_STUNNED    = 15,
	TRADE_STATUS_TARGET_STUNNED = 16,
	TRADE_STATUS_YOU_DEAD       = 17,
	TRADE_STATUS_TARGET_DEAD    = 18,
	TRADE_STATUS_YOU_LOGOUT     = 19,
	TRADE_STATUS_TARGET_LOGOUT  = 20,
	TRADE_STATUS_TRIAL_ACCOUNT  = 21,                       // Trial accounts can not perform that action
	TRADE_STATUS_ONLY_CONJURED  = 22                        // You can only trade conjured items... (cross realm BG related).
};

enum SpellEffectIndex
{
	EFFECT_INDEX_0     = 0,
	EFFECT_INDEX_1     = 1,
	EFFECT_INDEX_2     = 2
};

const int  MAX_EFFECT_INDEX = 3;

enum CharacterSlot
{
	SLOT_HEAD                          = 0,
	SLOT_NECK                          = 1,
	SLOT_SHOULDERS                     = 2,
	SLOT_SHIRT                         = 3,
	SLOT_CHEST                         = 4,
	SLOT_WAIST                         = 5,
	SLOT_LEGS                          = 6,
	SLOT_FEET                          = 7,
	SLOT_WRISTS                        = 8,
	SLOT_HANDS                         = 9,
	SLOT_FINGER1                       = 10,
	SLOT_FINGER2                       = 11,
	SLOT_TRINKET1                      = 12,
	SLOT_TRINKET2                      = 13,
	SLOT_BACK                          = 14,
	SLOT_MAIN_HAND                     = 15,
	SLOT_OFF_HAND                      = 16,
	SLOT_RANGED                        = 17,
	SLOT_TABARD                        = 18,
	SLOT_EMPTY                         = 19
};

enum MoneyConstants
{
	COPPER = 1,
	SILVER = COPPER*100,
	GOLD   = SILVER*100
};

// Client expected level limitation, like as used in DBC item max levels for "until max player level"
// use as default max player level, must be fit max level for used client
// also see MAX_LEVEL and STRONG_MAX_LEVEL define
#define DEFAULT_MAX_LEVEL 70

// client supported max level for player/pets/etc. Avoid overflow or client stability affected.
// also see GT_MAX_LEVEL define
#define MAX_LEVEL    100

// Server side limitation. Base at used code requirements.
// also see MAX_LEVEL and GT_MAX_LEVEL define
#define STRONG_MAX_LEVEL 255

#define MAX_PLAYER_NAME          12                         // max allowed by client name length
#define MAX_INTERNAL_PLAYER_NAME 15                         // max server internal player name length ( > MAX_PLAYER_NAME for support declined names )
#define MAX_PET_NAME             12                         // max allowed by client name length
#define MAX_CHARTER_NAME         24                         // max allowed by client name length


enum QuestSlotOffsets
{
	QUEST_ID_OFFSET         = 0,
	QUEST_STATE_OFFSET      = 1,
	QUEST_COUNTS_OFFSET     = 2,                            // 2 and 3
	QUEST_TIME_OFFSET       = 4
};

enum QuestSlotStateMask
{
	QUEST_STATE_NONE     = 0x0000,
	QUEST_STATE_COMPLETE = 0x0001,
	QUEST_STATE_FAIL     = 0x0002
};

enum SceneType
{
	SCENE_TYPE_MISSION		= 0,		// 剧情关卡
	SCENE_TYPE_HERO			= 1,		// 英雄关卡
	SCENE_TYPE_CHALLENGE	= 2,		// 挑战关卡
	SCENE_TYPE_CLASS		= 3,		// 职业关卡
	SCENE_TYPE_BATTLE		= 4,		// 竞技场关卡
	SCENE_TYPE_FUN			= 5,		// 娱乐关卡	
	SCENE_TYPE_END			= 6,		// 关卡类型结束
};

enum EnterSceneRet
{
	SCENE_ENTER_SUCCESSFUL			= 0,
	SCENE_ENTER_NOT_ENOUGH_LEVEL	= 1,
	SCENE_ENTER_NOT_ENOUGH_POWER	= 2,
	SCENE_ENTER_NOT_HAVE_MISSION	= 3,
	SCENE_ENTER_PRE_SCENE_NOT_COMPLETE = 4,
	SCENE_ENTER_IN_COOLDOWN			= 5,
	SCENE_ENTER_FAIL				= 6,
	SCENE_ENTER_OVER_MAX_PLAYER_COUNT = 7,
	SCENE_ENTER_LACKOF_CLASS		= 8,
	SCENE_ENTER_NOT_REPEATABLE		= 9,
	SCENE_ENTER_NOT_ENOUGH_MONEY	= 10,
	SCENE_ENTER_NOT_ENOUGH_YUANBAO	= 11,
	SCENE_ENTER_NOT_ENOUGH_ITEM		= 12,
};

enum GambleCardRet
{
	GAMBLE_CARD_SUCCESSFUL			= 0,
	GAMBLE_CARD_FAIL				= 1,
	GAMBLE_CARD_CANNOT_GAMBLE		= 2,
	GAMBLE_CARD_NOT_ENOUGH_MONEY	= 3,
};

enum SceneAgentOpRet
{
	SCENE_AGENT_OP_START			= 0,
	SCENE_AGENT_OP_CANCEL			= 1,
};

enum BattleFieldOPRet
{
	BATTLE_FIELD_OP_SUCCESSFUL		= 0,
	BATTLE_FIELD_OP_FAILED			= 1,
	BATTLE_FIELD_OP_WRONG_VERSION	= 2,
};

#define BATTLE_FIELD_MAP_ENTRY 7001

enum AuthResult
{
	WOW_SUCCESS                     = 0x00,
	WOW_FAIL_UNKNOWN0               = 0x01,                 ///< ? Unable to connect
	WOW_FAIL_UNKNOWN1               = 0x02,                 ///< ? Unable to connect
	WOW_FAIL_BANNED                 = 0x03,                 ///< This <game> account has been closed and is no longer available for use. Please go to <site>/banned.html for further information.
	WOW_FAIL_UNKNOWN_ACCOUNT        = 0x04,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
	WOW_FAIL_INCORRECT_PASSWORD     = 0x05,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
	// client reject next login attempts after this error, so in code used WOW_FAIL_UNKNOWN_ACCOUNT for both cases
	WOW_FAIL_ALREADY_ONLINE         = 0x06,                 ///< This account is already logged into <game>. Please check the spelling and try again.
	WOW_FAIL_NO_TIME                = 0x07,                 ///< You have used up your prepaid time for this account. Please purchase more to continue playing
	WOW_FAIL_DB_BUSY                = 0x08,                 ///< Could not log in to <game> at this time. Please try again later.
	WOW_FAIL_VERSION_INVALID        = 0x09,                 ///< Unable to validate game version. This may be caused by file corruption or interference of another program. Please visit <site> for more information and possible solutions to this issue.
	WOW_FAIL_VERSION_UPDATE         = 0x0A,                 ///< Downloading
	WOW_FAIL_INVALID_SERVER         = 0x0B,                 ///< Unable to connect
	WOW_FAIL_SUSPENDED              = 0x0C,                 ///< This <game> account has been temporarily suspended. Please go to <site>/banned.html for further information
	WOW_FAIL_FAIL_NOACCESS          = 0x0D,                 ///< Unable to connect
	WOW_SUCCESS_SURVEY              = 0x0E,                 ///< Connected.
	WOW_FAIL_PARENTCONTROL          = 0x0F,                 ///< Access to this account has been blocked by parental controls. Your settings may be changed in your account preferences at <site>
	WOW_FAIL_LOCKED_ENFORCED        = 0x10,                 ///< You have applied a lock to your account. You can change your locked status by calling your account lock phone number.
	WOW_FAIL_TRIAL_ENDED            = 0x11,                 ///< Your trial subscription has expired. Please visit <site> to upgrade your account.
	WOW_FAIL_USE_BATTLENET          = 0x12,                 ///< WOW_FAIL_OTHER This account is now attached to a Battle.net account. Please login with your Battle.net account email address and password.
};

enum EventLogType
{
	EVENT_LOG_BEGIN					= 1,
	EVENT_LOG_TIME_DATA				= 1,					/// 定时发送的数据
	EVENT_LOG_STAGE_ENTER			= 2,					/// 进入任意关卡,不含重试
	EVENT_LOG_STAGE_RETRY			= 3,					/// 重试任意关卡
	EVENT_LOG_STAGE_RETREAT			= 4,					/// 退出任意关卡,关卡失败导致的退出
	EVENT_LOG_STAGE_CLEAR			= 5,					/// 胜利通关任意关卡
	EVENT_LOG_ARENA_ENTER			= 6,					/// 开始竞技场挑战
	EVENT_LOG_ARENA_CLEAR			= 7,					/// 竞技场挑战结束时
	EVENT_LOG_BUY_CHAR				= 8,					/// 购买角色成功时
	EVENT_LOG_BUY_ITEM				= 9,					/// 购买物品成功时
	EVENT_LOG_BUY_GOLD				= 10,					/// 购买金币成功时
	EVENT_LOG_BUY_ENERGY			= 11,					/// 购买体力成功时
	EVENT_LOG_QUEST_CLEAR			= 12,					/// 获取任务奖励时
	EVENT_LOG_SYSTEM_TAP			= 13,					/// 点击系统按钮时
	EVENT_LOG_TRIAL_BOUNS			= 14,					/// 购买鼓舞buff成功时
	EVENT_LOG_PAY_CARD				= 15,					/// 使用付费翻卡功能时
	EVENT_LOG_TRIAL_RESET			= 16,					/// 使用挑战关卡重置功能时
	EVENT_LOG_PAY_UPDATE_ITEM		= 17,					/// 使用立即升级装备功能成功
	EVENT_LOG_ADWALL_YUANBAO		= 18,					/// 积分墙渠道增加元宝
	EVENT_LOG_REWARD_HOME_GET		= 19,					/// 领奖屋获得奖励时
	EVENT_LOG_CLEAR_SCENE_CD		= 20,					/// 清除关卡CD时
	EVENT_LOG_BUY_MONTH_CARD        = 21,                   /// 购买月卡时
	EVENT_LOG_ADD_CHALLENGE         = 22,                   /// 增加竞技场挑战次数
	EVENT_LOG_END					= 22,
};

enum EventLogField
{
	EVENT_LOG_FIELD_STORAGEIDX		= 0,					/// 存档index
	EVENT_LOG_FIELD_ALIASNAME		= 1,					/// 昵称
	EVENT_LOG_FIELD_VIP				= 2,					/// vip等级
	EVENT_LOG_FIELD_YUANBAO			= 3,					/// 元宝数量
	EVENT_LOG_FIELD_HONOR			= 4,					/// 荣誉数量
	EVENT_LOG_FIELD_MONEY			= 5,					/// 金钱数量
	EVENT_LOG_FIELD_ENERGY			= 6,					/// 体力数量
	EVENT_LOG_FIELD_SIGNCOUNT		= 7,					/// 签到次数
	EVENT_LOG_FIELD_OFFICIAL		= 8,					/// 官阶等级
	EVENT_LOG_FIELD_BP_COUNT		= 9,					/// 出战队伍角色数
	EVENT_LOG_FIELD_ALL_PLAYER_DATA	= 10,					/// 是否发送全部角色数据
	EVENT_LOG_FIELD_BP_DATA			= 11,					/// 是否发送出战角色数据
	EVENT_LOG_FIELD_CHAR_LEVEL		= 12,					/// 发送角色数据时是否发送角色等级
	EVENT_LOG_FIELD_CHAR_STANCE		= 13,					/// 发送角色数据时是否发送角色当前天赋
	EVENT_LOG_FIELD_CHAR_EQUIP		= 14,					/// 发送角色数据时是否发送角色装备
	EVENT_LOG_FIELD_CHAR_CARD		= 15,					/// 发送角色数据时是否发送角色卡片数据
	EVENT_LOG_FIELD_BATTLE_REPLAY	= 16,					/// 是否发送录像数据
	EVENT_LOG_FIELD_BATTLE_APM		= 17,					/// 一场战斗中的所有点击的平均APM
	EVENT_LOG_FIELD_BATTLE_SPELL_APM= 18,					/// 一场战斗中的点击技能的APM
	EVENT_LOG_FIELD_CHAR_HIGH_LEVEL	= 19,					/// 出战队伍中最高等级
};

enum EventLogSystem
{
	EVENT_LOG_SYS_TAP_QUEST			= 1,					/// 点击了大地图的任务按钮
	EVENT_LOG_SYS_TAP_CHAR			= 2,					/// 点击了大地图的角色按钮
	EVENT_LOG_SYS_TAP_GROUP			= 3,					/// 点击了大地图的队伍按钮
	EVENT_LOG_SYS_TAP_SPELL			= 4,					/// 点击了大地图的技能按钮
	EVENT_LOG_SYS_TAP_CARD			= 5,					/// 点击了大地图的卡片按钮
	EVENT_LOG_SYS_TAP_FORGE			= 6,					/// 点击了大地图的锻造按钮
	EVENT_LOG_SYS_TAP_SHOP			= 7,					/// 点击了大地图的商店按钮
	EVENT_LOG_SYS_TAP_ITEM			= 8,					/// 点击了大地图的道具按钮
	EVENT_LOG_SYS_TAP_BAR			= 9,					/// 点击了大地图的酒吧按钮
	EVENT_LOG_SYS_TAP_WANTED		= 10,					/// 点击了大地图的通缉关卡按钮
	EVENT_LOG_SYS_TAP_ARENA			= 11,					/// 点击了大地图的竞技场按钮
	EVENT_LOG_SYS_TAP_TRIAL			= 12,					/// 点击了大地图的挑战关卡按钮
	EVENT_LOG_SYS_TAP_DIAMOND		= 13,					/// 点击了大地图的钻石购买按钮
	EVENT_LOG_SYS_TAP_GLOD			= 14,					/// 点击了大地图的金币购买按钮
	EVENT_LOG_SYS_TAP_ENERGY		= 15,					/// 点击了大地图的体力购买按钮
};

enum RewardHomeLogSubType
{
	RHST_SIGN_REWARD				= 1,					/// 每日签到奖励
	RHST_OFFICIAL_REWARD			= 2,					/// 官阶奖励
	RHST_LEVEL_REWARD				= 3,					/// 等级奖励
	RHST_ACTIVE_REWARD				= 4,					/// 活跃奖励
	RHST_BATTLEFIELD_REWARD			= 5,					/// 竞技场奖励
};

enum GameSettingMask
{
	GAME_SETTING_MUSIC			= 0,			// 游戏音乐设置
	GAME_SETTING_EFFECTS		= 1,			// 游戏音效设置
};

enum HireType
{
	HIRETYPE_NORMAL	= 0,				// 普通人物
	HIRETYPE_ELITE	= 1,				// 精英级人物
	HIRETYPE_MASTER	= 2,				// 大师级人物
	HIRETYPE_MAX,
};

enum HireCostType
{
	HIRECOST_COIN		= 0,
	HIRECOST_YUNBAO		= 1,
	HIRECOST_HONOR		= 2,
	// 道具待扩展
};

enum UpgradeCostType
{
	UPGRADECOST_COIN	= 0,
	UPGRADECOST_YUNBAO  = 1,
	UPGRADECOST_HONOR	= 2,
	UPGRADECOST_ITEM	= 3,
	UPGRADECOST_MAX,
};

#define CHALLENGE_BUFF_SPELL_ID 46603

#define MonthCardRewardKeyType 17

#define MD5_HASH_PASSWD "renxiaobin"

// 12341	v1.0.0	20130425
// 12342	v1.0.1	20130510
// 12343	v1.0.2	20130513
// 12344	v1.1.0	20130528
// 12345	v1.1.2 ios.cn 20130702
// 12346	v1.1.3 ios.cn 20130715
// 12347	v1.1.4 ios.cn 20130726
// 12348	v1.2.0 ios.en 20130802 v1.2.0 ios.cn 20130802
// 12349	20130816 v1.2.1 ios.en v1.2.1 ios.cn
// 12350	20130827 v1.2.2 ios.en v1.2.2 ios.cn v1.2.2 tw
// 12351	20130905 v1.2.3 ios.en v1.2.3 ios.cn v1.2.3 tw
// 12352	20130909 v1.2.4 ios.en v1.2.4 ios.cn v1.2.4 tw
// 22352	20130916 v1.2.4 ios.en v1.2.4 ios.cn v1.2.4 tw (mini wow)
// 12353	20130919 v1.2.5 ios.en v1.2.5 ios.cn v1.2.5 tw
// 22353	20130919 v1.2.5 ios.en v1.2.5 ios.cn v1.2.5 tw (mini wow)
// 32353	20130919 v1.2.5 ios.jp v1.2.5 ios.pro
// 12354	20130926 v1.2.6 ios.en v1.2.6 ios.cn v1.2.6 tw
// 22354	20130926 v1.2.6 ios.en v1.2.6 ios.cn v1.2.6 tw (mini wow)
// 32354	20130926 v1.2.6 ios.jp v1.2.6 ios.pro
// 12355	20130926 v1.2.7 ios.en v1.2.7 ios.cn v1.2.7 tw
// 22355	20130926 v1.2.7 ios.en v1.2.7 ios.cn v1.2.7 tw (mini wow)
// 32355	20130926 v1.2.7 ios.jp v1.2.7 ios.pro
// 12356	20131008 v1.2.8 ios.en v1.2.8 ios.cn v1.2.8 tw
// 22356	20131008 v1.2.8 ios.en v1.2.8 ios.cn v1.2.8 tw (mini wow)
// 32356	20131008 v1.2.8 ios.jp v1.2.8 ios.pro
// 加入POCKETHERO_DEBUG宏是为了方便在外网真机上测试兑奖码,论坛,免费钻石等不在审核版本出现的内容
//石路要求测试版和正式版都统一用同一个版本号
/*#ifdef POCKETHERO_DEBUG

	#if VERSION_WOW
		#define POCKETHERO_CLIENT_VERSION 22354
	#elif VERSION_JP || VERSION_EN_PRO
		#define POCKETHERO_CLIENT_VERSION 32354
	#else
		#define POCKETHERO_CLIENT_VERSION 12354
	#endif
	
#else*/

	#if VERSION_WOW
		#define POCKETHERO_CLIENT_VERSION 22356
	#elif VERSION_JP || VERSION_EN_PRO
		#define POCKETHERO_CLIENT_VERSION 32356
	#else
		#define POCKETHERO_CLIENT_VERSION 12356
	#endif
/*
#endif*/


#endif
