/*GrowTopia Private Server v1.1 by Vallen / VallenBijuDama*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <algorithm>
#include <csignal>
#include <functional>
#include <unordered_set>
#include "enet/include/enet.h"
#include "include/read_item_packet_data.h"
#include "include/nlohmann/json.hpp"
#include "include/proton/rtparam.hpp"
#include "include/HTTPRequest.hpp"
#include "UcihaVallen/Handle/ItemDefination.h"
#include "UcihaVallen/Handle/BaseServer.h"
#include "UcihaVallen/Handle/PlayerInfo.h"
#include "UcihaVallen/Handle/PacketHandler.h"
#include "UcihaVallen/Handle/GuildInfo.h"
#include "UcihaVallen/Handle/WorldInfo.h"
#include "UcihaVallen/Handle/License.h"
#include "UcihaVallen/Handle/DialogReturn.h"
#include "UcihaVallen/Handle/LoginHandler.h"
#include "UcihaVallen/Handle/DiscordBot.h"
#include "UcihaVallen/Action/action.h"
#include "UcihaVallen/Dialog/dialog_return.h"
#include "UcihaVallen/Server/server_pool.h"
#include "UcihaVallen/Commands/Commands.h"

#pragma comment(lib, "Ws2_32.lib")
#ifdef _WINDOWS_
BOOL WINAPI ConsoleHandler(DWORD dwType) {
	switch (dwType) {
	case CTRL_LOGOFF_EVENT: case CTRL_SHUTDOWN_EVENT: case CTRL_CLOSE_EVENT: {
		ServerPool::Trigger();
		return TRUE;
	}
	default:
		break;
	}
	return FALSE;
}
#else
#define Sleep(x) sleep(x)
#include <signal.h>
void ConsoleHandler(int sig) {
	switch (sig) {
	case SIGINT: case SIGTERM: { ServerPool::Trigger(); break; }
	default: break;
	}
}
#endif
class Looping {
public:
	static void Events(ENetPeer* peer, bool forced = false) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->special_event == false && server_event_spawn + 300000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				int event_item = 0;
				if (rand() % 200 < 1 && world_->last_special_event + 900000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() or forced) {
					std::vector<int> list = { 263,942,942,1396,4774,4522, 4774, 5002, 121, 1636, 2798, 2704, 3786, 4354 , 4354, 2992, 2992, 10016, 10016, 1396 };
					world_->special_event_item = (WinterFest.Active ? 9186 : list[rand() % list.size()]);
					event_item = world_->special_event_item;
					world_->special_event = true;
					for (ENetPeer* cp__event = server->peers; cp__event < &server->peers[server->peerCount]; ++cp__event) {
						if (cp__event->state != ENET_PEER_STATE_CONNECTED or cp__event->data == NULL or pInfo(cp__event)->world != name_) continue;
						VarList::OnConsoleMessage(cp__event, "`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oYou have`` `030`` `oseconds to find and grab the`` `#" + items[world_->special_event_item].name + "```o.``" : "`#" + to_string(items[world_->special_event_item].event_total) + " " + items[world_->special_event_item].name + "`` `ospawn in your world, you have`` `030`` `oseconds to collect them.``") + "");
						VarList::OnAddNotification(cp__event, "`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oYou have`` `030`` `oseconds to find and grab the`` `#" + items[world_->special_event_item].name + "```o.``" : "`#" + to_string(items[world_->special_event_item].event_total) + " " + items[world_->special_event_item].name + "`` `ospawn in your world, you have`` `030`` `oseconds to collect them.``") + "", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
					}
					world_->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				else if (Event()->Zombie_Apocalypse && rand() % 3 < 1 && world_->last_special_event + 180000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != name_) continue;
						VarList::OnSetCurrentWeather(cp_, 31);
						VarList::OnConsoleMessage(cp_, "`2Zombie Apocalypse:`` `oIt's the Return of the Growing Dead!``");
						VarList::OnAddNotification(cp_, "`2Zombie Apocalypse:`` `oIt's the Return of the Growing Dead!``", "interface/large/special_event.rttex", "audio/owooooo.wav");
						if (not Playmods::HasById(pInfo(cp_), 28)) {
							if (rand() % 2 < 1) {
								Playmods::Add(cp_, 28);
								Clothing_V2::Update(cp_, true);
								Clothing_V2::Update_Value(cp_);
							}
						}
					}
					world_->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				else if (Event()->Comet_Dust && rand() % 3 < 1 && world_->last_comet_spawn + 180000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
					event_item = 2034;
					world_->last_comet_spawn = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				else if (WinterFest.Active and WinterFest.Goblin_Spawn + 500000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
					int sentto = 0;
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != name_ or not pInfo(cp_)->Silver_Donatur or pInfo(cp_)->Already_Tried_Gob) continue;
						if (sentto > 5) continue;
						sentto++;
						VarList::OnDialogRequest(cp_, "set_default_color|`o\nadd_label_with_icon|big|`9Stuff-4-Toys Volunteer Drive|left|4264|\nadd_spacer|small|\nadd_textbox|`9Stuff-4-Toys`` is looking for volunteers! Are you willing to hand out some toys right now, dressed in our `2Present Goblin Disguise``?|left|\nadd_smalltext|- It will only take about 30 seconds at your time!|left|\nadd_smalltext|- You won't be able to pick up items while in disguise.|left|\nadd_smalltext|- You will be teleported to the white door, and your Checkpoint will be reset.|left|\nadd_smalltext|- You'll be bringin joy to " + Environment()->server_name + "!|left|\nadd_smalltext|- `4You only have 30 seconds to respond this message!|left|\nend_dialog|Goblin_Disguise|I hate joy|I am happy to help!|");
					}
					WinterFest.Goblin_Spawn = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				if (event_item != 0) {
					if (find(Environment()->Another_Worlds.begin(), Environment()->Another_Worlds.end(), world_->name) == Environment()->Another_Worlds.end()) Environment()->Another_Worlds.emplace_back(world_->name);
					server_event_spawn = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					WorldDrop drop_block_{};
					drop_block_.count = 1;
					for (int i_ = 0; i_ < items[event_item].event_total; i_++) {
						drop_block_.id = event_item == 2034 ? (rand() % 100 < 25 ? 2036 : 2034) : world_->special_event_item, drop_block_.x = rand() % 99 * 32, drop_block_.y = rand() % 54 * 32;
						world_->world_event_items.emplace_back(drop_block_.id);
						VisualHandle::Drop(world_, drop_block_, true);
					}
				}
			}
		}
	}
	static void Worlds() {
		if (Environment()->Auto_Saving == false) {
			long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			if (Environment()->Last_Time2_ - ms_time <= 0 && Environment()->Restart_Status) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					VarList::OnConsoleMessage(cp_, "`4Global System Message``: Restarting server for update in `4" + to_string(Environment()->Restart_Time) + "`` minutes");
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/ogg/suspended.ogg", 700);
				}
				Environment()->Restart_Time -= 1;
				if (Environment()->Restart_Time == 0) {
					Environment()->Last_Time2_ = ms_time + 10000, Environment()->Restart_Status_Seconds = true, Environment()->Restart_Status = false;
					Environment()->Restart_Time = 50;
				}
				else Environment()->Last_Time2_ = ms_time + 60000;
			}
			if (Environment()->Restart_Status_Seconds && Environment()->Last_Time2_ - ms_time <= 0) {
				bool save_ = false, send_now = false;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					VarList::OnConsoleMessage(cp_, "`4Global System Message``: Restarting server for update in `4" + (Environment()->Restart_Time > 0 ? to_string(Environment()->Restart_Time) : "ZERO") + "`` seconds" + (Environment()->Restart_Time > 0 ? "" : "! Should be back up in a minute or so. BYE!") + "");
					send_now = true;
				}
				if (Environment()->Restart_Time > 0) save_ = false;
				else save_ = true;
				Environment()->Last_Time2_ = ms_time + 10000;
				if (save_ && send_now) {
					Environment()->Restart_Status_Seconds = false;
					Environment()->Maintenance = true;
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
						Peer_Disconnect(cp_, 0);
					}
				}
				else Environment()->Restart_Time -= 10;
			}
			if (Environment()->Last_Time - ms_time <= 0) {
				if (Environment()->Last_Checkip - ms_time <= 0) {
					Environment()->Last_Checkip = ms_time + 900000;
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world.empty()) continue;
						char ClientConnection[16];
						enet_address_get_host_ip(&cp_->address, ClientConnection, 16);
						std::string str(ClientConnection, ClientConnection + 16);
						if (pInfo(cp_)->ip != ClientConnection) pInfo(cp_)->ip = str, pInfo(cp_)->fa_ip = str;
					}
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (!special_char(pInfo(cp_)->world) and pInfo(cp_)->world != "" and pInfo(cp_)->world != "EXIT" and pInfo(cp_)->world.find("GROWMINES_") == string::npos) {
						std::vector<std::pair<int, std::string>>::iterator p = find_if(Environment()->Active_Worlds.begin(), Environment()->Active_Worlds.end(), [&](const pair < int, string>& element) { return element.second == pInfo(cp_)->world; });
						if (p != Environment()->Active_Worlds.end()) Environment()->Active_Worlds[p - Environment()->Active_Worlds.begin()].first++;
						else Environment()->Active_Worlds.emplace_back(1, pInfo(cp_)->world);
					}
					if (pInfo(cp_)->world != "") PlayerCharacter::Reset(cp_);
					if (Event()->x_gems_time - time(nullptr) <= 0 and Event()->Gems_Event) {
						Event()->Gems_Event = false;
						VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `o**`` `4Global System Message:`` `$Gems event has ended``");
						VarList::OnAddNotification(cp_, "`9Gems Event has ended`w!", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
					}
					if (Event()->x_xp_time - time(nullptr) <= 0 and Event()->Xp_Event) {
						Event()->Xp_Event = false;
						VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `o**`` `4Global System Message:`` `$Xp event has ended``");
						VarList::OnAddNotification(cp_, "`9Xp Event has ended`w!", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
					}
					if (Event()->x_exchange_time - time(nullptr) <= 0 and Event()->Exchange_Event) {
						Event()->Exchange_Event = false;
						VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `o**`` `4Global System Message:`` `$Exchange event has ended``");
						VarList::OnAddNotification(cp_, "`9Xp Event has ended`w!", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
					}
				}
				if (Honors_Update.last_honors_reset - ms_time <= 0) {
					std::vector<int> added;
					Environment()->janeway_item.clear();
					Environment()->janeway_payout = Environment()->random_janeway_payout[rand() % Environment()->random_janeway_payout.size()];
					for (int i = 0; i < 5; i++) {
						int random_item = rand() % Environment()->janeway_items.size();
						if (find(added.begin(), added.end(), Environment()->janeway_items[random_item].first) == added.end()) {
							added.push_back(Environment()->janeway_items[random_item].first);
							Environment()->janeway_item.push_back(std::make_pair(Environment()->janeway_items[random_item].first, Environment()->janeway_items[random_item].second));
							Environment()->janeway_item.push_back(std::make_pair(Environment()->janeway_items[random_item].first + 1, Environment()->janeway_items[random_item].second * 4));
						}
					}
					time_t currentTime;
					time(&currentTime);
					const auto localTime = localtime(&currentTime);
					const auto Hour = localTime->tm_hour; const auto Min = localTime->tm_min; const auto Sec = localTime->tm_sec; const auto Year = localTime->tm_year + 1900; const auto Day = localTime->tm_mday; const auto Month = localTime->tm_mon + 1;
					if (Hour >= 6 and Hour < 15) DaylightDragon.param1 = 0, DaylightDragon.param2 = 0, DaylightDragon.param3 = 1, DaylightDragon.param4 = 5, DaylightDragon.param5 = 0, DaylightDragon.param6 = 2;
					if (Hour >= 15 and Hour < 18) DaylightDragon.param1 = 1, DaylightDragon.param2 = 0, DaylightDragon.param3 = 1, DaylightDragon.param4 = 5, DaylightDragon.param5 = 0, DaylightDragon.param6 = 0;
					if (Hour >= 18 and Hour <= 0 or Hour > 0 and Hour < 6) DaylightDragon.param1 = 2, DaylightDragon.param2 = 0, DaylightDragon.param3 = 1, DaylightDragon.param4 = 5, DaylightDragon.param5 = 0, DaylightDragon.param6 = 1;
					ServerPool::Honors::Reset();
					Honors_Update.last_honors_reset = ms_time + 7200000;
				}
				struct tm newtime;
				time_t now = time(0);
#ifdef _WIN32
				localtime_s(&newtime, &now);
#elif defined(__linux__)
				localtime_r(&now, &newtime);
#endif
				if (today_day != newtime.tm_mday) {
					today_day = newtime.tm_mday;
					std::vector<int8_t> random_xy{ -1, 0 };
					Environment()->Dq_Item1 = Environment()->small_seeds[rand() % Environment()->small_seeds.size()] + random_xy[rand() % random_xy.size()];
					Environment()->Dq_Item2 = Environment()->small_seed_pack[rand() % Environment()->small_seed_pack.size()] + random_xy[rand() % random_xy.size()];
					Environment()->Dq_Count1 = rand() % 200 + 1;
					Environment()->Dq_Count2 = rand() % 100 + 1;
					Environment()->Dq_Day = today_day;
					int Random = rand() % 43 + 1;
					Environment()->Ancient_Riddle.clear();
					if (Random == 1) Environment()->Ancient_Riddle.emplace_back(982, "I see you wish to acquire greatness. I'd never block your efforts.");
					else if (Random == 2) Environment()->Ancient_Riddle.emplace_back(598, "This is a part of a fantasy, but I wouldn't want to be around it when it comes to a close.");
					else if (Random == 3) Environment()->Ancient_Riddle.emplace_back(320, "1812 is over, sure, but there's a way to bring it back. I can go on, but you should know how by now.");
					else if (Random == 4) Environment()->Ancient_Riddle.emplace_back(756, "Bring me a bandit. I don't even need all of him.");
					else if (Random == 5) Environment()->Ancient_Riddle.emplace_back(824, "I could never tell you what I want, because I'm not a fan of spoilers, and I'd prefer to keep things cool.");
					else if (Random == 6) Environment()->Ancient_Riddle.emplace_back(456, "My paradise is lost, but perhaps you can bring me halfway there.");
					else if (Random == 7) Environment()->Ancient_Riddle.emplace_back(480, "If you're a record breaker, stay away from this.");
					else if (Random == 8) Environment()->Ancient_Riddle.emplace_back(784, "I'd like a huckleberry. Know where I can find one?");
					else if (Random == 9) Environment()->Ancient_Riddle.emplace_back(658, "If you shoot this, would it be redundant? At the very least, I'll know you're bored.");
					else if (Random == 10) Environment()->Ancient_Riddle.emplace_back(1430, "Everyone asks the gods for these. Just once, I'd like to get one.");
					else if (Random == 11) Environment()->Ancient_Riddle.emplace_back(114, "You can silence this, but it will never die.");
					else if (Random == 12) Environment()->Ancient_Riddle.emplace_back(596, "A store full of wonders, none of which are for sale, is exactly the mark I'd like to spot.");
					else if (Random == 13) Environment()->Ancient_Riddle.emplace_back(286, "I'd like to remove some underlings from my employ. Give me a place to put them.");
					else if (Random == 14) Environment()->Ancient_Riddle.emplace_back(1048, "Spark my memories of the open range.");
					else if (Random == 15) Environment()->Ancient_Riddle.emplace_back(992, "I'd like a bright idea, but remember that I'm a city girl at heart.");
					else if (Random == 16) Environment()->Ancient_Riddle.emplace_back(1046, "I'm undecided, but I think the cowboy life calls to me on this one.");
					else if (Random == 17) Environment()->Ancient_Riddle.emplace_back(220, "Block out a little time to tune this the right way and that's what you'll have.");
					else if (Random == 18) Environment()->Ancient_Riddle.emplace_back(64, "If you ever had to use the bathroom in a dungeon, theres a chance you will put this together.");
					else if (Random == 19) Environment()->Ancient_Riddle.emplace_back(666, "Don't make an assumption, presume, or suppose - just take this for what it is and igneore the distractions.");
					else if (Random == 20) Environment()->Ancient_Riddle.emplace_back(684, "There aren't any drinks to be found here, but if they were, they'd be good for your blood.");
					else if (Random == 21) Environment()->Ancient_Riddle.emplace_back(872, "A creature of roads and rubber. It is dangerous to go alone, but even moreso, where beasts such as this are concerned.");
					else if (Random == 22) Environment()->Ancient_Riddle.emplace_back(866, "Time to get low. Perhaps this choice will cheese you off, but I suggest you move along.");
					else if (Random == 23) Environment()->Ancient_Riddle.emplace_back(1044, "It's worth more than a nickel, has nothing to do with chickens, and up to eight of them are correct, which I find baffling.");
					else if (Random == 24) Environment()->Ancient_Riddle.emplace_back(786, "Sorry, I can't quite racal what I wanted for this one. Call it a sign of the times.");
					else if (Random == 25) Environment()->Ancient_Riddle.emplace_back(1420, "Don't blink.");
					else if (Random == 26) Environment()->Ancient_Riddle.emplace_back(970, "Ag! You woke me up. I dreamt of when I was a smaller, simpler goddess. Perhaps you could remind me of that time?");
					else if (Random == 27) Environment()->Ancient_Riddle.emplace_back(260, "Find me a shimmering thing of wonder - I don't care what, so long as it's ausome!");
					else if (Random == 28) Environment()->Ancient_Riddle.emplace_back(186, "Bessie's a good name for a cow. Put it together with the sea France, and you have the first step in getting me what I want...");
					else if (Random == 29) Environment()->Ancient_Riddle.emplace_back(780, "2623, you'll know what to do. But there are alternates.");
					else if (Random == 30) Environment()->Ancient_Riddle.emplace_back(298, "Actually, I can't think of anything. Therefore, the opposite must do.");
					else if (Random == 31) Environment()->Ancient_Riddle.emplace_back(926, "Steel yourself, for I grow weary (or is it hungry?) and must set this discussion aside.");
					else if (Random == 32) Environment()->Ancient_Riddle.emplace_back(688, "These are spooky. I know everybody has one, but getting it to me is the key.");
					else if (Random == 33) Environment()->Ancient_Riddle.emplace_back(1002, "Hercules never defeated one of these, though, flames are still involved.");
					else if (Random == 34) Environment()->Ancient_Riddle.emplace_back(1530, "Whenever I sea these, I remember to keep quiet.");
					else if (Random == 35) Environment()->Ancient_Riddle.emplace_back(194, "Get me my favorite topping, and remember - I'm a fun girl.");
					else if (Random == 36) Environment()->Ancient_Riddle.emplace_back(334, "What's your favorite color? I can't decide between pink and yellow, so you'll have to bring me both.");
					else if (Random == 37) Environment()->Ancient_Riddle.emplace_back(1896, "I have trouble remembering things, so get me something that never forgets.");
					else if (Random == 38) Environment()->Ancient_Riddle.emplace_back(436, "Get me something to paint-and don't bangle it up.");
					else if (Random == 39) Environment()->Ancient_Riddle.emplace_back(454, "I want something strange, deadly, and otherworldly - but nothing from Mercury, please.");
					else if (Random == 40) Environment()->Ancient_Riddle.emplace_back(988, "Take one down from its perch and bring it here - just make sure you don't sluice it!");
					else if (Random == 41) Environment()->Ancient_Riddle.emplace_back(1312, "What do Vikings, Lumberjacks and Shrubbery have in common?");
					else if (Random == 42) Environment()->Ancient_Riddle.emplace_back(382, "I hate to break it to you, but it's time to give me some space.");
					else if (Random == 43) Environment()->Ancient_Riddle.emplace_back(922, "Most of the things I want are a mystery, but this one is especially so.");
					else if (Random == 44) Environment()->Ancient_Riddle.emplace_back(664, "I had a plan to get something tasty, but it's full of holes..");
					json j;
					j["Dq_Item1"] = Environment()->Dq_Item1;
					j["Dq_Item2"] = Environment()->Dq_Item2;
					j["Dq_Count1"] = Environment()->Dq_Count1;
					j["Dq_Count2"] = Environment()->Dq_Count2;
					j["Dq_Day"] = Environment()->Dq_Day;
					for (const auto& riddle : Environment()->Ancient_Riddle) {
						j["Ancient_Riddle"].push_back({ riddle.first, riddle.second });
					}
					std::ofstream o("database/json/daily_reset.json");
					if (!o.is_open()) {
						throw runtime_error("Failed to open daily_reset.json for writing: " + string(strerror(errno)));
					}
					o << j.dump(4) << endl;
					o.close();
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
						pInfo(cp_)->dd = 0, pInfo(cp_)->dq_day = newtime.tm_mday;
						CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/cash_register.wav", 0);
						VarList::OnConsoleMessage(cp_, "`2*** The Daily Quest Update``: requires `$" + to_string(Environment()->Dq_Count1) + " " + items[Environment()->Dq_Item1].name + "`` and `$" + to_string(Environment()->Dq_Count2) + " " + items[Environment()->Dq_Item2].name + "``. Go tell the `5Crazy Jim``!");
					}
				}
				if (Event()->daily_current_time - time(nullptr) <= 0 and Event()->DailyChallenge == true) {
					EventPool::DailyChallenge::Wait();
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
						VarList::OnConsoleMessage(cp_, "`2Daily Challenge: `oTime is Up! Figuring out the winners....");
						if (Event()->top_dailyc.size() != 0) VarList::OnConsoleMessage(cp_, "`9Today's winners:", 2000);
						std::vector<std::pair<long long int, std::string>> top_tiers = Event()->top_dailyc;
						sort(top_tiers.begin(), top_tiers.end());
						reverse(top_tiers.begin(), top_tiers.end());
						top_tiers.resize((top_tiers.size() >= 10 ? 10 : top_tiers.size()));
						for (std::uint8_t i = 0; i < top_tiers.size(); i++) {
							if (i < 5) VarList::OnConsoleMessage(cp_, "`w#" + to_string(i + 1) + ". `1" + top_tiers[i].second + " ``with " + Set_Count(top_tiers[i].first) + " Points", 2000);
						}
						if (pInfo(cp_)->world != "") Daily_Challenge::DailyChallengeRequest(cp_);
						VarList::OnConsoleMessage(cp_, "`9Join us in " + Time::Playmod(Event()->daily_wait_time - time(nullptr)) + " for another shot at the prize!", 2500);
					}
				}
				if (Event()->daily_wait_time - time(nullptr) <= 0 and not Event()->DailyChallenge) {
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
						if (pInfo(cp_)->world != "") Daily_Challenge::DailyChallengeRequest(cp_);
					}
					EventPool::DailyChallenge::Start();
				}
				if (current_event - time(nullptr) <= 0 and not Event()->Can_Event) EventPool::Guilds::Reset();
				if (wait_event - time(nullptr) <= 0 and Event()->Can_Event and not Event()->Wait_Next) EventPool::Guilds::Next();
				if (next_event - time(nullptr) <= 0 and Event()->Can_Event and Event()->Wait_Next) EventPool::Guilds::Start();
				if (Environment()->Worlds_Refresh - ms_time <= 0) {
					Environment()->Active_World_List.clear();
					Environment()->Active_World_List = "";
					for (std::uint8_t i = 0; i < Environment()->Active_Worlds.size(); i++) {
						std::uint8_t w_cz = 0;
						for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
							if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != Environment()->Active_Worlds[i].second) continue;
							w_cz++;
						}
						Environment()->Active_World_List += "\nadd_floater|" + Environment()->Active_Worlds[i].second + "|" + to_string(w_cz) + "|0.4" + (i == 0 ? "5" : "2") + "|3529161471";
					}
					if (Environment()->Active_World_List.empty()) {
						std::vector<std::string> active_worlds;
						for (std::uint8_t i = 0; i < worlds.size(); i++) {
							World world_ = worlds[rand() % worlds.size()];
							if (world_.name.find("_")) continue;
							if (find(active_worlds.begin(), active_worlds.end(), world_.name) == active_worlds.end()) {
								Environment()->Active_World_List += "\nadd_floater|" + world_.name + "|0|0.42|3529161471";
								active_worlds.emplace_back(world_.name);
							}
						}
					}
					if (Environment()->Active_World_List.empty()) Environment()->Active_World_List = "\nadd_floater|START|0|0.5|3529161471";
					Environment()->Active_Worlds.clear();
					Environment()->Worlds_Refresh = ms_time + 5000;
				}
			}
			if (Environment()->Last_Math - ms_time <= 0 and not Event()->DailyMaths) {
				if (Environment()->Last_Math - ms_time <= 0) Environment()->Last_Math = ms_time + 30000000;
				int number1 = rand() % 992 + 1, number2 = rand() % 892 + 1;
				Event()->Math_Num1 = rand() % number1 + number2;
				srand(time(0));
				Event()->Math_Num2 = rand() % number1 + number2 + 22;
				Event()->Math_Result = Event()->Math_Num1 + Event()->Math_Num2;
				Event()->Math_Prize = (rand() % 42220 + 1) + (rand() % 65300 + 1);
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL || pInfo(cp_)->world.empty()) continue;
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/startopia_tool_droid.wav", 0);
					VarList::OnConsoleMessage(cp_, "`9** " + Environment()->server_name + " Daily Math [Questions : `3'" + to_string(Event()->Math_Num1) + " + " + to_string(Event()->Math_Num2) + "'`9 = ?] Prize: `2" + to_string(Event()->Math_Prize) + "`9 (gems) ! `o(/a <answer>).");
					Event()->DailyMaths = true;
				}
			}
			if (Environment()->Last_Update - ms_time <= 0) {
				Environment()->Last_Update = ms_time + 1000;
				for (int i = 0; i < worlds.size(); i++) {
					World* world_ = &worlds[i];
					int blockCount = world_->blocks.size();
					if (blockCount == 0) continue;
					int ySize = blockCount / 100;
					if (ySize == 0) ySize = 1;
					int xSize = blockCount / ySize;
					for (int f = 0; f < blockCount; f++) {
						int x = f % xSize, y = f / xSize;
						WorldBlock* block_ = &world_->blocks[f];
						if (block_ != NULL) {
							for (auto it = block_->Admin_Bfg.begin(); it != block_->Admin_Bfg.end(); ) {
								if (it->first - time(nullptr) <= 0 || it->first < 0) {
									std::string find_ = it->second;
									auto it_ = std::find_if(block_->Admin_Bfg.begin(), block_->Admin_Bfg.end(), [find_](const auto& element) {
										return element.second == find_;
										});
									if (it_ != block_->Admin_Bfg.end()) {
										block_->Admin_Bfg.erase(it_);
									}
									bool has_ = false;
									for (ENetPeer* cp = server->peers; cp < &server->peers[server->peerCount]; ++cp) {
										if (cp->state != ENET_PEER_STATE_CONNECTED or cp->data == NULL) continue;
										if (to_lower(pInfo(cp)->tankIDName) == to_lower(find_)) {
											has_ = true;
											pInfo(cp)->Used_VipDoor.clear();
											if (pInfo(cp)->world == world_->name) {
												Player_Respawn(cp, true, 0, 1);
												PlayerMoving data_{};
												data_.packetType = 5, data_.punchX = x, data_.punchY = y, data_.characterState = 0x8;
												BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world_, block_));
												BYTE* blc = raw + 56;
												form_visual(blc, *block_, *world_, cp, false);
												send_raw(cp, 4, raw, 112 + alloc_(world_, block_), ENET_PACKET_FLAG_RELIABLE);
											}
											CAction::Positioned(cp, pInfo(cp)->netID, "audio/dialog_cancel.wav", 0);
											VarList::OnTalkBubble(cp, pInfo(cp)->netID, "System has `4removed`` you from a Pay VIP List.", 0, 1);
										}
										if (pInfo(cp)->world == world_->name) {
											VarList::OnConsoleMessage(cp, "`o[`4TIME-EXPIRED``] " + find_ + " was removed from a Pay VIP List.");
										}
									}
									if (not has_) {
										try {
											const std::string filePath = "database/players/" + find_ + "_.json";
											if (filesystem::exists(filePath)) {
												std::ifstream inputFile(filePath);
												json jsonData;
												inputFile >> jsonData;
												jsonData["Used_VipDoor"] = json::array();
												inputFile.close();
												std::ofstream outputFile(filePath);
												outputFile << jsonData << endl;
												outputFile.close();
											}
										}
										catch (exception) {
											return;
										}
									}
								}
								else {
									++it;
								}
							}
						}
					}
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL or pInfo(cp_)->tankIDName.empty() or pInfo(cp_)->world.empty()) continue;
					std::string name_ = pInfo(cp_)->world;
					auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (it != worlds.end()) {
						World* world = &(*it);
						if (world->name == "GROWCH" and WinterFest.Active) {
							if (WinterFest.Growch_Happy_Time - time(nullptr) <= 0 and WinterFest.GiftedGrowch != 0 and WinterFest.Growch_Happy) {
								world->weather = 12;
								WinterFest.Growch_Happy = false;
								WinterFest.Growch_Happy_Time = time(nullptr) + (300 * 60);
								for (ENetPeer* cp_2 = server->peers; cp_2 < &server->peers[server->peerCount]; ++cp_2) {
									if (cp_2->state != ENET_PEER_STATE_CONNECTED or cp_2->data == NULL) continue;
									VarList::OnConsoleMessage(cp_2, "`oThe Growch is angry again, making he happy again!");
									if (pInfo(cp_2)->world == "GROWCH") {
										VarList::OnSetCurrentWeather(cp_2, world->weather);
									}
								}
							}
						}
						world->fresh_world = true;
						std::vector<WorldBlock>::iterator p2 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == 5958; });
						if (p2 != world->blocks.end()) {
							int x_ = int(p2 - world->blocks.begin()) % 100, y_ = int(p2 - world->blocks.begin()) / 100;
							if (world->blocks[x_ + (y_ * 100)].flags & 0x00400000) {// EPOCH 
								long long current_time = time(nullptr);
								if (world->blocks[x_ + (y_ * 100)].epoch_cycle - current_time <= 1) {
									if (world->weather == 38) world->weather = (world->blocks[x_ + (y_ * 100)].epoch_state.first[1] == true ? 39 : world->blocks[x_ + (y_ * 100)].epoch_state.first[2] == true ? 40 : 38);
									else if (world->weather == 39) world->weather = (world->blocks[x_ + (y_ * 100)].epoch_state.first[2] == true ? 40 : world->blocks[x_ + (y_ * 100)].epoch_state.first[0] == true ? 38 : 39);
									else if (world->weather == 40) world->weather = (world->blocks[x_ + (y_ * 100)].epoch_state.first[0] == true ? 38 : world->blocks[x_ + (y_ * 100)].epoch_state.first[1] == true ? 38 : 40);
									world->blocks[x_ + (y_ * 100)].epoch_cycle = current_time + (world->blocks[x_ + (y_ * 100)].epoch_state.second * 60);
									if (pInfo(cp_)->world == world->name) {
										VarList::OnSetCurrentWeather(cp_, (Event()->Comet_Dust ? 16 : world->weather == 0 ? 80 : world->weather));
									}
								}
							}
						}
						std::vector<WorldBlock>::iterator p3 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == 10058; });
						if (p3 != world->blocks.end()) {
							int x_ = int(p3 - world->blocks.begin()) % 100, y_ = int(p3 - world->blocks.begin()) / 100;
							if (world->blocks[x_ + (y_ * 100)].flags & 0x00400000 && world->infinity.size() != 0) {// INFINITY
								long long current_time = time(nullptr);
								if (world->blocks[x_ + (y_ * 100)].epoch_cycle - current_time <= 1) {
									if (world->cycle_ke >= world->infinity.size() || world->cycle_ke < 0) world->cycle_ke = 0;
									world->weather = items[world->infinity[world->cycle_ke]].base_weather;
									world->cycle_ke++;
									world->blocks[x_ + (y_ * 100)].epoch_cycle = current_time + (world->blocks[x_ + (y_ * 100)].infinity_cycle * 60);
									if (pInfo(cp_)->world == world->name) {
										VarList::OnSetCurrentWeather(cp_, (Event()->Comet_Dust ? 16 : world->weather == 0 ? 80 : world->weather));
									}
								}
							}
						}
						std::vector<WorldBlock>::iterator p5 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == 3202; });
						if (p5 != world->blocks.end()) {
							int x_ = int(p5 - world->blocks.begin()) % 100, y_ = int(p5 - world->blocks.begin()) / 100;
							if (world->name == "GROWCH" and WinterFest.Active and world->blocks[x_ + (y_ * 100)].fg == 3202 and world->blocks[x_ + (y_ * 100)].planted - time(nullptr) <= 0) {
								world->blocks[x_ + (y_ * 100)].fg = 3200;
								for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
									if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
									if (world->name == "GROWCH") {
										update_tile(cp_, x_, y_, 3200, true);
										tile_update(cp_, world, &world->blocks[x_ + (y_ * 100)], x_, y_);
									}
								}
							}
						}
					}
				}
			}
			if (Environment()->Last_Growganoth - ms_time <= 0 and Event()->Halloween) {
				std::string name_ = "GROWGANOTH";
				auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (it != worlds.end()) {
					World* world_ = &(*it);
					Environment()->Last_Growganoth = ms_time + 20000;
					for (int i_ = 0; i_ < Environment()->growganoth_platform.size(); i_++) {
						int x_ = Environment()->growganoth_platform[i_] % 100, y_ = Environment()->growganoth_platform[i_] / 100;
						world_->blocks[x_ + (y_ * 100)].fg = 0;
						PlayerMoving data{ 0, 0, 3, 0, 0, Environment()->growganoth_platform[i_] % 100, Environment()->growganoth_platform[i_] / 100, 0, (float)x_, (float)y_, 0, 0 };
						BYTE* p_ = packPlayerMoving(&data);
						for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
							if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world_->name) continue;
							send_raw(cp_, 4, p_, 56, ENET_PACKET_FLAG_RELIABLE);
						}
						delete[] p_;
					}
					Environment()->growganoth_platform.clear();
					for (int i_ = 0; i_ < 50; i_++) {
						int x_ = rand() % 89 + 1, y_ = rand() % 52 + 1;
						if (world_->blocks[x_ + (y_ * 100)].fg == 0) {
							Environment()->growganoth_platform.push_back(x_ + (y_ * 100));
							world_->blocks[x_ + (y_ * 100)].fg = (i_ < 40 ? 1222 : 1224);
							PlayerMoving data{ 0, 0, 3, 0, world_->blocks[x_ + (y_ * 100)].fg, x_, y_, 0, (float)x_, (float)y_, 0, 0 };
							BYTE* p_ = packPlayerMoving(&data);
							for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
								if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world_->name) continue;
								send_raw(cp_, 4, p_, 56, ENET_PACKET_FLAG_RELIABLE);
							}
							delete[] p_;
						}
						if (world_->blocks[25 + (30 * 100)].fg == 0) {
							world_->blocks[25 + (30 * 100)].fg = (i_ > 40 ? 1226 : 1228);
							Environment()->growganoth_platform.push_back(25 + (30 * 100));
							PlayerMoving data{ 0, 0, 3, 0, world_->blocks[25 + (30 * 100)].fg, 25, 30, 0, (float)25, (float)30, 0, 0 };
							BYTE* p_ = packPlayerMoving(&data);
							for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
								if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world_->name) continue;
								send_raw(cp_, 4, p_, 56, ENET_PACKET_FLAG_RELIABLE);
							}
							delete[] p_;
						}
					}
				}
			}
			if (Environment()->Last_Update_Rich - ms_time <= 0) {
				Environment()->Last_Update_Rich = ms_time + 50000;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->tankIDName.empty()) continue;
					int world_lock = 0, diamond_lock = 0, plat_gem_lock = 0, ruth_gem_lock = 0, total_gems = pInfo(cp_)->gems / 2000, total_wl_in_bank = pInfo(cp_)->wl_bank_amount, total_dl_in_bank = pInfo(cp_)->dl_bank_amount, total_pgl_in_bank = pInfo(cp_)->pgl_bank_amount, total_rgl_in_bank = pInfo(cp_)->mgl_bank_amount;
					Inventory::Modify(cp_, 242, world_lock), Inventory::Modify(cp_, 1796, diamond_lock), Inventory::Modify(cp_, 7188, plat_gem_lock), Inventory::Modify(cp_, 8470, ruth_gem_lock);
					if (total_wl_in_bank != 0) world_lock += total_wl_in_bank;
					if (total_dl_in_bank != 0) world_lock += total_dl_in_bank * 100;
					if (total_pgl_in_bank != 0) world_lock += total_pgl_in_bank * 10000;
					if (total_rgl_in_bank != 0) world_lock += total_rgl_in_bank * 1000000;
					if (plat_gem_lock != 0) world_lock += plat_gem_lock * 10000;
					if (ruth_gem_lock != 0) world_lock += ruth_gem_lock * 1000000;
					if (diamond_lock != 0) world_lock += diamond_lock * 100;
					pInfo(cp_)->total_locks = world_lock;
					pInfo(cp_)->total_all_score = total_gems + world_lock;
					string find = pInfo(cp_)->tankIDName;
					auto it = std::find_if(top_richest.begin(), top_richest.end(), [&](const auto& p) { return p.first == p.first && p.second == find; });
					if (it != top_richest.end()) {
						*it = { pInfo(cp_)->total_all_score, find };
					}
					else top_richest.push_back({ pInfo(cp_)->total_all_score, find });
					std::sort(top_richest.begin(), top_richest.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
					{
						if (pInfo(cp_)->growpass_points == 0) continue;
						auto it = std::find_if(top_royalpass.begin(), top_royalpass.end(), [&](const auto& p) { return p.first == p.first && p.second == find; });
						if (it != top_royalpass.end()) {
							*it = { pInfo(cp_)->growpass_points, find };
						}
						else top_royalpass.push_back({ pInfo(cp_)->growpass_points, find });
						std::sort(top_royalpass.begin(), top_royalpass.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
					}
					{
						if (pInfo(cp_)->Mines_Score == 0) continue;
						auto it = std::find_if(top_mines.begin(), top_mines.end(), [&](const auto& p) { return p.first == p.first && p.second == find; });
						if (it != top_mines.end()) {
							*it = { pInfo(cp_)->Mines_Score, find };
						}
						else top_mines.push_back({ pInfo(cp_)->Mines_Score, find });
						std::sort(top_mines.begin(), top_mines.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
					}
					{
						if (pInfo(cp_)->punch_count == 0) continue;
						auto it = std::find_if(top_punch.begin(), top_punch.end(), [&](const auto& p) { return p.first == p.first && p.second == find; });
						if (it != top_punch.end()) {
							*it = { pInfo(cp_)->punch_count, find };
						}
						else top_punch.push_back({ pInfo(cp_)->punch_count, find });
						std::sort(top_punch.begin(), top_punch.end(), [](const auto& a, const auto& b) { return a.first > b.first; });
					}
				}
			}
			if (Environment()->Last_SystemInfo - ms_time <= 0) {
				Environment()->Last_SystemInfo = ms_time + 30000000;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL || pInfo(cp_)->world.empty()) continue;
					VarList::OnConsoleMessage(cp_, systemInfo[rand() % systemInfo.size()]);
					VarList::OnPlaySound(cp_, "audio/beep.wav");
				}
			}
			if (Environment()->Last_Firehouse - ms_time <= 0) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL or pInfo(cp_)->tankIDName.empty()) continue;
					std::string name_ = pInfo(cp_)->world;
					auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (it != worlds.end()) {
						World* world = &(*it);
						world->fresh_world = true;
						std::vector<WorldBlock>::iterator p3 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == 3072; });
						if (p3 != world->blocks.end()) {
							std::vector<WorldBlock>::iterator p2 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.flags & 0x10000000; });
							if (p2 != world->blocks.end()) {
								int x_ = int(p2 - world->blocks.begin()) % 100, y_ = int(p2 - world->blocks.begin()) / 100;
								int x_x = int(p3 - world->blocks.begin()) % 100, y_y = int(p3 - world->blocks.begin()) / 100;
								PlayerMoving data_{};
								data_.packetType = 36, data_.netID = 34, data_.characterState = 0x8, data_.x = x_x, data_.y = y_y;
								int32_t to_netid = 0x10000000;
								BYTE* raw = packPlayerMoving(&data_);
								raw[3] = 5;
								Memory_Copy(raw + 8, &to_netid, 4);
								for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
									if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
									if (pInfo(cp_)->world == pInfo(cp_)->world) {
										send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[] raw;
								apply_tile_visual(world, &world->blocks[x_ + (y_ * 100)], x_, y_, 0x10000000, true);
							}
						}
						if (Environment()->Last_Fire_Time - ms_time <= 0) {
							if (world->total_fires < 150) {
								std::vector<WorldBlock>::iterator p2 = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.flags & 0x10000000 && (world->fire_try > 10 ? a.applied_fire == true : a.applied_fire == false); });
								if (p2 != world->blocks.end()) {
									int x_ = int(p2 - world->blocks.begin()) % 100, y_ = int(p2 - world->blocks.begin()) / 100;
									std::vector<int> random_xy{ 1, 0, -1, 0 };
									int randomx = 0, randomy = 0;
									if (rand() % 2 < 1) randomx = x_ + random_xy[rand() % random_xy.size()], randomy = y_;
									else randomx = x_, randomy = y_ + random_xy[rand() % random_xy.size()];
									if (randomx > 0 && randomx < world->max_x && randomy > 0 && randomy < world->max_y) {
										bool has_fire = world->blocks[randomx + (randomy * 100)].flags & 0x10000000, has_water = world->blocks[randomx + (randomy * 100)].flags & 0x04000000;
										if (world->blocks[randomx + (randomy * 100)].fg != 0 && has_fire == false && has_water == false && items[world->blocks[randomx + (randomy * 100)].fg].blockType != BlockTypes::MAIN_DOOR && items[world->blocks[randomx + (randomy * 100)].fg].blockType != BlockTypes::BEDROCK && world->blocks[randomx + (randomy * 100)].fg != 9570) apply_tile_visual(world, &world->blocks[randomx + (randomy * 100)], randomx, randomy, 0x10000000);
										else {
											world->blocks[x_ + (y_ * 100)].fire_try++;
											if (world->blocks[x_ + (y_ * 100)].fire_try >= 8) world->blocks[x_ + (y_ * 100)].applied_fire = true, world->blocks[x_ + (y_ * 100)].fire_try = 0;
										}
									}
								}
								else {
									world->fire_try++;
									if (world->fire_try > 10) world->fire_try = 0;
								}
							}
						}
					}
				}
			}
			if (Environment()->Last_Time - ms_time <= 0) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL || pInfo(cp_)->world.empty()) continue;
					if (pInfo(cp_)->pet_netID == 0 && pInfo(cp_)->pet_type != -1 && !pInfo(cp_)->world.empty() && pInfo(cp_)->show_pets) {
						Pet_Ai::Create(cp_);
					}
					else if (pInfo(cp_)->pet_netID != 0 && pInfo(cp_)->pet_type != -1 && !pInfo(cp_)->world.empty()) {
						if (!pInfo(cp_)->pet_ClothesUpdated && pInfo(cp_)->show_pets) {
							Pet_Ai::Update(cp_, pInfo(cp_)->pet_netID, pInfo(cp_)->pet_level, pInfo(cp_)->master_pet, pInfo(cp_)->active_bluename);
						}
					}
				}
				for (int a = 0; a < Environment()->Another_Worlds.size(); a++) {
					std::string name = Environment()->Another_Worlds[a];
					auto it = std::find_if(worlds.begin(), worlds.end(), [name](const World& a) { return a.name == name; });
					if (it != worlds.end()) {
						World* world = &(*it);
						world->fresh_world = true;
						if (world->machines.size() == 0 && world->npc.size() == 0 && world->special_event == false) {
							Environment()->Another_Worlds.erase(Environment()->Another_Worlds.begin() + a);
							a--;
							if (ServerPool::PlayerCountWorld(world->name) == 0) save_world(world->name, true);
							continue;
						}
						if (world->special_event) {
							if (world->last_special_event + 30000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								for (ENetPeer* currentPeer_event = server->peers; currentPeer_event < &server->peers[server->peerCount]; ++currentPeer_event) {
									if (currentPeer_event->state != ENET_PEER_STATE_CONNECTED or currentPeer_event->data == NULL or pInfo(currentPeer_event)->world != world->name) continue;
									if (world->special_event_name == "Dr. Destructo") {
										if (pInfo(currentPeer_event)->DrDes) {
											VarList::OnConsoleMessage(currentPeer_event, "Destructo has won! (`4Dr. Destructo`` mod removed)");
											pInfo(currentPeer_event)->d_name = "";
											pInfo(currentPeer_event)->DrDes = false, pInfo(currentPeer_event)->ghost = false;
											pInfo(currentPeer_event)->Health_DrDes = 100, pInfo(currentPeer_event)->face = 0, pInfo(currentPeer_event)->shirt = 0, pInfo(currentPeer_event)->pants = 0, pInfo(currentPeer_event)->hair = 0, pInfo(currentPeer_event)->necklace = 0, pInfo(currentPeer_event)->back = 0, pInfo(currentPeer_event)->feet = 0, pInfo(currentPeer_event)->hand = 0, pInfo(currentPeer_event)->punched = 0;
											VisualHandle::State(pInfo(currentPeer_event));
											VisualHandle::Nick(currentPeer_event, NULL);
											Clothing_V2::Update_Value(currentPeer_event);
											Clothing_V2::Update(currentPeer_event);
										}
										VarList::OnConsoleMessage(currentPeer_event, "`4Dr. Destructo `oescaped!");
										VarList::OnAddNotification(currentPeer_event, "`4Dr. Destructo `oescaped!", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
									}
									else {
										VarList::OnConsoleMessage(currentPeer_event, "`2" + items[world->special_event_item].event_name + ":`` " + (items[world->special_event_item].event_total == 1 ? "`oTime's up! Nobody found it!``" : "`oTime's up! " + to_string(world->special_event_item_taken) + " of " + to_string(items[world->special_event_item].event_total) + " items found.``") + "");
										VarList::OnAddNotification(currentPeer_event, "`2" + items[world->special_event_item].event_name + ":`` " + (items[world->special_event_item].event_total == 1 ? "`oTime's up! Nobody found it!``" : "`oTime's up! " + to_string(world->special_event_item_taken) + " of " + to_string(items[world->special_event_item].event_total) + " items found.``") + "", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
									}
									PlayerMoving data_{};
									for (int i_ = 0; i_ < world->drop_new.size(); i_++) {
										if (find(world->world_event_items.begin(), world->world_event_items.end(), world->drop_new[i_][0]) != world->world_event_items.end()) {
											BYTE* raw1_ = PackBlockUpdate(14, 0, 0, 0, 0, 0, 0, 0, world->drop_new[i_][2], 0, 0, 0, 0, 0);
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world->name) continue;
												send_raw(cp_, 4, raw1_, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw1_;
											world->drop_new.erase(world->drop_new.begin() + i_);
											i_--;
										}
									}
								}
								world->world_event_items.clear();
								world->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count(), world->special_event_item = 0, world->special_event_item_taken = 0, world->special_event = false, world->special_event_name = "";
							}
							continue;
						}
						for (int i_ = 0; i_ < world->machines.size(); i_++) {
							WorldMachines* machine = &world->machines[i_];
							if (world->blocks[machine->x + (machine->y * 100)].pr <= 0 or not world->blocks[machine->x + (machine->y * 100)].enabled or machine->target_item == 0) {
								if (items[world->blocks[machine->x + (machine->y * 100)].fg].blockType == BlockTypes::AUTO_BLOCK) {
									world->machines.erase(world->machines.begin() + i_);
									i_--;
								}
								continue;
							}
							WorldBlock* itemas = &world->blocks[machine->x + (machine->y * 100)];
							int ySize = world->blocks.size() / 100, xSize = world->blocks.size() / ySize;
							if (itemas->pr > 0) {
								if (machine->last_ - ms_time > 0) break;
								if (itemas->fg == 6952 or (itemas->fg == 6954 && itemas->build_only == false)) {
									int itemas_ = (itemas->fg == 6954 ? machine->target_item - 1 : machine->target_item);
									std::vector<WorldBlock>::iterator p = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == itemas_ or a.bg == itemas_; });
									if (p != world->blocks.end()) {
										WorldBlock* block_ = &world->blocks[p - world->blocks.begin()];
										int size = p - world->blocks.begin(), x_ = size % xSize, y_ = size / xSize;
										if (items[itemas_].blockType == BlockTypes::BACKGROUND and block_->fg != 0) continue;
										BYTE* raw1_ = PackBlockUpdate(17, 0x8, x_ * 32 + 16, y_ * 32 + 16, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0);
										BYTE* raw2_ = PackBlockUpdate(36, 0x8, x_ * 32 + 16, y_ * 32 + 16, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0);
										for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
											if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world->name) continue;
											send_raw(cp_, 4, raw1_, 56, ENET_PACKET_FLAG_RELIABLE);
											send_raw(cp_, 4, raw2_, 56, ENET_PACKET_FLAG_RELIABLE);
										}
										delete[] raw1_;
										delete[] raw2_;
										itemas->pr--;
										if (itemas->pr <= 0) {
											PlayerMoving data_{};
											data_.packetType = 5, data_.punchX = machine->x, data_.punchY = machine->y, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world, itemas));
											BYTE* blc = raw + 56;
											form_visual(blc, *itemas, *world, NULL, false);
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
												if (pInfo(cp_)->world == world->name) {
													send_raw(cp_, 4, raw, 112 + alloc_(world, itemas), ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[] raw, blc;
										}
										if (block_->hp == -1) {
											int breakhits = items[itemas_].breakHits;
											block_->hp = (breakhits == 1 ? breakhits * 3 : breakhits > 3 ? 3 : breakhits);
											block_->lp = ms_time;
										}
										block_->hp -= 1;
										if (block_->hp == 0) {
											if (items[itemas_].max_gems != 0) {
												int maxgems = items[itemas_].max_gems;
												if (itemas_ == 120) maxgems = 50;
												int c_ = rand() % (maxgems + 1);
												if (c_ != 0) {
													bool no_seed = false, no_gems = false, no_block = false;
													if (itemas_ == 2242 or itemas_ == 2244 or itemas_ == 2246 or itemas_ == 2248 or itemas_ == 2250 or itemas_ == 542) no_seed = true, no_block = true;
													else {
														for (int i_ = 0; i_ < world->drop_new.size(); i_++) {
															if (abs(world->drop_new[i_][4] - y_ * 32) <= 16 and abs(world->drop_new[i_][3] - x_ * 32) <= 16) {
																if (world->drop_new[i_][0] == 112 and items[itemas_].rarity < 8) {
																	no_gems = true;
																}
																else {
																	no_seed = true, no_block = true;
																}
															}
														}
													}
													int chanced = 0;
													if (rand() % 100 < 8) {
														WorldDrop drop_block_{};
														drop_block_.id = itemas_, drop_block_.count = 1, drop_block_.x = (x_ * 32) + rand() % 17, drop_block_.y = (y_ * 32) + rand() % 17;
														if (not use_mag(world, drop_block_, x_, y_) and not no_block) {
															VisualHandle::Drop(world, drop_block_);
														}
													}
													else if (rand() % 100 < (items[itemas_].newdropchance + chanced)) {
														WorldDrop drop_seed_{};
														drop_seed_.id = itemas_ + 1, drop_seed_.count = 1, drop_seed_.x = (x_ * 32) + rand() % 17, drop_seed_.y = (y_ * 32) + rand() % 17;
														if (not use_mag(world, drop_seed_, x_, y_) and not no_seed) {
															VisualHandle::Drop(world, drop_seed_);
														}
													}
													else if (not no_gems) {
														drop_rare_item(world, NULL, itemas_, x_, y_, false);
														gems_(NULL, world, c_, x_ * 32, y_ * 32, itemas_);
													}
												}
											}
											reset_(block_, x_, y_, world);
											PlayerMoving data_{};
											data_.packetType = 5, data_.punchX = x_, data_.punchY = y_, data_.characterState = 0x8;
											BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world, block_));
											BYTE* blc = raw + 56;
											form_visual(blc, *block_, *world, NULL, false);
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
												if (pInfo(cp_)->world == world->name) {
													send_raw(cp_, 4, raw, 112 + alloc_(world, block_), ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[] raw, blc;
										}
										else {
											BYTE* raw1_ = PackBlockUpdate(0x8, 0x0, x_, y_, 0, 0, 0, -1, 6, x_, y_, 0, 0, 0);
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world->name) continue;
												send_raw(cp_, 4, raw1_, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw1_;
										}
									}
								}
								else if (itemas->fg == 6950 or (itemas->fg == 6954 && itemas->build_only)) {
									std::vector<WorldBlock>::iterator p = find_if(world->blocks.begin(), world->blocks.end(), [&](const WorldBlock& a) { return a.fg == machine->target_item; });
									if (p != world->blocks.end()) {
										int a_ = p - world->blocks.begin();
										long long times_ = time(nullptr);
										std::uint32_t laikas = std::uint32_t((times_ - world->blocks[a_].planted <= items[world->blocks[a_].fg].growTime ? times_ - world->blocks[a_].planted : items[world->blocks[a_].fg].growTime));
										if (items[world->blocks[a_].fg].blockType == BlockTypes::SEED and laikas == items[world->blocks[a_].fg].growTime) {
											int x_ = a_ % xSize, y_ = a_ / xSize;
											WorldBlock* block_ = &world->blocks[x_ + (y_ * 100)];
											int drop_count = items[block_->fg - 1].rarity == 1 ? (items[block_->fg - 1].farmable ? (rand() % 6) + 5 : (rand() % block_->fruit) + 1) : items[block_->fg - 1].farmable ? (rand() % 6) + 4 : (rand() % block_->fruit) + 1;
											if (harvest_seed(world, block_, x_, y_, drop_count, -1)) {

											}
											else if (world->weather == 8 and rand() % 300 < 2) {
												WorldDrop drop_block_{};
												drop_block_.id = 3722, drop_block_.count = 1, drop_block_.x = x_ * 32 + rand() % 17, drop_block_.y = y_ * 32 + rand() % 17;
												VisualHandle::Drop(world, drop_block_);
												BYTE* raw1_ = PackBlockUpdate(0x11, 0, drop_block_.x, drop_block_.y, 0, 108, 0, 0, 0, 0, 0, 0, 0, 0);
												for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
													if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world->name) continue;
													send_raw(cp_, 4, raw1_, 56, ENET_PACKET_FLAG_RELIABLE);
												}
												delete[] raw1_;
											}
											if (drop_count != 0) drop_rare_item(world, NULL, machine->target_item - 1, x_, y_, true);
											BYTE* raw1_ = PackBlockUpdate(17, 0x8, x_ * 32 + 16, y_ * 32 + 16, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0);
											BYTE* raw2_ = PackBlockUpdate(36, 0x8, x_ * 32 + 16, y_ * 32 + 16, 0, 0, 0, 109, 0, 0, 0, 0, 0, 0);
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world->name) continue;
												send_raw(cp_, 4, raw1_, 56, ENET_PACKET_FLAG_RELIABLE);
												send_raw(cp_, 4, raw2_, 56, ENET_PACKET_FLAG_RELIABLE);
											}
											delete[] raw1_;
											delete[] raw2_;
											itemas->pr--;
											if (itemas->pr <= 0) {
												PlayerMoving data_{};
												data_.packetType = 5, data_.punchX = machine->x, data_.punchY = machine->y, data_.characterState = 0x8;
												BYTE* raw = packPlayerMoving(&data_, 112 + alloc_(world, itemas));
												BYTE* blc = raw + 56;
												form_visual(blc, *itemas, *world, NULL, false);
												for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
													if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
													if (pInfo(cp_)->world == world->name) {
														send_raw(cp_, 4, raw, 112 + alloc_(world, itemas), ENET_PACKET_FLAG_RELIABLE);
													}
												}
												delete[] raw, blc;
											}
										}
									}
								}
							}
						}
						long long time_ = time(nullptr);
						for (int i_ = 0; i_ < world->npc.size(); i_++) {
							WorldNPC* npc = &world->npc[i_];
							if (not npc->enabled) continue;
							if (npc->last_ - time_ > 0) continue;
							int active = 0;
							std::map<std::string, std::vector<WorldNPC>>::iterator it;
							for (it = active_npc.begin(); it != active_npc.end(); it++) {
								if (it->first == world->name) {
									for (int i_ = 0; i_ < it->second.size(); i_++) {
										if (it->second[i_].uid != -1) active++;
										if (active > 10) break;
									}
									break;
								}
							}
							if (active > 10) continue;
							npc->last_ = time_ + npc->rate_of_fire;
							WorldBlock* itemas = &world->blocks[npc->x + (npc->y * 100)];
							if (not itemas->enabled) continue;
							switch (itemas->fg) {
							case 8020: case 4344: {
								PlayerMoving data_{};
								data_.packetType = 34;
								data_.x = static_cast<float>(npc->x) * 32 + 16;
								data_.y = static_cast<float>(npc->y) * 32 + (itemas->fg == 8020 ? 6 : 16); //nuo y
								data_.XSpeed = static_cast<float>(npc->x) * 32 + 16;
								data_.YSpeed = static_cast<float>(npc->y) * 32 + (itemas->fg == 8020 ? 6 : 16); // iki y
								data_.punchY = npc->projectile_speed;
								BYTE* raw = packPlayerMoving(&data_);
								uint16_t uid = (active_npc.find(world->name) != active_npc.end() ? active_npc[world->name].size() : 0);
								raw[1] = (itemas->fg == 8020 ? 15 : 8);
								raw[2] = uid;
								raw[3] = 2;
								Memory_Copy(raw + 40, &npc->kryptis, 4);
								npc->uid = uid;
								npc->started_moving = ms_time;
								if (active_npc.find(world->name) != active_npc.end()) {
									active_npc[world->name].emplace_back(*npc);
								}
								else {
									std::vector<WorldNPC> list_;
									list_.emplace_back(*npc);
									active_npc.insert({ world->name, list_ });
								}
								for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
									if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
									if (pInfo(cp_)->world == world->name and pInfo(cp_)->x != -1) {
										send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								delete[]raw;
								break;
							}
							default: {
								bool cant_del = false;
								std::map<std::string, std::vector<WorldNPC>>::iterator it;
								for (it = active_npc.begin(); it != active_npc.end(); it++) {
									if (cant_del) break;
									if (it->first == world->name) {
										for (int i_ = 0; i_ < it->second.size(); i_++) {
											WorldNPC* npc_ = &it->second[i_];
											if (npc->uid == npc_->uid) {
												cant_del = true;
												break;
											}
										}
									}
								}
								if (not cant_del) {
									world->npc.erase(world->npc.begin() + i_);
								}
								break;
							}
							}
						}
						std::map<std::string, std::vector<WorldNPC>>::iterator it;
						for (it = active_npc.begin(); it != active_npc.end(); it++) {
							if (it->first == world->name) {
								for (int i_ = 0; i_ < it->second.size(); i_++) {
									WorldNPC* npc_ = &it->second[i_];
									if (npc_->uid == -1) continue;
									WorldBlock* itemas = &world->blocks[npc_->x + (npc_->y * 100)];
									double per_sekunde_praeina_bloku = (double)npc_->projectile_speed / 32;
									double praejo_laiko = (double)(ms_time - npc_->started_moving) / 1000;
									double praejo_distancija = (double)per_sekunde_praeina_bloku * (double)praejo_laiko;
									double current_x = ((int)npc_->kryptis == 180 ? (((double)npc_->x - (double)praejo_distancija) * 32) + 16 : (((double)npc_->x + (double)praejo_distancija) * 32) + 16);
									double current_y = (double)npc_->y * 32;
									if (current_x / 32 < 0 or current_x / 32 >= 100 or current_y / 32 < 0 or current_y / 32 >= 60)
									{
										PlayerMoving data_{};
										data_.packetType = 34;
										data_.x = (current_x);
										data_.y = (current_y + (npc_->id == 8020 ? 6 : 16));
										data_.XSpeed = (current_x);
										data_.YSpeed = (current_y + (npc_->id == 8020 ? 6 : 16));
										data_.punchY = npc_->projectile_speed;
										BYTE* raw = packPlayerMoving(&data_);
										raw[1] = (itemas->fg == 8020 ? 15 : 8);
										raw[2] = npc_->uid;
										raw[3] = 7;
										for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
											if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
											if (pInfo(cp_)->world == world->name and pInfo(cp_)->x != -1) {
												send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
											}
										}
										delete[]raw;
										npc_->uid = -1;
										continue;
									}
									try {
										WorldBlock* block_ = &world->blocks[current_x / 32 + (current_y / 32 * 100)];
										if (items[block_->fg].collisionType == 1 or (current_x / 32) > 100 or (current_x / 32) < 0) {
											PlayerMoving data_{};
											data_.packetType = 34;
											data_.x = (current_x);
											data_.y = (current_y + (npc_->id == 8020 ? 6 : 16));
											data_.XSpeed = (current_x);
											data_.YSpeed = (current_y + (npc_->id == 8020 ? 6 : 16));
											data_.punchY = npc_->projectile_speed;
											BYTE* raw = packPlayerMoving(&data_);
											raw[1] = (itemas->fg == 8020 ? 15 : 8);
											raw[2] = npc_->uid;
											raw[3] = 7;
											for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
												if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
												if (pInfo(cp_)->world == world->name and pInfo(cp_)->x != -1) {
													send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
												}
											}
											delete[]raw;
											npc_->uid = -1;
										}
									}
									catch (out_of_range) {
										continue;
									}
								}
								break;
							}
						}
					}
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL or pInfo(cp_)->tankIDName.empty() or pInfo(cp_)->world.empty()) continue;
					auto mining_cooldownleft = calc_d(pInfo(cp_)->MiningTime);
					if (mining_cooldownleft < 1 and pInfo(cp_)->In_World_Mining) {
						Exit_World(cp_);
						VarList::OnEndMission(cp_);
					}
					if (pInfo(cp_)->face == 4260 and pInfo(cp_)->Present_Goblin - time(nullptr) < 0) {
						pInfo(cp_)->face = 0;
						Clothing_V2::Update_Value(cp_);
						Clothing_V2::Update(cp_);
					}
					if (pInfo(cp_)->world == "WINTERCLASHPARKOUR" and pInfo(cp_)->In_World_Clash) {
						pInfo(cp_)->In_World_Clash = false;
						VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "`6I SHALL FACE THE FINALE PARKOUR!!!", 0, 1, 500);
						gamepacket_t packet(500, pInfo(cp_)->netID);
						packet.Insert("OnCountdownStart"), packet.Insert(1500), packet.Insert(-1), packet.CreatePacket(cp_);
					}
					if (pInfo(cp_)->Role.BOOST) {
						if (pInfo(cp_)->Role.BOOST_TIME - time(nullptr) < 0) {
							pInfo(cp_)->Role.BOOST = false;
							pInfo(cp_)->Role.BOOST_TIME = 0;
							VisualHandle::Nick(cp_, NULL);
							VarList::OnConsoleMessage(cp_, "`oYour `5[BOOST]`` Role has run out, type /shop to purchase roles");
						}
					}
					if (pInfo(cp_)->Role.SUPER_BOOST) {
						if (pInfo(cp_)->Role.SUPER_BOOST_TIME - time(nullptr) < 0) {
							pInfo(cp_)->Role.SUPER_BOOST = false;
							pInfo(cp_)->Role.SUPER_BOOST_TIME = 0;
							VisualHandle::Nick(cp_, NULL);
							VarList::OnConsoleMessage(cp_, "`oYour `8[SUPER-BOOST]`` Role has run out, type /shop to purchase roles");
						}
					}
					if (pInfo(cp_)->St_Regen_Time - time(nullptr) < 0) {
						if (pInfo(cp_)->Masterless_Starglitter <= 4800) {
							pInfo(cp_)->St_Regen_Time = time(nullptr) + 240;
							pInfo(cp_)->Masterless_Starglitter += 1;
							if (pInfo(cp_)->Masterless_Starglitter >= 4800) pInfo(cp_)->Masterless_Starglitter = 1200;
							VarList::SetCurrency(cp_, pInfo(cp_)->Masterless_Starglitter);
						}
					}
					if (pInfo(cp_)->adventure_begins && pInfo(cp_)->timerActive) {
						if (!player::algorithm::adventureTimers(cp_)) {
							pInfo(cp_)->adventure_begins = false;
							pInfo(cp_)->timerActive = false;
							if (pInfo(cp_)->lives >= 1) {
								pInfo(cp_)->lives = 0;
								VisualHandle::Nick(cp_, NULL);
							}
							VarList::OnCountdownEnd(cp_, pInfo(cp_)->netID);
							Player_Respawn(cp_, true, 0, 1);
							VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, ":'( I failed my adventure!", 1, true);
							pInfo(cp_)->timers = 0;
						}
					}
					if (pInfo(cp_)->hand == 3578 || pInfo(cp_)->face == 3576) {
						if (pInfo(cp_)->hand_torch + 60000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
							int got = 0;
							if (pInfo(cp_)->hand == 3578) {
								if (pInfo(cp_)->hand_torch != 0) {
									Inventory::Modify(cp_, 3578, got);
									if (got - 1 >= 1) {
										VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "`4My torch went out, but I have " + to_string(got - 1) + " more!``", 0, 0);
									}
									Inventory::Modify(cp_, 3578, got = -1);
								}
							}
							else if (pInfo(cp_)->face == 3576) {
								Inventory::Modify(cp_, 3306, got = -1);
							}
							pInfo(cp_)->hand_torch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						}
					}
					else if (pInfo(cp_)->hand == 2204 or pInfo(cp_)->hand == 2558 and pInfo(cp_)->x != -1 and pInfo(cp_)->y != -1) {
						if (pInfo(cp_)->random_geiger_time < 100) {
							pInfo(cp_)->random_geiger_time++;
						}
						else {
							pInfo(cp_)->random_geiger_time = 0;
							pInfo(cp_)->geiger_x = (rand() % 100) * 32;
							pInfo(cp_)->geiger_y = (rand() % 54) * 32;
						}
						int hands_ = pInfo(cp_)->hand;
						if (not Playmods::HasById(pInfo(cp_), 10)) {
							if (pInfo(cp_)->geiger_x == -1 and pInfo(cp_)->geiger_y == -1) {
								pInfo(cp_)->geiger_x = (rand() % 100) * 32;
								pInfo(cp_)->geiger_y = (rand() % 54) * 32;
							}
							int a_ = pInfo(cp_)->geiger_x + ((pInfo(cp_)->geiger_y * 100) / 32), b_ = pInfo(cp_)->x + ((pInfo(cp_)->y * 100) / 32), diff = abs(a_ - b_) / 32;
							if (diff < 30) {
								int t_ = 1500;
								if (diff >= 6) t_ = 1350;
								else if (diff < 15) t_ = 1000;
								else if (diff <= 1) t_ = 2500;
								if (pInfo(cp_)->geiger_time + t_ < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
									pInfo(cp_)->geiger_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
									PlayerMoving data_{};
									data_.packetType = 17, data_.characterState = 0x8, data_.x = pInfo(cp_)->x + 10, data_.y = pInfo(cp_)->y + 16, data_.XSpeed = (diff >= 30 ? 0 : (diff >= 15 ? 1 : 2)), data_.YSpeed = 114;
									BYTE* raw = packPlayerMoving(&data_);
									send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
									delete[] raw;
									if (diff <= 1) {
										pInfo(cp_)->geiger_x = -1, pInfo(cp_)->geiger_y = -1;
										int give_back_geiger = items[pInfo(cp_)->hand].geiger_give_back;
										{
											int c_ = -1;
											Inventory::Modify(cp_, pInfo(cp_)->hand, c_);
											int c_2 = 1;
											if (Inventory::Modify(cp_, give_back_geiger, c_2) != 0) {
												std::string name_ = pInfo(cp_)->world;
												auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
												if (it != worlds.end()) {
													World* world_ = &(*it);
													world_->fresh_world = true;
													WorldDrop drop_block_{};
													drop_block_.id = give_back_geiger, drop_block_.count = 1, drop_block_.x = pInfo(cp_)->x + rand() % 17, drop_block_.y = pInfo(cp_)->y + rand() % 17;
													VisualHandle::Drop(world_, drop_block_);
												}
											}
											int seconds = 1800;
											if (Playmods::HasById(pInfo(cp_), 148) and rand() % 50 < 2) {/*Guild Potion: Geiger*/
												seconds = 500;
											}
											pInfo(cp_)->hand = give_back_geiger;
											Clothing_V2::Update(cp_);
											Playmods::Add(cp_, 10, seconds);
											CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/dialog_confirm.wav", 0);
										}
										if (Event()->dailyc_name == "Geiger") Daily_Challenge::Add_Points(cp_, rand() % 50);
										if (pInfo(cp_)->starglitter_geiger < pInfo(cp_)->starglitter_geiger2 && pInfo(cp_)->starglitter_geiger != -1) DailyEvent_Task::MStarglitter(cp_, "geiger", 1);
										if (pInfo(cp_)->lwiz_step == 13) {
											if (pInfo(cp_)->lwiz_quest == 5 || pInfo(cp_)->lwiz_quest == 6 || pInfo(cp_)->lwiz_quest == 7 || pInfo(cp_)->lwiz_quest == 8) {
												add_lwiz_points(cp_, 1);
											}
										}
										if (pInfo(cp_)->role_quest and pInfo(cp_)->quest_number == 1) {
											if (pInfo(cp_)->role_quest_type == "Geiger" and pInfo(cp_)->need_required < pInfo(cp_)->quest_required) {
												pInfo(cp_)->need_required += 1;
												if (pInfo(cp_)->need_required >= pInfo(cp_)->quest_required) {
													pInfo(cp_)->need_required = pInfo(cp_)->quest_required;
													VarList::OnConsoleMessage(cp_, "`9Geiger Quest! `ocomplete! Go claim your points!");
													VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "`9Geiger Quest! ``complete! Go claim your points!", 0, 0);
												}
											}
										}
										if (pInfo(cp_)->BiweeklyQ_2 < 20) {
											pInfo(cp_)->BiweeklyQ_2 += 1;
											if (pInfo(cp_)->BiweeklyQ_2 >= 20) {
												pInfo(cp_)->BiweeklyQ_2 = 20;
												VarList::OnConsoleMessage(cp_, "`9Biweekly Goal ''`2Find 20 radioactive items``'' is complete! Go call Crazy Jim!");
												VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "`9Biweekly Goal ''`2Find 20 radioactive items``'' is complete! Go call Crazy Jim!", 0, 0);
											}
										}
										int give_times = 1;
										if (pInfo(cp_)->gp) {
											if (complete_gpass_task(cp_, "Geiger")) give_times++;
										}
										for (int i = 0; i < give_times; i++) {
											int item_ = items[hands_].randomitem[rand() % items[hands_].randomitem.size()], c_ = 1;
											if (item_ == 1486) if (pInfo(cp_)->lwiz_step == 6) add_lwiz_points(cp_, 1);
											if (item_ == 1486 && pInfo(cp_)->C_QuestActive && pInfo(cp_)->C_QuestKind == 11 && pInfo(cp_)->C_QuestProgress < pInfo(cp_)->C_ProgressNeeded) {
												pInfo(cp_)->C_QuestProgress += 1;
												if (pInfo(cp_)->C_QuestProgress >= pInfo(cp_)->C_ProgressNeeded) {
													pInfo(cp_)->C_QuestProgress = pInfo(cp_)->C_ProgressNeeded;
													VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "`9Ring Quest task complete! Go tell the Ringmaster!", 0, 0);
												}
											}
											if (Inventory::Modify(cp_, item_, c_) != 0) {
												std::string name_ = pInfo(cp_)->world;
												auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
												if (it != worlds.end()) {
													World* world_ = &(*it);
													world_->fresh_world = true;
													WorldDrop drop_block_{};
													drop_block_.id = item_, drop_block_.count = 1, drop_block_.x = pInfo(cp_)->x + rand() % 17, drop_block_.y = pInfo(cp_)->y + rand() % 17;
													VisualHandle::Drop(world_, drop_block_);
												}
											}
											VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "I found `21 " + items[item_].name + "``!" + (hands_ == 2558 ? " But now I lost it in my basket!" : "") + "", 0, 0);
											PlayerMoving data_{};
											data_.packetType = 19, data_.plantingTree = 0, data_.netID = 0;
											data_.punchX = item_;
											data_.x = pInfo(cp_)->x + 10, data_.y = pInfo(cp_)->y + 16;
											int32_t to_netid = pInfo(cp_)->netID;
											BYTE* raw = packPlayerMoving(&data_);
											raw[3] = 5;
											Memory_Copy(raw + 8, &to_netid, 4);
											for (ENetPeer* cp_2 = server->peers; cp_2 < &server->peers[server->peerCount]; ++cp_2) {
												if (cp_2->state != ENET_PEER_STATE_CONNECTED or cp_2->data == NULL) continue;
												if (pInfo(cp_2)->world == pInfo(cp_)->world) {
													send_raw(cp_2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
													VarList::OnConsoleMessage(cp_2, get_player_nick(cp_) + " found `21 " + items[item_].name + "``!");
												}
											}
											delete[]raw;
										}
										CAction::Effect(cp_, 48, (float)pInfo(cp_)->x + 10, (float)pInfo(cp_)->y + 16);
									}
								}
							}
						}
					}
					if (pInfo(cp_)->text_time - ms_time <= 0) {
						if (pInfo(cp_)->show_pets and pInfo(cp_)->RandomSentences) {
							for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
								if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL || pInfo(cp_)->world.empty()) continue;
								if (pInfo(cp_)->world == pInfo(cp_)->world) {
									best_quote = Environment()->random_[rand() % Environment()->random_.size()];
									VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[W]_ `6<`w" + pInfo(cp_)->pet_name + "`6> " + best_quote + "");
									VarList::OnTalkBubble(cp_, pInfo(cp_)->pet_netID, best_quote, 2, 0);
								}
							}
						}
					}
					if (pInfo(cp_)->text_time - ms_time <= 0) pInfo(cp_)->text_time = ms_time + 500000;
					if (pInfo(cp_)->save_time + 300000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						if (pInfo(cp_)->save_time != 0) {
							pInfo(cp_)->opc++;
							if (pInfo(cp_)->show_pets and pInfo(cp_)->pet_level >= 40) {
								pInfo(cp_)->opc += 5;
								VarList::OnTalkBubble(cp_, pInfo(cp_)->pet_netID, "Received `25`` Opc");
							}
							if (pInfo(cp_)->hand == 10384) pInfo(cp_)->opc += 2;
							if (pInfo(cp_)->gp || pInfo(cp_)->hand == 10384 || pInfo(cp_)->hair == 9542 || pInfo(cp_)->hair == 9984 || pInfo(cp_)->hair == 9920 || pInfo(cp_)->necklace == 9964 || pInfo(cp_)->necklace == 10176 || pInfo(cp_)->pants == 9782 || pInfo(cp_)->hand == 9880 || pInfo(cp_)->hand == 10020 || pInfo(cp_)->hand == 9974 || pInfo(cp_)->hand == 9918 || pInfo(cp_)->hand == 10290 || pInfo(cp_)->hand == 9916 || pInfo(cp_)->hand == 9914 || pInfo(cp_)->hand == 9766 || pInfo(cp_)->hand == 9772 || pInfo(cp_)->hand == 9908) pInfo(cp_)->opc++;
							for (int i_ = 0; i_ < world_rating.size(); i_++) {
								if (world_rating[i_].name == pInfo(cp_)->world) ServerPool::Honors::Add(pInfo(cp_)->world, pInfo(cp_)->world_owner);
							}
							if (pInfo(cp_)->EarnFreeGems.Quest_2 < 60) pInfo(cp_)->EarnFreeGems.Quest_2 += 5;
							Looping::Events(cp_);
							ServerPool::Top_Player::Add(to_lower(pInfo(cp_)->tankIDName));
						}
						pInfo(cp_)->save_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					if (pInfo(cp_)->World_Timed != 0 and pInfo(cp_)->WorldTimed) {
						std::string name_ = pInfo(cp_)->world;
						auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (it != worlds.end()) {
							World* world_ = &(*it);
							if (to_lower(world_->owner_name) != to_lower(pInfo(cp_)->tankIDName)) {
								if (pInfo(cp_)->World_Timed - time(nullptr) == 60 && pInfo(cp_)->WorldTimed) {
									VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "Your access to this world will expire in less than a minute!", 0, 0);
								}
								else if (pInfo(cp_)->World_Timed - time(nullptr) < 0 && pInfo(cp_)->WorldTimed) {
									VarList::OnTalkBubble(cp_, pInfo(cp_)->netID, "Your access to this world has expired!", 0, 0);
									Exit_World(cp_);
								}
							}
						}
					}
					if (pInfo(cp_)->fishing_used != 0) {
						if (pInfo(cp_)->last_fish_catch + pInfo(cp_)->fish_seconds < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() && rand() % 100 < (pInfo(cp_)->hand == 6258 ? 20 : pInfo(cp_)->hand == 3010 ? 15 : 10)) {
							PlayerMoving data_{};
							data_.packetType = 17, data_.netID = 34, data_.YSpeed = 34, data_.x = pInfo(cp_)->f_x * 32 + 16, data_.y = pInfo(cp_)->f_y * 32 + 16;
							pInfo(cp_)->last_fish_catch = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
							BYTE* raw = packPlayerMoving(&data_);
							for (ENetPeer* cp__event = server->peers; cp__event < &server->peers[server->peerCount]; ++cp__event) {
								if (cp__event->state != ENET_PEER_STATE_CONNECTED or cp__event->data == NULL or pInfo(cp__event)->world != pInfo(cp_)->world) continue;
								send_raw(cp__event, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
								CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/splash.wav", 0);
							}
							delete[] raw;
							if (pInfo(cp_)->cheater_settings & SETTINGS::SETTINGS_16 && pInfo(cp_)->disable_cheater == 0) {
								int bait = pInfo(cp_)->fishing_used, fx = pInfo(cp_)->f_x, fy = pInfo(cp_)->f_y;
								stop_fishing(cp_, false, "");
								PlayerCharacter::Punch(cp_, bait, fx, fy, fx * 32, fy * 32);
							}
						}
					}
					long long time_ = time(nullptr);
					for (int i_ = 0; i_ < pInfo(cp_)->playmods.size(); i_++) {
						if (pInfo(cp_)->playmods[i_].id == 12) {
							if (pInfo(cp_)->valentine_time + 2500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
								pInfo(cp_)->valentine_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
								for (ENetPeer* valentine = server->peers; valentine < &server->peers[server->peerCount]; ++valentine) {
									if (valentine->state != ENET_PEER_STATE_CONNECTED or valentine->data == NULL) continue;
									if (pInfo(valentine)->world == pInfo(cp_)->world and pInfo(valentine)->tankIDName == pInfo(cp_)->playmods[i_].user) {
										if (not pInfo(valentine)->invis and not pInfo(cp_)->invis and pInfo(cp_)->x != -1 and pInfo(cp_)->y != -1 and pInfo(valentine)->x != -1 and pInfo(valentine)->y != -1) {
											gamepacket_t p;
											p.Insert("OnParticleEffect");
											p.Insert(13);
											p.Insert((float)pInfo(valentine)->x + 10, (float)pInfo(valentine)->y + 16);
											p.Insert((float)0), p.Insert((float)pInfo(cp_)->netID);
											bool double_send = false;
											for (int i_2 = 0; i_2 < pInfo(valentine)->playmods.size(); i_2++) {
												if (pInfo(valentine)->playmods[i_2].id == 12 and pInfo(valentine)->playmods[i_2].user == pInfo(cp_)->tankIDName) {
													double_send = true;
													break;
												}
											}
											gamepacket_t p2;
											p2.Insert("OnParticleEffect");
											p2.Insert(13);
											p2.Insert((float)pInfo(cp_)->x + 10, (float)pInfo(cp_)->y + 16);
											p2.Insert((float)0), p2.Insert((float)pInfo(valentine)->netID);
											for (ENetPeer* valentine_bc = server->peers; valentine_bc < &server->peers[server->peerCount]; ++valentine_bc) {
												if (valentine_bc->state != ENET_PEER_STATE_CONNECTED or valentine_bc->data == NULL) continue;
												if (pInfo(valentine_bc)->world == pInfo(cp_)->world) {
													p.CreatePacket(valentine_bc);
													if (double_send) p2.CreatePacket(valentine_bc);
												}
											}
										}
										break;
									}
								}
							}
						}
						if (pInfo(cp_)->playmods[i_].time - time_ < 0) {
							if (pInfo(cp_)->playmods[i_].id == 162) {
								VarList::OnCountdownEnd(cp_, pInfo(cp_)->netID);
								Exit_World(cp_);
							}
							if (pInfo(cp_)->playmods[i_].id == 125) {
								pInfo(cp_)->Role.Moderator = false;
								if (not pInfo(cp_)->d_name.empty()) {
									pInfo(cp_)->d_name = "";
									VisualHandle::Nick(cp_, NULL);
								}
							}
							else if (pInfo(cp_)->playmods[i_].id == 126) pInfo(cp_)->Role.Vip = false;
							else if (pInfo(cp_)->playmods[i_].id == 127 || pInfo(cp_)->playmods[i_].id == 128) Exit_World(cp_);
							else if (pInfo(cp_)->playmods[i_].id == 136) pInfo(cp_)->hit_by = 0;
							else if (pInfo(cp_)->playmods[i_].id == 143) {
								pInfo(cp_)->Role.Cheats = false;
								pInfo(cp_)->cheater_settings = 0;
								autofarm_status(cp_);
							}
							CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/dialog_confirm.wav", 0);
							VarList::OnConsoleMessage(cp_, info_about_playmods[pInfo(cp_)->playmods[i_].id - 1][5] + " (`$" + info_about_playmods[pInfo(cp_)->playmods[i_].id - 1][3] + "`` mod removed)");
							pInfo(cp_)->playmods.erase(pInfo(cp_)->playmods.begin() + i_);
							Clothing_V2::Update_Value(cp_);
							Clothing_V2::Update(cp_);
							break;
						}
					}
				}
				if (Environment()->Last_Time - ms_time <= 0) Environment()->Last_Time = ms_time + 2500;
				if (Environment()->Last_Firehouse - ms_time <= 0) Environment()->Last_Firehouse = ms_time + 2000000;
				if (Environment()->Last_Fire_Time - ms_time <= 0) Environment()->Last_Fire_Time = ms_time + 2000000;
			}
		}
	}
	static void autofarm() {
		long long ms_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		if (Environment()->Last_Autofarm - ms_time <= 0) {
			if (Environment()->Last_Autofarm - ms_time <= 0) Environment()->Last_Autofarm = ms_time + Environment()->AutoFarm_Delay;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL || pInfo(cp_)->world.empty()) continue;
				if (pInfo(cp_)->cheater_settings & SETTINGS::SETTINGS_0 && pInfo(cp_)->disable_cheater == 0) {
					if (pInfo(cp_)->last_used_block != 0 && pInfo(cp_)->autofarm_x != -1) {
						for (int i = 0; i < pInfo(cp_)->autofarm_slot; i++) {
							PlayerCharacter::Punch(
								cp_,
								pInfo(cp_)->last_used_block,
								pInfo(cp_)->autofarm_x + (pInfo(cp_)->backwards ? i * -1 : i),
								pInfo(cp_)->autofarm_y,
								pInfo(cp_)->x,
								pInfo(cp_)->y,
								true
							);
						}
					}
				}
			}
		}
	}
};
void Detected() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		Looping::Worlds();
	}
}
void autofarmdelay() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(Environment()->AutoFarm_Delay));
		Looping::autofarm();
	}
}
class Login_Detect {
private:
	std::unordered_map<std::string, int> loginAttempts;
	chrono::steady_clock::time_point lastCheckTime;
public:
	Login_Detect() {
		lastCheckTime = chrono::steady_clock::now();
	}
	void LoginAttempt(ENetPeer* peer, std::string& ipAddress) {
		if (Environment()->Anti_Proxy) {
			if (CheckProxyAndVpn(ipAddress)) {
				Logger::Info("WARNING", "The IP address [" + ipAddress + "] is associated with a Proxy or Vpn.");
				SystemPool::FailedLogin(peer, "`4Sorry, The IP address [" + ipAddress + "] is associated with a Proxy or Vpn.");
				return;
			}
		}
		//if (ipAddress == "127.0.0.1") {
			//SystemPool::FailedLogin(peer, "`oEnjoying a free proxy?");
			//return;
		//}
		if (find(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), ipAddress) != Environment()->Rid_Bans.end()) {
			SystemPool::FailedLogin(peer, "`4Sorry, this account (`5" + ipAddress + "`4) has been suspended. Visit `5" + Environment()->discord_url + "`` `4if you have any questions.", "`5Join Discord Server");
			return;
		}
		auto now = chrono::steady_clock::now();
		auto elapsedTime = chrono::duration_cast<chrono::seconds>(now - lastCheckTime).count();
		if (elapsedTime >= 60) {
			loginAttempts.clear();
			lastCheckTime = now;
		}
		loginAttempts[ipAddress]++;
		if (loginAttempts[ipAddress] > 5) {
			Logger::Info("WARNING", "Login spam attacks from ip addresses: " + ipAddress + "!");
			SystemPool::FailedLogin(peer, "`o[ANTI-SPAM] Please wait 5 seconds before logging on again.");
		}
	}
};
int main(int argc, char** argv[]) {
	load_blocked_items();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleTitleA("gtps");
	srand(unsigned int(time(nullptr)));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleOutputCP(CP_UTF8);
	DWORD mode; SMALL_RECT rect;
	rect.Left = 0, rect.Top = 0, rect.Right = 120, rect.Bottom = 40;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	std::string licenseKey = readLicenseFromFile(), password;
	if (licenseKey.empty() or licenseKey != Environment()->Server_Password) {
		Logger::Info("ERROR", "No valid license key. Application cannot run.");
		return EXIT_FAILURE;
	}
	/*
	const char* message = "Welcome to Growtopia Private Server 1.1 (C++), Development By Tianvan.\n"
		"\n"
		"Based on GTPS3 Source.\n\n"
		"We are dedicated to providing a secure and reliable service tailored to your needs.\n"
		"Your trust and feedback inspire us to continuously improve and introduce new features.\n"
		"Should you encounter any issues or have suggestions, feel free to contact our support team.\n"
		"and look forward to serving you better.\n";
	const char* title = "Growtopia Private Server. - @Tianvan";
	MessageBoxA(NULL, message, title, MB_OK | MB_ICONINFORMATION);
	*/
	Loading_Screen(50);
	clearScreen();
	Logger::Info("INFO", "(C) gtps");
	//Logger::Info("INFO", "Starting up server, this might take a while...");
	//Logger::Info("INFO", "Initializing server...");
	#ifdef _WIN32
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	std::signal(SIGSEGV, ServerPool::Auto_Save), std::signal(SIGABRT, ServerPool::Auto_Save);
#elif defined(__linux__)
	signal(SIGINT, ConsoleHandler);
	signal(SIGTERM, ConsoleHandler);
#endif
	Environment()->Server_Port = 17091;
	Environment()->UpTime = time(nullptr);
	if (Enet_Server()->Initialize(Environment()->Server_Port) == -1) {
		Logger::Info("ERROR", "Failed to Initialize ENet, Terminating the Server...");
		return EXIT_FAILURE;
	}
	//Logger::Info("INFO", "Loading items.dat...");
	ItemDataUtils::loadLinux(),ItemDataUtils::loadIOS();
	if (ItemManager()->Serialize() == -1) {
		Logger::Info("ERROR", "Failed to load items.dat, please make sure the file is on '/database'");
		return EXIT_FAILURE;
	}
	else Logger::Info("INFO", "Succesfully loaded Items.dat | Version: 19 | Hash: " + to_string(Environment()->ItemsDat_Hash) + " | Total Items: " + Set_Count(items.size()) + "");
	//Logger::Info("INFO", "Enet Initialized succesfully");
	//Logger::Info("INFO", "Loading server statistics...");
	EventPool::Load::All();
	Action::Action_Map(), Dialog_Return::Dialog(), Server_Pool::Events(), Commands::Command();
	Logger::Info("INFO", "Succesfully registered all actions, dialog return | Total Action: " + Set_Count(actionMap.size()) + " | Total Dialog Return: " + Set_Count(dialogMap.size()) + "");
	Logger::Info("INFO", "Succesfully registered all commands | Total Commands: " + Set_Count(commandMap.size()));
	//Logger::Info("INFO", "All configuration has been succesfully loaded");
	Logger::Info("INFO", "" + Environment()->server_name + " V" + Environment()->server_version + " - is now listening at " + Environment()->server_ip + ":" + to_string(Environment()->Server_Port) + " | Date: " + currentDateTime());
	Environment()->Threads.emplace_back(std::thread(Detected));
	Environment()->Threads.emplace_back(std::thread(autofarmdelay));
	Environment()->Threads.emplace_back(std::thread(ServerPool::SaveDatabase::All));
	//Environment()->Threads.emplace_back(std::thread(SystemPool::ServerInputPlugin));
	ENetEvent Event_Pool;
	while (true) {
		while (enet_host_service(server, &Event_Pool, 1000) > 0) {
			if (Environment()->Auto_Saving) continue;
			ENetPeer* peer = Event_Pool.peer;
			if (!Event_Pool.peer) continue;
			switch (Event_Pool.type) {
			case ENET_EVENT_TYPE_NONE: {
				break;
			}
			case ENET_EVENT_TYPE_CONNECT: {
				if (ServerPool::PlayerCountServer() >= 520) {
					SystemPool::FailedLogin(peer, "`oServer is at MAX capacity. Please click `5CANCEL `oand try again in a few seconds.``");
					break;
				}
				char clientConnection[16];
				enet_address_get_host_ip(&peer->address, clientConnection, 16);
				peer->data = new Player;
				send_(peer, 1, nullptr, 0);
				pInfo(peer)->ip = clientConnection, pInfo(peer)->id = peer->connectID;
				int count = 0;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (cp_->address.host == peer->address.host) count++;
				}
				if (count > 3) {
					SystemPool::FailedLogin(peer, "`4SERVER PROTECTION!`o: Please disable proxy or GTBot, before connecting to `6" + Environment()->server_name + "`o.````");
					break;
				}
				Login_Detect Monitor;
				Monitor.LoginAttempt(peer, pInfo(peer)->ip);
				VarList::OnConsoleMessage(peer, "`oConnecting to `2" + Environment()->server_name + " Private Server...");
				VarList::OnConsoleMessage(peer, "`oYour Ping : `2" + to_string(peer->roundTripTime) + "Ms");
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT: {
				if (!Event_Pool.peer->data) break;
				if (peer->data != NULL) {
					if (pInfo(peer)->world != "") Exit_World(peer);
					if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
					pInfo(peer)->in_enter_game = true;
					ServerPool::SaveDatabase::Players(pInfo(peer), true);
					delete Event_Pool.peer->data;
					Event_Pool.peer->data = NULL;
				}
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE: {
				if (peer->data == NULL) continue;
				if (peer->incomingDataTotal >= 25000) {
					VarList::OnConsoleMessage(peer, "`oWarning from `4System`o: Unusual packet detected");
					Peer_Disconnect(peer, 0);
				}
				if (Event_Pool.packet->dataLength < 0x4 || Event_Pool.packet->dataLength > 0x400) break;
				switch (GetMessageTypeFromPacket(Event_Pool.packet)) {
				case NET_MESSAGE_GENERIC_TEXT: {
					std::string cch = GetTextPointerFromPacket(Event_Pool.packet);
					SystemPool::SaveCchLogs(cch);
					if (not isASCII(cch) || cch.find("action|getDRAnimations") != string::npos || cch.find("action|refresh_player_tribute_data") != string::npos) {
						enet_packet_destroy(Event_Pool.packet);
						continue;
					}
					if (pInfo(peer)->packetSent.lastActionSent == 0) {
						pInfo(peer)->packetSent.lastActionSent = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() + 1000;
					}
					if (pInfo(peer)->packetSent.lastActionSent >= (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->packetSent.totalActionSent++;
					}
					else {
						pInfo(peer)->packetSent.totalActionSent = 0, pInfo(peer)->packetSent.lastActionSent = 0;
					}
					if (pInfo(peer)->packetSent.totalActionSent >= 10) {
						pInfo(peer)->Account_Notes.push_back("`o" + currentDateTime() + ": >> Flagged for Spam (in " + pInfo(peer)->world + ") Type: (FLAGGED AS: SPAM PACKET) (Code 1)");
						VarList::OnConsoleMessage(peer, "`7Your client sending too many packets. attempt to reconnect");
						ServerPool::SaveDatabase::Players(pInfo(peer), true);
						Peer_Disconnect(peer, 0);
						if (peer->data != NULL) {
							delete Event_Pool.peer->data;
							Event_Pool.peer->data = NULL;
						}
					}
					ServerLogsPkt.theCCH = currentDateTime() + " [NAME] " + pInfo(peer)->tankIDName + " [IP ADDRESS] " + pInfo(peer)->ip + " [EVENT TYPE] " + to_string(Event_Pool.type) + " [EVENT PACKET TYPE] " + to_string(GetMessageTypeFromPacket(Event_Pool.packet)) + " [TEXT POINTER] " + cch;
					if (not pInfo(peer)->Has_Login) {
						replaceAll(cch, "/p", "\n");
						SystemPool::PlayerLogin(peer, cch);
						break;
					}
					TextScanner parser(cch);
					std::string action = "";
					if (parser.try_get("action", action)) {
						if (actionMap.find(action) != actionMap.end()) {
							actionMap[action](peer, cch);
						}
						else {
							const seconds cooldownDuration(5);
							auto now = steady_clock::now();
							if (duration_cast<seconds>(now - pInfo(peer)->lastPacketTime) < cooldownDuration) {
								VarList::OnAddNotification(peer, "`wWarning from `4System`w: You were `4DETECTED`` using a script!", "interface/atomic_button.rttex", "audio/hub_open.wav");
								Peer_Disconnect(peer, 0);
								break;
							}
							pInfo(peer)->lastPacketTime = now;
							Logger::Info("WARNING", "Unhandle NET_MESSAGE_GENERIC_TEXT -> : [" + cch + "] Sent by " + pInfo(peer)->tankIDName);
							SystemPool::SaveLogsUnhandle_Packet("NET_MESSAGE_GENERIC_TEXT -> : [" + cch + "] Sent by " + pInfo(peer)->tankIDName);
						}
						break;
					}
				}
				case NET_MESSAGE_GAME_MESSAGE: {
					if (pInfo(peer)->bypass == false) {
						pInfo(peer)->Account_Notes.push_back("`o" + currentDateTime() + ": >> Flagged for Hacking Type: (FLAGGED AS: PACKET BYPASS) (Code 2)");
						Peer_Reset(peer);
						break;
					}
					std::string cch = GetTextPointerFromPacket(Event_Pool.packet);
					ServerLogsPkt.packet_logs = currentDateTime() + " " + pInfo(peer)->tankIDName + " [" + pInfo(peer)->requestedName + "] ip [" + pInfo(peer)->ip + "] " + to_string(peer->address.host) + ": " + cch;					
					if (pInfo(peer)->AccountSecured && pInfo(peer)->fa_ip != pInfo(peer)->ip or pInfo(peer)->tankIDName.empty() && explode("\n", cch)[0] == "action|join_request") {
						VarList::OnFailedToEnterWorld(peer);
						break;
					}
					TextScanner parser(cch);
					std::string action;
					if (parser.try_get("action", action)) {
						if (actionMap.find(action) != actionMap.end()) {
							actionMap[action](peer, cch);
						}
						else {
							const seconds cooldownDuration(5);
							auto now = steady_clock::now();
							if (duration_cast<seconds>(now - pInfo(peer)->lastPacketTime) < cooldownDuration) {
								VarList::OnAddNotification(peer, "`wWarning from `4System`w: You were `4DETECTED`` using a script!", "interface/atomic_button.rttex", "audio/hub_open.wav");
								Peer_Disconnect(peer, 0);
								break;
							}
							pInfo(peer)->lastPacketTime = now;
							Logger::Info("WARNING", "Unhandle NET_MESSAGE_GAME_MESSAGE -> [" + cch + "] Sent by " + pInfo(peer)->tankIDName);
							SystemPool::SaveLogsUnhandle_Packet("NET_MESSAGE_GAME_MESSAGE -> [" + cch + "] Sent by " + pInfo(peer)->tankIDName);
						}
						break;
					}
					break;
				}
				case NET_MESSAGE_GAME_PACKET: {
					if (pInfo(peer)->tankIDName.empty() || pInfo(peer)->world.empty() || pInfo(peer)->world == "EXIT") break;
					BYTE* tankUpdatePacket = GetStructPointerFromTankPacket(Event_Pool.packet);
					if (tankUpdatePacket == nullptr) break;
					PlayerMoving* pMov = unpackPlayerMoving(tankUpdatePacket);
					int tidown = 25, todc = 15;
					if (pInfo(peer)->lpps24 + tidown < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
						pInfo(peer)->pps24 = 0;
						pInfo(peer)->lpps24 = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					}
					else {
						pInfo(peer)->pps24++;
						if (pInfo(peer)->pps24 >= 20) {
							if (pMov->packetType == 11) todc = 200;
							if (pMov->packetType == 0 && (pMov->characterState == 16416 or pMov->characterState == 16512 or pMov->characterState == 16384 or pMov->characterState == 16400 or pMov->characterState == 16432 or pMov->characterState == 16528)) todc = 200;
							if (pInfo(peer)->pps24 >= todc) {
								pInfo(peer)->Account_Notes.push_back("`o" + currentDateTime() + ": >> Flagged for Spam (in " + pInfo(peer)->world + ") Type: (FLAGGED AS: SPAM PACKET) (Code 3)");
								VarList::OnConsoleMessage(peer, "`7Your client sending too many packets. attempt to reconnect");
								ServerPool::SaveDatabase::Players(pInfo(peer), true);
								Peer_Disconnect(peer, 0);
								if (peer->data != NULL) {
									delete Event_Pool.peer->data;
									Event_Pool.peer->data = NULL;
								}
							}
							break;
						}
					}
					ServerLogsPkt.packet_type = "[PACKET TYPE]: " + to_string(pMov->packetType), ServerLogsPkt.last_world = pInfo(peer)->world;
					if (eventMap.find(pMov->packetType) != eventMap.end()) {
						eventMap[pMov->packetType](peer, pMov);
					}
					else {
						const seconds cooldownDuration(5);
						auto now = steady_clock::now();
						if (duration_cast<seconds>(now - pInfo(peer)->lastPacketTime) < cooldownDuration) {
							VarList::OnAddNotification(peer, "`wWarning from `4System`w: You were `4DETECTED`` using a script!", "interface/atomic_button.rttex", "audio/hub_open.wav");
							Peer_Disconnect(peer, 0);
							break;
						}
						pInfo(peer)->lastPacketTime = now;
						Logger::Info("WARNING", "unhandled EVENT_TYPE_GAME_PACKET -> [" + to_string(pMov->packetType) + "] Sent by " + pInfo(peer)->tankIDName);
						SystemPool::SaveLogsUnhandle_Packet("EVENT_TYPE_GAME_PACKET -> [" + to_string(pMov->packetType) + "] Sent by " + pInfo(peer)->tankIDName);
					}
					if (pMov != NULL) delete pMov;
					break;
				}
				default:
					Logger::Info("WARNING", "Unhandled ENET_EVENT_TYPE_RECEIVE ->  [" + to_string(GetMessageTypeFromPacket(Event_Pool.packet)) + "] Sent by " + pInfo(peer)->tankIDName);
					break;
				}
				enet_packet_destroy(Event_Pool.packet);
				break;
			}
			default:
				Logger::Info("INFO", "Unhandle ENETEVENT -> [" + to_string(Event_Pool.type) + "] Sent by " + pInfo(peer)->tankIDName);
				SystemPool::SaveLogsUnhandle_Packet("ENETEVENT -> [" + to_string(Event_Pool.type) + "] Sent by " + pInfo(peer)->tankIDName);
				break;
			}
		}
	}
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}