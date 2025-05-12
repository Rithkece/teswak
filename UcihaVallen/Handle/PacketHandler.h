#pragma once
#ifdef _WIN32
#elif defined(__linux__)
#define BYTE unsigned char
#define DWORD unsigned int
#define __int64 int64_t
#define __int32 int32_t
#define __int16 int16_t
#define __int8 int8_t
#endif
#include <chrono>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
using namespace chrono;
const std::string COLOR_RESET = "\033[0m";
const std::string COLOR_BLACK = "\033[30m";
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_YELLOW = "\033[33m";
const std::string COLOR_BLUE = "\033[34m";
const std::string COLOR_MAGENTA = "\033[35m";
const std::string COLOR_CYAN = "\033[36m";
const std::string COLOR_WHITE = "\033[37m";
#pragma pack(push, 1)
typedef struct gametankpacket_t {
	int32_t m_type;
	char m_data;
} gametextpacket_t;
#pragma pack(pop)
enum {
	PACKET_STATE = 0,
	PACKET_CALL_FUNCTION,
	PACKET_UPDATE_STATUS,
	PACKET_TILE_CHANGE_REQUEST,
	PACKET_SEND_MAP_DATA,
	PACKET_SEND_TILE_UPDATE_DATA,
	PACKET_SEND_TILE_UPDATE_DATA_MULTIPLE,
	PACKET_TILE_ACTIVATE_REQUEST,
	PACKET_TILE_APPLY_DAMAGE,
	PACKET_SEND_INVENTORY_STATE,
	PACKET_ITEM_ACTIVATE_REQUEST,
	PACKET_ITEM_ACTIVATE_OBJECT_REQUEST,
	PACKET_SEND_TILE_TREE_STATE,
	PACKET_MODIFY_ITEM_INVENTORY,
	PACKET_ITEM_CHANGE_OBJECT,
	PACKET_SEND_LOCK,
	PACKET_SEND_ITEM_DATABASE_DATA,
	PACKET_SEND_PARTICLE_EFFECT,
	PACKET_SET_ICON_STATE,
	PACKET_ITEM_EFFECT,
	PACKET_SET_CHARACTER_STATE,
	PACKET_PING_REPLY,
	PACKET_PING_REQUEST,
	PACKET_GOT_PUNCHED,
	PACKET_APP_CHECK_RESPONSE,
	PACKET_APP_INTEGRITY_FAIL,
	PACKET_DISCONNECT,
	PACKET_BATTLE_JOIN,
	PACKET_BATTLE_EVENT,
	PACKET_USE_DOOR,
	PACKET_SEND_PARENTAL,
	PACKET_GONE_FISHIN,
	PACKET_STEAM,
	PACKET_PET_BATTLE,
	PACKET_NPC,
	PACKET_SPECIAL,
	PACKET_SEND_PARTICLE_EFFECT_V2,
	PACKET_ACTIVE_ARROW_TO_ITEM,
	PACKET_SELECT_TILE_INDEX,
	PACKET_SEND_PLAYER_TRIBUTE_DATA,
	PACKET_PVE_UNK1,
	PACKET_PVE_UNK2,
	PACKET_PVE_UNK3,
	PACKET_PVE_UNK4,
	PACKET_PVE_UNK5,
	PACKET_SET_EXTRA_MODS,
	PACKET_ON_STEP_ON_TILE_MOD,
	PACKET_MAXVAL,
	PACKET_PROXY_CHECK_RESPONSE = 76
};
enum { NET_MESSAGE_UNKNOWN = 0, NET_MESSAGE_SERVER_HELLO, NET_MESSAGE_GENERIC_TEXT, NET_MESSAGE_GAME_MESSAGE, NET_MESSAGE_GAME_PACKET, NET_MESSAGE_ERROR, NET_MESSAGE_TRACK, NET_MESSAGE_CLIENT_LOG_REQUEST, NET_MESSAGE_CLIENT_LOG_RESPONSE, };
enum packet_flags : uint32_t { PACKET_FLAGS_FLYING = 1 << 1, PACKET_FLAGS_UPDATE = 1 << 2, PACKET_FLAGS_EXTENDED = 1 << 3, PACKET_FLAGS_FACINGLEFT = 1 << 4, PACKET_FLAGS_ONGROUND = 1 << 5, PACKET_FLAGS_LAVA = 1 << 6, PACKET_FLAGS_JUMPSOUND = 1 << 7, PACKET_FLAGS_DEATH = 1 << 8, PACKET_FLAGS_PUNCH = 1 << 9, PACKET_FLAGS_PLACE = 1 << 10, PACKET_FLAGS_TILEACTION = 1 << 11, PACKET_FLAGS_KNOCKBACK = 1 << 12, PACKET_FLAGS_RESPAWN = 1 << 13, PACKET_FLAGS_PICKUPSOUND = 1 << 14, PACKET_FLAGS_TRAMPOLINE = 1 << 15, PACKET_FLAGS_CACTUS = 1 << 16, PACKET_FLAGS_SLIDING = 1 << 17, PACKET_FLAGS_JUMPPEAK = 1 << 18, PACKET_FLAGS_FALLING_SLOWLY = 1 << 19, PACKET_FLAGS_SWIM_SOUND = 1 << 20, PACKET_FLAGS_WALLHANG = 1 << 21, PACKET_FLAGS_RAYMAN_START = 1 << 22, PACKET_FLAGS_RAYMAN_END = 1 << 23, PACKET_FLAGS_RAYMAN_LOAD = 1 << 24, PACKET_FLAGS_FORCE_RING = 1 << 25, PACKET_FLAGS_CACTUS_RAPE = 1 << 26, PACKET_FLAGS_ACID = 1 << 28 };
#pragma pack(push, 1)
struct GameUpdatePacketSimple {
	uint32_t data_size;
	int32_t netid, item, flags;
	int32_t int_data, int_x, int_y;
	uint8_t type, objtype, count1, count2;
	float float1, vec_x, vec_y, vec2_x, vec2_y, float2;
};
#pragma once
#pragma pack(push, 1)
struct GameUpdatePacket {
	int type;
	int netID;
	int effectFlags;
	int objectType;
	int pingHash;
	int int_data;
	float vec_x;
	float vec_y;
	float vec2_x;
	float vec2_y;
	int particleEffect;
	int state1;
	int plantFlags;
	int tileX;
	int tileY;
	int tileFg;
	int tileBg;
	int audioId;
	int playerFlags;
	int packetFlags;
	unsigned char data[48]; // sisa payload
};
#pragma pack(pop)
struct gamepacket_t
{
private:
	int index = 0, len = 0;
	BYTE* packet_data = new BYTE[61];
public:
	gamepacket_t(int delay = 0, int NetID = -1) {
		len = 61;
		int MessageType = 0x4, PacketType = 0x1, CharState = 0x8;
		Memory_Set(packet_data, 0, 61);
		Memory_Copy(packet_data, &MessageType, 4);
		Memory_Copy(packet_data + 4, &PacketType, 4);
		Memory_Copy(packet_data + 8, &NetID, 4);
		Memory_Copy(packet_data + 16, &CharState, 4);
		Memory_Copy(packet_data + 24, &delay, 4);
	};
	~gamepacket_t() {
		delete[] packet_data;
	}
	void Insert(string a) {
		BYTE* data = new BYTE[len + 2 + a.length() + 4];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x2;
		int str_len = (int)a.length();
		Memory_Copy(data + len + 2, &str_len, 4);
		Memory_Copy(data + len + 6, a.data(), str_len);
		len = len + 2 + (int)a.length() + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(int a) {
		BYTE* data = new BYTE[len + 2 + 4];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x9;
		Memory_Copy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(unsigned int a) {
		BYTE* data = new BYTE[len + 2 + 4];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x5;
		Memory_Copy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a) {
		BYTE* data = new BYTE[len + 2 + 4];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x1;
		Memory_Copy(data + len + 2, &a, 4);
		len = len + 2 + 4;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a, float b) {
		BYTE* data = new BYTE[len + 2 + 8];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x3;
		Memory_Copy(data + len + 2, &a, 4);
		Memory_Copy(data + len + 6, &b, 4);
		len = len + 2 + 8;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void Insert(float a, float b, float c) {
		BYTE* data = new BYTE[len + 2 + 12];
		Memory_Copy(data, packet_data, len);
		delete[] packet_data;
		packet_data = data;
		data[len] = index;
		data[len + 1] = 0x4;
		Memory_Copy(data + len + 2, &a, 4);
		Memory_Copy(data + len + 6, &b, 4);
		Memory_Copy(data + len + 10, &c, 4);
		len = len + 2 + 12;
		index++;
		if (len > 60) {
			packet_data[60] = index;
		}
		else {
			std::cerr << "Error: packet_data does not have enough space for the 61st element." << std::endl;
		}
	}
	void CreatePacket(ENetPeer* peer) {
		ENetPacket* packet = enet_packet_create(packet_data, len, 1);
		enet_peer_send(peer, 0, packet);
	}
};
PlayerMoving* unpackPlayerMoving(BYTE* data) {
	PlayerMoving* dataStruct = new PlayerMoving;
	Memory_Copy(&dataStruct->packetType, data, 4);
	Memory_Copy(&dataStruct->netID, data + 4, 4);
	Memory_Copy(&dataStruct->characterState, data + 12, 4);
	Memory_Copy(&dataStruct->plantingTree, data + 20, 4);
	Memory_Copy(&dataStruct->x, data + 24, 4);
	Memory_Copy(&dataStruct->y, data + 28, 4);
	Memory_Copy(&dataStruct->XSpeed, data + 32, 4);
	Memory_Copy(&dataStruct->YSpeed, data + 36, 4);
	Memory_Copy(&dataStruct->punchX, data + 44, 4);
	Memory_Copy(&dataStruct->punchY, data + 48, 4);
	return dataStruct;
}
BYTE* GetStructPointerFromTankPacket(ENetPacket* packet) {
	const unsigned int packetLenght = (unsigned int)packet->dataLength;
	BYTE* result = NULL;
	if (packetLenght >= 0x3C) {
		BYTE* packetData = packet->data;
		result = packetData + 4;
		if (*static_cast<BYTE*>(packetData + 16) & 8) {
			if (packetLenght < *(int*)(packetData + 56) + 60) {
				cout << "[!] Packet too small for extended packet to be valid" << endl;
				cout << "[!] Sizeof float is 4.  TankUpdatePacket size: 56" << endl;
				result = 0;
			}
		}
		else {
			int zero = 0;
			Memory_Copy(packetData + 56, &zero, 4);
		}
	}
	return result;
}
std::string dialogrequest(ENetPeer* p) {
	pInfo(p)->isindialog = true;
	return "OnDialogRequest";
}
std::string SetColor(ENetPeer* peer) {
	if (pInfo(peer)->border_color == "Default" or pInfo(peer)->border_color.empty()) return "";
	else return "set_border_color|" + pInfo(peer)->border_color + "\nset_bg_color|" + pInfo(peer)->bg_color + "";
}
inline void SendParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay) {
	PlayerMoving datx{};
	datx.packetType = 0x11;
	datx.x = x;
	datx.y = y;
	datx.YSpeed = id;
	datx.XSpeed = size;
	datx.plantingTree = delay;
	BYTE* raw = packPlayerMoving(&datx);
	send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
	delete[]raw;
}
void Add_Piggy_Bank(ENetPeer* peer, int amount) {
	if (pInfo(peer)->pg_bank) {
		if (pInfo(peer)->Banked_Piggy < 350000) {
			pInfo(peer)->Banked_Piggy += amount;
			if (pInfo(peer)->Banked_Piggy >= 350000) pInfo(peer)->Banked_Piggy = 350000;
			gamepacket_t p;
			p.Insert("OnEventButtonDataSet");
			p.Insert("PiggyBankButton");
			p.Insert(1);
			p.Insert("{\"active\":true,\"buttonAction\":\"openPiggyBank\",\"buttonState\":" + a + (pInfo(peer)->Banked_Piggy > 350000 ? "2" : "0") + ",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"PiggyBankButton\",\"notification\":0,\"order\":2,\"rcssClass\":\"piggybank\",\"text\":\"" + (pInfo(peer)->Banked_Piggy > 350000 ? "350K" : ConvertToK(pInfo(peer)->Banked_Piggy) + "/350K") + "\"}");
			p.CreatePacket(peer);
		}
	}
}
bool complete_gpass_task(ENetPeer* peer, string task) {
	if (find(pInfo(peer)->growpass_quests.begin(), pInfo(peer)->growpass_quests.end(), task) == pInfo(peer)->growpass_quests.end()) {
		pInfo(peer)->growpass_quests.push_back(task);
		Add_Piggy_Bank(peer, 10000);
		int get_points = 10;
		if (task == "Growtoken") get_points = 40;
		else if (task == "Claim 4,000 gems") get_points = 150, pInfo(peer)->gems += 4000;
		else get_points = 10;
		if (pInfo(peer)->growpass_points < 5400) {
			string text = "`9Completed Grow Pass Task '" + task + "' and received " + to_string(get_points) + " points!``";
			if (not pInfo(peer)->world.empty()) {
				gamepacket_t p;
				p.Insert("OnTalkBubble"), p.Insert(pInfo(peer)->netID), p.Insert(text), p.Insert(0), p.Insert(0), p.CreatePacket(peer);
				PlayerMoving data_{};
				data_.packetType = 17, data_.netID = 198, data_.YSpeed = 198, data_.x = pInfo(peer)->x + 16, data_.y = pInfo(peer)->y + 16;
				BYTE* raw = packPlayerMoving(&data_);
				send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
				delete[] raw;
			}
			gamepacket_t p1;
			p1.Insert("OnConsoleMessage"), p1.Insert(text), p1.CreatePacket(peer);
			pInfo(peer)->growpass_points += get_points;
			return true;
		}
		else return false;
	}
	else return false;
}
class CAction {
public:
	static void Effect(ENetPeer* peer, int id, int x, int y, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnParticleEffect"), p.Insert(id), p.Insert(x, y), p.CreatePacket(peer);
	}
	static void Effect_V2(ENetPeer* peer, int id, int x, int y, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnParticleEffectV2"), p.Insert(id), p.Insert(x, y), p.CreatePacket(peer);
	}
	static void Positioned(ENetPeer* peer, int netID, string file, int delay = 0) {
		gamepacket_t p(delay, netID);
		p.Insert("OnPlayPositioned");
		p.Insert(file);
		p.CreatePacket(peer);
	}
	static void ScreenShotMode(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnPlayerScreenShotMode");
		p.CreatePacket(peer);
	}
	static void Log(ENetPeer* p_, string t_, string l_ = "", string w_ = "google.com") {
		if (l_ != "") t_ = "action|log\nmsg|" + t_;
		int y_ = 3;
		BYTE z_ = 0;
		BYTE* const d_ = new BYTE[5 + t_.length()];
		Memory_Copy(d_, &y_, 4);
		Memory_Copy(d_ + 4, t_.c_str(), t_.length());
		Memory_Copy(d_ + 4 + t_.length(), &z_, 1);
		ENetPacket* const p = enet_packet_create(d_, 5 + t_.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(p_, 0, p);
		delete[]d_;
		if (l_ != "") {
			l_ = "action|set_url\nurl|" + w_ + "\nlabel|" + l_ + "\n";
			BYTE* const u_ = new BYTE[5 + l_.length()];
			Memory_Copy(u_, &y_, 4);
			Memory_Copy(u_ + 4, l_.c_str(), l_.length());
			Memory_Copy(u_ + 4 + l_.length(), &z_, 1);
			ENetPacket* const p3 = enet_packet_create(u_, 5 + l_.length(), ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(p_, 0, p3);
			delete[]u_;
		}
	}
};
class Logger {
public:
	static void	Info(string type, string text) {
		struct tm newtime;
		time_t now = time(0);
#ifdef _WIN32
		localtime_s(&newtime, &now);
#elif defined(__linux__)
		localtime_r(&now, &newtime);
#endif
		if (type == "INFO") std::cout << COLOR_RESET << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] " << COLOR_GREEN << " [" + type + "]: " << COLOR_RESET << text << std::endl;
		if (type == "DEBUG") std::cout << COLOR_RESET << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] " << COLOR_BLUE << " [" + type + "]: " << COLOR_RESET << text << std::endl;
		if (type == "ERROR") std::cout << COLOR_RESET << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] " << COLOR_RED << " [" + type + "]: " << COLOR_RESET << text << std::endl;
		if (type == "WARNING") std::cout << COLOR_RESET << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] " << COLOR_YELLOW << " [" + type + "]: " << COLOR_RESET << text << std::endl;
		if (type == "CONSOLE") std::cout << COLOR_RESET << "[" << newtime.tm_hour << ":" << newtime.tm_min << "] " << COLOR_MAGENTA << " [" + type + "]: " << COLOR_RESET << text << std::endl;
	}
};

class VarList {
public:
	static void OnConsoleMessage(ENetPeer* peer, string text, bool all = false, int dly = 0) {
		gamepacket_t p(dly);
		p.Insert("OnConsoleMessage");
		p.Insert("`o" + text);
		if (!all) p.CreatePacket(peer);
		else {
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
				p.CreatePacket(currentPeer);
			}
		}
	}
	static void OnSuperMainStartAcceptLogon(ENetPeer* peer, string link, string path, string proto_) {
		gamepacket_t p;
		p.Insert("OnSuperMainStartAcceptLogonHrdxs47254722215a");
		p.Insert(Environment()->ItemsDat_Hash);
		p.Insert(link);
		p.Insert(path);
		p.Insert("cc.cz.madkite.freedom org.aqua.gg idv.aqua.bulldog com.cih.gamecih2 com.cih.gamecih com.cih.game_cih cn.maocai.gamekiller com.gmd.speedtime org.dax.attack com.x0.strai.frep com.x0.strai.free org.cheatengine.cegui org.sbtools.gamehack com.skgames.traffikrider org.sbtoods.gamehaca com.skype.ralder org.cheatengine.cegui.xx.multi1458919170111 com.prohiro.macro me.autotouch.autotouch com.cygery.repetitouch.free com.cygery.repetitouch.pro com.proziro.zacro com.slash.gamebuster");
		p.Insert("proto=" + proto_ + "|choosemusic=audio/ogg/theme_lobby.ogg|active_holiday=0|wing_week_day=0|ubi_week_day=0|server_tick=23802433|clash_active=1|drop_lavacheck_faster=1|isPayingUser=" + a + (pInfo(peer)->supp == 1 ? "1" : pInfo(peer)->supp == 2 ? "2" : "0") + "|usingStoreNavigation=1|enableInventoryTab=1|bigBackpack=1|m_clientBits=" + (Environment()->Enable_Joystick ? "3072" : "1024") + "|eventButtons={\"EventButtonData\":["
			"{\"active\":true,\"buttonAction\":\"dailychallengemenu\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":23,\"name\":\"DailyChallenge\",\"order\":0,\"rcssClass\":\"daily_challenge\",\"text\":\"\"},"
			"{\"active\":true,\"buttonAction\":\"openPiggyBank\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"PiggyBankButton\",\"order\":2,\"rcssClass\":\"piggybank\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"showdungeonsui\",\"buttonTemplate\":\"DungeonEventButton\",\"counter\":0,\"counterMax\":20,\"name\":\"ScrollsPurchaseButton\",\"order\":2,\"rcssClass\":\"scrollbank\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"winter_bingo_ui\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"BingoButton\",\"order\":2,\"rcssClass\":\"wf-bingo\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"winterrallymenu\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"WinterRallyButton\",\"order\":2,\"rcssClass\":\"winter-rally\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"leaderboardBtnClicked\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"AnniversaryLeaderboardButton\",\"order\":5,\"rcssClass\":\"anniversary-leaderboard\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"euphoriaBtnClicked\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"name\":\"AnniversaryEuphoriaButton\",\"order\":5,\"rcssClass\":\"anniversary-euphoria\",\"text\":\"\"},"
			"{\"active\":false,\"buttonAction\":\"openLnySparksPopup\",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":5,\"name\":\"LnyButton\",\"order\":5,\"rcssClass\":\"cny\",\"text\":\"\"}"
			"]}"
		);
		p.Insert("2436624451");
		p.CreatePacket(peer);
		pInfo(peer)->bypass = true;
	}
	static void OnEventButtonDataSet(ENetPeer* peer, string a, int c, string btn) {
		gamepacket_t p;
		p.Insert("OnEventButtonDataSet");
		p.Insert(a);
		p.Insert(c);
		p.Insert(btn);
		p.CreatePacket(peer);
	}
	static void OnBuxGems(ENetPeer* peer, int amount = 0, int delay = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p(delay);
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems += amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	static void OnMinGems(ENetPeer* peer, int amount = 0, int delay = 0) {
		if (pInfo(peer)->gp) {
			if (amount >= 30) {
				if (complete_gpass_task(peer, "Gems")) amount += 3;
			}
		}
		gamepacket_t p(delay);
		p.Insert("OnSetBux");
		p.Insert(pInfo(peer)->gems -= amount);
		p.Insert(0);
		p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
		if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
		p.CreatePacket(peer);
	}
	static void OnSetPos(ENetPeer* peer, int x, int y, int instant = 0, bool cooldown = false) {
		if (cooldown == false) pInfo(peer)->anticheat_cooldown = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		gamepacket_t p(instant, pInfo(peer)->netID);
		p.Insert("OnSetPos");
		p.Insert(float(x), float(y));
		p.CreatePacket(peer);
		pInfo(peer)->temp_x = x;
		pInfo(peer)->temp_y = y;
	}
	static void OnSetPos_2(ENetPeer* peer, const CL_Vec2f& pos, int netID) {
		gamepacket_t packet(0, netID);
		packet.Insert("OnSetPos");
		packet.Insert(pos.x, pos.y);
		packet.CreatePacket(peer);
	}
	static void OnSendToServer(ENetPeer* peer, int id, string name) {
		gamepacket_t p;
		p.Insert("OnSendToServer");
		p.Insert(17091);
		p.Insert("GrowPlus");
		p.Insert(id);
		p.Insert("www.gtps.pw|0|-1");
		p.Insert(1);
		p.Insert(name);
		p.CreatePacket(peer);
	}
	static void OnCountdownEnd(ENetPeer* peer, int netid) {
		gamepacket_t p(0, netid);
		p.Insert("OnCountdownEnd");
		p.CreatePacket(peer);
	}
	static void SetTapjoyTags(ENetPeer* peer, string a) {
		gamepacket_t p;
		p.Insert("SetTapjoyTags");
		p.Insert(a);
		p.CreatePacket(peer);
	}
	static void OnSetRoleSkinsAndIcons(ENetPeer* peer, int netid, int roleskin, int roleicon) {
		gamepacket_t p(0, netid);
		p.Insert("OnSetRoleSkinsAndIcons"), p.Insert(pInfo(peer)->roleSkin), p.Insert(pInfo(peer)->roleIcon), p.Insert(0);
		p.CreatePacket(peer);
	}
	static void ShowCurrency(ENetPeer* peer) {
		gamepacket_t pb;
		pb.Insert("ShowPearlCurrency");
		pb.CreatePacket(peer);
	}
	static void HideCurrency(ENetPeer* peer) {
		gamepacket_t pb;
		pb.Insert("HidePearlCurrency");
		pb.CreatePacket(peer);
	}
	static void SetCurrency(ENetPeer* peer, int amount = 0) {
		gamepacket_t pb2;
		pb2.Insert("OnSetPearl"), pb2.Insert(amount), pb2.Insert(0);
		pb2.CreatePacket(peer);
	}
	static void OnSetDungeonSouls(ENetPeer* peer, int amount = 0) {
		gamepacket_t pb2;
		pb2.Insert("OnSetDungeonSouls");
		pb2.Insert(amount);
		pb2.CreatePacket(peer);
	}
	static void OnSetVouchers(ENetPeer* peer, int amount = 0) {
		gamepacket_t p;
		p.Insert("OnSetVouchers");
		p.Insert(pInfo(peer)->voucher += amount);
		p.CreatePacket(peer);
	}
	static void CrashTheGameClient(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("CrashTheGameClient");
		p.CreatePacket(peer);
	}
	static void OnRequestWorldSelectMenu(ENetPeer* peer, string output) {
		gamepacket_t p;
		p.Insert("OnRequestWorldSelectMenu");
		p.Insert(output);
		p.CreatePacket(peer);
	}
	static void OnCommunityHubRequest(ENetPeer* peer, string CMNTY) {
		gamepacket_t p(500, -1);
		p.Insert("OnCommunityHubRequest");
		p.Insert(CMNTY);
		p.CreatePacket(peer);
	}
	static void OnSendLog(ENetPeer* enetPeer, string text, int type) {
		if (enetPeer) {
			ENetPacket* v3 = enet_packet_create(0, text.length() + 5, 1);
			Memory_Copy(v3->data, &type, 4);
			Memory_Copy((v3->data) + 4, text.c_str(), text.length());
			if (enet_peer_send(enetPeer, 0, v3) != 0) {
				enet_packet_destroy(v3);
			}
		}
	}
	static void OnAddNotification(ENetPeer* peer, string text, string interfaces, string audio, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnAddNotification");
		p.Insert(interfaces);
		p.Insert(text);
		p.Insert(audio);
		p.CreatePacket(peer);
	}
	static void OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor = 0, bool overlay = false, int delay = 0, bool overlay2 = false) {
		gamepacket_t p(delay);
		p.Insert("OnTalkBubble");
		p.Insert(netID);
		p.Insert(text);
		p.Insert(chatColor == 2 ? 2 : (overlay2 == true ? 1 : 0));
		p.Insert((overlay == true ? 1 : 0));
		p.CreatePacket(peer);
	}
	static void OnTextOverlay(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnTextOverlay");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	static void OnDialogRequest(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert(dialogrequest(peer).c_str());
		p.Insert(text);
		p.CreatePacket(peer);
	}
	static void OnDailyRewardRequest(ENetPeer* peer, string text, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnDailyRewardRequest");
		p.Insert(text);
		p.CreatePacket(peer);
	}
	static void OnStorePurchaseResult(ENetPeer* peer, string output) {
		gamepacket_t p;
		p.Insert("OnStorePurchaseResult");
		p.Insert(output);
		p.CreatePacket(peer);
	}
	static void SetHasAccountSecured(ENetPeer* peer, bool secured = false) {
		gamepacket_t p(0);
		p.Insert("SetHasAccountSecured");
		p.Insert(secured ? 1 : 0);
		p.CreatePacket(peer);
	}
	static void OnChangePureBeingMode(ENetPeer* peer, int netID, int mode) {
		gamepacket_t p(0, netID);
		p.Insert("OnChangePureBeingMode");
		p.Insert(mode);
		p.CreatePacket(peer);
	}
	static void OnAction(ENetPeer* peer, int netID, string action, int delay = 0) {
		gamepacket_t p(delay, netID);
		p.Insert("OnAction");
		p.Insert(action);
		p.CreatePacket(peer);
	}
	static void OnSetMissionTimer(ENetPeer* peer, int times_, int delay = 0) {
		gamepacket_t p3(delay);
		p3.Insert("OnSetMissionTimer"), p3.Insert(times_);
		p3.CreatePacket(peer);
	}
	static void OnSetCurrentWeather(ENetPeer* peer, int id) {
		gamepacket_t p;
		p.Insert("OnSetCurrentWeather");
		p.Insert(id);
		p.CreatePacket(peer);
	}
	static void OnPlaySound(ENetPeer* peer, string file, int delay = 0) {
		OnSendLog(peer, "action|play_sfx\nfile|" + file + "\ndelayMS|" + to_string(delay), 3);
	}
	static void OnParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay) {
		PlayerMoving datx{};
		datx.packetType = 0x11;
		datx.x = x;
		datx.y = y;
		datx.YSpeed = id;
		datx.XSpeed = size;
		datx.plantingTree = delay;
		BYTE* raw = packPlayerMoving(&datx);
		send_raw(peer, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
		delete[]raw;
	}
	static void OnSetPearl(ENetPeer* peer, int remove = 0) {
		gamepacket_t p;
		p.Insert("OnSetPearl"), p.Insert(pInfo(peer)->pearl += remove), p.Insert(0);
		p.CreatePacket(peer);
	}
	static void OnPlanterActivated(ENetPeer* p_, int id, int x_, int y_) {
		gamepacket_t p3;
		p3.Insert("OnPlanterActivated");
		p3.Insert(id);
		p3.Insert(x_);
		p3.Insert(y_);
		p3.CreatePacket(p_);
	}
	static void OnRemove(ENetPeer* peer, int netid, int pId, int delay = 0) {
		gamepacket_t p(delay);
		p.Insert("OnRemove"), p.Insert("netID|" + to_string(netid) + "\n"), p.Insert("pId|" + to_string(pId) + "\n"), p.CreatePacket(peer);
	}
	static void OnFailedToEnterWorld(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnFailedToEnterWorld"), p.CreatePacket(peer);
	}
	static void OnSetFreezeState(ENetPeer* peer, int netID, int delay, int num) {
		gamepacket_t p(delay, netID);
		p.Insert("OnSetFreezeState"), p.Insert(num), p.CreatePacket(peer);
	}
	static void OnZoomCamera(ENetPeer* peer, int delay) {
		gamepacket_t p(delay);
		p.Insert("OnZoomCamera"), p.Insert((float)10000.000000), p.Insert(1000), p.CreatePacket(peer);
	}
	static void OnKilled(ENetPeer* peer, int netID, int delay) {
		gamepacket_t p(delay, netID);
		p.Insert("OnKilled");
		p.CreatePacket(peer);
	}
	static void SetRespawnPos(ENetPeer* peer, int netID, int d, int delay) {
		gamepacket_t p(delay, netID);
		p.Insert("SetRespawnPos");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnPaw2018SkinColor1Changed(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnPaw2018SkinColor1Changed");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnPaw2018SkinColor2Changed(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnPaw2018SkinColor2Changed");
		p.Insert(d);
		p.CreatePacket(peer);
	}
	static void OnAchievementCompleted(ENetPeer* peer, int number) {
		gamepacket_t p;
		p.Insert("OnAchievementCompleted"), p.Insert(number), p.CreatePacket(peer);
	}
	static void OnPlayerLeveledUp(ENetPeer* peer, int number) {
		gamepacket_t p;
		p.Insert("OnPlayerLeveledUp"), p.Insert(number), p.CreatePacket(peer);
	}
	static void OnMagicCompassTrackingItemIDChanged(ENetPeer* peer, int d) {
		gamepacket_t p;
		p.Insert("OnMagicCompassTrackingItemIDChanged"), p.Insert(d), p.CreatePacket(peer);
	}
	static void UpdateMainMenuTheme(ENetPeer* peer, int d, int d1, int d2, string a) {
		gamepacket_t p;
		p.Insert("UpdateMainMenuTheme"), p.Insert(d), p.Insert(int(d1)), p.Insert(int(d2)), p.Insert(a), p.CreatePacket(peer);
	}
	static void SetHasGrowID(ENetPeer* peer, int d, string id, string pw) {
		gamepacket_t p;
		p.Insert("SetHasGrowID"), p.Insert(d), p.Insert(id), p.Insert(pw), p.CreatePacket(peer);
	}
	static void OnSetRoleSkinsAndTitles(ENetPeer* peer, string set_skins, string set_titles) {
		gamepacket_t p;
		p.Insert("OnSetRoleSkinsAndTitles");
		p.Insert(set_skins);
		p.Insert(set_titles);
		p.CreatePacket(peer);
	}
	static void OnProgressUISet(ENetPeer* peer, int id, int prog, int req) {
		gamepacket_t p;
		p.Insert("OnProgressUISet"), p.Insert(1), p.Insert(id), p.Insert(prog), p.Insert(req), p.Insert(""), p.Insert(1);
		p.CreatePacket(peer);
	}
	static void OnProgressUIUpdateValue(ENetPeer* peer, int id, int d) {
		gamepacket_t p;
		p.Insert("OnProgressUIUpdateValue"), p.Insert(id), p.Insert(d), p.CreatePacket(peer);
	}
	static void OnSpawn(ENetPeer* peer, string s) {
		gamepacket_t p;
		p.Insert("OnSpawn"), p.Insert(s), p.CreatePacket(peer);
	}
	static void OnEndMission(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnEndMission"), p.CreatePacket(peer);
	}
	static void OnSDBroadcast(ENetPeer* peer, string id, int d) {
		gamepacket_t p;
		p.Insert("OnSDBroadcast"), p.Insert(id), p.Insert(d), p.CreatePacket(peer);
	}
	static void OnForceTradeEnd(ENetPeer* peer) {
		gamepacket_t p;
		p.Insert("OnForceTradeEnd");
		p.CreatePacket(peer);
	}
	static void OnSendFavItemsList(ENetPeer* peer, std::string a, int aa) {
		gamepacket_t p;
		p.Insert("OnSendFavItemsList");
		p.Insert(a), p.Insert(aa);
		p.CreatePacket(peer);
	}
	static void OnFavItemUpdated(ENetPeer* peer, int a, int aa) {
		gamepacket_t p;
		p.Insert("OnFavItemUpdated");
		p.Insert(a), p.Insert(aa);
		p.CreatePacket(peer);
	}
	static void OnTradeStatus(ENetPeer* peer, int netid, string a, string aa, string aaa) {
		gamepacket_t p;
		p.Insert("OnTradeStatus");
		p.Insert(netid), p.Insert(a), p.Insert(aa), p.Insert(aaa);
		p.CreatePacket(peer);
	}
};
class SetEvent {
public:
	static void Gems(ENetPeer* peer, const string& error = "", const string& a = "", const string& aa = "") {
		VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wSet x Gems Event|left|14590|" + (error.empty() ? "" : "\nadd_spacer|small|\nadd_smalltext|`4" + error + "|left|") + "\nadd_spacer|small|\nadd_smalltext|`oX Gems (1-1000):|left|\nadd_text_input|count_x|`oCount:|" + a + "|5|\nadd_smalltext|`oTime: if you input 1 it is equal to 1 hours.|left|\nadd_text_input|time|`oTime:|" + aa + "|5|\nadd_spacer|small|\nend_dialog|Set_Gems_Event|Cancel|Update|");
	}
	static void Xp(ENetPeer* peer, const string& error = "", const string& a = "", const string& aa = "") {
		VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wSet x Xp Event|left|9590|" + (error.empty() ? "" : "\nadd_spacer|small|\nadd_smalltext|`4" + error + "|left|") + "\nadd_spacer|small|\nadd_smalltext|`oX Xp (1-1000):|left|\nadd_text_input|count_x|`oCount:|" + a + "|5|\nadd_smalltext|`oTime: if you input 1 it is equal to 1 hours.|left|\nadd_text_input|time|`oTime:|" + aa + "|5|\nadd_spacer|small|\nend_dialog|Set_Xp_Event|Cancel|Update|");
	}
	static void Exchange(ENetPeer* peer, const string& error = "", const string& a = "", const string& aa = "") {
		VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wSet x Exchange Event|left|9922|" + (error.empty() ? "" : "\nadd_spacer|small|\nadd_smalltext|`4" + error + "|left|") + "\nadd_spacer|small|\nadd_smalltext|`oX Xp (1-1000):|left|\nadd_text_input|count_x|`oCount:|" + a + "|5|\nadd_smalltext|`oTime: if you input 1 it is equal to 1 hours.|left|\nadd_text_input|time|`oTime:|" + aa + "|5|\nadd_spacer|small|\nend_dialog|Set_Exchange_Event|Cancel|Update|");
	}
};
int calcBanDuration(const long long banDuration) {
	auto duration = 0;
	duration = banDuration - GetCurrentTimeInternalSeconds();
	if (duration <= 0) return 0;
	else return duration;
}
inline int64_t currentTimestamp() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
double calculateDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
class PlayerDB {
public:
	static void RegisAndLogin_Page(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_image_button||interface/large/tianvan/page_banner.rttex|bannerlayout|||\nadd_smalltext|`oCreate your new GrowID, to playing on this `5Server ``by click this button|center|\nadd_custom_button|RegisterPage|image:interface/large/tianvan/gui_button_2.rttex;image_size:495,170;frame:0,1;width:0.3;|\nadd_custom_break|\nend_dialog|Login_Regis_Handle|||");
	}
	static void Aap_Page(ENetPeer* peer, const string& error = "") {
		VarList::OnDialogRequest(peer, "set_default_color|\nadd_label|big|`wAdvanced Account Protection|left|\nadd_smalltext|`4Advanced Account Protection: `oYou tried to log in from the new Device and IP`o, enter the pin that you created if you forgot your PIN, Please Report to the Developer or chat `2Dava `oon WhatsApp. And include proof that it is your account|left|" + (error.empty() ? "" : "\nadd_smalltext|`4OOPS:`` `o" + error + "``|") + "\nadd_text_input_password|verificationcode|`5Enter your Pin:``||4|\nadd_button|verify_2fa|`wSubmit|noflags|0|0|\nend_dialog|Login_Regis_Handle|||");
	}
	static string Regis_Dialog(const string& r_, const string& a_ = "", const string& b_ = "", const string& c_ = "", const string& d_ = "") {
		return "text_scaling_string|Dirttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt|\nset_default_color|`o\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\nadd_spacer|small|\nadd_textbox|" + (r_.empty() ? "By choosing a `wGrowID``, you can use a name and password to logon from any device.Your `wname`` will be shown to other players!" : r_) + "|left|\nadd_spacer|small|\nadd_text_input|username|Name|" + a_ + "|18|\nadd_textbox|Your `wpassword`` must contain `w8 to 18 characters, 1 letter, 1 number`` and `w1 special character: @#!$^&*.,``|left|\nadd_text_input_password|password|Password|" + b_ + "|18|\nadd_text_input_password|password_verify|Password Verify|" + c_ + "|18|\nadd_textbox|Your `wemail`` will only be used for account verification and support. If you enter a fake email, you can't verify your account, recover or change your password.|left|\nadd_text_input|email|Email|" + d_ + "|64|\nadd_textbox|We will never ask you for your password or email, never share it with anyone!|left|\nadd_button|back|Back|noflags|\nadd_custom_button|Get_GrowID|textLabel:`2Get My GrowID;anchor:_button_back;left:1;margin:40,0;|\nend_dialog|Login_Regis_Handle|||\n";
	}
};