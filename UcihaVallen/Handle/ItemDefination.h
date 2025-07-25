#pragma once
using namespace std;
#define Property_Zero 0
#define Property_NoSeed 1
#define Property_Dropless 2
#define Property_Beta 4
#define Property_Mod 8
#define Property_Chemical 12
#define Property_Untradable 16
#define Property_Wrenchable 32
#define Property_MultiFacing 64
#define Property_Permanent 128
#define Property_AutoPickup 256
#define Property_WorldLock 512
#define Property_NoSelf 1024
#define Property_RandomGrow 2048
#define Property_Public 4096
#define Property_Foreground 8192

enum ClothTypes { HAIR, SHIRT, PANTS, FEET, FACE, HAND, BACK, MASK, NECKLACE, ANCES, NONE };
enum BlockTypes { FOREGROUND, BACKGROUND, CONSUMABLE, SEED, Display_Shelf, PAIN_BLOCK, BEDROCK, VIP_ENTRANCE, Heart_Monitor, Painting_Easel, MAIN_DOOR, SIGN, DOOR, CLOTHING, FIST, WRENCH, CHECKPOINT, LOCK, LOCK_BOT, GATEWAY, TREASURE, WEATHER, TRAMPOLINE, MANNEQUIN, TOGGLE_FOREGROUND, CHEMICAL_COMBINER, SWITCH_BLOCK, SFX_FOREGROUND, RANDOM_BLOCK, Spirit_Storage, PORTAL, PLATFORM, Fish_Mount, MAILBOX, GIVING_TREE, MAGIC_EGG, CRYSTAL, GEMS, DEADLY, CHEST, FACTION, BULLETIN_BOARD, BOUNCY, ANIM_FOREGROUND, COMPONENT, SUCKER, FISH, FISH_TANK, BATTLE_CAGE, STEAM, GROUND_BLOCK, PORTRAIT, DISPLAY, STORAGE, VENDING, DONATION, PHONE, SEWINGMACHINE, CRIME_VILLAIN, PROVIDER, ADVENTURE, CCTV, STORAGE_BOX, TIMER, ITEM_SUCKER, TRICKSTER, KRANKEN, FOSSIL, GEIGER_CHARGER, COUNTRY_FLAG, AUTO_BLOCK, GAME_BLOCK, GAME_GENERATOR, OVEN, PET_TRAINER, ACHIEVEMENT_BLOCK, UNKNOWN };
struct ItemDB {
	bool block_possible_put = false;
	int grindable_count = 0;
	int grindable_prize = 0;
	string event_name = "";
	int event_total = 0;
	int oprc = 0;
	int flagmay = 256;
	int zombieprice = 0;
	int surgeryprice = 0;
	int wolfprice = 0;
	int pwl = 0;
	bool blocked_place = false, unobtainable = false;
	int extra_gems = 0;
	int newdropchance = 0;
	int gtwl = 0;
	int u_gtwl = 0;
	int chance = 0;
	int max_gems2 = 0;
	int max_gems3 = 0;
	int clash_token = 0;
	int buy_price = 0;
	int scan_price = 0;
	int battle_cage = 0;
	string petName = "";
	string petPrefix = "";
	string petSuffix = "";
	string petAbility = "";
	string petDescription = "";
	uint8_t petElement = 0;
	uint8_t petCooldown = 0;
	uint8_t box_size = 0;
	vector<int> last20sales{};
	vector<int> commontrain_reward, raretrain_reward;
	vector<int> randomitem, epic, rare, uncommon, price;
	int block_flag = 0;
	bool musical_block = false;
	string texture_name = "";
	int texture_y = 0;
	short val2 = 0;
	short isRayman = 0;
	unsigned char maxAmount = 0;
	char editableType = 0;
	char hitSoundType = 0;
	int fossil_rock = 0;
	int fossil_rock2 = 0;
	int compress_item_return = 0;
	int compress_return_count = 0;
	vector<pair<int, int>> noob_item, rare_item;
	int fish_max_lb = 0;
	string hand_scythe_text = "";
	int consume_needed = 0;
	vector<int> consume_prize;
	string emoji = "";
	bool farmable = false;
	uint32_t playmod_id = 0;
	int val1 = 0;
	int textureHash = 0;
	char itemCategory = 0;
	char itemKind = 0;
	char textureX = 0;
	char textureY = 0;
	char spreadType = 0;
	char isStripeyWallpaper = 0;
	string texture = "";
	string extraOptions = "";
	string texture2 = "";
	string extraOptions2 = "";
	string punchOptions = "";
	char treeBase = 0;
	char treeLeaves = 0;
	char seedBase = 0;
	char seedOverlay = 0;
	int seedColor = 0;
	int seedOverlayColor = 0;
	int extraFileHash = 0;
	int dropChance = 0;
	int shop_X = 0, shop_Y = 0;
	bool mooncake = false;
	bool solid = 0;
	int effect = 0;
	int id = 0;
	bool untradeable = 0;
	int breakHits = 25;
	int actionType = 0;
	int chi = 4;
	int growTime = 0;
	int properties = 0;
	bool multiple_sides = 0;
	int base_weather = 0;
	bool audio_rack = false;
	bool simple_load = 0;
	bool can_be_changed_to_public = 0;
	bool toggleable = 0;
	bool wrench_by_public = false;
	int geiger_give_back = 0;
	int collisionType = 0;
	int clothingType = 0;
	int r_1 = 0, r_2 = 0, max_gems = 0;
	string on_equip = "", on_remove = "", playmod = "", playmod_total = "";
	string extraFile = "";
	string name = "", ori_name;
	string description = "This item has no description.";
	int16_t rarity = 0;
	ClothTypes clothType{};
	BlockTypes blockType{};
	bool path_marker = false;
};
vector<ItemDB> items;