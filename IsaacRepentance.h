#pragma once

#include "libzhl.h"
#include <map>
#include <vector>

struct ANM2;
struct AchievementOverlay;
struct AchievementOverlay_Entry;
struct ActiveItemDesc;
struct AfterImageFrame;
struct Ambush;
struct AnimationData;
struct AnimationFrame;
struct AnimationLayer;
struct AnimationState;
struct Backdrop;
struct BackdropConfig;
struct BackwardsStageDesc;
struct BagOfCraftingOutput;
struct BeamRenderer;
struct BitSet128;
struct BlendMode;
struct BossPool;
struct BossPool_Entry;
struct BossPool_Pool;
struct Camera;
struct Capsule;
struct ChallengeParam;
struct Checksum;
struct ColorMod;
struct ColorModState;
struct ColorParams;
struct CompletionWidget;
struct Console;
struct Console_HistoryEntry;
struct ConsumableData;
struct CostumeSpriteDesc;
struct Cutscene;
struct CutsceneEntry;
struct DailyChallenge;
struct DebugRenderer;
struct DestinationQuad;
struct Devolve;
struct Entity;
struct EntityConfig;
struct EntityConfig_Baby;
struct EntityConfig_Boss;
struct EntityConfig_Boss_Alt;
struct EntityConfig_Entity;
struct EntityConfig_EntityEntry;
struct EntityConfig_Player;
struct EntityDesc;
struct EntityFactory;
struct EntityList;
struct EntityList_EL;
struct EntityPtr;
struct EntityRef;
struct EntitySaveState;
struct Entity_Bomb;
struct Entity_Effect;
struct Entity_Familiar;
struct Entity_Knife;
struct Entity_Laser;
struct Entity_NPC;
struct Entity_Pickup;
struct Entity_Player;
struct Entity_Projectile;
struct Entity_Slot;
struct Entity_Tear;
struct FXLayers;
struct FXParams;
struct FamiliarData;
struct Font;
struct FontSettings;
struct Game;
struct GameOver;
struct GameState;
struct GameStateBossPool;
struct GameStateIO;
struct GameStateItemPool;
struct GameStatePlayer;
struct GameStateRoomConfig;
struct GenericPopup;
struct GenericPrompt;
struct GlobalPost;
struct GlowingHourglassState;
struct GridEntity;
struct GridEntityDesc;
struct GridEntity_Decoration;
struct GridEntity_Door;
struct GridEntity_Fire;
struct GridEntity_Gravity;
struct GridEntity_Lock;
struct GridEntity_Pit;
struct GridEntity_Poop;
struct GridEntity_PressurePlate;
struct GridEntity_Rock;
struct GridEntity_Spikes;
struct GridEntity_Stairs;
struct GridEntity_Statue;
struct GridEntity_TNT;
struct GridEntity_Teleporter;
struct GridEntity_TrapDoor;
struct GridEntity_Wall;
struct GridEntity_Web;
struct HUD;
struct HUD_Message;
struct History;
struct HistoryHUD;
struct HistoryHUD_Item;
struct HistoryHUD_Player;
struct History_HistoryItem;
struct HomingLaser;
struct HomingLaser_Bezier;
struct InputDeviceBase;
struct InputManager;
struct Isaac;
struct ItemConfig;
struct ItemConfig_Card;
struct ItemConfig_Costume;
struct ItemConfig_Item;
struct ItemConfig_Pill;
struct ItemConfig_PlayerForm;
struct ItemOverlay;
struct ItemPool;
struct ItemPool_Item;
struct KAGE;
struct KAGE_Filesys_ArchivedFile;
struct KAGE_Filesys_ArchivedFile_ArchiveEntry;
struct KAGE_Filesys_ArchivedFile_FileEntry;
struct KAGE_Filesys_ContentManager;
struct KAGE_Filesys_File;
struct KAGE_Filesys_FileManager;
struct KAGE_Filesys_FileStream;
struct KAGE_Filesys_IFile;
struct KAGE_Filesys_SaveManager;
struct KAGE_Graphics_GraphicsBuffer;
struct KAGE_Graphics_GraphicsBufferObject;
struct KAGE_Graphics_ImageBase;
struct KAGE_Graphics_ImageBase_VertexAttributeDescriptor;
struct KAGE_Graphics_ImageManager;
struct KAGE_Graphics_ImagePCX;
struct KAGE_Graphics_ImagePIC;
struct KAGE_Graphics_ImagePNG;
struct KAGE_Graphics_Manager;
struct KAGE_Graphics_Manager_GL;
struct KAGE_Graphics_RenderBatch;
struct KAGE_Graphics_Shader;
struct KAGE_Graphics_ShaderBase;
struct KAGE_Graphics_VertexAttributeDescriptor;
struct KAGE_ReferenceCountBase;
struct KAGE_ReferenceCount_EntitySaveState;
struct KAGE_ReferenceCount_ImageBase;
struct KAGE_SmartPointer_EntitySaveState;
struct KAGE_SmartPointer_ImageBase;
struct KAGE_System_CriticalSection;
struct KAGE_System_Mutex;
struct KColor;
struct LRoomAreaDesc;
struct LRoomTileDesc;
struct LayerData;
struct LayerState;
struct Leaderboard;
struct LeaderboardEntry;
struct LeaderboardEntryData;
struct Level;
struct LevelGenerator;
struct LevelGenerator_Room;
struct LootListEntry;
struct LuaBridgeRef;
struct LuaCallbackCaller;
struct LuaCallbackCallerResult;
struct LuaEngine;
struct MTRNG;
struct Manager;
struct MenuManager;
struct Menu_Bestiary;
struct Menu_Challenge;
struct Menu_Character;
struct Menu_Character_Entry;
struct Menu_Collection;
struct Menu_ControllerSelect;
struct Menu_CustomChallenge;
struct Menu_Cutscenes;
struct Menu_DailyChallenge;
struct Menu_Game;
struct Menu_KeyConfig;
struct Menu_Mods;
struct Menu_Online;
struct Menu_OnlineLobby;
struct Menu_OnlineOptions;
struct Menu_Options;
struct Menu_Save;
struct Menu_SpecialSeeds;
struct Menu_Stats;
struct Menu_Title;
struct Minimap;
struct MinimapConfig;
struct ModEntry;
struct ModManager;
struct ModManager_CharacterMap;
struct ModReference;
struct ModShader;
struct Music;
struct MusicEntry;
struct NPCAI_Pathfinder;
struct NetplayManager;
struct NightmareScene;
struct NullFrame;
struct OptionsConfig;
struct PauseScreen;
struct PersistentGameData;
struct PersistentGameData_Bestiary;
struct PlayerCostumeMap;
struct PlayerHUD;
struct PlayerHUDActiveItem;
struct PlayerHUDHeart;
struct PlayerHUDTrinket;
struct PlayerManager;
struct PocketItem;
struct Point;
struct PosVel;
struct ProceduralEffect;
struct ProceduralEffect_ActionData_AddTemproryEffect;
struct ProceduralEffect_ActionData_AreaDamage;
struct ProceduralEffect_ActionData_ConvertEntities;
struct ProceduralEffect_ActionData_Fart;
struct ProceduralEffect_ActionData_SpawnEntity;
struct ProceduralEffect_ActionData_UseActiveItem;
struct ProceduralEffect_ConditionData_EntitySpawn;
struct ProceduralItem;
struct ProceduralItemManager;
struct ProjectileParams;
struct QueueItemData;
struct RNG;
struct RailManager;
struct RedirectedPath;
struct Rendering;
struct Room;
struct RoomConfig;
struct RoomConfig_Curse;
struct RoomConfig_Miniboss;
struct RoomConfig_Room;
struct RoomConfig_Stage;
struct RoomConfig_VariantSet;
struct RoomDescriptor;
struct RoomEntry;
struct RoomSet;
struct RoomSpawn;
struct RoomTransition;
struct RunCallbackRegistry;
struct SFXManager;
struct ScoreSheet;
struct Seeds;
struct Shape;
struct ShapeRenderer;
struct SoundEffect;
struct SoundEffects;
struct SourceQuad;
struct StageTransition;
struct StatHUD;
struct StaticArray;
struct SteamCloudFile;
struct StringTable;
struct TearParams;
struct TemporaryEffect;
struct TemporaryEffects;
struct TrinketPoolItem;
struct UnknownGameStartStruct;
struct Vector;
struct WaterClipInfo;
struct Weapon;
struct Weapon_Brimstone;
struct Weapon_MonstrosLung;
struct Weapon_MultiShotParams;
struct WeightedOutcomePicker;
struct WeightedOutcomePicker_Outcome;
struct XY;
struct _GLFWwindow;
struct xmldocument_rep;
struct xmlnode_rep;
	struct AnimationData_EventTrigger
	{
		uint32_t eventId; // max 32
		int animationFrame;
	};
struct RenderMatrix
{
    float a = 1.0f, b = 0.0f, tx = 0.0f;
    float c = 0.0f, d = 1.0f, ty = 0.0f;
};
#include <windows.h>
#include "rapidxml.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <functional>
#include <deque>
#include <cstdarg>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <cstdint>
#include <bitset>
#include <optional>
#include <rttidata.h>
#include <lua.hpp>
#undef LoadImage

using namespace rapidxml;

#ifndef M_PI
        #define M_PI 3.14159265358979323846
#endif

extern "C" {
    #include "lstate.h"
}

struct Console_HistoryEntry;
struct History_HistoryItem;
struct EntitySaveState;
struct LootListEntry;

struct EntityId {
    int type;
    int variant;
    int subtype;
};

struct IntPair {
    int pair[2];
};

// When adding typedefs, remember to define them in ExtraTypes!
typedef std::vector<MusicEntry> vector_MusicEntry;
typedef std::vector<SoundEffect> vector_SoundEffect;
typedef std::vector<RoomConfig_Curse> vector_Curse;
typedef std::deque<Point> deque_Point;
typedef std::vector<ColorParams> vector_ColorParams;
typedef std::deque<Console_HistoryEntry> deque_console_historyentry;
typedef std::set<int> std_set_int;
typedef std::vector<TemporaryEffect> vector_TemporaryEffect;
typedef std::vector<LevelGenerator_Room> vector_LevelGenRoom;
typedef std::string std_string;
typedef std::vector<std::string> vector_string;
typedef std::vector<ModEntry*> vector_ModEntryPointer;
typedef std::vector<ModManager_CharacterMap> vector_ModManager_CharacterMap;
typedef std::list<ModReference> std_list_ModReference;
typedef std::deque<std::string> deque_string;
typedef std::vector<int> std_vector_int;
typedef std::vector<Vector> std_vector_vector2;
typedef std::vector<History_HistoryItem> std_vector_history_historyitem;
typedef std::vector<HistoryHUD_Item> std_vector_HistoryHUDItem;
typedef std::vector<unsigned int> std_vector_uint;
typedef std::set<uint32_t> std_set_uint32t;
typedef std::vector<EntitySaveState> vector_EntitySaveState;
typedef std::vector<GridEntityDesc> vector_GridEntityDesc;
typedef std::map<int, int> std_map_int_int;
typedef std::map<std::string, int> std_map_string_int;
typedef std::map<int, ANM2> std_map_int_ANM2;
typedef std::vector<EntityId> vector_ErasedEntities;
typedef std::vector<Entity_Player*> vector_EntityPlayerPtr;
typedef std::vector<ItemConfig_Item*> vector_ItemPtr;
typedef std::vector<TrinketPoolItem> vector_TrinketPoolItem;
typedef std::vector<WeightedOutcomePicker_Outcome> vector_Outcome;
typedef std::vector<BossPool_Entry> vector_BossPoolEntry;
typedef std::vector<HomingLaser_Bezier> vector_HomingLaserBezier;
typedef std::vector<EntityConfig_Boss> vector_EntityConfig_Boss;
typedef std::vector<EntityConfig_Boss_Alt> vector_EntityConfig_Boss_Alt;
typedef std::vector<float> std_vector_float;
typedef std::map<uint32_t, RoomConfig_VariantSet*> std_map_uint_VariantSetPtr;
typedef std::map<uint32_t, EntityConfig_EntityEntry> std_map_uint_EntityConfigEntityEntry;
typedef std::vector<Devolve> vector_Devolve;
typedef std::bitset<8> DoorsBitSet;
typedef std::bitset<8> RoomConfigFlags;
typedef std::bitset<13> RoomShapeBitset;
typedef std::deque<AfterImageFrame> deque_afterImageFrames;
typedef std::deque<RoomConfig_Room> std_deque_RoomConfigRoom;
typedef std::vector<KAGE_Graphics_ImageBase*> vector_ImagePtr;
typedef std::vector<KAGE_Graphics_RenderBatch*> vector_RenderBatchPtr;
typedef std::vector<std::pair<KAGE_Graphics_RenderBatch*, KAGE_Graphics_ImageBase*>> vector_pair_RenderBatchPtr_ImagePtr;
typedef std::deque<ColorMod> deque_ColorMod;
typedef std::vector<FamiliarData> vector_FamiliarData;
typedef KColor KAGE_Graphics_Color;

struct PoolItem {
	uint32_t _itemID = 0;
	float _initialWeight = 1.0f;
	float _weight = 1.0f;
	float _decreaseBy = 0.5f;
	float _removeOn = 0.1f;
        bool _isUnlocked = false;
        bool _isSpecial = false;
	char _pad[2];
	
	//std_string _itemName;
};

typedef std::vector<PoolItem> vector_PoolItem;
// Something goofy seemed to be happening with std::vector<bool> in zhl
typedef std::vector<bool> vector_bool;

struct RoomConfig_Room;
typedef std::vector<RoomConfig_Room*> RoomConfigRoomPtrVector;

struct SmeltedTrinketDesc {
	short _trinketNum;
	short _goldenTrinketNum;
};
typedef std::vector<SmeltedTrinketDesc> vector_SmeltedTrinketDesc;
typedef std::vector<CostumeSpriteDesc> vector_CostumeSpriteDesc;
typedef std::deque<LootListEntry> LootList;

struct ShopRestockDesc {
	int _unk1;
	int _unk2;
};
typedef std::deque<ShopRestockDesc> deque_ShopRestockDesc;

struct FontCharBlock {
	uint32_t _id;
	uint16_t _x;
	uint16_t _y;
	uint16_t _width;
	uint16_t _height;
	int16_t _xoffset;
	int16_t _yoffset;
	int16_t _xAdvance;
	int8_t _page;
	int8_t _channel;
};

typedef std::map<char, int> std_map_CharBlocks;

struct FontKerningPair {
	uint32_t _first;
	uint32_t _second;
	int16_t _amount;
	int _unk;
};

typedef std::vector<FontKerningPair> vector_KerningPair;
//typedef std::list<ModShader*> list_ModShader;



enum eManagerState
{
    STATE_NULL = 0,
    STATE_MENU = 1,
    STATE_GAME = 2,
    STATE_CUTSCENE = 3,
    STATE_NIGHTMARE = 5
};

enum CharacterLockedFlag
{
		LOCKED = 65536,
		UNLOCKED = 65792,
};

enum eEntityType {
    ENTITY_NULL = 0,
    ENTITY_PLAYER = 1,
    ENTITY_TEAR = 2,
    ENTITY_FAMILIAR = 3,
    ENTITY_BOMB = 4,
    ENTITY_PICKUP = 5,
    ENTITY_SLOT = 6,
    ENTITY_LASER = 7,
    ENTITY_KNIFE = 8,
    ENTITY_PROJECTILE = 9,
    ENTITY_GAPER = 10,
    ENTITY_GUSHER = 11,
    ENTITY_HORF = 12,
    ENTITY_FLY = 13,
    ENTITY_POOTER = 14,
    ENTITY_CLOTTY = 15,
    ENTITY_MULLIGAN = 16,
    ENTITY_SHOPKEEPER = 17,
    ENTITY_ATTACKFLY = 18,
    ENTITY_LARRYJR = 19,
    ENTITY_MONSTRO = 20,
    ENTITY_MAGGOT = 21,
    ENTITY_HIVE = 22,
    ENTITY_CHARGER = 23,
    ENTITY_GLOBIN = 24,
    ENTITY_BOOMFLY = 25,
    ENTITY_MAW = 26,
    ENTITY_HOST = 27,
    ENTITY_CHUB = 28,
    ENTITY_HOPPER = 29,
    ENTITY_BOIL = 30,
    ENTITY_SPITTY = 31,
    ENTITY_BRAIN = 32,
    ENTITY_FIREPLACE = 33,
    ENTITY_LEAPER = 34,
    ENTITY_MRMAW = 35,
    ENTITY_GURDY = 36,
    ENTITY_BABY = 38,
    ENTITY_VIS = 39,
    ENTITY_GUTS = 40,
    ENTITY_KNIGHT = 41,
    ENTITY_STONEHEAD = 42,
    ENTITY_MONSTRO2 = 43,
    ENTITY_POKY = 44,
    ENTITY_MOM = 45,
    ENTITY_SLOTH = 46,
    ENTITY_LUST = 47,
    ENTITY_WRATH = 48,
    ENTITY_GLUTTONY = 49,
    ENTITY_GREED = 50,
    ENTITY_ENVY = 51,
    ENTITY_PRIDE = 52,
    ENTITY_DOPLE = 53,
    ENTITY_FLAMINGHOPPER = 54,
    ENTITY_LEECH = 55,
    ENTITY_LUMP = 56,
    ENTITY_MEMBRAIN = 57,
    ENTITY_PARA_BITE = 58,
    ENTITY_FRED = 59,
    ENTITY_EYE = 60,
    ENTITY_SUCKER = 61,
    ENTITY_PIN = 62,
    ENTITY_FAMINE = 63,
    ENTITY_PESTILENCE = 64,
    ENTITY_WAR = 65,
    ENTITY_DEATH = 66,
    ENTITY_DUKE = 67,
    ENTITY_PEEP = 68,
    ENTITY_LOKI = 69,
    ENTITY_FISTULA_BIG = 71,
    ENTITY_FISTULA_MEDIUM = 72,
    ENTITY_FISTULA_SMALL = 73,
    ENTITY_BLASTOCYST_BIG = 74,
    ENTITY_BLASTOCYST_MEDIUM = 75,
    ENTITY_BLASTOCYST_SMALL = 76,
    ENTITY_EMBRYO = 77,
    ENTITY_MOMS_HEART = 78,
    ENTITY_GEMINI = 79,
    ENTITY_MOTER = 80,
    ENTITY_FALLEN = 81,
    ENTITY_HEADLESS_HORSEMAN = 82,
    ENTITY_HORSEMAN_HEAD = 83,
    ENTITY_SATAN = 84,
    ENTITY_SPIDER = 85,
    ENTITY_KEEPER = 86,
    ENTITY_GURGLE = 87,
    ENTITY_WALKINGBOIL = 88,
    ENTITY_BUTTLICKER = 89,
    ENTITY_HANGER = 90,
    ENTITY_SWARMER = 91,
    ENTITY_HEART = 92,
    ENTITY_MASK = 93,
    ENTITY_BIGSPIDER = 94,
    ENTITY_ETERNALFLY = 96,
    ENTITY_MASK_OF_INFAMY = 97,
    ENTITY_HEART_OF_INFAMY = 98,
    ENTITY_GURDY_JR = 99,
    ENTITY_WIDOW = 100,
    ENTITY_DADDYLONGLEGS = 101,
    ENTITY_ISAAC = 102,
    ENTITY_STONE_EYE = 201,
    ENTITY_CONSTANT_STONE_SHOOTER = 202,
    ENTITY_BRIMSTONE_HEAD = 203,
    ENTITY_MOBILE_HOST = 204,
    ENTITY_NEST = 205,
    ENTITY_BABY_LONG_LEGS = 206,
    ENTITY_CRAZY_LONG_LEGS = 207,
    ENTITY_FATTY = 208,
    ENTITY_FAT_SACK = 209,
    ENTITY_BLUBBER = 210,
    ENTITY_HALF_SACK = 211,
    ENTITY_DEATHS_HEAD = 212,
    ENTITY_MOMS_HAND = 213,
    ENTITY_FLY_L2 = 214,
    ENTITY_SPIDER_L2 = 215,
    ENTITY_SWINGER = 216,
    ENTITY_DIP = 217,
    ENTITY_WALL_HUGGER = 218,
    ENTITY_WIZOOB = 219,
    ENTITY_SQUIRT = 220,
    ENTITY_COD_WORM = 221,
    ENTITY_RING_OF_FLIES = 222,
    ENTITY_DINGA = 223,
    ENTITY_OOB = 224,
    ENTITY_BLACK_MAW = 225,
    ENTITY_SKINNY = 226,
    ENTITY_BONY = 227,
    ENTITY_HOMUNCULUS = 228,
    ENTITY_TUMOR = 229,
    ENTITY_CAMILLO_JR = 230,
    ENTITY_NERVE_ENDING = 231,
    ENTITY_SKINBALL = 232,
    ENTITY_MOM_HEAD = 233,
    ENTITY_ONE_TOOTH = 234,
    ENTITY_GAPING_MAW = 235,
    ENTITY_BROKEN_GAPING_MAW = 236,
    ENTITY_GURGLING = 237,
    ENTITY_SPLASHER = 238,
    ENTITY_GRUB = 239,
    ENTITY_WALL_CREEP = 240,
    ENTITY_RAGE_CREEP = 241,
    ENTITY_BLIND_CREEP = 242,
    ENTITY_CONJOINED_SPITTY = 243,
    ENTITY_ROUND_WORM = 244,
    ENTITY_POOP = 245,
    ENTITY_RAGLING = 246,
    ENTITY_FLESH_MOBILE_HOST = 247,
    ENTITY_PSY_HORF = 248,
    ENTITY_FULL_FLY = 249,
    ENTITY_TICKING_SPIDER = 250,
    ENTITY_BEGOTTEN = 251,
    ENTITY_NULLS = 252,
    ENTITY_PSY_TUMOR = 253,
    ENTITY_FLOATING_KNIGHT = 254,
    ENTITY_NIGHT_CRAWLER = 255,
    ENTITY_DART_FLY = 256,
    ENTITY_CONJOINED_FATTY = 257,
    ENTITY_FAT_BAT = 258,
    ENTITY_IMP = 259,
    ENTITY_THE_HAUNT = 260,
    ENTITY_DINGLE = 261,
    ENTITY_MEGA_MAW = 262,
    ENTITY_GATE = 263,
    ENTITY_MEGA_FATTY = 264,
    ENTITY_CAGE = 265,
    ENTITY_MAMA_GURDY = 266,
    ENTITY_DARK_ONE = 267,
    ENTITY_ADVERSARY = 268,
    ENTITY_POLYCEPHALUS = 269,
    ENTITY_MR_FRED = 270,
    ENTITY_URIEL = 271,
    ENTITY_GABRIEL = 272,
    ENTITY_THE_LAMB = 273,
    ENTITY_MEGA_SATAN = 274,
    ENTITY_MEGA_SATAN_2 = 275,
    ENTITY_ROUNDY = 276,
    ENTITY_BLACK_BONY = 277,
    ENTITY_BLACK_GLOBIN = 278,
    ENTITY_BLACK_GLOBIN_HEAD = 279,
    ENTITY_BLACK_GLOBIN_BODY = 280,
    ENTITY_SWARM = 281,
    ENTITY_MEGA_CLOTTY = 282,
    ENTITY_BONE_KNIGHT = 283,
    ENTITY_CYCLOPIA = 284,
    ENTITY_RED_GHOST = 285,
    ENTITY_FLESH_DEATHS_HEAD = 286,
    ENTITY_MOMS_DEAD_HAND = 287,
    ENTITY_DUKIE = 288,
    ENTITY_ULCER = 289,
    ENTITY_MEATBALL = 290,
    ENTITY_PITFALL = 291,
    ENTITY_MOVABLE_TNT = 292,
    ENTITY_ULTRA_COIN = 293,
    ENTITY_ULTRA_DOOR = 294,
    ENTITY_CORN_MINE = 295,
    ENTITY_HUSH_FLY = 296,
    ENTITY_HUSH_GAPER = 297,
    ENTITY_HUSH_BOIL = 298,
    ENTITY_GREED_GAPER = 299,
    ENTITY_MUSHROOM = 300,
    ENTITY_POISON_MIND = 301,
    ENTITY_STONEY = 302,
    ENTITY_BLISTER = 303,
    ENTITY_THE_THING = 304,
    ENTITY_MINISTRO = 305,
    ENTITY_PORTAL = 306,
    ENTITY_TARBOY = 307,
    ENTITY_FISTULOID = 308,
    ENTITY_GUSH = 309,
    ENTITY_LEPER = 310,
    ENTITY_MR_MINE = 311,
    ENTITY_STAIN = 401,
    ENTITY_BROWNIE = 402,
    ENTITY_FORSAKEN = 403,
    ENTITY_LITTLE_HORN = 404,
    ENTITY_RAG_MAN = 405,
    ENTITY_ULTRA_GREED = 406,
    ENTITY_HUSH = 407,
    ENTITY_HUSH_SKINLESS = 408,
    ENTITY_RAG_MEGA = 409,
    ENTITY_SISTERS_VIS = 410,
    ENTITY_BIG_HORN = 411,
    ENTITY_DELIRIUM = 412,
    ENTITY_MATRIARCH = 413,
    ENTITY_BONE_WORM = 801,
    ENTITY_BLOOD_PUPPY = 802,
    ENTITY_QUAKE_GRIMACE = 804,
    ENTITY_BISHOP = 805,
    ENTITY_BUBBLES = 806,
    ENTITY_WRAITH = 807,
    ENTITY_WILLO = 808,
    ENTITY_BOMB_GRIMACE = 809,
    ENTITY_SMALL_LEECH = 810,
    ENTITY_DEEP_GAPER = 811,
    ENTITY_SUB_HORF = 812,
    ENTITY_BLURB = 813,
    ENTITY_STRIDER = 814,
    ENTITY_FISSURE = 815,
    ENTITY_POLTY = 816,
    ENTITY_PREY = 817,
    ENTITY_ROCK_SPIDER = 818,
    ENTITY_FLY_BOMB = 819,
    ENTITY_DANNY = 820,
    ENTITY_BLASTER = 821,
    ENTITY_BOUNCER = 822,
    ENTITY_QUAKEY = 823,
    ENTITY_GYRO = 824,
    ENTITY_FIRE_WORM = 825,
    ENTITY_HARDY = 826,
    ENTITY_FACELESS = 827,
    ENTITY_NECRO = 828,
    ENTITY_MOLE = 829,
    ENTITY_BIG_BONY = 830,
    ENTITY_GUTTED_FATTY = 831,
    ENTITY_EXORCIST = 832,
    ENTITY_CANDLER = 833,
    ENTITY_WHIPPER = 834,
    ENTITY_PEEPER_FATTY = 835,
    ENTITY_VIS_VERSA = 836,
    ENTITY_HENRY = 837,
    ENTITY_WILLO_L2 = 838,
    ENTITY_PON = 840,
    ENTITY_REVENANT = 841,
    ENTITY_BOMBGAGGER = 844,
    ENTITY_GAPER_L2 = 850,
    ENTITY_TWITCHY = 851,
    ENTITY_SPIKEBALL = 852,
    ENTITY_SMALL_MAGGOT = 853,
    ENTITY_ADULT_LEECH = 854,
    ENTITY_CHARGER_L2 = 855,
    ENTITY_GASBAG = 856,
    ENTITY_COHORT = 857,
    ENTITY_FLOATING_HOST = 859,
    ENTITY_UNBORN = 860,
    ENTITY_PUSTULE = 861,
    ENTITY_CYST = 862,
    ENTITY_MORNINGSTAR = 863,
    ENTITY_MOCKULUS = 864,
    ENTITY_EVIS = 865,
    ENTITY_DARK_ESAU = 866,
    ENTITY_MOTHERS_SHADOW = 867,
    ENTITY_ARMYFLY = 868,
    ENTITY_MIGRAINE = 869,
    ENTITY_DRIP = 870,
    ENTITY_SPLURT = 871,
    ENTITY_CLOGGY = 872,
    ENTITY_FLY_TRAP = 873,
    ENTITY_FARTIGAN = 874,
    ENTITY_POOT_MINE = 875,
    ENTITY_DUMP = 876,
    ENTITY_GRUDGE = 877,
    ENTITY_BUTT_SLICKER = 878,
    ENTITY_BLOATY = 879,
    ENTITY_FLESH_MAIDEN = 880,
    ENTITY_NEEDLE = 881,
    ENTITY_DUST = 882,
    ENTITY_BABY_BEGOTTEN = 883,
    ENTITY_SWARM_SPIDER = 884,
    ENTITY_CULTIST = 885,
    ENTITY_VIS_FATTY = 886,
    ENTITY_DUSTY_DEATHS_HEAD = 887,
    ENTITY_SHADY = 888,
    ENTITY_CLICKETY_CLACK = 889,
    ENTITY_MAZE_ROAMER = 890,
    ENTITY_GOAT = 891,
    ENTITY_POOFER = 892,
    ENTITY_BALL_AND_CHAIN = 893,
    ENTITY_REAP_CREEP = 900,
    ENTITY_LIL_BLUB = 901,
    ENTITY_RAINMAKER = 902,
    ENTITY_VISAGE = 903,
    ENTITY_SIREN = 904,
    ENTITY_HERETIC = 905,
    ENTITY_HORNFEL = 906,
    ENTITY_GIDEON = 907,
    ENTITY_BABY_PLUM = 908,
    ENTITY_SCOURGE = 909,
    ENTITY_CHIMERA = 910,
    ENTITY_ROTGUT = 911,
    ENTITY_MOTHER = 912,
    ENTITY_MIN_MIN = 913,
    ENTITY_CLOG = 914,
    ENTITY_SINGE = 915,
    ENTITY_BUMBINO = 916,
    ENTITY_COLOSTOMIA = 917,
    ENTITY_TURDLET = 918,
    ENTITY_RAGLICH = 919,
    ENTITY_HORNY_BOYS = 920,
    ENTITY_CLUTCH = 921,
    ENTITY_CADAVRA = 922,
    ENTITY_DOGMA = 950,
    ENTITY_BEAST = 951,
    ENTITY_GENERIC_PROP = 960,
    ENTITY_FROZEN_ENEMY = 963,
    ENTITY_DUMMY = 964,
    ENTITY_MINECART = 965,
    ENTITY_SIREN_HELPER = 966,
    ENTITY_HORNFEL_DOOR = 967,
    ENTITY_TRIGGER_OUTPUT = 969,
    ENTITY_ENVIRONMENT = 970,
    ENTITY_EFFECT = 1000,
    ENTITY_TEXT = 9001
};

enum eRoomSpawnType {
    SPAWN_DECORATION = 0,
    SPAWN_EFFECT = 999,
    SPAWN_ROCK = 1000,
    SPAWN_BOMB_ROCK = 1001,
    SPAWN_ALT_ROCK = 1002,
    SPAWN_TINTED_ROCK = 1003,
    SPAWN_MARKED_SKULL = 1008,
    SPAWN_EVENT_ROCK = 1009,
    SPAWN_SPIKE_ROCK = 1010,
    SPAWN_FOOLS_GOLD_ROCK = 1011,
    SPAWN_TNT = 1300,
    SPAWN_RED_POOP = 1490,
    SPAWN_RAINBOW_POOP = 1494,
    SPAWN_CORN_POOP = 1495,
    SPAWN_GOLDEN_POOP = 1496,
    SPAWN_BLACK_POOP = 1497,
    SPAWN_HOLY_POOP = 1498,
    SPAWN_GIANT_POOP = 1499,
    SPAWN_POOP = 1500,
    SPAWN_CHARMED_POOP = 1501,
    SPAWN_BLOCK = 1900,
    SPAWN_PILLAR = 1901,
    SPAWN_SPIKES = 1930,
    SPAWN_RETRACTING_SPIKES = 1931,
    SPAWN_COBWEB = 1940,
    SPAWN_INVISIBLE_BLOCK = 1999,
    SPAWN_PIT = 3000,
    SPAWN_EVENT_RAIL = 3002,
    SPAWN_EVENT_PIT = 3009,
    SPAWN_KEY_BLOCK = 4000,
    SPAWN_PRESSURE_PLATE = 4500,
    SPAWN_DEVIL_STATUE = 5000,
    SPAWN_ANGEL_STATUE = 5001,
    SPAWN_RAIL = 6000,
    SPAWN_RAIL_PIT = 6001,
    SPAWN_TELEPORTER = 6100,
    SPAWN_TRAP_DOOR = 9000,
    SPAWN_CRAWLSPACE = 9100,
    SPAWN_GRAVITY = 10000,
};

enum ePlayerType {
    PLAYER_POSSESSOR = -1,
    PLAYER_ISAAC = 0,
    PLAYER_MAGDALENE = 1,
    PLAYER_CAIN = 2,
    PLAYER_JUDAS = 3,
    PLAYER_BLUEBABY = 4,
    PLAYER_EVE = 5,
    PLAYER_SAMSON = 6,
    PLAYER_AZAZEL = 7,
    PLAYER_LAZARUS = 8,
    PLAYER_EDEN = 9,
    PLAYER_THELOST = 10,
    PLAYER_LAZARUS2 = 11,
    PLAYER_BLACKJUDAS = 12,
    PLAYER_LILITH = 13,
    PLAYER_KEEPER = 14,
    PLAYER_APOLLYON = 15,
    PLAYER_THEFORGOTTEN = 16,
    PLAYER_THESOUL = 17,
    PLAYER_BETHANY = 18,
    PLAYER_JACOB = 19,
    PLAYER_ESAU = 20,
    PLAYER_ISAAC_B = 21,
    PLAYER_MAGDALENE_B = 22,
    PLAYER_CAIN_B = 23,
    PLAYER_JUDAS_B = 24,
    PLAYER_BLUEBABY_B = 25,
    PLAYER_EVE_B = 26,
    PLAYER_SAMSON_B = 27,
    PLAYER_AZAZEL_B = 28,
    PLAYER_LAZARUS_B = 29,
    PLAYER_EDEN_B = 30,
    PLAYER_THELOST_B = 31,
    PLAYER_LILITH_B = 32,
    PLAYER_KEEPER_B = 33,
    PLAYER_APOLLYON_B = 34,
    PLAYER_THEFORGOTTEN_B = 35,
    PLAYER_BETHANY_B = 36,
    PLAYER_JACOB_B = 37,
    PLAYER_LAZARUS2_B = 38,
    PLAYER_JACOB2_B = 39,
    PLAYER_THESOUL_B = 40,
    NUM_PLAYER_TYPES = 41
};

enum WeaponType
{
        WEAPON_NULL = 0x0,
        WEAPON_TEARS = 0x1,
        WEAPON_BRIMSTONE = 0x2,
        WEAPON_LASER = 0x3,
        WEAPON_KNIFE = 0x4,
        WEAPON_BOMBS = 0x5,
        WEAPON_ROCKETS = 0x6,
        WEAPON_MONSTROS_LUNGS = 0x7,
        WEAPON_LUDOVICO_TECHNIQUE = 0x8,
        WEAPON_TECH_X = 0x9,
        WEAPON_BONE = 0xA,
        WEAPON_NOTCHED_AXE = 0xB,
        WEAPON_URN_OF_SOULS = 0xC,
        WEAPON_SPIRIT_SWORD = 0xD,
        WEAPON_FETUS = 0xE,
        WEAPON_UMBILICAL_WHIP = 0xF,
        NUM_WEAPON_TYPES = 0x10,
};

enum GridEntityType {
        GRID_NULL = 0x0,
        GRID_DECORATION = 0x1,
        GRID_ROCK = 0x2,
        GRID_ROCKB = 0x3,	
        GRID_ROCKT = 0x4,	
        GRID_ROCK_BOMB = 0x5,	
        GRID_ROCK_ALT = 0x6,	
        GRID_PIT = 0x7,
        GRID_SPIKES = 0x8,
        GRID_SPIKES_ONOFF = 0x9,
        GRID_SPIDERWEB = 0xA,
        GRID_LOCK = 0xB,
        GRID_TNT = 0xC,
        GRID_FIREPLACE = 0xD,
        GRID_POOP = 0xE,
        GRID_WALL = 0xF,
        GRID_DOOR = 0x10,
        GRID_TRAPDOOR = 0x11,
        GRID_STAIRS = 0x12,
        GRID_GRAVITY = 0x13,
        GRID_PRESSURE_PLATE = 0x14,
        GRID_STATUE = 0x15,
        GRID_ROCK_SS = 0x16,
        GRID_TELEPORTER = 0x17,
        GRID_PILLAR = 0x18,
        GRID_ROCK_SPIKED = 0x19,
        GRID_ROCK_ALT2 = 0x1A,
        GRID_ROCK_GOLD = 0x1B,
};

enum Direction
{
        NO_DIRECTION = 0xFFFFFFFF,
        LEFT = 0x0,
        UP = 0x1,
        RIGHT = 0x2,
        DOWN = 0x3,
};

enum eRoomShape 
{
    ROOMSHAPE_NULL = 0,
    ROOMSHAPE_1x1 = 1,
    ROOMSHAPE_IH = 2, // Horizontal, narrow
    ROOMSHAPE_IV = 3, // Vertical, narrow
    ROOMSHAPE_1x2 = 4, // Vertical, two high
    ROOMSHAPE_IIV = 5, // Vertical, two high, narrow
    ROOMSHAPE_2x1 = 6, // Horizontal, two wide
    ROOMSHAPE_IIH = 7, // Horizontal, two wide, narrow
    ROOMSHAPE_2x2 = 8,
    ROOMSHAPE_LTL = 9, 
    ROOMSHAPE_LTR = 10,
    ROOMSHAPE_LBL = 11,
    ROOMSHAPE_LBR = 12,
    MAX_ROOMSHAPES,
    NUM_ROOMSHAPES = MAX_ROOMSHAPES
};

enum eRoomType {
    ROOM_NULL = 0,
    ROOM_DEFAULT = 1,
    ROOM_SHOP = 2,
    ROOM_ERROR = 3,
    ROOM_TREASURE = 4,
    ROOM_BOSS = 5,
    ROOM_MINIBOSS = 6,
    ROOM_SECRET = 7,
    ROOM_SUPERSECRET = 8,
    ROOM_ARCADE = 9,
    ROOM_CURSE = 10,
    ROOM_CHALLENGE = 11,
    ROOM_LIBRARY = 12,
    ROOM_SACRIFICE = 13,
    ROOM_DEVIL = 14,
    ROOM_ANGEL = 15,
    ROOM_DUNGEON = 16,
    ROOM_BOSSRUSH = 17,
    ROOM_ISAACS = 18,
    ROOM_BARREN = 19,
    ROOM_CHEST = 20,
    ROOM_DICE = 21,
    ROOM_BLACK_MARKET = 22,
    ROOM_GREED_EXIT = 23,
    ROOM_PLANETARIUM = 24,
    ROOM_TELEPORTER = 25,
    ROOM_TELEPORTER_EXIT = 26,
    ROOM_SECRET_EXIT = 27,
    ROOM_BLUE = 28,
    ROOM_ULTRASECRET = 29,
    ROOM_DEATHMATCH = 30,
    NUM_ROOMTYPES = 31
};

enum eDoorSlots 
{
    NO_DOOR_SLOT = -1,
    DOOR_SLOT_LEFT0 = 0, // Left wall, top
    DOOR_SLOT_UP0, // Top wall, left
    DOOR_SLOT_RIGHT0, // Right wall, top
    DOOR_SLOT_DOWN0, // Down wall, left
    DOOR_SLOT_LEFT1, // Left wall, bottom
    DOOR_SLOT_UP1, // Top wall, right
    DOOR_SLOT_RIGHT1, // Right wall, bottom
    DOOR_SLOT_DOWN1, // Bottom wall, right
    MAX_DOOR_SLOTS,
    NUM_DOOR_SLOTS = MAX_DOOR_SLOTS
};

enum eRoomConfigFlag {
    FLAG_MINESHAFT_CHASE = 1,
    FLAG_DISABLE_CHAMPIONS = 2,
    FLAG_AFTERBIRTH_REPLACE_GRID = 3,
    FLAG_MERGED_ROOM = 4,
    FLAG_MIRRORED_ROOM = 5,

    FLAG_HAS_CLEAR_PLATE = 7,

    NUM_ROOM_CONFIG_FLAGS
};

enum GridCollisionClass
{
        COLLISION_NONE = 0,
        COLLISION_PIT,
        COLLISION_OBJECT,
        COLLISION_SOLID,
        COLLISION_WALL,
        COLLISION_WALL_EXCEPT_PLAYER
};

enum CollectibleType
{
        COLLECTIBLE_NULL = 0,
        COLLECTIBLE_SAD_ONION = 1,
        COLLECTIBLE_INNER_EYE = 2,
        COLLECTIBLE_SPOON_BENDER = 3,
        COLLECTIBLE_CRICKETS_HEAD = 4,
        COLLECTIBLE_MY_REFLECTION = 5,
        COLLECTIBLE_NUMBER_ONE = 6,
        COLLECTIBLE_BLOOD_OF_THE_MARTYR = 7,
        COLLECTIBLE_BROTHER_BOBBY = 8,
        COLLECTIBLE_SKATOLE = 9,
        COLLECTIBLE_HALO_OF_FLIES = 10,
        COLLECTIBLE_1UP = 11,
        COLLECTIBLE_MAGIC_MUSHROOM = 12,
        COLLECTIBLE_VIRUS = 13,
        COLLECTIBLE_ROID_RAGE = 14,
        COLLECTIBLE_HEART = 15,
        COLLECTIBLE_RAW_LIVER = 16,
        COLLECTIBLE_SKELETON_KEY = 17,
        COLLECTIBLE_DOLLAR = 18,
        COLLECTIBLE_BOOM = 19,
        COLLECTIBLE_TRANSCENDENCE = 20,
        COLLECTIBLE_COMPASS = 21,
        COLLECTIBLE_LUNCH = 22,
        COLLECTIBLE_DINNER = 23,
        COLLECTIBLE_DESSERT = 24,
        COLLECTIBLE_BREAKFAST = 25,
        COLLECTIBLE_ROTTEN_MEAT = 26,
        COLLECTIBLE_WOODEN_SPOON = 27,
        COLLECTIBLE_BELT = 28,
        COLLECTIBLE_MOMS_UNDERWEAR = 29,
        COLLECTIBLE_MOMS_HEELS = 30,
        COLLECTIBLE_MOMS_LIPSTICK = 31,
        COLLECTIBLE_WIRE_COAT_HANGER = 32,
        COLLECTIBLE_BIBLE = 33,
        COLLECTIBLE_BOOK_OF_BELIAL = 34,
        COLLECTIBLE_NECRONOMICON = 35,
        COLLECTIBLE_POOP = 36,
        COLLECTIBLE_MR_BOOM = 37,
        COLLECTIBLE_TAMMYS_HEAD = 38,
        COLLECTIBLE_MOMS_BRA = 39,
        COLLECTIBLE_KAMIKAZE = 40,
        COLLECTIBLE_MOMS_PAD = 41,
        COLLECTIBLE_BOBS_ROTTEN_HEAD = 42,
        // 43
        COLLECTIBLE_TELEPORT = 44,
        COLLECTIBLE_YUM_HEART = 45,
        COLLECTIBLE_LUCKY_FOOT = 46,
        COLLECTIBLE_DOCTORS_REMOTE = 47,
        COLLECTIBLE_CUPIDS_ARROW = 48,
        COLLECTIBLE_SHOOP_DA_WHOOP = 49,
        COLLECTIBLE_STEVEN = 50,
        COLLECTIBLE_PENTAGRAM = 51,
        COLLECTIBLE_DR_FETUS = 52,
        COLLECTIBLE_MAGNETO = 53,
        COLLECTIBLE_TREASURE_MAP = 54,
        COLLECTIBLE_MOMS_EYE = 55,
        COLLECTIBLE_LEMON_MISHAP = 56,
        COLLECTIBLE_DISTANT_ADMIRATION = 57,
        COLLECTIBLE_BOOK_OF_SHADOWS = 58,
        COLLECTIBLE_BOOK_OF_BELIAL_PASSIVE = 59,
        COLLECTIBLE_LADDER = 60,
        // 61
        COLLECTIBLE_CHARM_VAMPIRE = 62,
        COLLECTIBLE_BATTERY = 63,
        COLLECTIBLE_STEAM_SALE = 64,
        COLLECTIBLE_ANARCHIST_COOKBOOK = 65,
        COLLECTIBLE_HOURGLASS = 66,
        COLLECTIBLE_SISTER_MAGGY = 67,
        COLLECTIBLE_TECHNOLOGY = 68,
        COLLECTIBLE_CHOCOLATE_MILK = 69,
        COLLECTIBLE_GROWTH_HORMONES = 70,
        COLLECTIBLE_MINI_MUSH = 71,
        COLLECTIBLE_ROSARY = 72,
        COLLECTIBLE_CUBE_OF_MEAT = 73,
        COLLECTIBLE_QUARTER = 74,
        COLLECTIBLE_PHD = 75,
        COLLECTIBLE_XRAY_VISION = 76,
        COLLECTIBLE_MY_LITTLE_UNICORN = 77,
        COLLECTIBLE_BOOK_OF_REVELATIONS = 78,
        COLLECTIBLE_MARK = 79,
        COLLECTIBLE_PACT = 80,
        COLLECTIBLE_DEAD_CAT = 81,
        COLLECTIBLE_LORD_OF_THE_PIT = 82,
        COLLECTIBLE_THE_NAIL = 83,
        COLLECTIBLE_WE_NEED_TO_GO_DEEPER = 84,
        COLLECTIBLE_DECK_OF_CARDS = 85,
        COLLECTIBLE_MONSTROS_TOOTH = 86,
        COLLECTIBLE_LOKIS_HORNS = 87,
        COLLECTIBLE_LITTLE_CHUBBY = 88,
        COLLECTIBLE_SPIDER_BITE = 89,
        COLLECTIBLE_SMALL_ROCK = 90,
        COLLECTIBLE_SPELUNKER_HAT = 91,
        COLLECTIBLE_SUPER_BANDAGE = 92,
        COLLECTIBLE_GAMEKID = 93,
        COLLECTIBLE_SACK_OF_PENNIES = 94,
        COLLECTIBLE_ROBO_BABY = 95,
        COLLECTIBLE_LITTLE_CHAD = 96,
        COLLECTIBLE_BOOK_OF_SIN = 97,
        COLLECTIBLE_RELIC = 98,
        COLLECTIBLE_LITTLE_GISH = 99,
        COLLECTIBLE_LITTLE_STEVEN = 100,
        COLLECTIBLE_HALO = 101,
        COLLECTIBLE_MOMS_BOTTLE_OF_PILLS = 102,
        COLLECTIBLE_COMMON_COLD = 103,
        COLLECTIBLE_PARASITE = 104,
        COLLECTIBLE_D6 = 105,
        COLLECTIBLE_MR_MEGA = 106,
        COLLECTIBLE_PINKING_SHEARS = 107,
        COLLECTIBLE_WAFER = 108,
        COLLECTIBLE_MONEY_EQUALS_POWER = 109,
        COLLECTIBLE_MOMS_CONTACTS = 110,
        COLLECTIBLE_BEAN = 111,
        COLLECTIBLE_GUARDIAN_ANGEL = 112,
        COLLECTIBLE_DEMON_BABY = 113,
        COLLECTIBLE_MOMS_KNIFE = 114,
        COLLECTIBLE_OUIJA_BOARD = 115,
        COLLECTIBLE_9_VOLT = 116,
        COLLECTIBLE_DEAD_BIRD = 117,
        COLLECTIBLE_BRIMSTONE = 118,
        COLLECTIBLE_BLOOD_BAG = 119,
        COLLECTIBLE_ODD_MUSHROOM_THIN = 120,
        COLLECTIBLE_ODD_MUSHROOM_LARGE = 121,
        COLLECTIBLE_WHORE_OF_BABYLON = 122,
        COLLECTIBLE_MONSTER_MANUAL = 123,
        COLLECTIBLE_DEAD_SEA_SCROLLS = 124,
        COLLECTIBLE_BOBBY_BOMB = 125,
        COLLECTIBLE_RAZOR_BLADE = 126,
        COLLECTIBLE_FORGET_ME_NOW = 127,
        COLLECTIBLE_FOREVER_ALONE = 128,
        COLLECTIBLE_BUCKET_OF_LARD = 129,
        COLLECTIBLE_PONY = 130,
        COLLECTIBLE_BOMB_BAG = 131,
        COLLECTIBLE_LUMP_OF_COAL = 132,
        COLLECTIBLE_GUPPYS_PAW = 133,
        COLLECTIBLE_GUPPYS_TAIL = 134,
        COLLECTIBLE_IV_BAG = 135,
        COLLECTIBLE_BEST_FRIEND = 136,
        COLLECTIBLE_REMOTE_DETONATOR = 137,
        COLLECTIBLE_STIGMATA = 138,
        COLLECTIBLE_MOMS_PURSE = 139,
        COLLECTIBLE_BOBS_CURSE = 140,
        COLLECTIBLE_PAGEANT_BOY = 141,
        COLLECTIBLE_SCAPULAR = 142,
        COLLECTIBLE_SPEED_BALL = 143,
        COLLECTIBLE_BUM_FRIEND = 144,
        COLLECTIBLE_GUPPYS_HEAD = 145,
        COLLECTIBLE_PRAYER_CARD = 146,
        COLLECTIBLE_NOTCHED_AXE = 147,
        COLLECTIBLE_INFESTATION = 148,
        COLLECTIBLE_IPECAC = 149,
        COLLECTIBLE_TOUGH_LOVE = 150,
        COLLECTIBLE_MULLIGAN = 151,
        COLLECTIBLE_TECHNOLOGY_2 = 152,
        COLLECTIBLE_MUTANT_SPIDER = 153,
        COLLECTIBLE_CHEMICAL_PEEL = 154,
        COLLECTIBLE_PEEPER = 155,
        COLLECTIBLE_HABIT = 156,
        COLLECTIBLE_BLOODY_LUST = 157,
        COLLECTIBLE_CRYSTAL_BALL = 158,
        COLLECTIBLE_SPIRIT_OF_THE_NIGHT = 159,
        COLLECTIBLE_CRACK_THE_SKY = 160,
        COLLECTIBLE_ANKH = 161,
        COLLECTIBLE_CELTIC_CROSS = 162,
        COLLECTIBLE_GHOST_BABY = 163,
        COLLECTIBLE_CANDLE = 164,
        COLLECTIBLE_CAT_O_NINE_TAILS = 165,
        COLLECTIBLE_D20 = 166,
        COLLECTIBLE_HARLEQUIN_BABY = 167,
        COLLECTIBLE_EPIC_FETUS = 168,
        COLLECTIBLE_POLYPHEMUS = 169,
        COLLECTIBLE_DADDY_LONGLEGS = 170,
        COLLECTIBLE_SPIDER_BUTT = 171,
        COLLECTIBLE_SACRIFICIAL_DAGGER = 172,
        COLLECTIBLE_MITRE = 173,
        COLLECTIBLE_RAINBOW_BABY = 174,
        COLLECTIBLE_DADS_KEY = 175,
        COLLECTIBLE_STEM_CELLS = 176,
        COLLECTIBLE_PORTABLE_SLOT = 177,
        COLLECTIBLE_HOLY_WATER = 178,
        COLLECTIBLE_FATE = 179,
        COLLECTIBLE_BLACK_BEAN = 180,
        COLLECTIBLE_WHITE_PONY = 181,
        COLLECTIBLE_SACRED_HEART = 182,
        COLLECTIBLE_TOOTH_PICKS = 183,
        COLLECTIBLE_HOLY_GRAIL = 184,
        COLLECTIBLE_DEAD_DOVE = 185,
        COLLECTIBLE_BLOOD_RIGHTS = 186,
        COLLECTIBLE_GUPPYS_HAIRBALL = 187,
        COLLECTIBLE_ABEL = 188,
        COLLECTIBLE_SMB_SUPER_FAN = 189,
        COLLECTIBLE_PYRO = 190,
        COLLECTIBLE_3_DOLLAR_BILL = 191,
        COLLECTIBLE_TELEPATHY_BOOK = 192,
        COLLECTIBLE_MEAT = 193,
        COLLECTIBLE_MAGIC_8_BALL = 194,
        COLLECTIBLE_MOMS_COIN_PURSE = 195,
        COLLECTIBLE_SQUEEZY = 196,
        COLLECTIBLE_JESUS_JUICE = 197,
        COLLECTIBLE_BOX = 198,
        COLLECTIBLE_MOMS_KEY = 199,
        COLLECTIBLE_MOMS_EYESHADOW = 200,
        COLLECTIBLE_IRON_BAR = 201,
        COLLECTIBLE_MIDAS_TOUCH = 202,
        COLLECTIBLE_HUMBLEING_BUNDLE = 203,
        COLLECTIBLE_FANNY_PACK = 204,
        COLLECTIBLE_SHARP_PLUG = 205,
        COLLECTIBLE_GUILLOTINE = 206,
        COLLECTIBLE_BALL_OF_BANDAGES = 207,
        COLLECTIBLE_CHAMPION_BELT = 208,
        COLLECTIBLE_BUTT_BOMBS = 209,
        COLLECTIBLE_GNAWED_LEAF = 210,
        COLLECTIBLE_SPIDERBABY = 211,
        COLLECTIBLE_GUPPYS_COLLAR = 212,
        COLLECTIBLE_LOST_CONTACT = 213,
        COLLECTIBLE_ANEMIC = 214,
        COLLECTIBLE_GOAT_HEAD = 215,
        COLLECTIBLE_CEREMONIAL_ROBES = 216,
        COLLECTIBLE_MOMS_WIG = 217,
        COLLECTIBLE_PLACENTA = 218,
        COLLECTIBLE_OLD_BANDAGE = 219,
        COLLECTIBLE_SAD_BOMBS = 220,
        COLLECTIBLE_RUBBER_CEMENT = 221,
        COLLECTIBLE_ANTI_GRAVITY = 222,
        COLLECTIBLE_PYROMANIAC = 223,
        COLLECTIBLE_CRICKETS_BODY = 224,
        COLLECTIBLE_GIMPY = 225,
        COLLECTIBLE_BLACK_LOTUS = 226,
        COLLECTIBLE_PIGGY_BANK = 227,
        COLLECTIBLE_MOMS_PERFUME = 228,
        COLLECTIBLE_MONSTROS_LUNG = 229,
        COLLECTIBLE_ABADDON = 230,
        COLLECTIBLE_BALL_OF_TAR = 231,
        COLLECTIBLE_STOP_WATCH = 232,
        COLLECTIBLE_TINY_PLANET = 233,
        COLLECTIBLE_INFESTATION_2 = 234,
        // 235
        COLLECTIBLE_E_COLI = 236,
        COLLECTIBLE_DEATHS_TOUCH = 237,
        COLLECTIBLE_KEY_PIECE_1 = 238,
        COLLECTIBLE_KEY_PIECE_2 = 239,
        COLLECTIBLE_EXPERIMENTAL_TREATMENT = 240,
        COLLECTIBLE_CONTRACT_FROM_BELOW = 241,
        COLLECTIBLE_INFAMY = 242,
        COLLECTIBLE_TRINITY_SHIELD = 243,
        COLLECTIBLE_TECH_5 = 244,
        COLLECTIBLE_20_20 = 245,
        COLLECTIBLE_BLUE_MAP = 246,
        COLLECTIBLE_BFFS = 247,
        COLLECTIBLE_HIVE_MIND = 248,
        COLLECTIBLE_THERES_OPTIONS = 249,
        COLLECTIBLE_BOGO_BOMBS = 250,
        COLLECTIBLE_STARTER_DECK = 251,
        COLLECTIBLE_LITTLE_BAGGY = 252,
        COLLECTIBLE_MAGIC_SCAB = 253,
        COLLECTIBLE_BLOOD_CLOT = 254,
        COLLECTIBLE_SCREW = 255,
        COLLECTIBLE_HOT_BOMBS = 256,
        COLLECTIBLE_FIRE_MIND = 257,
        COLLECTIBLE_MISSING_NO = 258,
        COLLECTIBLE_DARK_MATTER = 259,
        COLLECTIBLE_BLACK_CANDLE = 260,
        COLLECTIBLE_PROPTOSIS = 261,
        COLLECTIBLE_MISSING_PAGE_2 = 262,
        COLLECTIBLE_CLEAR_RUNE = 263,
        COLLECTIBLE_SMART_FLY = 264,
        COLLECTIBLE_DRY_BABY = 265,
        COLLECTIBLE_JUICY_SACK = 266,
        COLLECTIBLE_ROBO_BABY_2 = 267,
        COLLECTIBLE_ROTTEN_BABY = 268,
        COLLECTIBLE_HEADLESS_BABY = 269,
        COLLECTIBLE_LEECH = 270,
        COLLECTIBLE_MYSTERY_SACK = 271,
        COLLECTIBLE_BBF = 272,
        COLLECTIBLE_BOBS_BRAIN = 273,
        COLLECTIBLE_BEST_BUD = 274,
        COLLECTIBLE_LIL_BRIMSTONE = 275,
        COLLECTIBLE_ISAACS_HEART = 276,
        COLLECTIBLE_LIL_HAUNT = 277,
        COLLECTIBLE_DARK_BUM = 278,
        COLLECTIBLE_BIG_FAN = 279,
        COLLECTIBLE_SISSY_LONGLEGS = 280,
        COLLECTIBLE_PUNCHING_BAG = 281,
        COLLECTIBLE_HOW_TO_JUMP = 282,
        COLLECTIBLE_D100 = 283,
        COLLECTIBLE_D4 = 284,
        COLLECTIBLE_D10 = 285,
        COLLECTIBLE_BLANK_CARD = 286,
        COLLECTIBLE_BOOK_OF_SECRETS = 287,
        COLLECTIBLE_BOX_OF_SPIDERS = 288,
        COLLECTIBLE_RED_CANDLE = 289,
        COLLECTIBLE_THE_JAR = 290,
        COLLECTIBLE_FLUSH = 291,
        COLLECTIBLE_SATANIC_BIBLE = 292,
        COLLECTIBLE_HEAD_OF_KRAMPUS = 293,
        COLLECTIBLE_BUTTER_BEAN = 294,
        COLLECTIBLE_MAGIC_FINGERS = 295,
        COLLECTIBLE_CONVERTER = 296,
        COLLECTIBLE_BLUE_BOX = 297,
        COLLECTIBLE_UNICORN_STUMP = 298,
        COLLECTIBLE_TAURUS = 299,
        COLLECTIBLE_ARIES = 300,
        COLLECTIBLE_CANCER = 301,
        COLLECTIBLE_LEO = 302,
        COLLECTIBLE_VIRGO = 303,
        COLLECTIBLE_LIBRA = 304,
        COLLECTIBLE_SCORPIO = 305,
        COLLECTIBLE_SAGITTARIUS = 306,
        COLLECTIBLE_CAPRICORN = 307,
        COLLECTIBLE_AQUARIUS = 308,
        COLLECTIBLE_PISCES = 309,
        COLLECTIBLE_EVES_MASCARA = 310,
        COLLECTIBLE_JUDAS_SHADOW = 311,
        COLLECTIBLE_MAGGYS_BOW = 312,
        COLLECTIBLE_HOLY_MANTLE = 313,
        COLLECTIBLE_THUNDER_THIGHS = 314,
        COLLECTIBLE_STRANGE_ATTRACTOR = 315,
        COLLECTIBLE_CURSED_EYE = 316,
        COLLECTIBLE_MYSTERIOUS_LIQUID = 317,
        COLLECTIBLE_GEMINI = 318,
        COLLECTIBLE_CAINS_OTHER_EYE = 319,
        COLLECTIBLE_BLUE_BABYS_ONLY_FRIEND = 320,
        COLLECTIBLE_SAMSONS_CHAINS = 321,
        COLLECTIBLE_MONGO_BABY = 322,
        COLLECTIBLE_ISAACS_TEARS = 323,
        COLLECTIBLE_UNDEFINED = 324,
        COLLECTIBLE_SCISSORS = 325,
        COLLECTIBLE_BREATH_OF_LIFE = 326,
        COLLECTIBLE_POLAROID = 327,
        COLLECTIBLE_NEGATIVE = 328,
        COLLECTIBLE_LUDOVICO_TECHNIQUE = 329,
        COLLECTIBLE_SOY_MILK = 330,
        COLLECTIBLE_GODHEAD = 331,
        COLLECTIBLE_LAZARUS_RAGS = 332,
        COLLECTIBLE_MIND = 333,
        COLLECTIBLE_BODY = 334,
        COLLECTIBLE_SOUL = 335,
        COLLECTIBLE_DEAD_ONION = 336,
        COLLECTIBLE_BROKEN_WATCH = 337,
        COLLECTIBLE_BOOMERANG = 338,
        COLLECTIBLE_SAFETY_PIN = 339,
        COLLECTIBLE_CAFFEINE_PILL = 340,
        COLLECTIBLE_TORN_PHOTO = 341,
        COLLECTIBLE_BLUE_CAP = 342,
        COLLECTIBLE_LATCH_KEY = 343,
        COLLECTIBLE_MATCH_BOOK = 344,
        COLLECTIBLE_SYNTHOIL = 345,
        COLLECTIBLE_SNACK = 346,
        COLLECTIBLE_DIPLOPIA = 347,
        COLLECTIBLE_PLACEBO = 348,
        COLLECTIBLE_WOODEN_NICKEL = 349,
        COLLECTIBLE_TOXIC_SHOCK = 350,
        COLLECTIBLE_MEGA_BEAN = 351,
        COLLECTIBLE_GLASS_CANNON = 352,
        COLLECTIBLE_BOMBER_BOY = 353,
        COLLECTIBLE_CRACK_JACKS = 354,
        COLLECTIBLE_MOMS_PEARLS = 355,
        COLLECTIBLE_CAR_BATTERY = 356,
        COLLECTIBLE_BOX_OF_FRIENDS = 357,
        COLLECTIBLE_THE_WIZ = 358,
        COLLECTIBLE_8_INCH_NAILS = 359,
        COLLECTIBLE_INCUBUS = 360,
        COLLECTIBLE_FATES_REWARD = 361,
        COLLECTIBLE_LIL_CHEST = 362,
        COLLECTIBLE_SWORN_PROTECTOR = 363,
        COLLECTIBLE_FRIEND_ZONE = 364,
        COLLECTIBLE_LOST_FLY = 365,
        COLLECTIBLE_SCATTER_BOMBS = 366,
        COLLECTIBLE_STICKY_BOMBS = 367,
        COLLECTIBLE_EPIPHORA = 368,
        COLLECTIBLE_CONTINUUM = 369,
        COLLECTIBLE_MR_DOLLY = 370,
        COLLECTIBLE_CURSE_OF_THE_TOWER = 371,
        COLLECTIBLE_CHARGED_BABY = 372,
        COLLECTIBLE_DEAD_EYE = 373,
        COLLECTIBLE_HOLY_LIGHT = 374,
        COLLECTIBLE_HOST_HAT = 375,
        COLLECTIBLE_RESTOCK = 376,
        COLLECTIBLE_BURSTING_SACK = 377,
        COLLECTIBLE_NUMBER_TWO = 378,
        COLLECTIBLE_PUPULA_DUPLEX = 379,
        COLLECTIBLE_PAY_TO_PLAY = 380,
        COLLECTIBLE_EDENS_BLESSING = 381,
        COLLECTIBLE_FRIEND_BALL = 382,
        COLLECTIBLE_TEAR_DETONATOR = 383,
        COLLECTIBLE_LIL_GURDY = 384,
        COLLECTIBLE_BUMBO = 385,
        COLLECTIBLE_D12 = 386,
        COLLECTIBLE_CENSER = 387,
        COLLECTIBLE_KEY_BUM = 388,
        COLLECTIBLE_RUNE_BAG = 389,
        COLLECTIBLE_SERAPHIM = 390,
        COLLECTIBLE_BETRAYAL = 391,
        COLLECTIBLE_ZODIAC = 392,
        COLLECTIBLE_SERPENTS_KISS = 393,
        COLLECTIBLE_MARKED = 394,
        COLLECTIBLE_TECH_X = 395,
        COLLECTIBLE_VENTRICLE_RAZOR = 396,
        COLLECTIBLE_TRACTOR_BEAM = 397,
        COLLECTIBLE_GODS_FLESH = 398,
        COLLECTIBLE_MAW_OF_THE_VOID = 399,
        COLLECTIBLE_SPEAR_OF_DESTINY = 400,
        COLLECTIBLE_EXPLOSIVO = 401,
        COLLECTIBLE_CHAOS = 402,
        COLLECTIBLE_SPIDER_MOD = 403,
        COLLECTIBLE_FARTING_BABY = 404,
        COLLECTIBLE_GB_BUG = 405,
        COLLECTIBLE_D8 = 406,
        COLLECTIBLE_PURITY = 407,
        COLLECTIBLE_ATHAME = 408,
        COLLECTIBLE_EMPTY_VESSEL = 409,
        COLLECTIBLE_EVIL_EYE = 410,
        COLLECTIBLE_LUSTY_BLOOD = 411,
        COLLECTIBLE_CAMBION_CONCEPTION = 412,
        COLLECTIBLE_IMMACULATE_CONCEPTION = 413,
        COLLECTIBLE_MORE_OPTIONS = 414,
        COLLECTIBLE_CROWN_OF_LIGHT = 415,
        COLLECTIBLE_DEEP_POCKETS = 416,
        COLLECTIBLE_SUCCUBUS = 417,
        COLLECTIBLE_FRUIT_CAKE = 418,
        COLLECTIBLE_TELEPORT_2 = 419,
        COLLECTIBLE_BLACK_POWDER = 420,
        COLLECTIBLE_KIDNEY_BEAN = 421,
        COLLECTIBLE_GLOWING_HOUR_GLASS = 422,
        COLLECTIBLE_CIRCLE_OF_PROTECTION = 423,
        COLLECTIBLE_SACK_HEAD = 424,
        COLLECTIBLE_NIGHT_LIGHT = 425,
        COLLECTIBLE_OBSESSED_FAN = 426,
        COLLECTIBLE_MINE_CRAFTER = 427,
        COLLECTIBLE_PJS = 428,
        COLLECTIBLE_HEAD_OF_THE_KEEPER = 429,
        COLLECTIBLE_PAPA_FLY = 430,
        COLLECTIBLE_MULTIDIMENSIONAL_BABY = 431,
        COLLECTIBLE_GLITTER_BOMBS = 432,
        COLLECTIBLE_MY_SHADOW = 433,
        COLLECTIBLE_JAR_OF_FLIES = 434,
        COLLECTIBLE_LIL_LOKI = 435,
        COLLECTIBLE_MILK = 436,
        COLLECTIBLE_D7 = 437,
        COLLECTIBLE_BINKY = 438,
        COLLECTIBLE_MOMS_BOX = 439,
        COLLECTIBLE_KIDNEY_STONE = 440,
        COLLECTIBLE_MEGA_BLAST = 441,
        COLLECTIBLE_DARK_PRINCES_CROWN = 442,
        COLLECTIBLE_APPLE = 443,
        COLLECTIBLE_LEAD_PENCIL = 444,
        COLLECTIBLE_DOG_TOOTH = 445,
        COLLECTIBLE_DEAD_TOOTH = 446,
        COLLECTIBLE_LINGER_BEAN = 447,
        COLLECTIBLE_SHARD_OF_GLASS = 448,
        COLLECTIBLE_METAL_PLATE = 449,
        COLLECTIBLE_EYE_OF_GREED = 450,
        COLLECTIBLE_TAROT_CLOTH = 451,
        COLLECTIBLE_VARICOSE_VEINS = 452,
        COLLECTIBLE_COMPOUND_FRACTURE = 453,
        COLLECTIBLE_POLYDACTYLY = 454,
        COLLECTIBLE_DADS_LOST_COIN = 455,
        COLLECTIBLE_MIDNIGHT_SNACK = 456,
        COLLECTIBLE_CONE_HEAD = 457,
        COLLECTIBLE_BELLY_BUTTON = 458,
        COLLECTIBLE_SINUS_INFECTION = 459,
        COLLECTIBLE_GLAUCOMA = 460,
        COLLECTIBLE_PARASITOID = 461,
        COLLECTIBLE_EYE_OF_BELIAL = 462,
        COLLECTIBLE_SULFURIC_ACID = 463,
        COLLECTIBLE_GLYPH_OF_BALANCE = 464,
        COLLECTIBLE_ANALOG_STICK = 465,
        COLLECTIBLE_CONTAGION = 466,
        COLLECTIBLE_FINGER = 467,
        COLLECTIBLE_SHADE = 468,
        COLLECTIBLE_DEPRESSION = 469,
        COLLECTIBLE_HUSHY = 470,
        COLLECTIBLE_LIL_MONSTRO = 471,
        COLLECTIBLE_KING_BABY = 472,
        COLLECTIBLE_BIG_CHUBBY = 473,
        COLLECTIBLE_BROKEN_GLASS_CANNON = 474,
        COLLECTIBLE_PLAN_C = 475,
        COLLECTIBLE_D1 = 476,
        COLLECTIBLE_VOID = 477,
        COLLECTIBLE_PAUSE = 478,
        COLLECTIBLE_SMELTER = 479,
        COLLECTIBLE_COMPOST = 480,
        COLLECTIBLE_DATAMINER = 481,
        COLLECTIBLE_CLICKER = 482,
        COLLECTIBLE_MAMA_MEGA = 483,
        COLLECTIBLE_WAIT_WHAT = 484,
        COLLECTIBLE_CROOKED_PENNY = 485,
        COLLECTIBLE_DULL_RAZOR = 486,
        COLLECTIBLE_POTATO_PEELER = 487,
        COLLECTIBLE_METRONOME = 488,
        COLLECTIBLE_D_INFINITY = 489,
        COLLECTIBLE_EDENS_SOUL = 490,
        COLLECTIBLE_ACID_BABY = 491,
        COLLECTIBLE_YO_LISTEN = 492,
        COLLECTIBLE_ADRENALINE = 493,
        COLLECTIBLE_JACOBS_LADDER = 494,
        COLLECTIBLE_GHOST_PEPPER = 495,
        COLLECTIBLE_EUTHANASIA = 496,
        COLLECTIBLE_CAMO_UNDIES = 497,
        COLLECTIBLE_DUALITY = 498,
        COLLECTIBLE_EUCHARIST = 499,
        COLLECTIBLE_SACK_OF_SACKS = 500,
        COLLECTIBLE_GREEDS_GULLET = 501,
        COLLECTIBLE_LARGE_ZIT = 502,
        COLLECTIBLE_LITTLE_HORN = 503,
        COLLECTIBLE_BROWN_NUGGET = 504,
        COLLECTIBLE_POKE_GO = 505,
        COLLECTIBLE_BACKSTABBER = 506,
        COLLECTIBLE_SHARP_STRAW = 507,
        COLLECTIBLE_MOMS_RAZOR = 508,
        COLLECTIBLE_BLOODSHOT_EYE = 509,
        COLLECTIBLE_DELIRIOUS = 510,
        
        // Booster Pack #1
        COLLECTIBLE_ANGRY_FLY = 511,
        COLLECTIBLE_BLACK_HOLE = 512,
        COLLECTIBLE_BOZO = 513,
        COLLECTIBLE_BROKEN_MODEM = 514,
        COLLECTIBLE_MYSTERY_GIFT = 515,
        COLLECTIBLE_SPRINKLER = 516,
        COLLECTIBLE_FAST_BOMBS = 517,
        COLLECTIBLE_BUDDY_IN_A_BOX = 518,
        COLLECTIBLE_LIL_DELIRIUM = 519,

        // Booster Pack #2
        COLLECTIBLE_JUMPER_CABLES = 520,
        COLLECTIBLE_COUPON = 521,
        COLLECTIBLE_TELEKINESIS = 522,
        COLLECTIBLE_MOVING_BOX = 523,
        COLLECTIBLE_TECHNOLOGY_ZERO = 524,
        COLLECTIBLE_LEPROSY = 525,
        
        // Booster Pack #3
        COLLECTIBLE_7_SEALS = 526,
        COLLECTIBLE_MR_ME = 527,
        COLLECTIBLE_ANGELIC_PRISM = 528,
        COLLECTIBLE_POP = 529,

        // Booster Pack #4
        COLLECTIBLE_DEATHS_LIST = 530,
        COLLECTIBLE_HAEMOLACRIA = 531,
        COLLECTIBLE_LACHRYPHAGY = 532,
        COLLECTIBLE_TRISAGION = 533,
        COLLECTIBLE_SCHOOLBAG = 534,
        
        // Booster Pack #5
        COLLECTIBLE_BLANKET = 535,
        COLLECTIBLE_SACRIFICIAL_ALTAR = 536,
        COLLECTIBLE_LIL_SPEWER = 537,
        COLLECTIBLE_MARBLES = 538,
        COLLECTIBLE_MYSTERY_EGG = 539,
        COLLECTIBLE_FLAT_STONE = 540,

        COLLECTIBLE_MARROW = 541,
        COLLECTIBLE_SLIPPED_RIB = 542,
        COLLECTIBLE_HALLOWED_GROUND = 543,
        COLLECTIBLE_POINTY_RIB = 544,
        COLLECTIBLE_BOOK_OF_THE_DEAD = 545,
        COLLECTIBLE_DADS_RING = 546,
        COLLECTIBLE_DIVORCE_PAPERS = 547,
        COLLECTIBLE_JAW_BONE = 548,
        COLLECTIBLE_BRITTLE_BONES = 549,

        COLLECTIBLE_BROKEN_SHOVEL_1 = 550,
        COLLECTIBLE_BROKEN_SHOVEL_2 = 551,
        COLLECTIBLE_MOMS_SHOVEL = 552,

        //NUM_COLLECTIBLES = 553
        
        // Repentance
        COLLECTIBLE_MUCORMYCOSIS = 553,
        COLLECTIBLE_2SPOOKY = 554,
        COLLECTIBLE_GOLDEN_RAZOR = 555,
        COLLECTIBLE_SULFUR = 556,
        COLLECTIBLE_FORTUNE_COOKIE = 557,
        COLLECTIBLE_EYE_SORE = 558,
        COLLECTIBLE_120_VOLT = 559,
        COLLECTIBLE_IT_HURTS = 560,
        COLLECTIBLE_ALMOND_MILK = 561,
        COLLECTIBLE_ROCK_BOTTOM = 562,
        COLLECTIBLE_NANCY_BOMBS = 563,
        COLLECTIBLE_BAR_OF_SOAP = 564,
        COLLECTIBLE_BLOOD_PUPPY = 565,
        COLLECTIBLE_DREAM_CATCHER = 566,
        COLLECTIBLE_PASCHAL_CANDLE = 567,
        COLLECTIBLE_DIVINE_INTERVENTION = 568,
        COLLECTIBLE_BLOOD_OATH = 569,
        COLLECTIBLE_PLAYDOUGH_COOKIE = 570,
        COLLECTIBLE_SOCKS = 571,
        COLLECTIBLE_EYE_OF_THE_OCCULT = 572,
        COLLECTIBLE_IMMACULATE_HEART = 573,
        COLLECTIBLE_MONSTRANCE = 574,
        COLLECTIBLE_INTRUDER = 575,
        COLLECTIBLE_DIRTY_MIND = 576,
        COLLECTIBLE_DAMOCLES = 577,
        COLLECTIBLE_FREE_LEMONADE = 578,
        COLLECTIBLE_SPIRIT_SWORD = 579,
        COLLECTIBLE_RED_KEY = 580,
        COLLECTIBLE_PSY_FLY = 581,
        COLLECTIBLE_WAVY_CAP = 582,
        COLLECTIBLE_ROCKET_IN_A_JAR = 583,
        COLLECTIBLE_BOOK_OF_VIRTUES = 584,
        COLLECTIBLE_ALABASTER_BOX = 585,
        COLLECTIBLE_STAIRWAY = 586,
        // 587
        COLLECTIBLE_SOL = 588,
        COLLECTIBLE_LUNA = 589,
        COLLECTIBLE_MERCURIUS = 590,
        COLLECTIBLE_VENUS = 591,
        COLLECTIBLE_TERRA = 592,
        COLLECTIBLE_MARS = 593,
        COLLECTIBLE_JUPITER = 594,
        COLLECTIBLE_SATURNUS = 595,
        COLLECTIBLE_URANUS = 596,
        COLLECTIBLE_NEPTUNUS = 597,
        COLLECTIBLE_PLUTO = 598,
        COLLECTIBLE_VOODOO_HEAD = 599,
        COLLECTIBLE_EYE_DROPS = 600,
        COLLECTIBLE_ACT_OF_CONTRITION = 601,
        COLLECTIBLE_MEMBER_CARD = 602,
        COLLECTIBLE_BATTERY_PACK = 603,
        COLLECTIBLE_MOMS_BRACELET = 604,
        COLLECTIBLE_SCOOPER = 605,
        COLLECTIBLE_OCULAR_RIFT = 606,
        COLLECTIBLE_BOILED_BABY = 607,
        COLLECTIBLE_FREEZER_BABY = 608,
        COLLECTIBLE_ETERNAL_D6 = 609,
        COLLECTIBLE_BIRD_CAGE = 610,
        COLLECTIBLE_LARYNX = 611,
        COLLECTIBLE_LOST_SOUL = 612,
        // 613
        COLLECTIBLE_BLOOD_BOMBS = 614,
        COLLECTIBLE_LIL_DUMPY = 615,
        COLLECTIBLE_BIRDS_EYE = 616,
        COLLECTIBLE_LODESTONE = 617,
        COLLECTIBLE_ROTTEN_TOMATO = 618,
        COLLECTIBLE_BIRTHRIGHT = 619,
        // 620
        COLLECTIBLE_RED_STEW = 621,
        COLLECTIBLE_GENESIS = 622,
        COLLECTIBLE_SHARP_KEY = 623,
        COLLECTIBLE_BOOSTER_PACK = 624,
        COLLECTIBLE_MEGA_MUSH = 625,
        COLLECTIBLE_KNIFE_PIECE_1 = 626,
        COLLECTIBLE_KNIFE_PIECE_2 = 627,
        COLLECTIBLE_DEATH_CERTIFICATE = 628,
        COLLECTIBLE_BOT_FLY = 629,
        // 630
        COLLECTIBLE_MEAT_CLEAVER = 631,
        COLLECTIBLE_EVIL_CHARM = 632,
        COLLECTIBLE_DOGMA = 633,
        COLLECTIBLE_PURGATORY = 634,
        COLLECTIBLE_STITCHES = 635,
        COLLECTIBLE_R_KEY = 636,
        COLLECTIBLE_KNOCKOUT_DROPS = 637,
        COLLECTIBLE_ERASER = 638,
        COLLECTIBLE_YUCK_HEART = 639,
        COLLECTIBLE_URN_OF_SOULS = 640,
        COLLECTIBLE_AKELDAMA = 641,
        COLLECTIBLE_MAGIC_SKIN = 642,
        COLLECTIBLE_REVELATION = 643,
        COLLECTIBLE_CONSOLATION_PRIZE = 644,
        COLLECTIBLE_TINYTOMA = 645,
        COLLECTIBLE_BRIMSTONE_BOMBS = 646,
        COLLECTIBLE_4_5_VOLT = 647,
        // 648
        COLLECTIBLE_FRUITY_PLUM = 649,
        COLLECTIBLE_PLUM_FLUTE = 650,
        COLLECTIBLE_STAR_OF_BETHLEHEM = 651,
        COLLECTIBLE_CUBE_BABY = 652,
        COLLECTIBLE_VADE_RETRO = 653,
        COLLECTIBLE_FALSE_PHD = 654,
        COLLECTIBLE_SPIN_TO_WIN = 655,
        COLLECTIBLE_DAMOCLES_PASSIVE = 656,
        COLLECTIBLE_VASCULITIS = 657,
        COLLECTIBLE_GIANT_CELL = 658,
        COLLECTIBLE_TROPICAMIDE = 659,
        COLLECTIBLE_CARD_READING = 660,
        COLLECTIBLE_QUINTS = 661,
        // 662
        COLLECTIBLE_TOOTH_AND_NAIL = 663,
        COLLECTIBLE_BINGE_EATER = 664,
        COLLECTIBLE_GUPPYS_EYE = 665,
        // 666
        COLLECTIBLE_STRAW_MAN = 667,
        COLLECTIBLE_DADS_NOTE = 668,
        COLLECTIBLE_SAUSAGE = 669,
        COLLECTIBLE_OPTIONS = 670,
        COLLECTIBLE_CANDY_HEART = 671,
        COLLECTIBLE_POUND_OF_FLESH = 672,
        COLLECTIBLE_REDEMPTION = 673,
        COLLECTIBLE_SPIRIT_SHACKLES = 674,
        COLLECTIBLE_CRACKED_ORB = 675,
        COLLECTIBLE_EMPTY_HEART = 676,
        COLLECTIBLE_ASTRAL_PROJECTION = 677,
        COLLECTIBLE_C_SECTION = 678,
        COLLECTIBLE_LIL_ABADDON = 679,
        COLLECTIBLE_MONTEZUMAS_REVENGE = 680,
        COLLECTIBLE_LIL_PORTAL = 681,
        COLLECTIBLE_WORM_FRIEND = 682,
        COLLECTIBLE_BONE_SPURS = 683,
        COLLECTIBLE_HUNGRY_SOUL = 684,
        COLLECTIBLE_JAR_OF_WISPS = 685,
        COLLECTIBLE_SOUL_LOCKET = 686,
        COLLECTIBLE_FRIEND_FINDER = 687,
        COLLECTIBLE_INNER_CHILD = 688,
        COLLECTIBLE_GLITCHED_CROWN = 689,
        COLLECTIBLE_JELLY_BELLY = 690,
        COLLECTIBLE_SACRED_ORB = 691,
        COLLECTIBLE_SANGUINE_BOND = 692,
        COLLECTIBLE_SWARM = 693,
        COLLECTIBLE_HEARTBREAK = 694,
        COLLECTIBLE_BLOODY_GUST = 695,
        COLLECTIBLE_SALVATION = 696,
        COLLECTIBLE_VANISHING_TWIN = 697,
        COLLECTIBLE_TWISTED_PAIR = 698,
        COLLECTIBLE_AZAZELS_RAGE = 699,
        COLLECTIBLE_ECHO_CHAMBER = 700,
        COLLECTIBLE_ISAACS_TOMB = 701,
        COLLECTIBLE_VENGEFUL_SPIRIT = 702,
        COLLECTIBLE_ESAU_JR = 703,
        COLLECTIBLE_BERSERK = 704,
        COLLECTIBLE_DARK_ARTS = 705,
        COLLECTIBLE_ABYSS = 706,
        COLLECTIBLE_SUPPER = 707,
        COLLECTIBLE_STAPLER = 708,
        COLLECTIBLE_SUPLEX = 709,
        COLLECTIBLE_BAG_OF_CRAFTING = 710,
        COLLECTIBLE_FLIP = 711,
        COLLECTIBLE_LEMEGETON = 712,
        COLLECTIBLE_SUMPTORIUM = 713,
        COLLECTIBLE_RECALL = 714,
        COLLECTIBLE_HOLD = 715,
        COLLECTIBLE_KEEPERS_SACK = 716,
        COLLECTIBLE_KEEPERS_KIN = 717,
        // 718
        COLLECTIBLE_KEEPERS_BOX = 719,
        COLLECTIBLE_EVERYTHING_JAR = 720,
        COLLECTIBLE_TMTRAINER = 721,
        COLLECTIBLE_ANIMA_SOLA = 722,
        COLLECTIBLE_SPINDOWN_DICE = 723,
        COLLECTIBLE_HYPERCOAGULATION = 724,
        COLLECTIBLE_IBS = 725,
        COLLECTIBLE_HEMOPTYSIS = 726,
        COLLECTIBLE_GHOST_BOMBS = 727,
        COLLECTIBLE_GELLO = 728,
        COLLECTIBLE_DECAP_ATTACK = 729,
        COLLECTIBLE_GLASS_EYE = 730,
        COLLECTIBLE_STYE = 731,
        COLLECTIBLE_MOMS_RING = 732,
        
        NUM_COLLECTIBLES = 733
};

enum eCard {
        CARD_RANDOM = -1,
        CARD_NULL = 0,
        CARD_FOOL = 1,
        CARD_MAGICIAN = 2,
        CARD_HIGH_PRIESTESS = 3,
        CARD_EMPRESS = 4,
        CARD_EMPEROR = 5,
        CARD_HIEROPHANT = 6,
        CARD_LOVERS = 7,
        CARD_CHARIOT = 8,
        CARD_JUSTICE = 9,
        CARD_HERMIT = 10,
        CARD_WHEEL_OF_FORTUNE = 11,
        CARD_STRENGTH = 12,
        CARD_HANGED_MAN = 13,
        CARD_DEATH = 14,
        CARD_TEMPERANCE = 15,
        CARD_DEVIL = 16,
        CARD_TOWER = 17,
        CARD_STARS = 18,
        CARD_MOON = 19,
        CARD_SUN = 20,
        CARD_JUDGEMENT = 21,
        CARD_WORLD = 22,
        CARD_CLUBS_2 = 23,
        CARD_DIAMONDS_2 = 24,
        CARD_SPADES_2 = 25,
        CARD_HEARTS_2 = 26,
        CARD_ACE_OF_CLUBS = 27,
        CARD_ACE_OF_DIAMONDS = 28,
        CARD_ACE_OF_SPADES = 29,
        CARD_ACE_OF_HEARTS = 30,
        CARD_JOKER = 31,
        RUNE_HAGALAZ = 32,
        RUNE_JERA = 33,
        RUNE_EHWAZ = 34,
        RUNE_DAGAZ = 35,
        RUNE_ANSUZ = 36,
        RUNE_PERTHRO = 37,
        RUNE_BERKANO = 38,
        RUNE_ALGIZ = 39,
        RUNE_BLANK = 40,
        RUNE_BLACK = 41,
        CARD_CHAOS = 42,
        CARD_CREDIT = 43,
        CARD_RULES = 44,
        CARD_HUMANITY = 45,
        CARD_SUICIDE_KING = 46,
        CARD_GET_OUT_OF_JAIL = 47,
        CARD_QUESTIONMARK = 48,
        CARD_DICE_SHARD = 49,
        CARD_EMERGENCY_CONTACT = 50,
        CARD_HOLY = 51,
        CARD_HUGE_GROWTH = 52,
        CARD_ANCIENT_RECALL = 53,
        CARD_ERA_WALK = 54,
        RUNE_SHARD = 55,
        CARD_REVERSE_FOOL = 56,
        CARD_REVERSE_MAGICIAN = 57,
        CARD_REVERSE_HIGH_PRIESTESS = 58,
        CARD_REVERSE_EMPRESS = 59,
        CARD_REVERSE_EMPEROR = 60,
        CARD_REVERSE_HIEROPHANT = 61,
        CARD_REVERSE_LOVERS = 62,
        CARD_REVERSE_CHARIOT = 63,
        CARD_REVERSE_JUSTICE = 64,
        CARD_REVERSE_HERMIT = 65,
        CARD_REVERSE_WHEEL_OF_FORTUNE = 66,
        CARD_REVERSE_STRENGTH = 67,
        CARD_REVERSE_HANGED_MAN = 68,
        CARD_REVERSE_DEATH = 69,
        CARD_REVERSE_TEMPERANCE = 70,
        CARD_REVERSE_DEVIL = 71,
        CARD_REVERSE_TOWER = 72,
        CARD_REVERSE_STARS = 73,
        CARD_REVERSE_MOON = 74,
        CARD_REVERSE_SUN = 75,
        CARD_REVERSE_JUDGEMENT = 76,
        CARD_REVERSE_WORLD = 77,
        CARD_CRACKED_KEY = 78,
        CARD_QUEEN_OF_HEARTS = 79,
        CARD_WILD = 80,
        CARD_SOUL_ISAAC = 81,
        CARD_SOUL_MAGDALENE = 82,
        CARD_SOUL_CAIN = 83,
        CARD_SOUL_JUDAS = 84,
        CARD_SOUL_BLUEBABY = 85,
        CARD_SOUL_EVE = 86,
        CARD_SOUL_SAMSON = 87,
        CARD_SOUL_AZAZEL = 88,
        CARD_SOUL_LAZARUS = 89,
        CARD_SOUL_EDEN = 90,
        CARD_SOUL_LOST = 91,
        CARD_SOUL_LILITH = 92,
        CARD_SOUL_KEEPER = 93,
        CARD_SOUL_APOLLYON = 94,
        CARD_SOUL_FORGOTTEN = 95,
        CARD_SOUL_BETHANY = 96,
        CARD_SOUL_JACOB = 97,
		
        NUM_CARDS,
};

enum eCardType {
        CARDTYPE_TAROT = 0,
        CARDTYPE_SUIT = 1,
        CARDTYPE_RUNE = 2,
        CARDTYPE_SPECIAL = 3,
        CARDTYPE_OBJECT = 4,
        CARDTYPE_TAROT_REVERSE = 5
};

enum ePillEffect {
    PILLEFFECT_NULL = -1,
    PILLEFFECT_BAD_GAS = 0,
    PILLEFFECT_BAD_TRIP = 1,
    PILLEFFECT_BALLS_OF_STEEL = 2,
    PILLEFFECT_BOMBS_ARE_KEYS = 3,
    PILLEFFECT_EXPLOSIVE_DIARRHEA = 4,
    PILLEFFECT_FULL_HEALTH = 5,
    PILLEFFECT_HEALTH_DOWN = 6,
    PILLEFFECT_HEALTH_UP = 7,
    PILLEFFECT_I_FOUND_PILLS = 8,
    PILLEFFECT_PUBERTY = 9,
    PILLEFFECT_PRETTY_FLY = 10,
    PILLEFFECT_RANGE_DOWN = 11,
    PILLEFFECT_RANGE_UP = 12,
    PILLEFFECT_SPEED_DOWN = 13,
    PILLEFFECT_SPEED_UP = 14,
    PILLEFFECT_TEARS_DOWN = 15,
    PILLEFFECT_TEARS_UP = 16,
    PILLEFFECT_LUCK_DOWN = 17,
    PILLEFFECT_LUCK_UP = 18,
    PILLEFFECT_TELEPILLS = 19,
    PILLEFFECT_48HOUR_ENERGY = 20,
    PILLEFFECT_HEMATEMESIS = 21,
    PILLEFFECT_PARALYSIS = 22,
    PILLEFFECT_SEE_FOREVER = 23,
    PILLEFFECT_PHEROMONES = 24,
    PILLEFFECT_AMNESIA = 25,
    PILLEFFECT_LEMON_PARTY = 26,
    PILLEFFECT_WIZARD = 27,
    PILLEFFECT_PERCS = 28,
    PILLEFFECT_ADDICTED = 29,
    PILLEFFECT_RELAX = 30,
    PILLEFFECT_QUESTIONMARK = 31,
    PILLEFFECT_LARGER = 32,
    PILLEFFECT_SMALLER = 33,
    PILLEFFECT_INFESTED_EXCLAMATION = 34,
    PILLEFFECT_INFESTED_QUESTION = 35,
    PILLEFFECT_POWER = 36,
    PILLEFFECT_RETRO_VISION = 37,
    PILLEFFECT_FRIENDS_TILL_THE_END = 38,
    PILLEFFECT_X_LAX = 39,
    PILLEFFECT_SOMETHINGS_WRONG = 40,
    PILLEFFECT_IM_DROWSY = 41,
    PILLEFFECT_IM_EXCITED = 42,
    PILLEFFECT_GULP = 43,
    PILLEFFECT_HORF = 44,
    PILLEFFECT_SUNSHINE = 45,
    PILLEFFECT_VURP = 46,
    PILLEFFECT_SHOT_SPEED_DOWN = 47,
    PILLEFFECT_SHOT_SPEED_UP = 48,
    PILLEFFECT_EXPERIMENTAL = 49,
	
    NUM_PILL_EFFECTS,
};

enum ePillColor {
    PILL_NULL = 0,
    PILL_BLUE_BLUE = 1,
    PILL_WHITE_BLUE = 2,
    PILL_ORANGE_ORANGE = 3,
    PILL_WHITE_WHITE = 4,
    PILL_REDDOTS_RED = 5,
    PILL_PINK_RED = 6,
    PILL_BLUE_CADETBLUE = 7,
    PILL_YELLOW_ORANGE = 8,
    PILL_ORANGEDOTS_WHITE = 9,
    PILL_WHITE_AZURE = 10,
    PILL_BLACK_YELLOW = 11,
    PILL_WHITE_BLACK = 12,
    PILL_WHITE_YELLOW = 13,
    NUM_STANDARD_PILLS = 14,
    PILL_GOLD = 14,
	
    NUM_PILLS,
	
    PILL_GIANT_FLAG = 1 << 11,
    PILL_COLOR_MASK = (1 << 11) - 1,
};
        
enum LevelStateFlag
{
        STATE_BUM_KILLED = 0,
        STATE_EVIL_BUM_KILLED = 1,
        STATE_REDHEART_DAMAGED = 2,
        STATE_BUM_LEFT = 3,
        STATE_EVIL_BUM_LEFT = 4,
        STATE_DAMAGED = 5,
        STATE_SHOPKEEPER_KILLED_LVL = 6,
        STATE_COMPASS_EFFECT = 7,
        STATE_MAP_EFFECT = 8,
        STATE_BLUE_MAP_EFFECT = 9,
        STATE_FULL_MAP_EFFECT = 10,
        STATE_GREED_LOST_PENALTY = 11,
        STATE_GREED_MONSTRO_SPAWNED = 12,
        STATE_ITEM_DUNGEON_FOUND = 13,
        STATE_MAMA_MEGA_USED = 14,
        //NUM_STATE_FLAGS = 15

        STATE_WOODEN_CROSS_REMOVED = 15,
        STATE_SHOVEL_QUEST_TRIGGERED = 16,
        STATE_SATANIC_BIBLE_USED = 17,
        STATE_SOL_EFFECT = 18,
        STATE_LEVEL_START_TRIGGERED = 19,
        STATE_LUNA_EFFECT = 20,
        STATE_VOID_DOOR_DISABLED = 21,
        STATE_MINESHAFT_ESCAPE = 22,
        STATE_MIRROR_BROKEN = 23,
        NUM_STATE_FLAGS = 24
};

enum TrinketType
{
        TRINKET_NULL = 0,
        TRINKET_SWALLOWED_PENNY = 1,
        TRINKET_PETRIFIED_POOP = 2,
        TRINKET_AAA_BATTERY = 3,
        TRINKET_BROKEN_REMOTE = 4,
        TRINKET_PURPLE_HEART = 5,
        TRINKET_BROKEN_MAGNET = 6,
        TRINKET_ROSARY_BEAD = 7,
        TRINKET_CARTRIDGE = 8,
        TRINKET_PULSE_WORM = 9,
        TRINKET_WIGGLE_WORM = 10,
        TRINKET_RING_WORM = 11,
        TRINKET_FLAT_WORM = 12,
        TRINKET_STORE_CREDIT = 13,
        TRINKET_CALLUS = 14,
        TRINKET_LUCKY_ROCK = 15,
        TRINKET_MOMS_TOENAIL = 16,
        TRINKET_BLACK_LIPSTICK = 17,
        TRINKET_BIBLE_TRACT = 18,
        TRINKET_PAPER_CLIP = 19,
        TRINKET_MONKEY_PAW = 20,
        TRINKET_MYSTERIOUS_PAPER = 21,
        TRINKET_DAEMONS_TAIL = 22,
        TRINKET_MISSING_POSTER = 23,
        TRINKET_BUTT_PENNY = 24,
        TRINKET_MYSTERIOUS_CANDY = 25,
        TRINKET_HOOK_WORM = 26,
        TRINKET_WHIP_WORM = 27,
        TRINKET_BROKEN_ANKH = 28,
        TRINKET_FISH_HEAD = 29,
        TRINKET_PINKY_EYE = 30,
        TRINKET_PUSH_PIN = 31,
        TRINKET_LIBERTY_CAP = 32,
        TRINKET_UMBILICAL_CORD = 33,
        TRINKET_CHILDS_HEART = 34,
        TRINKET_CURVED_HORN = 35,
        TRINKET_RUSTED_KEY = 36,
        TRINKET_GOAT_HOOF = 37,
        TRINKET_MOMS_PEARL = 38,
        TRINKET_CANCER = 39,
        TRINKET_RED_PATCH = 40,
        TRINKET_MATCH_STICK = 41,
        TRINKET_LUCKY_TOE = 42,
        TRINKET_CURSED_SKULL = 43,
        TRINKET_SAFETY_CAP = 44,
        TRINKET_ACE_SPADES = 45,
        TRINKET_ISAACS_FORK = 46,
        TRINKET_POLAROID_OBSOLETE = 47,
        TRINKET_MISSING_PAGE = 48,
        TRINKET_BLOODY_PENNY = 49,
        TRINKET_BURNT_PENNY = 50,
        TRINKET_FLAT_PENNY = 51,
        TRINKET_COUNTERFEIT_PENNY = 52,
        TRINKET_TICK = 53,
        TRINKET_ISAACS_HEAD = 54,
        TRINKET_MAGGYS_FAITH = 55,
        TRINKET_JUDAS_TONGUE = 56,
        TRINKET_SOUL = 57,
        TRINKET_SAMSONS_LOCK = 58,
        TRINKET_CAINS_EYE = 59,
        TRINKET_EVES_BIRD_FOOT = 60,
        TRINKET_LEFT_HAND = 61,
        TRINKET_SHINY_ROCK = 62,
        TRINKET_SAFETY_SCISSORS = 63,
        TRINKET_RAINBOW_WORM = 64,
        TRINKET_TAPE_WORM = 65,
        TRINKET_LAZY_WORM = 66,
        TRINKET_CRACKED_DICE = 67,
        TRINKET_SUPER_MAGNET = 68,
        TRINKET_FADED_POLAROID = 69,
        TRINKET_LOUSE = 70,
        TRINKET_BOBS_BLADDER = 71,
        TRINKET_WATCH_BATTERY = 72,
        TRINKET_BLASTING_CAP = 73,
        TRINKET_STUD_FINDER = 74,
        TRINKET_ERROR = 75,
        TRINKET_POKER_CHIP = 76,
        TRINKET_BLISTER = 77,
        TRINKET_SECOND_HAND = 78,
        TRINKET_ENDLESS_NAMELESS = 79,
        TRINKET_BLACK_FEATHER = 80,
        TRINKET_BLIND_RAGE = 81,
        TRINKET_GOLDEN_HORSE_SHOE = 82,
        TRINKET_STORE_KEY = 83,
        TRINKET_RIB_OF_GREED = 84,
        TRINKET_KARMA = 85,
        TRINKET_LIL_LARVA = 86,
        TRINKET_MOMS_LOCKET = 87,
        TRINKET_NO = 88,
        TRINKET_CHILD_LEASH = 89,
        TRINKET_BROWN_CAP = 90,
        TRINKET_MECONIUM = 91,
        TRINKET_CRACKED_CROWN = 92,
        TRINKET_USED_DIAPER = 93,
        TRINKET_FISH_TAIL = 94,
        TRINKET_BLACK_TOOTH = 95,
        TRINKET_OUROBOROS_WORM = 96,
        TRINKET_TONSIL = 97,
        TRINKET_NOSE_GOBLIN = 98,
        TRINKET_SUPER_BALL = 99,
        TRINKET_VIBRANT_BULB = 100,
        TRINKET_DIM_BULB = 101,
        TRINKET_FRAGMENTED_CARD = 102,
        TRINKET_EQUALITY = 103,
        TRINKET_WISH_BONE = 104,
        TRINKET_BAG_LUNCH = 105,
        TRINKET_LOST_CORK = 106,
        TRINKET_CROW_HEART = 107,
        TRINKET_WALNUT = 108,
        TRINKET_DUCT_TAPE = 109,
        TRINKET_SILVER_DOLLAR = 110,
        TRINKET_BLOODY_CROWN = 111,
        TRINKET_PAY_TO_WIN = 112,
        TRINKET_LOCUST_OF_WRATH = 113,
        TRINKET_LOCUST_OF_PESTILENCE = 114,
        TRINKET_LOCUST_OF_FAMINE = 115,
        TRINKET_LOCUST_OF_DEATH = 116,
        TRINKET_LOCUST_OF_CONQUEST = 117,
        TRINKET_BAT_WING = 118,
        TRINKET_STEM_CELL = 119,
        
        // Booster pack #1
        TRINKET_HAIRPIN = 120,
        TRINKET_WOODEN_CROSS = 121,
        TRINKET_BUTTER = 122,

        // Booster pack #2
        TRINKET_FILIGREE_FEATHERS = 123,
        
        // Booster pack #3
        TRINKET_DOOR_STOP = 124,
        
        // Booster pack #4
        TRINKET_EXTENSION_CORD = 125,
        
        // Booster pack #5
        TRINKET_ROTTEN_PENNY = 126,
        TRINKET_BABY_BENDER = 127,
        TRINKET_FINGER_BONE = 128,
        
        //NUM_TRINKETS = 129
        
        // Repentance
        TRINKET_JAW_BREAKER = 129,
        TRINKET_CHEWED_PEN = 130,
        TRINKET_BLESSED_PENNY = 131,
        TRINKET_BROKEN_SYRINGE = 132,
        TRINKET_SHORT_FUSE = 133,
        TRINKET_GIGANTE_BEAN = 134,
        TRINKET_LIGHTER = 135,
        TRINKET_BROKEN_PADLOCK = 136,
        TRINKET_MYOSOTIS = 137,
        TRINKET_M = 138,
        TRINKET_TEARDROP_CHARM = 139,
        TRINKET_APPLE_OF_SODOM = 140,
        TRINKET_FORGOTTEN_LULLABY = 141,
        TRINKET_BETHS_FAITH = 142,
        TRINKET_OLD_CAPACITOR = 143,
        TRINKET_BRAIN_WORM = 144,
        TRINKET_PERFECTION = 145,
        TRINKET_DEVILS_CROWN = 146,
        TRINKET_CHARGED_PENNY = 147,
        TRINKET_FRIENDSHIP_NECKLACE = 148,
        TRINKET_PANIC_BUTTON = 149,
        TRINKET_BLUE_KEY = 150,
        TRINKET_FLAT_FILE = 151,
        TRINKET_TELESCOPE_LENS = 152,
        TRINKET_MOMS_LOCK = 153,
        TRINKET_DICE_BAG = 154,
        TRINKET_HOLY_CROWN = 155,
        TRINKET_MOTHERS_KISS = 156,
        TRINKET_TORN_CARD = 157,
        TRINKET_TORN_POCKET = 158,
        TRINKET_GILDED_KEY = 159,
        TRINKET_LUCKY_SACK = 160,
        TRINKET_WICKED_CROWN = 161,
        TRINKET_AZAZELS_STUMP = 162,
        TRINKET_DINGLE_BERRY = 163,
        TRINKET_RING_CAP = 164,
        TRINKET_NUH_UH = 165,
        TRINKET_MODELING_CLAY = 166,
        TRINKET_POLISHED_BONE = 167,
        TRINKET_HOLLOW_HEART = 168,
        TRINKET_KIDS_DRAWING = 169,
        TRINKET_CRYSTAL_KEY = 170,
        TRINKET_KEEPERS_BARGAIN = 171,
        TRINKET_CURSED_PENNY = 172,
        TRINKET_YOUR_SOUL = 173,
        TRINKET_NUMBER_MAGNET = 174,
        TRINKET_STRANGE_KEY = 175,
        TRINKET_LIL_CLOT = 176,
        TRINKET_TEMPORARY_TATTOO = 177,
        TRINKET_SWALLOWED_M80 = 178,
        TRINKET_RC_REMOTE = 179,
        TRINKET_FOUND_SOUL = 180,
        TRINKET_EXPANSION_PACK = 181,
        TRINKET_BETHS_ESSENCE = 182,
        TRINKET_THE_TWINS = 183,
        TRINKET_ADOPTION_PAPERS = 184,
        TRINKET_CRICKET_LEG = 185,
        TRINKET_APOLLYONS_BEST_FRIEND = 186,
        TRINKET_BROKEN_GLASSES = 187,
        TRINKET_ICE_CUBE = 188,
        TRINKET_SIGIL_OF_BAPHOMET = 189,
        NUM_TRINKETS = 190,
        
        // Golden trinkets
        TRINKET_GOLDEN_FLAG = 0x8000,
        TRINKET_ID_MASK = 0x7fff
};

enum StageType
{
        STAGETYPE_ORIGINAL = 0,
        STAGETYPE_WOTL = 1,
        STAGETYPE_AFTERBIRTH = 2,
        STAGETYPE_GREEDMODE = 3, // deprecated, Greed Mode no longer has its own stages
        STAGETYPE_REPENTANCE = 4,
        STAGETYPE_REPENTANCE_B = 5,
};

enum LevelStage 
{
        STAGE_NULL = 0,
        STAGE1_1 = 1,
        STAGE1_2 = 2,
        STAGE2_1 = 3,
        STAGE2_2 = 4,
        STAGE3_1 = 5,
        STAGE3_2 = 6,
        STAGE4_1 = 7,
        STAGE4_2 = 8,
        STAGE4_3 = 9,
        STAGE5 = 10,
        STAGE6 = 11,
        STAGE7 = 12,
        STAGE8 = 13, // Home
        NUM_STAGES = 14,
        
        STAGE1_GREED = 1,
        STAGE2_GREED = 2,
        STAGE3_GREED = 3,
        STAGE4_GREED = 4,
        STAGE5_GREED = 5,
        STAGE6_GREED = 6,
        STAGE7_GREED = 7,
        
        NUM_BACKWARDS_STAGES = 7 // Save stages up to Mausoleum II for the Ascent (7 stages)
};

enum eStbType {
    STB_SPECIAL_ROOMS = 0,
    STB_BASEMENT = 1,
    STB_CELLAR = 2,
    STB_BURNING_BASEMENT = 3,
    STB_CAVES = 4,
    STB_CATACOMBS = 5,
    STB_FLOODED_CAVES = 6,
    STB_DEPTHS = 7,
    STB_NECROPOLIS = 8,
    STB_DANK_DEPTHS = 9,
    STB_WOMB = 10,
    STB_UTERO = 11,
    STB_SCARRED_WOMB = 12,
    STB_BLUE_WOMB = 13,
    STB_SHEOL = 14,
    STB_CATHEDRAL = 15,
    STB_DARK_ROOM = 16,
    STB_CHEST = 17,
    STB_UNUSED1 = 18,
    STB_UNUSED2 = 19,
    STB_UNUSED3 = 20,
    STB_UNUSED4 = 21,
    STB_UNUSED5 = 22,
    STB_UNUSED6 = 23,
    STB_THE_SHOP = 24,
    STB_ULTRA_GREED = 25,
    STB_THE_VOID = 26,
    STB_DOWNPOUR = 27,
    STB_DROSS = 28,
    STB_MINES = 29,
    STB_ASHPIT = 30,
    STB_MAUSOLEUM = 31,
    STB_GEHENNA = 32,
    STB_CORPSE = 33,
    STB_MORTIS = 34,
    STB_HOME = 35,
    STB_BACKWARDS = 36,

    NUM_STB
};

enum eDimension {
    DIMENSION_CURRENT = -1,
    DIMENSION_NORMAL = 0,
    DIMENSION_KNIFE_PUZZLE = 1,
    DIMENSION_MIRROR = 1,
    DIMENSION_MINESHAFT = 1,
    DIMENSION_DEATH_CERTIFICATE = 2,
    NUM_DIMENSIONS = 3,
};

enum eGridRooms {
    NO_ROOM_IDX = -99999,
    ROOM_DEVIL_IDX = -1,
    ROOM_ERROR_IDX = -2,
    ROOM_DEBUG_IDX = -3,
    ROOM_DUNGEON_IDX = -4,
    ROOM_BOSSRUSH_IDX = -5,
    ROOM_BLACK_MARKET_IDX = -6,
    ROOM_MEGA_SATAN_IDX = -7,
    ROOM_BLUE_WOOM_IDX = -8,
    ROOM_THE_VOID_IDX = -9,
    ROOM_SECRET_EXIT_IDX = -10,
    ROOM_GIDEON_DUNGEON_IDX = -11,
    ROOM_GENESIS_IDX = -12,
    ROOM_SECRET_SHOP_IDX = -13,
    ROOM_ROTGUT_DUNGEON1_IDX = -14,
    ROOM_ROTGUT_DUNGEON2_IDX = -15,
    ROOM_BLUE_ROOM_IDX = -16,
    ROOM_EXTRA_BOSS_IDX = -17,
    ROOM_ANGEL_SHOP_IDX = -18,
    ROOM_DEATHMATCH_IDX = -19,
    ROOM_LIL_PORTAL_IDX = -20,

    ROOM_MIRROR_IDX = -100,
    ROOM_MINESHAFT_IDX = -101,

    NUM_OFF_GRID_ROOMS = 20,
    NUM_DIMENSION_GRID_ROOMS = 169,
    MAX_GRID_ROOMS = NUM_DIMENSION_GRID_ROOMS * NUM_DIMENSIONS,
    MAX_ROOMS = MAX_GRID_ROOMS + NUM_OFF_GRID_ROOMS
};

static DWORD GetBaseAddress()
{
        return (DWORD)GetModuleHandle(NULL);
}

enum BagOfCraftingPickup : uint8_t 
{
        BOC_NONE = 0,
        BOC_RED_HEART = 1,
        BOC_SOUL_HEART = 2,
        BOC_BLACK_HEART = 3,
        BOC_ETERNAL_HEART = 4,
        BOC_GOLD_HEART = 5,
        BOC_BONE_HEART = 6,
        BOC_ROTTEN_HEART = 7,
        BOC_PENNY = 8,
        BOC_NICKEL = 9,
        BOC_DIME = 10,
        BOC_LUCKY_PENNY = 11,
        BOC_KEY = 12,
        BOC_GOLD_KEY = 13,
        BOC_CHARGED_KEY = 14,
        BOC_BOMB = 15,
        BOC_GOLD_BOMB = 16,
        BOC_GIGA_BOMB = 17,
        BOC_MINI_BATTERY = 18,
        BOC_BATTERY = 19,
        BOC_MEGA_BATTERY = 20,
        BOC_CARD = 21,
        BOC_PILL = 22,
        BOC_RUNE = 23,
        BOC_DICE_SHARD = 24,
        BOC_CRACKED_KEY = 25,
        BOC_GOLD_PENNY = 26,
        BOC_GOLD_PILL = 27,
        BOC_GOLD_BATTERY = 28,
        BOC_POOP = 29,
        BOC_MAX = 30
};

enum RailType : uint8_t {
    RAIL_HORIZONTAL = 0,
    RAIL_VERTICAL = 1,
    RAIL_DOWN_TO_RIGHT = 2,
    RAIL_DOWN_TO_LEFT = 3,
    RAIL_UP_TO_RIGHT = 4,
    RAIL_UP_TO_LEFT = 5,
    RAIL_CROSSROAD = 6,
    RAIL_END_LEFT = 7,
    RAIL_END_RIGHT = 8,
    RAIL_END_UP = 9,
    RAIL_END_DOWN = 10,
    RAIL_HORIZONTAL_CART_LEFT = 16,
    RAIL_HORIZONTAL_CART_RIGHT = 32,
    RAIL_VERTICAL_CART_UP = 17,
    RAIL_VERTICAL_CART_DOWN = 33,
    RAIL_MINESHAFT_HORIZONTAL_1 = 80,
    RAIL_MINESHAFT_HORIZONTAL_2 = 96,
    RAIL_MINESHAFT_HORIZONTAL_3 = 112,
    RAIL_MINESHAFT_VERTICAL_1 = 81,
    RAIL_MINESHAFT_VERTICAL_2 = 97,
    RAIL_MINESHAFT_VERTICAL_3 = 113,
    RAIL_MINESHAFT_DOWN_TO_RIGHT_1 = 82,
    RAIL_MINESHAFT_DOWN_TO_RIGHT_2 = 98,
    RAIL_MINESHAFT_DOWN_TO_LEFT_1 = 83,
    RAIL_MINESHAFT_DOWN_TO_LEFT_2 = 99,
    RAIL_MINESHAFT_UP_TO_RIGHT_1 = 84,
    RAIL_MINESHAFT_UP_TO_RIGHT_2 = 100,
    RAIL_MINESHAFT_UP_TO_LEFT_1 = 85,
    RAIL_MINESHAFT_UP_TO_LEFT_2 = 101,
    RAIL_DOOR_LEFT = 144,
    RAIL_DOOR_BOTTOM = 145,
    RAIL_DOOR_RIGHT = 160,
    RAIL_DOOR_TOP = 161,
    RAIL_NONE = 255
};

enum ShaderType : uint8_t {
    SHADER_COLOR_OFFSET,
    SHADER_PIXELATION,
    SHADER_BLOOM,
    SHADER_COLOR_CORRECTION,
    SHADER_HQ4X,
    SHADER_SHOCKWAVE,
    SHADER_OLDTV,
    SHADER_WATER,
    SHADER_HALLUCINATION,
    SHADER_COLOR_MOD,
    SHADER_COLOR_OFFSET_CHAMPION,
    SHADER_WATER_V2,
    SHADER_BACKGROUND,
    SHADER_WATER_OVERLAY,
    SHADER_UNK,
    SHADER_COLOR_OFFSET_DOGMA,
    SHADER_COLOR_OFFSET_GOLD,
    SHADER_DIZZY,
    SHADER_HEAT_WAVE,
    SHADER_MIRROR,
    SHADER_MAX
};

enum eItemPoolType {
    POOL_NULL = -1,
    POOL_TREASURE = 0,
    POOL_SHOP = 1,
    POOL_BOSS = 2,
    POOL_DEVIL = 3,
    POOL_ANGEL = 4,
    POOL_SECRET = 5,
    POOL_LIBRARY = 6,
    POOL_SHELL_GAME = 7, // unused (for now)
    POOL_GOLDEN_CHEST = 8,
    POOL_RED_CHEST = 9,
    POOL_BEGGAR = 10,
    POOL_DEMON_BEGGAR = 11,
    POOL_CURSE = 12,
    POOL_KEY_MASTER = 13,
    POOL_BATTERY_BUM = 14,
    POOL_MOMS_CHEST = 15,
    POOL_GREED_TREASURE = 16,
    POOL_GREED_BOSS = 17,
    POOL_GREED_SHOP = 18,
    POOL_GREED_DEVIL = 19,
    POOL_GREED_ANGEL = 20,
    POOL_GREED_CURSE = 21,
    POOL_GREED_SECRET = 22,
    POOL_CRANE_GAME = 23,
    POOL_ULTRA_SECRET = 24,
    POOL_BOMB_BUM = 25,
    POOL_PLANETARIUM = 26,
    POOL_OLD_CHEST = 27,
    POOL_BABY_SHOP = 28,
    POOL_WOODEN_CHEST = 29,
    POOL_ROTTEN_BEGGAR = 30,
    NUM_ITEMPOOLS = 31
};

enum EntityFlag : UINT64 {
	FLAG_NO_STATUS_EFFECTS = 1,			// prevent freeze/poison/slow/charm/confusion/fear/burn
	FLAG_NO_INTERPOLATE = 1 << 1,			// do not interpolate position
	FLAG_APPEAR = 1 << 2,					// play appear animation after Init
	FLAG_RENDER_FLOOR = 1 << 3,				// will be rendered to floor texture
	FLAG_NO_TARGET = 1 << 4,					// will not be a target of NPCs or familiars
	FLAG_FREEZE = 1 << 5,					// freezing effect
	FLAG_POISON = 1 << 6,					// poison effect
	FLAG_SLOW = 1 << 7,						// slowing (velocity)
	FLAG_CHARM = 1 << 8,						// Charmed
	FLAG_CONFUSION = 1 << 9,					// Confused
	FLAG_MIDAS_FREEZE = 1 << 10,				// Midas frozen
	FLAG_FEAR = 1 << 11,						// Fleeing in Fear (like Mom's Pad)
	FLAG_BURN = 1 << 12,						// Caused by Fire Mind tears, works like poison except with Red color effect.
	FLAG_RENDER_WALL = 1 << 13,				// will be rendered to wall texture
	FLAG_INTERPOLATION_UPDATE = 1 << 14,		// entity is updating at 60 fps, and this is an odd frame
	FLAG_APPLY_GRAVITY = 1 << 15,			// In sidescrolling room, this indicates that we're in a gravity zone.
	FLAG_NO_BLOOD_SPLASH = 1 << 16,
	FLAG_NO_REMOVE_ON_TEX_RENDER = 1 << 17,	// for FLAG_RENDER_FLOOR and FLAG_RENDER_WALL
	FLAG_NO_DEATH_TRIGGER = 1 << 18,

	// NOTE: Those next flags share the same bit but have a different meaning depending on entity type
	FLAG_NO_SPIKE_DAMAGE = 1 << 19,			// EntityNPC: shouldn't take any damage from spikes
	FLAG_LASER_POP = 1 << 19,					// EntityTear: Pop tear fired by a laser, should decelerate very quickly for the first few frames
	FLAG_ITEM_SHOULD_DUPLICATE = 1 << 19,		// EntityPickup: item pedestal affected by Damocles, will be duplicated at the end of the current frame

	FLAG_BOSSDEATH_TRIGGERED = 1 << 20,
	FLAG_DONT_OVERWRITE = 1 << 21,			// Used in entityfactory to not remove this entity if there is no space left for new entity
	FLAG_SPAWN_STICKY_SPIDERS = 1 << 22,		// Used by Sticky bombs to generate spiders on death
	FLAG_SPAWN_BLACK_HP = 1 << 23,			// Used by black hp drop tear flag to drop a black hp on enemy death
	FLAG_SHRINK = 1 << 24,					// God's flesh effect
	FLAG_NO_FLASH_ON_DAMAGE = 1 << 25,		// Entity will not flash red when damaged
	FLAG_NO_KNOCKBACK = 1 << 26,				// Bombs and farts have no knockback effects
	FLAG_SLIPPERY_PHYSICS = 1 << 27,			// Standing on a slippery surface
	FLAG_ADD_JAR_FLY = 1 << 28,				// Adds a fly to the jar when killed
	FLAG_FRIENDLY = 1 << 29,					// Charmed and m_CharmCountdown<0
	FLAG_NO_PHYSICS_KNOCKBACK = 1 << 30,		// No knockback from general collisions
	FLAG_DONT_COUNT_BOSS_HP = 1 << 31,		// Do not count boss hp
	FLAG_NO_SPRITE_UPDATE = (UINT64)1 << 32,			// Do not update sprite animation
	FLAG_CONTAGIOUS = (UINT64)1 << 33,				// Used for Contagious item (if the enemy is infected)
	FLAG_BLEED_OUT = (UINT64)1 << 34,					// Used for Mom's Razor
	FLAG_HIDE_HP_BAR = (UINT64)1 << 35,				// Added for Ultra Greed so his HP can be hidden after he "dies" since his entity sticks around
	FLAG_NO_DAMAGE_BLINK = (UINT64)1 << 36,			// Player was given a short period of invulnerability by something other than damage, don't blink
	FLAG_PERSISTENT = (UINT64)1 << 37,				// Entity persists between rooms

	FLAG_BACKDROP_DETAIL = (UINT64)1 << 38,			// Was spawned as a backdrop decoration, should be deleted if the current backdrop changes (due to Delirium)
	FLAG_AMBUSH = (UINT64)1 << 39,					// Enemy was spawned by some sort of ambush (Greed Mode, challenge rooms), don't collide with the player for a few frames
	FLAG_GLITCH = (UINT64)1 << 40,					// Glitched out, has different effects depending on the entity
	FLAG_SPIN = (UINT64)1 << 41,						// Used by Spin to Win, causes a familiar to rapidly spin around its owner
	FLAG_NO_REWARD = (UINT64)1 << 42,					// Doesn't spawn any kind of reward on death
	FLAG_REDUCE_GIBS = (UINT64)1 << 43,				// Spawn less gibs on death
	FLAG_TRANSITION_UPDATE = (UINT64)1 << 44,			// Updates during room/stage transitions
	FLAG_NO_PLAYER_CONTROL = (UINT64)1 << 45,			// Cannot be controlled by players
	FLAG_NO_QUERY = (UINT64)1 << 46,					// Hide from query results
	FLAG_KNOCKED_BACK = (UINT64)1 << 47,				// Strong knockback: Forcefy moved in a specified direction for a short duration
	FLAG_APPLY_IMPACT_DAMAGE = (UINT64)1 << 48,		// Inflicts damage upon colliding with enemies, takes damage when colliding with walls
	FLAG_ICE_FROZEN = (UINT64)1 << 49,				// Frozen solid
	FLAG_ICE = (UINT64)1 << 50,						// Flagged to become frozen on death
	FLAG_MAGNETIZED = (UINT64)1 << 51,				// Magnetized: Attracts nearby enemies, projectiles and pickups
	FLAG_BAITED = (UINT64)1 << 52,					// Baited: Is targeted by nearby enemies
	FLAG_KILLSWITCH = (UINT64)1 << 53,				// Killed by a killswitch
	FLAG_WEAKNESS = (UINT64)1 << 54,					// Weakness effect from Reverse Strength
	FLAG_EXTRA_GORE = (UINT64)1 << 55,				// Spawns more gibs on death
	FLAG_BRIMSTONE_MARKED = (UINT64)1 << 56,			// Marked by Azazel B, takes extra damage from Brimstone attacks
	FLAG_HELD = (UINT64)1 << 57,						// Picked up by a player
	FLAG_THROWN = (UINT64)1 << 58,					// Thrown by a player
	FLAG_FRIENDLY_BALL = (UINT64)1 << 59,				// Used to detect enemies spawned by Friendly Ball

	FLAG_STATUS_EFFECTS = (UINT64)(FLAG_FREEZE + FLAG_POISON + FLAG_SLOW + FLAG_CHARM + FLAG_CONFUSION + FLAG_MIDAS_FREEZE + FLAG_FEAR + FLAG_BURN + FLAG_SHRINK + FLAG_FRIENDLY + FLAG_BLEED_OUT + FLAG_ICE_FROZEN + FLAG_ICE + FLAG_MAGNETIZED + FLAG_BAITED + FLAG_WEAKNESS + FLAG_BRIMSTONE_MARKED),
	FLAG_NON_STATUS_EFFECTS = (((UINT64)1 << 60) - 1) - FLAG_STATUS_EFFECTS,
};

enum eBossId {
    BOSS_NULL = 0,
    BOSS_MONSTRO = 1,
    BOSS_LARRY_JR = 2,
    BOSS_CHUB = 3,
    BOSS_GURDY = 4,
    BOSS_MONSTRO_II = 5,
    BOSS_MOM = 6,
    BOSS_SCOLEX = 7,
    BOSS_MOMS_HEART = 8,
    BOSS_FAMINE = 9,
    BOSS_PESTILENCE = 10,
    BOSS_WAR = 11,
    BOSS_DEATH = 12,
    BOSS_DUKE_OF_FLIES = 13,
    BOSS_PEEP = 14,
    BOSS_LOKI = 15,
    BOSS_BLASTOCYST = 16,
    BOSS_GEMINI = 17,
    BOSS_FISTULA = 18,
    BOSS_GISH = 19,
    BOSS_STEVEN = 20,
    BOSS_CHAD = 21,
    BOSS_HEADLESS_HORSEMAN = 22,
    BOSS_FALLEN = 23,
    BOSS_SATAN = 24,
    BOSS_IT_LIVES = 25,
    BOSS_HOLLOW = 26,
    BOSS_CARRION_QUEEN = 27,
    BOSS_GURDY_JR = 28,
    BOSS_HUSK = 29,
    BOSS_BLOAT = 30,
    BOSS_LOKII = 31,
    BOSS_BLIGHTED_OVUM = 32,
    BOSS_TERATOMA = 33,
    BOSS_WIDOW = 34,
    BOSS_MASK_OF_INFAMY = 35,
    BOSS_WRETCHED = 36,
    BOSS_PIN = 37,
    BOSS_CONQUEST = 38,
    BOSS_ISAAC = 39,
    BOSS_BLUE_BABY = 40,
    BOSS_DADDY_LONG_LEGS = 41,
    BOSS_TRIACHNID = 42,
    BOSS_HAUNT = 43,
    BOSS_DINGLE = 44,
    BOSS_MEGA_MAW = 45,
    BOSS_GATE = 46,
    BOSS_MEGA_FATTY = 47,
    BOSS_CAGE = 48,
    BOSS_MEGA_GURDY = 49,
    BOSS_DARK_ONE = 50,
    BOSS_ADVERSARY = 51,
    BOSS_POLYCEPHALUS = 52,
    BOSS_MR_FRED = 53,
    BOSS_LAMB = 54,
    BOSS_MEGA_SATAN = 55,
    BOSS_GURGLINGS = 56,
    BOSS_STAIN = 57,
    BOSS_BROWNIE = 58,
    BOSS_FORSAKEN = 59,
    BOSS_LITTLE_HORN = 60,
    BOSS_RAG_MAN = 61,
    BOSS_ULTRA_GREED = 62,
    BOSS_HUSH = 63,
    BOSS_DANGLE = 64,
    BOSS_TURDLINGS = 65,
    BOSS_FRAIL = 66,
    BOSS_RAG_MEGA = 67,
    BOSS_SISTERS_VIS = 68,
    BOSS_BIG_HORN = 69,
    BOSS_DELIRIUM = 70,
    BOSS_ULTRA_GREEDIER = 71,
    BOSS_MATRIARCH = 72,
    BOSS_PILE = 73,
    BOSS_REAP_CREEP = 74,
    BOSS_BEELZEBLUB = 75,
    BOSS_WORMWOOD = 76,
    BOSS_RAINMAKER = 77,
    BOSS_VISAGE = 78,
    BOSS_SIREN = 79,
    BOSS_TUFF_TWINS = 80,
    BOSS_HERETIC = 81,
    BOSS_HORNFEL = 82,
    BOSS_GREAT_GIDEON = 83,
    BOSS_BABY_PLUM = 84,
    BOSS_SCOURGE = 85,
    BOSS_CHIMERA = 86,
    BOSS_ROTGUT = 87,
    BOSS_MOTHER = 88,
    BOSS_MOM_MAUSOLEUM = 89,
    BOSS_MOMS_HEART_MAUSOLEUM = 90,
    BOSS_MIN_MIN = 91,
    BOSS_CLOG = 92,
    BOSS_SINGE = 93,
    BOSS_BUMBINO = 94,
    BOSS_COLOSTOMIA = 95,
    BOSS_SHELL = 96,
    BOSS_TURDLET = 97,
    BOSS_RAGLICH = 98,
    BOSS_DOGMA = 99,
    BOSS_BEAST = 100,
    BOSS_HORNY_BOYS = 101,
    BOSS_CLUTCH = 102,
    BOSS_CADAVRA = 103,

    NUM_BOSSES,
};

enum eMainMenuType {
    TITLE = 1, // 0 exists but it's unusable
    SAVES = 2,
    GAME = 3, // the actual menu where all the menus are
    DAILYRUN = 4,
    CHARACTER = 5,
    SPECIALSEEDS = 6,
    CHALLENGE = 7,
    COLLECTION = 8,
    STATS = 9,
    OPTIONS = 10,
    CONTROLS = 11,
    KEYCONFIG = 12,
    ENDINGS = 13,
    BESTIARY = 14,
    MODCHALLENGES = 15,
    MODS = 16,
    ONLINELOBBY = 17,
	FRIENDLOBBIES = 18,
	MULTIPLAYER = 19,
	OPTIONSONLINE = 20,
	CREATELOBBY = 21,
	ONLINEAWARDS = 22 //sins list
};

enum eChallenge {
    CHALLENGE_NULL = 0,
    CHALLENGE_PITCH_BLACK = 1,
    CHALLENGE_HIGH_BROW = 2,
    CHALLENGE_HEAD_TRAUMA = 3,
    CHALLENGE_DARKNESS_FALLS = 4,
    CHALLENGE_THE_TANK = 5,
    CHALLENGE_SOLAR_SYSTEM = 6,
    CHALLENGE_SUICIDE_KING = 7,
    CHALLENGE_CAT_GOT_YOUR_TONGUE = 8,
    CHALLENGE_DEMO_MAN = 9,
    CHALLENGE_CURSED = 10,
    CHALLENGE_GLASS_CANNON = 11,
    CHALLENGE_WHEN_LIFE_GIVES_LEMONS = 12,
    CHALLENGE_BEANS = 13,
    CHALLENGE_ITS_IN_THE_CARDS = 14,
    CHALLENGE_SLOW_ROLL = 15,
    CHALLENGE_COMPUTER_SAVY = 16,
    CHALLENGE_WAKA_WAKA = 17,
    CHALLENGE_THE_HOST = 18,
    CHALLENGE_THE_FAMILY_MAN = 19,
    CHALLENGE_PURIST = 20,
    CHALLENGE_XXXXXXXXL = 21,
    CHALLENGE_SPEED = 22,
    CHALLENGE_BLUE_BOMBER = 23,
    CHALLENGE_PAY_TO_PLAY = 24,
    CHALLENGE_HAVE_A_HEART = 25,
    CHALLENGE_I_RULE = 26,
    CHALLENGE_BRAINS = 27,
    CHALLENGE_PRIDE_DAY = 28,
    CHALLENGE_ONANS_STREAK = 29,
    CHALLENGE_GUARDIAN = 30,
    CHALLENGE_BACKASSWARDS = 31,
    CHALLENGE_APRILS_FOOL = 32,
    CHALLENGE_POKEY_MANS = 33,
    CHALLENGE_ULTRA_HARD = 34,
    CHALLENGE_PONG = 35,
    CHALLENGE_SCAT_MAN = 36,
    CHALLENGE_BLOODY_MARY = 37,
    CHALLENGE_BAPTISM_BY_FIRE = 38,
    CHALLENGE_ISAACS_AWAKENING = 39,
    CHALLENGE_SEEING_DOUBLE = 40,
    CHALLENGE_PICA_RUN = 41,
    CHALLENGE_HOT_POTATO = 42,
    CHALLENGE_CANTRIPPED = 43,
    CHALLENGE_RED_REDEMPTION = 44,
    CHALLENGE_DELETE_THIS = 45,
    NUM_CHALLENGES = 46,
};

enum eSeedEffect {
    SEED_NORMAL = 0,
    SEED_MOVEMENT_PITCH = 1,
    SEED_HEALTH_PITCH = 2,
    SEED_CAMO_ISAAC = 3,
    SEED_CAMO_ENEMIES = 4,
    SEED_CAMO_PICKUPS = 5,
    SEED_CAMO_EVERYTHING = 6,
    SEED_FART_SOUNDS = 7,
    SEED_OLD_TV = 8,
    SEED_DYSLEXIA = 9,
    SEED_NO_HUD = 10,
    SEED_PICKUPS_SLIDE = 11,
    SEED_CONTROLS_REVERSED = 12,
    SEED_ALL_CHAMPIONS = 13,
    SEED_INVISIBLE_ISAAC = 14,
    SEED_INVISIBLE_ENEMIES = 15,
    SEED_INFINITE_BASEMENT = 16,
    SEED_ALWAYS_CHARMED = 17,
    SEED_ALWAYS_CONFUSED = 18,
    SEED_ALWAYS_AFRAID = 19,
    SEED_ALWAYS_ALTERNATING_FEAR = 20,
    SEED_ALWAYS_CHARMED_AND_AFRAID = 21,
    SEED_EXTRA_BLOOD = 23,
    SEED_POOP_TRAIL = 24,
    SEED_PACIFIST = 25,
    SEED_DAMAGE_WHEN_STOPPED = 26,
    SEED_DAMAGE_ON_INTERVAL = 27,
    SEED_DAMAGE_ON_TIME_LIMIT = 28,
    SEED_PILLS_NEVER_IDENTIFY = 29,
    SEED_MYSTERY_TAROT_CARDS = 30,
    SEED_ENEMIES_RESPAWN = 32,
    SEED_ITEMS_COST_MONEY = 33,
    SEED_BIG_HEAD = 35,
    SEED_SMALL_HEAD = 36,
    SEED_BLACK_ISAAC = 37,
    SEED_GLOWING_TEARS = 38,
    SEED_SLOW_MUSIC = 41,
    SEED_ULTRA_SLOW_MUSIC = 42,
    SEED_FAST_MUSIC = 43,
    SEED_ULTRA_FAST_MUSIC = 44,
    SEED_NO_FACE = 46,
    SEED_ISAAC_TAKES_HIGH_DAMAGE = 47,
    SEED_ISAAC_TAKES_MASSIVE_DAMAGE = 48,
    SEED_ICE_PHYSICS = 52,
    SEED_KAPPA = 53,
    SEED_CHRISTMAS = 54,
    SEED_KIDS_MODE = 55,
    SEED_PERMANENT_CURSE_DARKNESS = 56,
    SEED_PERMANENT_CURSE_LABYRINTH = 57,
    SEED_PERMANENT_CURSE_LOST = 58,
    SEED_PERMANENT_CURSE_UNKNOWN = 59,
    SEED_PERMANENT_CURSE_MAZE = 60,
    SEED_PERMANENT_CURSE_BLIND = 61,
    SEED_PERMANENT_CURSE_CURSED = 62,
    SEED_PREVENT_CURSE_DARKNESS = 63,
    SEED_PREVENT_CURSE_LABYRINTH = 64,
    SEED_PREVENT_CURSE_LOST = 65,
    SEED_PREVENT_CURSE_UNKNOWN = 66,
    SEED_PREVENT_CURSE_MAZE = 67,
    SEED_PREVENT_CURSE_BLIND = 68,
    SEED_PREVENT_ALL_CURSES = 70,
    SEED_NO_BOSS_ROOM_EXITS = 71,
    SEED_PICKUPS_TIMEOUT = 72,
    SEED_INVINCIBLE = 73,
    SEED_SHOOT_IN_MOVEMENT_DIRECTION = 74,
    SEED_SHOOT_OPPOSITE_MOVEMENT_DIRECTION = 75,
    SEED_AXIS_ALIGNED_CONTROLS = 76,
    SEED_SUPER_HOT = 77,
    SEED_RETRO_VISION = 78,
    SEED_G_FUEL = 79,
	
    NUM_SEEDS
};

enum SuplexState {
	INACTIVE = 0,	
	DASHING = 1,
	AIMING = 2,
	ASCENDING = 3,	
	DESCENDING = 4
};

enum CacheFlag {
	CACHE_DAMAGE = 0x1,
	CACHE_FIREDELAY = 0x2,
	CACHE_SHOTSPEED = 0x4,
	CACHE_RANGE = 0x8,
	CACHE_SPEED = 0x10,
	CACHE_TEARFLAG = 0x20,
	CACHE_TEARCOLOR = 0x40,
	CACHE_FLYING = 0x80,
	CACHE_WEAPON = 0x100,
	CACHE_FAMILIARS = 0x200,
	CACHE_LUCK = 0x400,
	CACHE_SIZE = 0x800,
	CACHE_COLOR = 0x1000,
	CACHE_PICKUP_VISION = 0x2000,
	CACHE_ALL = 0xFFFF,
	CACHE_TWIN_SYNC = 0x80000000,
};

enum ePickupVariant {
	PICKUP_NULL = 0,
	PICKUP_HEART = 10,
	PICKUP_COIN = 20,
	PICKUP_KEY = 30,
	PICKUP_BOMB = 40,
	PICKUP_THROWABLEBOMB = 41,
	PICKUP_POOP = 42,
	PICKUP_CHEST = 50,
	PICKUP_BOMBCHEST = 51,
	PICKUP_SPIKEDCHEST = 52,
	PICKUP_ETERNALCHEST = 53,
	PICKUP_MIMICCHEST = 54,
	PICKUP_OLDCHEST = 55,
	PICKUP_WOODENCHEST = 56,
	PICKUP_MEGACHEST = 57,
	PICKUP_HAUNTEDCHEST = 58,
	PICKUP_LOCKEDCHEST = 60,
	PICKUP_GRAB_BAG = 69,
	PICKUP_PILL = 70,
	PICKUP_LIL_BATTERY = 90,
	PICKUP_COLLECTIBLE = 100,
	PICKUP_BROKEN_SHOVEL = 110,
	PICKUP_SHOPITEM = 150,
	PICKUP_TAROTCARD = 300,
	PICKUP_BIGCHEST = 340,
	PICKUP_TRINKET = 350,
	PICKUP_REDCHEST = 360,
	PICKUP_TROPHY = 370,
	PICKUP_BED = 380,
	PICKUP_MOMSCHEST = 390,
};

enum eDamageFlag : UINT64 {
	DAMAGE_NOKILL = 1,
	DAMAGE_FIRE = 1<<1,
	DAMAGE_EXPLOSION = 1<<2,
	DAMAGE_LASER = 1<<3,
	DAMAGE_ACID = 1<<4,
	DAMAGE_RED_HEARTS = 1<<5,
	DAMAGE_COUNTDOWN = 1<<6,
	DAMAGE_SPIKES = 1<<7,
	DAMAGE_CLONES = 1<<8,
	DAMAGE_POOP = 1<<9,
	DAMAGE_DEVIL = 1<<10,
	DAMAGE_ISSAC_HEART = 1<<11,
	DAMAGE_TNT = 1<<12,
	DAMAGE_INVINCIBLE = 1<<13,
	DAMAGE_SPAWN_FLY = 1<<14,
	DAMAGE_POISON_BURN = 1<<15,
	DAMAGE_CURSED_DOOR = 1<<16,
	DAMAGE_TIMER = 1<<17,
	DAMAGE_IV_BAG = 1<<18,
	DAMAGE_PITFALL = 1<<19,
	DAMAGE_CHEST = 1<<20,
	DAMAGE_FAKE = 1<<21,
	DAMAGE_BOOGER = 1<<22,
	DAMAGE_SPAWN_BLACK_HEART = 1<<23,
	DAMAGE_CRUSH = 1<<24,
	DAMAGE_NO_MODIFIERS = 1<<25,
	DAMAGE_SPAWN_RED_HEART = 1<<26,
	DAMAGE_SPAWN_COIN = 1<<27,
	DAMAGE_NO_PENALTIES = 1<<28,
	DAMAGE_SPAWN_TEMP_HEART = 1<<29,
	DAMAGE_IGNORE_ARMOR = 1<<30,
	DAMAGE_SPAWN_CARD = 1<<31,
	DAMAGE_SPAWN_RUNE = (UINT64)1<<32,
};

enum class eAchievement : int {
	MAGDALENE = 1,
	CAIN = 2,
	JUDAS = 3,
	THE_WOMB = 4, WOMB = 4,
	THE_HARBINGERS = 5, HARBINGERS = 5, HORSEMEN = 5,
	A_CUBE_OF_MEAT = 6, CUBE_OF_MEAT = 6,
	THE_BOOK_OF_REVELATIONS = 7, BOOK_OF_REVELATIONS = 7,
	A_NOOSE = 8, TRANSENDENCE = 8,
	THE_NAIL = 9, NAIL = 9,
	A_QUARTER = 10, QUARTER = 10,
	A_FETUS_IN_A_JAR = 11, DR_FETUS = 11,
	A_SMALL_ROCK = 12, SMALL_ROCK = 12,
	MONSTROS_LUNG = 13,
	LIL_CHUBBY = 14,
	LOKIS_HORNS = 15,
	SOMETHING_FROM_THE_FUTURE = 16, STEVEN = 16,
	SOMETHING_CUTE = 17, CHAD = 17,
	SOMETHING_STICKY = 18, GISH = 18,
	A_BANDAGE = 19, SUPER_BANDAGE = 19,
	A_CROSS = 20, THE_RELIC = 20, RELIC = 20,
	A_BAG_OF_PENNIES = 21, BAG_OF_PENNIES = 21,
	THE_BOOK_OF_SIN = 22, BOOK_OF_SIN = 23,
	LITTLE_GISH = 23,
	LITTLE_STEVEN = 24,
	LITTLE_CHAD = 25,
	A_GAMEKID = 26, GAMEKID = 26,
	A_HALO = 27, HALO = 27,
	MR_MEGA = 28,
	ISAAC_HOLDS_THE_D6 = 29,
	THE_SCISSORS = 30, SCISSORS = 30,
	THE_PARASITE = 31, PARASITE = 31,
	BLUE_BABY = 32, QQQ = 32,
	EVERYTHING_IS_TERRIBLE = 33,
	IT_LIVES = 34,
	MOMS_CONTACT = 35,
	THE_NECRONOMICON = 36, NECRONOMICON = 36,
	BASEMENT_BOY = 37,
	SPELUNKER_BOY = 38,
	DARK_BOY = 39,
	MAMAS_BOY = 40,
	GOLDEN_GOD = 41,
	EVE = 42,
	MOMS_KNIFE = 43,
	THE_RAZOR = 44, RAZOR = 44,
	GUARDIAN_ANGEL = 45,
	A_BAG_OF_BOMBS = 46, BAG_OF_BOMBS = 46,
	A_DEMON_BABY = 47, DEMON_BABY = 47,
	A_FORGET_ME_NOW = 48, FORGET_ME_NOW = 48,
	THE_D20 = 49, D20 = 49,
	THE_CRUCIFIX = 50, CELTIC_CROSS = 50,
	ABEL = 51,
	CURVED_HORN = 52,
	SACRIFICIAL_DAGGER = 53,
	BLOOD_LUST = 54, BLOODY_LUST = 54,
	BLOOD_PENNY = 55, BLOODY_PENNY = 55,
	BLOOD_RIGHTS = 56,
	THE_POLAROID = 57, POLAROID = 57,
	DADS_KEY = 58,
	THE_BLUE_CANDLE = 59, BLUE_CANDLE = 59,
	BURNT_PENNY = 60,
	LUCKY_TOE = 61,
	EPIC_FETUS = 62,
	SMB_SUPER_FAN = 63,
	COUNTERFEIT_COIN = 64, COUNTERFEIT_PENNY = 64,
	GUPPYS_HAIRBALL = 65,
	A_FORGOTTEN_HORSEMAN = 66, CONQUEST = 66,
	SAMSON = 67,
	SOMETHING_ICKY = 68, TRIACHNID = 68,
	PLATINUM_GOD = 69,
	ISAACS_HEAD = 70,
	MAGGYS_FAITH = 71,
	JUDAS_TONGUE = 72,
	BLUE_BABYS_SOUL = 73, QQQS_SOUL = 73,
	SAMSONS_LOCK = 74,
	CAINS_EYE = 75,
	EVES_BIRD_FOOT = 76,
	THE_LEFT_HAND = 77, LEFT_HAND = 77,
	THE_NEGATIVE = 78, NEGATIVE = 78,
	DEMON_ISAAC = 79, AZAZEL = 79,
	LAZARUS = 80,
	EDEN = 81,
	THE_SOUL = 82, THE_LOST = 82, LOST = 82,
	DEAD_BOY = 83,
	THE_REAL_PLATINUM_GOD = 84, REAL_PLATINUM_GOD = 84,
	LUCKY_ROCK = 85,
	THE_CELLAR = 86, CELLAR = 86,
	THE_CATACOMBS = 87, CATACOMBS = 87,
	THE_NECROPOLIS = 88, NECROPOLIS = 88,
	RUNE_OF_HAGALAZ = 89, HAGALAZ = 89,
	RUNE_OF_JERA = 90, JERA = 90,
	RUNE_OF_EHWAZ = 91, EHWAZ = 91,
	RUNE_OF_DAGAZ = 92, DAGAZ = 92,
	RUNE_OF_ANSUZ = 93, ANSUZ = 93,
	RUNE_OF_PERTHRO = 94, PERTHRO = 94,
	RUNE_OF_BERKANO = 95, BERKANO = 95,
	RUNE_OF_ALGIZ = 96, ALGIZ = 96,
	CHAOS_CARD = 97,
	CREDIT_CARD = 98,
	RULES_CARD = 99,
	CARD_AGAINST_HUMANITY = 100,
	SWALLOWED_PENNY = 101,
	ROBO_BABY_2 = 102,
	DEATHS_TOUCH = 103,
	TECHNOLOGY_5 = 104,
	MISSING_NO = 105,
	ISAACS_TEARS = 106,
	GUILLOTINE = 107,
	JUDAS_SHADOW = 108,
	MAGGYS_BOW = 109,
	CAINS_OTHER_EYE = 110,
	BLACK_LIPSTICK = 111,
	EVES_MASCARA = 112,
	FATE = 113,
	BLUE_BABYS_ONLY_FRIEND = 114, QQQS_ONLY_FRIEND = 114,
	SAMSONS_CHAINS = 115,
	LAZARUS_RAGS = 116,
	BROKEN_ANKH = 117,
	STORE_CREDIT = 118,
	PANDORAS_BOX = 119,
	SUICIDE_KING = 120,
	BLANK_CARD = 121,
	BOOK_OF_SECRETS = 122,
	MYSTERIOUS_PAPER = 123,
	MYSTERY_SACK = 124,
	UNDEFINED = 125,
	SATANIC_BIBLE = 126,
	DAEMONS_TAIL = 127,
	ABADDON = 128,
	ISAACS_HEART = 129,
	THE_MIND_ITEM = 130, MIND = 130,
	THE_BODY_ITEM = 131, BODY = 131,
	THE_SOUL_ITEM = 132, SOUL = 132,
	A_D100 = 133, D100 = 133,
	BLUE_MAP = 134,
	THERES_OPTIONS = 135,
	BLACK_CANDLE = 136,
	RED_CANDLE = 137,
	STOP_WATCH = 138,
	WIRE_COAT_HANGER = 139,
	IPECAC = 140,
	EXPERIMENTAL_TREATMENT = 141,
	KRAMPUS_UNLOCKED = 142, KRAMPUS = 142,
	HEAD_OF_KRAMPUS = 143,
	SUPER_MEAT_BOY = 144,
	BUTTER_BEAN = 145,
	LITTLE_BAGGY = 146,
	BLOOD_BAG = 147,
	A_D4 = 148, D4 = 148,
	THE_LOST_POSTER = 149, LOST_POSTER = 149, MISSING_POSTER = 149,
	RUBBER_CEMENT = 150,
	STORE_UPGRADE_LV1 = 151,
	STORE_UPGRADE_LV2 = 152,
	STORE_UPGRADE_LV3 = 153,
	STORE_UPGRADE_LV4 = 154,
	UNLOCKED_ANGEL_BOSSES = 155, ANGELS = 155,
	GODHEAD = 156,
	CHALLENGE_4_DARKNESS_FALLS = 157, DARKNESS_FALLS = 157,
	CHALLENGE_5_THE_TANK = 158, THE_TANK = 158,
	CHALLENGE_6_SOLAR_SYSTEM = 159, SOLAR_SYSTEM = 159,
	CHALLENGE_7_SUICIDE_KING = 160, SUICIDE_KING_CHALLENGE = 160,
	CHALLENGE_8_CAT_GOT_YOUR_TONGUE = 161, CAT_GOT_YOUR_TONGUE = 161,
	CHALLENGE_9_DEMO_MAN = 162, DEMO_MAN = 162,
	CHALLENGE_10_CURSED = 163, CURSED = 163,
	CHALLENGE_11_GLASS_CANNON = 164, GLASS_CANNON = 164,
	CHALLENGE_19_THE_FAMILY_MAN = 165, THE_FAMILY_MAN = 165, FAMILY_MAN = 165,
	CHALLENGE_20_PURIST = 166, PURIST = 166,
	LOST_BABY = 167,
	CUTE_BABY = 168,
	CROW_BABY = 169,
	SHADOW_BABY = 170,
	GLASS_BABY = 171,
	WRAPPED_BABY = 172,
	BEGOTTEN_BABY = 173,
	DEAD_BABY = 174,
	O_BABY = 175, ZERO_BABY = 175,
	GLITCH_BABY = 176,
	FIGHTING_BABY = 177,
	BECAME_LORD_OF_THE_FLIES = 178,
	FART_BABY = 179, FARTING_BABY = 179,
	PURITY = 180,
	D12 = 181,
	BETRAYAL = 182,
	FATES_REWARD = 183,
	ATHAME = 184,
	BLIND_RAGE = 185,
	MAW_OF_THE_VOID = 186,
	EMPTY_VESSEL = 187,
	EDENS_BLESSING = 188,
	SWORN_PROTECTOR = 189,
	INCUBUS = 190,
	KEEPER_HOLDS_A_PENNY = 191,
	LIL_CHEST = 192,
	CENSER = 193,
	EVIL_EYE = 194,
	MY_SHADOW = 195,
	CRACKED_DICE = 196,
	BLACK_FEATHER = 197,
	LUSTY_BLOOD = 198,
	LILITH = 199,
	KEY_BUM = 200,
	GB_BUG = 201,
	ZODIAC = 202,
	BOX_OF_FRIENDS = 203,
	RIB_OF_GREED = 204,
	CRY_BABY = 205,
	RED_BABY = 206,
	GREEN_BABY = 207,
	BROWN_BABY = 208,
	BLUE_COOP_BABY= 209,
	LIL_BABY = 210,
	RAGE_BABY = 211,
	BLACK_BABY = 212,
	LONG_BABY = 213,
	YELLOW_BABY = 214,
	WHITE_BABY = 215,
	BIG_BABY = 216,
	NOOSE_BABY = 217,
	RUNE_BAG = 218,
	CAMBION_CONCEPTION = 219,
	SERPENTS_KISS = 220,
	SUCCUBUS = 221,
	IMMACULATE_CONCEPTION = 222,
	GOAT_HEAD_BABY = 223,
	GOLD_HEART = 224, GOLDEN_HEARTS = 224,
	GET_OUT_OF_JAIL_FREE_CARD = 225, GET_OUT_OF_JAIL_FREE = 225,
	GOLD_BOMB = 226, GOLDEN_BOMBS = 226,
	TWO_NEW_PILLS = 227,
	TWO_NEW_PILLS_2 = 228,
	POKER_CHIP = 229,
	STUD_FINDER = 230,
	D8 = 231,
	KIDNEY_STONE = 232,
	BLANK_RUNE = 233,
	BLUE_WOMB = 234,
	ONE_THOUSAND_AND_ONE_PERCENT = 235, NERD_1_MILLION = 235,
	KEEPER_HOLDS_WOODEN_NICKEL = 236,
	KEEPER_HOLDS_STORE_KEY = 237,
	DEEP_POCKETS = 238,
	KARMA = 239,
	STICKY_NICKELS = 240,
	SUPER_GREED_BABY = 241,
	LUCKY_PENNIES = 242,
	SPECIAL_HANGING_SHOPKEEPERS = 243,
	WOODEN_NICKEL = 244,
	CAIN_HOLDS_PAPERCLIP = 245,
	EVERYTHING_IS_TERRIBLE_2 = 246,
	SPECIAL_SHOPKEEPERS = 247,
	EVE_HOLDS_RAZOR_BLADE = 248,
	STORE_KEY = 249,
	THE_LOST_HOLDS_HOLY_MANTLE = 250, LOST_HOLDS_HOLY_MANTLE = 250,
	KEEPER = 251,
	HIVE_BABY = 252,
	BUDDY_BABY = 253,
	COLORFUL_BABY = 254,
	WHORE_BABY = 255,
	CRACKED_BABY = 256,
	DRIPPING_BABY = 257,
	BLINDING_BABY = 258,
	SUCKY_BABY = 259,
	DARK_BABY = 260,
	PICKY_BABY = 261,
	REVENGE_BABY = 262,
	BELIAL_BABY = 263,
	SALE_BABY = 264,
	CHALLENGE_21_XXXXXXXXL = 265, XXXXXXXXL = 265,
	CHALLENGE_22_SPEED = 266, SPEED = 266,
	CHALLENGE_23_BLUE_BOMBER = 267, BLUE_BOMBER = 267,
	CHALLENGE_24_PAY_TO_PLAY = 268, PAY_TO_PLAY = 268,
	CHALLENGE_25_HAVE_A_HEART = 269, HAVE_A_HEART = 269,
	CHALLENGE_26_I_RULE = 270, I_RULE = 270,
	CHALLENGE_27_BRAINS = 271, BRAINS = 271,
	CHALLENGE_28_PRIDE_DAY = 272, PRIDE_DAY = 272,
	CHALLENGE_29_ONANS_STREAK = 273, ONANS_STREAK = 273,
	CHALLENGE_30_THE_GUARDIAN = 274, THE_GUARDIAN = 274,
	GENEROSITY = 275,
	MEGA_BLAST = 276,
	CHALLENGE_31_BACKASSWARDS = 277, BACKASSWARDS = 277,
	CHALLENGE_32_APRILS_FOOL = 278, APRILS_FOOL = 278,
	CHALLENGE_33_POKEY_MANS = 279, POKEY_MANS = 279,
	CHALLENGE_34_ULTRA_HARD = 280, ULTRA_HARD = 280,
	CHALLENGE_35_PONG = 281, PONG = 281,
	D_INFINITY = 282,
	EUCHARIST = 283,
	SILVER_DOLLAR = 284,
	SHADE = 285,
	KING_BABY = 286,
	BLOODY_CROWN = 287,
	DULL_RAZOR = 288,
	EDENS_SOUL = 289,
	DARK_PRINCES_CROWN = 290,
	COMPOUND_FRACTURE = 291,
	EUTHANASIA = 292,
	HOLY_CARD = 293,
	CROOKED_PENNY = 294,
	VOID_ITEM = 295,
	D1 = 296,
	GLYPH_OF_BALANCE = 297,
	SACK_OF_SACKS = 298,
	EYE_OF_BELIAL = 299,
	MECONIUM = 300,
	STEM_CELL = 301,
	CROW_HEART = 302,
	METRONOME = 303,
	BAT_WING = 304,
	PLAN_C = 305,
	DUALITY = 306,
	DADS_LOST_COIN = 307,
	EYE_OF_GREED = 308,
	BLACK_RUNE = 309,
	LOCUST_OF_WRATH = 310,
	LOCUST_OF_PESTILENCE = 311,
	LOCUST_OF_FAMINE = 312,
	LOCUST_OF_DEATH = 313,
	LOCUST_OF_CONQUEST = 314,
	HUSHY = 315,
	BROWN_NUGGET = 316,
	MORT_BABY = 317,
	SMELTER = 318,
	APOLLYON_BABY = 319,
	UNLOCKED_A_NEW_AREA = 320, THE_VOID = 320, VOID_FLOOR = 320,
	ONCE_MORE_WITH_FEELING = 321, GULP_PILL = 321,
	HAT_TRICK = 322, ACE_OF_CLUBS = 322,
	FIVE_NIGHTS_AT_MOMS = 323, SUPER_SPECIAL_ROCKS = 323,
	SIN_COLLECTOR = 324, FEELS_LIKE_IM_WALKING_ON_SUNSHINE = 324, SUNSHINE_PILL = 324,
	DEDICATION = 325, HORF = 325,
	ZIP = 326, ACE_OF_DIAMONDS = 326,
	ITS_THE_KEY = 327, ACE_OF_SPADES = 327,
	MR_RESETTER = 328, SCARED_HEART = 328,
	LIVING_ON_THE_EDGE = 329, ACE_OF_HEARTS = 329,
	U_BROKE_IT = 330, VURP = 330,
	LAZARUS_BLEEDS_MORE = 331, LAZARUS_HOLDS_ANEMIA = 331,
	MAGGY_HOLDS_A_PILL = 332, MAGDALENE_HOLDS_A_PILL = 332,
	CHARGED_KEY = 333,
	SAMMSON_FEELS_HEALTHY = 334, SAMSON_HOLDS_CHILDS_HEART = 334,
	GREEDS_GULLET = 335,
	CRACKED_CROWN = 336,
	UNLOCKED_RERUNS = 337, RERUNS = 337,
	DELIRIOUS = 338,
	ONE_MILLION_PERCENT_JUST_STOP = 339, ONE_MILLION_PERCENT = 339, JUST_STOP = 339,
	THE_DESTROYER = 340, APOLLYON = 340,
	GREEDIER = 341,
	BURNING_BASEMENT = 342,
	FLOODED_CAVES = 343,
	DANK_DEPTHS = 344,
	SCARRED_WOMB = 345,
	SOMETHING_WICKED = 346,
	SOMETHING_WICKED_PLUS = 347, SOMETHING_WICKED_2 = 347,
	THE_GATE_IS_OPEN = 348,
	BLACK_HOLE = 349,
	MYSTERY_GIFT = 350,
	SPRINKLER = 351,
	ANGRY_FLY = 352,
	BOZO = 353,
	BROKEN_MODEM = 354,
	BUDDY_IN_A_BOX = 355,
	FAST_BOMBS = 356,
	LIL_DELIRIUM = 357,
	HAIRPIN = 358,
	WOODEN_CROSS = 359,
	BUTTER = 360,
	HUGE_GROWTH = 361,
	ANCIENT_RECALL = 362,
	ERA_WALK = 363,
	COUPON = 364,
	TELEKINESIS = 365,
	MOVING_BOX = 366,
	JUMPER_CABLES = 367,
	LEPROSY = 368,
	TECHNOLOGY_ZERO = 369,
	FILIGREE_FEATHER = 370,
	MR_ME = 371,
	SEVEN_SEALS = 372,
	ANGELIC_PRISM = 373,
	POP = 374,
	DOOR_STOP = 375,
	DEATHS_LIST = 376,
	HAEMOLACRIA = 377,
	LACHRYPHAGY = 378,
	SCHOOLBAG = 379,
	TRISAGION = 380,
	EXTENSION_CORD = 381,
	FLAT_STONE = 382,
	SACRIFICAL_ALTAR = 383,
	LIL_SPEWER = 384,
	BLANKET = 385,
	MARBLES = 386,
	MYSTERY_EGG = 387,
	ROTTEN_PENNY = 388,
	BABY_BENDER = 389,
	THE_FORGOTTEN = 390, FORGOTTEN = 390,
	BONE_HEARTS = 391,
	MARROW = 392,
	SLIPPED_RIB = 393,
	POINTY_RIB = 394,
	JAW_BONE = 395,
	BRITTLE_BONES = 396,
	DIVORCE_PAPERS = 397,
	HALLOWED_GROUND = 398,
	FINGER_BONE = 399,
	DADS_RING = 400,
	BOOK_OF_THE_DEAD = 401,
	BONE_BABY = 402,
	BOUND_BABY = 403,
	BETHANY = 404,
	JACOB_AND_ESAU = 405,
	THE_STARS_ARE_CALLING = 406, PLANETARIUMS = 406,
	UNLOCKED_A_SECRET_EXIT = 407, SECRET_EXIT = 407, ALT_PATH = 407, ANTIBIRTH_PATH = 407,
	FORGOTTEN_LULLABY = 408,
	FRUITY_PLUM = 409,
	PLUM_FLUTE = 410,
	ROTTEN_HEARTS = 411,
	DROSS = 412,
	ASHPIT = 413,
	GEHENNA = 414,
	RED_KEY = 415,
	WISP_BABY = 416,
	BOOK_OF_VIRTUES = 417,
	URN_OF_SOULS = 418,
	BLESSED_PENNY = 419,
	ALABASTER_BOX = 420,
	BETHS_FAITH = 421,
	SOUL_LOCKET = 422,
	DIVINE_INTERVENTION = 423,
	VADE_RETRO = 424,
	STAR_OF_BETHLEHEM = 425,
	HOPE_BABY = 426,
	GLOWING_BABY = 427,
	DOUBLE_BABY = 428,
	THE_STAIRWAY = 429, STAIRWAY = 429,
	RED_STEW = 430,
	BIRTHRIGHT = 431,
	DAMOCLES = 432,
	ROCK_BOTTOM = 433,
	INNER_CHILD = 434,
	VANISHING_TWIN = 435,
	GENESIS = 436,
	SUPLEX = 437,
	SOLOMONS_BABY = 438,
	ILLUSION_BABY = 439,
	MEAT_CLEAVER = 440,
	OPTIONS = 441, OPTIONS_Q = 441,
	YUCK_HEART = 442,
	CANDY_HEART = 443,
	GUPPYS_EYE = 444,
	A_POUND_OF_FLESH = 445, POUND_OF_FLESH = 445,
	AKELDAMA = 446,
	REDEMPTION = 447,
	ETERNAL_D6 = 448,
	MONTEZUMAS_REVENGE = 449,
	BIRD_CAGE = 450,
	CRACKED_ORB = 451,
	BLOODY_GUST = 452,
	EMPTY_HEART = 453,
	DEVILS_CROWN = 454,
	LIL_ABADDON = 455,
	TINYTOMA = 456,
	ASTRAL_PROJECTION = 457,
	M = 458, APOSTROPHE_M = 458,
	EVERYTHING_JAR = 459,
	LOST_SOUL = 460,
	HUNGRY_SOUL = 461,
	BLOOD_PUPPY = 462,
	C_SECTION = 463,
	KEEPERS_SACK = 464,
	KEEPERS_BOX = 465,
	LIL_PORTAL = 466,
	WORM_FRIEND = 467,
	BONE_SPURS = 468,
	SPIRIT_SHACKLES = 469,
	REVELATION = 470,
	JAR_OF_WISPS = 471,
	MAGIC_SKIN = 472,
	FRIEND_FINDER = 473,
	TAINTED_ISAAC = 474,
	TAINTED_MAGGY = 475, TAINTED_MAGDALENE = 475,
	TAINTED_CAIN = 476,
	TAINTED_JUDAS = 477,
	TAINTED_BLUE_BABY = 478, TAINTED_QQQ = 478,
	TAINTED_EVE = 479,
	TAINTED_SAMSON = 480,
	TAINTED_AZAZEL = 481,
	TAINTED_LAZARUS = 482,
	TAINTED_EDEN = 483,
	TAINTED_THE_LOST = 484, TAINTED_LOST = 484,
	TAINTED_LILITH = 485,
	TAINTED_KEEPER = 486,
	TAINTED_APOLLYON = 487,
	TAINTED_THE_FORGOTTEN = 488, TAINTED_FORGOTTEN = 488,
	TAINTED_BETHANY = 489,
	TAINTED_JACOB = 490, TAINTED_JACOB_AND_ESAU = 490,
	GLITCHED_CROWN = 491,
	BELLY_JELLY = 492,
	BLUE_KEY = 493,
	SANGUINE_BOND = 494,
	THE_SWARM = 495, SWARM = 495,
	HEARTBREAK = 496,
	LARYNX = 497,
	AZAZELS_RAGE = 498,
	SALVATION = 499,
	TMTRAINER = 500,
	SACRED_ORB = 501,
	TWISTED_PAIR = 502,
	STRAWMAN = 503,
	ECHO_CHAMBER = 504,
	ISAACS_TOMB = 505,
	VENGEFUL_SPIRIT = 506,
	ESAU_JR = 507,
	CHALLENGE_37_BLOODY_MARY = 508, BLOODY_MARY = 508,
	CHALLENGE_38_BAPTISM_BY_FIRE = 509, BAPTISM_BY_FIRE = 509,
	CHALLENGE_39_ISAACS_AWAKENING = 510, ISAACS_AWAKENING = 510,
	CHALLENGE_40_SEEING_DOUBLE = 511, SEEING_DOUBLE = 511,
	CHALLENGE_41_PICA_RUN = 512, PICA_RUN = 512,
	CHALLENGE_42_HOT_POTATO = 513, HOT_POTATO = 513,
	CHALLENGE_43_CANTRIPPED = 514, CANTRIPPED = 514,
	CHALLENGE_44_RED_REDEMPTION = 515, RED_REDEMPTION = 515,
	CHALLENGE_45_DELETE_THIS = 516, DELETE_THIS = 516,
	DIRTY_MIND = 517,
	SIGIL_OF_BAPHOMET = 518,
	PURGATORY = 519,
	SPIRIT_SWORD = 520,
	BROKEN_GLASSES = 521,
	ICE_CUBE = 522,
	CHARGED_PENNY = 523,
	REVERSED_THE_FOOL = 524, REVERSED_FOOL = 524,
	REVERSED_THE_MAGICIAN = 525, REVERSED_MAGICIAN = 525,
	REVERSED_THE_HIGH_PRIESTESS = 526, REVERSED_HIGH_PRIESTESS = 526,
	REVERSED_THE_EMPRESS = 527, REVERSED_EMPRESS = 527,
	REVERSED_THE_EMPEROR = 528, REVERSED_EMPEROR = 528,
	REVERSED_THE_HIEROPHANT = 529, REVERSED_HIEROPHANT = 529,
	REVERSED_THE_LOVERS = 530, REVERSED_LOVERS = 530,
	REVERSED_THE_CHARIOT = 531, REVERSED_CHARIOT = 531,
	REVERSED_JUSTICE = 532,
	REVERSED_THE_HERMIT = 533, REVERSED_HERMIT = 533,
	REVERSED_WHEEL_OF_FORTUNE = 534,
	REVERSED_STRENGTH = 535,
	REVERSED_THE_HANGED_MAN = 536, REVERSED_HANGED_MAN = 536,
	REVERSED_DEATH = 537,
	REVERSED_TEMPERANCE = 538,
	REVERSED_THE_DEVIL = 539, REVERSED_DEVIL = 539,
	REVERSED_THE_TOWER = 540, REVERSED_TOWER = 540,
	REVERSED_THE_STARS = 541, REVERSED_STARS = 541,
	REVERSED_THE_SUN_AND_THE_MOON = 542, REVERSED_SUN_AND_MOON = 542,
	REVERSED_JUDGEMENT = 543,
	REVERSED_THE_WORLD = 544, REVERSED_WORLD = 544,
	OLD_CAPACITOR = 545,
	BRIMSTONE_BOMBS = 546,
	MEGA_MUSH = 547,
	MOMS_LOCK = 548,
	DICE_BAG = 549,
	HOLY_CROWN = 550,
	MOTHERS_KISS = 551,
	GILDED_KEY = 552,
	LUCKY_SACK = 553,
	YOUR_SOUL = 554,
	NUMBER_MAGNET = 555,
	DINGLE_BERRY = 556,
	RING_CAP = 557,
	STRANGE_KEY = 558,
	LIL_CLOT = 559,
	TEMPORARY_TATTOO = 560,
	SWALLOWED_M80 = 561,
	WICKED_CROWN = 562,
	AZAZELS_STUMP = 563,
	TORN_POCKET = 564,
	TORN_CARD = 565,
	NUH_UH = 566,
	MODELING_CLAY = 567,
	KIDS_DRAWING = 568,
	CRYSTAL_KEY = 569,
	THE_TWINS = 570,
	ADOPTION_PAPERS = 571,
	KEEPERS_BARGAIN = 572,
	CURSED_PENNY = 573,
	CRICKET_LEG = 574,
	APOLLYONS_BEST_FRIEND = 575,
	POLISHED_BONE = 576,
	HOLLOW_HEART = 577,
	EXPANSION_PACK = 578,
	BETHS_ESSENCE = 579,
	RC_REMOTE = 580,
	FOUND_SOUL = 581,
	MEMBER_CARD = 582,
	GOLDEN_RAZOR = 583,
	SPINDOWN_DICE = 584,
	HYPERCOAGULATION = 585,
	BAG_OF_CRAFTING = 586,
	DARK_ARTS = 587,
	IBS = 588,
	SUMPTORIUM = 589,
	BERSERK = 590,
	HEMOPTYSIS = 591,
	FLIP = 592,
	CORRUPTED_DATA = 593,
	GHOST_BOMBS = 594,
	GELLO = 595,
	KEEPERS_KIN = 596,
	ABYSS = 597,
	DECAP_ATTACK = 598,
	LEMEGETON = 599,
	ANIMA_SOLA = 600,
	MEGA_CHEST = 601,
	QUEEN_OF_HEARTS = 602,
	GOLD_PILL = 603, GOLDEN_PILLS = 603,
	BLACK_SACK = 604,
	CHARMING_POOP = 605,
	HORSE_PILLS = 606,
	CRANE_GAME = 607,
	HELL_GAME = 608,
	WOODEN_CHEST = 609,
	WILD_CARD = 610,
	HAUNTED_CHEST = 611,
	FOOLS_GOLD = 612,
	GOLDEN_PENNY = 613, GOLDEN_PENNIES = 613,
	ROTTEN_BEGGAR = 614,
	GOLDEN_BATTERY = 615, GOLDEN_BATTERIES = 615,
	CONFESSIONAL = 616,
	GOLDEN_TRINKET = 617, GOLDEN_TRINKETS = 617,
	SOUL_OF_ISAAC = 618,
	SOUL_OF_MAGDALENE = 619, SOUL_OF_MAGGY = 619,
	SOUL_OF_CAIN = 620,
	SOUL_OF_JUDAS = 621,
	SOUL_OF_BLUE_BABY = 622, SOUL_OF_QQQ = 622,
	SOUL_OF_EVE = 623,
	SOUL_OF_SAMSON = 624,
	SOUL_OF_AZAZEL = 625,
	SOUL_OF_LAZARUS = 626,
	SOUL_OF_EDEN = 627,
	SOUL_OF_THE_LOST = 628, SOUL_OF_LOST = 628,
	SOUL_OF_LILITH = 629,
	SOUL_OF_THE_KEEPER = 630, SOUL_OF_KEEPER = 630,
	SOUL_OF_APOLLYON = 631,
	SOUL_OF_THE_FORGOTTEN = 632, SOUL_OF_FORGOTTEN = 632,
	SOUL_OF_BETHANY = 633,
	SOUL_OF_JACOB = 634, SOUL_OF_JACOB_AND_ESAU = 634,
	A_STRANGE_DOOR = 635, STRANGE_DOOR = 635, ASCENT_DOOR = 635,
	DEATH_CERTIFICATE = 636,
	DEAD_GOD = 637,
	PLAYED_ONLINE = 638,
	WON_ONLINE = 639, ONLINE_WON = 639,
	WON_ONLINE_DAILY = 640, DAILY_ONLINE_WON = 640,
	NUM_ACHIEVEMENTS,
};

enum eUseFlag : int {
    USE_NOANIM = 1,
    USE_NOCOSTUME = 1 << 1,
    USE_OWNED = 1 << 2,
    USE_ALLOWNONMAIN = 1 << 3,
    USE_REMOVEACTIVE = 1 << 4,
    USE_CARBATTERY = 1 << 5,
    USE_VOID = 1 << 6,
    USE_MIMIC = 1 << 7,
    USE_NOANNOUNCER = 1 << 8,
    USE_ALLOWWISPSPAWN = 1 << 9,
    USE_CUSTOMVARDATA = 1 << 10,
    USE_NOHUD = 1 << 11,
};

enum class eAnimationFlag : int {
    IGNORE_COLOR_MODIFIERS = 1 << 0,
    GLITCH = 1 << 1,
    IS_LIGHT = 1 << 2,
    APPLY_LAYER_SCALE_TO_SPRITE = 1 << 3,
    USE_CHAMPION_SHADER = 1 << 4,
    USE_DOGMA_SHADER = 1 << 5,
    IGNORE_GAME_TIME = 1 << 6,
    USE_GOLD_SHADER = 1 << 7,
    USE_SIMPLE_COLOR_OFFSET_SHADER = 1 << 8, // unused in PC
    PROCEDURAL = 1 << 9,
};

enum class eImageFlag : uint64_t {
    PROCEDURAL = 1 << 1,
};

enum class eVertexAttributeFormat : int {
    TERMINATOR = 0, // Used to define the end of the VertexAttributeDescriptor array
    FLOAT = 1,
    VEC_2 = 2,
    VEC_3 = 3,
    VEC_4 = 4,
    POSITION = 5, // Special handling in image render
    COLOR = 6, // Special handling in image render
    TEX_COORD = 7, // Special handling in image render
};

enum class eBlendFactor : int {
    ZERO = 0,
    ONE = 1,
    SRC_COLOR = 2,
    ONE_MINUS_SRC_COLOR = 3,
    DEST_COLOR = 4,
    ONE_MINUS_DST_COLOR = 5,
    SRC_ALPHA = 6,
    ONE_MINUS_SRC_ALPHA = 7,
    DST_ALPHA = 8,
    ONE_MINUS_DST_ALPHA = 9,

    NUM_BLEND_FACTORS,
};

enum class eBlendEquation : int {
    FUNC_ADD = 0,
    FUN_SUBTRACT = 1,
    FUNC_REVERSE_SUBTRACT = 2,
    MIN = 3,
    MAX = 4,

    NUM_BLEND_EQUATIONS
};

	// For address "literals" in LibZHL, it's best to define them here to avoid clashing with the parser more than needed
	static void* wglSwapBuffersAddr = GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
    struct DisjointedSet
    {
        uint32_t lowerBound;
        uint32_t upperBound;
        DisjointedSet* next;
    };
extern LIBZHL_API void ** __ptr_UserdataValue_ANM2_vftable;
#define UserdataValue_ANM2_vftable (*__ptr_UserdataValue_ANM2_vftable)
extern LIBZHL_API float* __ptr_g_WIDTH;
#define g_WIDTH (*__ptr_g_WIDTH)
extern LIBZHL_API float* __ptr_g_HEIGHT;
#define g_HEIGHT (*__ptr_g_HEIGHT)
extern LIBZHL_API float* __ptr_g_PointScale;
#define g_PointScale (*__ptr_g_PointScale)
extern LIBZHL_API float* __ptr_g_DisplayPixelsPerPoint;
#define g_DisplayPixelsPerPoint (*__ptr_g_DisplayPixelsPerPoint)
extern LIBZHL_API deque_ColorMod* __ptr_g_ColorOverrideStack;
#define g_ColorOverrideStack (*__ptr_g_ColorOverrideStack)
extern LIBZHL_API bool* __ptr_g_ANM2_LightRendering;
#define g_ANM2_LightRendering (*__ptr_g_ANM2_LightRendering)
extern LIBZHL_API bool* __ptr_g_ANM2_ReflectionRendering;
#define g_ANM2_ReflectionRendering (*__ptr_g_ANM2_ReflectionRendering)
extern LIBZHL_API bool* __ptr_g_ANM2_GlitchRendering;
#define g_ANM2_GlitchRendering (*__ptr_g_ANM2_GlitchRendering)
extern LIBZHL_API float* __ptr_g_ANM2_PixelationAmount;
#define g_ANM2_PixelationAmount (*__ptr_g_ANM2_PixelationAmount)
extern LIBZHL_API Vector* __ptr_g_ANM2_ClipPaneNormal;
#define g_ANM2_ClipPaneNormal (*__ptr_g_ANM2_ClipPaneNormal)
extern LIBZHL_API float* __ptr_g_ANM2_ClipPaneThreshold;
#define g_ANM2_ClipPaneThreshold (*__ptr_g_ANM2_ClipPaneThreshold)
extern LIBZHL_API BeamRenderer ** __ptr_g_BeamRenderer;
#define g_BeamRenderer (*__ptr_g_BeamRenderer)
extern LIBZHL_API void ** __ptr_EntityRTTI;
#define EntityRTTI (*__ptr_EntityRTTI)
extern LIBZHL_API void ** __ptr_EntityEffectRTTI;
#define EntityEffectRTTI (*__ptr_EntityEffectRTTI)
extern LIBZHL_API void ** __ptr_EntityFamiliarRTTI;
#define EntityFamiliarRTTI (*__ptr_EntityFamiliarRTTI)
extern LIBZHL_API void ** __ptr_EntityNPCRTTI;
#define EntityNPCRTTI (*__ptr_EntityNPCRTTI)
extern LIBZHL_API unsigned int* __ptr_s_EntityPickup_IgnoreModifiers;
#define s_EntityPickup_IgnoreModifiers (*__ptr_s_EntityPickup_IgnoreModifiers)
extern LIBZHL_API void ** __ptr_EntityPickupRTTI;
#define EntityPickupRTTI (*__ptr_EntityPickupRTTI)
extern LIBZHL_API void ** __ptr_EntityPlayerRTTI;
#define EntityPlayerRTTI (*__ptr_EntityPlayerRTTI)
extern LIBZHL_API void ** __ptr_EntityProjectileRTTI;
#define EntityProjectileRTTI (*__ptr_EntityProjectileRTTI)
extern LIBZHL_API Game ** __ptr_g_Game;
#define g_Game (*__ptr_g_Game)
extern LIBZHL_API char ** __ptr_g_KAGEInputController;
#define g_KAGEInputController (*__ptr_g_KAGEInputController)
extern LIBZHL_API char ** __ptr_ModReferences;
#define ModReferences (*__ptr_ModReferences)
extern LIBZHL_API char const* __ptr_g_GameVersionString;
#define g_GameVersionString (*__ptr_g_GameVersionString)
extern LIBZHL_API char* __ptr_g_ModsDirectory;
#define g_ModsDirectory (*__ptr_g_ModsDirectory)
extern LIBZHL_API char* __ptr_g_ModSaveDataPath;
#define g_ModSaveDataPath (*__ptr_g_ModSaveDataPath)
extern LIBZHL_API InputManager* __ptr_g_InputManagerBase;
#define g_InputManagerBase (*__ptr_g_InputManagerBase)
extern LIBZHL_API KAGE_Filesys_ContentManager* __ptr_g_ContentManager;
#define g_ContentManager (*__ptr_g_ContentManager)
extern LIBZHL_API void ** __ptr_KAGE_Filesys_File_vftable;
#define KAGE_Filesys_File_vftable (*__ptr_KAGE_Filesys_File_vftable)
extern LIBZHL_API KAGE_Filesys_FileManager* __ptr_g_FileManager;
#define g_FileManager (*__ptr_g_FileManager)
extern LIBZHL_API void ** __ptr_KAGE_Filesys_FileStream_vftable;
#define KAGE_Filesys_FileStream_vftable (*__ptr_KAGE_Filesys_FileStream_vftable)
extern LIBZHL_API KAGE_Filesys_SaveManager* __ptr_g_SaveManager;
#define g_SaveManager (*__ptr_g_SaveManager)
extern LIBZHL_API KAGE_Graphics_ImageBase_VertexAttributeDescriptor* __ptr_g_VertexAttributeDescriptor_Position;
#define g_VertexAttributeDescriptor_Position (*__ptr_g_VertexAttributeDescriptor_Position)
extern LIBZHL_API KAGE_Graphics_ImageManager* __ptr_g_KAGE_Graphics_ImageManager;
#define g_KAGE_Graphics_ImageManager (*__ptr_g_KAGE_Graphics_ImageManager)
extern LIBZHL_API KAGE_Graphics_Manager* __ptr_g_KAGE_Graphics_Manager;
#define g_KAGE_Graphics_Manager (*__ptr_g_KAGE_Graphics_Manager)
extern LIBZHL_API float* __ptr_g_OrthographicWidth;
#define g_OrthographicWidth (*__ptr_g_OrthographicWidth)
extern LIBZHL_API float* __ptr_g_OrthographicHeight;
#define g_OrthographicHeight (*__ptr_g_OrthographicHeight)
extern LIBZHL_API KAGE_Graphics_Shader ** __ptr_g_CurrentShader;
#define g_CurrentShader (*__ptr_g_CurrentShader)
extern LIBZHL_API KAGE_Graphics_Shader ** __ptr_g_AllShaders;
#define g_AllShaders (*__ptr_g_AllShaders)
extern LIBZHL_API void ** __ptr_KAGE_Graphics_Shader_vftable;
#define KAGE_Graphics_Shader_vftable (*__ptr_KAGE_Graphics_Shader_vftable)
extern LIBZHL_API KAGE_Graphics_VertexAttributeDescriptor* __ptr_g_ColorOffset_VertexAttributes;
#define g_ColorOffset_VertexAttributes (*__ptr_g_ColorOffset_VertexAttributes)
extern LIBZHL_API KAGE_Graphics_VertexAttributeDescriptor* __ptr_g_ColorOffset_Champion_VertexAttributes;
#define g_ColorOffset_Champion_VertexAttributes (*__ptr_g_ColorOffset_Champion_VertexAttributes)
extern LIBZHL_API LuaEngine ** __ptr_g_LuaEngine;
#define g_LuaEngine (*__ptr_g_LuaEngine)
extern LIBZHL_API char* __ptr_g_SaveDataPath;
#define g_SaveDataPath (*__ptr_g_SaveDataPath)
extern LIBZHL_API unsigned int* __ptr_g_WindowSizeX;
#define g_WindowSizeX (*__ptr_g_WindowSizeX)
extern LIBZHL_API unsigned int* __ptr_g_WindowSizeY;
#define g_WindowSizeY (*__ptr_g_WindowSizeY)
extern LIBZHL_API Manager ** __ptr_g_Manager;
#define g_Manager (*__ptr_g_Manager)
extern LIBZHL_API Menu_Character_Entry* __ptr_g_MenuCharacterEntries;
#define g_MenuCharacterEntries (*__ptr_g_MenuCharacterEntries)
extern LIBZHL_API MenuManager ** __ptr_g_MenuManager;
#define g_MenuManager (*__ptr_g_MenuManager)
extern LIBZHL_API int* __ptr_g_MenuControllerIndex;
#define g_MenuControllerIndex (*__ptr_g_MenuControllerIndex)
extern LIBZHL_API vector_ModManager_CharacterMap* __ptr_g_ModCharacterMap;
#define g_ModCharacterMap (*__ptr_g_ModCharacterMap)
extern LIBZHL_API char* __ptr_g_ModdingDataPath;
#define g_ModdingDataPath (*__ptr_g_ModdingDataPath)
extern LIBZHL_API std_list_ModReference* __ptr_g_Mods;
#define g_Mods (*__ptr_g_Mods)
extern LIBZHL_API unsigned int* __ptr_s_Shifts;
#define s_Shifts (*__ptr_s_Shifts)
extern LIBZHL_API RoomDescriptor* __ptr_g_DefaultRoomDescriptor;
#define g_DefaultRoomDescriptor (*__ptr_g_DefaultRoomDescriptor)
extern LIBZHL_API ShapeRenderer ** __ptr_g_ShapeRenderer;
#define g_ShapeRenderer (*__ptr_g_ShapeRenderer)
extern LIBZHL_API void ** __ptr_SteamCloudFile_vftable;
#define SteamCloudFile_vftable (*__ptr_SteamCloudFile_vftable)
struct Vector {
	float x; // 0x0
	float y; // 0x4
	LIBZHL_API void Lerp(Vector * other, float t);
	Vector() : x(0.f), y(0.f) {}
	Vector(float _x, float _y) : x(_x), y(_y) {}
	
	Vector operator-() const {
		return Vector(-x, -y);
	}

	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}
	
	Vector operator-(const Vector& other)
	{		
		return Vector(x - other.x, y - other.y);
	}
	
	Vector operator/(float amount)
	{		
		return Vector(x / amount, y / amount);
	}
	
	Vector operator*(float amount)
	{		
		return Vector(x * amount, y * amount);
	}

	Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector& operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector& operator+=(float amount)
	{
		x += amount;
		y += amount;
		return *this;
	}

	Vector& operator-=(float amount)
	{
		x -= amount;
		y -= amount;
		return *this;
	}
	
	Vector& operator*=(float amount)
	{
		x *= amount;
		y *= amount;
		return *this;
	}

	friend void swap(Vector& a, Vector& b)
	{
		std::swap(a.x, b.x);
		std::swap(a.y, b.y);
	}
}; // 0x8

struct ColorMod {
	float _tint[4]; // 0x0
	float _colorize[4]; // 0x10
	float _offset[3]; // 0x20
		ColorMod(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f,
				float ro = 0.0f, float go = 0.0f, float bo = 0.0f,
				float cr = 0.0f, float cg = 0.0f, float cb = 0.0f, float ca = 0.0f)
			: _tint{r, g, b, a}, _offset{ro, go, bo}, _colorize{cr, cg, cb, ca} {}
		
		bool operator==(const ColorMod& other) const {
			for (int i = 0; i < 4; i++) {
				if (_tint[i] != other._tint[i])
					return false;
				if (_colorize[i] != other._colorize[i])
					return false;
				if (i < 3 && _offset[i] != other._offset[i])
					return false;
			}
			return true;
		}

		inline ColorMod& operator*=(const ColorMod& other) {
			for (int i = 0; i < 4; ++i)
				_tint[i] *= other._tint[i];

			if (other._colorize[0] + other._colorize[1] + other._colorize[2] != 0.0f) {
				if (_colorize[0] + _colorize[1] + _colorize[2] != 0.0f) {
					for (int i = 0; i < 4; ++i)
						_colorize[i] = (_colorize[i] + other._colorize[i]) * 0.5f;
				} else {
					for (int i = 0; i < 4; ++i)
						_colorize[i] = other._colorize[i];
				}
			}

			for (int i = 0; i < 3; ++i)
				_offset[i] += other._offset[i];

			return *this;
		}
		
		inline ColorMod& operator=(const ColorMod& other) {
			for (int i = 0; i < 4; ++i) {
				_tint[i] = other._tint[i];
				_colorize[i] = other._colorize[i];
			}
			for (int i = 0; i < 3; ++i)
				_offset[i] = other._offset[i];
			
			return *this;
		}

}; // 0x2c

struct AnimationFrame {
	Vector crop; // 0x0
	float width; // 0x8
	float height; // 0xc
	Vector pos; // 0x10
	Vector scale; // 0x18
	Vector pivot; // 0x20
	int duration; // 0x28
	bool visible; // 0x2c
	char pad0[0x3]; // 0x2d
	ColorMod color; // 0x30
	float rotation; // 0x5c
	bool interpolated; // 0x60
	char pad1[0x3]; // 0x61
	int startFrame; // 0x64
	int endFrame; // 0x68
}; // 0x6c

struct AnimationLayer {
	int _layerID; // 0x0
	AnimationFrame * _animFrames; // 0x4
	int _numFrames; // 0x8
	bool _visible; // 0xc
	char pad0[0x3]; // 0xd
	LIBZHL_API void RenderFrame(Vector const & position, int frameIndex, Vector const & topLeftClamp, Vector const & BottomRightClamp, ANM2 * animation);
	LIBZHL_API static SourceQuad * __stdcall GetSourceQuad(SourceQuad * ret, void * unused, AnimationFrame const & frame, LayerState const & layer, Vector const & topLeftClamp, Vector const & BottomRightClamp, ANM2 const & animation);
	LIBZHL_API static DestinationQuad * __stdcall GetDestQuad(DestinationQuad * ret, Vector const & position, AnimationFrame const & frame, LayerState const & layer, Vector const & topLeftClamp, Vector const & BottomRightClamp, ANM2 const & animation);
	inline int GetLayerID() { return this->_layerID; }
	// Number of unique frames. Not the total length of the animation.
	// Note that interpolated frames have been split into multiple frames.
	// Should only be used internally, for accessing the array of AnimationFrames.
	inline int GetFrameCount() { return this->_numFrames; }
	inline AnimationFrame* GetFrame(const int frame) {
		if (this->_animFrames != nullptr && frame >= 0 && frame < this->GetFrameCount()) {
			return &this->_animFrames[frame];
		}
		return nullptr;
	}
	inline bool IsVisible() { return this->_visible; }
}; // 0x10

struct AnimationData {
	std_string _name; // 0x0
	AnimationLayer * _animLayers; // 0x18
	int _layerCount; // 0x1c
	char _nullLayersPtr[4]; // 0x20
	int _nullLayerCount; // 0x24
	AnimationData_EventTrigger * _eventTriggers; // 0x28
	unsigned int _eventTriggerCount; // 0x2c
	int _length; // 0x30
	bool _loop; // 0x34
	char pad0[0x3]; // 0x35
	int _layerMap[64]; // 0x38
	char pad1[0x4]; // 0x138
	inline std_string GetName() { return this->_name; };
	inline int GetLayerCount() { return this->_layerCount; };
	// Returns the Nth layer, from the bottom to the top.
	inline AnimationLayer* GetLayerByOrder(const int layer) {
		if (this->_animLayers != nullptr && layer >= 0 && layer < this->GetLayerCount()) {
			return &this->_animLayers[layer];
		}
		return nullptr;
	}
	// Given a layer ID, returns where in the layer order it sits.
	// IE, the very bottom layer is the 0th layer regardless of its ID.
	inline int GetLayerOrder(const int layerID) {
		if (this->_layerMap != nullptr && layerID >= 0 && layerID < 64) {
			return this->_layerMap[layerID];
		}
		return -1;
	}
	// Returns the layer with the provided ID, regardless of layer ordering.
	inline AnimationLayer* GetLayerById(const int layerID) {
		return this->GetLayerByOrder(this->GetLayerOrder(layerID));
	}
	inline int GetLength() { return this->_length; };
	inline bool IsLoopingAnimation() { return this->_loop; };
}; // 0x13c

struct AnimationState {
	ANM2 * _animation; // 0x0
	AnimationData * _animData; // 0x4
	int * _layerFrames; // 0x8
	int * _nullLayerFrames; // 0xc
	float _animFrame; // 0x10
	bool _isPlaying; // 0x14
	char pad0[0x3]; // 0x15
	int _currentlyTriggeredEvents; // 0x18
	int _previouslyTriggeredEvents; // 0x1c
	LIBZHL_API NullFrame * GetNullFrame(char const * nullLayerName);
	LIBZHL_API NullFrame * GetNullFrameByID(int nullLayerID);
	LIBZHL_API bool IsEventTriggered(char const * eventName);
	LIBZHL_API bool WasEventTriggered(char const * eventName);
	LIBZHL_API int NextEventTrigger(char const * eventName);
	LIBZHL_API void AdvancePosition(int targetFrame);
	LIBZHL_API void AdvanceLayerPosition(int layerID, float targetFrame);
	LIBZHL_API void AdvanceNullLayerPosition(int nullLayerID, float targetFrame);
	LIBZHL_API void Rewind();
	LIBZHL_API void Reset(AnimationState * right);
	LIBZHL_API void SetLayerFrame(int layerID, int frame);
	LIBZHL_API void Render(Vector const & position, Vector const & topLeftClamp, Vector const & bottomRightClamp);
    inline AnimationData* GetAnimationData() { return this->_animData; }
    inline void SetFrame(const float frame) { this->_animFrame = frame; }
    inline bool IsPlaying() { return this->_isPlaying; }
    inline void Play() {
        if (this->_animData != nullptr) {
            if (this->_animFrame < 0) {
                this->Rewind();
            }
            this->_isPlaying = true;
        }
    }
    inline void Stop() { if (this->_animData != nullptr) this->_isPlaying = false; }
}; // 0x20

struct ANM2 {
	std_string _filename; // 0x0
	std_string _animDefaultName; // 0x18
	AnimationState _animState; // 0x30
	AnimationState _overlayAnimState; // 0x50
	bool _overlayRenderFirst; // 0x70
	char pad0[0x3]; // 0x71
	AnimationData * _animData; // 0x74
	int _animCount; // 0x78
	LayerState * _layerState; // 0x7c
	unsigned int _layerCount; // 0x80
	std_string * _nullLayerNames; // 0x84
	unsigned int _numNullLayers; // 0x88
	std_string * _eventNames; // 0x8c
	unsigned int _numEvents; // 0x90
	Vector _offset; // 0x94
	Vector _scale; // 0x9c
	float _rotation; // 0xa4
	ColorMod _color; // 0xa8
	ColorMod _championColor; // 0xd4
	bool _flipX; // 0x100
	bool _flipY; // 0x101
	char pad1[0x2]; // 0x102
	float _playbackSpeed; // 0x104
	char pad2[0x1]; // 0x108
	bool _loaded; // 0x109
	char pad3[0x6]; // 0x10a
	unsigned int _bitflags; // 0x110
	LIBZHL_API void Render(Vector * position, Vector * topleftclamp, Vector * bottomrightclamp);
	LIBZHL_API void Update();
	LIBZHL_API void SetLayerFrame(int layerid, int frame);
	LIBZHL_API bool ReplaceSpritesheet(int LayerId, std_string & PngFilename);
	LIBZHL_API void LoadGraphics(bool unk);
	LIBZHL_API void Reset();
	LIBZHL_API LayerState * GetLayer(char const * layerName);
	LIBZHL_API LayerState * GetLayer(int layer);
	LIBZHL_API void RenderLayer(int param_1, Vector * param_2, Vector * param_3, Vector * param_4);
	LIBZHL_API bool IsPlaying(char const * name);
	LIBZHL_API int GetFrame();
	LIBZHL_API void SetFrame(std_string * anim, int frame);
	LIBZHL_API void Load(std_string & ANM2Path, bool loadgraphics);
	LIBZHL_API void Reload();
	LIBZHL_API bool SetAnimation(char const * anim, bool reset);
	LIBZHL_API bool SetOverlayAnimation(char const * anim, bool reset);
	LIBZHL_API void SetOverlayFrame(int frame);
	LIBZHL_API void SetOverlayFrame(char const * anim, int frame);
	LIBZHL_API void Play(char const * anim, bool reset);
	LIBZHL_API void constructor();
	LIBZHL_API void construct_from_copy(ANM2 * right);
	LIBZHL_API void destructor();
    inline AnimationState* GetAnimationState() { return &this->_animState; }
    inline AnimationState* GetOverlayAnimationState() { return &this->_overlayAnimState; }
    inline unsigned int GetAnimationCount() { return this->_animCount; }
    LIBZHL_API AnimationData* GetAnimationData(const int index);
	LIBZHL_API AnimationData* GetAnimationData(const std_string& animName);
	inline NullFrame* GetNullFrame(const char * name) {return this->GetAnimationState()->GetNullFrame(name); }
	inline NullFrame* GetOverlayNullFrame(const char * name) {return this->GetOverlayAnimationState()->GetNullFrame(name); }
	inline unsigned int GetLayerCount() { return this->_layerCount; } 
    inline unsigned int* GetRenderFlags() { return &this->_bitflags; } 
	inline ColorMod* GetColor() { return &this->_color; } 
	
	ANM2() 
	{
		this->constructor();
	}

    static inline void StartLightRendering() { g_ANM2_LightRendering = true; }
    static inline void EndLightRendering() { g_ANM2_LightRendering = false; }

    inline std::optional<uint32_t> GetAnimationByName(std::string_view name) const
    {
        for (size_t i = 0; i < (size_t)this->_animCount; ++i)
        {
            if (name == this->_animData[i]._name)
            {
                return i;
            }
        }

        return std::nullopt;
    }

    inline std::optional<uint32_t> GetEventByName(std::string_view name) const
    {
        for (size_t i = 0; i < this->_numEvents; ++i)
        {
            if (name == this->_eventNames[i])
            {
                return i;
            }
        }

        return std::nullopt;
    }
}; // 0x114

struct AchievementOverlay {
	char pad0[0x14]; // 0x0
	unsigned int displayedachievement; // 0x14
	unsigned int frame; // 0x18
	unsigned int status; // 0x1c
	ANM2 anm2; // 0x20
	char pad1[0x8238]; // 0x134
	LIBZHL_API void Update();
	inline ANM2* GetANM2() { return &anm2; }
}; // 0x836c

struct AchievementOverlay_Entry {
	unsigned int id; // 0x0
	std_string name; // 0x4
	std_string gfx; // 0x1c
}; // 0x34

struct ActiveItemDesc {
	int _item; // 0x0
	int _unk; // 0x4
	int _charge; // 0x8
	int _batteryCharge; // 0xc
	int _subCharge; // 0x10
	int _timeRechargeCooldown; // 0x14
	int _partialCharge; // 0x18
	int _varData; // 0x1c
}; // 0x20

struct AfterImageFrame {
	int _duration; // 0x0
	Vector _position; // 0x4
}; // 0xc

struct RNG {
	unsigned int _seed; // 0x0
	unsigned int _shift1; // 0x4
	unsigned int _shift2; // 0x8
	unsigned int _shift3; // 0xc
	LIBZHL_API void SetSeed(unsigned int Seed, unsigned int ShiftIdx);
	LIBZHL_API unsigned int RandomInt(unsigned int max);
	LIBZHL_API float RandomFloat();
	LIBZHL_API unsigned int Next();
	LIBZHL_API void game_constructor(unsigned int seed, unsigned int shiftidx);
}; // 0x10

struct Ambush {
	char pad0[0x18]; // 0x0
	int maxBossWaves; // 0x18
	int bossesPerWave; // 0x1c
	bool active; // 0x20
	char pad1[0x3]; // 0x21
	int currentWave; // 0x24
	char pad2[0x14]; // 0x28
	RNG rng; // 0x3c
	LIBZHL_API void StartChallenge();
	LIBZHL_API void SpawnBossrushWave();
	LIBZHL_API void SpawnWave();
	inline int* GetMaxBossrushWaves() {return &this->maxBossWaves; }
	inline int* GetNumBossesPerWave() {return &this->bossesPerWave; }
	inline int* GetCurrentWave() {return &this->currentWave; }
}; // 0x4c

struct KAGE_System_Mutex {
	void * vtable; // 0x0
	bool initialized; // 0x4
	char pad0[0x3]; // 0x5
	KAGE_System_CriticalSection * cs; // 0x8
}; // 0xc

struct KAGE_ReferenceCountBase {
	char pad0[0x4]; // 0x0
	unsigned short int strong; // 0x4
	unsigned short int weak; // 0x6
	KAGE_System_Mutex mutex; // 0x8
	LIBZHL_API void Free(unsigned int flags);
	LIBZHL_API void Free_Original(unsigned int flags);
	LIBZHL_API bool IncrementReferenceNonZero();
	LIBZHL_API bool IncrementReferenceNonZero_Original();
	LIBZHL_API void IncrementReference();
	LIBZHL_API void IncrementReference_Original();
	LIBZHL_API bool DecrementReference();
	LIBZHL_API bool DecrementReference_Original();
	LIBZHL_API void IncrementWeakReference();
	LIBZHL_API void IncrementWeakReference_Original();
	LIBZHL_API bool DecrementWeakReference();
	LIBZHL_API bool DecrementWeakReference_Original();
}; // 0x14

struct KAGE_ReferenceCount_ImageBase : public KAGE_ReferenceCountBase {
	KAGE_Graphics_ImageBase * image; // 0x14
}; // 0x18

struct KAGE_SmartPointer_ImageBase {
	KAGE_Graphics_ImageBase * image; // 0x0
	KAGE_ReferenceCount_ImageBase * counter; // 0x4
	LIBZHL_API KAGE_SmartPointer_ImageBase & swap(KAGE_SmartPointer_ImageBase const & other);
	LIBZHL_API void DecrRef();
private:
    void copy(const KAGE_SmartPointer_ImageBase& other)
    {
        if (other.counter)
        {
            other.counter->IncrementReference();
        }

        this->image = other.image;
        this->counter = other.counter;
    }

    void move(KAGE_SmartPointer_ImageBase& other)
    {
        this->image = other.image;
        this->counter = other.counter;
        other.image = nullptr;
        other.counter = nullptr;
    }

    void destroy()
    {
        DecrRef();
    }

public:
    KAGE_SmartPointer_ImageBase() {
        image = nullptr;
        counter = nullptr;
    }

    ~KAGE_SmartPointer_ImageBase() {
        destroy();
    }

    KAGE_SmartPointer_ImageBase(const KAGE_SmartPointer_ImageBase& other)
    {
        this->copy(other);
    }

    KAGE_SmartPointer_ImageBase(KAGE_SmartPointer_ImageBase&& other)
    {
        this->move(other);
    }

    KAGE_SmartPointer_ImageBase& operator=(const KAGE_SmartPointer_ImageBase& other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->destroy();
        this->copy(other);
        return *this;
    }

    KAGE_SmartPointer_ImageBase& operator=(KAGE_SmartPointer_ImageBase&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->destroy();
        this->move(other);
        return *this;
    }
   
}; // 0x8

struct BackdropConfig {
	unsigned int backdropId; // 0x0
	std_string gfx; // 0x4
	std_string waterGfx; // 0x1c
	std_string lFloorGfx; // 0x34
	std_string nFloorGfx; // 0x4c
	unsigned int walls; // 0x64
	unsigned int wallVariants; // 0x68
	unsigned int floors; // 0x6c
	unsigned int floorVariants; // 0x70
	unsigned int unk1; // 0x74
	std_string props; // 0x78
	std_string rocks; // 0x90
	std_string pit; // 0xa8
	std_string waterPit; // 0xc0
	std_string bridge; // 0xd8
	std_string door; // 0xf0
	std_string holeInWall; // 0x108
	std_string spikes; // 0x120
	unsigned int waterPitsMode; // 0x138
}; // 0x13c

struct Backdrop {
	KAGE_SmartPointer_ImageBase floorBuffer; // 0x0
	KAGE_SmartPointer_ImageBase wallsBuffer; // 0x8
	KAGE_SmartPointer_ImageBase floorSurface2; // 0x10
	KAGE_SmartPointer_ImageBase tempBackdropSurface; // 0x18
	char pad0[0x4]; // 0x20
	KAGE_SmartPointer_ImageBase gfx; // 0x24
	KAGE_SmartPointer_ImageBase waterGfx; // 0x2c
	KAGE_SmartPointer_ImageBase nlfloorGfx; // 0x34
	ANM2 floorANM2; // 0x3c
	unsigned int backdropId; // 0x150
	BackdropConfig configurations[63]; // 0x154
	Vector unkVec1; // 0x4f18
	Vector unkVec2; // 0x4f20
	RNG rng; // 0x4f28
	unsigned int seed; // 0x4f38
	ANM2 _wallDetailANM2; // 0x4f3c
	ANM2 _controlsANM2; // 0x5050
	ANM2 _controlsButtonsANM2; // 0x5164
	LIBZHL_API void Init(unsigned int backdropId, bool LoadGraphics);
	LIBZHL_API void LoadConfig(char * xmlpath);
	LIBZHL_API void RenderWater(Vector const & offset);
	LIBZHL_API void RenderWalls(Vector const & renderOffset, ColorMod color);
	LIBZHL_API void RenderFloor(Vector const & renderOffset, ColorMod color);
	LIBZHL_API void pre_render_walls();
}; // 0x5278

struct RoomEntry {
	unsigned int type; // 0x0
	unsigned short int variant; // 0x4
	unsigned short int subtype; // 0x6
	float weight; // 0x8
        RoomEntry()
        {
            type = 0;
            variant = 0;
            subtype = 0;
            weight = 0.0f;
        }
   
}; // 0xc

struct RoomSpawn {
	unsigned short int X; // 0x0
	unsigned short int Y; // 0x2
	RoomEntry * Entries; // 0x4
	unsigned char CountEntries; // 0x8
	char pad0[0x3]; // 0x9
	float SumWeights; // 0xc
    private:
        void copy(const RoomSpawn& other)
        {
            assert(this != &other);

            X = other.X;
            Y = other.Y;
            Entries = nullptr;
            CountEntries = other.CountEntries;
            SumWeights = other.SumWeights;

            if (CountEntries > 0)
            {
                Entries = new RoomEntry[CountEntries];

                for (size_t i = 0; i < CountEntries; ++i)
                {
                    Entries[i] = other.Entries[i];
                }
            }
        }

        void move(RoomSpawn&& other)
        {
            assert(this != &other);

            X = other.X;
            Y = other.Y;
            Entries = other.Entries;
            CountEntries = other.CountEntries;
            SumWeights = other.SumWeights;

            other.Entries = nullptr;
            other.CountEntries = 0;
        }

        void free()
        {
            if (CountEntries > 0)
            {
                delete[] Entries;
            }
        }

    public:
        RoomSpawn()
        {
            X = 0;
            Y = 0;
            Entries = nullptr;
            CountEntries = 0;
            SumWeights = 0.0f;
        }

        RoomSpawn(const RoomSpawn& other)
        {
            this->copy(other);
        }

        RoomSpawn(RoomSpawn&& other)
        {
            this->move(std::move(other));
        }

        RoomSpawn& operator=(const RoomSpawn& other)
        {
            if (this != &other)
            {
                this->free();
                this->copy(other);
            }

            return *this;
        }

        RoomSpawn& operator=(RoomSpawn&& other)
        {
            if (this != &other)
            {
                this->free();
                this->move(std::move(other));
            }

            return *this;
        }

        ~RoomSpawn()
        {
            this->free();
        }
   
}; // 0x10

struct RoomConfig_Room {
	int StageId; // 0x0
	int Mode; // 0x4
	int Type; // 0x8
	unsigned int Variant; // 0xc
	int Subtype; // 0x10
	std_string Name; // 0x14
	int Difficulty; // 0x2c
	float InitialWeight; // 0x30
	float Weight; // 0x34
	unsigned int Doors; // 0x38
	DoorsBitSet QuestDoors; // 0x3c
	RoomSpawn * Spawns; // 0x40
	unsigned short int SpawnCount; // 0x44
	char Width; // 0x46
	char Height; // 0x47
	int Shape; // 0x48
	RoomConfigFlags Flags; // 0x4c
	RoomConfig_Room * MergedData[2]; // 0x50
	unsigned int originalVariant; // 0x58
        static constexpr uint32_t VIRTUAL_ROOM_FLAG = 1 << 31;
        static constexpr uint32_t BOSS_DOUBLE_TROUBLE_START = 3700;
        static constexpr uint32_t BOSS_DOUBLE_TROUBLE_END = 3850;

    private:
        void copy(const RoomConfig_Room& other)
        {
            StageId = other.StageId;
            Mode = other.Mode;
            Type = other.Type;
            Variant = other.Variant;
            Subtype = other.Subtype;
            Name = other.Name;
            Difficulty = other.Difficulty;
            InitialWeight = other.InitialWeight;
            Weight = other.Weight;
            Doors = other.Doors;
            QuestDoors = other.QuestDoors;
            SpawnCount = other.SpawnCount;
            Width = other.Width;
            Height = other.Height;
            Shape = other.Shape;
            Flags = other.Flags;
            MergedData[0] = other.MergedData[0];
            MergedData[1] = other.MergedData[1];
            originalVariant = other.originalVariant;

            Spawns = nullptr;
            if (SpawnCount > 0)
            {
                Spawns = new RoomSpawn[SpawnCount];

                for (size_t i = 0; i < SpawnCount; ++i)
                {
                    Spawns[i] = other.Spawns[i];
                }
            }
        }

        void move(RoomConfig_Room&& other)
        {
            StageId = other.StageId;
            Mode = other.Mode;
            Type = other.Type;
            Variant = other.Variant;
            Subtype = other.Subtype;
            Name = std::move(other.Name);
            Difficulty = other.Difficulty;
            InitialWeight = other.InitialWeight;
            Weight = other.Weight;
            Doors = other.Doors;
            QuestDoors = other.QuestDoors;
            Spawns = other.Spawns;
            SpawnCount = other.SpawnCount;
            Width = other.Width;
            Height = other.Height;
            Shape = other.Shape;
            Flags = other.Flags;
            MergedData[0] = other.MergedData[0];
            MergedData[1] = other.MergedData[1];
            originalVariant = other.originalVariant;

            other.Spawns = nullptr;
            other.SpawnCount = 0;
        }

        void free()
        {
            if (SpawnCount > 0)
            {
                delete[] Spawns;
            }
        }

    public:
        RoomConfig_Room()
        {
            StageId = 0;
            Mode = 0;
            Type = 0;
            Variant = 0;
            Subtype = 0;
            Difficulty = 0;
            InitialWeight = 0.0f;
            Weight = 0.0f;
            Doors = 0;
            QuestDoors = 0;
            Spawns = nullptr;
            SpawnCount = 0;
            Width = 13;
            Height = 7;
            Shape = 1;
            Flags = 0;
            MergedData[0] = nullptr;
            MergedData[1] = nullptr;
            originalVariant = 0;
        }

        RoomConfig_Room(const RoomConfig_Room& other)
        {
            this->copy(other);
        }

        RoomConfig_Room(RoomConfig_Room&& other)
        {
            this->move(std::move(other));
        }

        RoomConfig_Room& operator=(const RoomConfig_Room& other)
        {
            if (this != &other)
            {
                this->free();
                this->copy(other);
            }

            return *this;
        }

        RoomConfig_Room& operator=(RoomConfig_Room&& other)
        {
            if (this != &other)
            {
                this->free();
                this->move(std::move(other));
            }

            return *this;
        }

        ~RoomConfig_Room()
        {
            this->free();
        }
   
    bool LIBZHL_API IsValidGridIndex(int index, bool includeWalls = true) const;
    bool LIBZHL_API IsAllowedGridIndex(int index) const;
   
}; // 0x5c

struct RoomDescriptor {
	int GridIndex; // 0x0
	int SafeGridIndex; // 0x4
	int ListIndex; // 0x8
	int Dimension; // 0xc
	RoomConfig_Room * Data; // 0x10
	RoomConfig_Room * OverrideData; // 0x14
	int AllowedDoors; // 0x18
	int Doors[8]; // 0x1c
	int DisplayFlags; // 0x3c
	int VisitedCount; // 0x40
	int Flags; // 0x44
	short int TotalMoneySpent; // 0x48
	short int ClearCount; // 0x4a
	int GreedSubType; // 0x4c
	short int PoopCount; // 0x50
	short int TKeeperCoinSpawns; // 0x52
	int PitsCount; // 0x54
	int DecorationSeed; // 0x58
	int SpawnSeed; // 0x5c
	int AwardSeed; // 0x60
	unsigned int BossDeathSeed; // 0x64
	vector_GridEntityDesc SavedGridEntities; // 0x68
	vector_EntitySaveState SavedEntities; // 0x74
	std_set_int RestrictedGridIndexes; // 0x80
	vector_EntitySaveState SavedEffects; // 0x88
	char pad0[0x18]; // 0x94
	short int ShopItemIdx; // 0xac
	short int ShopItemDiscountIdx; // 0xae
	int DeliriumDistance; // 0xb0
	int Group; // 0xb4
	LIBZHL_API RoomConfig_Room * constructor();
	LIBZHL_API void destructor();
	LIBZHL_API void InitSeeds(RNG * rng);
		int LIBZHL_API RoomDescriptor::GetErrorTrinketEffect();

        void RoomDescriptor::Reset()
        {
            this->destructor();
            this->constructor();
        }

}; // 0xb8

struct GameStateRoomConfig {
	unsigned int _compactData; // 0x0
	unsigned int _type; // 0x4
	unsigned int _variant; // 0x8
        static constexpr uint32_t UNK_ROOM_FLAG = 1 << 5;
        static constexpr uint32_t MIRRORED_ROOM_FLAG = 1 << 6;
        static constexpr uint32_t MERGED_ROOM_FLAG = 1 << 7;

        // Custom Flags
        static constexpr uint32_t DB_ROOM_FLAG = 1 << 0;
        static constexpr uint32_t VIRTUAL_ROOM_FLAG = 1 << 1;

        int GetStageID() const
        {
            return _compactData & 0xFFFF;
        }

        int GetMode() const
        {
            return (_compactData >> 16) & 0xFF; 
        }

        uint32_t GetFlags() const
        {
            return (_compactData >> 24) & 0xFF;
        }

        void SetStageID(int stage)
        {
            _compactData = (_compactData & ~0xFFFF) | (stage & 0xFFFF);
        }

        void SetMode(int mode)
        {
            _compactData = (_compactData & ~(0xFF << 16)) | ((mode & 0xFF) << 16);
        }

        void SetFlags(uint32_t flags)
        {
            _compactData = (_compactData & ~(0xFF << 24)) | ((flags & 0xFF) << 24);
        }
   
}; // 0xc

struct BackwardsStageDesc {
	RoomDescriptor _bossRooms[2]; // 0x0
	GameStateRoomConfig _bossRoomConfigs[2]; // 0x170
	RoomDescriptor _treasureRooms[2]; // 0x188
	GameStateRoomConfig _treasureRoomConfigs[2]; // 0x2f8
	unsigned int _bossRoomsCount; // 0x310
	unsigned int _treasureRoomsCount; // 0x314
	unsigned int _stageType; // 0x318
	bool _isXL; // 0x31c
	char pad0[0x3]; // 0x31d
}; // 0x320

struct BagOfCraftingOutput {
	int collectibleType; // 0x0
	int itemPoolType; // 0x4
}; // 0x8

struct Point {
	Vector _pos; // 0x0
	float _width; // 0x8
	float _spritesheetCoordinate; // 0xc
	ColorMod _color; // 0x10
	bool _worldSpace; // 0x3c
	char pad0[0x3]; // 0x3d
	LIBZHL_API void UpdateNormal(Vector * unk);
		Point() : _pos(Vector()), _spritesheetCoordinate(0.0f), _width(1.0f), _color(ColorMod()), _worldSpace(true) {}
		Point(Vector const& pos, float spritesheetCoordinate, float width, ColorMod const& color, bool worldSpace) : _pos(pos), _spritesheetCoordinate(spritesheetCoordinate), _width(width), _color(color), _worldSpace(worldSpace) {}

}; // 0x40

struct BeamRenderer {
	ANM2 _anm2; // 0x0
	char pad0[0x4]; // 0x114
	unsigned int _layer; // 0x118
	bool _useOverlayData; // 0x11c
	bool _unkBool; // 0x11d
	char pad1[0x2]; // 0x11e
	deque_Point _points; // 0x120
	char pad2[0xc]; // 0x134
	LIBZHL_API static void __stdcall Begin(ANM2 * anm2, unsigned int layer, bool useOverlay, bool unk);
	LIBZHL_API static void __stdcall Add(Vector * point, ColorMod * color, float spritesheetCoordinate, float width);
	LIBZHL_API static void __stdcall End();
		BeamRenderer(unsigned int layer, bool useOverlayData, bool unkBool) : _layer(layer), _useOverlayData(useOverlayData), _unkBool(unkBool) {}
	
		inline ANM2* GetANM2() { return &this->_anm2; }
		inline unsigned int* GetLayer() { return &this->_layer; }
		inline bool* GetUseOverlay() { return &this->_useOverlayData; }
		inline bool* GetUnkBool() { return &this->_unkBool; } 

}; // 0x140

struct BitSet128 {
	unsigned int ll; // 0x0
	unsigned int lh; // 0x4
	unsigned int hl; // 0x8
	unsigned int hh; // 0xc
	BitSet128() : ll(0), lh(0), hl(0), hh(0) {}
	BitSet128(unsigned int _ll, unsigned int _lh, unsigned int _hl, unsigned int _hh) : ll(_ll), lh(_lh), hl(_hl), hh(_hh) {}

	void AddFlags(const BitSet128& toAdd) {
		ll |= toAdd.ll;
		lh |= toAdd.lh;
		hl |= toAdd.hl;
		hh |= toAdd.hh;
	}

	void RemoveFlags(const BitSet128& toRemove) {
		ll &= ~toRemove.ll;
		lh &= ~toRemove.lh;
		hl &= ~toRemove.hl;
		hh &= ~toRemove.hh;
	}

	bool HasAny(const BitSet128& other) {
		return (ll & other.ll)
			|| (lh & other.lh)
			|| (hl & other.hl)
			|| (hh & other.hh);
	}
}; // 0x10

struct BlendMode {
	unsigned int _equation; // 0x0
	unsigned int _rgbSourceFactor; // 0x4
	unsigned int _rgbDestFactor; // 0x8
	unsigned int _alphaSourceFactor; // 0xc
	unsigned int _alphaDestFactor; // 0x10
	LIBZHL_API void GetMode(unsigned int mode, void * unk);
	BlendMode() : _equation(0), _rgbSourceFactor(1), _rgbDestFactor(7), _alphaSourceFactor(1), _alphaDestFactor(7){}
	BlendMode(int equation, int rgbS, int rgbD, int aS, int aD) : _equation(equation), _rgbSourceFactor(rgbS), _rgbDestFactor(rgbD), _alphaSourceFactor(aS), _alphaDestFactor(aD) {}
	BlendMode(unsigned int mode) {
		this->GetMode(mode, nullptr);
	}
}; // 0x14

struct BossPool_Pool {
	std_string _name; // 0x0
	vector_BossPoolEntry _entries; // 0x18
	float _totalWeight; // 0x24
	RNG _rng; // 0x28
	int _doubleTroubleRoomVariantStart; // 0x38
}; // 0x3c

struct BossPool {
	BossPool_Pool _pool[37]; // 0x0
	vector_bool _removedBosses; // 0x8ac
	vector_bool _levelBlacklist; // 0x8bc
	LIBZHL_API int GetBossId(int leveltype, int levelvariant, RNG * rng);
	LIBZHL_API BossPool_Entry * PickBoss(BossPool_Pool * pool);
	inline bool BossPool::WasBossRemoved(uint32_t bossId)
	{
		return _removedBosses[bossId] || _levelBlacklist[bossId];
	}
}; // 0x8cc

struct BossPool_Entry {
	int _id; // 0x0
	float _initialWeight; // 0x4
	float _weight; // 0x8
	int _achievementID; // 0xc
	int _roomVariantStart; // 0x10
}; // 0x14

struct EntityPtr {
	Entity * _ref; // 0x0
	LIBZHL_API void SetReference(Entity * entity);
	EntityPtr() : _ref(nullptr) {}
	EntityPtr(Entity* entity) { this->SetReference(entity); }
	~EntityPtr() { this->SetReference(nullptr); }

	inline Entity* GetReference() { return this->_ref; }
}; // 0x4

struct Entity {
	char pad0[0x20]; // 0x0
	unsigned int _index; // 0x20
	unsigned int _collisionIndex; // 0x24
	unsigned int _type; // 0x28
	unsigned int _variant; // 0x2c
	unsigned int _subtype; // 0x30
	unsigned int _spawnerType; // 0x34
	unsigned int _spawnerVariant; // 0x38
	char pad1[0xc]; // 0x3c
	ANM2 _sprite; // 0x48
	float _shadowSize; // 0x15c
	char pad2[0x8]; // 0x160
	unsigned long long int _flags; // 0x168
	bool _valid; // 0x170
	bool _visible; // 0x171
	bool _exists; // 0x172
	bool _dead; // 0x173
	char pad3[0x3]; // 0x174
	bool _removedByFactory; // 0x177
	char pad4[0xc]; // 0x178
	int _entityGridCollisionClass; // 0x184
	int _entityCollisionClass; // 0x188
	char pad5[0x2]; // 0x18c
	unsigned short int _entityExtraDataPtrUpperBytes; // 0x18e
	bool _collidesWithGrid; // 0x190
	char pad6[0x1]; // 0x191
	unsigned short int _entityExtraDataPtrLowerBytes; // 0x192
	char pad7[0x18]; // 0x194
	vector_ColorParams _colorParams; // 0x1ac
	char pad8[0x58]; // 0x1b8
	int _fireDamageCountdown; // 0x210
	int _damageCountdown; // 0x214
	int _freezeCountdown; // 0x218
	int _poisonCountdown; // 0x21c
	int _slowingCountdown; // 0x220
	int _charmedCountdown; // 0x224
	int _confusionCountdown; // 0x228
	int _midasFreezeCountdown; // 0x22c
	int _fearCountdown; // 0x230
	int _burnCountdown; // 0x234
	int _bossStatusEffectCooldown; // 0x238
	int _shrinkCountdown; // 0x23c
	char pad9[0x38]; // 0x240
	float _poisonDamage; // 0x278
	float _burnDamage; // 0x27c
	char pad10[0x30]; // 0x280
	float _depthOffset; // 0x2b0
	char pad11[0x20]; // 0x2b4
	float _mass; // 0x2d4
	char pad12[0x8]; // 0x2d8
	int _poisonDamageTimer; // 0x2e0
	int _burnDamageTimer; // 0x2e4
	int _bleedingCountdown; // 0x2e8
	char pad13[0x4]; // 0x2ec
	int _magnetizedCountdown; // 0x2f0
	int _baitedCountdown; // 0x2f4
	int _knockbackCountdown; // 0x2f8
	int _weaknessCountdown; // 0x2fc
	int _iceCountdown; // 0x300
	int _brimstoneMarkCountdown; // 0x304
	Vector _knockbackDirection; // 0x308
	char pad14[0xc]; // 0x310
	int _pauseTimer; // 0x31c
	char pad15[0x1c]; // 0x320
	Vector _pos; // 0x33c
	char pad16[0x8]; // 0x344
	Vector _posOffset; // 0x34c
	char pad17[0xc]; // 0x354
	Vector _velocity; // 0x360
	char pad18[0x8]; // 0x368
	float _size; // 0x370
	char pad19[0xc]; // 0x374
	float _health; // 0x380
	char pad20[0x4]; // 0x384
	float _collisionDamage; // 0x388
	char pad21[0x10]; // 0x38c
	float _speedMultiplier; // 0x39c
	char pad22[0x10]; // 0x3a0
	bool _isInvicible; // 0x3b0
	char pad23[0x3]; // 0x3b1
	float _shrinkStatus1; // 0x3b4
	float _shrinkStatus2; // 0x3b8
	EntityPtr _parent; // 0x3bc
	EntityPtr _child; // 0x3c0
	EntityPtr _target; // 0x3c4
	EntityPtr _spawnerEntity; // 0x3c8
	char pad24[0x8]; // 0x3cc
	EntityPtr _minecart; // 0x3d4
	char pad25[0x4]; // 0x3d8
	RNG _dropRNG; // 0x3dc
	unsigned int _initSeed; // 0x3ec
	char pad26[0x18]; // 0x3f0
	LuaBridgeRef * _luaBridgeRef; // 0x408
	char pad27[0x4]; // 0x40c
	LIBZHL_API void constructor();
	LIBZHL_API void destructor();
	LIBZHL_API void CopyStatusEffects();
	LIBZHL_API unsigned int ComputeStatusEffectDuration(int initial, EntityRef * source);
	LIBZHL_API Vector GetNullOffset(char const * nullLayerName);
	LIBZHL_API Capsule GetNullCapsule(char const * nullLayerName);
	LIBZHL_API bool RenderShadowLayer(Vector * offset);
	LIBZHL_API static bool ForceCollide(Entity * boom, Entity * collider, bool low);
	LIBZHL_API Capsule GetCollisionCapsule(Vector * vec);
	LIBZHL_API unsigned int GetHitListIndex();
	LIBZHL_API static void __stdcall DoGroundImpactEffects(Vector * pos, Vector * velocity, float strength);
	LIBZHL_API bool IgnoreEffectFromFriendly(EntityRef * source);
	LIBZHL_API Entity_Effect * MakeBloodPoof(Vector * pos, ColorMod * color, float size);
	LIBZHL_API Entity_Effect * MakeGroundPoof(Vector * pos, ColorMod * color, float size);
	LIBZHL_API void TeleportToRandomPosition(bool unused);
	LIBZHL_API bool IsFlying();
	LIBZHL_API void AddBaited(EntityRef const & ref, int duration, bool unused);
	LIBZHL_API void AddBleeding(EntityRef const & ref, int duration, bool unused);
	LIBZHL_API void AddBrimstoneMark(EntityRef const & ref, int duration);
	LIBZHL_API void AddBurn(EntityRef const & ref, int duration, float damage, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddCharmed(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown, bool addEnemyKillScore);
	LIBZHL_API void AddConfusion(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddFear(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddFreeze(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddKnockback(EntityRef const & ref, Vector const & pushDirection, int duration, bool takeImpactDamage);
	LIBZHL_API void AddIce(EntityRef const & ref, int duration);
	LIBZHL_API void AddMagnetized(EntityRef const & ref, int duration, bool unused);
	LIBZHL_API void AddMidasFreeze(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddPoison(EntityRef const & ref, int duration, float damage, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddShrink(EntityRef const & ref, int duration, bool ignoreBossStatusCooldown, bool unk);
	LIBZHL_API void AddSlowing(EntityRef const & ref, int duration, float amount, ColorMod color, bool ignoreBossStatusCooldown);
	LIBZHL_API void AddWeakness(EntityRef const & ref, int duration);
	LIBZHL_API Entity * GetStatusEffectTarget();
	LIBZHL_API bool DoesEntityShareStatus();
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API void ClearBossHazards(bool excludeNPCs);
	LIBZHL_API bool CanDevolve();
	LIBZHL_API bool IsActiveEnemy(bool includeDead);
	LIBZHL_API Entity_NPC * GiveMinecart(Vector * position, Vector * velocity);
	LIBZHL_API void Free(unsigned int flags);
	LIBZHL_API void Original_Free(unsigned int flags);
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	void virtual_unk0() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk1() { }
	void virtual_unk2() { }
	void virtual_unk3() { }
	void virtual_unk4() { }
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API void Kill(EntityRef * Source);
	LIBZHL_API void Original_Kill(EntityRef * Source);
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	void virtual_unk5() { }
	void virtual_unk6() { }
	void virtual_unk7() { }
	void virtual_unk8() { }
	LIBZHL_API void SetColor(ColorMod * color, int Duration, int Priority, bool Fadeout, bool Shared);
	LIBZHL_API void Original_SetColor(ColorMod * color, int Duration, int Priority, bool Fadeout, bool Shared);
	void virtual_unk9() { }
	LIBZHL_API void ClearReferences();
	LIBZHL_API void Original_ClearReferences();
	void virtual_unk10() { }
	void virtual_unk11() { }
	void virtual_unk12() { }
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * dir, float force);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * dir, float force);
	void virtual_unk13() { }
	void virtual_unk14() { }
	LIBZHL_API void ResetColor();
	LIBZHL_API void Original_ResetColor();
	void virtual_unk15() { }
	inline int GetIndex() { return this->_index; }
	inline unsigned int* GetType() { return &this->_type; }
	inline unsigned int* GetVariant() { return &this->_variant; }
	inline unsigned int* GetSubType() { return &this->_subtype; }
	inline AnimationState* GetAnimationState() { return (AnimationState*)((char*)this + 0x6c); }
	inline bool IsAnimationExist() {
		int animSomething = *(int*)((char*)this + 0x70); //unknown type, so use int instead
		return animSomething != NULL;
	}
	inline AnimationState* GetOverlayAnimationState() { return (AnimationState*)((char*)this + 0x8c); }
	inline bool IsOverlayAnimationExist() {
		int overlayAnimSomething = *(int*)((char*)this + 0x90); //unknown type, so use int instead
		return overlayAnimSomething != NULL;
	}
	inline float* GetShadowSize() { return &this->_shadowSize; }
	inline bool* GetVisible() { return &this->_visible; }
	inline bool* IsDead() { return &this->_dead; }
	inline int* GetBossStatusEffectCooldown() { return &this->_bossStatusEffectCooldown; }
	inline int* GetPauseTime() { return &this->_pauseTimer; }
	inline Vector* GetPosition() { return &this->_pos; }
	inline bool* IsInvincible() { return &this->_isInvicible; }
	inline int* GetFireDamageCountdown() { return &this->_fireDamageCountdown; }
	inline int* GetDamageCountdown() { return &this->_damageCountdown; }

    template<typename T>
    inline T Downcast(void* target) {
        return (T)__RTDynamicCast(this, 0, (void*)__ptr_EntityRTTI, target, false); 
    }

	inline Entity* GetParent() { return this->_parent.GetReference(); }
	inline void SetParent(Entity* entity) { this->_parent.SetReference(entity); }

	inline Entity* GetChild() { return this->_child.GetReference(); }
	inline void SetChild(Entity* entity) { this->_child.SetReference(entity); }

	inline Entity* GetTarget() { return this->_target.GetReference(); }
	inline void SetTarget(Entity* entity) { this->_target.SetReference(entity); }

	inline Entity* GetSpawnerEntity() { return this->_spawnerEntity.GetReference(); }
	inline void SetSpawnerEntity(Entity* entity) { this->_spawnerEntity.SetReference(entity); }

	inline Entity* GetMinecart() { return this->_minecart.GetReference(); }
	
	inline LuaBridgeRef** GetLuaRef() { return &this->_luaBridgeRef; }
	
    inline Entity_NPC* ToNPC() { return Downcast<Entity_NPC*>(__ptr_EntityNPCRTTI); } 
    inline Entity_Player* ToPlayer() { return Downcast<Entity_Player*>(__ptr_EntityPlayerRTTI); }
    inline Entity_Familiar* ToFamiliar() { return Downcast<Entity_Familiar*>(__ptr_EntityFamiliarRTTI); }
    inline Entity_Pickup* ToPickup() { return Downcast<Entity_Pickup*>(__ptr_EntityPickupRTTI); }
    inline Entity_Projectile* ToProjectile() { return Downcast<Entity_Projectile*>(__ptr_EntityProjectileRTTI); }
	inline Entity_Effect* ToEffect() { return Downcast<Entity_Effect*>(__ptr_EntityEffectRTTI); }

    Vector LIBZHL_API Entity::GetPredictedTargetPosition(Entity* target, float multiplier);
	
	Entity() 
	{
		this->constructor();
	}
}; // 0x410

struct EntityList_EL {
	bool _sublist; // 0x0
	char pad0[0x3]; // 0x1
	Entity * * _data; // 0x4
	unsigned int _capacity; // 0x8
	unsigned int _size; // 0xc
	LIBZHL_API void constructor(EntityList_EL * source);
	LIBZHL_API void Destroy();
	EntityList_EL(EntityList_EL *source) 
	{
		this->constructor(source);
	}
    
    EntityList_EL()
    {
    
    }

    void RemoveAt(size_t index)
    {
        size_t size = this->_size;

        if (size <= index)
        {
            assert(false);
            return;
        }

        if (index < size - 1)
        {
            Entity** data = this->_data;
            size_t moveCount = (size - 1 - index) * sizeof(Entity*);
            memmove(&data[index], &data[index + 1], moveCount);
        }

        this->_size--;
    }

    /* If this list is a sublist, turn it into a non sublist. This makes the content 
     * of the list no longer shared with other sublists, preventing some issues with
     * the way the game manages sublists.
     */
    LIBZHL_API void Untie();
}; // 0x10

struct EntityList {
	char pad0[0x20]; // 0x0
	EntityList_EL _mainEL; // 0x20
	EntityList_EL _persistentEL; // 0x30
	EntityList_EL _updateEL; // 0x40
	EntityList_EL _renderEL; // 0x50
	EntityList_EL _effectEL; // 0x60
	EntityList_EL _tempEL; // 0x70
	EntityList_EL _bufferTemplateEL; // 0x80
	EntityList_EL _wispEL; // 0x90
	char pad1[0x360]; // 0xa0
	LIBZHL_API void RenderShadows(Vector * offset);
	LIBZHL_API void Reset();
	LIBZHL_API EntityList_EL * QueryType(EntityList_EL * result, int Type, int Variant, int Subtype, bool Cache, bool IgnoreFriendly);
	LIBZHL_API EntityList_EL QueryRadius(Vector * Position, float Radius, unsigned int Partitions);
	LIBZHL_API EntityList_EL * QueryCapsule(EntityList_EL * result, Capsule * Capsule, unsigned int Partitions);
	LIBZHL_API void render_sort();
	inline EntityList_EL* GetMainEL() { return &this->_mainEL; }
    inline EntityList_EL* GetUpdateEL() { return &this->_updateEL; }
	inline EntityList_EL* GetRenderEL() { return &this->_renderEL; }
    inline EntityList_EL* GetTempEL() { return &this->_tempEL; }
	inline EntityList_EL* GetWispEL() { return &this->_wispEL; }
    inline EntityList_EL* GetPersistentEL() { return &this->_persistentEL; }

	// This exists in the original source code as evidenced in the Switch decomp, but was inlined on PC.
	int CountWisps(unsigned int WispSubtype) {
	
		EntityList_EL* wisps = this->GetWispEL();
		unsigned int size = wisps->_size;
		unsigned int wispCount = 0;
		
		if (size) {
			Entity** data = wisps->_data;

			while (size) {
				Entity* wisp = *data;
				++data;
				if (wisp->_subtype == WispSubtype) // int WispSubtype
					wispCount++;
				--size;
			}
		}
		
		return wispCount;
	}
	
	
}; // 0x400

struct KColor {
	float _red; // 0x0
	float _green; // 0x4
	float _blue; // 0x8
	float _alpha; // 0xc
	int _unk; // 0x10
	KColor(float r = 1, float g = 1, float b = 1, float a = 1, int unk = 0) : _red(r), _green(g), _blue(b), _alpha(a), _unk(unk) {}
}; // 0x14

struct TemporaryEffects {
	char pad0[0x4]; // 0x0
	vector_TemporaryEffect _effects; // 0x4
	bool _shouldEvaluateCache; // 0x10
	bool _disabled; // 0x11
	char pad1[0x2]; // 0x12
	Entity_Player * _player; // 0x14
	LIBZHL_API void AddCollectibleEffect(int coltype, bool addcostume, int count);
	LIBZHL_API TemporaryEffect * GetCollectibleEffect(int coltype);
	LIBZHL_API int GetCollectibleEffectNum(int coltype);
	LIBZHL_API bool HasCollectibleEffect(int coltype);
	LIBZHL_API void RemoveCollectibleEffect(int coltype, int count);
	LIBZHL_API void AddNullEffect(int nulleffectid, bool addcostume, int count);
	LIBZHL_API TemporaryEffect * GetNullEffect(int nulleffectid);
	LIBZHL_API int GetNullEffectNum(int nulleffectid);
	LIBZHL_API bool HasNullEffect(int nulleffectid);
	LIBZHL_API void RemoveNullEffect(int nulleffectid, int count);
	LIBZHL_API void AddTrinketEffect(int trinkettype, bool addcostume, int count);
	LIBZHL_API TemporaryEffect * GetTrinketEffect(int trinkettype);
	LIBZHL_API int GetTrinketEffectNum(int trinkettype);
	LIBZHL_API bool HasTrinketEffect(int trinkettype);
	LIBZHL_API void RemoveTrinketEffect(int trinkettype, int count);
	LIBZHL_API void AddEffect(TemporaryEffect * Effect, bool addcostume, int count);
}; // 0x18

struct FXParams {
	KColor roomColor; // 0x0
	float brightness; // 0x14
	float contrast; // 0x18
	bool useWaterV2; // 0x1c
	char pad0[0x3]; // 0x1d
	KColor waterColor; // 0x20
	KColor waterColorMultiplier; // 0x34
	float shadowAlpha; // 0x48
	KColor shadowColor; // 0x4c
	KColor lightColor; // 0x60
	ColorMod waterEffectColor; // 0x74
	LIBZHL_API FXParams * Init();
	inline bool* GetWaterV2() { return &this->useWaterV2; }
	inline KColor* GetWaterColor() { return &this->waterColor; }
	inline KColor* GetWaterColorMultiplier() { return &this->waterColorMultiplier; }
	inline float* GetShadowAlpha() { return &this->shadowAlpha; }
	inline KColor* GetShadowColor() { return &this->shadowColor; }
	inline KColor* GetLightColor() { return &this->lightColor; }
	inline ColorMod* GetWaterEffectColor() { return &this->waterEffectColor; }
}; // 0xa0

struct FXLayers {
	char pad0[0x8]; // 0x0
	bool _loaded; // 0x8
	char pad1[0x2b]; // 0x9
	int _poopFxCountdown; // 0x34
	char pad2[0x4c]; // 0x38
	ColorMod _poopFxColor; // 0x84
	char pad3[0x448]; // 0xb0
	FXParams _fxParams; // 0x4f8
	LIBZHL_API void AddPoopFx(ColorMod * color);
}; // 0x598

struct RailManager {
	Room * _room; // 0x0
	unsigned char _gridflags[447]; // 0x4
	char pad0[0x1]; // 0x1c3
	ANM2 _sprite; // 0x1c4
	
}; // 0x2d8

struct Room {
	char pad0[0x4]; // 0x0
	RoomDescriptor * _descriptor; // 0x4
	unsigned int _roomType; // 0x8
	unsigned int _gridWidth; // 0xc
	unsigned int _gridHeight; // 0x10
	char pad1[0x10]; // 0x14
	GridEntity * _gridEntities[447]; // 0x24
	char pad2[0x4]; // 0x720
	GridEntity * _doors[8]; // 0x724
	unsigned int _doorGridPositions[8]; // 0x744
	char pad3[0x8]; // 0x764
	int _gridPaths[456]; // 0x76c
	char pad4[0x360]; // 0xe8c
	int _roomClearDelay; // 0x11ec
	char pad5[0x8]; // 0x11f0
	Camera * _Camera; // 0x11f8
	char pad6[0x8]; // 0x11fc
	Vector _renderScrollOffset; // 0x1204
	bool _redHeartDamage; // 0x120c
	char pad7[0xb]; // 0x120d
	EntityList _entityList; // 0x1218
	FXLayers _fxLayers; // 0x1618
	unsigned int _bossId; // 0x1bb0
	char pad8[0x14]; // 0x1bb4
	Backdrop _backdrop; // 0x1bc8
	char pad9[0x230]; // 0x6e40
	deque_ShopRestockDesc _shopItemDeque; // 0x7070
	char pad10[0x19c]; // 0x7084
	int _slowdownDuration; // 0x7220
	char pad11[0x18]; // 0x7224
	int _greedWaveTimer; // 0x723c
	float _waterAmount; // 0x7240
	KColor _waterColor; // 0x7244
	KColor _waterColorMultiplier; // 0x7258
	KColor _waterLerpTargetColor; // 0x726c
	KColor _waterLerpTargetColorMult; // 0x7280
	int _waterLerpColorDuration; // 0x7294
	int _waterLerpColorCountdown; // 0x7298
	char pad12[0x5]; // 0x729c
	bool _pacifist; // 0x72a1
	char pad13[0x2]; // 0x72a2
	ColorMod _floorColor; // 0x72a4
	ColorMod _wallColor; // 0x72d0
	char pad14[0x14]; // 0x72fc
	TemporaryEffects _temporaryEffects; // 0x7310
	char pad15[0x12c]; // 0x7328
	int _numRainSpawners; // 0x7454
	float _rainIntensity; // 0x7458
	char pad16[0x4]; // 0x745c
	Vector _waterCurrent; // 0x7460
	RailManager _railManager; // 0x7468
	float _lavaIntensity; // 0x7740
	Entity_Effect * _redDoorOutlines[8]; // 0x7744
	char pad17[0x134]; // 0x7764
	LIBZHL_API Room * constructor();
	LIBZHL_API void destructor();
	LIBZHL_API int GetFrameCount();
	LIBZHL_API float GetDevilRoomChance();
	LIBZHL_API GridEntity * GetGridEntity(unsigned int idx);
	LIBZHL_API unsigned int GetGridCollision(int index);
	LIBZHL_API void ShopRestockFull();
	LIBZHL_API void ShopRestockPartial();
	LIBZHL_API void TriggerRestock(int grid_idx, int shop_idx);
	LIBZHL_API int GetShopItemPrice(unsigned int entVariant, unsigned int entSubType, int shopItemID);
	LIBZHL_API bool SpawnGridEntity(int GridIndex, unsigned int Type, unsigned int Variant, unsigned int Seed, int VarData);
	LIBZHL_API bool SpawnGridEntityDesc(int GridIndex, GridEntityDesc * Desc);
	LIBZHL_API void RemoveGridEntityImmediate(int GridIndex, int PathTrail, bool KeepDecoration);
	LIBZHL_API void TriggerClear(bool playSound);
	LIBZHL_API void UpdateRedKey();
	LIBZHL_API bool CanSpawnObstacleAtPosition(int GridIndex, bool Force);
	LIBZHL_API float GetLightingAlpha();
	LIBZHL_API void PreRender();
	LIBZHL_API void RenderGridLight(GridEntity * grid, Vector & offset);
	LIBZHL_API void RenderEntityLight(Entity * ent, Vector & offset);
	LIBZHL_API bool CanPickupGridEntity(int GridIndex);
	LIBZHL_API bool PickupGridEntity(int GridIndex, GridEntityDesc * Desc, ANM2 * Sprite);
	LIBZHL_API Entity_Effect * PickupGridEntity(int GridIndex);
	LIBZHL_API int GetGridIndexByTile(int GridRow, int GridColumn);
	LIBZHL_API void Init(RoomConfig_Room * room, RoomDescriptor * descriptor);
	LIBZHL_API void SetPauseTimer(int Duration);
	LIBZHL_API ColorModState ComputeColorModifier();
	LIBZHL_API int TryGetShopDiscount(int shopItemIdx, int price);
	LIBZHL_API bool IsPersistentRoomEntity(int type, int variant, int subtype);
	LIBZHL_API GridEntity_Door * GetDoor(int slot);
	LIBZHL_API void MakeDoor(int slot);
	LIBZHL_API bool TrySpawnSpecialQuestDoor();
	LIBZHL_API void SaveState();
	LIBZHL_API void RestoreState();
	LIBZHL_API unsigned int GetBossVictoryJingle();
	LIBZHL_API void TriggerEffectRemoved(ItemConfig_Item * item, int unused);
	LIBZHL_API void TriggerRedRoomCreated(int param_1, RoomDescriptor * RoomDesc);
	LIBZHL_API static int GetItemPool(unsigned int seed, RoomDescriptor * roomDesc, int boss);
	LIBZHL_API unsigned int GetBrokenWatchState();
	LIBZHL_API void MamaMegaExplosion(Vector * Position);
	LIBZHL_API LRoomAreaDesc * GetLRoomAreaDesc(LRoomAreaDesc * buffer);
	LIBZHL_API LRoomTileDesc * GetLRoomTileDesc(LRoomTileDesc * buffer);
	LIBZHL_API KColor GetFloorColorAt(Vector & pos, float radius);
	LIBZHL_API void SpawnGreedModeWave(bool unusedBool);
	LIBZHL_API void TriggerOutput(unsigned int outputGroupdIdx);
	LIBZHL_API int GetRoomConfigStage();
	LIBZHL_API bool GetBossThematicItem(int * retCollectibleType, int * retTrinketType, unsigned int * seed);
	LIBZHL_API bool HasCurseMist();
	LIBZHL_API void RecomputeRoomBounds(bool init);
	LIBZHL_API bool save_entity(Entity * entity, EntitySaveState * data, bool savingMinecartEntity);
	LIBZHL_API void restore_entity(Entity * entity, EntitySaveState * data);
	inline Camera* GetCamera() { return this->_Camera; }
	inline bool GetRedHeartDamage() { return this->_redHeartDamage; }
	inline EntityList* GetEntityList() { return &this->_entityList; }
	inline FXParams* GetFXParams() { return &this->_fxLayers._fxParams; }
	inline float* GetWaterAmount() { return &this->_waterAmount; }
	inline KColor* GetWaterColor() { return &this->_waterColor; }
	inline KColor* GetWaterColorMultiplier() { return &this->_waterColorMultiplier; }
	inline int* GetWaterLerpColorMultiplier() { return &this->_waterLerpColorDuration; }
	
	inline ColorMod* GetFloorColor() { return &this->_floorColor; }
	inline TemporaryEffects* GetTemporaryEffects() {return &this->_temporaryEffects; }
    inline Backdrop* GetBackdrop() { return &this->_backdrop; }
	inline Vector* GetWaterCurrent() {return &this->_waterCurrent; }
    inline RailType* GetRails() { return (RailType*)((char*)this + 0x746c); }
    inline RailType GetRailType(uint16_t gridIndex) { return GetRails()[gridIndex]; }
    inline void SetRailType(uint16_t gridIndex, RailType railType) { GetRails()[gridIndex] = railType; }
    static bool LIBZHL_API IsValidRailType(int rail);
    inline bool IsValidGridIndex(int index, bool includeWalls = true) const {
        return _descriptor->Data->IsValidGridIndex(index, includeWalls);
    }
    bool LIBZHL_API IsChampionBossSeed() const;
    float LIBZHL_API GetChampionBossChance() const;
}; // 0x7898

struct Camera {
	char pad0[0x8c]; // 0x0
	bool _shouldOverride; // 0x8c
	char pad1[0x7]; // 0x8d
	LIBZHL_API void constructor(Room * room);
	LIBZHL_API void SetFocusPosition(Vector * pos);
	LIBZHL_API bool IsPosVisible(Vector * Pos);
	LIBZHL_API void DoUpdate(bool unk);
	LIBZHL_API void SnapToPosition(Vector const & pos);
	LIBZHL_API Vector * ClampedToRoom(Vector & pos);
	LIBZHL_API void UpdateDrag2();
	LIBZHL_API void UpdateUltrasmooth(bool unk);
	LIBZHL_API void destructor();
	inline bool* ShouldOverride() { return &_shouldOverride; }
	
	Camera(Room* room)
	{
		this->constructor(room);
	}
}; // 0x94

struct Capsule {
	Vector _position; // 0x0
	Vector _vec2; // 0x8
	Vector _vec3; // 0x10
	Vector _direction; // 0x18
	float _unkFloat1; // 0x20
	float _unkFloat2; // 0x24
	LIBZHL_API void constructor(Vector * Position, Vector * Multiplier, float Rotation, float size);
	LIBZHL_API void constructor2(Vector * Position, Vector * TargetPosition, float size);
	LIBZHL_API static bool Collide(Capsule * Cap1, Capsule * Cap2, Vector * retHitLocation);
	
	Capsule(Vector* pos, Vector* mult, float rot, float size) {
		this->constructor(pos, mult, rot, size);
	}
	
	Capsule(Vector* pos, Vector* targetPos, float size) {
		this->constructor2(pos, targetPos, size);
	}
	
	inline Vector* GetPosition() { return &_position; }
	inline Vector* GetVec2() { return &_vec2; }
}; // 0x28

struct ChallengeParam {
	std_string _name; // 0x0
	std_set_int _roomset; // 0x18
	std_vector_int _collectibleList; // 0x20
	std_vector_int _trinketList; // 0x2c
	int _startingPill; // 0x38
	int _startingCard; // 0x3c
	int _endStage; // 0x40
	int _playerType; // 0x44
	std_vector_int _achievementList; // 0x48
	int _soulHearts; // 0x54
	int _blackHearts; // 0x58
	int _hearts; // 0x5c
	int _maxHearts; // 0x60
	int _coins; // 0x64
	float _addDamage; // 0x68
	bool _canShoot; // 0x6c
	char pad0[0x3]; // 0x6d
	int _difficulty; // 0x70
	bool _isMegaSatan; // 0x74
	char pad1[0x3]; // 0x75
	float _minFireRate; // 0x78
	bool _maxDamage; // 0x7c
	bool _minShotSpeed; // 0x7d
	bool _bigRange; // 0x7e
	char pad2[0x1]; // 0x7f
	int _pathType; // 0x80
	unsigned int _getCurse; // 0x84
	unsigned int _curseFilter; // 0x88
	std_vector_int _collectibleTwinList; // 0x8c
	char pad3[0xc]; // 0x98
}; // 0xa4

struct Checksum {
	char pad0[0x10]; // 0x0
	LIBZHL_API static unsigned int  Generate(int unused, KAGE_Filesys_FileStream * file, int start, int endOffset);
}; // 0x10

struct ColorModState {
	float r; // 0x0
	float g; // 0x4
	float b; // 0x8
	float a; // 0xc
	float brightness; // 0x10
	float contrast; // 0x14
	ColorModState() : r(1.0f), g(1.0f), b(1.0f), a(0.0f), brightness(0.0f), contrast(1.0f) {}
	ColorModState(float _r, float _g, float _b, float _a, float _brightness, float _contrast ) : r(_r), g(_g), b(_b), a(_a), brightness(_brightness), contrast(_contrast) {}

	ColorModState& operator=(ColorModState const& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		brightness = other.brightness;
		contrast = other.contrast;
		return *this;
	}
	
	bool operator ==(ColorModState const& other) {
		return r == other.r && g == other.g && b == other.b && a == other.a && brightness == other.brightness && contrast == other.contrast;
	}	

	ColorModState& operator+=(ColorModState const& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		brightness += other.brightness;
		contrast += other.contrast;
		return *this;
	}

	ColorModState operator+(ColorModState const& other) {
		return ColorModState(r + other.r, g + other.g, b + other.b, a + other.a, brightness + other.brightness, contrast + other.contrast);
	}
	
	ColorModState& operator-=(ColorModState const& other) {
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		brightness -= other.brightness;
		contrast -= other.contrast;
		return *this;
	}

	ColorModState operator-(ColorModState const& other) {
		return ColorModState(r - other.r, g - other.g, b - other.b, a - other.a, brightness - other.brightness, contrast - other.contrast);
	}

	ColorModState& operator*=(float amount) {
		r *= amount;
		g *= amount;
		b *= amount;
		a *= amount;
		brightness *= amount;
		contrast *= amount;
		return *this;
	}
	
	ColorModState& operator*=(ColorModState const& other) {
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		brightness *= other.brightness;
		contrast *= other.contrast;
		return *this;
	}	
	
	ColorModState operator*(float amount) {
		return ColorModState(r * amount, g * amount, b * amount, a * amount, brightness * amount, contrast * amount);
	}
	
	ColorModState operator*(ColorModState const& other) {
		return ColorModState(r * other.r, g * other.g, b * other.b, a * other.a, brightness * other.brightness, contrast * other.contrast);
	}
	
	ColorModState& operator/=(float amount) {
		r /= amount;
		g /= amount;
		b /= amount;
		a /= amount;
		brightness /= amount;
		contrast /= amount;
		return *this;
	}

	ColorModState operator/(float amount) {
		return ColorModState(r / amount, g / amount, b / amount, a / amount, brightness / amount, contrast / amount);
	}	

	inline float* GetR() { return &this->r; }
	inline float* GetG() { return &this->g; }
	inline float* GetB() { return &this->b; }
	inline float* GetA() { return &this->a; }
	inline float* GetBrightness() { return &this->brightness; }
	inline float* GetContrast() { return &this->contrast; }

}; // 0x18

struct ColorParams {
	int _priority; // 0x0
	ColorMod _color; // 0x4
	int _duration1; // 0x30
	int _duration2; // 0x34
	bool _fadeout; // 0x38
	bool _shared; // 0x39
	char pad0[0x2]; // 0x3a
		ColorParams() : _priority(255), _color(ColorMod()), _duration1(-1), _duration2(-1), _fadeout(false), _shared(false) {}

}; // 0x3c

struct CompletionWidget {
	int CharacterId; // 0x0
	ANM2 anm2; // 0x4
	char pad0[0x4]; // 0x118
	LIBZHL_API void Render(Vector * pos, Vector * scale);
	LIBZHL_API void Update();
	inline ANM2* GetANM2() { return &anm2; } 
}; // 0x11c

struct Console_HistoryEntry {
	std_string _text; // 0x0
	char pad0[0x10]; // 0x18
		inline int GetColorMap() {return *(int*)((char*)this + 0x1C); }

}; // 0x28

struct Console {
	int _state; // 0x0
	char pad0[0x18]; // 0x4
	std_string _input; // 0x1c
	char pad1[0xc]; // 0x34
	deque_console_historyentry _history; // 0x40
	deque_string _commandHistory; // 0x54
	char pad2[0xa0]; // 0x68
	LIBZHL_API void PrintError(std_string const & err);
	LIBZHL_API void RunCommand(std_string & in, std_string * out, Entity_Player * player);
	LIBZHL_API void Print(std_string const & text, unsigned int color, unsigned int fadeTime);
	LIBZHL_API void FillOmnicomplete();
	LIBZHL_API void SubmitInput(bool unk);
	LIBZHL_API void ProcessInput();
	LIBZHL_API void Render();
	LIBZHL_API deque_console_historyentry * RenderHistory(Font * font, float unk, float unk2, bool unk3);
	LIBZHL_API void SaveCommandHistory();
	enum Color: unsigned int {
		WHITE = 0xFFD3D3D3,
		WARNING = 0xFFFCCA03,
	};

	void PrintWarning(const std_string& text)
	{
		this->Print(text, Color::WARNING, 0x96u);
	}
}; // 0x108

struct ConsumableData {
	int coins; // 0x0
	int keys; // 0x4
	int bombs; // 0x8
	bool goldkey; // 0xc
	bool goldbomb; // 0xd
	char pad0[0x2]; // 0xe
	int soulcharges; // 0x10
	int gigabombs; // 0x14
	int poopmana; // 0x18
	int bloodcharges; // 0x1c
}; // 0x20

struct ItemConfig_Costume {
	unsigned int id; // 0x0
	std_string anm2Path; // 0x4
	unsigned int priority; // 0x1c
	bool hasOverlay; // 0x20
	bool isFlying; // 0x21
	bool hasSkinAlt; // 0x22
	char pad0[0x1]; // 0x23
	int skinColor; // 0x24
	bool overwriteColor; // 0x28
	char pad1[0x3]; // 0x29
}; // 0x2c

struct ItemConfig_Item {
	int type; // 0x0
	int id; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	std_string gfxFilename; // 0x38
	int achievementId; // 0x50
	int cacheFlags; // 0x54
	int addMaxhearts; // 0x58
	int addHearts; // 0x5c
	int addSoulHearts; // 0x60
	int addBlackHearts; // 0x64
	int addBombs; // 0x68
	int addKeys; // 0x6c
	int addCoins; // 0x70
	unsigned int maxCharges; // 0x74
	unsigned int maxCooldown; // 0x78
	short int devilprice; // 0x7c
	short int shopPrice; // 0x7e
	ItemConfig_Costume costume; // 0x80
	unsigned int chargeType; // 0xac
	bool special; // 0xb0
	bool passiveCache; // 0xb1
	bool addCostumeOnPickup; // 0xb2
	bool hidden; // 0xb3
	bool persistentEffect; // 0xb4
	bool clearEffectsOnRemove; // 0xb5
	char pad0[0x2]; // 0xb6
	unsigned long long int tags; // 0xb8
	int quality; // 0xc0
	int craftingQuality; // 0xc4
	char pad1[0x18]; // 0xc8
	LIBZHL_API bool IsAvailableEx(unsigned int flags);
	LIBZHL_API bool IsAvailable(unsigned int flags);
}; // 0xe0

struct CostumeSpriteDesc {
	ANM2 _sprite; // 0x0
	ItemConfig_Item * _item; // 0x114
	int _priority; // 0x118
	bool _itemAnimPlay; // 0x11c
	bool _isFlying; // 0x11d
	bool _hasOverlay; // 0x11e
	bool _hasSkinAlt; // 0x11f
	int _defaultSkinColor; // 0x120
	int _skinColor; // 0x124
	bool _overwriteColor; // 0x128
	bool _itemStateOnly; // 0x129
	char pad0[0x2]; // 0x12a
	int _playerType; // 0x12c
}; // 0x130

struct CutsceneEntry {
	int _id; // 0x0
	std_string _name; // 0x4
	char pad0[0x29]; // 0x1c
	bool _isVideo; // 0x45
	char pad1[0x6]; // 0x46
	LIBZHL_API CutsceneEntry * Constructor();
	LIBZHL_API void Destructor();
	LIBZHL_API void Unload();
}; // 0x4c

struct Cutscene {
	int _state; // 0x0
	CutsceneEntry _cutscenes[27]; // 0x4
	int _queuedCutscene; // 0x808
	char pad0[0x34]; // 0x80c
	bool _startCutscene; // 0x840
	char pad1[0xf]; // 0x841
	LIBZHL_API void Init(char * xmlresourcespath);
	LIBZHL_API void Show(int cutsceneid);
}; // 0x850

struct DailyChallenge {
	unsigned int _id; // 0x0
	unsigned int _seed; // 0x4
	bool _isPractice; // 0x8
	char pad0[0x3]; // 0x9
	unsigned int _specialDailyId; // 0xc
	ChallengeParam _params; // 0x10
	LIBZHL_API void Init(unsigned int dailyDate);
	inline ChallengeParam* GetChallengeParams() {return &_params; }
}; // 0xb4

struct DebugRenderer {
	LIBZHL_API Shape * Get(int Index, bool Unk);
}; // 0x1

struct DestinationQuad {
	Vector _topLeft; // 0x0
	Vector _topRight; // 0x8
	Vector _bottomLeft; // 0x10
	Vector _bottomRight; // 0x18
    inline void FlipX()
    {
        std::swap(_topLeft, _topRight);
        std::swap(_bottomLeft, _bottomRight);
    }

    inline void FlipY()
    {
        std::swap(_topLeft, _bottomLeft);
        std::swap(_topRight, _bottomRight);
    }

    inline void Translate(const Vector& offset)
    {
        this->_topLeft += offset;
        this->_topRight += offset;
        this->_bottomLeft += offset;
        this->_bottomRight += offset;
    }

    inline void Scale(const Vector& scale, const Vector& anchor)
    {
        this->Translate(-anchor);

        auto scale_point = [&](Vector& vec) {
            vec.x *= scale.x;
            vec.y *= scale.y;
        };

        scale_point(this->_topLeft);
        scale_point(this->_topRight);
        scale_point(this->_bottomLeft);
        scale_point(this->_bottomRight);

        this->Translate(anchor);
    }

    inline void RotateRadians(const Vector& pivot, float radians)
    {
        float sin = std::sin(radians);
        float cos = std::cos(radians);

        this->Translate(-pivot);

        auto rotate = [](auto& p, float sin, float cos) {
            float x = p.x;
            float y = p.y;
            p.x =  cos * x - sin * y;
            p.y =  sin * x + cos * y;
        };

        rotate(_topLeft, sin, cos);
        rotate(_topRight, sin, cos);
        rotate(_bottomLeft, sin, cos);
        rotate(_bottomRight, sin, cos);

        this->Translate(pivot);
    }

    inline void RotateDegrees(const Vector& pivot, float degrees)
    {
        constexpr float DEGREES_TO_RADIANS = 3.14159265358979323846f / 180.0f;
        float radians = degrees * DEGREES_TO_RADIANS;
        RotateRadians(pivot, radians);
    }

    inline void Shear(const Vector& shear, const Vector& anchor)
    {
        this->Translate(-anchor);

        auto shear_point = [&](Vector& vec) {
            float x = vec.x;
            float y = vec.y;
            vec.x += shear.x * y;
            vec.y += shear.y * x;
        };

        shear_point(this->_topLeft);
        shear_point(this->_topRight);
        shear_point(this->_bottomLeft);
        shear_point(this->_bottomRight);

        this->Translate(anchor);
    }

    inline void ApplyMatrix(const RenderMatrix& matrix, const Vector& anchor)
    {
        this->Translate(-anchor);

        auto apply_matrix = [](Vector& v, const RenderMatrix& m) {
            float x = v.x;
            float y = v.y;
            v.x = (m.a * x + m.b * y + m.tx);
            v.y = (m.c * x + m.d * y + m.ty);
        };

        apply_matrix(this->_topLeft, matrix);
        apply_matrix(this->_topRight, matrix);
        apply_matrix(this->_bottomLeft, matrix);
        apply_matrix(this->_bottomRight, matrix);

        this->Translate(anchor);
    }
}; // 0x20

struct Devolve {
	int type; // 0x0
	unsigned short int variant; // 0x4
	unsigned short int subtype; // 0x6
	float weight; // 0x8
}; // 0xc

struct KAGE_Graphics_ShaderBase {
	void * _vtable; // 0x0
	bool _initialized; // 0x4
	char pad0[0x3]; // 0x5
	KAGE_Graphics_VertexAttributeDescriptor * _vertexAttributes; // 0x8
	unsigned int _numVertexAttributes; // 0xc
	char pad1[0x18]; // 0x10
	LIBZHL_API void Free(bool deletePtr);
	LIBZHL_API void Free_Original(bool deletePtr);
	void virtual_unk16() { }
	LIBZHL_API void Shutdown();
	LIBZHL_API void Shutdown_Original();
    // ShaderBase has pure methods and so it should not be instantiable
    protected:
        KAGE_Graphics_ShaderBase() : _vtable(__ptr_KAGE_Graphics_Shader_vftable) {
            std::memset((void*)((uintptr_t)this + 0x4), 0, sizeof(*this) - 0x4); // the constructor would normally set everything to 0 so we emulate that here
        };

    public:
        ~KAGE_Graphics_ShaderBase() {
            this->Free(false);
        }
   
}; // 0x28

struct KAGE_Graphics_Shader : public KAGE_Graphics_ShaderBase {
	unsigned int _glProgram; // 0x28
        KAGE_Graphics_Shader() {
            _vtable = __ptr_KAGE_Graphics_Shader_vftable;
            this->_glProgram = -1;
        }

        ~KAGE_Graphics_Shader() {
            if (this->_initialized)
            {
                // We must call Shutdown manually, as the Free method only calls the base class Shutdown, causing _glProgram to leak.
                // _glProgram is not reset to a default value on Shutdown, so we can't be sure that we are not deleting an already deleted glProgram,
                // but based on usage the only time glDeleteProgram is called is on Shutdown (where _initialized is set to false),
                // and when Initialize fails (where _initialized is left as false).
                this->Shutdown();
            }
        }

        // Use this if you want to reload the shader, as none of the methods gracefully handle a double initialization, causing some resources to leak.
        void HardReset()
        {
            this->~KAGE_Graphics_Shader();
            new (this) KAGE_Graphics_Shader();
        }

        inline int GetShaderId() { return this->_glProgram; }
   
}; // 0x2c

struct ModShader {
	std_string name; // 0x0
	KAGE_Graphics_Shader shader; // 0x18
	char pad0[0x34]; // 0x44
}; // 0x78

struct ModEntry {
	std_string _directory; // 0x0
	std_string _name; // 0x18
	std_string _resourcesDirectory; // 0x30
	std_string _contentDirectory; // 0x48
	std_string _dataDirectory; // 0x60
	std_string _metadataVersion; // 0x78
	std_string _metadataWorkshopID; // 0x90
	std_string _metadataDescription; // 0xa8
	std_string _metadataVisibility; // 0xc0
	char pad0[0x24]; // 0xd8
	bool _enabled; // 0xfc
	bool _loaded; // 0xfd
	char pad1[0xe06]; // 0xfe
	LIBZHL_API void constructor();
	LIBZHL_API void GetContentPath(std_string * result, std_string const * filePath);
	LIBZHL_API void WriteMetadata();
	inline std_string GetDir() { return this->_directory; }
	inline std_string GetName() { return this->_name; }
	inline char* GetVersion() { return (char*)this->_metadataVersion.c_str(); } //these last 2 are consistent
	inline char* GetId() { return (char*)this->_metadataWorkshopID.c_str(); } //these last 2 are consistent (this is the one I needed anyway)
	
	inline bool IsEnabled() { return this->_enabled; }
	inline void SetEnabled(bool x) { this->_enabled = x; }

	inline ANM2* GetDeathEnemiesAnm2() { return (ANM2*)((char*)this + 0xDF0); }

	inline std::list<ModShader*>* GetShaders() {
		return (std::list<ModShader*>*)((char*)this + 0xe4);
	}
}; // 0xf04

struct EntityConfig_Entity {
	int id; // 0x0
	int variant; // 0x4
	int subtype; // 0x8
	std_string name; // 0xc
	float shadowSize; // 0x24
	float collisionDamage; // 0x28
	bool isBoss; // 0x2c
	char pad0[0x3]; // 0x2d
	int bossID; // 0x30
	bool canBeChampion; // 0x34
	char pad1[0x3]; // 0x35
	float collisionRadius; // 0x38
	Vector collisionRadiusMulti; // 0x3c
	float mass; // 0x44
	unsigned int gridCollisionPoints; // 0x48
	float friction; // 0x4c
	float baseHP; // 0x50
	float stageHP; // 0x54
	bool shutDoors; // 0x58
	char pad2[0x3]; // 0x59
	unsigned int gibsAmount; // 0x5c
	unsigned int gibFlags; // 0x60
	int portrait; // 0x64
	char pad3[0xc]; // 0x68
	std_string anm2Path; // 0x74
	char pad4[0x18]; // 0x8c
	vector_Devolve devolve; // 0xa4
	char pad5[0x4]; // 0xb0
	std_string gridCollisionClassString; // 0xb4
	bool reroll; // 0xcc
	bool hasFloorAlts; // 0xcd
	char pad6[0x2]; // 0xce
	unsigned int collisionInterval; // 0xd0
	char pad7[0x4]; // 0xd4
	unsigned int tags; // 0xd8
	char pad8[0x4]; // 0xdc
	float shieldStrength; // 0xe0
	char pad9[0x4]; // 0xe4
	bool bestiary; // 0xe8
	char pad10[0x3]; // 0xe9
	Vector bestiaryOffset; // 0xec
	float bestiaryScale; // 0xf4
	std_string bestiaryAnm2Path; // 0xf8
	std_string bestiaryAnim; // 0x110
	std_string bestiaryOverlay; // 0x128
	std_string bestiaryFloorAlt; // 0x140
	int bestiaryParentType; // 0x158
	int bestiaryParentVariant; // 0x15c
	ModEntry * modEntry; // 0x160
	char pad11[0x4]; // 0x164
}; // 0x168

struct EntityConfig_Player {
	int _id; // 0x0
	std_string _name; // 0x4
	std_string _skinPath; // 0x1c
	std_string _nameImagePath; // 0x34
	std_string _portraitPath; // 0x4c
	std_string _unkString; // 0x64
	std_string _extraPortraitPath; // 0x7c
	std_string _costumeSuffixName; // 0x94
	int _costumeID; // 0xac
	int _heart; // 0xb0
	int _armor; // 0xb4
	int _blackHeart; // 0xb8
	int _coins; // 0xbc
	int _bombs; // 0xc0
	int _keys; // 0xc4
	int _card; // 0xc8
	int _pill; // 0xcc
	bool _canShoot; // 0xd0
	char pad0[0x3]; // 0xd1
	std_vector_int _collectibles; // 0xd4
	int _trinket; // 0xe0
	int _skinColor; // 0xe4
	int _achievement; // 0xe8
	int _brokenHeart; // 0xec
	unsigned int _pocketActiveID; // 0xf0
	std_string _birthrightDescription; // 0xf4
	std_string _bSkinParentName; // 0x10c
	int _moddedTaintedPlayerID; // 0x124
	bool _hidden; // 0x128
	char pad1[0x3]; // 0x129
	ModEntry * _modEntry; // 0x12c
	bool _renderCustomBackground; // 0x130
	char pad2[0x3]; // 0x131
	ANM2 * _moddedMenuBackgroundANM2; // 0x134
	ANM2 * _moddedMenuPortraitANM2; // 0x138
	ANM2 * _moddedGameOverANM2; // 0x13c
	ANM2 * _moddedCoopMenuANM2; // 0x140
	ANM2 * _moddedControlsANM2; // 0x144
	LIBZHL_API std_string GetDisplayName(void * ptr);
		inline int* GetAchievement() { return &this->_achievement; }
		inline ANM2* GetModdedMenuBackgroundANM2() { return *(ANM2**)((char*)this + 0x134); }
		inline ANM2* GetModdedMenuPortraitANM2() { return *(ANM2**)((char*)this + 0x138); }

}; // 0x148

struct EntityConfig_Boss_Alt {
	int stageId; // 0x0
	std_string portraitPath; // 0x4
        EntityConfig_Boss_Alt()
        {
            stageId = 0;
        }
   
}; // 0x1c

struct EntityConfig_Boss {
	int bossID; // 0x0
	std_string name; // 0x4
	std_string namePath; // 0x1c
	std_string portraitPath; // 0x34
	Vector pivot; // 0x4c
	int achievement; // 0x54
	vector_EntityConfig_Boss_Alt alts; // 0x58
		EntityConfig_Boss()
		{
			bossID = 0;
			pivot.x = 0.0f;
			pivot.y = 0.0f;
			achievement = 0;
		}

}; // 0x64

struct EntityConfig_Baby {
	int id; // 0x0
	std_string name; // 0x4
	std_string gfx; // 0x1c
	int achievementID; // 0x34
}; // 0x38

struct EntityConfig_EntityEntry {
	unsigned int unk; // 0x0
	EntityConfig_Entity entity; // 0x4
}; // 0x16c

struct EntityConfig {
	std_map_uint_EntityConfigEntityEntry _entities; // 0x0
	char pad0[0x18]; // 0x8
	vector_EntityConfig_Boss _bosses; // 0x20
	vector_string _edenHair; // 0x2c
	char pad1[0x18]; // 0x38
	LIBZHL_API void Load(char * xmlpath, ModEntry * param_2);
	LIBZHL_API void LoadPlayers(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadBabies(char * xmlpath);
	LIBZHL_API EntityConfig_Entity * GetEntity(int id, int variant, int subtype);
	LIBZHL_API EntityConfig_Entity * GetBestiaryConfig(int id, int variant);
        inline std::vector<EntityConfig_Player>* GetPlayers() { return (std::vector<EntityConfig_Player>*)((char*)this + 0x8); }
        inline EntityConfig_Player* GetPlayer(const int ptype) {
            if (ptype < 0 || ptype >= (int)this->GetPlayers()->size()) {
		        return nullptr;
	        }
            return &this->GetPlayers()->at(ptype);
        }
        inline std::vector<EntityConfig_Baby>* GetBabies() { return (std::vector<EntityConfig_Baby>*)((char*)this + 0x14); }
        inline EntityConfig_Baby* GetBaby(const int id) {
            if (id < 0 || id >= (int)this->GetBabies()->size()) {
		        return nullptr;
	        }
            return &this->GetBabies()->at(id);
        }
        inline std::vector<EntityConfig_Boss>* GetBosses() { return &this->_bosses; }
   
}; // 0x50

struct EntityDesc {
	unsigned int _type; // 0x0
	unsigned int _variant; // 0x4
	unsigned int _subtype; // 0x8
	int _championId; // 0xc
	float _health; // 0x10
	float _maxHealth; // 0x14
	bool _playerControlled; // 0x18
	char pad0[0x3]; // 0x19
	EntityDesc(unsigned int type = 0, unsigned int variant = 0, unsigned int subtype = 0, int champion = -1, float health = .0f, float maxHealth = .0f, bool playerControlled = false) : _type(type), _variant(variant), _subtype(subtype), _championId(champion), _health(health), _maxHealth(_maxHealth), _playerControlled(playerControlled) {}
}; // 0x1c

struct KAGE_SmartPointer_EntitySaveState {
	EntitySaveState * saveState; // 0x0
	KAGE_ReferenceCount_EntitySaveState * counter; // 0x4
	LIBZHL_API KAGE_SmartPointer_EntitySaveState & SetP(EntitySaveState * other);
    KAGE_SmartPointer_EntitySaveState() {
        saveState = nullptr;
        counter = nullptr;
    }
   
}; // 0x8

struct Entity_Pickup : public Entity {
	ANM2 _priceANM2; // 0x410
	char pad0[0xa]; // 0x524
	bool _isForceBlind; // 0x52e
	char pad1[0x5]; // 0x52f
	int _price; // 0x534
	char pad2[0x8]; // 0x538
	int _timeout; // 0x540
	char pad3[0x10]; // 0x544
	int _dropDelay; // 0x554
	char pad4[0x38]; // 0x558
	Entity_Effect * _pickupGhost; // 0x590
	Entity_Pickup * _megaChestCollectible[2]; // 0x594
	int _varData; // 0x59c
	unsigned int _cycleCollectibleList[8]; // 0x5a0
	unsigned int _cycleCollectibleCount; // 0x5c0
	char pad5[0x4]; // 0x5c4
	KAGE_SmartPointer_EntitySaveState _flipSaveState; // 0x5c8
	ANM2 _altPedestalANM2; // 0x5d0
	char pad6[0xc]; // 0x6e4
	LIBZHL_API void Morph(int EntityType, int Variant, int SubType, bool KeepPrice, bool KeepSeed, bool IgnoreModifiers);
	LIBZHL_API void TriggerShopPurchase(Entity_Player * player, int spentMoney);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void SetAlternatePedestal(int pedestalType);
	LIBZHL_API bool TryRemoveCollectible();
	LIBZHL_API void SetForceBlind(bool setBlind);
	LIBZHL_API int SetNewOptionsPickupIndex();
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API bool TryInitOptionCycle(int numCycle);
	LIBZHL_API int GetCoinValue();
	LIBZHL_API bool CanReroll();
	LIBZHL_API bool CanJeraDuplicate();
	LIBZHL_API static bool CanRerollVariant(int variant, int subtype);
	LIBZHL_API void MakeShopItem(int shopId);
	LIBZHL_API bool TryFlip(Entity_Player * unusedPlayer, unsigned int unusedSeed);
	LIBZHL_API static Vector * GetRandomPickupVelocity(Vector const & buffer, Vector * position, RNG * rng, unsigned int ePickupVelType);
	LIBZHL_API void Constructor();
	LIBZHL_API int GetAlternatePedestal();
	LIBZHL_API LootList GetLootList(bool ShouldAdvance, Entity_Player * player);
	LIBZHL_API void UpdatePickupGhosts();
	LIBZHL_API void TriggerTheresOptionsPickup();
	LIBZHL_API bool TryOpenChest(Entity_Player * player);
	LIBZHL_API static bool IsChest(unsigned int variant);
	LIBZHL_API bool CanBePickedUp(bool ignorePrice);
	LIBZHL_API bool CanPickupShopItem(Entity_Player * player);
	LIBZHL_API static void SetupCollectibleGraphics(ANM2 * pedestalSprite, int layer, CollectibleType id, unsigned int seed, bool blind);
	LIBZHL_API void ReloadGraphics(bool ignoreBlind);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	void virtual_unk17() { }
	LIBZHL_API void Init(unsigned int Type, int Variant, int Subtype, unsigned int Seed);
	LIBZHL_API void Original_Init(unsigned int Type, int Variant, int Subtype, unsigned int Seed);
	void virtual_unk18() { }
	void virtual_unk19() { }
	void virtual_unk20() { }
	void virtual_unk21() { }
	void virtual_unk22() { }
	void virtual_unk23() { }
	void virtual_unk24() { }
	void virtual_unk25() { }
	void virtual_unk26() { }
	void virtual_unk27() { }
	void virtual_unk28() { }
	void virtual_unk29() { }
	void virtual_unk30() { }
	void virtual_unk31() { }
	void virtual_unk32() { }
	void virtual_unk33() { }
	void virtual_unk34() { }
	void virtual_unk35() { }
	void virtual_unk36() { }
	void virtual_unk37() { }
	void virtual_unk38() { }
	void virtual_unk39() { }
	inline bool IsBlind() { return this->_isForceBlind; }
	inline int* GetDropDelay() { return &this->_dropDelay; }
	inline int* GetVarData() { return &this->_varData; }

	static inline bool ShouldIgnoreModifiers() { return s_EntityPickup_IgnoreModifiers != 0; }
	static inline void BeginIgnoreModifiers() { s_EntityPickup_IgnoreModifiers++; }
	static inline void EndIgnoreModifiers() { s_EntityPickup_IgnoreModifiers--; }
}; // 0x6f0

struct NPCAI_Pathfinder {
	Entity * _entity; // 0x0
	Vector _targetRelated1; // 0x4
	Vector _targetRelated2; // 0xc
	int _directionMaybe; // 0x14
	int _unkCounter; // 0x18
	int _framecountMaybe; // 0x1c
	int _gridIndex; // 0x20
	float _interpFrameRelated; // 0x24
	int _countdownMaybe; // 0x28
	int _unk_pathmarkers[448]; // 0x2c
	bool _hasDirectPath; // 0x72c
	bool _unkBool; // 0x72d
	char pad0[0x2]; // 0x72e
	Vector _posBackupMaybe; // 0x730
	bool _canCrushRocks; // 0x738
	char pad1[0x3]; // 0x739
	int _evadeMovementCountdown; // 0x73c
	float _unkFloat2; // 0x740
	float _unkFloat; // 0x744
	char pad2[0x8]; // 0x748
	LIBZHL_API void Reset();
	LIBZHL_API void FindGridPath(Vector * Pos, float Speed, int PathMarker, bool UseDirectPath);
	LIBZHL_API void EvadeTarget(Vector * TargetPos, bool IgnoreStatusEffects);
	LIBZHL_API void MoveRandomlyAxisAligned(float Speed, bool IgnoreStatusEffects);
	LIBZHL_API bool MoveRandomly(bool IgnoreStatusEffects);
	LIBZHL_API void MoveRandomlyBoss(bool IgnoreStatusEffects);
	LIBZHL_API void ResetMovementTarget();
	LIBZHL_API void UpdateGridIndex();
	LIBZHL_API bool HasPathToPos(Vector * Position, bool IgnorePoop);
	LIBZHL_API void SimulatePlayerMovement(Vector * movementInput, float speed, bool unused);
}; // 0x750

struct Entity_Familiar : public Entity {
	Entity_Player * _player; // 0x410
	char pad0[0x1e4]; // 0x414
	int _moveDelayNum; // 0x5f8
	NPCAI_Pathfinder _pathfinder; // 0x5fc
	char pad1[0x28]; // 0xd4c
	bool _isFollower; // 0xd74
	bool _isDelayed; // 0xd75
	char pad2[0x12]; // 0xd76
	int _state; // 0xd88
	char pad3[0x24]; // 0xd8c
	Weapon * _weapon; // 0xdb0
	bool _isLilDelirium; // 0xdb4
	char pad4[0x11f]; // 0xdb5
	ItemConfig_Item * _item; // 0xed4
	char pad5[0x4]; // 0xed8
	ColorMod _dirtColor; // 0xedc
	char pad6[0x4]; // 0xf08
	int _wispCollectibleType; // 0xf0c
	char pad7[0x20]; // 0xf10
	LIBZHL_API void AddToFollowers();
	LIBZHL_API void AddToDelayed();
	LIBZHL_API void Constructor();
	LIBZHL_API int GetFollowerPriority();
	LIBZHL_API void GetMultiplier();
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void Shoot();
	LIBZHL_API bool TryAimAtMarkedTarget(Vector * AimDirection, int * eDirection, Vector * TargetPosBuffer);
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API void UpdateDirtColor(bool Immediate);
	LIBZHL_API Entity_Tear * FireProjectile(Vector const & AimDirection, bool Unk);
	LIBZHL_API Entity_Laser * FireBrimstone(Vector const & AimDirection, bool Unk);
	LIBZHL_API Entity_Laser * FireTechLaser(Vector const & AimDirection);
	LIBZHL_API bool CanBeDamagedByEnemy();
	LIBZHL_API bool CanBlockProjectiles();
	LIBZHL_API void RemoveFromPlayer(bool UnusedRemoveFamiliar);
	LIBZHL_API bool CanCharm();
	LIBZHL_API void WispInit();
	LIBZHL_API bool wisp_kill();
	LIBZHL_API void delirium_morph();
	LIBZHL_API static int __fastcall GetRandomWisp(RNG & rng);
	LIBZHL_API void RestoreState(FamiliarData * saveData);
	LIBZHL_API void ai_buddy_inbox();
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk40() { }
	void virtual_unk41() { }
	void virtual_unk42() { }
	void virtual_unk43() { }
	void virtual_unk44() { }
	void virtual_unk45() { }
	void virtual_unk46() { }
	void virtual_unk47() { }
	void virtual_unk48() { }
	void virtual_unk49() { }
	void virtual_unk50() { }
	void virtual_unk51() { }
	void virtual_unk52() { }
	void virtual_unk53() { }
	void virtual_unk54() { }
	void virtual_unk55() { }
	void virtual_unk56() { }
	void virtual_unk57() { }
	void virtual_unk58() { }
	void virtual_unk59() { }
	void virtual_unk60() { }
	void virtual_unk61() { }
	void virtual_unk62() { }
	void virtual_unk63() { }
	inline Entity_Player* GetPlayer() { return this->_player; }
	inline NPCAI_Pathfinder* GetPathFinder() { return &this->_pathfinder; }
	inline Weapon** GetWeapon() { return &this->_weapon; }
}; // 0xf30

struct EntityFactory {
	char pad0[0x130008]; // 0x0
	Entity_Familiar _familiar[64]; // 0x130008
	char pad1[0x1eaa28]; // 0x16cc08
	Entity_Pickup _pickup[512]; // 0x357630
	char pad2[0x260630]; // 0x435630
	LIBZHL_API Entity * Create(unsigned int type, bool force);
}; // 0x695c60

struct EntityRef {
	int _type; // 0x0
	int _variant; // 0x4
	int _spawnerType; // 0x8
	unsigned int _spawnerVariant; // 0xc
	Vector _position; // 0x10
	Vector _velocity; // 0x18
	unsigned int _flags; // 0x20
	Entity * _entity; // 0x24
	LIBZHL_API void constructor(Entity * entity);
    EntityRef() { this->constructor(nullptr); }
    EntityRef(Entity* entity) { this->constructor(entity); }
 
}; // 0x28

struct EntitySaveState {
	int type; // 0x0
	int variant; // 0x4
	int subtype; // 0x8
	unsigned int intStorage1; // 0xc
	unsigned int intStorage2; // 0x10
	unsigned int intStorage3; // 0x14
	int intStorage4; // 0x18
	int intStorage5; // 0x1c
	short int gridSpawnIdx; // 0x20
	bool boolStorage1; // 0x22
	bool boolStorage2; // 0x23
	unsigned int intStorage6; // 0x24
	Vector targetPosition; // 0x28
	unsigned int _intStorage7; // 0x30
	unsigned int _initSeed; // 0x34
	unsigned int _dropSeed; // 0x38
	int spawnerType; // 0x3c
	int spawnerVariant; // 0x40
	char pad0[0xc]; // 0x44
	float floatStorage1; // 0x50
	float floatStorage2; // 0x54
	char pad1[0x4]; // 0x58
	unsigned int intStorage8; // 0x5c
	char byteStorage; // 0x60
	char pad2[0xb]; // 0x61
	KAGE_SmartPointer_EntitySaveState entitySaveState; // 0x6c
	char pad3[0x4]; // 0x74
	LIBZHL_API void constructor();
	LIBZHL_API void destructor();
		EntitySaveState() {
			this->constructor();
		}

}; // 0x78

struct Entity_Bomb : public Entity {
	int _explosionCountdown1; // 0x410
	char pad0[0x8]; // 0x414
	float _fallSpeed; // 0x41c
	float _fallAcceleration; // 0x420
	char pad1[0x4]; // 0x424
	float _rocketAngle; // 0x428
	float _rocketSpeed; // 0x42c
	char pad2[0x4]; // 0x430
	float _scale; // 0x434
	char pad3[0x24]; // 0x438
	bool _prismTouched; // 0x45c
	char pad4[0x6]; // 0x45d
	bool _loadCostumes; // 0x463
	ANM2 _bombCostumesSprites[5]; // 0x464
	std_vector_uint _hitList; // 0x9c8
	char pad5[0x4]; // 0x9d4
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk64() { }
	void virtual_unk65() { }
	void virtual_unk66() { }
	void virtual_unk67() { }
	void virtual_unk68() { }
	void virtual_unk69() { }
	void virtual_unk70() { }
	void virtual_unk71() { }
	void virtual_unk72() { }
	void virtual_unk73() { }
	void virtual_unk74() { }
	void virtual_unk75() { }
	void virtual_unk76() { }
	void virtual_unk77() { }
	void virtual_unk78() { }
	void virtual_unk79() { }
	void virtual_unk80() { }
	void virtual_unk81() { }
	void virtual_unk82() { }
	void virtual_unk83() { }
	void virtual_unk84() { }
	void virtual_unk85() { }
	void virtual_unk86() { }
	void virtual_unk87() { }
	void virtual_unk88() { }
    inline int* GetExplosionCountdown() { return &this->_explosionCountdown1; }
    void LIBZHL_API Entity_Bomb::UpdateDirtColor();
}; // 0x9d8

struct Entity_Effect : public Entity {
	char pad0[0x10]; // 0x410
	BitSet128 _varData; // 0x420
	char pad1[0x20]; // 0x430
	int _state; // 0x450
	char pad2[0x8]; // 0x454
	int _timeout; // 0x45c
	int _lifespan; // 0x460
	char pad3[0x2c]; // 0x464
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API static Entity_Effect * CreateTimer(void * fn, unsigned int delay, unsigned int times, bool persistent);
	LIBZHL_API static Entity_Effect * CreateLootPreview(LootList * lootlist, Vector * pos, Entity * owner, Entity_Effect * effect);
	LIBZHL_API void constructor();
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk89() { }
	void virtual_unk90() { }
	void virtual_unk91() { }
	void virtual_unk92() { }
	void virtual_unk93() { }
	void virtual_unk94() { }
	void virtual_unk95() { }
	void virtual_unk96() { }
	void virtual_unk97() { }
	void virtual_unk98() { }
	void virtual_unk99() { }
	void virtual_unk100() { }
	void virtual_unk101() { }
	void virtual_unk102() { }
	void virtual_unk103() { }
	void virtual_unk104() { }
	void virtual_unk105() { }
	void virtual_unk106() { }
	void virtual_unk107() { }
	void virtual_unk108() { }
	void virtual_unk109() { }
	void virtual_unk110() { }
	void virtual_unk111() { }
	void virtual_unk112() { }
	void virtual_unk113() { }
}; // 0x490

struct Entity_Knife : public Entity {
	BitSet128 _tearFlags; // 0x410
	char pad0[0x24]; // 0x420
	float _knifeDistance; // 0x444
	float _knifeVelocity; // 0x448
	char pad1[0x19]; // 0x44c
	bool _isSwinging; // 0x465
	char pad2[0x5e]; // 0x466
	float _pathOffset; // 0x4c4
	float _pathFollowSpeed; // 0x4c8
	char pad3[0x19]; // 0x4cc
	bool _prismApplied; // 0x4e5
	bool _multidimensionalApplied; // 0x4e6
	char pad4[0x3]; // 0x4e7
	bool _isSpinAttack; // 0x4ea
	char pad5[0x98d]; // 0x4eb
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API std_vector_uint * GetHitEntities();
	LIBZHL_API void Constructor();
	LIBZHL_API Entity_Player * GetPlayer();
	LIBZHL_API void InitHomingPath(Vector direction, Entity * source, float pathOffset);
	LIBZHL_API void Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Original_Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk114() { }
	void virtual_unk115() { }
	void virtual_unk116() { }
	void virtual_unk117() { }
	void virtual_unk118() { }
	void virtual_unk119() { }
	void virtual_unk120() { }
	void virtual_unk121() { }
	void virtual_unk122() { }
	void virtual_unk123() { }
	void virtual_unk124() { }
	void virtual_unk125() { }
	void virtual_unk126() { }
	void virtual_unk127() { }
	void virtual_unk128() { }
	void virtual_unk129() { }
	void virtual_unk130() { }
	void virtual_unk131() { }
	void virtual_unk132() { }
	void virtual_unk133() { }
	void virtual_unk134() { }
	void virtual_unk135() { }
	void virtual_unk136() { }
	void virtual_unk137() { }
}; // 0xe78

struct HomingLaser_Bezier {
	char pad0[0x18]; // 0x0
}; // 0x18

struct HomingLaser {
	Entity * _entity; // 0x0
	Vector _origin; // 0x4
	Vector _endPoint; // 0xc
	float _unkFloat1; // 0x14
	unsigned int _sampleNum; // 0x18
	std_vector_vector2 _samples; // 0x1c
	std_vector_vector2 _nonOptimizedSamples; // 0x28
	std_vector_int _unkVec; // 0x34
	int _unkInt; // 0x40
	float _unkFloat2; // 0x44
	vector_HomingLaserBezier _bezier; // 0x48
	LIBZHL_API void CalculateSamples(float param_2);
}; // 0x54

struct Entity_Laser : public Entity {
	char pad0[0x18]; // 0x410
	BitSet128 _tearFlags; // 0x428
	char pad1[0x20]; // 0x438
	int _timeout; // 0x458
	char pad2[0x1]; // 0x45c
	bool _sampleLaser; // 0x45d
	bool _shrink; // 0x45e
	char pad3[0x5]; // 0x45f
	HomingLaser _homingLaser; // 0x464
	char pad4[0x18]; // 0x4b8
	float _maxDistance; // 0x4d0
	unsigned int _homingType; // 0x4d4
	char pad5[0x8]; // 0x4d8
	float _scale; // 0x4e0
	bool _disableFollowParent; // 0x4e4
	char pad6[0x1b]; // 0x4e5
	bool _multidimensionalTouched; // 0x500
	char pad7[0x13]; // 0x501
	bool _prismTouched; // 0x514
	bool _oneHit; // 0x515
	char pad8[0x2]; // 0x516
	bool _disableInitSound; // 0x518
	char pad9[0x3]; // 0x519
	float _damageMultiplier; // 0x51c
	std_vector_uint _hitList; // 0x520
	char pad10[0x34]; // 0x52c
	int _chainedLasers; // 0x560
	char pad11[0x4]; // 0x564
	LIBZHL_API void ResetSpriteScale();
	LIBZHL_API void DoDamage(Entity * entity, float damage);
	LIBZHL_API bool CanDamageEntity(Entity * entity);
	LIBZHL_API void RotateToAngle(float angle, float speed);
	LIBZHL_API void ClearLaserSamples();
	LIBZHL_API void Constructor();
	LIBZHL_API ColorMod * CalculateTearColor(ColorMod * buffer);
	LIBZHL_API void PlayInitSound();
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int seed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int seed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	void virtual_unk138() { }
	void virtual_unk139() { }
	void virtual_unk140() { }
	void virtual_unk141() { }
	void virtual_unk142() { }
	void virtual_unk143() { }
	void virtual_unk144() { }
	void virtual_unk145() { }
	void virtual_unk146() { }
	void virtual_unk147() { }
	void virtual_unk148() { }
	void virtual_unk149() { }
	void virtual_unk150() { }
	void virtual_unk151() { }
	void virtual_unk152() { }
	void virtual_unk153() { }
	void virtual_unk154() { }
	void virtual_unk155() { }
	void virtual_unk156() { }
	void virtual_unk157() { }
	void virtual_unk158() { }
	void virtual_unk159() { }
	void virtual_unk160() { }
	inline uint32_t* GetHomingType() { return &this->_homingType; }
	inline float* GetScale() { return &this->_scale; }
	
	inline int* GetTimeout() { return &this->_timeout; }
	inline bool* GetShrink() { return &this->_shrink; }
	inline bool* GetDisableFollowParent() { return &this->_disableFollowParent; }
	inline bool* GetOneHit() { return &this->_oneHit; }
	inline std_vector_uint* GetHitList() { return &this->_hitList; }

}; // 0x568

struct Entity_NPC : public Entity {
	int _stateFrame; // 0x410
	NPCAI_Pathfinder _pathfinder; // 0x414
	int _state; // 0xb64
	char pad0[0x38]; // 0xb68
	int _projectileCooldown; // 0xba0
	int _projectileDelay; // 0xba4
	char pad1[0x8]; // 0xba8
	Vector _v1; // 0xbb0
	Vector _v2; // 0xbb8
	int _i1; // 0xbc0
	int _i2; // 0xbc4
	unsigned int _deliriumBossType; // 0xbc8
	unsigned int _deliriumBossVariant; // 0xbcc
	unsigned short int _deliriumTransformationTimer; // 0xbd0
	unsigned char _deliriumRemainingAttacks; // 0xbd2
	unsigned char _deliriumState; // 0xbd3
	char pad2[0x4]; // 0xbd4
	unsigned int _deliriumAttackID; // 0xbd8
	unsigned char _deliriumAttackAngle; // 0xbdc
	char pad3[0x3]; // 0xbdd
	unsigned int _deliriumCycleID; // 0xbe0
	char pad4[0x59]; // 0xbe4
	bool _isBoss; // 0xc3d
	char pad5[0x2]; // 0xc3e
	float _shieldStrength; // 0xc40
	char pad6[0x30]; // 0xc44
	unsigned short int _championRegenTimer; // 0xc74
	char pad7[0x2]; // 0xc76
	int _bosscoloridx; // 0xc78
	char pad8[0x30]; // 0xc7c
	ColorMod _dirtColor; // 0xcac
	char pad9[0x228]; // 0xcd8
	std_vector_uint _hitList; // 0xf00
	char pad10[0x10]; // 0xf0c
	int _controllerID; // 0xf1c
	char pad11[0x20]; // 0xf20
	Entity_Player * _sirenPlayerEntity; // 0xf40
	char pad12[0xc]; // 0xf44
	Entity_Effect * _pickupGhostsEntity; // 0xf50
	char pad13[0xc]; // 0xf54
	LIBZHL_API void Morph(int EntityType, int Variant, int SubType, int Championid);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void UpdateDirtColor(bool immediate);
	LIBZHL_API static bool Redirect(int * EntityType, int * Variant);
	LIBZHL_API bool TryForceTarget(Entity * Target, int Duration);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void FireProjectiles(Vector * position, Vector * velocity, unsigned int mode, ProjectileParams * params);
	LIBZHL_API void Constructor();
	LIBZHL_API Entity_Projectile * FireBossProjectiles(int numProjectiles, Vector const & targetPos, float trajectoryModifier, ProjectileParams const & params);
	LIBZHL_API Entity_Projectile * FireGridEntity(ANM2 * anm2, GridEntityDesc * desc, Vector * velocity, unsigned int backdrop);
	LIBZHL_API void PlaySound(int id, float volume, int framedelay, bool loop, float pitch);
	LIBZHL_API Entity * GetPlayerTarget();
	LIBZHL_API bool CheckPlayerProximity(Vector * pos, float margin);
	LIBZHL_API void CreateBling();
	LIBZHL_API void CreateGoldParticles(unsigned int count);
	LIBZHL_API Entity_Effect * MakeBloodCloud(Vector * pos, ColorMod * color);
	LIBZHL_API void MakeBloodSplash();
	LIBZHL_API void SetScale(float scale);
	LIBZHL_API static Entity_NPC * ThrowMaggot(Vector * origin, float yOffset, Vector * velocity, float fallingSpeed);
	LIBZHL_API static Entity_NPC * ThrowMaggotAtPos(Vector * pos, Vector * targetPos, float yOffset);
	LIBZHL_API static Entity_NPC * ShootMaggotProjectile(Vector * pos, float yOffset, Vector * dir, float fallingSpeed);
	LIBZHL_API static Entity_NPC * ThrowStrider(Vector * pos, Entity * spanwer, Vector * targetPos);
	LIBZHL_API static Entity_NPC * ThrowRockSpider(Vector * pos, Vector * targetPos, Entity * spanwer, int variant, float yPosOffset);
	LIBZHL_API static Entity_NPC * ThrowLeech(Vector * pos, Entity * spanwer, float yPosOffset, Vector * targetPos, bool big);
	LIBZHL_API LootList shopkeeper_get_loot(bool ShouldAdvance);
	LIBZHL_API LootList fireplace_get_loot(bool ShouldAdvance);
	LIBZHL_API static int __stdcall FindTargetPit(Vector * Pos1, Vector * Pos2, unsigned int PitIndex);
	LIBZHL_API bool TrySplit(float defaultDamage, EntityRef * source, bool doScreenEffects);
	LIBZHL_API void load_graphics(bool param_1);
	LIBZHL_API void translate_gfx_path(std_string & returnString, std_string & input);
	LIBZHL_API void Hornfel_UpdateAI();
	LIBZHL_API void Hornfel_UpdateFrame();
	LIBZHL_API static void __cdecl moms_heart_mausoleum_death();
	LIBZHL_API void UpdatePickupGhosts();
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API void ResetColor();
	LIBZHL_API void Original_ResetColor();
	void virtual_unk161() { }
	void virtual_unk162() { }
	void virtual_unk163() { }
	void virtual_unk164() { }
	void virtual_unk165() { }
	void virtual_unk166() { }
	void virtual_unk167() { }
	void virtual_unk168() { }
	void virtual_unk169() { }
	void virtual_unk170() { }
	void virtual_unk171() { }
	void virtual_unk172() { }
	void virtual_unk173() { }
	void virtual_unk174() { }
	void virtual_unk175() { }
	void virtual_unk176() { }
	void virtual_unk177() { }
	void virtual_unk178() { }
	void virtual_unk179() { }
	void virtual_unk180() { }
	void virtual_unk181() { }
	void virtual_unk182() { }
    inline ColorMod* GetDirtColor() { return &this->_dirtColor; }
    inline uint32_t* GetDeliriumBossType() { return &this->_deliriumBossType; }
    inline uint32_t* GetDeliriumBossVariant() { return &this->_deliriumBossVariant; }
    inline uint16_t* GetDeliriumTransformationTimer() { return &this->_deliriumTransformationTimer; }
    inline uint8_t* GetDeliriumRemainingAttacks() { return &this->_deliriumRemainingAttacks; }
    inline uint8_t* GetDeliriumState() { return &this->_deliriumState; }
    inline uint32_t* GetDeliriumAttackID() { return &this->_deliriumAttackID; }
    inline uint8_t* GetDeliriumAttackAngle() { return &this->_deliriumAttackAngle; }
    inline uint32_t* GetDeliriumCycleID() { return &this->_deliriumCycleID; }
    inline float* GetShieldStrength() { return &this->_shieldStrength; }
    inline std_vector_uint* GetHitList() { return &this->_hitList; }
    inline int32_t * GetControllerId() { return &this->_controllerID; }
    inline void SetControllerId(int32_t x) { this->_controllerID = x; }
}; // 0xf60

struct PlayerCostumeMap {
	int _index; // 0x0
	int _layerID; // 0x4
	int _priority; // 0x8
	bool _isBodyLayer; // 0xc
	char pad0[0x3]; // 0xd
}; // 0x10

struct History {
	std_vector_history_historyitem _historyItems; // 0x0
	char pad0[0x8]; // 0xc
	LIBZHL_API bool RemoveHistoryItemByIndex(int index);
	LIBZHL_API void AddHistoryItem(History_HistoryItem * historyItem);
}; // 0x14

struct GameStatePlayer {
	int _playerType; // 0x0
	char pad0[0x1d0]; // 0x4
	vector_EntitySaveState _movingBoxContents; // 0x1d4
	char pad1[0x160]; // 0x1e0
	int _immaculateConceptionState; // 0x340
	int _cambionConceptionState; // 0x344
	char pad2[0x2c]; // 0x348
	vector_FamiliarData _familiarData; // 0x374
	char pad3[0x30]; // 0x380
	History _history; // 0x3b0
	char pad4[0x100]; // 0x3c4
	BagOfCraftingOutput _bagOfCraftingOutput; // 0x4c4
	char pad5[0x4c]; // 0x4cc
	int _controllerIndex; // 0x518
	char pad6[0xa0]; // 0x51c
	LIBZHL_API void Init();
}; // 0x5bc

struct Entity_Player : public Entity {
	char pad0[0xc]; // 0x410
	ANM2 _bodySprite; // 0x41c
	char pad1[0x9b4]; // 0x530
	ANM2 _bloodGushSprite; // 0xee4
	ANM2 _heldSprite; // 0xff8
	char pad2[0x114]; // 0x110c
	vector_CostumeSpriteDesc _costumeSpriteDescs; // 0x1220
	PlayerCostumeMap _playerCostumeMap[15]; // 0x122c
	char pad3[0x4]; // 0x131c
	std_string _headAnim; // 0x1320
	int _blinkTime; // 0x1338
	int _headDirectionTime; // 0x133c
	int _maxHearts; // 0x1340
	int _redHearts; // 0x1344
	int _eternalHearts; // 0x1348
	int _soulHearts; // 0x134c
	int _blackHearts; // 0x1350
	char pad4[0x8]; // 0x1354
	int _numKeys; // 0x135c
	bool _hasGoldenKey; // 0x1360
	bool _hasGoldenBomb; // 0x1361
	char pad5[0x2]; // 0x1362
	int _numBombs; // 0x1364
	int _numCoins; // 0x1368
	char pad6[0x8]; // 0x136c
	int _gnawedLeafTimer; // 0x1374
	char pad7[0x4]; // 0x1378
	short int _bloodLustCounter; // 0x137c
	char pad8[0xa]; // 0x137e
	int _metronomeCollectibleID; // 0x1388
	char pad9[0x8]; // 0x138c
	int _monkeyPawCounter; // 0x1394
	char pad10[0x20]; // 0x1398
	int _damageCooldown; // 0x13b8
	int _playerType; // 0x13bc
	char pad11[0x18]; // 0x13c0
	Weapon * _weapon[5]; // 0x13d8
	char pad12[0x1c]; // 0x13ec
	Entity_Effect * _markedTarget; // 0x1408
	Entity * _heldEntity; // 0x140c
	char pad13[0x44]; // 0x1410
	Entity_Laser * _megaBlastLaser; // 0x1454
	int _rUaWizardTimer; // 0x1458
	float _maxfiredelay; // 0x145c
	float _shotspeed; // 0x1460
	char pad14[0x8]; // 0x1464
	float _damage; // 0x146c
	float _tearheight; // 0x1470
	float _tearfallspeed; // 0x1474
	float _tearfallaccel; // 0x1478
	float _tearrange; // 0x147c
	char pad15[0x3c]; // 0x1480
	ColorMod _laserColor; // 0x14bc
	char pad16[0x18]; // 0x14e8
	TemporaryEffects _temporaryeffects; // 0x1500
	int _speedModifier; // 0x1518
	int _fireDelayModifier; // 0x151c
	int _damageModifier; // 0x1520
	int _tearRangeModifier; // 0x1524
	int _shotSpeedModifier; // 0x1528
	int _luckModifier; // 0x152c
	int _donateLuck; // 0x1530
	int _potatoPeelerCounter; // 0x1534
	char pad17[0x8]; // 0x1538
	float _edenSpeed; // 0x1540
	float _edenFireDelay; // 0x1544
	float _edenDamage; // 0x1548
	float _edenTearRange; // 0x154c
	float _edenShotSpeed; // 0x1550
	float _edenLuck; // 0x1554
	char pad18[0x4]; // 0x1558
	float _movespeed; // 0x155c
	float _luck; // 0x1560
	bool _canFly; // 0x1564
	char pad19[0x3]; // 0x1565
	unsigned int _cacheFlags; // 0x1568
	char _tearDisplacement; // 0x156c
	char pad20[0x3]; // 0x156d
	float _tearPoisonDamage; // 0x1570
	ActiveItemDesc _activeDesc[4]; // 0x1574
	char pad21[0x4]; // 0x15f4
	int _itemStateCooldown; // 0x15f8
	unsigned int _vampireCharmKills; // 0x15fc
	char pad22[0x4]; // 0x1600
	int _bombPlaceDelay; // 0x1604
	int _forgottenSwapFormCooldown; // 0x1608
	int _controllerIndex; // 0x160c
	int _playerIndex; // 0x1610
	char pad23[0x4]; // 0x1614
	int _moveDirection; // 0x1618
	int _headDirection; // 0x161c
	char pad24[0x90]; // 0x1620
	unsigned int _trinketsID[2]; // 0x16b0
	std_vector_int _collectibleCounts; // 0x16b8
	char pad25[0x74]; // 0x16c4
	vector_SmeltedTrinketDesc _smeltedTrinkets; // 0x1738
	std_vector_int _voidedCollectibles; // 0x1744
	char pad26[0x60]; // 0x1750
	unsigned int _actionHoldDrop; // 0x17b0
	char pad27[0x18]; // 0x17b4
	int _playerForms[15]; // 0x17cc
	char pad28[0x8]; // 0x1808
	bool _postLevelInitFinished; // 0x1810
	bool _canShoot; // 0x1811
	char pad29[0x2]; // 0x1812
	ColorMod _footprintColor1; // 0x1814
	ColorMod _footprintColor2; // 0x1840
	char pad30[0x8]; // 0x186c
	int _ponyCharge; // 0x1874
	int _planCKillCountdown; // 0x1878
	char pad31[0x14]; // 0x187c
	int _epiphoraCharge; // 0x1890
	char pad32[0x8]; // 0x1894
	unsigned int _deadEyeCharges; // 0x189c
	unsigned int _deadEyeMisses; // 0x18a0
	char pad33[0x4]; // 0x18a4
	unsigned int _mawOfTheVoidChargeTimer; // 0x18a8
	char pad34[0x28]; // 0x18ac
	unsigned int _imExcitedSpeedupCountdown; // 0x18d4
	char pad35[0x8]; // 0x18d8
	int _megaBlastDuration; // 0x18e0
	int _peeBurstCooldown; // 0x18e4
	int _maxPeeBurstCooldown; // 0x18e8
	int _bladderCharge; // 0x18ec
	int _maxBladderCharge; // 0x18f0
	bool _isUrethraBlocked; // 0x18f4
	char pad36[0x3]; // 0x18f5
	int _nextUrethraBlockFrame; // 0x18f8
	EntityDesc _friendBallEnemy; // 0x18fc
	int _purityState; // 0x1918
	int _immaculateConceptionState; // 0x191c
	int _cambionConceptionState; // 0x1920
	unsigned int _conceptionFamiliarFlags; // 0x1924
	float _d8DamageModifier; // 0x1928
	float _d8SpeedModifier; // 0x192c
	float _d8RangeModifier; // 0x1930
	float _d8FireDelayModifier; // 0x1934
	int _goldenHearts; // 0x1938
	char pad37[0x19c]; // 0x193c
	int _babySkin; // 0x1ad8
	char pad38[0x28c]; // 0x1adc
	vector_EntitySaveState _movingBoxContents; // 0x1d68
	int _boneHearts; // 0x1d74
	int _boneHeartsMask; // 0x1d78
	int _hallowedGroundCountdown; // 0x1d7c
	char pad39[0xc]; // 0x1d80
	int _brokenHearts; // 0x1d8c
	int _rottenHearts; // 0x1d90
	char pad40[0x8]; // 0x1d94
	unsigned short int _candyHeartStatUps[6]; // 0x1d9c
	unsigned short int _soulLocketStatUps[6]; // 0x1da8
	char pad41[0x8]; // 0x1db4
	unsigned int _urnSouls; // 0x1dbc
	int _numGigaBombs; // 0x1dc0
	char pad42[0x14]; // 0x1dc4
	History _history; // 0x1dd8
	int _inventoryHistoryIdx[16]; // 0x1dec
	char pad43[0xc]; // 0x1e2c
	deque_afterImageFrames _afterImageFrames; // 0x1e38
	EntityPtr _twinPlayer; // 0x1e4c
	Entity_Player * _backupPlayer; // 0x1e50
	float _posOffsetYSpeed; // 0x1e54
	int _redStewBonusDuration; // 0x1e58
	char pad44[0x14]; // 0x1e5c
	int _marsUnk1; // 0x1e70
	int _marsCooldown; // 0x1e74
	int _marsUnk2; // 0x1e78
	bool _marsUnkBool; // 0x1e7c
	char pad45[0x17]; // 0x1e7d
	float _rockBottomMoveSpeed; // 0x1e94
	float _rockBottomMaxFireDelay; // 0x1e98
	float _rockBottomDamage; // 0x1e9c
	float _rockBottomTearRange; // 0x1ea0
	float _rockBottomShotSpeed; // 0x1ea4
	float _rockBottomLuck; // 0x1ea8
	char pad46[0x14]; // 0x1eac
	unsigned int _revelationChargeTimer; // 0x1ec0
	unsigned int _montezumaChargeTimer; // 0x1ec4
	char pad47[0x8]; // 0x1ec8
	unsigned int _maggyHealthDrainCooldown; // 0x1ed0
	int _maggySwingCooldown; // 0x1ed4
	char pad48[0x30]; // 0x1ed8
	int _suplexState; // 0x1f08
	int _suplexAimCountdown; // 0x1f0c
	Vector _suplexTargetPos; // 0x1f10
	Vector _suplexLandPos; // 0x1f18
	char _bagOfCraftingContent[8]; // 0x1f20
	BagOfCraftingOutput _bagOfCraftingOutput; // 0x1f28
	int _poopMana; // 0x1f30
	char _poopSpellQueue[6]; // 0x1f34
	char pad49[0x1e]; // 0x1f3a
	int _eveSumptoriumCharge; // 0x1f58
	std_map_int_int _itemWispsList; // 0x1f5c
	char pad50[0x30]; // 0x1f64
	int _modelingClayEffect; // 0x1f94
	int _keepersSackBonus; // 0x1f98
	char pad51[0x78]; // 0x1f9c
	ConsumableData _consumablesBackup; // 0x2014
	char pad52[0x30]; // 0x2034
	unsigned char _wildCardItemType; // 0x2064
	char pad53[0x3]; // 0x2065
	int _wildCardItem; // 0x2068
	char pad54[0x11]; // 0x206c
	bool _isCoopGhost; // 0x207d
	char pad55[0x2a]; // 0x207e
	PlayerHUD * _playerHUD; // 0x20a8
	char pad56[0x10]; // 0x20ac
	bool _hasUnlistedRestoreState; // 0x20bc
	char pad57[0x3]; // 0x20bd
	GameStatePlayer _unlistedRestoreState; // 0x20c0
	Entity_Player * _replacedPlayer; // 0x267c
	char pad58[0x820]; // 0x2680
	LIBZHL_API void constructor();
	LIBZHL_API void destructor();
	LIBZHL_API void update_red_hearts();
	LIBZHL_API void update_golden_hearts(bool unk);
	LIBZHL_API void update_bone_hearts();
	LIBZHL_API void AdjustBlackHearts();
	LIBZHL_API void update_greeds_gullet();
	LIBZHL_API void trigger_max_hearts_removed(int removed);
	LIBZHL_API void AddCollectible(int type, int charge, bool firsttime, int slot, int vardata, int unk);
	LIBZHL_API void AddTrinket(int type, bool firsttime);
	LIBZHL_API int GetMaxInventorySize();
	LIBZHL_API void AddBrokenHearts(int amount);
	LIBZHL_API void AddBombs(int amount);
	LIBZHL_API void AddKeys(int amount);
	LIBZHL_API void AddJarHearts(int amount);
	LIBZHL_API void AddJarFlies(int amount);
	LIBZHL_API void AddPrettyFly();
	LIBZHL_API void AddCoins(int amount);
	LIBZHL_API void ControlActiveItem(int slot);
	LIBZHL_API static PosVel GetMultiShotPositionVelocity(int loopIndex, WeaponType weaponType, Vector shotDirection, float shotSpeed, Weapon_MultiShotParams multiShotParams);
	LIBZHL_API Weapon_MultiShotParams * GetMultiShotParams(Weapon_MultiShotParams * params, int weaponType);
	LIBZHL_API Entity_Player * InitTwin(int playerType);
	LIBZHL_API void ChangePlayerType(int playerType, bool unk);
	LIBZHL_API Entity * ThrowHeldEntity(Vector * Velocity);
	LIBZHL_API void InitPostLevelInitStats();
	LIBZHL_API void TriggerRoomExit(bool unk);
	LIBZHL_API bool TriggerDeath(bool checkOnly);
	LIBZHL_API bool WillPlayerRevive();
	LIBZHL_API void Revive();
	LIBZHL_API void ReviveFromCollectible(unsigned int itemID, bool ownedByThisPlayer);
	LIBZHL_API void ReviveFromTrinket(unsigned int trinketID);
	LIBZHL_API int GetExtraLives();
	LIBZHL_API void SetItemState(CollectibleType collectible);
	LIBZHL_API void UseCard(int cardType, unsigned int useFlag);
	LIBZHL_API void UsePill(int ePillEffect, int ePillColor, unsigned int useFlag);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API int GetHealthType();
	LIBZHL_API void RenderHead(Vector * position);
	LIBZHL_API void RenderBody(Vector * position);
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API bool CanUseCollectible(CollectibleType collectible, int slot);
	LIBZHL_API bool HasCollectible(int type, bool ignoreModifiers);
	LIBZHL_API bool HasInnateCollectible(int collectibleType, int unused);
	LIBZHL_API bool HasTrinket(unsigned int type, bool ignoreModifiers);
	LIBZHL_API int GetTrinketMultiplier(unsigned int type);
	LIBZHL_API int GetCollectibleCount();
	LIBZHL_API void EvaluateItems();
	LIBZHL_API void CheckFamiliar(unsigned int FamiliarVariant, unsigned int TargetCount, RNG * rng, ItemConfig_Item * Item, int FamiliarSubType);
	LIBZHL_API void AddCacheFlags(int flags);
	LIBZHL_API int GetActiveItem(int slot);
	LIBZHL_API int GetActiveItemSlot(int id);
	LIBZHL_API int GetTotalActiveCharge(int slot);
	LIBZHL_API int GetActiveMaxCharge(int collectible, int vardata);
	LIBZHL_API int GetActiveMaxCharge(int slot);
	LIBZHL_API int GetActiveMinUsableCharge(int slot);
	LIBZHL_API void SetActiveVarData(int vardata, int slot);
	LIBZHL_API int GetActiveCharge(int slot);
	LIBZHL_API int GetActiveSubCharge(int slot);
	LIBZHL_API int GetBatteryCharge(int slot);
	LIBZHL_API bool NeedsCharge(int slot);
	LIBZHL_API void SetActiveCharge(int charge, int slot);
	LIBZHL_API int AddActiveCharge(int charge, int slot, bool flashHUD, bool overcharge, bool force);
	LIBZHL_API bool FullCharge(int slot, bool force);
	LIBZHL_API void DischargeActiveItem(unsigned int slot, bool unk);
	LIBZHL_API void SetPocketActiveItem(int collectible, int slot, bool keepInPools);
	LIBZHL_API Entity_Pickup * DropCollectible(int collectible, Entity_Pickup * existingCollectible, bool removeFromPlayerForm);
	LIBZHL_API Entity_Pickup * DropCollectibleByHistoryIndex(int index, Entity_Pickup * existingCollectible, bool unusedBool);
	LIBZHL_API void AddHearts(int hearts, bool unk, bool unk2);
	LIBZHL_API void AddMaxHearts(int amount, bool ignoreKeeper);
	LIBZHL_API void AddEternalHearts(int amount);
	LIBZHL_API void AddSoulHearts(int amount, bool unk);
	LIBZHL_API void AddGoldenHearts(int amount, bool retBool);
	LIBZHL_API void AddBoneHearts(int amount);
	LIBZHL_API int GetHealthLimit(bool keeper);
	LIBZHL_API void IncrementPlayerFormCounter(int ePlayerForm, int num);
	LIBZHL_API void TriggerNewRoom_TemporaryEffects();
	LIBZHL_API void TriggerNewStage(bool FromPlayerUpdate);
	LIBZHL_API bool TryPreventDeath();
	LIBZHL_API void RemoveCollectibleByHistoryIndex(int index, bool RemovedBool);
	LIBZHL_API void Teleport(Vector * position, bool doEffects, bool teleportTwinPlayers);
	LIBZHL_API bool TryFakeDeath();
	LIBZHL_API int GetCollectibleNum(int collectibleID, bool OnlyCountTrueItems);
	LIBZHL_API void TriggerCollectibleRemoved(int collectibleID);
	LIBZHL_API void TriggerTrinketAdded(unsigned int trinketID, bool firstTimePickingUp);
	LIBZHL_API void TriggerTrinketRemoved(unsigned int trinketID);
	LIBZHL_API void TriggerEchoChamber(unsigned int pocketItemType, int cardOrPillColor);
	LIBZHL_API int GetWeaponModifiers();
	LIBZHL_API void EnableWeaponType(WeaponType weaponType, bool Set);
	LIBZHL_API PocketItem * GetPocketItem(int SlotID);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void InitPreLevelInitStats();
	LIBZHL_API void AddBlackHearts(int amount);
	LIBZHL_API void AddRottenHearts(int amount, bool unk);
	LIBZHL_API void AddGigaBombs(int amount);
	LIBZHL_API void ShuffleCostumes(unsigned int seed);
	LIBZHL_API void RemoveCollectible(unsigned int CollectibleType, bool IgnoreModifiers, unsigned int ActiveSlot, bool RemoveFromPlayerForm);
	LIBZHL_API void UpdateEffects();
	LIBZHL_API void UpdateIsaacPregnancy(bool Cambion);
	LIBZHL_API int GetCambionPregnancyLevel();
	LIBZHL_API void CheckPoopSpellQueue();
	LIBZHL_API void AddCostume(ItemConfig_Item * collectibleID, bool itemStateOnly);
	LIBZHL_API void RemoveCostume(ItemConfig_Item * Item);
	LIBZHL_API void AddNullCostume(int costumeid);
	LIBZHL_API void ClearDeadEyeCharge();
	LIBZHL_API bool SwapForgottenForm(bool unk1, bool unk2);
	LIBZHL_API TearParams * GetTearHitParams(TearParams * res, int WeaponType, float DamageScale, int TearDisplacement, Entity * Source);
	LIBZHL_API void PlayDelayedSFX(unsigned int soundEffectID, int soundDelay, int frameDelay, float volume);
	LIBZHL_API bool CanUsePill(int pillEffect);
	LIBZHL_API unsigned int InvalidateCoPlayerItems();
	LIBZHL_API bool TryRemoveTrinket(unsigned int id);
	LIBZHL_API bool TryRemoveSmeltedTrinket(unsigned int id);
	LIBZHL_API bool IsItemCostumeVisible(ItemConfig_Item * item, int playerSpriteLayerID);
	LIBZHL_API bool IsCollectibleCostumeVisible(CollectibleType collectible, int playerSpriteLayerID);
	LIBZHL_API bool IsNullItemCostumeVisible(int nullItemID, int playerSpriteLayerID);
	LIBZHL_API void PlayCollectibleAnim(CollectibleType collectible, bool checkBodyAnim, std_string & animName, int frameNum, bool unused);
	LIBZHL_API bool IsCollectibleAnimFinished(CollectibleType collectible, std_string & animName);
	LIBZHL_API void ClearCollectibleAnim(CollectibleType collectible);
	LIBZHL_API unsigned int GetMaxPocketItems();
	LIBZHL_API void AddPocketItem(int id, unsigned int pocketItemType);
	LIBZHL_API void SetCard(int slot, int card);
	LIBZHL_API void SetPill(int slot, int pillColor);
	LIBZHL_API Entity * AddBoneOrbital(Vector * Position);
	LIBZHL_API unsigned int AddItemCard(unsigned int itemID);
	LIBZHL_API void AddLeprosy();
	LIBZHL_API void AddUrnSouls(unsigned int amount);
	LIBZHL_API bool CanAddCollectibleToInventory(int id);
	LIBZHL_API void UpdateBookOfVirtues(bool addedBookOfVirtues);
	LIBZHL_API bool CanOverrideActiveItem(unsigned int slot);
	LIBZHL_API Entity_Bomb * FireBomb(Vector * pos, Vector * vel, Entity * source);
	LIBZHL_API Entity_Knife * FireBoneClub(Entity * parent, unsigned int variant, bool unk, Weapon * weapon, float unk2);
	LIBZHL_API Entity_Effect * FireBrimstoneBall(Vector const & pos, Vector const & vel, Vector const & offset, unsigned int unk1, unsigned int unk2, Entity * unk3);
	LIBZHL_API Entity_Knife * FireKnife(Entity * parent, unsigned int variant, float rotationOffset, bool cantOverwrite, unsigned int subType);
	LIBZHL_API Entity_Laser * FireTechLaser(Vector const & pos, unsigned int offsetID, Vector const & dir, bool leftEye, bool oneHit, Entity * source, float damageScale);
	LIBZHL_API Entity_Laser * FireTechXLaser(Vector const & pos, Vector const & dir, float radius, Entity * source, float damageMultiplier);
	LIBZHL_API void GetLaserOffset(Vector * buffer, int laserOffsetID, Vector * direction);
	LIBZHL_API void GetBodyMoveDirection(Vector * buffer);
	LIBZHL_API char * GetDeathAnimName();
	LIBZHL_API unsigned int GetGlitchBabySubType();
	LIBZHL_API int GetGreedsGulletHearts();
	LIBZHL_API unsigned int GetSpecialGridCollision(Vector * pos);
	LIBZHL_API bool CanCrushRocks();
	LIBZHL_API void GetEnterPosition(Vector * buffer);
	LIBZHL_API bool PlayItemNullAnimation(char const * animName);
	LIBZHL_API Entity * GetFocusEntity();
	LIBZHL_API void GetGlyphOfBalanceDrop(int * variant, int * subtype);
	LIBZHL_API bool HasInstantDeathCurse();
	LIBZHL_API bool HasPoisonImmunity();
	LIBZHL_API bool IsEntityValidTarget(Entity * entity);
	LIBZHL_API bool IsInvisible();
	LIBZHL_API bool IsFootstepFrame(int eFoot);
	LIBZHL_API bool IsHeadless();
	LIBZHL_API bool IsHologram();
	LIBZHL_API void MorphToCoopGhost();
	LIBZHL_API void RemovePocketItem(int slot);
	LIBZHL_API void DropPocketItem(int slot, Vector * pos);
	LIBZHL_API void RerollAllCollectibles(RNG * rng, bool includeActives);
	LIBZHL_API void ResetPlayer();
	LIBZHL_API void RevivePlayerGhost();
	LIBZHL_API void SalvageCollectible(Vector * pos, int subtype, unsigned int seed, int poolType);
	LIBZHL_API void SetControllerIndex(int index, bool includePlayerOwned);
	LIBZHL_API void SetFootprintColor(KColor color, bool unk);
	LIBZHL_API Entity * ShootBlueCandle(Vector * dir);
	LIBZHL_API Entity * ShootRedCandle(Vector * dir);
	LIBZHL_API void SpawnClot(Vector * pos, bool unk);
	LIBZHL_API unsigned int SpawnSaturnusTears();
	LIBZHL_API void SyncConsumableCounts(Entity_Player * player, int bitflags);
	LIBZHL_API void ConsumableCountChanged(int bitflags);
	LIBZHL_API bool TryAddToBagOfCrafting(Entity_Pickup * pickup);
	LIBZHL_API static BagOfCraftingOutput * __stdcall CalculateBagOfCraftingOutput(BagOfCraftingOutput * implicit_output, BagOfCraftingPickup * bagContent, bool unused);
	LIBZHL_API void TryDecreaseGlowingHourglassUses(int unk1, bool unk2);
	LIBZHL_API bool TryForgottenThrow(Vector * dir);
	LIBZHL_API void UseRedKey();
	LIBZHL_API bool VoidHasCollectible(int id);
	LIBZHL_API RNG * GetCollectibleRNG(int id);
	LIBZHL_API RNG * GetTrinketRNG(int id);
	LIBZHL_API void AttachMinecart(Entity_NPC * minecart);
	LIBZHL_API void ClearQueueItem();
	LIBZHL_API void TriggerEffectRemoved(ItemConfig_Item * item, int unused);
	LIBZHL_API bool HasGoldenTrinket(unsigned int TrinketID);
	LIBZHL_API void TriggerEnemyDeath(Entity_NPC * npc);
	LIBZHL_API bool CanRerollCollectible(int id, bool unk);
	LIBZHL_API bool HasInvincibility(unsigned long long int damageFlags, EntityRef * source);
	LIBZHL_API void UseActiveItem(short int * resultFlags, int collectible, unsigned int useFlags, int activeSlot, int varData);
	LIBZHL_API void StoreGameState(GameStatePlayer * saveState, bool saveTemporaryFamiliars);
	LIBZHL_API void RestoreGameState(GameStatePlayer * saveState);
	LIBZHL_API void RestoreGameState_PostLevelInit(GameStatePlayer * saveState);
	LIBZHL_API void GetTearMovementInheritance(Vector * out, Vector * direction, bool unkFlag);
	LIBZHL_API Entity_Pickup * DropTrinket(Vector * DropPos, bool ReplaceTick);
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API void ResetColor();
	LIBZHL_API void Original_ResetColor();
	void virtual_unk183() { }
	void virtual_unk184() { }
	void virtual_unk185() { }
	void virtual_unk186() { }
	void virtual_unk187() { }
	void virtual_unk188() { }
	void virtual_unk189() { }
	void virtual_unk190() { }
	void virtual_unk191() { }
	void virtual_unk192() { }
	void virtual_unk193() { }
	void virtual_unk194() { }
	void virtual_unk195() { }
	void virtual_unk196() { }
	void virtual_unk197() { }
	void virtual_unk198() { }
	void virtual_unk199() { }
	void virtual_unk200() { }
	void virtual_unk201() { }
	void virtual_unk202() { }
	void virtual_unk203() { }
    inline int* GetMaxHearts() {return &this->_maxHearts; }
	inline int* GetRedHearts() {return &this->_redHearts; }
	inline int* GetEternalHearts() {return &this->_eternalHearts; }
	inline int* GetSoulHearts() {return &this->_soulHearts; }
	inline int* GetBlackHearts() {return &this->_blackHearts; }
	inline int* GetMetronomeCollectibleID() { return &this->_metronomeCollectibleID; } 
	inline int GetPlayerType() { return this->_playerType; }
	inline Weapon** GetWeapon(int index) { return &_weapon[index]; }
	inline Entity_Effect* GetMarkedTarget() { return this->_markedTarget; }
	inline Entity* GetHeldEntity() { return this->_heldEntity; }
	inline int* GetFireDelayModifier() { return &this->_fireDelayModifier; }
	inline int* GetDamageModifier() { return &this->_damageModifier; }
	inline float* GetEdenSpeed() { return &this->_edenSpeed; }
	inline float* GetEdenFireDelay() { return &this->_edenFireDelay; }
	inline float* GetEdenDamage() { return &this->_edenDamage; }
	inline float* GetEdenRange() { return &this->_edenTearRange; }
	inline float* GetEdenShotSpeed() { return &this->_edenShotSpeed; }
	inline float* GetEdenLuck() { return &this->_edenLuck; }
	inline bool* GetCanFly() { return &this->_canFly; }
	inline std_vector_int* GetCollectiblesList() { return &this->_collectibleCounts; }
	inline vector_SmeltedTrinketDesc* GetSmeltedTrinket() { return &this->_smeltedTrinkets; }
	inline std_vector_int* GetVoidedCollectiblesList() { return &this->_voidedCollectibles; }
	inline int* GetPonyCharge() { return &this->_ponyCharge; } 
	inline uint32_t GetDeadEyeCharge() { return this->_deadEyeCharges; }
	inline uint32_t GetDeadEyeMisses() { return this->_deadEyeMisses; }
	inline bool* GetCanShoot() { return &this->_canShoot; }
	inline int* GetEpiphoraCharge() { return &this->_epiphoraCharge; }
	inline int* GetMegaBlastDuration() { return &this->_megaBlastDuration; }
	inline int* GetPeeBurstCooldown() { return &this->_peeBurstCooldown; }
	inline int* GetMaxPeeBurstCooldown() { return &this->_maxPeeBurstCooldown; }
	inline int* GetBladderCharge() { return &this->_bladderCharge; }
	inline int* GetMaxBladderCharge() { return &this->_maxBladderCharge; }
	inline bool* IsUrethraBlocked() { return &this->_isUrethraBlocked; }
	inline int* GetNextUrethraBlockFrame() { return &this->_nextUrethraBlockFrame; }
	inline int* GetPurityState() { return &this->_purityState; }
	inline int* GetImmaculateConceptionState() { return &this->_immaculateConceptionState; }
	inline int* GetCambionConceptionState() { return &this->_cambionConceptionState; }
	inline float* GetD8DamageModifier() { return &this->_d8DamageModifier; }
	inline float* GetD8SpeedModifier() { return &this->_d8SpeedModifier; }
	inline float* GetD8RangeModifier() { return &this->_d8RangeModifier; }
	inline float* GetD8FireDelayModifier() { return &this->_d8FireDelayModifier; }
	inline int* GetGoldenHearts() { return &this->_goldenHearts; }
	inline vector_EntitySaveState* GetMovingBoxContents() {return &this->_movingBoxContents; }
	inline int* GetBoneHearts() { return &this->_boneHearts; }
	inline int* GetBrokenHearts() { return &this->_brokenHearts; }
	inline int* GetRottenHearts() { return &this->_rottenHearts; }
	inline int* GetGigaBombs() { return &this->_numGigaBombs; }
	inline History* GetHistory() { return &this->_history; }
	inline float* GetTearPoisonDamage() { return &this->_tearPoisonDamage; }
	inline ActiveItemDesc* GetActiveItemDesc(int index) { return &this->_activeDesc[index]; }
	inline ANM2* GetHeldSprite() { return &this->_heldSprite; }

    inline int* GetRedStewBonusDuration() { return &this->_redStewBonusDuration; }
    inline BagOfCraftingPickup* GetBagOfCraftingContent() { return (BagOfCraftingPickup*)(&this->_bagOfCraftingContent); }
	inline std_map_int_int* GetItemWispsList() { return &this->_itemWispsList; }
    inline BagOfCraftingOutput* GetBagOfCraftingOutput() { return &this->_bagOfCraftingOutput; }
	inline uint8_t* GetWildCardItemType() { return &this->_wildCardItemType; }
	inline int* GetWildCardItem() { return &this->_wildCardItem; }
	
	inline Entity_Player* GetTwinPlayer() { return (Entity_Player*)this->_twinPlayer.GetReference(); }
	inline void SetTwinPlayer(Entity_Player* player) { this->_twinPlayer.SetReference(player); }
   
}; // 0x2ea0

struct Entity_Projectile : public Entity {
	char pad0[0x60]; // 0x410
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void Reflect(Entity * unused, Vector * newVelocity);
	LIBZHL_API void Constructor();
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk204() { }
	void virtual_unk205() { }
	void virtual_unk206() { }
	void virtual_unk207() { }
	void virtual_unk208() { }
	void virtual_unk209() { }
	void virtual_unk210() { }
	void virtual_unk211() { }
	void virtual_unk212() { }
	void virtual_unk213() { }
	void virtual_unk214() { }
	void virtual_unk215() { }
	void virtual_unk216() { }
	void virtual_unk217() { }
	void virtual_unk218() { }
	void virtual_unk219() { }
	void virtual_unk220() { }
	void virtual_unk221() { }
	void virtual_unk222() { }
	void virtual_unk223() { }
	void virtual_unk224() { }
	void virtual_unk225() { }
	void virtual_unk226() { }
	void virtual_unk227() { }
	void virtual_unk228() { }
}; // 0x470

struct Entity_Slot : public Entity {
	int _state; // 0x410
	int _prizeType; // 0x414
	char pad0[0x2]; // 0x418
	short int _shellGameAnimationIndex; // 0x41a
	short int _timeout; // 0x41c
	char pad1[0x2]; // 0x41e
	int _donationValue; // 0x420
	unsigned int _triggerTimer; // 0x424
	short int _unkShort1; // 0x428
	unsigned short int _touch; // 0x42a
	ANM2 _prizeAnm2; // 0x42c
	int _prizeCollectible; // 0x540
	char pad2[0x4]; // 0x544
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void CreateDropsFromExplosion();
	LIBZHL_API void SetPrizeCollectible(int CollectibleType);
	LIBZHL_API void Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Original_Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	void virtual_unk229() { }
	void virtual_unk230() { }
	void virtual_unk231() { }
	void virtual_unk232() { }
	void virtual_unk233() { }
	void virtual_unk234() { }
	void virtual_unk235() { }
	void virtual_unk236() { }
	void virtual_unk237() { }
	void virtual_unk238() { }
	void virtual_unk239() { }
	void virtual_unk240() { }
	void virtual_unk241() { }
	void virtual_unk242() { }
	void virtual_unk243() { }
	void virtual_unk244() { }
	void virtual_unk245() { }
	void virtual_unk246() { }
	void virtual_unk247() { }
	void virtual_unk248() { }
	LIBZHL_API bool HandleCollision(Entity * Collider, bool Low);
	LIBZHL_API bool Original_HandleCollision(Entity * Collider, bool Low);
	void virtual_unk249() { }
	void virtual_unk250() { }
	inline int* GetState() { return &this->_state; }
	inline int* GetPrizeType() { return &this->_prizeType; }
	inline short* GetTimeout() { return &this->_timeout; }
	inline int* GetDonationValue() { return &this->_donationValue; }
	inline unsigned short* GetTouch() { return &this->_touch; }
	inline int* GetPrizeCollectible() { return &this->_prizeCollectible; }
}; // 0x548

struct Entity_Tear : public Entity {
	float _height; // 0x410
	float _fallingSpeed; // 0x414
	float _fallingAccel; // 0x418
	float _homingFriction; // 0x41c
	float _fScale; // 0x420
	float _baseScale; // 0x424
	BitSet128 _tearFlags; // 0x428
	int _waitFrames; // 0x438
	Vector _continueVelocity; // 0x43c
	std_vector_uint _hitList; // 0x444
	int _tearIdx; // 0x450
	float _baseDamage; // 0x454
	float _rotation; // 0x458
	int _scaleAnimNum; // 0x45c
	float _knockbackMultiplier; // 0x460
	float _deadEyeIntensity; // 0x464
	bool _multidimensionalTouched; // 0x468
	bool _prismTouched; // 0x469
	char pad0[0x42]; // 0x46a
	ANM2 _tearHaloANM2; // 0x4ac
	ANM2 _tearEffectANM2; // 0x5c0
	ANM2 _deadEyeANM2; // 0x6d4
	char pad1[0x38]; // 0x7e8
	float _tearRange; // 0x820
	char pad2[0x24]; // 0x824
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API Entity_Tear * MakeMultidimensionalCopy(Entity * spawner);
	LIBZHL_API void ResetSpriteScale();
	LIBZHL_API void Constructor();
	LIBZHL_API float GetRenderHeight();
	LIBZHL_API void SetTearFlags(BitSet128 flags);
	LIBZHL_API void SetHeight(float height);
	LIBZHL_API void SetScale(float scale);
	LIBZHL_API static void ApplyTearFlagEffects(Entity * entity, Vector * position, BitSet128 flags, Entity * source, float damage);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk251() { }
	void virtual_unk252() { }
	void virtual_unk253() { }
	void virtual_unk254() { }
	void virtual_unk255() { }
	void virtual_unk256() { }
	void virtual_unk257() { }
	void virtual_unk258() { }
	void virtual_unk259() { }
	void virtual_unk260() { }
	void virtual_unk261() { }
	void virtual_unk262() { }
	void virtual_unk263() { }
	void virtual_unk264() { }
	void virtual_unk265() { }
	void virtual_unk266() { }
	void virtual_unk267() { }
	void virtual_unk268() { }
	void virtual_unk269() { }
	void virtual_unk270() { }
	void virtual_unk271() { }
	void virtual_unk272() { }
	void virtual_unk273() { }
	void virtual_unk274() { }
	void virtual_unk275() { }
}; // 0x848

struct FamiliarData {
	unsigned int _seed; // 0x0
	unsigned int _variant; // 0x4
	int _subtype; // 0x8
	int _coins; // 0xc
	int _hearts; // 0x10
	int _keys; // 0x14
	int _state; // 0x18
	int _roomClearCount; // 0x1c
	char pad0[0x8]; // 0x20
	float _health; // 0x28
	unsigned int _dropRNGSeed; // 0x2c
	char pad1[0x4]; // 0x30
}; // 0x34

struct Font {
	bool _isLoaded; // 0x0
	char pad0[0x3]; // 0x1
	short int _fontSize; // 0x4
	unsigned char _infoBitField; // 0x6
	unsigned char _charSet; // 0x7
	unsigned short int _stretchH; // 0x8
	unsigned char _aa; // 0xa
	unsigned char _paddingUp; // 0xb
	unsigned char _paddingRight; // 0xc
	unsigned char _paddingDown; // 0xd
	unsigned char _paddingLeft; // 0xe
	unsigned char _spacingHoriz; // 0xf
	unsigned char _spacingVert; // 0x10
	unsigned char _outline; // 0x11
	char pad1[0x2]; // 0x12
	unsigned short int _lineHeight; // 0x14
	unsigned short int _base; // 0x16
	unsigned short int _scaleW; // 0x18
	unsigned short int _scaleH; // 0x1a
	unsigned short int _pages; // 0x1c
	unsigned char _commonBitField; // 0x1e
	unsigned char _alphaChannel; // 0x1f
	unsigned char _redChannel; // 0x20
	unsigned char _greenChannel; // 0x21
	unsigned char _blueChannel; // 0x22
	char pad2[0x1]; // 0x23
	unsigned int _numChars; // 0x24
	FontCharBlock * _chars; // 0x28
	vector_KerningPair _kerningPairs; // 0x2c
	char pad3[0x8]; // 0x38
	std_map_CharBlocks _charsBlock; // 0x40
	int _missingCharacter; // 0x48
	LIBZHL_API void Load(char const * path, bool unusedIsLoading);
	LIBZHL_API void DrawString(char const * str, Vector pos, Vector scale, KColor * color, FontSettings * settings);
	LIBZHL_API int GetStringWidth(char const * str);
}; // 0x4c

struct FontSettings {
	int _align; // 0x0
	short int _maxChars; // 0x4
	unsigned short int _maxLineWidth; // 0x6
	int _wrapMode; // 0x8
	float _lineHeightModifier; // 0xc
	int _missingCharOverride; // 0x10
	int _unk1; // 0x14
	int _unk2; // 0x18
	LIBZHL_API void constructor();
		FontSettings() { this->constructor(); }

}; // 0x1c

struct MinimapConfig {
	ANM2 _mapSprite; // 0x0
	char pad0[0x8]; // 0x114
	Vector _vec1; // 0x11c
	Vector _borderPadding; // 0x124
	float _posOffsetX; // 0x12c
	float _borderScale; // 0x130
	int _i1; // 0x134
	int _i2; // 0x138
	int _minimapIconNum; // 0x13c
	char pad1[0x8]; // 0x140
	Vector _size1; // 0x148
	Vector _size2; // 0x150
	float _alpha; // 0x158
	char pad2[0x4]; // 0x15c
	LIBZHL_API void Render();
}; // 0x160

struct Minimap {
	int _state; // 0x0
	bool _unkBool; // 0x4
	char pad0[0x3]; // 0x5
	unsigned int _holdTime; // 0x8
	float _unkFloat; // 0xc
	char pad1[0x8]; // 0x10
	MinimapConfig _config[2]; // 0x18
	ANM2 _itemIconsSprite; // 0x2d8
	ANM2 _hudPickupSprite; // 0x3ec
	ANM2 _iconsSprite; // 0x500
	char pad2[0x8]; // 0x614
	int _shakeDuration; // 0x61c
	Vector _shakeOffset; // 0x620
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	LIBZHL_API Vector * GetDisplayedSize(Vector & buffer);
	LIBZHL_API void RenderIcons(Vector * Position, float Alpha);
	LIBZHL_API void Refresh();
}; // 0x628

struct RoomConfig_Miniboss {
	unsigned int _idMaybe; // 0x0
	std_string _displayName; // 0x4
}; // 0x1c

struct RoomSet {
	std_string _filepath; // 0x0
	RoomConfig_Room * _configs; // 0x18
	unsigned int _count; // 0x1c
	std_map_uint_VariantSetPtr variantSetMap; // 0x20
	bool _loaded; // 0x28
	char pad0[0x3]; // 0x29
	LIBZHL_API void unload();
	LIBZHL_API RoomConfig_VariantSet * GetVariantSet(unsigned int type);
}; // 0x2c

struct RoomConfig_Stage {
	unsigned int _id; // 0x0
	std_string _displayName; // 0x4
	std_string _playerSpot; // 0x1c
	std_string _bossSpot; // 0x34
	std_string _suffix; // 0x4c
	RoomSet _rooms[2]; // 0x64
	int _musicId; // 0xbc
	int _backdrop; // 0xc0
	LIBZHL_API RoomConfig_Stage * game_constructor();
	LIBZHL_API void game_destructor();
	LIBZHL_API void unload();
}; // 0xc4

struct RoomConfig_Curse {
	unsigned int _idMaybe; // 0x0
	std_string _displayName; // 0x4
}; // 0x1c

struct RoomConfig {
	RoomConfig_Stage _stages[37]; // 0x0
	vector_Curse _curses; // 0x1c54
	RoomConfig_Miniboss _miniboss; // 0x1c60
	char pad0[0x1a4]; // 0x1c7c
	RoomConfig_Room * _rooms; // 0x1e20
	unsigned int _roomCount; // 0x1e24
	LIBZHL_API void LoadCurses(char * xmlpath, bool ismod);
	LIBZHL_API static unsigned int GetStageID(unsigned int LevelStage, unsigned int StageType, unsigned int Mode);
	LIBZHL_API void LoadStages(char * xmlpath);
	LIBZHL_API void LoadStageBinary(unsigned int Stage, unsigned int Mode);
	LIBZHL_API RoomConfig_Room * GetRoomByStageTypeAndVariant(unsigned int stage, unsigned int type, unsigned int variant, int mode);
	LIBZHL_API RoomConfig_Room * GetRandomRoom(unsigned int seed, bool reduceWeight, int stage, int roomType, int roomShape, unsigned int minVariant, int maxVariant, int minDifficulty, int maxDifficulty, unsigned int * requiredDoors, unsigned int roomSubtype, int mode);
	LIBZHL_API RoomConfigRoomPtrVector GetRooms(int stage, int type, int shape, int minVariant, int maxVariant, int minDifficulty, int maxDifficulty, unsigned int * doors, unsigned int subtype, int mode);
	LIBZHL_API static int get_door_from_position(short int posX, short int posY, int shape);
	LIBZHL_API static void read_room(RoomSet * set, int idx, int stageId, KAGE_Filesys_IFile * file);
	LIBZHL_API void ResetRoomWeights(unsigned int Stage, int Mode);
}; // 0x1e28

struct RoomTransition {
	int _mode; // 0x0
	char pad0[0xc]; // 0x4
	int _direction; // 0x10
	int _roomIndex; // 0x14
	int _roomDimension; // 0x18
	char pad1[0x1c]; // 0x1c
	ANM2 _versusScreenANM2; // 0x38
	char pad2[0xd8]; // 0x14c
	std_map_int_ANM2 _extraLayerANM2s; // 0x224
	char pad3[0xc]; // 0x22c
	int _unkStartRoomTransitionCond; // 0x238
	LIBZHL_API void ChangeRoom();
	LIBZHL_API void StartBossIntro(unsigned int bossID1, unsigned int bossID2);
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	inline int GetTransitionMode() { return this->_mode; }
	inline ANM2* GetVersusScreenSprite() { return &this->_versusScreenANM2; }
	inline bool IsRenderingBossIntro() {
		return GetTransitionMode() == 2 && _unkStartRoomTransitionCond != 0;
	}
	inline std::map<int, ANM2>* GetExtraLayerANM2s() { return &this->_extraLayerANM2s; }
}; // 0x23c

struct ScoreSheet {
	int _stageBonus; // 0x0
	int _schwagBonus; // 0x4
	int _blueBabyBonus; // 0x8
	int _lambBonus; // 0xc
	int _megaSatanBonus; // 0x10
	int _motherBonus; // 0x14
	int _deliriumBonus; // 0x18
	int _beastBonus; // 0x1c
	int _rushBonus; // 0x20
	int _explorationBonus; // 0x24
	int _damagePenalty; // 0x28
	int _timePenalty; // 0x2c
	int _itemPenalty; // 0x30
	int _totalScore; // 0x34
	int _runTimeLevel; // 0x38
	int _runTimeLevelType; // 0x3c
	unsigned int _runTime; // 0x40
	char pad0[0x14]; // 0x44
	int _runEnding; // 0x58
	char pad1[0x34]; // 0x5c
	LIBZHL_API void Calculate();
	LIBZHL_API void AddKilledEnemy(Entity_NPC * ent);
	LIBZHL_API void AddFinishedStage(int stage, int stageType, unsigned int time, bool repeatedStage);
		//void LIBZHL_API AddFinishedStage(int stage, int stageType, unsigned int time);
	
		/*inline void AddFinishedStage(int stage, int stageType, uint32_t time) {
			if ((this->_runTimeLevel < stage) && g_Game->GetDailyChallenge()._id == 0) {
				this->_runTimeLevel = stage;
				this->_runTimeLevelStage = stageType;
				this->_runTime = time;
			}
			return;
		};
		*/

}; // 0x90

struct ItemPool_Item {
	float _totalWeight; // 0x0
	vector_PoolItem _poolList; // 0x4
	RNG _rng1; // 0x10
	RNG _rng2; // 0x20
	unsigned int _bibleUpgrade; // 0x30
		ItemPool_Item()
		{
			_totalWeight = 0.0f;
			_rng1.SetSeed(2853650767, 35);
			_rng2.SetSeed(2853650767, 35);
			_bibleUpgrade = 0;
		}

}; // 0x34

struct ItemPool {
	char pad0[0x4]; // 0x0
	ItemPool_Item _pools[31]; // 0x4
	int _lastPool; // 0x650
	RNG _itemPoolRNG; // 0x654
	char pad1[0x18]; // 0x664
	vector_bool _removedCollectibles; // 0x67c
	vector_bool _roomBlacklistedCollectibles; // 0x68c
	char pad2[0xf8]; // 0x69c
	vector_TrinketPoolItem _trinketPoolItems; // 0x794
	int _numAvailableTrinkets; // 0x7a0
	int _pillEffects[15]; // 0x7a4
	bool _idendifiedPillEffects[15]; // 0x7e0
	char pad3[0x1]; // 0x7ef
	unsigned short int _remainingGenesisItems[31]; // 0x7f0
	char pad4[0x2]; // 0x82e
	LIBZHL_API void Init(unsigned int seed, char * filename);
	LIBZHL_API void AddRoomBlacklist(int item);
	LIBZHL_API unsigned int GetTrinket(bool DontAdvanceRNG);
	LIBZHL_API static int __stdcall GetCardEx(int Seed, int SpecialChance, int RuneChance, int SuitChance, bool AllowNonCards);
	LIBZHL_API void load_pools(char * xmlpath, bool ismod);
	LIBZHL_API void shuffle_pools();
	LIBZHL_API void StoreGameState(GameStateItemPool * itemPoolState);
	LIBZHL_API void RestoreGameState(GameStateItemPool * itemPoolState);
	LIBZHL_API int GetCollectible(int itemPoolType, unsigned int seed, unsigned int flags, int defaultItem);
	LIBZHL_API int get_chaos_pool(RNG * rng);
	LIBZHL_API PoolItem * pick_collectible(float targetWeight, ItemPool_Item * pool, unsigned int flags);
	LIBZHL_API int GetCollectibleFromList(int const * list, unsigned int length, unsigned int seed, unsigned int defaultItem, bool addToBlacklist, bool excludeLockedItems);
	LIBZHL_API static bool __stdcall TryReplaceWithMagicSkin(unsigned int seed);
	LIBZHL_API void AddBibleUpgrade(int Add, int PoolType);
	LIBZHL_API void ResetCollectible(int Collectible);
	LIBZHL_API ItemPool_Item * GetPool(int itemPoolType);
	LIBZHL_API int GetPoolForRoom(unsigned int RoomType, unsigned int Seed);
	LIBZHL_API int ForceAddPillEffect(int ID);
	LIBZHL_API int GetFirstItemPoolForCollectible(int collectible);
	LIBZHL_API void GetItemPoolsForCollectible(int collectible, std_vector_uint * result);
	LIBZHL_API static int GetSeededCollectible(unsigned int seed, bool noDecrease, RoomDescriptor * roomDesc);
	LIBZHL_API int GetPillEffect(unsigned int pillColor, Entity_Player * player);
	LIBZHL_API void IdentifyPill(unsigned int pillColor);
	LIBZHL_API bool IsPillIdentified(unsigned int pillColor);
		inline std::vector<bool>* GetRemovedCollectibles() { return &this->_removedCollectibles; }
		inline std::vector<bool>* GetRoomBlacklistedCollectibles() { return &this->_roomBlacklistedCollectibles; }

}; // 0x830

struct StatHUD {
	char pad0[0x2b0]; // 0x0
	LIBZHL_API int GetPlayerId(Entity_Player * player);
	LIBZHL_API void RecomputeStats(int playerId, unsigned int flags, bool unk);
}; // 0x2b0

struct HistoryHUD_Player {
	Entity_Player * _player; // 0x0
	char pad0[0x4]; // 0x4
	std_vector_HistoryHUDItem _historyHudItems; // 0x8
}; // 0x14

struct HistoryHUD {
	HistoryHUD_Player _playerHistoryHuds[2]; // 0x0
	char pad0[0x4]; // 0x28
	LIBZHL_API void Render(Vector * pos, bool mini);
	LIBZHL_API int GetPlayerIdx(Entity_Player * player);
	LIBZHL_API void Recompute(int idx, bool immediate);
	LIBZHL_API void RecomputeAll(bool immediate);
		Vector LIBZHL_API HistoryHUD::GetPosition() const;
		bool LIBZHL_API HistoryHUD::HasTwin() const;
		bool LIBZHL_API HistoryHUD::IsMini() const;
		float LIBZHL_API HistoryHUD::GetScale() const;
		float LIBZHL_API HistoryHUD::GetIconSize() const;
		int LIBZHL_API HistoryHUD::GetNumRows() const;
		int LIBZHL_API HistoryHUD::GetNumColumns() const;
		int LIBZHL_API HistoryHUD::GetNumVisibleItems() const;

}; // 0x2c

struct HUD_Message {
	wchar_t * _text; // 0x0
	wchar_t * _subtext; // 0x4
	bool _showing; // 0x8
	bool _autoHide; // 0x9
	bool _isCurseDisplay; // 0xa
	char pad0[0x15]; // 0xb
	ANM2 _streakSprite; // 0x20
	KColor _color1; // 0x134
	KColor _color2; // 0x148
	char pad1[0x98]; // 0x15c
	LIBZHL_API void Show(char const * title, char const * subtitle, bool autoHide, bool isCurseDisplay);
	LIBZHL_API void LoadText(wchar_t const * str, bool asSubText);
	LIBZHL_API void UpdateTextImage();
	LIBZHL_API void text_out();
}; // 0x1f4

struct SourceQuad : public DestinationQuad {
	int _coordinateSpace; // 0x20
        enum eCoordinateSpace
        {
            PIXEL = 0,
            NORMALIZED_UV = 1,
        };

        LIBZHL_API void ConvertToPixelSpace(KAGE_Graphics_ImageBase& image);
        LIBZHL_API void ConvertToUVSpace(KAGE_Graphics_ImageBase& image);
   
}; // 0x24

struct KAGE_Graphics_ImageBase {
	char pad0[0x10]; // 0x0
	unsigned long long int _flags; // 0x10
	char pad1[0x8]; // 0x18
	unsigned int _predefinedShader; // 0x20
	unsigned int _minFilterMode; // 0x24
	unsigned int _magFilterMode; // 0x28
	unsigned int _wrapSMode; // 0x2c
	unsigned int _wrapTMode; // 0x30
	unsigned char * _vertexFormat; // 0x34
	unsigned char _numVertexAttributes; // 0x38
	char pad2[0x1]; // 0x39
	unsigned short int _vertexFormatStride; // 0x3a
	char * _name; // 0x3c
	vector_RenderBatchPtr _renderBatches; // 0x40
	KAGE_Graphics_RenderBatch * _lastRenderBatch; // 0x4c
	vector_RenderBatchPtr _reusableTransparentRenderBatches; // 0x50
	KAGE_Graphics_RenderBatch * _lastTransparentRenderBatch; // 0x5c
	char pad3[0x20]; // 0x60
	LIBZHL_API KAGE_Graphics_RenderBatch * get_batch(bool isTransparent);
	void virtual_unk276() { }
	void virtual_unk277() { }
	LIBZHL_API float * Render(SourceQuad const & source, DestinationQuad const & dest, KColor const & colTopLeft, KColor const & colTopRight, KColor const & colBottomLeft, KColor const & colBottomRight);
	LIBZHL_API float * Original_Render(SourceQuad const & source, DestinationQuad const & dest, KColor const & colTopLeft, KColor const & colTopRight, KColor const & colBottomLeft, KColor const & colBottomRight);
	LIBZHL_API float * Render(SourceQuad const & source, DestinationQuad const & dest, KColor const & color);
	LIBZHL_API float * Original_Render(SourceQuad const & source, DestinationQuad const & dest, KColor const & color);
	void virtual_unk278() { }
	void virtual_unk279() { }
	void virtual_unk280() { }
	void virtual_unk281() { }
	void virtual_unk282() { }
	void virtual_unk283() { }
	LIBZHL_API int GetWidth();
	LIBZHL_API int GetWidth_Original();
	LIBZHL_API int GetHeight();
	LIBZHL_API int GetHeight_Original();
	LIBZHL_API int GetPaddedWidth();
	LIBZHL_API int GetPaddedWidth_Original();
	LIBZHL_API int GetPaddedHeight();
	LIBZHL_API int GetPaddedHeight_Original();
	void virtual_unk284() { }
	LIBZHL_API void SetVertexFormat(KAGE_Graphics_ImageBase_VertexAttributeDescriptor const & vertexFormat);
	LIBZHL_API void Original_SetVertexFormat(KAGE_Graphics_ImageBase_VertexAttributeDescriptor const & vertexFormat);
	void virtual_unk285() { }
	void virtual_unk286() { }
	void virtual_unk287() { }
	void virtual_unk288() { }
	void virtual_unk289() { }
	void virtual_unk290() { }
	LIBZHL_API void GetTexelRegion(int x, int y, unsigned int width, unsigned int height, void * buffer);
	LIBZHL_API void Original_GetTexelRegion(int x, int y, unsigned int width, unsigned int height, void * buffer);
	void virtual_unk291() { }
	void virtual_unk292() { }
	void virtual_unk293() { }
	void virtual_unk294() { }
	void virtual_unk295() { }
	void virtual_unk296() { }
	void virtual_unk297() { }
	void virtual_unk298() { }
	void virtual_unk299() { }
	void virtual_unk300() { }
	void virtual_unk301() { }
	void virtual_unk302() { }
	LIBZHL_API void apply_image();
	LIBZHL_API void Original_apply_image();
	void virtual_unk303() { }
}; // 0x80

struct PlayerHUDTrinket {
	int id; // 0x0
	int slot; // 0x4
	KAGE_Graphics_ImageBase * image; // 0x8
	char pad0[0xc]; // 0xc
}; // 0x18

struct PlayerHUDHeart {
	bool _visibility; // 0x0
	bool _eternalHeartVisibility; // 0x1
	bool _goldenHeartVisibility; // 0x2
	bool _fadeHeart; // 0x3
	char _flashType; // 0x4
	char pad0[0x3]; // 0x5
	char const * _spriteAnim; // 0x8
	char const * _spriteOverlayAnim; // 0xc
}; // 0x10

struct PlayerHUDActiveItem {
	int id; // 0x0
	char pad0[0x4]; // 0x4
	KAGE_Graphics_ImageBase * itemImage; // 0x8
	char pad1[0x4]; // 0xc
	KAGE_Graphics_ImageBase * bookImage; // 0x10
	char pad2[0x8]; // 0x14
	LIBZHL_API void RenderGfx(SourceQuad * sourceQuad, DestinationQuad * destQuad, ColorMod const & color);
}; // 0x1c

struct PlayerHUD {
	Entity_Player * _player; // 0x0
	HUD * _HUD; // 0x4
	short int _playerHudIndex; // 0x8
	char pad0[0x2]; // 0xa
	char _redHeartFlashCountdown; // 0xc
	char _soulHeartFlashCountdown; // 0xd
	char _goldHeartFlashCountdown; // 0xe
	char pad1[0x1]; // 0xf
	PlayerHUDHeart _heart[24]; // 0x10
	PlayerHUDActiveItem _activeItem[4]; // 0x190
	PlayerHUDTrinket _trinket[2]; // 0x200
	char pad2[0x4b0]; // 0x230
	LIBZHL_API void Update();
	LIBZHL_API void RenderActiveItem(unsigned int activeSlot, Vector const & pos, int playerHudLayout, float size, float alpha, bool unused);
	LIBZHL_API void RenderHearts(Vector * unk, ANM2 * sprite, int playerHudLayout, float scale, Vector pos);
	LIBZHL_API void UpdateHearts(PlayerHUDHeart * heart, int unkInt, Entity_Player * player);
	LIBZHL_API void RenderTrinket(unsigned int TrinketSlot, Vector * pos, float unused, float scale, bool unk);
	LIBZHL_API void RenderCraftingTable(Vector * pos, float scale);
	LIBZHL_API void RenderInventory(Vector * pos, float scale);
	LIBZHL_API void RenderSpellQueue(Vector * pos, float scale);
	inline Entity_Player* GetPlayer() { return this->_player; }
}; // 0x6e0

struct HUD {
	PlayerHUD _playerHUD[8]; // 0x0
	char pad0[0x98]; // 0x3700
	ANM2 _chargeBarSprite; // 0x3798
	char pad1[0x114]; // 0x38ac
	ANM2 _heartsSprite; // 0x39c0
	ANM2 _pickupHUDSprite; // 0x3ad4
	ANM2 _cardsPillsSprite; // 0x3be8
	HUD_Message _messageMain; // 0x3cfc
	HUD_Message _messageStack[6]; // 0x3ef0
	HUD_Message _messagePlayerHUD[4]; // 0x4aa8
	ANM2 _fortuneSprite; // 0x5278
	char pad2[0x8]; // 0x538c
	ANM2 _statsSprite; // 0x5394
	char pad3[0x8]; // 0x54a8
	float _bossHPBarFill; // 0x54b0
	char pad4[0x30]; // 0x54b4
	bool _isVisible; // 0x54e4
	char pad5[0x3]; // 0x54e5
	int _hudRefreshType; // 0x54e8
	char pad6[0x4]; // 0x54ec
	int _hudRefreshCountdown; // 0x54f0
	ANM2 _coopMenuSprite; // 0x54f4
	ANM2 _inventorySprite; // 0x5608
	ANM2 _craftingTableSprite; // 0x571c
	ANM2 _poopSpellsSprite; // 0x5830
	char pad7[0x70]; // 0x5944
	StatHUD _statHUD; // 0x59b4
	HistoryHUD _historyHUD; // 0x5c64
	LIBZHL_API void Render();
	LIBZHL_API void Update();
	LIBZHL_API void PostUpdate();
	LIBZHL_API void LoadGraphics();
	LIBZHL_API void FlashRedHearts(Entity_Player * player);
	LIBZHL_API void ShowItemText(Entity_Player * player, ItemConfig_Item * item);
	LIBZHL_API void ShowItemTextCustomUTF8(Entity_Player * player, char * title, char * subtitle);
	LIBZHL_API void ShowStackedItemTextCustomUTF16(wchar_t * title, wchar_t * subtitle, bool unused1, bool unused2);
	LIBZHL_API void ShowStackedItemTextCustomUTF8(char * title, char * subtitle, bool unused, bool isCurseDisplay);
	LIBZHL_API void ShowFortuneText(int * * param_1);
	LIBZHL_API void InvalidateCraftingItem(Entity_Player * player);
	LIBZHL_API int GetPlayerHUDLayout(int playerHudIndex, Entity_Player * player);
	inline PlayerHUD* GetPlayerHUD(int index) {
		if (index < 0 || index > 7) {
			return nullptr;
		}
		return &this->_playerHUD[index];
	}
}; // 0x5c90

struct Level {
	unsigned int _stage; // 0x0
	unsigned int _stageType; // 0x4
	char pad0[0x181fc]; // 0x8
	unsigned int _greedwavesclearedwithoutredheartdamage; // 0x18204
	char pad1[0x24]; // 0x18208
	unsigned int _levelStateFlag; // 0x1822c
	char pad2[0x6dc]; // 0x18230
	LIBZHL_API void SetStage(int stageid, int alt);
	LIBZHL_API void Init(bool resetLilPortalRoom);
	LIBZHL_API void Update();
	LIBZHL_API void ChangeRoom(int targetRoomIDX, int dimension);
	LIBZHL_API void swap_rooms(int leftIdx, int rightIdx);
	LIBZHL_API bool TryInitializeExtraBossRoom(unsigned int seed);
	LIBZHL_API bool CanSpawnDoorOutline(int roomIDX, unsigned int doorSlot);
	LIBZHL_API bool HasAbandonedMineshaft();
	LIBZHL_API bool HasMirrorDimension();
	LIBZHL_API bool HasPhotoDoor();
	LIBZHL_API std_string GetName();
	LIBZHL_API void SetNextStage();
	LIBZHL_API static bool __stdcall IsStageAvailable(int LevelStage, int StageType);
	LIBZHL_API bool place_room(LevelGenerator_Room * slot, RoomConfig_Room * data, unsigned int seed, unsigned int unk);
	LIBZHL_API bool IsNextStageAvailable();
	LIBZHL_API bool IsAltPath();
	LIBZHL_API void InitializeDevilAngelRoom(bool ForceAngel, bool ForceDevil);
	LIBZHL_API void InitializeGenesisRoom();
	LIBZHL_API bool TryInitializeBlueRoom(int currentIdx, int destinationIdx, int direction);
	LIBZHL_API RoomDescriptor * GetRoomByIdx(int idx, int dimension);
	LIBZHL_API int GetRandomRoomIndex(bool IAmErrorRoom, unsigned int Seed);
	LIBZHL_API void generate_dungeon(RNG * RNG);
	LIBZHL_API bool place_rooms_backwards(LevelGenerator * levelGen, BackwardsStageDesc * backwardsStage, unsigned int stage, unsigned int minDifficulty, unsigned int maxDifficulty);
	LIBZHL_API void StartMamaMega(Vector * Position, Entity_Player * player);
	LIBZHL_API static RoomConfig_Room * __stdcall read_room_config(GameStateRoomConfig * room, std_deque_RoomConfigRoom * deque);
	LIBZHL_API static void __stdcall write_room_config(RoomConfig_Room * roomConfig, GameStateRoomConfig * gameStateRoom, std_deque_RoomConfigRoom * deque);
	LIBZHL_API void DEBUG_goto_room(RoomConfig_Room * roomConfig);
	LIBZHL_API void reset_room_list(bool resetLilPortalRoom);
	LIBZHL_API void RestoreGameState(GameState * gameState);
	LIBZHL_API static int __stdcall GetStageID();
}; // 0x1890c

struct ProceduralEffect_ConditionData_EntitySpawn {
	char pad0[0x4]; // 0x0
	short int variant; // 0x4
	short int type; // 0x6
}; // 0x8

struct ProceduralEffect_ActionData_UseActiveItem {
	int collectibleId; // 0x0
}; // 0x4

struct ProceduralEffect_ActionData_AddTemproryEffect {
	int collectibleId; // 0x0
}; // 0x4

struct ProceduralEffect_ActionData_AreaDamage {
	char pad0[0x8]; // 0x0
	float radius; // 0x8
	float damage; // 0xc
	long long int flags1; // 0x10
	long long int flags2; // 0x18
}; // 0x20

struct ProceduralEffect_ActionData_Fart {
	float fartScale; // 0x0
	char pad0[0x8]; // 0x4
	float radius; // 0xc
}; // 0x10

struct ProceduralEffect_ActionData_SpawnEntity {
	short int variant; // 0x0
	short int type; // 0x2
}; // 0x4

struct ProceduralEffect_ActionData_ConvertEntities {
	short int fromVariant; // 0x0
	short int fromType; // 0x2
	short int toVariant; // 0x4
	short int toType; // 0x6
}; // 0x8

struct ProceduralEffect {
	int effectConditionType; // 0x0
	int effectActionType; // 0x4
	char pad0[0x28]; // 0x8
	float triggerChanceScale; // 0x30
	char pad1[0x2c]; // 0x34
	float score; // 0x60
	char pad2[0x4]; // 0x64
    enum ConditionType{
        CONDITION_ACTIVE,
        CONDITION_TEAR_FIRE,
        CONDITION_ENEMY_HIT,
        CONDITION_ENEMY_KILL,
        CONDITION_DAMAGE_TAKEN,
        CONDITION_ROOM_CLEAR,
        CONDITION_ENTITY_SPAWN,
        CONDITION_PICKUP_COLLECTED,
        CONDITION_CHAIN,
    };

    enum ActionType{
        ACTION_USE_ACTIVE_ITEM,
        ACTION_ADD_TEMPRORY_EFFECT,
        ACTION_CONVERT_ENTITIES,
        ACTION_AREA_DAMAGE,
        ACTION_SPAWN_ENTITY,
        ACTION_FART,
    };

    union ConditionData{
        struct ProceduralEffect_ConditionData_EntitySpawn entitySpawn;
    };

    union ActionData{
        struct ProceduralEffect_ActionData_UseActiveItem useActiveItem;
        struct ProceduralEffect_ActionData_AddTemproryEffect addTempraryEffect;
        struct ProceduralEffect_ActionData_SpawnEntity spawnEntity;
        struct ProceduralEffect_ActionData_ConvertEntities convertEntities;
        struct ProceduralEffect_ActionData_AreaDamage areaDamage;
        struct ProceduralEffect_ActionData_Fart fart;
    };

    inline union ConditionData * GetConditionData(){
        return (union ConditionData*)((char*)this + 0x8);
    }
    inline union ActionData * GetActionData(){
        return (union ActionData*)((char*)this + 0x10);
    }
    
    // FIXME: ColorMod class
    // inline ColorMod* GetColor(){
    //     return (ColorMod*)((char *)this + 0x34);
    // }
}; // 0x68

struct ProceduralItem {
	ItemConfig_Item * item; // 0x0
	int _id; // 0x4
	char pad0[0x8]; // 0x8
	ItemConfig_Item * targetItem; // 0x10
	float damage; // 0x14
	float firedelay; // 0x18
	float speed; // 0x1c
	float range; // 0x20
	float shotspeed; // 0x24
	float luck; // 0x28
	char pad1[0xc]; // 0x2c
    inline std::vector<ProceduralEffect*>* GetEffects() { return (std::vector<ProceduralEffect*>*)((char*)this + 0x2c); }
}; // 0x38

struct ProceduralItemManager {
	char pad0[0x10]; // 0x0
	KAGE_SmartPointer_ImageBase _proceduralItemTexture; // 0x10
	LIBZHL_API int CreateProceduralItem(unsigned int seed, unsigned int unk);
    inline std::vector<ProceduralItem*>* GetProceduralItems() { return (std::vector<ProceduralItem*>*)((char*)this + 0x0); }
}; // 0x18

struct GenericPrompt {
	ANM2 _anm2; // 0x0
	char pad0[0x14]; // 0x114
	int _currentSelection; // 0x128
	int _submittedSelection; // 0x12c
	char pad1[0x4]; // 0x130
	LIBZHL_API void Initialize(bool SmallPrompt);
	LIBZHL_API void Show(bool UNK);
	LIBZHL_API bool IsActive();
	LIBZHL_API void SetImageToVictoryRun(std_string * unused);
	LIBZHL_API void Update(bool processInput);
	LIBZHL_API void Render();
	LIBZHL_API void SetText(char const * param_1, char const * param_2, char const * param_3, char const * param_4, char const * param_5);
	LIBZHL_API static void Disappear(ANM2 * anm2);
	
	/*GenericPrompt() {
		this->constructor();
	}
	*/
	
}; // 0x134

struct ItemOverlay {
	int _state; // 0x0
	int _overlayID; // 0x4
	ANM2 _sprite; // 0x8
	char pad0[0x1028]; // 0x11c
	int _delay; // 0x1144
	Entity_Player * _player; // 0x1148
	ANM2 _megaMushPlayerSprite; // 0x114c
	LIBZHL_API void Show(int eOverlayID, int delay, Entity_Player * player);
	LIBZHL_API void Update(bool unk);
	LIBZHL_API void Render();
	inline int* GetOverlayID() { return &_overlayID; } 
	inline ANM2* GetSprite() { return &_sprite; } 
	inline int* GetDelay() { return &_delay; } 
	inline Entity_Player* GetPlayer() { &_player; }
	
	enum eItemOverlayState {
		INACTIVE = 0,
		WAITING = 1,
		ACTIVE = 2,
	};
}; // 0x1260

struct GameOver {
	char pad0[0x8]; // 0x0
	ANM2 anm2; // 0x8
	char pad1[0x10]; // 0x11c
	EntityConfig_Entity * modEntityConfig; // 0x12c
	LIBZHL_API void Show();
	LIBZHL_API void RenderItemSprite(int itemId, Vector * pos, ColorMod * color, Vector * scale, BlendMode * blendMode);
}; // 0x130

struct LeaderboardEntryData {
	int _stageBonus; // 0x0
	int _schwagBonus; // 0x4
	char pad0[0x2c]; // 0x8
	int _isDead; // 0x34
	int _encodedGameVersion; // 0x38
}; // 0x3c

struct LeaderboardEntry {
	unsigned int _numDisplayedEntry; // 0x0
	char pad0[0x18]; // 0x4
	LeaderboardEntryData * _entriesData; // 0x1c
	char pad1[0x8]; // 0x20
}; // 0x28

struct Leaderboard {
	char pad0[0x4]; // 0x0
	int _displayState; // 0x4
	char pad1[0x8]; // 0x8
	ANM2 _scoreMenuSprite; // 0x10
	ANM2 _leaderboardMenuSprite; // 0x124
	char pad2[0x20]; // 0x238
	DailyChallenge _dailyChallenge; // 0x258
	ScoreSheet _scoreSheet; // 0x30c
	char pad3[0x14]; // 0x39c
	int _isLeaderboardClosing; // 0x3b0
	LIBZHL_API void ProcessInput();
	LIBZHL_API void get_leaderboard(int RankingState, int LiveSelectionState);
	LIBZHL_API void Show(unsigned int Date, ScoreSheet * ScoreSheet, bool SubmitScore, bool Group);

}; // 0x3b4

struct StageTransition {
	char pad0[0x10]; // 0x0
	bool _sameStage; // 0x10
	char pad1[0xf]; // 0x11
}; // 0x20

struct PlayerManager {
	vector_EntityPlayerPtr _playerList; // 0x0
	char pad0[0x74]; // 0xc
	Entity_Player * _esauJrState[4]; // 0x80
	char pad1[0x28]; // 0x90
	RNG _rng; // 0xb8
	LIBZHL_API Entity_Player * SpawnCoPlayerBaby(int babyID);
	LIBZHL_API Entity_Player * SpawnCoPlayer2(int playerType);
	LIBZHL_API Entity_Player * FirstCollectibleOwner(CollectibleType collectibleID, RNG * * rng, bool lazSharedGlobalTag);
	LIBZHL_API Entity_Player * RandomCollectibleOwner(CollectibleType collectibleID, unsigned int seed, RNG * * returnRNG);
	LIBZHL_API bool IsCoopPlay();
	LIBZHL_API int GetNumCollectibles(CollectibleType type);
	LIBZHL_API bool AnyoneHasTrinket(TrinketType trinketType);
	LIBZHL_API Entity_Player * RandomTrinketOwner(TrinketType trinketType, unsigned int seed, RNG * * returnRNG);
	LIBZHL_API Entity_Player * FirstPlayerByType(unsigned int type);
	LIBZHL_API Entity_Player * FirstBirthrightOwner(unsigned int type);
	LIBZHL_API bool HasTemporaryEffect(ItemConfig_Item * item);
	LIBZHL_API int GetTrinketMultiplier(int TrinketID);
	LIBZHL_API Entity_Player * GetPlayer(int param1);
	LIBZHL_API void TriggerNewRoom_TemporaryEffects();
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API static bool __stdcall CoopBabiesOnly();
	LIBZHL_API void spawn_selected_baby(int param_1, int param_2);
	LIBZHL_API void RemoveCoPlayer(Entity_Player * player, bool unusedBool);
	LIBZHL_API void RestoreGameState(GameState * state);
	LIBZHL_API void RestoreGameState_PostLevelInit(GameState * state);
	LIBZHL_API void Update();
	LIBZHL_API void AutoReassignControllers();
}; // 0xc8

struct Menu_Options {
	char pad0[0x8]; // 0x0
	int SelectedElement; // 0x8
	float PositionX_duplicate; // 0xc
	float PositionY_duplicate; // 0x10
	float PositionX; // 0x14
	float PositionY; // 0x18
	char pad1[0x8]; // 0x1c
	ANM2 OptionsSprite; // 0x24
	ANM2 GammaMenuSprite; // 0x138
	int HoldLeftCounter; // 0x24c
	int HoldRightCounter; // 0x250
	int HoldUpDownCounter; // 0x254
	char pad2[0x30]; // 0x258
         inline ANM2* GetOptionsSprite() { return &this->OptionsSprite; }
         inline ANM2* GetGammaMenuSprite() { return &this->GammaMenuSprite; }
    
}; // 0x288

struct GenericPopup {
	char pad0[0x120]; // 0x0
	LIBZHL_API void Render();
}; // 0x120

struct PauseScreen {
	int state; // 0x0
	char pad0[0x4]; // 0x4
	int selectedelement; // 0x8
	char pad1[0x20]; // 0xc
	ANM2 mainsprite; // 0x2c
	ANM2 minisprite; // 0x140
	ANM2 statssprite; // 0x254
	ANM2 mystuffminispritebase; // 0x368
	char pad2[0x134]; // 0x47c
	Menu_Options menuoptions; // 0x5b0
	char pad3[0x8]; // 0x838
	CompletionWidget completionWidget; // 0x840
	char pad4[0x498]; // 0x95c
	LIBZHL_API void Render();
	LIBZHL_API void Show();
	inline CompletionWidget* GetCompletionWidget() { return &this->completionWidget; } 
}; // 0xdf4

struct GameStateItemPool {
	std_vector_float _poolsItemWeights[31]; // 0x0
	unsigned int _bibleUpgrades[31]; // 0x174
	unsigned int _seed; // 0x1f0
	int _lastPool; // 0x1f4
	unsigned int _itemPoolRNGseed; // 0x1f8
	unsigned int _trinketPoolRNGseed; // 0x1fc
	char pad0[0x8]; // 0x200
	vector_bool _removedCollectibles; // 0x208
	vector_TrinketPoolItem _trinketPoolItems; // 0x218
	char pad1[0x4]; // 0x224
	int _pillEffects[15]; // 0x228
	bool _identifiedPillEffects[15]; // 0x264
	char pad2[0x1]; // 0x273
	unsigned short int _remainingGenesisItems[31]; // 0x274
	char pad3[0x2]; // 0x2b2
}; // 0x2b4

struct GameStateBossPool {
	unsigned int _poolSeeds[37]; // 0x0
	vector_bool _removedBosses; // 0x94
}; // 0xa4

struct Seeds {
	bool _isCustomRun; // 0x0
	char pad0[0x3]; // 0x1
	unsigned int _gameStartSeed; // 0x4
	RNG _rng; // 0x8
	unsigned int _stageSeeds[14]; // 0x18
	unsigned int _playerInitSeed; // 0x50
	char pad1[0x4]; // 0x54
	int _seedEffectsCount; // 0x58
	LIBZHL_API static int __stdcall String2Seed(std_string * str);
	LIBZHL_API void __fastcall constructor();
	LIBZHL_API void set_start_seed(unsigned int seed);
	LIBZHL_API void construct_from_copy(Seeds * right);
	LIBZHL_API bool HasSeedEffect(unsigned int seedEffect);
	LIBZHL_API bool AchievementUnlocksDisallowed();
}; // 0x5c

struct GameState {
	char pad0[0x19c]; // 0x0
	unsigned int _roomCount; // 0x19c
	RoomDescriptor _rooms[527]; // 0x1a0
	GameStateRoomConfig _roomConfigs[527]; // 0x17c68
	char pad1[0x800]; // 0x1951c
	int _roomIdx; // 0x19d1c
	int _lastRoomIdx; // 0x19d20
	char pad2[0x4c]; // 0x19d24
	unsigned int _playerCount; // 0x19d70
	GameStatePlayer _players[8]; // 0x19d74
	GameStatePlayer _esauJrStates[4]; // 0x1cb54
	GameStateItemPool _itemPool; // 0x1e244
	GameStateBossPool _bossPool; // 0x1e4f8
	Seeds _seeds; // 0x1e59c
	char pad3[0x34]; // 0x1e5f8
	BackwardsStageDesc _backwardsStages[7]; // 0x1e62c
	char pad4[0x10]; // 0x1fc0c
	unsigned int _checksum; // 0x1fc1c
	unsigned int _rerunChecksum; // 0x1fc20
	std_string _localGameStatePath; // 0x1fc24
	std_string _localRerunStatePath; // 0x1fc3c
	char pad5[0x18]; // 0x1fc54
	std_string _cloudGameStatePath; // 0x1fc6c
	std_string _cloudRerunStatePath; // 0x1fc84
	GameStateIO * _saveFile; // 0x1fc9c
	LIBZHL_API void Clear();
	LIBZHL_API bool write(GameStateIO * * gameStateIO);
	LIBZHL_API bool write_rerun(GameStateIO * * gameStateIO);
	LIBZHL_API bool read(GameStateIO * * gameStateIO, bool isLocalRun);
	LIBZHL_API bool read_rerun(GameStateIO * * gameStateIO);
	LIBZHL_API void Delete();
	LIBZHL_API void DeleteRerun();
}; // 0x1fca0

struct GlowingHourglassState {
	bool _isUsable; // 0x0
	char pad0[0x3]; // 0x1
	GameState _gameState; // 0x4
	int _leaveDoor; // 0x1fca4
	unsigned int _timeCounter; // 0x1fca8
	int _eventCounters[523]; // 0x1fcac
}; // 0x204d8

struct Game {
	unsigned int _stage; // 0x0
	unsigned int _stageType; // 0x4
	bool _bossChallenge; // 0x8
	bool _devilRoomDisabled; // 0x9
	char pad0[0x2]; // 0xa
	unsigned int _curses; // 0xc
	char pad1[0x4]; // 0x10
	RoomDescriptor _gridRooms[507]; // 0x14
	RoomDescriptor _negativeGridRooms[20]; // 0x16c7c
	unsigned int _roomOffset[507]; // 0x17adc
	char pad2[0x4]; // 0x182c8
	unsigned int _nbRooms; // 0x182cc
	unsigned int _startingRoomIdx; // 0x182d0
	RNG _generationRNG; // 0x182d4
	char pad3[0x1c]; // 0x182e4
	Room * _room; // 0x18300
	unsigned int _currentRoomIdx; // 0x18304
	unsigned int _lastRoomIdx; // 0x18308
	unsigned int _currentDimensionIdx; // 0x1830c
	unsigned int _lastRoomDimensionIdx; // 0x18310
	unsigned int _lastBossRoomListIdx; // 0x18314
	unsigned int _leaveDoor; // 0x18318
	unsigned int _enterDoor; // 0x1831c
	char pad4[0xc]; // 0x18320
	unsigned int _dungeonPlacementSeed; // 0x1832c
	char pad5[0x4]; // 0x18330
	unsigned int _greedModeWave; // 0x18334
	unsigned int _greedWaveSeed[12]; // 0x18338
	char pad6[0x8]; // 0x18368
	unsigned int _greedModeTreasureRoomIdx; // 0x18370
	char pad7[0x28]; // 0x18374
	unsigned int _levelStateFlags; // 0x1839c
	char pad8[0x4]; // 0x183a0
	vector_EntitySaveState _myosotisPickups; // 0x183a4
	char pad9[0x560]; // 0x183b0
	RoomConfig _roomConfig; // 0x18910
	char pad10[0x8]; // 0x1a738
	ItemPool _itemPool; // 0x1a740
	BossPool _bossPool; // 0x1af70
	RoomTransition _roomTransition; // 0x1b83c
	StageTransition _stageTransition; // 0x1ba78
	char pad11[0x10]; // 0x1ba98
	PlayerManager _playerManager; // 0x1baa8
	char pad12[0x14]; // 0x1bb70
	Seeds _seedEffects; // 0x1bb84
	char pad13[0x454]; // 0x1bbe0
	ItemOverlay _itemOverlay; // 0x1c034
	char pad14[0x234]; // 0x1d294
	GameOver _gameOver; // 0x1d4c8
	Leaderboard _leaderboard; // 0x1d5f8
	HUD _hud; // 0x1d9ac
	PauseScreen _pauseScreen; // 0x2363c
	char pad15[0x1014]; // 0x24430
	Minimap _minimap; // 0x25444
	char pad16[0x4]; // 0x25a6c
	int _frameCount; // 0x25a70
	char pad17[0x10]; // 0x25a74
	Vector _screenShakeOffset; // 0x25a84
	char pad18[0x20]; // 0x25a8c
	bool _triggerWindowResize; // 0x25aac
	char pad19[0xf]; // 0x25aad
	unsigned int _debugFlags; // 0x25abc
	unsigned long long int _gameStateFlags; // 0x25ac0
	char pad20[0x4]; // 0x25ac8
	int _lastDevilRoomStage; // 0x25acc
	int _treasureRoomsVisited; // 0x25ad0
	int _planetariumsVisited; // 0x25ad4
	char pad21[0xc]; // 0x25ad8
	int _donationModGreed; // 0x25ae4
	int _donationModAngel; // 0x25ae8
	int _shopVisits; // 0x25aec
	char pad22[0x8]; // 0x25af0
	EntityFactory * _entityFactory; // 0x25af8
	unsigned int _challenge; // 0x25afc
	bool _isRerun; // 0x25b00
	bool _isDebug; // 0x25b01
	char pad23[0x3e]; // 0x25b02
	Ambush _ambush; // 0x25b40
	char pad24[0x1c]; // 0x25b8c
	DailyChallenge _dailyChallenge; // 0x25ba8
	ScoreSheet _scoreSheet; // 0x25c5c
	char pad25[0x4]; // 0x25cec
	GenericPrompt _genericPrompt; // 0x25cf0
	char pad26[0x114]; // 0x25e24
	int _lastLevelWithoutHalfHp; // 0x25f38
	char pad27[0x4]; // 0x25f3c
	unsigned int _difficulty; // 0x25f40
	int _lastLevelWithDamage; // 0x25f44
	char pad28[0x19]; // 0x25f48
	bool _isStartingFromState; // 0x25f61
	bool _isStoringGlowingHourglassState; // 0x25f62
	bool _isRestoringGlowingHourglassState; // 0x25f63
	GlowingHourglassState _glowingHourglassStates[2]; // 0x25f64
	int _currentGlowingHourglassSlot; // 0x66914
	char pad29[0x4]; // 0x66918
	bool _shouldLerpColorModState; // 0x6691c
	char pad30[0x3]; // 0x6691d
	ColorModState _currentColorModifier; // 0x66920
	ColorModState _targetColorModifier; // 0x66938
	ColorModState _lerpColorModifier; // 0x66950
	char pad31[0x2c]; // 0x66968
	DebugRenderer _debugRenderer; // 0x66994
	char pad32[0x7]; // 0x66995
	float _lightningIntensity; // 0x6699c
	float _dizzyIntensity; // 0x669a0
	float _dizzyTargetIntensity; // 0x669a4
	float _dizzyIntensityChangeSpeed; // 0x669a8
	char pad33[0x4]; // 0x669ac
	vector_ErasedEntities _erasedEntities; // 0x669b0
	ProceduralItemManager _proceduralItemManager; // 0x669bc
	char pad34[0x1c]; // 0x669d4
	BackwardsStageDesc _backwardsStages[7]; // 0x669f0
	char pad35[0x4]; // 0x67fd0
	Console _console; // 0x67fd4
	char pad36[0xc]; // 0x680dc
	LIBZHL_API void constructor();
	LIBZHL_API void StartDebug(int levelStage, int stageType, int difficulty, std_string * unk);
	LIBZHL_API void StartFromRerunState(GameState * state);
	LIBZHL_API void RestoreState(GameState * state, bool startGame);
	LIBZHL_API void SaveState(GameState * state);
	LIBZHL_API void ResetState();
	LIBZHL_API GlowingHourglassState * GetGlowingHourglassState();
	LIBZHL_API bool IsPaused();
	LIBZHL_API static bool __stdcall IsHardMode();
	LIBZHL_API Entity * Spawn(unsigned int type, unsigned int variant, Vector const & position, Vector const & velocity, Entity * spawner, unsigned int subtype, unsigned int seed, unsigned int unk);
	LIBZHL_API void ShakeScreen(int timeout);
	LIBZHL_API void MakeShockwave(Vector const & pos, float amplitude, float speed, int duration);
	LIBZHL_API Entity_Player * GetPlayer(unsigned int Index);
	LIBZHL_API int GetNumPlayers();
	LIBZHL_API void Update();
	LIBZHL_API bool AchievementUnlocksDisallowed();
	LIBZHL_API bool PlaceRoom(LevelGenerator_Room * room, RoomConfig_Room * data, unsigned int Seed, int unk);
	LIBZHL_API void UpdateVisibility();
	LIBZHL_API int * GetRoomDescriptorsOffsetsArrayForDimension(int dimension);
	LIBZHL_API RoomDescriptor * GetRoomByIdx(int idx, int dimension);
	LIBZHL_API RoomDescriptor * GetCurrentRoomDesc();
	LIBZHL_API float GetPlanetariumChance();
	LIBZHL_API void StartStageTransition(bool SameStage, int param_2, Entity_Player * param_3);
	LIBZHL_API void Render();
	LIBZHL_API void ToggleDebugFlag(unsigned int flag);
	LIBZHL_API bool GetDebugFlag(unsigned int flag);
	LIBZHL_API void BombDamage(Vector * pos, float damage, float radius, bool lineCheck, Entity * source, BitSet128 tearFlags, unsigned long long int damageFlags, bool damageSource);
	LIBZHL_API void BombExplosionEffects(Vector * pos, float damage, BitSet128 tearFlags, ColorMod * Color, Entity * source, float radiusMult, bool lineCheck, unsigned long long int damageFlags, bool damageSource);
	LIBZHL_API void BombTearflagEffects(Vector * pos, float radius, BitSet128 tearFlags, Entity * source, float radiusMult);
	LIBZHL_API Entity * SpawnBombCrater(Vector * Pos, float Scale);
	LIBZHL_API static void __stdcall DevolveEnemy(Entity * ent, int * unk);
	LIBZHL_API void NetStart(void * unk, int challenge, Seeds seed, unsigned int difficulty, GameState * state);
	LIBZHL_API static void __stdcall ProcessInput();
	LIBZHL_API void Start(int playertype, int challenge, Seeds seeds, unsigned int difficulty);
	LIBZHL_API void StartDailyChallenge(DailyChallenge * daily);
	LIBZHL_API void NextVictoryLap();
	LIBZHL_API void SetColorModifier(ColorModState * color, bool lerp, float rate);
	LIBZHL_API ChallengeParam * GetChallengeParams();
	LIBZHL_API static bool __stdcall IsGreedBoss();
	LIBZHL_API static bool __stdcall IsGreedFinalBoss();
	LIBZHL_API bool IsGreedMode();
	LIBZHL_API void End(int EndingID);
	LIBZHL_API void FadeOut(float Speed, int FadeoutTarget, KColor * color);
	LIBZHL_API void MoveToRandomRoom(bool iAmErrorRoom, int Seed, Entity_Player * player);
	LIBZHL_API void __stdcall Exit(bool ShouldSave);
	LIBZHL_API void SetBloom(int Time, float Strength);
	LIBZHL_API unsigned int GetStageID(bool unused);
	LIBZHL_API bool GetGameStateFlag(unsigned int GameStateFlag);
	LIBZHL_API bool GetLevelStateFlag(unsigned int LevelStateFlag);
	LIBZHL_API bool LevelHasPhotoDoor();
	LIBZHL_API void __stdcall SaveBackwardsStage(int stage);
	LIBZHL_API static Entity_Effect * __stdcall ChainLightning(Vector * position, float damage, BitSet128 tearFlags, Entity * spawner);
	LIBZHL_API bool HasSeedEffect(int SeedEffect);
	LIBZHL_API static void __stdcall AddErasedEnemy(Entity * entity);
	LIBZHL_API static bool __stdcall ShouldEraseEnemy(Entity * Entity);
	LIBZHL_API static void FixErasedEnemyID(int * type, int * variant, int * subtype);
	Game()
	{
		this->constructor();
	}
	
	inline Level* GetLevel() { return (Level*)this; }
    
    uint32_t GetNbRooms() const 
    { 
        return this->_nbRooms; 
    }
    
	inline Console* GetConsole() { return &this->_console; }
	
	inline ItemOverlay* GetItemOverlay() { return &this->_itemOverlay; }
	
	inline Ambush* GetAmbush() { return &this->_ambush; }
	
	inline Room* GetCurrentRoom() { return this->_room; }
		
	inline int GetCurrentRoomIdx() {return this->_currentRoomIdx; }

    inline int GetDimension() {return this->_currentDimensionIdx;}
	
	inline int GetLastBossRoomListIdx() {return this->_lastBossRoomListIdx; }
	
	inline int GetGreedModeWave() { return this->_greedModeWave; }
	
	inline const unsigned int* GetLevelStateFlags() { return &this->_levelStateFlags; }
	
	inline RoomConfig* GetRoomConfig() { return &this->_roomConfig; }
	
	inline PlayerManager* GetPlayerManager() { return &this->_playerManager; }
	
	inline int GetLastDevilRoomStage() { return this->_lastDevilRoomStage; }
	
	inline int GetLastLevelWithDamage() { return this->_lastLevelWithDamage; }
	
	inline int GetLastLevelWithoutHalfHp() { return this->_lastLevelWithoutHalfHp; }

	inline int GetTreasureRoomsVisited() { return this->_treasureRoomsVisited; }
	
	inline int GetPlanetariumsVisited() { return this->_planetariumsVisited; }
	
	inline bool IsPauseMenuOpen() { return this->_pauseScreen.state > 0; }
	
	inline PauseScreen* GetPauseMenu() { return &this->_pauseScreen; }
	
	inline DailyChallenge GetDailyChallenge() { return this->_dailyChallenge; }
	
	inline unsigned int GetChallenge() { return this->_challenge; }
	
	inline bool* IsDebug() { return &this->_isDebug; }
	
	inline unsigned int* GetDebugFlags() { return &this->_debugFlags; }
	
	inline ScoreSheet* GetScoreSheet() { return &this->_scoreSheet; }
	
	inline int GetDifficulty() {return this->_difficulty; }

	inline int GetMode() { return this->IsGreedMode() ? 1 : 0; }
	
	inline ProceduralItemManager* GetProceduralItemManager() {return &this->_proceduralItemManager; }
    
	inline HUD* GetHUD() { return &this->_hud; }

	inline PlayerHUD* GetPlayerHUD(int playerId) { return this->_hud.GetPlayerHUD(playerId); }
	
	inline Minimap* GetMinimap() { return &this->_minimap; }
	
	inline RoomTransition* GetRoomTransition() { return &this->_roomTransition; }

    inline StageTransition* GetStageTransition() { return &this->_stageTransition; }
	
	inline DebugRenderer* GetDebugRenderer() { return &this->_debugRenderer; }
	
	inline GenericPrompt* GetGenericPrompt() { return &this->_genericPrompt; }

	inline GameOver* GetGameOver() { return &this->_gameOver; }

	inline ColorModState* GetCurrentColorModifier() { return &this->_currentColorModifier; }
	inline ColorModState* GetTargetColorModifier() { return &this->_targetColorModifier; }
	inline ColorModState* GetLerpColorModifier() { return &this->_lerpColorModifier; }

    void LIBZHL_API AddErasedEnemyByIds(int type, int variant, int subtype);
    void LIBZHL_API RemoveErasedEnemy(int type, int variant, int subtype);
    bool LIBZHL_API IsErased(int type, int variant, int subtype);
}; // 0x680e8

struct GameStateIO {
	LIBZHL_API void Free(bool deletePtr);
	LIBZHL_API void Free_Original(bool deletePtr);
	LIBZHL_API long int GetSize();
	LIBZHL_API long int GetSize_Original();
	LIBZHL_API long int GetPosition();
	LIBZHL_API long int GetPosition_Original();
	LIBZHL_API void SetPosition(long int offset, int origin);
	LIBZHL_API void SetPosition_Original(long int offset, int origin);
	LIBZHL_API bool IsEof();
	LIBZHL_API bool IsEof_Original();
	LIBZHL_API unsigned int Read(void * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int Read_Original(void * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int ReadLine(char * buffer, unsigned int maxSize);
	LIBZHL_API unsigned int ReadLine_Original(char * buffer, unsigned int maxSize);
	LIBZHL_API unsigned int Write(void const * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int Write_Original(void const * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API void Flush();
	LIBZHL_API void Flush_Original();
	LIBZHL_API bool OpenRB(char const * filePath);
	LIBZHL_API bool OpenRB_Original(char const * filePath);
	LIBZHL_API bool OpenWB(char const * filePath);
	LIBZHL_API bool OpenWB_Original(char const * filePath);
	LIBZHL_API void CloseFile();
	LIBZHL_API void CloseFile_Original();
	LIBZHL_API bool IsOpen();
	LIBZHL_API bool IsOpen_Original();
	LIBZHL_API void Close();
	LIBZHL_API void Close_Original();
	LIBZHL_API char const * GetFilePath();
	LIBZHL_API char const * GetFilePath_Original();
}; // 0x1

struct GlobalPost {

}; // 0x1

struct GridEntityDesc {
	int _type; // 0x0
	int _variant; // 0x4
	int _state; // 0x8
	int _spawnCount; // 0xc
	unsigned int _spawnSeed; // 0x10
	int _varData; // 0x14
	bool _initialized; // 0x18
	char pad0[0x3]; // 0x19
	unsigned int _variableSeed; // 0x1c
}; // 0x20

struct GridEntity {
	char pad0[0x4]; // 0x0
	GridEntityDesc _desc; // 0x4
	unsigned int _gridIndex; // 0x24
	unsigned int _spawnFrame; // 0x28
	RNG _rng; // 0x2c
	int _collisionClass; // 0x3c
	ANM2 _sprite; // 0x40
	LIBZHL_API void Init(unsigned int Seed);
	LIBZHL_API void hurt_func(Entity * ent, float DamageAmount, int PlayerDamage, unsigned long long int DamageFlags, bool IgnoreGridCollisionClass);
	LIBZHL_API void hurt_surroundings(float Distance, float PlayerDistance, float DamageAmount, int PlayerDamage, unsigned long long int DamageFlags, bool IgnoreGridCollisionClass);
	LIBZHL_API Vector * GetRenderPosition(Vector * buffer);
	LIBZHL_API bool IsBreakableRock();
	LIBZHL_API bool IsEasyCrushableOrWalkable();
	LIBZHL_API bool IsDangerousCrushableOrWalkable();
	void virtual_unk304() { }
	void virtual_unk305() { }
	void virtual_unk306() { }
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API bool Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Original_Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API bool Original_Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk307() { }
	void virtual_unk308() { }
	void virtual_unk309() { }
	void virtual_unk310() { }
	inline GridEntityDesc* GetDesc() { return &this->_desc; }
	inline int GetType() { return this->_desc._type; }
}; // 0x154

struct GridEntity_Decoration : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk311() { }
	void virtual_unk312() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk313() { }
	void virtual_unk314() { }
	void virtual_unk315() { }
	void virtual_unk316() { }
	void virtual_unk317() { }
	void virtual_unk318() { }
}; // 0x154

struct GridEntity_Door : public GridEntity {
	char pad0[0x14]; // 0x154
	ANM2 _extraSprite; // 0x168
	char pad1[0x4]; // 0x27c
	int _targetRoomIdx; // 0x280
	unsigned int _previousState; // 0x284
	unsigned int _previousVariant; // 0x288
	char pad2[0x60]; // 0x28c
	LIBZHL_API void play_animation();
	LIBZHL_API void SetRoomTypes(int CurrentRoomType, int TargetRoomType);
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk319() { }
	void virtual_unk320() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk321() { }
	void virtual_unk322() { }
	void virtual_unk323() { }
	void virtual_unk324() { }
	void virtual_unk325() { }
	void virtual_unk326() { }
}; // 0x2ec

struct GridEntity_Fire : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API bool Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Original_Hurt(int damage, EntityRef * source);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk327() { }
	void virtual_unk328() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk329() { }
	void virtual_unk330() { }
	void virtual_unk331() { }
	void virtual_unk332() { }
	void virtual_unk333() { }
}; // 0x154

struct GridEntity_Gravity : public GridEntity {
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk334() { }
	void virtual_unk335() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk336() { }
	void virtual_unk337() { }
	void virtual_unk338() { }
	void virtual_unk339() { }
	void virtual_unk340() { }
	void virtual_unk341() { }
	void virtual_unk342() { }
}; // 0x154

struct GridEntity_Lock : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API void TryUnlock(Entity_Player * player, bool force);
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk343() { }
	void virtual_unk344() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk345() { }
	void virtual_unk346() { }
	void virtual_unk347() { }
	void virtual_unk348() { }
	void virtual_unk349() { }
	void virtual_unk350() { }
}; // 0x158

struct GridEntity_Pit : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk351() { }
	void virtual_unk352() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk353() { }
	void virtual_unk354() { }
	void virtual_unk355() { }
	void virtual_unk356() { }
	void virtual_unk357() { }
	void virtual_unk358() { }
}; // 0x158

struct GridEntity_Poop : public GridEntity {
	char pad0[0x20]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API bool Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Original_Hurt(int damage, EntityRef * source);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk359() { }
	void virtual_unk360() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk361() { }
	void virtual_unk362() { }
	void virtual_unk363() { }
	void virtual_unk364() { }
	void virtual_unk365() { }
}; // 0x174

struct GridEntity_PressurePlate : public GridEntity {
	char pad0[0x128]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk366() { }
	void virtual_unk367() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk368() { }
	void virtual_unk369() { }
	void virtual_unk370() { }
	void virtual_unk371() { }
	void virtual_unk372() { }
	void virtual_unk373() { }
}; // 0x27c

struct GridEntity_Rock : public GridEntity {
	char pad0[0x44]; // 0x154
	LIBZHL_API static void SpawnDrops(Vector const & pos, int GridEntityType, int GridEntityVariant, unsigned int Seed, bool Unk, int BackdropType);
	LIBZHL_API void RenderTop(Vector const & pos);
	LIBZHL_API void TrySpawnWorms();
	LIBZHL_API bool TrySpawnLadder();
	LIBZHL_API void UpdateNeighbors();
	LIBZHL_API static void PlayBreakSound(int GridEntityType, int BackdropType);
	LIBZHL_API static int GetAltRockType(int BackdropType);
	LIBZHL_API static void RegisterRockDestroyed(int GridEntityType);
	LIBZHL_API void update_collision();
	LIBZHL_API void Render(Vector & offset);
	LIBZHL_API void Original_Render(Vector & offset);
	LIBZHL_API bool Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API bool Original_Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk374() { }
	void virtual_unk375() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk376() { }
	void virtual_unk377() { }
	void virtual_unk378() { }
	void virtual_unk379() { }
	void virtual_unk380() { }
}; // 0x198

struct GridEntity_Spikes : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk381() { }
	void virtual_unk382() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk383() { }
	void virtual_unk384() { }
	void virtual_unk385() { }
	void virtual_unk386() { }
	void virtual_unk387() { }
	void virtual_unk388() { }
	void virtual_unk389() { }
}; // 0x158

struct GridEntity_Stairs : public GridEntity {
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk390() { }
	void virtual_unk391() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk392() { }
	void virtual_unk393() { }
	void virtual_unk394() { }
	void virtual_unk395() { }
	void virtual_unk396() { }
	void virtual_unk397() { }
	void virtual_unk398() { }
}; // 0x154

struct GridEntity_Statue : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk399() { }
	void virtual_unk400() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk401() { }
	void virtual_unk402() { }
	void virtual_unk403() { }
	void virtual_unk404() { }
	void virtual_unk405() { }
	void virtual_unk406() { }
	void virtual_unk407() { }
}; // 0x158

struct GridEntity_TNT : public GridEntity {
	int _frameCount; // 0x154
	LIBZHL_API bool Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Original_Hurt(int damage, EntityRef * source);
	LIBZHL_API bool Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API bool Original_Destroy(bool Immediate, EntityRef * Source);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk408() { }
	void virtual_unk409() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk410() { }
	void virtual_unk411() { }
	void virtual_unk412() { }
	void virtual_unk413() { }
	void virtual_unk414() { }
}; // 0x158

struct GridEntity_Teleporter : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk415() { }
	void virtual_unk416() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk417() { }
	void virtual_unk418() { }
	void virtual_unk419() { }
	void virtual_unk420() { }
	void virtual_unk421() { }
	void virtual_unk422() { }
}; // 0x154

struct GridEntity_TrapDoor : public GridEntity {
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk423() { }
	void virtual_unk424() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk425() { }
	void virtual_unk426() { }
	void virtual_unk427() { }
	void virtual_unk428() { }
	void virtual_unk429() { }
	void virtual_unk430() { }
	void virtual_unk431() { }
}; // 0x154

struct GridEntity_Wall : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk432() { }
	void virtual_unk433() { }
	void virtual_unk434() { }
	void virtual_unk435() { }
	void virtual_unk436() { }
	void virtual_unk437() { }
	void virtual_unk438() { }
	void virtual_unk439() { }
	void virtual_unk440() { }
}; // 0x154

struct GridEntity_Web : public GridEntity {
	LIBZHL_API WaterClipInfo * GetWaterClipInfo(WaterClipInfo * out);
	LIBZHL_API WaterClipInfo * Original_GetWaterClipInfo(WaterClipInfo * out);
	void virtual_unk441() { }
	void virtual_unk442() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk443() { }
	void virtual_unk444() { }
	void virtual_unk445() { }
	void virtual_unk446() { }
	void virtual_unk447() { }
	void virtual_unk448() { }
	void virtual_unk449() { }
}; // 0x154

struct History_HistoryItem {
	int _time; // 0x0
	bool _isTrinket; // 0x4
	char pad0[0x3]; // 0x5
	int _itemID; // 0x8
	int _levelStage; // 0xc
	int _stageType; // 0x10
	int _roomType; // 0x14
	int _itemPoolType; // 0x18
	
	History_HistoryItem(TrinketType itemID, int levelStage, int stageType, int roomType, int itemPoolType, int time = -1)
	{
		_itemID = itemID;
		_levelStage = levelStage;
		_stageType = stageType;
		_roomType = roomType;
		_isTrinket = true;
		_time = time;
		_itemPoolType = itemPoolType;
		
		if (time < 0) {
			_time = g_Game->_frameCount;
		}
	}
}; // 0x1c

struct HistoryHUD_Item {
	char pad0[0x4]; // 0x0
	KAGE_Graphics_ImageBase * _image; // 0x4
	char pad1[0x4]; // 0x8
	History_HistoryItem _historyItem; // 0xc
}; // 0x28

struct InputDeviceBase {
	char pad0[0x3fc]; // 0x0
	char * _deviceName; // 0x3fc
	LIBZHL_API bool Initialize(void * unk);
}; // 0x400

struct InputManager {
	LIBZHL_API bool IsActionTriggered(int btnaction, int controllerid, int unk);
	LIBZHL_API bool IsButtonTriggered(int btn, int controllerid, int unk);
	LIBZHL_API bool IsActionPressed(int btn, int controllerid, int unk);
	LIBZHL_API bool IsButtonPressed(int btn, int controllerid, int unk);
	LIBZHL_API float GetActionValue(int action, int controllerid, int unk);
	LIBZHL_API char * GetDeviceNameByIdx(int cidx);
	LIBZHL_API int GetFirstActionButton(int action, int controlleridx);
	LIBZHL_API void GetActionButtons(int action, int controlleridx, int * out);
	LIBZHL_API static int __stdcall GetControllerButtonFrame(int button);
}; // 0x1

struct Isaac {
	LIBZHL_API static GridEntity * CreateGridEntity(int Type, unsigned int Index);
	LIBZHL_API static int __fastcall Random(int Max);
	LIBZHL_API static char const * __stdcall GetString(StringTable * table, char const * key);
	LIBZHL_API static void * __cdecl GetRoomEntities(void * unk);
	LIBZHL_API static void __cdecl SetBuiltInCallbackState(int callbackid, bool enabled);
	LIBZHL_API static bool __cdecl GetBuiltInCallbackState(int callbackid);
	LIBZHL_API static void __cdecl free(void * block);
	LIBZHL_API static void * __cdecl operator_new(unsigned int size);
	LIBZHL_API static Weapon * CreateWeapon(WeaponType type, Entity * ent);
	LIBZHL_API static void DestoryWeapon(Weapon * * wep);
	LIBZHL_API static void SpawnLocust(Entity_Player * player, int collectibleType, Vector * pos);
	LIBZHL_API static unsigned int __stdcall genrand_int32();
	LIBZHL_API static Vector  RandomUnitVector(unsigned int seed);
	LIBZHL_API static void __cdecl Shutdown();
	LIBZHL_API static Vector  GetRenderPosition(Vector * source, bool scale);
	LIBZHL_API static void __fastcall GetRandomPickupVelocity(Vector * buffer, Vector * position, unsigned int ePickupVelType, RNG * rng);
	LIBZHL_API static Vector  GetCollectibleSpawnPosition(Vector * target);
	LIBZHL_API static Vector  GetAxisAlignedUnitVectorFromDir(int eDir);
	LIBZHL_API static void __stdcall RebuildContentMountPoints();
	LIBZHL_API static void SwapANM2(ANM2 * left, ANM2 * right);
	LIBZHL_API static void __stdcall ConfirmGameExit();
    LIBZHL_API static bool IsInGame();
   
}; // 0x1

struct ItemConfig_Pill {
	int id; // 0x0
	int achievementId; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	bool greedModeAllowed; // 0x38
	char pad0[0x3]; // 0x39
	unsigned int announcerVoice; // 0x3c
	unsigned int announcerVoiceSuper; // 0x40
	unsigned int announcerVoiceDelay; // 0x44
	unsigned int mimicCharge; // 0x48
	unsigned char effectClass; // 0x4c
	unsigned char effectSubClass; // 0x4d
	char pad1[0x2]; // 0x4e
}; // 0x50

struct ItemConfig_Card {
	int id; // 0x0
	int achievementId; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	std_string hudAnim; // 0x38
	bool greedModeAllowed; // 0x50
	char pad0[0x3]; // 0x51
	unsigned int pickupSubtype; // 0x54
	unsigned int cardType; // 0x58
	unsigned int announcerVoice; // 0x5c
	unsigned int announcerDelay; // 0x60
	unsigned int mimicCharge; // 0x64
	ModEntry * modEntry; // 0x68
	ANM2 * moddedCardFront; // 0x6c
	LIBZHL_API bool IsAvailable();
}; // 0x70

struct ItemConfig_PlayerForm {
	int id; // 0x0
	char pad0[0x4]; // 0x4
	unsigned long long int tags; // 0x8
	std_string name; // 0x10
	int costume; // 0x28
	unsigned int cache; // 0x2c
}; // 0x30

struct ItemConfig {
	char pad0[0x3c]; // 0x0
	std_map_string_int _collectibleNameMap; // 0x3c
	char pad1[0xe0]; // 0x44
	LIBZHL_API void Init();
	LIBZHL_API void Unload();
	LIBZHL_API ItemConfig_Item * GetCollectible(int id);
	LIBZHL_API ItemConfig_Card * GetCard(int id);
	LIBZHL_API void LoadCostumes(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadMetadata(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadWispConfig(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadLocustConfig(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadCraftingRecipes(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadBombConfigRules(char * xmlpath, bool ismod);
	LIBZHL_API void LoadPocketItems(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void Load(char * xmlpath, ModEntry * modentry);
	LIBZHL_API ItemConfig_Item * GetTrinket(unsigned int TrinketType);
	LIBZHL_API vector_ItemPtr & GetTaggedItems(unsigned long long int tags);
	LIBZHL_API static bool IsQuestItem(int id);
	LIBZHL_API static bool IsValidCollectible(int CollectibleType);
		inline std::vector<ItemConfig_Item*>* GetCollectibles() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x00); }
		inline std::vector<ItemConfig_Item*>* GetTrinkets() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x0C); }
		inline std::vector<ItemConfig_Item*>* GetNullItems() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x18); }
		inline std::vector<ItemConfig_Card*>* GetCards() { return (std::vector<ItemConfig_Card*>*)((char*)this + 0x24); }
		inline std::vector<ItemConfig_Pill*>* GetPillEffects() { return (std::vector<ItemConfig_Pill*>*)((char*)this + 0x30); }
		inline std::vector<ItemConfig_PlayerForm*>* GetPlayerForms() { return (std::vector<ItemConfig_PlayerForm*>*)((char*)this + 0x44); }

		inline ItemConfig_Item* GetNullItem(const unsigned int id) {
			const auto* nullItems = this->GetNullItems();
			if (id < nullItems->size()) {
				return nullItems->at(id);
			}
			return nullptr;
		}
		
		static bool LIBZHL_API IsValidTrinket(unsigned int TrinketType);

}; // 0x124

struct KAGE {
	LIBZHL_API static void LogMessage(int flag, char const * string);
    LIBZHL_API static void _LogMessage(int flag, const char* fmt, ...);
    LIBZHL_API static void SafeLogMessage(int flag, const char* nonFormatString);
   
}; // 0x1

struct KAGE_Filesys_ArchivedFile {
	char pad0[0x4]; // 0x0
	KAGE_Filesys_ArchivedFile_ArchiveEntry * _archiveEntry; // 0x4
	KAGE_Filesys_File * _file; // 0x8
	KAGE_Filesys_ArchivedFile_FileEntry * _fileEntry; // 0xc
	char pad1[0xc1c]; // 0x10
}; // 0xc2c

struct KAGE_Filesys_ArchivedFile_ArchiveEntry {
	char * _filePath; // 0x0
	int _compressionType; // 0x4
}; // 0x8

struct KAGE_Filesys_ArchivedFile_FileEntry {
	unsigned int _archiveIndex; // 0x0
	unsigned int _primaryHash; // 0x4
	unsigned int _secondaryHash; // 0x8
	unsigned int _archiveOffset; // 0xc
	unsigned int _size; // 0x10
	unsigned int _checksum; // 0x14
	bool _valid; // 0x18
	char pad0[0x3]; // 0x19
}; // 0x1c

struct KAGE_Filesys_ContentManager {
	LIBZHL_API void AddMountPoint(char const * mountPoint);
	void virtual_unk450() { }
	void virtual_unk451() { }
	void virtual_unk452() { }
	LIBZHL_API char const * GetMountedFilePath_DeleteMe(char const * filePath);
	LIBZHL_API char const * Original_GetMountedFilePath_DeleteMe(char const * filePath);
	void virtual_unk453() { }
	void virtual_unk454() { }
		std::optional<std::string> LIBZHL_API KAGE_Filesys_ContentManager::GetMountedFilePath(const std::string& filePath);
		std::optional<std::string> LIBZHL_API KAGE_Filesys_ContentManager::GetMountedFilePath(const char* filePath);
		bool LIBZHL_API KAGE_Filesys_ContentManager::MountedFileExists(const std::string& filePath);
		bool LIBZHL_API KAGE_Filesys_ContentManager::MountedFileExists(const char* filePath);

}; // 0x1

struct KAGE_Filesys_IFile {
	void * _vtable; // 0x0
	LIBZHL_API void Free(bool deletePtr);
	LIBZHL_API void Free_Original(bool deletePtr);
	LIBZHL_API long int GetSize();
	LIBZHL_API long int GetSize_Original();
	LIBZHL_API long int GetPosition();
	LIBZHL_API long int GetPosition_Original();
	LIBZHL_API void SetPosition(long int offset, int origin);
	LIBZHL_API void SetPosition_Original(long int offset, int origin);
	LIBZHL_API bool IsEof();
	LIBZHL_API bool IsEof_Original();
	LIBZHL_API unsigned int Read(void * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int Read_Original(void * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int ReadLine(char * buffer, unsigned int maxSize);
	LIBZHL_API unsigned int ReadLine_Original(char * buffer, unsigned int maxSize);
	LIBZHL_API unsigned int Write(void const * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API unsigned int Write_Original(void const * buffer, unsigned int elementSize, unsigned int elementCount);
	LIBZHL_API void Flush();
	LIBZHL_API void Flush_Original();
        ~KAGE_Filesys_IFile()
        {
            this->Free(false);
        }
   
}; // 0x4

struct KAGE_Filesys_FileStream : public KAGE_Filesys_IFile {
	int _status; // 0x4
	char const * _filePath; // 0x8
	LIBZHL_API bool OpenRead(char const * filePath);
	LIBZHL_API bool OpenRead_Original(char const * filePath);
	LIBZHL_API bool OpenWrite(char const * filePath);
	LIBZHL_API bool OpenWrite_Original(char const * filePath);
	LIBZHL_API void CloseFile();
	LIBZHL_API void CloseFile_Original();
	LIBZHL_API bool IsOpen();
	LIBZHL_API bool IsOpen_Original();
	LIBZHL_API void Close();
	LIBZHL_API void Close_Original();
	LIBZHL_API char const * GetFilePath();
	LIBZHL_API char const * GetFilePath_Original();
}; // 0xc

struct KAGE_Filesys_File : public KAGE_Filesys_FileStream {
	FILE * _file; // 0xc
        KAGE_Filesys_File()
        {
            this->_vtable = __ptr_KAGE_Filesys_File_vftable;
            this->_status = 2;
            this->_filePath = nullptr;
            this->_file = nullptr;
        }
   
}; // 0x10

struct KAGE_Filesys_FileManager {
	LIBZHL_API static void __stdcall LoadArchiveFile(char * path, int unk1, unsigned short int unk2);
	LIBZHL_API KAGE_Filesys_IFile * OpenRead(char const * filePath);
	LIBZHL_API static unsigned int __fastcall GetPrimaryFilePathHash(char const * filePath);
	LIBZHL_API static unsigned int __fastcall GetSecondaryFilePathHash(char const * filePath);
}; // 0x1

struct KAGE_Filesys_SaveManager {
	LIBZHL_API void * OpenSaveFileForReading(int param_1);
}; // 0x1

struct KAGE_Graphics_GraphicsBuffer {
	void * data; // 0x0
	unsigned int size; // 0x4
	unsigned int capacity; // 0x8
	unsigned int processed; // 0xc
}; // 0x10

struct KAGE_Graphics_GraphicsBufferObject {
	KAGE_Graphics_GraphicsBuffer * container; // 0x0
	unsigned int activeBufferIdx; // 0x4
	unsigned int elementSize; // 0x8
	LIBZHL_API void * Allocate(unsigned int n);
        inline void* GetBase() {
            auto& activeBuffer = this->container[this->activeBufferIdx];
            uintptr_t buffer = (uintptr_t)activeBuffer.data;
            return (void*)(buffer + (this->elementSize * activeBuffer.processed));
        }
   
}; // 0xc

struct KAGE_Graphics_ImageBase_VertexAttributeDescriptor {
	char const * const * name; // 0x0
	unsigned int format; // 0x4
}; // 0x8

struct KAGE_Graphics_ImageManager {
	char pad0[0x10]; // 0x0
	vector_ImagePtr _frameImages; // 0x10
	char pad1[0xc]; // 0x1c
	vector_pair_RenderBatchPtr_ImagePtr _transparentBatches; // 0x28
	char pad2[0x8]; // 0x34
	LIBZHL_API void apply_frame_images();
	LIBZHL_API static KAGE_SmartPointer_ImageBase * __stdcall CreateProceduralImage_Internal(KAGE_SmartPointer_ImageBase * implicit_output, unsigned int width, unsigned int height, void * unused_1, char const * name, unsigned int unused_2, unsigned int unused_3, KColor color);
        static KAGE_SmartPointer_ImageBase CreateProceduralImage(uint32_t width, uint32_t height, const char* name, KColor& color)
        {
            KAGE_SmartPointer_ImageBase result;
            CreateProceduralImage_Internal(&result, width, height, nullptr, name, 0, 0, color);
            return result;
        }
   
}; // 0x3c

struct KAGE_Graphics_ImagePCX : public KAGE_Graphics_ImageBase {
}; // 0x80

struct KAGE_Graphics_ImagePIC : public KAGE_Graphics_ImageBase {
}; // 0x80

struct KAGE_Graphics_ImagePNG : public KAGE_Graphics_ImageBase {
}; // 0x80

struct _GLFWwindow {
	char pad0[0x48]; // 0x0
	double virtualCursorPosX; // 0x48
	double virtualCursorPosY; // 0x50
	char pad1[0x4]; // 0x58
	char mouseButtons[8]; // 0x5c
	char pad2[0x1b4]; // 0x64
	void * HWND; // 0x218
	char pad3[0x3c]; // 0x21c
}; // 0x258

struct KAGE_Graphics_Manager {
	char pad0[0x4]; // 0x0
	BlendMode _blendMode; // 0x4
	KAGE_Graphics_Shader * _shader; // 0x18
	KAGE_Graphics_ImageBase * currentRenderTarget; // 0x1c
	bool renderTargetUsesScreenSize; // 0x20
	char pad1[0xab]; // 0x21
	KAGE_Graphics_ImageBase * _boundImage; // 0xcc
	char pad2[0x10]; // 0xd0
	_GLFWwindow * _window; // 0xe0
	LIBZHL_API void SetCurrentRenderTarget(KAGE_Graphics_ImageBase * target, bool usesScreenSize);
	LIBZHL_API void Clear();
	LIBZHL_API void Present();
	LIBZHL_API void PresentWithoutSwap();
}; // 0xe4

struct KAGE_Graphics_VertexAttributeDescriptor {
	char const * name; // 0x0
	unsigned int format; // 0x4
private:
    void copy_name(const std::string_view name)
    {
        size_t len = name.size();
        char* newName = new char[len + 1];
        std::memcpy(newName, name.data(), len);
        newName[len] = '\0';

        this->name = newName;
    }

public:
    KAGE_Graphics_VertexAttributeDescriptor()
    {
        char* name = new char[1];
        name[0] = '\0';
        this->name = name;
        this->format = (uint32_t)eVertexAttributeFormat::TERMINATOR;
    }

    KAGE_Graphics_VertexAttributeDescriptor(const std::string_view name, uint32_t format)
    {
        copy_name(name);
        this->format = format;
    }

    KAGE_Graphics_VertexAttributeDescriptor(const KAGE_Graphics_VertexAttributeDescriptor& other)
    {
        copy_name(other.name);
        this->format = other.format;
    }

    ~KAGE_Graphics_VertexAttributeDescriptor()
    {
        delete[] this->name;
    }

    void SetName(std::string_view name)
    {
        delete[] this->name;
        copy_name(name);
    }

    KAGE_Graphics_VertexAttributeDescriptor& operator=(const KAGE_Graphics_VertexAttributeDescriptor& other)
    {
        delete[] this->name;
        copy_name(other.name);
        this->format = other.format;
    }

    bool operator==(const KAGE_Graphics_VertexAttributeDescriptor& other) const
    {
        return std::strcmp(this->name, other.name) == 0 && this->format == other.format;
    }

    bool operator!=(const KAGE_Graphics_VertexAttributeDescriptor& other) const
    {
        return !(*this == other);
    }
}; // 0x8

struct KAGE_Graphics_Manager_GL {
	LIBZHL_API static void LoadShader(KAGE_Graphics_Shader * shader, KAGE_Graphics_VertexAttributeDescriptor const * descriptor, char const * shaderPath);
}; // 0x1

struct KAGE_Graphics_RenderBatch {
	char pad0[0x14]; // 0x0
	KAGE_Graphics_Shader * shader; // 0x14
	char pad1[0xc]; // 0x18
	KAGE_Graphics_GraphicsBufferObject _vertexBuffer; // 0x24
	KAGE_Graphics_GraphicsBufferObject _indexBuffer; // 0x30
}; // 0x3c

struct KAGE_ReferenceCount_EntitySaveState : public KAGE_ReferenceCountBase {
	EntitySaveState * _saveState; // 0x14
}; // 0x18

struct KAGE_System_CriticalSection {
	CRITICAL_SECTION criticalSection; // 0x0
	bool locked; // 0x18
	char pad0[0x3]; // 0x19
}; // 0x1c

struct LRoomAreaDesc {
	Vector _high[2]; // 0x0
	Vector _low[2]; // 0x10
}; // 0x20

struct XY {
	int x; // 0x0
	int y; // 0x4
	XY() : x(0), y(0) {}
	XY(int _x, int _y) : x(_x), y(_y) {}

	XY operator+(const XY& other) const {
		return XY(x + other.x, y + other.y);
	}
	
	XY operator-(const XY& other) const {		
		return XY(x - other.x, y - other.y);
	}
	static inline XY XY::NewFromGridIdx(int gridIdx)
	{
		if (!(0 <= gridIdx && gridIdx < 169))
		{
			return XY(-1, -1);
		}

		return XY(gridIdx % 13, gridIdx / 13);
	}

	inline int XY::ToGridIdx() const
	{
		if (!(0 <= x && x < 13) || !(0 <= y && y < 13))
		{
			return -1;
		}

		return y * 13 + x;
	}
}; // 0x8

struct LRoomTileDesc {
	XY _high[2]; // 0x0
	XY _low[2]; // 0x10
	LIBZHL_API XY * GetRandomTile(XY * ret, unsigned int seed);
}; // 0x20

struct LayerData {
	unsigned int ID; // 0x0
	unsigned int spritesheetID; // 0x4
	std_string name; // 0x8
	std_string defaultSpriteSheetPath; // 0x20
}; // 0x38

struct LayerState {
	LayerData * _layerData; // 0x0
	ANM2 * _animation; // 0x4
	std_string _spriteSheetPath; // 0x8
	unsigned int _minFilterMode; // 0x20
	unsigned int _magFilterMode; // 0x24
	unsigned int _wrapSMode; // 0x28
	unsigned int _wrapTMode; // 0x2c
	bool _spriteSheetLoaded; // 0x30
	bool _unk; // 0x31
	bool _flipX; // 0x32
	bool _flipY; // 0x33
	Vector _size; // 0x34
	float _rotation; // 0x3c
	Vector _pos; // 0x40
	ColorMod _color; // 0x48
	bool _visible; // 0x74
	char pad0[0x3]; // 0x75
	BlendMode _blendMode; // 0x78
	unsigned int _bitflags; // 0x8c
	Vector _cropOffset; // 0x90
	KAGE_SmartPointer_ImageBase _spriteSheet; // 0x98
	LIBZHL_API KAGE_SmartPointer_ImageBase GetSpriteSheet();
    inline int GetLayerID() { return this->_layerData->ID; }
    inline std_string GetName() { return this->_layerData->name; }
	inline std_string GetSpritesheetPath() { return this->_spriteSheetPath; }
    inline std_string GetDefaultSpritesheetPath() { return this->_layerData->defaultSpriteSheetPath; }
	inline Vector* GetSize() { return &this->_size; }
	inline float* GetRotation() { return &this->_rotation; }
	inline Vector* GetPos() { return &this->_pos; }
	inline ColorMod* GetColor() { return &this->_color; }
	inline bool* IsVisible() { return &this->_visible; }
	inline BlendMode* GetBlendMode() { return &this->_blendMode; }
	inline unsigned int* GetRenderFlags() { return &this->_bitflags; }
	inline Vector* GetCropOffset() { return &this->_cropOffset; }

    inline void SetSpriteSheet(KAGE_SmartPointer_ImageBase& image)
    {
        this->_spriteSheet = image;
        auto* img = image.image;
        if (img)
        {
            this->_minFilterMode = img->_minFilterMode;
            this->_magFilterMode = img->_magFilterMode;
            this->_wrapSMode = img->_wrapSMode;
            this->_wrapTMode = img->_wrapTMode;
        }

        this->_spriteSheetLoaded = img != nullptr;
    }
}; // 0xa0

struct LevelGenerator_Room {
	bool _unk1; // 0x0
	char pad0[0x3]; // 0x1
	unsigned int _generationIndex; // 0x4
	unsigned int _gridColIdx; // 0x8
	unsigned int _gridLineIdx; // 0xc
	unsigned int _horizontalSize; // 0x10
	unsigned int _verticalSize; // 0x14
	unsigned int _shape; // 0x18
	unsigned int _doors; // 0x1c
	int _originNeighborConnectDir; // 0x20
	int _originNeighborConnectDirAdjust; // 0x24
	int _linkColIdx; // 0x28
	int _linkLineIdx; // 0x2c
	std_set_int _neighbors; // 0x30
	unsigned int _setExtraField; // 0x38
	bool _deadEnd; // 0x3c
	char pad1[0x3]; // 0x3d
	unsigned int _distanceFromStart; // 0x40
	bool _unk8; // 0x44
	char pad2[0x3]; // 0x45
	LIBZHL_API LevelGenerator_Room * constructor(unsigned int column, unsigned int line, unsigned int shape);
}; // 0x48

struct LevelGenerator {
	RNG _rng; // 0x0
	RoomShapeBitset _allowedShapes; // 0x10
	int _roomMap[169]; // 0x14
	bool _blockedPositions[169]; // 0x2b8
	char pad0[0x3]; // 0x361
	vector_LevelGenRoom _rooms; // 0x364
	std_vector_uint _deadEnds; // 0x370
	std_vector_uint _nonDeadEnds; // 0x37c
	int _nextBossRoomIdx; // 0x388
	unsigned int _numBossRooms; // 0x38c
	bool _isXL; // 0x390
	bool _isChapter6; // 0x391
	bool _isStageVoid; // 0x392
	char pad1[0x1]; // 0x393
	LIBZHL_API bool place_room(LevelGenerator_Room * room);
	LIBZHL_API LevelGenerator_Room * CreateRoom(int x, int y, int shape, int connectX, int connectY, Direction connectDir);
	LIBZHL_API void Generate(int unk, bool unk2, bool unk3, bool unk4, unsigned int const & allowedShapes, unsigned int numDeadEnds, LevelGenerator_Room * startRoom);
	LIBZHL_API LevelGenerator_Room * GetNewEndRoom(int roomShape, unsigned int const & possibleDoors);
	LIBZHL_API void DetermineBossRoom(int shape, unsigned int const & possibleDoors);
	LIBZHL_API void get_neighbor_candidates(vector_LevelGenRoom * neighbors, unsigned int generationIndex, bool unk);
	LIBZHL_API void calc_required_doors();
	LIBZHL_API bool is_pos_free(XY const * position, unsigned int shape);
	LIBZHL_API bool is_placement_valid(unsigned int * position, unsigned int shape);
	LIBZHL_API void mark_dead_ends();
	LIBZHL_API static int * * __fastcall get_room_placement_offsets(int shape);
	LIBZHL_API static XY * get_door_source_position(XY * ret, XY * position, int shape, int doorSlot);
	LIBZHL_API static XY * get_door_target_position(XY * ret, XY * position, int shape, int doorSlot, bool unk);
	LIBZHL_API static bool has_shape_slot(int shape, int doorSlot, bool ignoreThinShapesRestrictions);
    inline int* GetNumBossRooms() { return (int*)((char*)this + 0x38C); }
    inline std::vector<LevelGenerator_Room>* GetAllRooms() { return (std::vector<LevelGenerator_Room>*)((char*)this + 0x364); }
    inline std::vector<int>* GetDeadEnds() { return (std::vector<int>*)((char*)this + 0x370); }
    inline std::vector<int>* GetNonDeadEnds() { return (std::vector<int>*)((char*)this + 0x37C); }
    static inline bool LevelGenerator::IsPositionInBounds(int gridIdx)
    {
        return 0 <= gridIdx && gridIdx < 169;
    }

    static inline bool LevelGenerator::IsPositionInBounds(const XY& position)
    {
        return (0 <= position.x && position.x < 13) && (0 <= position.y && position.y < 13);
    }

    inline void LevelGenerator::BlockPosition(int gridIdx)
    {
        if (IsPositionInBounds(gridIdx))
        {
            _blockedPositions[gridIdx] = true;
        }
    }

    inline void LevelGenerator::BlockPosition(const XY& position)
    {
        this->BlockPosition(position.ToGridIdx());
    }

    inline bool LevelGenerator::CanPlaceShapeAtPosition(XY& position, uint32_t shape)
    {
        return is_pos_free(&position, shape) && is_placement_valid((uint32_t*)&position, shape);
    }

    inline bool LevelGenerator::CanPlaceShapeAtPosition(int gridIdx, uint32_t shape)
    {
        XY position = XY::NewFromGridIdx(gridIdx);
        return CanPlaceShapeAtPosition(position, shape);
    }
}; // 0x394

struct LootListEntry {
	unsigned int _type; // 0x0
	unsigned int _variant; // 0x4
	unsigned int _subType; // 0x8
	unsigned int _seed; // 0xc
	RNG * _rng; // 0x10
}; // 0x14

struct LuaBridgeRef {
	lua_State * _state; // 0x0
	int _ref; // 0x4
		LuaBridgeRef() {

		}

}; // 0x8

struct LuaCallbackCallerResult {
	lua_State * state; // 0x0
	int ref; // 0x4
}; // 0x8

struct LuaCallbackCaller {
	lua_State * state; // 0x0
	int callbackId; // 0x4
	int optionalArg; // 0x8
	char pad0[0x4]; // 0xc
	LIBZHL_API LuaCallbackCallerResult CallInputAction(LuaEngine * engine, Entity * entity, int hook, int action);
}; // 0x10

struct RunCallbackRegistry {
	lua_State * state; // 0x0
	int key; // 0x4
}; // 0x8

struct LuaEngine {
	char pad0[0xc]; // 0x0
	bool _debug; // 0xc
	char pad1[0x3]; // 0xd
	RunCallbackRegistry * runCallbackRegistry; // 0x10
	LuaBridgeRef * _unloadModFuncRef; // 0x14
	lua_State * _state; // 0x18
	int _runCallbackRegistryKey; // 0x1c
	unsigned int _pointerMask; // 0x20
	char pad2[0x244]; // 0x24
	LIBZHL_API void Init(bool Debug);
	LIBZHL_API void RegisterClasses();
	LIBZHL_API bool RunBundledScript(char const * path);
	LIBZHL_API char * LuamodCMD(char * modname);
	LIBZHL_API static void __stdcall PostGameStart(unsigned int state);
	LIBZHL_API static void __stdcall PostRender();
	LIBZHL_API static void __stdcall Callback_PreEntitySpawn(int * type, int * variant, Vector * position, Vector * velocity, Entity * spawner, int * subType, unsigned int * seed);
	LIBZHL_API static Vector * __cdecl GetMousePosition(Vector * buffer, bool gamecoords);
	LIBZHL_API static bool __cdecl IsMouseButtonPressed(unsigned int button);
	LIBZHL_API void RunScript(char const * path);
	LIBZHL_API void destroy();
	LIBZHL_API static void __stdcall PostPlayerInit(Entity_Player * player);
	LIBZHL_API bool EntityTakeDamage(Entity * entity, float damage, unsigned long long int damageFlags, EntityRef * source, int damageCountdown);
	LIBZHL_API void EvaluateItems(Entity_Player * player, int cacheFlag);
	LIBZHL_API int PreBombCollision(Entity_Bomb * bomb, Entity * collider, bool low);
	LIBZHL_API int PreFamiliarCollision(Entity_Familiar * familiar, Entity * collider, bool low);
	LIBZHL_API int PreKnifeCollision(Entity_Knife * knife, Entity * collider, bool low);
	LIBZHL_API int PreNPCCollision(Entity_NPC * npc, Entity * collider, bool low);
	LIBZHL_API int PrePickupCollision(Entity_Pickup * pickup, Entity * collider, bool low);
	LIBZHL_API int PreProjectileCollision(Entity_Projectile * proj, Entity * collider, bool low);
	LIBZHL_API int PreTearCollision(Entity_Tear * tear, Entity * collider, bool low);
	LIBZHL_API int PrePlayerCollide(Entity_Player * player, Entity * collider, bool low);
	LIBZHL_API void UsePill(int pillEffect, Entity_Player * player, unsigned int useFlags);
	LIBZHL_API bool PreUseItem(int collectibleType, RNG * rng, Entity_Player * player, unsigned int useFlags, int activeSlot, int customVarData);
	LIBZHL_API bool UseItem(int collectibleType, RNG * rng, Entity_Player * player, unsigned int useFlags, int activeSlot, int customVarData, short int * resultFlags);
	LIBZHL_API static void __stdcall PostPickupSelection(Entity_Pickup * pickup, int * variant, int * subType);
	LIBZHL_API static void __stdcall PostKnifeInit(Entity_Knife * knife);
	LIBZHL_API static void __cdecl Isaac_WorldToScreen(Vector * buffer, Vector * pos);
	LIBZHL_API static int __cdecl Isaac_GetItemIdByName(std_string * name);
	LIBZHL_API static int __stdcall GetPillEffect(int pillEffect, int pillColor);
	LIBZHL_API static void __stdcall PostEntityKill(Entity * ent);
	
		inline bool GetLuaDebug() {return this->_debug; }
        inline uintptr_t GetMaskedPointer(uintptr_t pointer) { return pointer ^ this->_pointerMask; }
        LIBZHL_API ModReference* GetModRefByTable(int tblIdx);

}; // 0x268

struct MTRNG {
	unsigned int _seeds[624]; // 0x0
	unsigned int _currentIndex; // 0x9c0
	LIBZHL_API void Init(unsigned int seed);
	LIBZHL_API unsigned int Next();
}; // 0x9c4

struct UnknownGameStartStruct {
	char pad0[0x5c]; // 0x0
}; // 0x5c

struct NightmareScene {
	char pad0[0x20]; // 0x0
	ANM2 _backgroundANM2; // 0x20
	ANM2 _bubbleANM2; // 0x134
	ANM2 _ProgressBarANM2; // 0x248
	char pad1[0x178]; // 0x35c
	ANM2 _playerExtraPortraitANM2; // 0x4d4
	char pad2[0x4]; // 0x5e8
	LIBZHL_API void LoadConfig(char * xmlpath);
	LIBZHL_API void Render();
	LIBZHL_API void Show(bool unk);
	inline ANM2* GetBackgroundSprite() { return &this->_backgroundANM2; }
	inline ANM2* GetBubbleSprite() { return &this->_bubbleANM2; }
	inline ANM2* GetProgressBarSprite() { return &this->_ProgressBarANM2; }
	inline int* GetProgressBarMap() { return (int*)((char*)this + 0x36c); }
	inline bool* IsDogmaNightmare() { return (bool*)((char*)this + 0x5e8); }
}; // 0x5ec

struct PersistentGameData_Bestiary {
	std_map_int_int encounters; // 0x0
	std_map_int_int kills; // 0x8
	std_map_int_int hits; // 0x10
	std_map_int_int deaths; // 0x18
	LIBZHL_API PersistentGameData_Bestiary * constructor();
	PersistentGameData_Bestiary() {
		this->constructor();
	}
}; // 0x20

struct PersistentGameData {
	bool changesmade; // 0x0
	bool readonly; // 0x1
	char pad0[0x2]; // 0x2
	KAGE_Filesys_FileStream * file; // 0x4
	std_string filepath; // 0x8
	std_string steamcloudfilepath; // 0x20
	bool achievements[641]; // 0x38
	char pad1[0x3]; // 0x2b9
	int eventCounter[523]; // 0x2bc
	bool itemsCollection[733]; // 0xae8
	char pad2[0x42]; // 0xdc5
	bool bosses[104]; // 0xe07
	bool challenges[45]; // 0xe6f
	char pad3[0xc8]; // 0xe9c
	PersistentGameData_Bestiary bestiary; // 0xf64
	char pad4[0x8]; // 0xf84
	bool fileLoadedSucessfully; // 0xf8c
	char pad5[0x3]; // 0xf8d
	LIBZHL_API bool TryUnlock(int achievementID);
	LIBZHL_API void IncreaseEventCounter(int eEventCounters, int num);
	LIBZHL_API bool Unlocked(int achievementID);
	LIBZHL_API void AddToCollection(int collectibleID);
	LIBZHL_API bool Load(char const * filepath);
	LIBZHL_API bool TryImportRepLocalSave(char const * path);
	LIBZHL_API bool TryImportABPLocalSave(char const * path);
	LIBZHL_API bool TryImportABLocalSave(char const * path);
	LIBZHL_API bool TryImportRebirthLocalSave(char const * path);
	LIBZHL_API bool LoadFromSteamCloud();
	LIBZHL_API bool TryImportRepCloudSave();
	LIBZHL_API bool TryImportABPCloudSave();
	LIBZHL_API bool TryImportABCloudSave();
	LIBZHL_API bool AddBestiaryKill(int EntityType, int EntityVariant);
	LIBZHL_API int GetBestiaryDeathCount(int EntityType, int EntityVariant);
	LIBZHL_API int GetBestiaryKillCount(int EntityType, int EntityVariant);
	LIBZHL_API int GetBestiaryEncounterCount(int EntityType, int EntityVariant);
	LIBZHL_API void UnlockSteamAchievement(int achievementID);
	LIBZHL_API void SaveLocally();
	LIBZHL_API void SaveToSteamCloud();
	LIBZHL_API void AddChallenge(int challengeID);
	LIBZHL_API void AddBoss(int bossID);
	LIBZHL_API void Clear(bool unk);
	LIBZHL_API PersistentGameData * constructor();
	PersistentGameData() {
		this->constructor();
	}
	~PersistentGameData() {
		if (this->file) {
			this->file->Free(true);
			this->file = nullptr;
		}
	}
	
	inline int GetEventCounter(int eventCounterNum) {return this->eventCounter[eventCounterNum]; }
	inline bool IsItemInCollection (int collectibleID) {
		bool savedata = this->itemsCollection[collectibleID];
		return savedata != false; 
	}
	inline bool IsChallengeCompleted (int challengeID) {
		bool savedata = this->challenges[challengeID];
		return savedata != false; 
	}
	
	LIBZHL_API void Save();
}; // 0xf90

struct MusicEntry {
	char pad0[0x4]; // 0x0
	std_string _string1; // 0x4
	char pad1[0x44]; // 0x1c
}; // 0x60

struct Music {
	unsigned int _currentStream; // 0x0
	char pad0[0x308]; // 0x4
	unsigned int _currentId; // 0x30c
	unsigned int _queuedId; // 0x310
	float _pitch; // 0x314
	float _targetPitch; // 0x318
	vector_MusicEntry _entries; // 0x31c
	bool _enabled; // 0x328
	char pad1[0x1]; // 0x329
	unsigned short int _jingleId; // 0x32a
	char pad2[0x34]; // 0x32c
	float _jingleVolumeMaybe; // 0x360
	int _jingleCountdownMaybe; // 0x364
	LIBZHL_API void Play(int musicid, float volume);
	LIBZHL_API void Crossfade(int musicid, float faderate);
	LIBZHL_API void PlayJingle(int musicid, int unusedInt, bool unusedBool);
	LIBZHL_API void Fadein(unsigned int Id, float Volume, float FadeRate);
	LIBZHL_API void Fadeout(float FadeRate);
	LIBZHL_API void LoadConfig(char * xmlpath, bool ismod);
	LIBZHL_API void DisableLayer(int id);
	LIBZHL_API void EnableLayer(int id, bool instant);
	LIBZHL_API bool IsLayerEnabled(unsigned int id);
	LIBZHL_API void Pause();
	LIBZHL_API void ResetPitch();
	LIBZHL_API void Resume();
	LIBZHL_API void UpdateVolume();
	LIBZHL_API void VolumeSlide(float TargetVolume, float FadeRate);
	inline void StopJingle() {
		// this is inside _jingleStream
		*(int*)((char*)this + 0x348) = 0; // _volume
		*(int*)((char*)this + 0x34c) = 0; // _targetVolume
		*(bool*)((char*)this + 0x354) = false; // _playing
		
		this->_jingleVolumeMaybe = 0.0f;
		this->_jingleCountdownMaybe = 0;
	};
	
	  bool LIBZHL_API ValidateMusicID(int id, int& max);
}; // 0x368

struct NetplayManager {
	char pad0[0x1]; // 0x0
	LIBZHL_API bool IsIdxLocalPlayer(unsigned int idx);
}; // 0x1

struct SoundEffect {
	unsigned int _id; // 0x0
	char pad0[0x194]; // 0x4
	bool _loaded; // 0x198
	bool _shouldPreload; // 0x199
	char pad1[0x1e]; // 0x19a
	LIBZHL_API void Load();
}; // 0x1b8

struct SoundEffects {
	vector_SoundEffect _sounds; // 0x0
	int _count; // 0xc
	float _volume; // 0x10
	char pad0[0x4]; // 0x14
	LIBZHL_API void ClearVolumeModifier();
	LIBZHL_API void Play(int ID, float Volume, int FrameDelay, bool Loop, float Pitch, float Pan);
	LIBZHL_API void LoadConfig(char * filename, bool ismod);
}; // 0x18

struct RedirectedPath {
	unsigned int _primaryHash; // 0x0
	unsigned int _secondaryHash; // 0x4
	ModEntry * _modEntry; // 0x8
	std_string _filePath; // 0xc
}; // 0x24

struct ModManager {
	vector_ModEntryPointer _mods; // 0x0
	RedirectedPath * _redirectedPathsMap[32768]; // 0xc
	char pad0[0x250]; // 0x2000c
	int _modBanStatus; // 0x2025c
	LIBZHL_API void UpdateWorkshopMods();
	LIBZHL_API static void __stdcall RenderCustomCharacterMenu(int CharacterId, Vector * RenderPos, ANM2 * DefaultSprite);
	LIBZHL_API void RenderCustomCharacterPortraits(int id, Vector * pos, ColorMod * color, Vector * scale);
	LIBZHL_API void RenderCustomCollectionItem(unsigned int itemID, Vector * pos, Vector * scale, ColorMod * color, BlendMode * blendMode);
	LIBZHL_API void ListMods();
	LIBZHL_API void LoadConfigs();
	LIBZHL_API void UpdateRooms(int id, int mode);
	LIBZHL_API void TryRedirectPath(std_string * result, std_string * filePath);
	LIBZHL_API void LoadShaders();
	LIBZHL_API void Reset();
	LIBZHL_API void TriggerResize();
}; // 0x20260

struct OptionsConfig {
	std_string _optionsIniFilePath; // 0x0
	float _musicVolume; // 0x18
	float _sfxVolume; // 0x1c
	float _mapOpacity; // 0x20
	bool _isFullscreen; // 0x24
	bool _filterEnabled; // 0x25
	char pad0[0x2]; // 0x26
	float _gamma; // 0x28
	float _exposure; // 0x2c
	float _brightness; // 0x30
	float _contrast; // 0x34
	bool _controlHotplugEnabled; // 0x38
	char pad1[0x3]; // 0x39
	int _popupsMode; // 0x3c
	bool _enableFoundHUD; // 0x40
	char pad2[0x3]; // 0x41
	int _cameraStyle; // 0x44
	int _historyHudMode; // 0x48
	float _hudOffset; // 0x4c
	bool _tryImportSave; // 0x50
	bool _enableMods; // 0x51
	bool _enableRumble; // 0x52
	bool _enableChargeBars; // 0x53
	bool _enableBulletVisibility; // 0x54
	bool _enableAimLock; // 0x55
	char pad3[0x2]; // 0x56
	int _touchMode; // 0x58
	bool _enableDebugConsole; // 0x5c
	bool _enableVSync; // 0x5d
	bool _enableSteamCloud; // 0x5e
	bool _enablePauseOnFocusLost; // 0x5f
	bool _enableMouseControl; // 0x60
	char pad4[0x3]; // 0x61
	int _maxScale; // 0x64
	int _maxRenderScale; // 0x68
	int _windowWidth; // 0x6c
	int _windowHeight; // 0x70
	int _windowPosX; // 0x74
	int _windowPosY; // 0x78
	int _consoleFont; // 0x7c
	bool _enableFadedConsoleDisplay; // 0x80
	bool _enableSaveCommandHistory; // 0x81
	bool _enableBorderlessFullscreen; // 0x82
	bool _enableInterpolation; // 0x83
	bool _enableColorCorrection; // 0x84
	bool _enableLighting; // 0x85
	bool _enableShockwave; // 0x86
	bool _enableCaustics; // 0x87
	bool _enableFilter; // 0x88
	bool _enablePixelation; // 0x89
	bool _enableBloom; // 0x8a
	bool _enableWaterSurface; // 0x8b
	bool _getsSetToEnableWaterSurface; // 0x8c
	bool _enableColorModifier; // 0x8d
	bool _bossHpOnBottom; // 0x8e
	char pad5[0x1]; // 0x8f
	int _announcerVoiceMode; // 0x90
	int _jacobEsauControls; // 0x94
	bool _ascentVoiceover; // 0x98
	char pad6[0x3]; // 0x99
	int _onlineHud; // 0x9c
	bool _streamerMode; // 0xa0
	char pad7[0x3]; // 0xa1
	int _onlinePlayerVolume; // 0xa4
	int _onlinePlayerOpacity; // 0xa8
	bool _onlineChatEnabled; // 0xac
	bool _onlineFilterEnabled; // 0xad
	char pad8[0x2]; // 0xae
	int _onlineColorSet; // 0xb0
	int _onlineInputDelay; // 0xb4
	bool _acceptedPublicBeta_VERSION; // 0xb8
	bool _acceptedModDisclaimer; // 0xb9
	bool _acceptedDataCollectionDisclaimer; // 0xba
	char pad9[0x1]; // 0xbb
	LIBZHL_API void Load(char const * path);
	LIBZHL_API void Save();
	LIBZHL_API void SetFullScreen(bool value);
	LIBZHL_API void SetMusicVolume(float volume);
	inline bool ModsEnabled() { return _enableMods; }
	inline bool PopUpsEnabled() { return _popupsMode > 0; }
}; // 0xbc

struct StringTable {
	unsigned int language; // 0x0
	char pad0[0x14]; // 0x4
	LIBZHL_API char * GetString(char const * category, int language, char const * key, bool * retBool);
	LIBZHL_API bool Load(char * fileName);
	LIBZHL_API void load_ascii_data(char * param_1);
}; // 0x18

struct Manager {
	char pad0[0x8]; // 0x0
	int _state; // 0x8
	char pad1[0x4]; // 0xc
	unsigned int _currentSaveSlot; // 0x10
	PersistentGameData _persistentGameData; // 0x14
	GameState _gamestate; // 0xfa4
	char pad2[0x4]; // 0x20c44
	Cutscene _cutsceneManager; // 0x20c48
	NightmareScene _nightmareScene; // 0x21498
	char pad3[0x8]; // 0x21a84
	AchievementOverlay _achievementOverlay; // 0x21a8c
	Music _musicmanager; // 0x29df8
	SoundEffects _sfxManager; // 0x2a160
	OptionsConfig _optionsConfig; // 0x2a178
	ItemConfig _itemConfig; // 0x2a234
	char pad4[0x14]; // 0x2a358
	EntityConfig _entityConfig; // 0x2a36c
	ModManager _modManager; // 0x2a3bc
	StringTable _stringTable; // 0x4a61c
	char pad5[0x284]; // 0x4a634
	unsigned int _framecount; // 0x4a8b8
	char pad6[0x11]; // 0x4a8bc
	bool _isConsoleEnabled; // 0x4a8cd
	char pad7[0x12]; // 0x4a8ce
	ANM2 _buttonsSprite; // 0x4a8e0
	char pad8[0x14]; // 0x4a9f4
	Font _font1_TeamMeatEx10; // 0x4aa08
	Font _font2_TeamMeatEx12; // 0x4aa54
	Font _font3_TeamMeatEx16; // 0x4aaa0
	Font _font4_terminus; // 0x4aaec
	Font _font5_terminus8; // 0x4ab38
	Font _font6_PFTempestaSevenCondensed; // 0x4ab84
	Font _font7_Upheaval; // 0x4abd0
	Font _font8_LuaMiniOutlined; // 0x4ac1c
	Font _font9_PFTempestaSevenCondensedAgain; // 0x4ac68
	char pad9[0x5c]; // 0x4acb4
	bool _starting; // 0x4ad10
	bool _rerunAvailable; // 0x4ad11
	bool _startingFromRerun; // 0x4ad12
	char pad10[0x9]; // 0x4ad13
	Seeds _startSeeds; // 0x4ad1c
	char pad11[0x4]; // 0x4ad78
	bool _debugStart; // 0x4ad7c
	char pad12[0x23]; // 0x4ad7d
	DailyChallenge _dailyChallenge; // 0x4ada0
	bool _networkPlay; // 0x4ae54
	char pad13[0x33]; // 0x4ae55
	ANM2 _cursorSprite; // 0x4ae88
	char pad14[0x1c]; // 0x4af9c
	NetplayManager _netplayManager; // 0x4afb8
	char pad15[0x1daf]; // 0x4afb9
	LIBZHL_API static void __stdcall Init();
	LIBZHL_API static void __stdcall Update(bool unk);
	LIBZHL_API static void __stdcall RecordPlayerCompletion(int eCompletionEvent);
	LIBZHL_API void LoadGameState(int saveslot);
	LIBZHL_API void LoadConfigs();
	LIBZHL_API void LoadChallenges(char * xmlpath, bool ismod);
	LIBZHL_API ChallengeParam * GetChallengeParams(int challengeID);
	LIBZHL_API void StartNewGame(int playerType, int challenge, Seeds unk, int difficulty);
	LIBZHL_API bool AchievementUnlocksDisallowed(bool unk);
	LIBZHL_API void ExecuteStartGame();
	LIBZHL_API static void __stdcall RestartGame(Seeds seeds, bool clearSeedEffects, bool progresScaredHeart);
	LIBZHL_API void cleanup_current_state();
	LIBZHL_API static KAGE_SmartPointer_ImageBase * __stdcall LoadImage(KAGE_SmartPointer_ImageBase * result, char const * path, KAGE_Graphics_ImageBase_VertexAttributeDescriptor * descriptor, bool unk);
	LIBZHL_API void Render();
	LIBZHL_API void ResizeWindow(int windowWidth, int windowHeight);
	LIBZHL_API void ResizeWindowCallback(int windowWidth, int windowHeight);
	LIBZHL_API void SetFullscreenRendering(bool value);
	LIBZHL_API void SetSaveSlot(unsigned int slot);
	LIBZHL_API void ShowCutscene(unsigned int cutsceneID, bool shouldCleanup, unsigned int UNKNOWN);
	LIBZHL_API bool IsSteamCloudEnabled();
	LIBZHL_API void destructor();
	LIBZHL_API static char * __stdcall GetLanguage();
	inline int GetState() { return this->_state; }
	inline PersistentGameData* GetPersistentGameData() { return &this->_persistentGameData; }
	inline NightmareScene* GetNightmareScene() { return &this->_nightmareScene; }
	inline bool GetDebugConsoleEnabled() { return this->_isConsoleEnabled; }
	inline int GetMaxRenderScale() { return this->_optionsConfig._maxRenderScale; }
	inline ModManager* GetModManager() { return &this->_modManager; }
	inline DailyChallenge* GetDailyChallenge() { return &this->_dailyChallenge; }
	inline StringTable* GetStringTable() { return &this->_stringTable; }
	inline bool GetNetStart() { return this->_networkPlay; }
	inline Cutscene* GetCutscene() { return &this->_cutsceneManager; }
	inline OptionsConfig* GetOptions() { return &this->_optionsConfig; }
	inline AchievementOverlay* GetAchievementOverlay() { return &this->_achievementOverlay; }
	inline ItemConfig* GetItemConfig() { return &this->_itemConfig; }
	inline EntityConfig* GetEntityConfig() { return &this->_entityConfig; }
	inline std::vector<EntityConfig_Player>* GetPlayerConfig() { return this->GetEntityConfig()->GetPlayers(); }
	inline NetplayManager* GetNetplayManager() { return &this->_netplayManager; }
}; // 0x4cd68

struct Menu_Stats {
	int _countTotalAchievements; // 0x0
	int _countItemsInCollection; // 0x4
	int _countDeaths; // 0x8
	int _countMomKills; // 0xc
	int _statsMenuCurrentSelection; // 0x10
	float _PositionX; // 0x14
	float _PositionY; // 0x18
	ANM2 _StatsMenuSprite; // 0x1c
	bool _isAchievementScreenVisible; // 0x130
	char pad0[0x3]; // 0x131
	float _achievementScrollInPosition; // 0x134
	float _achievementScrollThruListPosition; // 0x138
	int _selectedAchievmentId; // 0x13c
	int _IconIDtoUseForAchievementID[641]; // 0x140
	ANM2 _achievementsSprite; // 0xb44
	ANM2 _achievementMiniSprite1; // 0xc58
	ANM2 _achievementMiniSprite2; // 0xd6c
	ANM2 _achievementMiniSprite3; // 0xe80
	ANM2 _achievementMiniSprite4; // 0xf94
	ANM2 _achievementMiniSprite5; // 0x10a8
	ANM2 _achievementMiniSprite6; // 0x11bc
	ANM2 _achievementMiniSprite7; // 0x12d0
	ANM2 _achievementMiniSprite8; // 0x13e4
	ANM2 _achievementMiniSprite9; // 0x14f8
	ANM2 _cursorLeftSprite; // 0x160c
	ANM2 _cursorRightSprite; // 0x1720
	AchievementOverlay_Entry _achievementOverlayEntries[641]; // 0x1834
	int _achievementIDList[641]; // 0x9a68
	int _maxAchievementID; // 0xa46c
	int _holdInputTimer; // 0xa470
	float _scrollSpeed; // 0xa474
	LIBZHL_API void Update();
	LIBZHL_API void UpdateSecrets();
	LIBZHL_API void Render();

}; // 0xa478

struct Menu_Title {
	float PositionX; // 0x0
	float PositionY; // 0x4
	ANM2 TitleScreenSprite; // 0x8
	char pad0[0x8]; // 0x11c
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	inline ANM2* GetTitleScreenSprite() { return &this->TitleScreenSprite; }
}; // 0x124

struct Menu_Mods {
	int SelectedElement; // 0x0
	int HoldInputTimer; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 ModsMenuSprite; // 0x10
	int State; // 0x124
	ModEntry * _pointerToSelectedMod; // 0x128
	LIBZHL_API void Update();
	LIBZHL_API void Render();
         inline ANM2* GetModsMenuSprite() { return &this->ModsMenuSprite; }
    
}; // 0x12c

struct Menu_Save {
	int State; // 0x0
	int SelectedSave; // 0x4
	char pad0[0x4]; // 0x8
	int HoldInputTimer; // 0xc
	float PositionX; // 0x10
	float PositionY; // 0x14
	ANM2 SaveSelectMenuSprite; // 0x18
	ANM2 Save1DrawingSprite; // 0x12c
	ANM2 Save2DrawingSprite; // 0x240
	ANM2 Save3DrawingSprite; // 0x354
	char pad1[0x8]; // 0x468
	ANM2 DeleteButtonSprite; // 0x470
	ANM2 DeletePopupSprite; // 0x584
	char pad2[0x8]; // 0x698
	LIBZHL_API void select_save_slot(unsigned int slot);
	LIBZHL_API void Reset();
	LIBZHL_API void replace_slot_graphics(ANM2 * sprite);
         inline ANM2* GetSaveSelectMenuSprite() { return &this->SaveSelectMenuSprite; }
         inline ANM2* GetDeleteButtonSprite() { return &this->DeleteButtonSprite; }
         inline ANM2* GetDeletePopupSprite() { return &this->DeletePopupSprite; }
         inline ANM2* GetSave1DrawingSprite() { return &this->Save1DrawingSprite; }
         inline ANM2* GetSave2DrawingSprite() { return &this->Save2DrawingSprite; }
         inline ANM2* GetSave3DrawingSprite() { return &this->Save3DrawingSprite; }
    
}; // 0x6a0

struct Menu_SpecialSeeds {
	int State; // 0x0
	int SelectedElement; // 0x4
	int HoldInputTimer; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	char pad0[0x8]; // 0x14
	ANM2 SpecialSeedsSprite; // 0x1c
	char pad1[0x3c]; // 0x130
         inline ANM2* GetSpecialSeedsSprite() { return &this->SpecialSeedsSprite; }
    
}; // 0x16c

struct Menu_Challenge {
	char pad0[0x4]; // 0x0
	int SelectedChallengeID; // 0x4
	int HoldInputTimer; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	ANM2 ChallengeMenuSprite; // 0x14
	char _unkImageBase[8]; // 0x128
	LIBZHL_API void Render();
	inline ANM2* GetChallengeMenuSprite() { return &this->ChallengeMenuSprite; }
}; // 0x130

struct Menu_ControllerSelect {
	int HoldInputTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 ControllerSelectSprite; // 0x10
	char pad0[0xc]; // 0x124
	inline ANM2* GetControllerSelectSprite() { return &this->ControllerSelectSprite; }
}; // 0x130

struct Menu_Character {
	int Status; // 0x0
	char pad0[0x1]; // 0x4
	bool IsCharacterUnlocked; // 0x5
	bool IsInputPossible; // 0x6
	char pad1[0x1]; // 0x7
	int Difficulty; // 0x8
	int CooldownWhenHoldDirection; // 0xc
	int SelectedCharacterID; // 0x10
	int _chosenRandomCharacter; // 0x14
	float _randomRotationVelocity; // 0x18
	char pad2[0x4]; // 0x1c
	int _randomRotationAmount; // 0x20
	float _characterWheelDepth; // 0x24
	float _scrollSpeed; // 0x28
	float _characterWheelWidth; // 0x2c
	float MenuBlackColorizeIntensity; // 0x30
	float MenuYellowColorizeIntensity; // 0x34
	float _PositionX; // 0x38
	float _PositionY; // 0x3c
	ANM2 _BigCharPageSprite; // 0x40
	ANM2 _DifficultyOverlaySprite; // 0x154
	ANM2 _GreedDecoOverlaySprite; // 0x268
	ANM2 _CharacterMenuBGSprite; // 0x37c
	CompletionWidget _completionWidget; // 0x490
	ANM2 _DifficultyPageSprite; // 0x5ac
	ANM2 _SeedPageSprite; // 0x6c0
	ANM2 _WinStreakPageSprite; // 0x7d4
	ANM2 _EastereggPageSprite; // 0x8e8
	char pad3[0x8]; // 0x9fc
	ANM2 _SeedUnlockPageSprite; // 0xa04
	int _numCharacters; // 0xb18
	int _numCharacters_MINUS_SelectedEntry; // 0xb1c
	ANM2 _CharacterPortraitsSprite; // 0xb20
	float _horizontalScrollPosition; // 0xc34
	char pad4[0x18]; // 0xc38
	ANM2 _SeedEntrySprite; // 0xc50
	char pad5[0x50]; // 0xd64
	int _characterMenuShown; // 0xdb4
	ANM2 _PageSwapWidgetSprite; // 0xdb8
	ANM2 _TaintedMenuBGDecoSprite; // 0xecc
	char pad6[0x8]; // 0xfe0
	LIBZHL_API void Update();
	LIBZHL_API void Reset();
	LIBZHL_API void Render();
	LIBZHL_API void Init(Vector * unk);
	LIBZHL_API void SelectRandomChar();
	LIBZHL_API void UpdateRotations();
	LIBZHL_API void DoPageSwap();
	LIBZHL_API void ChangeCharacterPage(int menu);
	inline CompletionWidget* GetCompletionWidget() { return &this->_completionWidget; } 
	inline ANM2* GetBigCharPageSprite() { return &this->_BigCharPageSprite; }
	inline ANM2* GetDifficultyOverlaySprite() { return &this->_DifficultyOverlaySprite; }
	inline ANM2* GetGreedDecoSprite() { return &this->_GreedDecoOverlaySprite; }
	inline ANM2* GetBGSprite() { return &this->_CharacterMenuBGSprite; }
	inline ANM2* GetDifficultyPageSprite() { return &this->_DifficultyPageSprite; }
	inline ANM2* GetSeedPageSprite() { return &this->_SeedPageSprite; }
	inline ANM2* GetWinStreakPageSprite() { return &this->_WinStreakPageSprite; }
	inline ANM2* GetEastereggPageSprite() { return &this->_EastereggPageSprite; }
	inline ANM2* GetSeedUnlockPageSprite() { return &this->_SeedUnlockPageSprite; }
	inline ANM2* GetCharacterPortraitSprite() { return &this->_CharacterPortraitsSprite; }
	inline ANM2* GetSeedEntrySprite() { return &this->_SeedEntrySprite; }
	inline ANM2* GetPageSwapWidgetSprite() { return &this->_PageSwapWidgetSprite; }
	inline ANM2* GetTaintedBGDecoSprite() { return &this->_TaintedMenuBGDecoSprite; }

	inline int GetNumCharacters() { return this->_numCharacters; }
	inline int GetSelectedCharacterMenu() { return this->_characterMenuShown; }

	// Given a CharacterMenu ID, returns the corresponding PlayerType in the specified menu (-1 for random).
	static int LIBZHL_API Menu_Character::GetPlayerTypeFromMenuID(int menuID, bool taintedMenu);

	// Given a CharacterMenu ID, returns the corresponding PlayerType in the current menu (-1 for random).
	int LIBZHL_API Menu_Character::GetPlayerTypeFromCurrentMenuID(int menuID);

	// Returns the PlayerType of the currently selected character in the wheel (-1 for random).
	int LIBZHL_API Menu_Character::GetSelectedPlayerType();
}; // 0xfe8

struct Menu_CustomChallenge {
	int SelectedElement; // 0x0
	int HoldInputTimer; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 CustomChallengeSprite; // 0x10
	LIBZHL_API void Render();
	LIBZHL_API void Update();
	inline ANM2* GetCustomChallengeSprite() { return &this->CustomChallengeSprite; }
}; // 0x124

struct Menu_Bestiary {
	float PositionX; // 0x0
	float PositionY; // 0x4
	ANM2 BestiaryMenuSprite; // 0x8
	ANM2 DeathScreenSprite; // 0x11c
	ANM2 EnemySprite; // 0x230
	int CurrentPage; // 0x344
	int SelectedElement; // 0x348
	int LastEnemyPageID; // 0x34c
	char pad0[0xc]; // 0x350
	int unk1; // 0x35c
	int unk2; // 0x360
	char pad1[0x4]; // 0x364
	int _holdLeftArrowCounter; // 0x368
	int _holdUpArrowCounter; // 0x36c
	int _holdRightArrowCounter; // 0x370
	int _holdDownArrowCounter; // 0x374
	LIBZHL_API void LoadPreview();
	inline ANM2* GetBestiaryMenuSprite() { return &this->BestiaryMenuSprite; }
	inline ANM2* GetDeathScreenSprite() { return &this->DeathScreenSprite; }
	inline ANM2* GetEnemySprite() { return &this->EnemySprite; }
}; // 0x378

struct Menu_Collection {
	int HoldInputTimer; // 0x0
	int SelectedPage; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	int SelectedElement; // 0x10
	ANM2 CollectionMenuSprite; // 0x14
	ANM2 DeathScreenSprite; // 0x128
	char pad0[0xc]; // 0x23c
	float MoveXAxisDirection; // 0x248
	float MoveYAxisDirection; // 0x24c
	char pad1[0xc]; // 0x250
	int NumItems; // 0x25c
	inline ANM2* GetCollectionMenuSprite() { return &this->CollectionMenuSprite; }
	inline ANM2* GetDeathScreenSprite() { return &this->DeathScreenSprite; }
}; // 0x260

struct Menu_DailyChallenge {
	int State; // 0x0
	int _holdInputTimer; // 0x4
	int SelectedElement; // 0x8
	float _positionX; // 0xc
	float _positionY; // 0x10
	ANM2 _DailyRunSprite; // 0x14
	int lastRunScore; // 0x128
	int _timeHoursLeft; // 0x12c
	int _timeMinutesLeft; // 0x130
	int _timeSecondsLeft; // 0x134
	AnimationState * _leaderboardAnmState; // 0x138
	GenericPopup _genericPopup; // 0x13c
	char pad0[0x14]; // 0x25c
	GenericPrompt _genericPrompt; // 0x270
	Leaderboard _leaderboard; // 0x3a4
	char pad1[0x8]; // 0x758
	LIBZHL_API void Render();
	
}; // 0x760

struct Menu_Game {
	int KeyDownTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 GameMenuSprite; // 0x10
	ANM2 ContinueWidgetSprite; // 0x124
	char pad0[0x8]; // 0x238
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	LIBZHL_API void PreRenderContinueImg();
	LIBZHL_API bool online_mods_check();
	LIBZHL_API void UnknownJoinLobby(int unk1, int unk2, int unk3);
	inline ANM2* GetGameMenuSprite() { return &this->GameMenuSprite; }
	inline ANM2* GetContinueWidgetSprite() { return &this->ContinueWidgetSprite; }
}; // 0x240

struct Menu_KeyConfig {
	int State; // 0x0
	int SelectedElement; // 0x4
	int SelectedColumn; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	ANM2 KeyConfigSprite; // 0x14
	inline ANM2* GetKeyConfigSprite() { return &this->KeyConfigSprite; }
}; // 0x128

struct Menu_Cutscenes {
	int HoldInputTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 CutscenesMenuSprite; // 0x10
	inline ANM2* GetCutscenesMenuSprite() { return &this->CutscenesMenuSprite; }
}; // 0x124

struct MenuManager {
	char pad0[0xc]; // 0x0
	int _state; // 0xc
	float _fadeOutProgress; // 0x10
	int _fadeInActive; // 0x14
	float _fadeInProgress; // 0x18
	KColor _fadeInColor; // 0x1c
	int _returnState; // 0x30
	float _vingnetteIntensity; // 0x34
	float _backWidgetPositionOffsetY; // 0x38
	float _selectWidgetPositionOffsetY; // 0x3c
	int _selectedMenuID; // 0x40
	Vector _ViewPosition; // 0x44
	ANM2 _MenuShadowSprite; // 0x4c
	char pad1[0x18]; // 0x160
	Seeds _seedsObject; // 0x178
	Menu_Title _menuTitle; // 0x1d4
	Menu_Save _menuSave; // 0x2f8
	char pad2[0x1f8]; // 0x998
	Menu_Game _menuGame; // 0xb90
	Menu_DailyChallenge _menuDailyChallenge; // 0xdd0
	Menu_Character _menuCharacter; // 0x1530
	Menu_SpecialSeeds _menuSpecialSeeds; // 0x2518
	Menu_Challenge _menuChallenge; // 0x2684
	Menu_Collection _menuCollection; // 0x27b4
	Menu_Stats _menuStats; // 0x2a14
	Menu_Options _menuOptions; // 0xce8c
	Menu_ControllerSelect _menuControllerSelect; // 0xd114
	Menu_KeyConfig _menuKeyConfig; // 0xd244
	Menu_Cutscenes _menuCutscenes; // 0xd36c
	Menu_Bestiary _menuBestiary; // 0xd490
	Menu_CustomChallenge _menuCustomChallenge; // 0xd808
	Menu_Mods _menuMods; // 0xd92c
	char pad3[0x1cb4]; // 0xda58
	Vector _viewPositionSet[23]; // 0xf70c
	bool _shouldLerpColorModState; // 0xf7c4
	char pad4[0x3]; // 0xf7c5
	ColorModState _currentColorModState; // 0xf7c8
	ColorModState _targetColorModState; // 0xf7e0
	ColorModState _lerpColorModState; // 0xf7f8
	float _scrollinterpolationX; // 0xf810
	float _scrollinterpolationY; // 0xf814
	char pad5[0x8]; // 0xf818
	ANM2 _flySprite; // 0xf820
	char pad6[0x4]; // 0xf934
	LIBZHL_API void constructor();
	LIBZHL_API void Init();
	LIBZHL_API void Render();
	LIBZHL_API void Update();
	MenuManager()
	{
		this->constructor();
	}
	
	inline Menu_Game* GetMenuGame() {return &this->_menuGame; }
	inline Menu_Character* GetMenuCharacter() {return &this->_menuCharacter; }

	inline Menu_Title* GetMenuTitle() {return &this->_menuTitle; }
	inline Menu_Save* GetMenuSave() {return &this->_menuSave; }
	inline Menu_Challenge* GetMenuChallenge() {return &this->_menuChallenge; }
	inline Menu_DailyChallenge* GetMenuDailyChallenge() {return &this->_menuDailyChallenge; }
	inline Menu_Collection* GetMenuCollection() {return &this->_menuCollection; }
	inline Menu_Bestiary* GetMenuBestiary() {return &this->_menuBestiary; }
	inline Menu_Stats* GetMenuStats() {return &this->_menuStats; }
	inline Menu_Options* GetMenuOptions() {return &this->_menuOptions; }
	inline Menu_SpecialSeeds* GetMenuSpecialSeeds() {return &this->_menuSpecialSeeds; }
	inline Menu_ControllerSelect* GetMenuControllerSelect() {return &this->_menuControllerSelect; }
	inline Menu_KeyConfig* GetMenuKeyConfig() {return &this->_menuKeyConfig; }
	inline Menu_Cutscenes* GetMenuCutscenes() {return &this->_menuCutscenes; }
	inline Menu_CustomChallenge* GetMenuCustomChallenge() {return &this->_menuCustomChallenge; }
	inline Menu_Mods* GetMenuMods() {return &this->_menuMods; }
	inline ColorModState* GetCurrentColorModifier() { return &this->_currentColorModState; }
	inline ColorModState* GetTargetColorModifier() { return &this->_targetColorModState; }
	inline ColorModState* GetLerpColorModifier() { return &this->_lerpColorModState; }
}; // 0xf938

struct Menu_Character_Entry {
	char * animationName; // 0x0
	int playerType; // 0x4
	bool hidden; // 0x8
	char pad0[0xf]; // 0x9
	LIBZHL_API bool IsCharacterAvailable(int unused);
}; // 0x18

struct Menu_Online {
	char pad0[0x4]; // 0x0
	ANM2 _anm2; // 0x4
	char pad1[0x114]; // 0x118
	int _prevState; // 0x22c
	int _state; // 0x230
	LIBZHL_API void Update();
	LIBZHL_API void Render();
}; // 0x234

struct Menu_OnlineLobby {
}; // 0x1

struct Menu_OnlineOptions {
	LIBZHL_API void Update();
}; // 0x1

struct ModManager_CharacterMap {
	int normal; // 0x0
	int tainted; // 0x4
}; // 0x8

struct ModReference {
	std_string _mainLuaPath; // 0x0
	std_string _dataDirectory; // 0x18
	std_string _name; // 0x30
	LuaBridgeRef * _luaTableRef; // 0x48
	int _apiVersion; // 0x4c
}; // 0x50

struct NullFrame {
	char pad0[0x48]; // 0x0
	inline Vector* GetPos() {return (Vector*)((char*)this); }
	inline bool* IsVisible() {return (bool*)((char*)this + 0xC); }
	inline Vector* GetScale() {return (Vector*)((char*)this + 0x10); }
	inline ColorMod* GetColor() {return (ColorMod*)((char*)this + 0x18); }
	inline float* GetRotation() {return (float*)((char*)this + 0x44); }
}; // 0x48

struct PocketItem {
	int _id; // 0x0
	unsigned int _type; // 0x4
}; // 0x8

struct PosVel {
	Vector pos; // 0x0
	Vector vel; // 0x8
	PosVel() : pos(Vector()), vel(Vector()) {}
	PosVel(Vector _pos, Vector _vel) : pos(_pos), vel(_vel) {}

	PosVel operator+(const PosVel& other)
	{
		return PosVel(pos + other.pos, vel + other.vel);
	}
	
	PosVel operator-(const PosVel& other)
	{		
		return PosVel(pos - other.pos, vel - other.vel);
	}
	
	PosVel operator/(float amount)
	{		
		return PosVel(pos / amount, vel / amount);
	}
	
	PosVel operator*(float amount)
	{		
		return PosVel(pos * amount, vel * amount);
	}

}; // 0x10

struct ProjectileParams {
	bool GridCollision; // 0x0
	char pad0[0x3]; // 0x1
	float HeightModifier; // 0x4
	float FallingSpeedModifier; // 0x8
	float FallingAccelModifier; // 0xc
	float VelocityMulti; // 0x10
	float Scale; // 0x14
	float CircleAngle; // 0x18
	float HomingStrength; // 0x1c
	float CurvingStrength; // 0x20
	float Acceleration; // 0x24
	float Spread; // 0x28
	ColorMod Color; // 0x2c
	unsigned long long int BulletFlags; // 0x58
	Vector PositionOffset; // 0x60
	Vector TargetPosition; // 0x68
	Vector FireDirectionLimit; // 0x70
	float DotProductLimit; // 0x78
	int WiggleFrameOffset; // 0x7c
	unsigned long long int ChangeFlags; // 0x80
	float ChangeVelocity; // 0x88
	unsigned int ChangeTimeout; // 0x8c
	float DepthOffset; // 0x90
	unsigned int Variant; // 0x94
	char pad1[0x4]; // 0x98
	float Damage; // 0x9c
	char pad2[0x8]; // 0xa0
}; // 0xa8

struct QueueItemData {
	ItemConfig_Item * _item; // 0x0
	int _charge; // 0x4
	unsigned int _flags; // 0x8
	int _vardata; // 0xc
}; // 0x10

struct Rendering {
	LIBZHL_API static void __stdcall PushCurrentRenderTarget();
	LIBZHL_API static void __stdcall RestorePreviousRenderTarget();
}; // 0x1

struct RoomConfig_VariantSet {
	DisjointedSet * _set; // 0x0
	LIBZHL_API bool Add(unsigned int variant);
        inline uint32_t AddUnique(uint32_t variant)
        {
            bool isUnique = this->Add(variant);
            if (!isUnique)
            {
                variant = this->_set->upperBound + 1;
                this->Add(variant);
            }

            return variant;
        }
   
}; // 0x4

struct SFXManager {
	LIBZHL_API void Play(int ID, float Volume, int FrameDelay, bool Loop, float Pitch, float Pan);
	LIBZHL_API void LoadConfig(char * xmlpath, bool ismod);
}; // 0x1

struct Shape {
	char pad0[0x8]; // 0x0
	LIBZHL_API void Capsula(Capsule * Thing);
	LIBZHL_API void Circle(Vector * Position, float Scale);
	inline int* GetTimeout() { return (int*)((char*)this + 0x4); }
}; // 0x8

struct ShapeRenderer {
	LIBZHL_API int RenderLine(Vector * pos1, Vector * pos2, KColor * col1, KColor * col2, float const & thickness);
	int OutlineQuad(DestinationQuad* quad, KColor* col, float thickness) 
	{ // LOOK, OUR FLOAT IS NOT A POINTER! ISN'T THAT A CONCEPT??????? WHAT????????
		int ret = this->RenderLine(&quad->_topLeft, &quad->_topRight, col, col, thickness);
		this->RenderLine(&quad->_topRight, &quad->_bottomRight, col, col, thickness);
		this->RenderLine(&quad->_bottomRight, &quad->_bottomLeft, col, col, thickness);
		this->RenderLine(&quad->_bottomLeft, &quad->_topLeft, col, col, thickness);
		return ret;
	}
}; // 0x1

struct StaticArray {
	void * data; // 0x0
	unsigned short int size; // 0x4
	char pad0[0x2]; // 0x6
}; // 0x8

struct SteamCloudFile : public KAGE_Filesys_FileStream {
	char const * _steamCloudFilename; // 0xc
	char * _buffer; // 0x10
	unsigned int _bufferSize; // 0x14
	unsigned int _position; // 0x18
	unsigned int _size; // 0x1c
	bool _unk; // 0x20
	bool _isEof; // 0x21
	char pad0[0x2]; // 0x22
	LIBZHL_API bool PushToSteamCloud(char const * path, unsigned int size);
        SteamCloudFile()
        {
            this->_vtable = __ptr_SteamCloudFile_vftable;
            this->_status = 2;
            this->_filePath = nullptr;
            this->_steamCloudFilename = nullptr;
            this->_buffer = nullptr;
            this->_bufferSize = 0;
            this->_position = 0;
            this->_size = 0;
            this->_unk = false;
            this->_isEof = false;
        }
   
}; // 0x24

struct TearParams {
	int _tearVariant; // 0x0
	int _bombVariant; // 0x4
	ColorMod _tearColor; // 0x8
	int _unused; // 0x34
	BitSet128 _flags; // 0x38
	float _tearDamage; // 0x48
	float _tearScale; // 0x4c
	float _tearHeight; // 0x50
	float _massMultiplier; // 0x54
	float _knockbackMultiplier; // 0x58
	float _speedMultiplier; // 0x5c
	int _tearDisplacement; // 0x60
	LIBZHL_API void constructor();
	TearParams() 
	{
		this->constructor();
	}
}; // 0x64

struct TemporaryEffect {
	ItemConfig_Item * _item; // 0x0
	int _count; // 0x4
	int _cooldown; // 0x8
	char pad0[0x4]; // 0xc
}; // 0x10

struct TrinketPoolItem {
	unsigned int _ID; // 0x0
	bool _inPool; // 0x4
	bool _isAvailable; // 0x5
	char pad0[0x2]; // 0x6
}; // 0x8

struct WaterClipInfo {
	unsigned int bitFlags; // 0x0
	float unkFloat; // 0x4
}; // 0x8

struct Weapon {
	char pad0[0x4]; // 0x0
	Entity * _owner; // 0x4
	char pad1[0x4]; // 0x8
	float _fireDelay; // 0xc
	float _maxFireDelay; // 0x10
	float _charge; // 0x14
	char pad2[0x8]; // 0x18
	Vector _direction; // 0x20
	char pad3[0x8]; // 0x28
	int _weaponType; // 0x30
	unsigned int _modifiers; // 0x34
	int _numFired; // 0x38
	char pad4[0x4]; // 0x3c
	LIBZHL_API void PlayItemAnim(unsigned int collectibleID, int itemAnim, Vector const & pos, float Charge);
	LIBZHL_API void SetBlinkTime(int Delay);
	LIBZHL_API void TriggerTearFired(Vector const & pos, int FireAmount);
	LIBZHL_API bool IsAxisAligned();
	LIBZHL_API bool IsItemAnimFinished(unsigned int collectibleID);
	LIBZHL_API void ClearItemAnim(unsigned int collectibleID);
	LIBZHL_API void SetHeadLockTime(int Time);
	LIBZHL_API static Entity_Laser * FireBrimstone(Entity * entity, Vector const & position, Vector const & direction, float damageMult, float unk1, unsigned int unk2);
	LIBZHL_API Entity_Knife * FireSword(Entity * param_1, unsigned int param_2, float param_3, bool param_4, bool param_5, unsigned int param_6, Entity * param_7);
	void virtual_unk455() { }
	void virtual_unk456() { }
	void virtual_unk457() { }
	LIBZHL_API void Fire(Vector const & pos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & pos, bool IsShooting, bool IsInterpolated);
	void virtual_unk458() { }
	void virtual_unk459() { }
	LIBZHL_API float GetMaxCharge();
	LIBZHL_API float Original_GetMaxCharge();
	void virtual_unk460() { }
	void virtual_unk461() { }
	void virtual_unk462() { }
	LIBZHL_API Entity * GetMainEntity();
	LIBZHL_API Entity * Original_GetMainEntity();
	void virtual_unk463() { }
	void virtual_unk464() { }
	void virtual_unk465() { }
	void virtual_unk466() { }
	void virtual_unk467() { }
	void virtual_unk468() { }
	inline Entity* GetOwner() { return this->_owner; }
	inline float* GetFireDelay() { return &this->_fireDelay; }
	inline float GetMaxFireDelay() { return this->_maxFireDelay; }
	inline float* GetCharge() { return &this->_charge; }
	inline Vector* GetDirection() { return &this->_direction; }
	inline int GetWeaponType() { return this->_weaponType; }
	inline uint32_t* GetModifiers() { return &this->_modifiers; }
	inline int GetNumFired() { return this->_numFired; }
}; // 0x40

struct Weapon_Brimstone : public Weapon {
	char pad0[0x8]; // 0x40
	LIBZHL_API bool do_baby_brimstone_burst(Vector * unused1, Vector * dir, int unused2, float damageScale);
	LIBZHL_API void Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	void virtual_unk469() { }
	void virtual_unk470() { }
	void virtual_unk471() { }
	void virtual_unk472() { }
	void virtual_unk473() { }
	void virtual_unk474() { }
	void virtual_unk475() { }
	void virtual_unk476() { }
	void virtual_unk477() { }
	void virtual_unk478() { }
	void virtual_unk479() { }
	void virtual_unk480() { }
	void virtual_unk481() { }
	void virtual_unk482() { }
	void virtual_unk483() { }
	void virtual_unk484() { }

}; // 0x48

struct Weapon_MonstrosLung : public Weapon {
	LIBZHL_API void Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	void virtual_unk485() { }
	void virtual_unk486() { }
	void virtual_unk487() { }
	void virtual_unk488() { }
	void virtual_unk489() { }
	void virtual_unk490() { }
	void virtual_unk491() { }
	void virtual_unk492() { }
	void virtual_unk493() { }
	void virtual_unk494() { }
	void virtual_unk495() { }
	void virtual_unk496() { }
	void virtual_unk497() { }
	void virtual_unk498() { }
	void virtual_unk499() { }
	void virtual_unk500() { }

}; // 0x40

struct Weapon_MultiShotParams {
	short int numTears; // 0x0
	short int numLanesPerEye; // 0x2
	float spreadAngleTears; // 0x4
	float spreadAngleLaser; // 0x8
	float speadAngleTechX; // 0xc
	float spreadAngleKnife; // 0x10
	int numEyesActive; // 0x14
	float multiEyeAngle; // 0x18
	bool isCrossEyed; // 0x1c
	bool isShootingBackwards; // 0x1d
	bool isShootingSideways; // 0x1e
	char pad0[0x1]; // 0x1f
	short int numRandomDirTears; // 0x20
	char pad1[0x2]; // 0x22
}; // 0x24

struct WeightedOutcomePicker_Outcome {
	unsigned int _value; // 0x0
	unsigned int _weight; // 0x4
}; // 0x8

struct WeightedOutcomePicker {
	vector_Outcome _outcomes; // 0x0
	LIBZHL_API unsigned int PickOutcome(RNG rng);
	LIBZHL_API void AddOutcomeWeight(WeightedOutcomePicker_Outcome outcome, bool unk);
	LIBZHL_API void * InsertOutcomeToVec(WeightedOutcomePicker_Outcome * unk, WeightedOutcomePicker_Outcome * outcome);
    inline vector_Outcome* GetOutcomes() { return (vector_Outcome*)this; }
}; // 0xc

struct xmldocument_rep {
	LIBZHL_API void parse(char * xmldata);

}; // 0x1

struct xmlnode_rep {
	LIBZHL_API xml_node<char> * first_node(char * name, int size, bool casesensitive);

}; // 0x1

LIBZHL_API char * * __stdcall GetXMLNode(char * thi, int unk, char * name);
LIBZHL_API void RepCaughtException(int x);
LIBZHL_API void KAGE_EngineStartup(int numArgs, char * * args);
LIBZHL_API void  IsaacStartup(int param_1, int param_2, int param_3);
LIBZHL_API void __stdcall SetupSaveDirectories();
LIBZHL_API GridEntity * __fastcall CreateGridEntity(GridEntityType type, unsigned int seed);
LIBZHL_API int IsaacMain(int argc, char * * argv);
LIBZHL_API void GetLevelName(std_string * result, unsigned int levelStage, unsigned int stageType, unsigned int curseMask, int BASEMENTnum, bool jumble, int mode);
LIBZHL_API unsigned int __stdcall Random();

namespace OpenGL {
	bool __stdcall wglSwapBuffers(HDC hdc);

}
namespace VCRuntime {
	void __stdcall _CxxThrowException(void * except, ThrowInfo * info);

#ifdef DEBUG
	void __stdcall _CxxThrowExceptionD(void * except, ThrowInfo * info);

#endif
}namespace AsmDefinitions {
	extern LIBZHL_API char MaxBombs_ControlBombs;
	extern LIBZHL_API char DisableExitPrompt;
	extern LIBZHL_API char PreRenderHistoryItem;
	extern LIBZHL_API char TakeDmg_CountdownOffset;
	extern LIBZHL_API char PreSampleLaserCollision;
	extern LIBZHL_API char EntityPlayer_RemoveCollectible_TriggerCollectibleRemoved;
	extern LIBZHL_API char MaxKeys_HudRender;
	extern LIBZHL_API char RenderCharacterWheel_PreRenderVanillaCharacter;
	extern LIBZHL_API char PreRenderHistoryItemColorModOffset;
	extern LIBZHL_API char LeaderboardGoalPatch;
	extern LIBZHL_API char HideModdedCharacterByAchievement;
	extern LIBZHL_API char CustomModManager_CurseMapIconsArrayOffset;
	extern LIBZHL_API char KAGE_Sound_Manager_Initialize_OpenAL32_call_alcCreateContext;
	extern LIBZHL_API char RenderCharacterWheel_GetMenuCharacterIndex;
	extern LIBZHL_API char TryAddToBagOfCraftingPostPickType;
	extern LIBZHL_API char MenuCharacter_PreSelectCharacter;
	extern LIBZHL_API char EntityNPC_UpdatePickupGhosts_ShouldShow;
	extern LIBZHL_API char LevelGenerator_TryResizeEndroom_Fix;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Knockback;
	extern LIBZHL_API char RenderCharacterWheel_RenderPositionStackOffset;
	extern LIBZHL_API char RenderCharacterWheel_PostRenderVanillaCharacter;
	extern LIBZHL_API char StatMultiplier;
	extern LIBZHL_API char RenderCharacterWheel_RenderModdedCharacter;
	extern LIBZHL_API char RenderVanillaCharacterMenu;
	extern LIBZHL_API char LaserDoDamagePlayer;
	extern LIBZHL_API char EntityPickup_UpdatePickupGhosts_ShouldShow;
	extern LIBZHL_API char RenderVanillaCharacterMenu_EdenTokens;
	extern LIBZHL_API char SetSaveSlotLocalFilePath;
	extern LIBZHL_API char RenderCustomCharacterMenu_Nop;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CoopMenu;
	extern LIBZHL_API char StagePortrait_ExtraPortraitOverrideCheck;
	extern LIBZHL_API char TryAddToBagOfCraftingAccessArray;
	extern LIBZHL_API char RenderCustomCharacterMenu_RenderCustom;
	extern LIBZHL_API char EntityNPC_UpdatePickupGhosts_GetShopkeeperLoot;
	extern LIBZHL_API char RenderCustomCharacterMenu_RenderDefault;
	extern LIBZHL_API char SplitTears_SwordBeam;
	extern LIBZHL_API char EntityNPC_GetFireplaceLoot_SelectRNG;
	extern LIBZHL_API char SplitTears_CricketsBody;
	extern LIBZHL_API char PreRenderHistoryItemStackOffsets;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CharacterMenuAlt;
	extern LIBZHL_API char RenderCustomCharacterCoopMenu_GetAnimName;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CharacterPortraitsAlt;
	extern LIBZHL_API char EntityConfig_LoadPlayers_DeathScreenAlt;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CoopMenuAlt;
	extern LIBZHL_API char EntityConfig_LoadPlayers_ControlsAlt;
	extern LIBZHL_API char EntityList_destructor_RemoveEntityMainEL;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CharacterMenu;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CustomBackgroundCheck;
	extern LIBZHL_API char MaxCoins_HudRender;
	extern LIBZHL_API char LoadArchiveFile_ArchiveFileOffset;
	extern LIBZHL_API char EntityConfig_LoadPlayers_CharacterPortraits;
	extern LIBZHL_API char CustomModManager_CurseMapIconsColorModAlphaOffset;
	extern LIBZHL_API char EntityNPC_GetShopkeeperLoot_SelectRNG;
	extern LIBZHL_API char EntityConfig_LoadPlayers_DeathScreen;
	extern LIBZHL_API char EntityConfig_LoadPlayers_Controls;
	extern LIBZHL_API char EntityConfig_PostLoadMods_BSkinParentGetName;
	extern LIBZHL_API char RenderCustomCharacterMenu_GetAnimName;
	extern LIBZHL_API char RenderCustomCharacters_GetAnimName;
	extern LIBZHL_API char Backdrop_PreRenderControls_GetCharacterAnimName;
	extern LIBZHL_API char RoomInit_VoidEx;
	extern LIBZHL_API char GameOver_Render_GetCharacterAnimName;
	extern LIBZHL_API char RenderPocketItemPillIdentifiedCheck;
	extern LIBZHL_API char TryRemoveSmeltedTrinketIdCheck;
	extern LIBZHL_API char PlayerItemNoMetronome;
	extern LIBZHL_API char ForceAddPillEffectIdCheck;
	extern LIBZHL_API char UsePillIdentifyPill;
	extern LIBZHL_API char GreedDonationCoinCountForModdedCharacters;
	extern LIBZHL_API char ItemPoolGetPillEffect;
	extern LIBZHL_API char MaxKeys_AddKeys;
	extern LIBZHL_API char MaxCoins_AddCoins;
	extern LIBZHL_API char HistoryHudRecomputeGfx;
	extern LIBZHL_API char HistoryHudRecomputeGfx_Jump;
	extern LIBZHL_API char HistoryHudRecomputeGfx_RefreshCheck;
	extern LIBZHL_API char LoadBackdropGraphics_VoidEx2;
	extern LIBZHL_API char PostRenderHistoryItem;
	extern LIBZHL_API char GreedDonationBreakChanceForModdedCharacters;
	extern LIBZHL_API char GameState_Read_ItemPoolRead;
	extern LIBZHL_API char SplitTears_LaserPopTearOffset;
	extern LIBZHL_API char GameState_Read_Return;
	extern LIBZHL_API char FamiliarGetMultiplier;
	extern LIBZHL_API char EntityPickup_GetLootList_SelectRNG;
	extern LIBZHL_API char MaxCoins_CurseMist_Exit;
	extern LIBZHL_API char EntityNPC_UpdatePickupGhosts_ShopkeeperCheck;
	extern LIBZHL_API char MaxCoins_CurseMist;
	extern LIBZHL_API char MaxKeys_CurseMist;
	extern LIBZHL_API char SetupSaveDirectoryModSaveDataFolder;
	extern LIBZHL_API char MaxBombs_AddBombs;
	extern LIBZHL_API char MaxBombs_HudRender;
	extern LIBZHL_API char SetSaveSlotSteamCloudFileName;
	extern LIBZHL_API char MaxBombs_CurseMist;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Shrink;
	extern LIBZHL_API char TearsCap;
	extern LIBZHL_API char StatMultiplier_Jump;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_MidasFreeze;
	extern LIBZHL_API char TakeDmg_PreEntityCallback;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Confusion;
	extern LIBZHL_API char SplitTears_AbsorbNewTearOffset;
	extern LIBZHL_API char TakeDmg_PostEntityCallback;
	extern LIBZHL_API char AutoReassignControllers_Unassign;
	extern LIBZHL_API char TakeDmg_PrePlayerCallback;
	extern LIBZHL_API char TakeDmg_PostPlayerCallback;
	extern LIBZHL_API char CanPickupJawboneInlinedFalse;
	extern LIBZHL_API char TakeDmg_FlagsOffset;
	extern LIBZHL_API char TakeDmg_AmountFloatOffset;
	extern LIBZHL_API char TakeDmg_SourceOffset;
	extern LIBZHL_API char TakeDmg_PlayerAmountHeartsOffset;
	extern LIBZHL_API char TakeDmg_PlayerRedHeartDamagedOffset;
	extern LIBZHL_API char TakeDmg_PlayerLowerFlagsOffset;
	extern LIBZHL_API char EvaluateItems_PlayerTears;
	extern LIBZHL_API char LoadButtonMaps_InputConfigsPath;
	extern LIBZHL_API char EvaluateItems_PlayerDamage;
	extern LIBZHL_API char EvaluateItems_TearsUp;
	extern LIBZHL_API char EvaluateItems_FlatTears;
	extern LIBZHL_API char EvaluateItems_DamageUp;
	extern LIBZHL_API char Manager_Init_PreInitCursor;
	extern LIBZHL_API char EvaluateItems_FlatDamage;
	extern LIBZHL_API char EvaluateItems_RangeUp;
	extern LIBZHL_API char EvaluateItems_ShotSpeedUp;
	extern LIBZHL_API char EvaluateItems_SpeedUp;
	extern LIBZHL_API char SplitTears_LaserCricketsBody;
	extern LIBZHL_API char TryAddToBagOfCraftingBelialEffectEspOffset;
	extern LIBZHL_API char SplitTears_KnifeCricketsBody;
	extern LIBZHL_API char SplitTears_KnifeParasite;
	extern LIBZHL_API char SplitTears_Parasite;
	extern LIBZHL_API char SplitTears_Haemo;
	extern LIBZHL_API char SplitTears_KnifeHaemo;
	extern LIBZHL_API char Room_SpawnGreedModeWave_PostGetRandomRoom;
	extern LIBZHL_API char SplitTears_Absorb;
	extern LIBZHL_API char BrimstoneBallDamageEbpOffset;
	extern LIBZHL_API char SplitTears_Spore;
	extern LIBZHL_API char SplitTears_LudoSticky;
	extern LIBZHL_API char GelloDamageEbpOffset;
	extern LIBZHL_API char SplitTears_LaserSticky;
	extern LIBZHL_API char SplitTears_LaserStickyLaserOffset;
	extern LIBZHL_API char PreTriggerBedSleepEffect;
	extern LIBZHL_API char SplitTears_KnifeSticky;
	extern LIBZHL_API char SplitTears_LaserPop;
	extern LIBZHL_API char SplitTears_LaserPopJump;
	extern LIBZHL_API char SplitTears_Bone;
	extern LIBZHL_API char SplitTears_KnifeBone;
	extern LIBZHL_API char SplitTears_AngelicPrism;
	extern LIBZHL_API char BrimstoneBallDamage;
	extern LIBZHL_API char SplitTears_PreAngelicPrism;
	extern LIBZHL_API char SplitTears_PostAngelicPrism;
	extern LIBZHL_API char SplitTears_AngelicPrismOriginalTearOffset;
	extern LIBZHL_API char UpdateBoneSwingDamage;
	extern LIBZHL_API char UpdateBoneSwingDamageFireplace;
	extern LIBZHL_API char StagePortrait_PortraitOverride;
	extern LIBZHL_API char LaserDoDamagePushEbxA;
	extern LIBZHL_API char LaserDoDamagePushEbxB;
	extern LIBZHL_API char LaserDoDamageA;
	extern LIBZHL_API char LaserDoDamageB;
	extern LIBZHL_API char LaserDoDamageExit;
	extern LIBZHL_API char GelloDamage;
	extern LIBZHL_API char GelloDamageFireplace;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Baited;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Bleeding;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_BrimstoneMark;
	extern LIBZHL_API char Game_Update_MainUpdate;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Burn;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Charmed;
	extern LIBZHL_API char ControllerDisconnected_Unassign;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Fear;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Freeze;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Ice;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Magnetized;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Poison;
	extern LIBZHL_API char DeliriumAggression;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Slowing;
	extern LIBZHL_API char InlinedGetStatusEffectTarget_Weakness;
	extern LIBZHL_API char KAGE_Sound_Manager_Initialize_OpenAL32_pre_alcCreateContext;
	extern LIBZHL_API char SetupSaveDirectoryFinalFallback;
	extern LIBZHL_API char SetupSaveDirectoryModFolder;
	extern LIBZHL_API char ButtonMapManager_LoadButtonMaps_RapidXmlParse;
	extern LIBZHL_API char DeliriumVadeRetro;
	extern LIBZHL_API char SaveButtonMaps_InputConfigsPath;
	extern LIBZHL_API char CanPickupMelee;
	extern LIBZHL_API char CanPickupBoomerang;
	extern LIBZHL_API char CanPickupJawboneInlinedStart;
	extern LIBZHL_API char SetActiveItemGFXPath;
	extern LIBZHL_API char CanPickupJawboneInlinedTrue;
	extern LIBZHL_API char TryAddToBagOfCraftingChosenTypeEspOffset;
	extern LIBZHL_API char TryAddToBagOfCraftingPickupEspOffset;
	extern LIBZHL_API char TryAddToBagOfCraftingInvalidType;
	extern LIBZHL_API char TryAddToBagOfCraftingArrayLength;
	extern LIBZHL_API char PostMeleeHitboxInit;
	extern LIBZHL_API char PreBombApplyTearFlagEffects;
	extern LIBZHL_API char KAGE_ReferenceCount_EntitySaveState_DecrementReference_SaveStateDestructor;
	extern LIBZHL_API char PreBedSleepCallback;
	extern LIBZHL_API char PreBedSleepCallback_IncPlayerAddr;
	extern LIBZHL_API char PreMMorphCallback;
	extern LIBZHL_API char PreMMorphJump;
	extern LIBZHL_API char ControllerDisconnected_Reassign;
	extern LIBZHL_API char SetActiveItemCropOffset;
	extern LIBZHL_API char Player_HurtSoundOverride;
	extern LIBZHL_API char Player_DeathSoundOverride;
	extern LIBZHL_API char Player_SoulOfLazarusDeathSoundOverride;
	extern LIBZHL_API char Player_SoulDeathSoundOverride;
	extern LIBZHL_API char Player_AstralProjectionDeathSoundOverride;
	extern LIBZHL_API char Level_RestoreGameState_PreRoomLoad;
	extern LIBZHL_API char Camera_ClampOverride;
	extern LIBZHL_API char Camera_SlowStopClampOverride;
	extern LIBZHL_API char StagePortrait_ExtraPortraitOverrideCheckNightmareOffset;
	extern LIBZHL_API char DifferentNumberOfAchievements;
	extern LIBZHL_API char LoadArchiveFile_SkipFile;
	extern LIBZHL_API char CustomModManager_LoadCustomSprites;
	extern LIBZHL_API char CustomModManager_CurseCaptureModEntry;
	extern LIBZHL_API char CustomModManager_CurseRegisterSprite;
	extern LIBZHL_API char CustomModManager_CurseGuessIdOffset;
	extern LIBZHL_API char CustomModManager_CurseRegisterFrameOffset;
	extern LIBZHL_API char CustomModManager_CurseMapIconsPositionOffset;
	extern LIBZHL_API char CustomModManager_CurseMapIconsCustomRender;
	extern LIBZHL_API char LoadBackdropGraphics_VoidEx1;
	extern LIBZHL_API char Manager_Render_PreCursorRender;
	extern LIBZHL_API char Portals_VoidEx1;
	extern LIBZHL_API char Portals_VoidEx2;
	extern LIBZHL_API char PortalUnaliveSelf;
	extern LIBZHL_API char Misc_FixOptionsMusicVolumeBoundCheck;
	extern LIBZHL_API char Misc_PushRenderTargetStackOverflow;
	extern LIBZHL_API char Level_Reset_RoomReset;
	extern LIBZHL_API char Level_Reset_PostRoomReset;
	extern LIBZHL_API char Manager_Render_OnCursorRender;
	extern LIBZHL_API char GetTearHitParams_BloodyTears;
	extern LIBZHL_API char GetTearHitParams_BloodyTearsDisabled;
	extern LIBZHL_API char LoadArchiveFile_CheckFile;
	extern LIBZHL_API char LoadArchiveFile_DoWhileBegin;
	extern LIBZHL_API char LoadArchiveFile_DoWhileEnd;
	extern LIBZHL_API char Image_GetBatch_TryGetReusableTransparentBatch;
	extern LIBZHL_API char Image_BeginQuadBatch_InvalidateLastTransparentBatch;
	extern LIBZHL_API char Minimap_Render_SetShaderPreImageRender;
	extern LIBZHL_API char EntityPlayer_RecomputeWispCollectibles_TriggerCollectibleAdded;
	extern LIBZHL_API char EntityPlus_PlayerForceCamo;
	extern LIBZHL_API char EntityTear_InitTear_PrePlaySound;
	extern LIBZHL_API char EntityPlayer_StoreGameState_AssignUnlistedFamiliarData;
	extern LIBZHL_API char EntityTear_InitTear_PostPlaySound;
	extern LIBZHL_API char Room_RestoreState_ClearSavedEntities;
	extern LIBZHL_API char LostSoulHeartTypeSkipSpawnPuddle;
	extern LIBZHL_API char Game_Update_Return;
	extern LIBZHL_API char MoveRandomlyAxisAligned_FamiliarCheckA;
	extern LIBZHL_API char MoveRandomlyAxisAligned_FamiliarCheckA_JumpTarget;
	extern LIBZHL_API char MoveRandomlyAxisAligned_FamiliarCheckB;
	extern LIBZHL_API char MoveRandomlyAxisAligned_FamiliarCheckB_JumpTarget;
	extern LIBZHL_API char RedirectToLocalizedResources;
	extern LIBZHL_API char EntityPlayer_RecomputeWispCollectibles_TriggerCollectibleRemoved;
	extern LIBZHL_API char EntityPlayer_TriggerCollectibleRemoved_Stompy;
	extern LIBZHL_API char EntityPlayer_TriggerCollectibleRemoved_Heartbreak;
	extern LIBZHL_API char EntityList_Update_PreCommitRemovedEntities;
	extern LIBZHL_API char Ambush_SpawnWave_PostGetRandomRoom;
	extern LIBZHL_API char Room_save_entity_CheckShouldSaveEntity;
	extern LIBZHL_API char Room_Pre_Render_Entities;
	extern LIBZHL_API char Game_RestoreState_PostBackwardsStageDescRestore;
	extern LIBZHL_API char Level_place_rooms_backwards_Treasure_AssignEntitySaveStateVector;
	extern LIBZHL_API char Level_Init_PostMyosotisEffect;
	extern LIBZHL_API char Level_place_rooms_backwards_Boss_AssignEntitySaveStateVector;
	extern LIBZHL_API char Level_generate_dark_closet_PostGenerateCollectibleSaveState;
	extern LIBZHL_API char Room_SaveState_ClearSavedEntities;
	extern LIBZHL_API char PlayerManager_RestoreGameState_AssignBackupFamiliarData;
	extern LIBZHL_API char EntityPlayer_UseActiveItem_MovingBox_ClearVector;
	extern LIBZHL_API char EntityList_Reset_RemoveNonPersistentEntity;
	extern LIBZHL_API char EntityPlayer_StoreGameState_FamiliarStoreState;
	extern LIBZHL_API char EntityPickup_InitFlipState_PostSaveStateConstructor;
	extern LIBZHL_API char EntityPickup_TryFlip_PostRestoreFlipState;
	extern LIBZHL_API char EntityNPC_ai_mothers_shadow_ChangeMineshaftRoom;
	extern LIBZHL_API char EntityList_destructor_RemoveEntityPersistentEL;
	extern LIBZHL_API char EntityList_Update_RemoveEntityMainEL;
	extern LIBZHL_API char EntityList_Update_RemoveEntityPersistentEL;
	extern LIBZHL_API char AutoReassignControllers_Reassign;
	extern LIBZHL_API char ControllerDisconnected_LoopEnd;
	extern LIBZHL_API char DeliriumSpawnCompanion;
}
