#pragma once
#include <string>
#include "UcihaVallen/Handle/WorldInfo.h"
#include "UcihaVallen/Commands/Commands.h"

class Action {
public:
	static void Action_Map() {
		actionMap["input"] = Action::input,
			actionMap["refresh_item_data"] = Action::refresh_item_data,
			actionMap["enter_game"] = Action::Enter_Game,
			actionMap["wrench"] = Action::wrench,
			actionMap["mod_trade"] = Action::Mod_Trade,
			actionMap["rem_trade"] = Action::Rem_Trade,
			actionMap["trade_accept"] = Action::trade_accept,
			actionMap["trade_cancel"] = Action::trade_cancel,
			actionMap["trade_check_price"] = Action::trade_check_price,
			actionMap["setRoleIcon"] = Action::SetRole,
			actionMap["setRoleSkin"] = Action::SetRole,
			actionMap["setSkin"] = Action::setSkin,
			actionMap["drop"] = Action::drop,
			actionMap["trash"] = Action::trash,
			actionMap["info"] = Action::info,
			actionMap["halloweenquestpopup"] = Action::halloweenquestpopup,
			actionMap["warp_player_into_halloween_world"] = Action::warp_player_into_halloween_world,
			actionMap["rt_grope_gem_halloween_bundle"] = Action::rt_grope_gem_halloween_bundle,
			actionMap["valentine_valuepack"] = Action::valentine_valuepack,
			actionMap["valentine_starterpack"] = Action::valentine_starterpack,
			actionMap["winterfest_eventpack"] = Action::winterfest_eventpack,
			actionMap["winterrallymenu"] = Action::winterrallymenu,
			actionMap["winter_bingo_ui"] = Action::winter_bingo_ui,
			actionMap["royalwinterseals"] = Action::royalwinterseals,
			actionMap["opengachasystem"] = Action::opengachasystem,
			actionMap["growpass"] = Action::growpass,
			actionMap["assets_shop"] = Action::assets_shop,
			actionMap["buy_growpass"] = Action::assets_shop,
			actionMap["marketplace"] = Action::marketplace,
			actionMap["showphoenixreturns"] = Action::showphoenixreturns,
			actionMap["buy"] = Action::buy,
			actionMap["killstore"] = Action::killstore,
			actionMap["respawn"] = Action::respawn,
			actionMap["respawn_spike"] = Action::respawn,
			actionMap["validate_world"] = Action::validate_world,
			actionMap["inventoryfavuitrigger"] = Action::inventoryfavuitrigger,
			actionMap["itemfavourite"] = Action::itemfavourite,
			actionMap["store"] = Action::store,
			actionMap["communitytabs"] = Action::communitytabs,
			actionMap["dailychallengemenu"] = Action::dailychallengemenu,
			actionMap["iotm_shop"] = Action::iotm_shop,
			actionMap["opc_shop"] = Action::opc_shop,
			actionMap["storenavigate"] = Action::storenavigate,
			actionMap["eventmenu"] = Action::eventmenu,
			actionMap["openeventmenu"] = Action::eventmenu,
			actionMap["showredeemcodewindow"] = Action::showredeemcodewindow,
			actionMap["friends"] = Action::friends,
			actionMap["handle_gems_shop"] = Action::handle_gems_shop,
			actionMap["openPiggyBank"] = Action::openPiggyBank,
			actionMap["openPageFreeGems"] = Action::openPageFreeGems,
			actionMap["showdungeonsui"] = Action::showdungeonsui,
			actionMap["leaderboardBtnClicked"] = Action::leaderboardBtnClicked,
			actionMap["euphoriaBtnClicked"] = Action::euphoriaBtnClicked,
			actionMap["quit"] = Action::quit,
			actionMap["quit_to_exit"] = Action::quit_to_exit,
			actionMap["gohomeworld"] = Action::gohomeworld,
			actionMap["join_request"] = Action::join_request,
			actionMap["world_button"] = Action::world_button,
			actionMap["trade_started"] = Action::trade_started,
			actionMap["dialog_return"] = Action::dialog_return;
	}
private:
	static void input(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 4) return;
		std::string msg = explode("\n", t_[3])[0];
		if (msg.length() <= 0 || msg.length() > 120 || msg.empty() || std::all_of(msg.begin(), msg.end(), [](char c) {return std::isspace(c); })) return;
		for (char c : msg) if (c < 0x20 || c>0x7A) continue;
		space_(msg);
		if (pInfo(peer)->tankIDName.empty() || pInfo(peer)->world.empty() || msg[0] == '`' and msg.size() <= 2) return;
		if (msg.starts_with('/')) {
			Commands::Execute(peer, msg);
		}
		else chat_message(peer, msg);
	}
	static void refresh_item_data(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->bypass) {
			VarList::OnConsoleMessage(peer, "`oOne moment, updating item data...");
			enet_peer_send(peer, 0, enet_packet_create(Environment()->ItemsDat, static_cast<size_t>(Environment()->ItemsDat_Size) + 60, ENET_PACKET_FLAG_RELIABLE));
			enet_host_flush(server);
		}
	}
	static void Enter_Game(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->bypass and !pInfo(peer)->in_enter_game) {
			pInfo(peer)->in_enter_game = true;
			Playmods::HasById(pInfo(peer), 76, 1);
			pInfo(peer)->name_color = Role::Prefix(peer);
			int on_ = 0;
			std::vector<std::string> friends_;
			for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) friends_.emplace_back(to_lower(pInfo(peer)->friends[c_].name));
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(peer)->guild_id != 0) {
					if (pInfo(peer)->guild_id == pInfo(cp_)->guild_id) {
						if (pInfo(peer)->tankIDName == pInfo(cp_)->tankIDName) continue;
						VarList::OnConsoleMessage(cp_, "`5GUILD ALERT:`` " + pInfo(peer)->tankIDName + " has `2logged on``.");
					}
				}
				if (find(friends_.begin(), friends_.end(), to_lower(pInfo(cp_)->tankIDName)) != friends_.end()) {
					if (not pInfo(peer)->invis and not pInfo(peer)->m_h) {
						if (pInfo(cp_)->show_friend_notifications_) {
							CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/friend_logon.wav", 0);
							VarList::OnConsoleMessage(cp_, "`3FRIEND ALERT:`` " + pInfo(peer)->tankIDName + " has `2logged on``.");
						}
					}
					on_++;
				}
			}
			if (pInfo(peer)->Fav_Items.size() != 0) {
				std::vector<std::string> Fav_Item_List;
				for (int i = 0; i < pInfo(peer)->Fav_Items.size(); i++) Fav_Item_List.emplace_back(to_string(pInfo(peer)->Fav_Items[i]));
				VarList::OnSendFavItemsList(peer, join(Fav_Item_List, ","), 20);
			}
			PlayerCharacter::Reset(peer);
			form_emoji(peer);
			VarList::OnSetVouchers(peer);
			Inventory::Visuals(peer);
			Clothing_V2::Update_Value(peer);
			Clothing_V2::Update_Value(peer, true);
			if (pInfo(peer)->playtime_items.size() < 5 and not pInfo(peer)->tankIDName.empty()) {
				int hours_ = ((time(NULL) - pInfo(peer)->playtime) + pInfo(peer)->seconds) / 3600, delay = 0;
				if (hours_ > 300) {
					for (int i = 0; i < Environment()->play_items.size(); i++) {
						if (find(pInfo(peer)->playtime_items.begin(), pInfo(peer)->playtime_items.end(), Environment()->play_items[i].first) == pInfo(peer)->playtime_items.end() && hours_ >= Environment()->play_items[i].second) {
							int get_him = 1;
							if (Inventory::Modify(peer, Environment()->play_items[i].first, get_him) == 0) {
								pInfo(peer)->playtime_items.emplace_back(Environment()->play_items[i].first);
								VarList::OnAddNotification(peer, "You've unlocked `$" + items[Environment()->play_items[i].first].ori_name + "``!", "interface/large/friend_button.rttex", "audio/hub_open.wav");
								VarList::OnConsoleMessage(peer, "You've unlocked `$" + items[Environment()->play_items[i].first].ori_name + "``!", 0, delay);
								delay += 2000;
							}
						}
					}
				}
			}
			if (WinterFest.Active) {
				VarList::OnEventButtonDataSet(peer, "BingoButton", 1, "{\"active\":true,\"buttonAction\":\"winter_bingo_ui\",\"buttonState\":0,\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"BingoButton\",\"notification\":0,\"order\":4,\"rcssClass\":\"wf-bingo\",\"text\":\"\"}");
				VarList::OnEventButtonDataSet(peer, "WinterRallyButton", 1, "{\"active\":true,\"buttonAction\":\"winterrallymenu\",\"buttonState\":0,\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"WinterRallyButton\",\"notification\":0,\"order\":5,\"rcssClass\":\"winter-rally\",\"text\":\"\"}");
			}
			if (Event()->Anniversary) {
				EventPool::Load::Anniversary_Leaderboard();
				VarList::OnEventButtonDataSet(peer, "AnniversaryLeaderboardButton", 1, "{\"active\":true,\"buttonAction\":\"leaderboardBtnClicked\",\"buttonState\":1,\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"AnniversaryLeaderboardButton\",\"notification\":0,\"order\":5,\"rcssClass\":\"anniversary-leaderboard\",\"text\":\"" + to_string(EventPool::Anniversary::Point::Get(peer)) + "\"}");
				VarList::OnEventButtonDataSet(peer, "AnniversaryEuphoriaButton", 1, "{\"active\":true,\"buttonAction\":\"euphoriaBtnClicked\",\"buttonState\":0,\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"AnniversaryEuphoriaButton\",\"notification\":0,\"order\":5,\"rcssClass\":\"anniversary-euphoria\",\"text\":\"0%\"}");
			}
			//VarList::OnEventButtonDataSet(peer, "ScrollsPurchaseButton", 1, "{\"active\":true,\"buttonAction\":\"showdungeonsui\",\"buttonState\":0,\"buttonTemplate\":\"DungeonEventButton\",\"counter\":20,\"counterMax\":20,\"itemIdIcon\":0,\"name\":\"ScrollsPurchaseButton\",\"notification\":0,\"order\":2,\"rcssClass\":\"scrollbank\",\"text\":\"0/20\"}");
			VarList::OnEventButtonDataSet(peer, "PiggyBankButton", 1, "{\"active\":true,\"buttonAction\":\"openPiggyBank\",\"buttonState\":" + a + (pInfo(peer)->Banked_Piggy >= 350000 ? "2" : "0") + ",\"buttonTemplate\":\"BaseEventButton\",\"counter\":0,\"counterMax\":0,\"itemIdIcon\":0,\"name\":\"PiggyBankButton\",\"notification\":0,\"order\":2,\"rcssClass\":\"piggybank\",\"text\":\"" + (pInfo(peer)->Banked_Piggy >= 350000 ? "350K" : ConvertToK(pInfo(peer)->Banked_Piggy) + "/350K") + "\"}");
			VarList::SetTapjoyTags(peer, "TJ4209834|");
			world_menu(peer);
			Daily_Challenge::DailyChallengeRequest(peer);
			if (pInfo(peer)->gp) {
				VarList::OnPaw2018SkinColor1Changed(peer, 1);
				VarList::OnPaw2018SkinColor2Changed(peer, 1);
				complete_gpass_task(peer, "Claim 4,000 gems");
			}
			else Playmods::HasById(pInfo(peer), 150, 1);
			if (not pInfo(peer)->tankIDName.empty()) {
				if (pInfo(peer)->tankIDPass.find_first_not_of("!\"#$€%&/{/[]}\`?:;><=*,.-|") != string::npos and pInfo(peer)->tankIDPass.length() < 5) {
					VarList::OnConsoleMessage(peer, "`4WARNING:  `oYour password is really easy to guess. Go to `#" + Environment()->website_url + " ``to change it!", false, 6000);
				}
				VarList::OnConsoleMessage(peer, "Welcome back to " + Environment()->server_name + ", `w" + get_player_nick(peer) + "``." + (pInfo(peer)->friends.size() == 0 ? "" : (on_ != 0 ? " `w" + to_string(on_) + "`` friend is online." : " No friends are online.")));
			}
			if (rolequest_day == 0) VarList::OnConsoleMessage(peer, "`3Today is Jack of all Trades Day!`` Your first Role quest will give 1 `2Growtoken`` and all Role quests will give 25% bonus points!");
			else if (rolequest_day == 1) VarList::OnConsoleMessage(peer, "`3Today is Fishing Day!`` Your first Fishing quest will give 1 `2Growtoken`` and all Fishing quests will give 25% bonus points!");
			else if (rolequest_day == 2) VarList::OnConsoleMessage(peer, "`3Today is Farming Day!`` Your first Farmer quest will give 1 `2Growtoken`` and all Farmer quests will give 25% bonus points!");
			else if (rolequest_day == 3) VarList::OnConsoleMessage(peer, "`3Today is Builder Day!`` Your first Builder quest will give 1 `2Growtoken`` and all Builder quests will give 25% bonus points!");
			else if (rolequest_day == 4) VarList::OnConsoleMessage(peer, "`3Today is Surgery Day!`` Your first Surgery quest will give 1 `2Growtoken`` and all Surgery quests will give 25% bonus points!");
			else if (rolequest_day == 5) VarList::OnConsoleMessage(peer, "`3Today is Geiger Day!`` Your first Geiger quest will give 1 `2Growtoken`` and all Geiger quests will give 25% bonus points!");
			else if (rolequest_day == 6) VarList::OnConsoleMessage(peer, "`3Today is Provider Day!`` Your first Provider quest will give 1 `2Growtoken`` and all Provider quests will give 25% bonus points!");
			if (Event()->Can_Event == false) {
				VarList::OnConsoleMessage(peer, "`3" + guild_event_type + " is here! ``Use " + items[event_item].name + " items to earn points. Hurry, it only lasts 8 days!");
				if (items[event_item].hand_scythe_text == "Block Bashers") VarList::OnConsoleMessage(peer, "`5Block Bashers! - This is not a drill! I repeat, this is not a drill! Get Your Block Bashers out, because Block Bashers is back!", false, 3500);
				if (items[event_item].hand_scythe_text == "Fishing Fanatics") VarList::OnConsoleMessage(peer, "`5Fishing Fanatics! - Get your anomarods ready as we are starting the Fishing Fanatics clash event!", false, 3500);
			}
			if (wait_event - time(nullptr) != 0 && Event()->Can_Event == true) VarList::OnConsoleMessage(peer, "`3*** " + guild_event_type + " has ended. `oYou have 4 days to claim your prizes!");
			if (Event()->Anniversary) VarList::OnConsoleMessage(peer, "`2" + Environment()->server_name + " is a year older!`` Get `5Double Bonus Golden Party Boxes`` for your money this week, and enjoy special party events!``");
			if (Event()->Xp_Event) VarList::OnConsoleMessage(peer, "`5***`` `9x" + to_string(Event()->X_Xp) + " Xp event is going on! Make sure to grab your farmables.");
			if (Event()->Gems_Event) VarList::OnConsoleMessage(peer, "`5***`` `9x" + to_string(Event()->X_Gems) + " Gems event is going on! Make sure to grab your farmables.");
			if (Event()->Exchange_Event) VarList::OnConsoleMessage(peer, "`5***`` `9x" + to_string(Event()->X_Exchange) + " Exchange event is going on! visit TRADE to Exchange your Items.");
			if (Event()->Valentine) VarList::OnConsoleMessage(peer, "`4Happy Valentine's Week!");
			if (Event()->Carnival) VarList::OnConsoleMessage(peer, "`2The Carnival has come to " + Environment()->server_name + "! `oCheck out the fun and games to the world `9CARNIVAL`o! Hurry, it only lasts 7 days!");
			if (Event()->Halloween) {
				VarList::OnConsoleMessage(peer, "`6It's `4Halloween!`` Visit the world `4GROWGANOTH`` to sacrifice your items to Almighty Growganoth!``");
				VarList::OnConsoleMessage(peer, "Growtopians have collectively released `22,147,483,647`` `9Corrupted Souls`` from the Tomb of Growganoth! Growganoth is pleased and unleashes the corrupted `2Tarantula Legs`` upon " + Environment()->server_name + "!");
			}
			if (Event()->Summerfest) VarList::OnConsoleMessage(peer, "`3Party down, it's `4Summerfest!`` Collect Fireworks and celebrate!``");
			if (WinterFest.Active) {
				VarList::OnConsoleMessage(peer, "`6It's `wWinterFest! `6Visit the world `2GROWCH `6to meet the evil Growch, and warm his icy heart!``");
				if (WinterFest.GiftedGrowch != 0) VarList::OnConsoleMessage(peer, "`2The Growch's heart is size " + to_string(WinterFest.Heart_Size) + ", and " + (WinterFest.Growch_Happy ? "he is happy! For now." : to_string(WinterFest.GiftedGrowch) + "% of the way to growing bigger."));
			}
			if (Event()->Harvest_Festival) VarList::OnConsoleMessage(peer, "`3Party down, it's `2Harvest Festival!`` Go collect some mooncakes from harvesting trees.``");
			if (Event()->Comet_Dust) VarList::OnConsoleMessage(peer, "It's the `2Night of the Comet!`` Stardust is sprinkling down from the sky, and you just might be able to get items that can only be spliced in the cosmic energy of the comet!");
			if (Event()->Locke_Salesman) VarList::OnConsoleMessage(peer, "`oA `2Traveling Salesman `ohas come to " + Environment()->server_name + " visit `2LOCKETOWN`o! Go trade hime some of your Locks for fabulous items before he leave town again!");
			if (Role::Moderator(peer)) VarList::OnConsoleMessage(peer, "`oYou are " + a + (Role::Owner(peer) ? "`b@Owner Server" : Role::Developer(peer) ? "`6@Developer" : Role::Administrator(peer) ? "`6@Administrator" : Role::Moderator(peer) ? "`#@Moderator" : "") + "``, Welcome to " + Environment()->server_name + " don't forget to read /modrules before Playing.");
			if (Environment()->Maintenance and Role::Clist(pInfo(peer)->tankIDName)) VarList::OnConsoleMessage(peer, "`5Server might be under Maintenance, fixing some issues We will back soon.");
			if (pInfo(peer)->tankIDName.empty() and pInfo(peer)->tankIDPass.empty()) {
				PlayerDB::RegisAndLogin_Page(peer);
			}
			else {
				if (pInfo(peer)->AccountSecured && pInfo(peer)->fa_ip != pInfo(peer)->ip) {
					PlayerDB::Aap_Page(peer);
				}
				else DialogHandle::News(peer);
			}
		}
	}
	static void wrench(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 4) return;
		int netID = std::atoi(explode("\n", t_[3])[0].c_str());
		if (netID == int(GTPS_NPC::NPC_EXCHANGE) && pInfo(peer)->world == "TRADE") {
			pInfo(peer)->last_netid = int(GTPS_NPC::NPC_EXCHANGE);
			if (abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_EXCHANGE)[0] / 32) == 1 || abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_EXCHANGE)[0] / 32) == 2 || abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_EXCHANGE)[0] / 32) == 3) {
				NonPlayerCharacter::State(peer, NPC_EXCHANGE, (pInfo(peer)->x / 32 <= getNpcSpawnPos(NPC_EXCHANGE)[0] / 32));
				NonPlayerCharacter::Talk(peer, NPC_EXCHANGE, "hello " + pInfo(peer)->tankIDName + ", welcome to the goods exchange place!");
				NonPlayerCharacter::Action(peer, NPC_EXCHANGE, "/wave");
				string fish = "", crystal = "";
				for (int i_ = 0; i_ < items.size(); i_++) {
					int item_id = items[i_].id;
					if (items[item_id].blockType == BlockTypes::FISH) {
						fish += "\nadd_button_with_icon|item_" + to_string(item_id) + "|" + items[item_id].name + "|staticPurpleFrame|" + to_string(item_id) + "||\n";
					}
					if (items[item_id].blockType == BlockTypes::CRYSTAL) {
						crystal += "\nadd_button_with_icon|item_" + to_string(item_id) + "|" + items[item_id].name + "|staticPurpleFrame|" + to_string(item_id) + "||\n";
					}
				}
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|`w[`2NPC`w] Exchange Place|left|9922|\nadd_spacer|small|\nadd_textbox|`wGreetings, Traveler! Welcome to the Exchange Place. I am here to assist you in Trading your treasures for valuable rewards<CR>If you'd like to strike a dead, simply browse the list below and choose the item you wish to offer. I'll ensure you get a fair trade in return!|left|\nadd_spacer|small|\nadd_textbox|`wItems available for exchange:|left|\nadd_spacer|small|\nadd_textbox|`5Fish:|left|\ntext_scaling_string|Subscribtions++++++++|\nadd_spacer|small|" + fish + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`5Crystal:|left|\nadd_spacer|small|" + crystal + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog|Exchange_Npc|Close||", 700);
			}
		}
		if (netID == int(GTPS_NPC::NPC_MARKETPLACE) && pInfo(peer)->world == "MARKETPLACE") {
			pInfo(peer)->last_netid = int(GTPS_NPC::NPC_MARKETPLACE);
			if (abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_MARKETPLACE)[0] / 32) == 1 || abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_MARKETPLACE)[0] / 32) == 2 || abs(pInfo(peer)->x / 32 - getNpcSpawnPos(NPC_MARKETPLACE)[0] / 32) == 3) {
				NonPlayerCharacter::State(peer, NPC_MARKETPLACE, (pInfo(peer)->x / 32 <= getNpcSpawnPos(NPC_MARKETPLACE)[0] / 32));
				NonPlayerCharacter::Talk(peer, NPC_MARKETPLACE, "hello " + pInfo(peer)->tankIDName + ", welcome to the goods Market Place!");
				NonPlayerCharacter::Action(peer, NPC_MARKETPLACE, "/wave");
				std::string item_list = ""; int total = 0;
				for (const auto& item : Environment()->Npc_MarketPlace) {
					total++;
					item_list += "\nadd_button_with_icon|searchableItemListButton_" + to_string(std::get<0>(item)) + "_" + to_string(std::get<1>(item)) + "_" + to_string(std::get<2>(item)) + "|" + items[std::get<0>(item)].name + "|staticYellowFrame|" + to_string(std::get<0>(item)) + "|";
				}
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|`w[`2NPC`w] MarketPlace|left|9922|\nadd_spacer|small|\nadd_smalltext|`5Hello and welcome! I’m [NPC] MarketPlace, and this is the best place to sell everything you have! From unique treasures to everyday essentials, I have it all right here. Feel free to browse my collection!<CR>If you have any questions, I’m here to help.|left|\nadd_smalltext|`5I hope you find what you’re looking for and enjoy your time here!|left|\nadd_spacer|small|\nadd_textbox|`2Items available:|left|\ntext_scaling_string|Subscribtions++++++++|\nadd_spacer|small|" + (total >= 1 ? item_list + "\nadd_button_with_icon||END_LIST|noflags|0||" : "") + "\nadd_spacer|small|\nend_dialog|MarketPlace_Npc|Close||", 700);
			}
		}
		if (pInfo(peer)->pet_netID == netID) {
			Pet_Ai::Dialog(peer, "");
		}
		if (pInfo(peer)->netID == netID) {
			send_wrench_self(peer);
		}
		else {
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->pet_netID != pInfo(peer)->pet_netID and pInfo(cp_)->pet_netID == netID and pInfo(cp_)->world == pInfo(peer)->world) {
					if (not pInfo(cp_)->show_pets) continue;
					VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`w" + pInfo(cp_)->pet_name + " -#" + get_player_nick(cp_) + "`` `4(" + (pInfo(cp_)->pet_level == 50 ? "MAX" : to_string(pInfo(cp_)->pet_level)) + ")``|left|" + to_string(pInfo(cp_)->pet_ID) + "|\nadd_spacer|small|\nend_dialog||Close||\nadd_quick_exit|");
				}
				if (pInfo(cp_)->netID == netID and pInfo(cp_)->world == pInfo(peer)->world) {
					pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
					bool already_friends = false, trade_blocked = false, muted = false;
					for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
						if (pInfo(peer)->friends[c_].name == pInfo(cp_)->tankIDName) {
							already_friends = true;
							if (pInfo(peer)->friends[c_].block_trade) trade_blocked = true;
							if (pInfo(peer)->friends[c_].mute) continue;
						}
					}
					std::string name_ = pInfo(peer)->world;
					auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
					if (it != worlds.end()) {
						World* world_ = &(*it);
						world_->fresh_world = true;
						int x_ = (pInfo(cp_)->state == 16 ? (int)pInfo(cp_)->x / 32 : round((double)pInfo(cp_)->x / 32)), y_ = (int)pInfo(cp_)->y / 32;
						if (x_ < 0 or x_ >= world_->max_x or y_ < 0 or y_ >= world_->max_y) {
						}
						else {
							if (world_->blocks[x_ + (y_ * 100)].fg == 1256) pInfo(cp_)->hospital_bed = true;
							else pInfo(cp_)->hospital_bed = false;
						}
						std::string msg2 = "", inv_guild = "", extra = "";
						for (int i = 0; i < to_string(pInfo(cp_)->level).length(); i++) msg2 += "?";
						if (pInfo(cp_)->guild_id != 0) {
							std::uint32_t guild_id = pInfo(cp_)->guild_id;
							std::vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
							if (find_guild != guilds.end()) {
								Guild* guild_information = &guilds[find_guild - guilds.begin()];
								for (GuildMember member_search : guild_information->guild_members) {
									if (to_lower(member_search.member_name) == to_lower(pInfo(cp_)->tankIDName)) {
										if (guild_information->guild_mascot[1] == 0 and guild_information->guild_mascot[0] == 0) {
											extra += "\nadd_label_with_icon|small|`9Guild: `2" + guild_information->guild_name + "``|left|5814||\nadd_smalltext|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
										}
										else {
											extra += "\nadd_dual_layer_icon_label|small|`9Guild: `2" + guild_information->guild_name + "``|left|" + to_string(guild_information->guild_mascot[1]) + "|" + to_string(guild_information->guild_mascot[0]) + "|1.0|1||\nadd_smalltext|`9Rank: `2" + (member_search.role_id == 0 ? "Member" : (member_search.role_id == 1 ? "Elder" : (member_search.role_id == 2 ? "Co-Leader" : "Leader"))) + "``|left|\nadd_spacer|small|";
										}
										continue;
									}
								}
							}
						}
						if (pInfo(peer)->guild_id != 0 and pInfo(cp_)->guild_id == 0) {
							std::uint32_t guild_id = pInfo(peer)->guild_id;
							std::vector<Guild>::iterator find_guild = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
							if (find_guild != guilds.end()) {
								Guild* guild_information = &guilds[find_guild - guilds.begin()];
								for (GuildMember member_search : guild_information->guild_members) {
									if (to_lower(member_search.member_name) == to_lower(pInfo(peer)->tankIDName)) {
										if (member_search.role_id >= 1) {
											inv_guild = "\nadd_custom_button|invitetoguild|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,16;width:0.27;min_width:60;|\nadd_custom_break|";
										}
										continue;
									}
								}
							}
						}
						std::string surgery = "\nadd_spacer|small|\nadd_custom_button|start_surg|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,17;width:0.27;min_width:60;|\nadd_custom_break|\nadd_smalltext|Surgeon Skill: " + to_string(pInfo(peer)->surgery_skill) + "|left|";
						if (Playmods::HasById(pInfo(cp_), 87)) surgery = "\nadd_spacer|small|\nadd_textbox|Recovering from surgery...|left|";
						if (pInfo(cp_)->hospital_bed == false) surgery = "";
						pInfo(peer)->last_netID = netID;
						VarList::OnDialogRequest(peer, SetColor(peer) + "embed_data|mynetID|" + to_string(pInfo(peer)->netID) + "\nset_default_color|`o\nadd_label_with_icon|big|" + get_player_nick(cp_) + "```` `0(```2" + (Role::Administrator(cp_) ? (Role::Moderator(cp_) ? to_string(pInfo(cp_)->level) : msg2) : to_string(pInfo(cp_)->level)) + "```0)``|left|18|" + surgery + "\nembed_data|othernetID|" + to_string(netID) + "\nadd_label_with_icon|small|`5Player Role``: " + (Role::Clist(pInfo(cp_)->tankIDName) ? "`2@Creator List" : Role::Owner(cp_) ? "`b@Owner Server" : Role::Unlimited(cp_) ? "`8@Unlimited" : Role::God(cp_) ? "`9@God" : Role::Developer(cp_) ? "`6@Developer" : Role::Administrator(cp_) ? "`e@Administrator" : Role::Moderator(cp_) ? "`#@Moderator" : Role::Vip(cp_) ? "`1VIP" : "`wNoobs!") + "|left|15044|\nadd_spacer|small|" + extra + (trade_blocked ? "\nadd_custom_button||image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,14;width:0.27;min_width:60;state:disabled;|\nadd_custom_break|" : "\nadd_custom_button|trade|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,0;width:0.27;min_width:60;|\nadd_custom_break|") + "\nadd_custom_button|send_gems|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,13;width:0.27;min_width:60;|\nadd_custom_break|\nadd_custom_button|send_msg|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,12;width:0.27;min_width:60;|\nadd_custom_break|\nadd_textbox|(No Battle Leash equipped)|left|\nadd_textbox|Your opponent needs a valid license to battle!|left|" + (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName) or (find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) != world_->admins.end()) or Role::Administrator(peer) or Role::Moderator(peer) ? "\nadd_custom_button|kick|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,11;width:0.27;min_width:60;|\nadd_custom_break|\nadd_custom_button|pull|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,10;width:0.27;min_width:60;|\nadd_custom_break|\nadd_custom_button|worldban|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,2;width:0.27;min_width:60;|\nadd_custom_break|" : "") + a + (Role::Moderator(peer) || Role::Administrator(peer) ? "\nadd_custom_button|punish_view|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,9;width:0.27;min_width:60;|\nadd_custom_break|" : "") + inv_guild + (!already_friends ? "\nadd_custom_button|friend_add|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,8;width:0.27;min_width:60;|\nadd_custom_break|" : "") + (muted ? "\nadd_custom_button|unmute_player|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,7;width:0.27;min_width:60;|\nadd_custom_break|" : (already_friends ? "\nadd_custom_button|mute_player|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,6;width:0.27;min_width:60;|\nadd_custom_break|" : "")) + "|\nadd_custom_button|view_worn_clothes|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,5;width:0.27;min_width:60;|\nadd_custom_break|\nadd_custom_button|ignore_player|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,1;width:0.27;min_width:60;|\nadd_custom_break|\nadd_custom_button|report_player|image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,15;width:0.27;min_width:60;|\nadd_custom_break|\nadd_spacer|small|\nadd_custom_button||image:interface/large/player_wrench.rttex;image_size:227,57;frame:0,3;width:0.27;min_width:60;|\nadd_custom_break|\nend_dialog|Aparece_Otro|||\nadd_quick_exit|");
					}
					continue;
				}
			}
		}
	}
	static void Rem_Trade(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 3) return;
		int item_id = std::atoi(explode("\n", t_[2])[0].c_str()), c_ = Inventory::Contains(peer, item_id);
		if (c_ == 0) return;
		if (items[item_id].untradeable || items[item_id].blockType == BlockTypes::FISH) {
			VarList::OnTextOverlay(peer, "You'd be sorry if you lost that!");
			return;
		}
		bool cancel_ = false, guildss = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				if (pInfo(cp_)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(cp_)->trading_with) {
					if (item_id == 5816 and pInfo(cp_)->guild_id != 0) {
						CAction::Positioned(peer, pInfo(peer)->netID, "audio/cant_place_tile.wav", 0);
						VarList::OnTextOverlay(peer, "`4Oops - " + get_player_nick(cp_) + " is already in guild.");
						guildss = true;
						continue;
					}
				}
			}
		}
		if (item_id == 1424 || item_id == 5816) {
			std::string name_ = pInfo(peer)->world;
			auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (it != worlds.end()) {
				World* world_ = &(*it);
				if (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName)) {
				}
				else cancel_ = true;
			}
		}
		if (cancel_) if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		if (not guildss) {
			mod_trade(peer, item_id, c_, true);
			return;
		}
	}
	static void Mod_Trade(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 3) return;
		int item_id = std::atoi(explode("\n", t_[2])[0].c_str()), c_ = Inventory::Contains(peer, item_id);
		if (c_ == 0) return;
		if (items[item_id].untradeable || items[item_id].blockType == BlockTypes::FISH) {
			VarList::OnTextOverlay(peer, "You'd be sorry if you lost that!");
			return;
		}
		bool cancel_ = false, guildss = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				if (pInfo(cp_)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(cp_)->trading_with) {
					if (item_id == 5816 and pInfo(cp_)->guild_id != 0) {
						CAction::Positioned(peer, pInfo(peer)->netID, "audio/cant_place_tile.wav", 0);
						VarList::OnTextOverlay(peer, "`4Oops - " + get_player_nick(cp_) + " is already in guild.");
						guildss = true;
						continue;
					}
				}
			}
		}
		if (item_id == 1424 || item_id == 5816) {
			std::string name_ = pInfo(peer)->world;
			auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (it != worlds.end()) {
				World* world_ = &(*it);
				if (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName)) {
				}
				else cancel_ = true;
			}
		}
		if (cancel_) if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		if (c_ == 1 and not guildss) {
			mod_trade(peer, item_id, c_, false);
			return;
		}
		if (not guildss) {
			VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`2Trade`` `w" + items[item_id].name + "``|left|" + to_string(item_id) + "|\nadd_textbox|`2Trade how many?``|left|\nadd_text_input|count||" + to_string(c_) + "|5|\nembed_data|itemID|" + to_string(item_id) + "\nend_dialog|trade_item|Cancel|OK|");
		}
	}
	static void trade_accept(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) {
			std::vector<std::string> t_ = explode("|", cch);
			if (t_.size() < 3) return;
			string status_ = explode("\n", t_[2])[0];
			if (status_ != "1" and status_ != "0") return;
			bool f_ = false;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					if (pInfo(cp_)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(cp_)->trading_with) {
						std::string name_ = pInfo(peer)->world;
						auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
						if (it != worlds.end()) {
							World* world_ = &(*it);
							world_->fresh_world = true;
							if (status_ == "1") pInfo(peer)->trade_accept = 1;
							else pInfo(peer)->trade_accept = 0;
							if (pInfo(peer)->trade_accept and pInfo(cp_)->trade_accept) {
								if (not trade_space_check(peer, cp_)) {
									pInfo(peer)->trade_accept = 0, pInfo(cp_)->trade_accept = 0;
									VarList::OnTradeStatus(peer, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "``'s offer.``", make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|0");
									VarList::OnTradeStatus(cp_, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "``'s offer.``", make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
									f_ = true;
									continue;
								}
								else if (not trade_space_check(cp_, peer)) {
									pInfo(peer)->trade_accept = 0, pInfo(cp_)->trade_accept = 0;
									VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "``'s offer.``", make_trade_offer(pInfo(cp_), true) + "locked|0\naccepted|0");
									VarList::OnTradeStatus(peer, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "``'s offer.``", make_trade_offer(pInfo(cp_), true) + "locked|0\nreset_locks|1\naccepted|0");
									f_ = true;
									continue;
								}
								VarList::OnForceTradeEnd(peer);
								bool blocked = false;
								for (int i_ = 0; i_ < pInfo(cp_)->trade_items.size(); i_++) {
									std::map<std::string, int>::iterator it;
									for (auto it = pInfo(cp_)->trade_items[i_].begin(); it != pInfo(cp_)->trade_items[i_].end(); it++) {
										if (Inventory::Contains(cp_, it->first) == 0) if (pInfo(cp_)->trading_with != -1) cancel_trade(cp_, false, true), blocked = true;
									}
								}
								for (int i_ = 0; i_ < pInfo(peer)->trade_items.size(); i_++) {
									std::map<std::string, int>::iterator it;
									for (auto it = pInfo(peer)->trade_items[i_].begin(); it != pInfo(peer)->trade_items[i_].end(); it++) {
										if (Inventory::Contains(peer, it->first) == 0) if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false, true), blocked = true;
									}
								}
								if (blocked == false) send_trade_confirm_dialog(peer, cp_);
								continue;
							}
							VarList::OnTradeStatus(peer, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "``'s offer.``", make_trade_offer(pInfo(peer), true) + "locked|0\naccepted|" + status_);
							VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "``'s offer.``", "locked|0\nreset_locks|1\naccepted|0");
							VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "``'s offer.``", "locked|0\naccepted|1");
							VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "``'s offer.``", make_trade_offer(pInfo(cp_), true) + "locked|0\nreset_locks|1\naccepted|0");
							VarList::OnTradeStatus(cp_, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "``'s offer.``", make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|" + status_);
						}
						f_ = true;
						continue;
					}
				}
			}
			if (not f_) {
				if (status_ == "1") pInfo(peer)->trade_accept = 1;
				else pInfo(peer)->trade_accept = 0;
			}
		}
	}
	static void trade_cancel(ENetPeer* peer, std::string cch) {
		cancel_trade(peer);
	}
	static void trade_check_price(ENetPeer* peer, std::string cch) {
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				if (pInfo(cp_)->netID == pInfo(peer)->trading_with and pInfo(peer)->netID == pInfo(cp_)->trading_with) {
					std::string theiritems = "", myitems = "";
					int tt = 0, mt = 0;
					for (int i = 0; i < pInfo(cp_)->trade_items.size(); i++) {
						std::map<std::string, int>::iterator it;
						for (auto it = pInfo(cp_)->trade_items[i].begin(); it != pInfo(cp_)->trade_items[i].end(); it++) {
							std::string est = "N/A";
							int id = it->first; int sum = 0, itemprice = 0, count = it->second;
							if (not items[id].last20sales.empty()) {
								for (int i_ = 0; i_ < items[id].last20sales.size(); i_++) {
									sum += items[id].last20sales[i_];
								}
								itemprice = (int)sum / items[id].last20sales.size();
							}
							if (itemprice > 1) est = Set_Count(itemprice), tt += count * itemprice;
							theiritems += "add_label_with_icon|small|`w" + items[id].name + " = `ois averaged at price is " + est + " World Locks!|left|" + to_string(id) + "|\n";
						}
					}
					for (int i = 0; i < pInfo(peer)->trade_items.size(); i++) {
						std::map<std::string, int>::iterator it;
						for (auto it = pInfo(peer)->trade_items[i].begin(); it != pInfo(peer)->trade_items[i].end(); it++) {
							std::string est = "N/A";
							int id = it->first; int sum = 0, itemprice = 0, count = it->second;
							if (not items[id].last20sales.empty()) {
								for (int i_ = 0; i_ < items[id].last20sales.size(); i_++) {
									sum += items[id].last20sales[i_];
								}
								itemprice = (int)sum / items[id].last20sales.size();
							}
							if (itemprice > 1) est = Set_Count(itemprice), mt += count * itemprice;
							myitems += "add_label_with_icon|small|`w" + items[id].name + " = `ois averaged at price is " + est + " World Locks!|left|" + to_string(id) + "|\n";
						}
					}
					if (myitems == "") myitems = "add_textbox|None!|left|\n";
					if (theiritems == "") theiritems = "add_textbox|None!|left|\n";
					VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wTrade-Scan``|left|13816|\nadd_spacer|small|\nadd_textbox|`o" + get_player_nick(cp_) + "'s `witems:``|left|" + theiritems + "\nadd_textbox|`oTotal value of items `w" + Set_Count(tt) + "ā|left|\nadd_spacer|small|\nadd_textbox|`omy `witems:``|left|" + myitems + "\nadd_textbox|`oTotal value of items `w" + Set_Count(mt) + "ā|left|\nadd_spacer|small|\nend_dialog|check_price|OK||\n");
				}
			}
		}
	}
	static void SetRole(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 3) return;
		std::string id_ = explode("\n", t_[2])[0];
		if (not isdigit(id_[0])) return;
		std::uint32_t role_t = std::atoi(id_.c_str());
		if (cch.find("action|setRoleIcon") != string::npos) {
			if (role_t == 6) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 0 and pInfo(peer)->t_lvl >= 10) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 1 and pInfo(peer)->bb_lvl >= 10) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 2 and pInfo(peer)->s_lvl >= 10) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 3 and pInfo(peer)->ff_lvl >= 10) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 4 and pInfo(peer)->p_lvl >= 10) pInfo(peer)->roleIcon = role_t;
			else if (role_t == 5 and pInfo(peer)->g_lvl >= 10) pInfo(peer)->roleIcon = role_t;
		}
		else {
			if (role_t == 6) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 0 and pInfo(peer)->t_lvl >= 10) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 1 and pInfo(peer)->bb_lvl >= 10) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 2 and pInfo(peer)->s_lvl >= 10) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 3 and pInfo(peer)->ff_lvl >= 10) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 4 and pInfo(peer)->p_lvl >= 10) pInfo(peer)->roleSkin = role_t;
			else if (role_t == 5 and pInfo(peer)->g_lvl >= 10) pInfo(peer)->roleSkin = role_t;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != pInfo(peer)->world) continue;
			VarList::OnSetRoleSkinsAndIcons(cp_, pInfo(peer)->netID, pInfo(peer)->roleSkin, pInfo(peer)->roleIcon);
		}
	}
	static void setSkin(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 3) return;
		std::string id_ = explode("\n", t_[2])[0];
		if (not isdigit(id_[0])) return;
		char* endptr = NULL;
		unsigned int skin_ = strtoll(id_.c_str(), &endptr, 10);
		if (skin_ == 3531226367 || skin_ == 4023103999 || skin_ == 1345519520 || skin_ == 194314239) {
			if (pInfo(peer)->supp == 2 or pInfo(peer)->subscriber) pInfo(peer)->skin = skin_;
		}
		else if (skin_ == 3578898848 || skin_ == 3317842336) {
			if (pInfo(peer)->gp || pInfo(peer)->subscriber) pInfo(peer)->skin = skin_;
		}
		else pInfo(peer)->skin = skin_;
		Clothing_V2::Update(peer, true, true);
	}
	static void drop(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			world_->fresh_world = true;
			std::vector<std::string> t_ = explode("|", cch);
			if (t_.size() < 4) return;
			int id_ = std::atoi(explode("\n", t_[3])[0].c_str()), c_ = 0, invTotal = 0;
			Inventory::Modify(peer, id_, invTotal);
			if (invTotal < 1 || invTotal == 0) return;
			if (id_ <= 0 or id_ >= items.size()) return;
			if (find(world_->active_jammers.begin(), world_->active_jammers.end(), 4758) != world_->active_jammers.end()) {
				if (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName) or find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) != world_->admins.end()) {
				}
				else {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The Mini-Mod says no dropping items in this world!", 0, 0);
					return;
				}
			}
			if (is_item_blocked(id_)) {
				VarList::OnTextOverlay(peer, "`4Item ini tidak boleh di-drop!");
				return;
			}
			if (items[id_].untradeable or id_ == 1424 or id_ == 5816) {
				VarList::OnTextOverlay(peer, "You can't drop that.");
				return;
			}
			std::string name_ = pInfo(peer)->world;
			auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (it != worlds.end()) {
				World* world_ = &(*it);
				world_->fresh_world = true;
				int a_ = rand() % 12;
				int x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - (a_ + 20) : (pInfo(peer)->x + 20) + a_);
				int y = pInfo(peer)->y + rand() % 16;
				int where_ = (pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100);
				if (where_ < 0 || x < 0 || y < 0 || where_ > world_->blocks.size()) {
					VarList::OnTextOverlay(peer, "You can't drop that here, face somewhere with open space.");
					return;
				}
				WorldBlock* block_ = &world_->blocks[where_];
				if (items[block_->fg].collisionType == 1 || block_->fg == 6 || items[block_->fg].blockType == BlockTypes::GATEWAY || items[block_->fg].toggleable and is_false_state(world_->blocks[(pInfo(peer)->state == 16 ? x / 32 : round((double)x / 32)) + (y / 32 * 100)], 0x00400000)) {
					VarList::OnTextOverlay(peer, items[block_->fg].blockType == BlockTypes::MAIN_DOOR ? "You can't drop items on the white door." : "You can't drop that here, face somewhere with open space.");
					return;
				}
				int count_ = 0;
				for (int i_ = 0; i_ < world_->drop_new.size(); i_++) {
					if (abs(world_->drop_new[i_][4] - y) <= 16 and abs(world_->drop_new[i_][3] - x) <= 16) count_ += 1;
				}
				if (count_ > 20) {
					VarList::OnTextOverlay(peer, "You can't drop that here, find an emptier spot!");
					return;
				}
			}
			Inventory::Modify(peer, id_, c_);
			if (pInfo(peer)->cheater_settings & SETTINGS::SETTINGS_5 && pInfo(peer)->disable_cheater == 0) {
				std::string name_ = pInfo(peer)->world;
				auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (it != worlds.end()) {
					World* world_ = &(*it);
					world_->fresh_world = true;
					WorldDrop drop_{};
					drop_.id = id_, drop_.count = c_;
					int a_ = rand() % 12;
					drop_.x = (pInfo(peer)->state == 16 ? pInfo(peer)->x - (a_ + 20) : (pInfo(peer)->x + 20) + a_), drop_.y = pInfo(peer)->y + rand() % 16;
					c_ *= -1;
					if (Inventory::Modify(peer, id_, c_) == 0) {
						ServerPool::Logs::Add(pInfo(peer)->tankIDName + " in [" + pInfo(peer)->world + "] Dropped  `w" + to_string(abs(c_)) + " " + (items[id_].blockType == BlockTypes::FISH ? "lb." : "") + " " + items[id_].ori_name + "``." + (items[id_].rarity > 363 ? "" : " Rarity: `w" + to_string(items[id_].rarity) + "``"), "Drop Item");
						ServerPool::CctvLogs::Add(peer, "dropped", to_string(abs(c_)) + " " + items[id_].name);
						VisualHandle::Drop(world_, drop_, pInfo(peer)->netID);
					}
				}
			}
			else VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to drop?|left|\nadd_text_input|count||" + (items[id_].blockType == BlockTypes::FISH ? "1" : to_string(c_)) + "|5|\nembed_data|itemID|" + to_string(id_) + "" + (to_lower(world_->owner_name) != to_lower(pInfo(peer)->tankIDName) and not Role::Administrator(peer) and (find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) == world_->admins.end()) ? "\nadd_textbox|If you are trying to trade an item with another player, use your wrench on them instead to use our Trade System! `4Dropping items is not safe!``|left|" : "") + "\nend_dialog|drop_item|Cancel|OK|");
		}
	}
	static void trash(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 4) return;
		int id_ = std::atoi(explode("\n", t_[3])[0].c_str()), c_ = 0, invTotal = 0;
		Inventory::Modify(peer, id_, invTotal);
		if (invTotal < 1 || invTotal == 0) return;
		if (id_ <= 0 or id_ >= items.size()) return;
		if (id_ == 18 || id_ == 32 || id_ == 6336 || id_ == 9384) {
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/cant_place_tile.wav", 0);
			VarList::OnTextOverlay(peer, "You'd be sorry if you lost that!");
			return;
		}
		if (is_item_blocked(id_)) {
			VarList::OnTextOverlay(peer, "`4Item ini tidak boleh di-trash!");
			return;
		}
		Inventory::Modify(peer, id_, c_);
		if (pInfo(peer)->cheater_settings & SETTINGS::SETTINGS_15 && pInfo(peer)->disable_cheater == 0) {
			int count = c_;
			c_ = c_ * -1;
			if (Inventory::Modify(peer, id_, c_) == 0) {
				CAction::Positioned(peer, pInfo(peer)->netID, "audio/trash.wav", 0);
				if (pInfo(peer)->supp != 0) {
					int item = id_, maxgems = 0, receivegems = 0;
					if (id_ % 2 != 0) item -= 1;
					maxgems = items[item].max_gems2;
					if (items[item].max_gems2 != 0) if (maxgems != 0) for (int i = 0; i < count; i++) receivegems += rand() % maxgems;
					if (items[item].max_gems3 != 0) receivegems = count * items[item].max_gems3;
					if (receivegems != 0) VarList::OnBuxGems(peer, receivegems);
					VarList::OnConsoleMessage(peer, (items[id_].blockType == BlockTypes::FISH ? (to_string(abs(c_))) + "lb." : to_string(abs(c_))) + " `w" + items[id_].ori_name + "`` recycled, `0" + Set_Count(receivegems) + "`` gems earned.");
				}
				else VarList::OnConsoleMessage(peer, (items[id_].blockType == BlockTypes::FISH ? (to_string(abs(c_))) + "lb." : to_string(abs(c_))) + " `w" + items[id_].ori_name + "`` trashed.");
				return;
			}
		}
		if (pInfo(peer)->supp == 0) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`4Trash`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|How many to `4destroy``? (you have " + (items[id_].blockType == BlockTypes::FISH ? "1" : to_string(c_)) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
		else {
			int item = id_, maxgems = 0, maximum_gems = 0;
			if (id_ % 2 != 0) item -= 1;
			maxgems = items[item].max_gems2;
			if (items[item].max_gems3 != 0) maximum_gems = items[item].max_gems3;
			std::string recycle_text = "0" + (maxgems == 0 ? "" : "-" + to_string(maxgems)) + "";
			if (maximum_gems != 0) recycle_text = to_string(maximum_gems);
			VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`4Recycle`` `w" + items[id_].ori_name + "``|left|" + to_string(id_) + "|\nadd_textbox|You will get " + recycle_text + " gems per item.|\nadd_textbox|How many to `4destroy``? (you have " + (items[id_].blockType == BlockTypes::FISH ? "1" : to_string(c_)) + ")|left|\nadd_text_input|count||0|5|\nembed_data|itemID|" + to_string(id_) + "\nend_dialog|trash_item|Cancel|OK|");
		}
	}
	static void info(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 4) return;
		int id_ = std::atoi(explode("\n", t_[3])[0].c_str()), invTotal = 0;
		Inventory::Modify(peer, id_, invTotal);
		if (invTotal < 1 || invTotal == 0) return;
		if (id_ > items.size() || id_ <= 0) return;
		if (id_ % 2 != 0) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].ori_name + "``|left|" + to_string(id_) + "|" + to_string(items[id_ - 1].chi) + "|\nadd_spacer|small|\nadd_textbox|Plant this seed to grow a `0" + items[id_ - 1].ori_name + " Tree.``|left|\nadd_spacer|small|\nadd_textbox|Rarity: `0" + to_string(items[id_].rarity) + "``|left|\nadd_spacer|small|\nend_dialog|||OK|\n");
		else {
			std::string extra_ = "\nadd_textbox|";
			if (id_ == 18) extra_ += "You've punched `w" + to_string(pInfo(peer)->punch_count) + "`` times.";
			if (items[id_].blockType == BlockTypes::LOCK) extra_ += "A lock makes it so only you (and designated friends) can edit an area.";
			if (items[id_].extra_gems != 0) extra_ += "<CR>This item gives " + to_string(items[id_].extra_gems) + "x gems.";
			if (items[id_].r_1 == 0 or items[id_].r_2 == 0) {
				if (items[id_].properties & Property_Untradable) {
				}
				else extra_ += "<CR>This item can't be spliced.";
			}
			else extra_ += "Rarity: `w" + to_string(items[id_].rarity) + "``<CR><CR>To grow, plant a `w" + items[id_ + 1].name + "``.   (Or splice a `w" + items[items[id_].r_1].name + "`` with a `w" + items[items[id_].r_2].name + "``)<CR>";
			if (items[id_].properties & Property_Dropless or items[id_].rarity == 999) {
				if (items[id_].properties & Property_Untradable) {

				}
				else {
					if (items[id_].r_1 != 0 or items[id_].r_2 != 0) {
					}
					else extra_ += "<CR>`1This item never drops any seeds.``";
				}
			}
			if (items[id_].properties & Property_Untradable) extra_ += "<CR>`1This item cannot be dropped or traded.``";
			if (items[id_].properties & Property_AutoPickup) extra_ += "<CR>`1This item can't be destroyed - smashing it will return it to your backpack if you have room!``";
			if (items[id_].properties & Property_MultiFacing && items[id_].properties & Property_Wrenchable) {
				extra_ += "<CR>`1This item can be placed in two directions, depending on the direction you're facing.``";
			}
			else {
				if (items[id_].properties & Property_Wrenchable) extra_ += "<CR>`1This item has special properties you can adjust with the Wrench.``";
				if (items[id_].properties & Property_MultiFacing) extra_ += "<CR>`1This item can be placed in two directions, depending on the direction you're facing.``";
			}
			if (items[id_].properties & Property_NoSelf) extra_ += "<CR>`1This item has no use... by itself.``";
			extra_ += "|left|";
			if (extra_ == "\nadd_textbox||left|") extra_ = "";
			else extra_ = replace_str(extra_, "add_textbox|<CR>", "add_textbox|");
			std::string extra_ore = "", item_info = "", Extra_ = ""; int total_ = 0;
			for (int i_2 = 0; i_2 < EditItem.size(); i_2++) {
				if (EditItem[i_2].ID == id_) {
					for (const auto& result : EditItem[i_2].Extra_Drops) {
						total_++;
						Extra_ += "\nadd_button_with_icon||" + items[result.first].name + "|staticPurpleFrame|" + to_string(result.first) + "|" + to_string(result.second) + "|\n";
					}
					item_info = "\nadd_textbox|`5Special Effects:|left|" + a + (items.at(id_).blockType == BlockTypes::CLOTHING ? "\nadd_smalltext|`1Far Break >> " + to_string(EditItem[i_2].Far_Punch) + "|\nadd_smalltext|`1Far Place >> " + to_string(EditItem[i_2].Punch_Place) + "|\nadd_smalltext|`1Punch Hit >> " + to_string(EditItem[i_2].Punch_Hit) + "|" : "") + "\nadd_smalltext|`1Extra Gems >> " + to_string(EditItem[i_2].Gems) + "|\nadd_smalltext|`1Extra Xp >> " + to_string(EditItem[i_2].Xp) + "|\nadd_smalltext|`1Change Bonus >> " + to_string(EditItem[i_2].Bonus) + "%|\nadd_smalltext|`1Extra Drops:|left|\ntext_scaling_string|Subscribtions++++++++|" + (total_ >= 1 ? Extra_ + "\nadd_button_with_icon||END_LIST|noflags|0||" : "") + "\nadd_spacer|small|";
				}
			}
			VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_ele_icon|big|`wAbout " + items[id_].name + "`` (" + to_string(id_) + ")|left|" + to_string(id_) + "|" + to_string(items[id_].chi) + "|\nadd_spacer|small|" + item_info + "\nadd_textbox|" + items[id_].description + "|left|" + (pInfo(peer)->subscriber ? "\nadd_spacer|small|\nadd_textbox|`1This item average price is " + (items[id_].price.size() == 0 ? "unknown" : to_string(item_average2(items[id_].price)) + " World Locks") + "!``|left|" : "") + "" + (extra_ore != "" ? "\nadd_spacer|small|\nadd_textbox|This item also drops:|left|" + extra_ore : "") + "" + (id_ == 8552 ? "\nadd_spacer|small|\nadd_textbox|Angelic Healings: " + to_string(pInfo(peer)->surgery_done) + "|left|" : "") + "\nadd_spacer|small|" + extra_ + "\nadd_spacer|small|\nend_dialog|||OK|\n");
		}
	}
	static void halloweenquestpopup(ENetPeer* peer, std::string cch) {
		if (Event()->Halloween) DialogHandle::Halloween_Task(peer);
	}
	static void warp_player_into_halloween_world(ENetPeer* peer, std::string cch) {
		if (Event()->Halloween) {
			std::string world = "GROWGANOTH";
			Enter_World(peer, world);
		}
	}
	static void rt_grope_gem_halloween_bundle(ENetPeer* peer, std::string cch) {
		if (Event()->Halloween) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|Halloween Starter Pack|left|\nadd_spacer|small|\nadd_smalltext|`2You Get:`` `w540,000 Gems, 25x Dark King's Offering, 5x Dark Tickets, 75x Gift of Growganoth, 1x Carved Pumpkin Hat, 1x Carved Pumpkin Onesie.``|left|\nadd_spacer|small|\nadd_smalltext|`5Description:`` `wTreat yourself with all the gems you could ever want and everything you need to give a scare this Halloween! The Carved Pumpkin Set will only be available from this pack in 2024. Get out there, we're \"rotting\" for you!|left|\nadd_spacer|small|\nadd_button|purchase_halloween_pack|ĳ 600 " + Environment()->server_name + " Coin|noflags|0|0|\nend_dialog|halloween_tasks_popup_handle|Cancel||\nadd_quick_exit|", 500);
	}
	static void valentine_valuepack(ENetPeer* peer, std::string cch) {
		if (Event()->Valentine) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|Valentine Value Pack|left|\nadd_spacer|small|\nadd_smalltext|`2You Get:`` `w105,000 Gems, 2x Lost Valentine, 20x Golden Booty Chest, 1x Well of Love.``|left|\nadd_spacer|small|\nadd_smalltext|`5Description:`` `w\"An extra sweet deal to go with the event!\"|left|\nadd_spacer|small|\nadd_button|purchase_value|ĳ 250 " + Environment()->server_name + " Coin|noflags|0|0|\nend_dialog|Valentine_Shop|Cancel||\nadd_quick_exit|", 500);
	}
	static void valentine_starterpack(ENetPeer* peer, std::string cch) {
		if (Event()->Valentine) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|Valentine Starter Pack|left|\nadd_spacer|small|\nadd_smalltext|`2You Get:`` `w540,000 Gems, 50x Golden Booty Chest, 3x Super Golden Booty Chest, 1x Well of Love , 1x Corny Couple Shirt, 1x Heartstone Circlet.``|left|\nadd_spacer|small|\nadd_smalltext|`5Description:`` `w\"An extra sweet deal to go with the event!\"|left|\nadd_spacer|small|\nadd_button|purchase_starter|ĳ 900 " + Environment()->server_name + " Coin|noflags|0|0|\nend_dialog|Valentine_Shop|Cancel||\nadd_quick_exit|", 500);
	}
	static void winterfest_eventpack(ENetPeer* peer, std::string cch) {
		if (WinterFest.Active) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|Winterfest Event Pack|left|\nadd_spacer|small|\nadd_smalltext|`2You Get:`` `w1,200 Winter Seals, 230,000 Gems, 10x Snowball, 15x Winterfest Crackers, 1x Deluxe Winterfest Crackers, 1x Special Winter Wish.``|left|\nadd_spacer|small|\nadd_smalltext|`5Description:`` `wTreat yourself with all the gems you could ever want and everything you need to give a scare this Winterfest! The Buttoned Eyes will only be available from this pack in 2024. Get out there, we're \"rotting\" for you!|left|\nadd_spacer|small|\nadd_button|purchase|ĳ 700 " + Environment()->server_name + " Coin|noflags|0|0|\nend_dialog|WinterFest_Shop|Cancel||\nadd_quick_exit|", 500);
	}
	static void winterrallymenu(ENetPeer* peer, std::string cch) {
		if (WinterFest.Active) DialogHandle::Winterfest_Task(peer);
	}
	static void winter_bingo_ui(ENetPeer* peer, std::string cch) {
		if (WinterFest.Active) {
			if (pInfo(peer)->Has_WinBingo) DialogHandle::Winter_Bingo(peer);
		}
	}
	static void royalwinterseals(ENetPeer* peer, std::string cch) {
		if (WinterFest.Active) DialogHandle::Royal_Winter(peer, 500);
	}
	static void opengachasystem(ENetPeer* peer, std::string cch) {
		DialogHandle::Gacha(peer, "Event");
	}
	static void growpass(ENetPeer* peer, std::string cch) {
		DialogHandle::GrowPass(peer, "Tasks");
	}
	static void assets_shop(ENetPeer* peer, std::string cch) {
		DialogHandle::Shop_Assets(peer);
	}
	static void marketplace(ENetPeer* peer, std::string cch) {
		DialogHandle::MarketPlace(peer, 500);
	}
	static void showphoenixreturns(ENetPeer* peer, std::string cch) {
		std::string available = "";
		for (int i = 0; i < Environment()->all_phoenix_items.size(); i++) {
			available += "\nadd_label_with_icon|small| - " + to_string(find_phoenix_item(Environment()->all_phoenix_items[i])) + " / 1 Found|left|" + to_string(Environment()->all_phoenix_items[i]) + "|";
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wThe Phoenix Rising!``|left|11038|\nadd_spacer|small|\nadd_textbox|Rising from the ashes are the Phoenix items of the past.|left|\nadd_spacer|small|\nadd_textbox|During the event, Phoenix items can only be obtained from `2Summer Artifact Chest``.|left|\nadd_spacer|small|\nadd_textbox|The available Phoenix items are as follows:|left|\nadd_spacer|small|" + available + "\nadd_spacer|small|\nadd_textbox|The amount available is updated every 24 hours. If an item isn't found in that time it won't be added to the total available.|left|\nadd_spacer|small|\nend_dialog|phoenix_returns||Back|", 500);
	}
	static void buy(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->world.empty() or not pInfo(peer)->Is_In_Dialog) return;
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 3) return;
		std::string item = explode("\n", t_[2])[0];
		int price = 0, free = Inventory::Get_Slots(pInfo(peer)), slot = 1, getcount = 0, get_counted = 0, random_pack = 0, token = 0;
		if (item == "main") shop_tab(peer, "tab1");
		else if (item == "locks") shop_tab(peer, "tab4");
		else if (item == "itempack") shop_tab(peer, "tab2");
		else if (item == "bigiitems") shop_tab(peer, "tab6");
		else if (item == "weather") shop_tab(peer, "tab3");
		else if (item == "token") shop_tab(peer, "tab5");
		else if (item == "upgrade_backpack") {
			price = (100 * ((((pInfo(peer)->inv.size() - 17) / 10) * ((pInfo(peer)->inv.size() - 17) / 10)) + 1)) * 2;
			if (price > pInfo(peer)->gems) {
				CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
				VarList::OnStorePurchaseResult(peer, "You can't afford `0Upgrade Backpack`` (`w10 Slots``)!  You're `$" + Set_Count(price - pInfo(peer)->gems) + "`` Gems short.");
			}
			else {
				if (pInfo(peer)->inv.size() < 476) {
					VarList::OnConsoleMessage(peer, "You've purchased `0Upgrade Backpack`` (`010 Slots``) for `$" + Set_Count(price) + "`` Gems.\nYou have `$" + Set_Count(pInfo(peer)->gems - price) + "`` Gems left.");
					VarList::OnStorePurchaseResult(peer, "You've purchased `0Upgrade Backpack (10 Slots)`` for `$" + Set_Count(price) + "`` Gems.\nYou have `$" + Set_Count(pInfo(peer)->gems - price) + "`` Gems left.\n\n`5Received: ```0Backpack Upgrade``\n");
					CAction::Positioned(peer, pInfo(peer)->netID, "audio/piano_nice.wav", 0);
					VarList::OnBuxGems(peer, price * -1);
					for (int i_ = 0; i_ < 10; i_++) pInfo(peer)->inv.push_back({ 0,0 });
					Inventory::Visuals(peer);
					Clothing_V2::Update(peer);
					shop_tab(peer, "tab4_upgrade_backpack");
				}
			}
		}
		else {
			bool aaaa = false;
			bool voucher = false;
			std::vector<int> list;
			std::vector<std::vector<int>> itemai;
			std::string item_name = "";
			if (item == "superhero") item += to_string(rand() % 4 + 1);
			std::ifstream ifs("database/shop/-" + item + ".json");
			if (ifs.is_open()) {
				json j;
				ifs >> j;
				if (!(j.find("v") == j.end())) {
					voucher = true;
					price = j["v"].get<int>();
				}
				else price = j["g"].get<int>();
				item_name = j["p"].get<string>();
				if (j.find("itemai") != j.end()) {
					if (item == "egg_carton") {
						if (pInfo(peer)->magic_egg < 1000) {
							CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
							VarList::OnStorePurchaseResult(peer, "You don't have enough magic bunny eggs!");
							return;
						}
						else pInfo(peer)->magic_egg -= 1000;
					}
					if (pInfo(peer)->gems < price && voucher == false) {
						CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
						VarList::OnStorePurchaseResult(peer, "You can't afford `o" + item_name + "``!  You're `$" + Set_Count(price - pInfo(peer)->gems) + "`` Gems short.");
						return;
					}
					else if (pInfo(peer)->voucher < price && voucher) {
						CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
						VarList::OnStorePurchaseResult(peer, "You can't afford `o" + item_name + "``!  You're `$" + Set_Count(price - pInfo(peer)->voucher) + "`` Vouchers short.");
						return;
					}
					itemai = j["itemai"].get<std::vector<std::vector<int>>>();
					if (item == "mystery_item") {
						itemai = { {Environment()->random_shop_item[rand() % Environment()->random_shop_item.size()], 1} };
					}
					if (rand() % 20 < 1) if (item == "mega_party_pack") itemai.push_back({ {7672, 1} });
					if (item == "sportsball_pack") {
						std::vector<std::uint16_t> list{ 2886,2890,2878,2882,6672,2880,2882,2884,2888,2906,6670 };
						itemai.push_back({ {list[rand() % list.size()], 1} });
					}
					int reik_slots = itemai.size();
					int turi_slots = Inventory::Get_Slots(pInfo(peer));
					for (std::vector<int> item_info : itemai) {
						int turi_dabar = 0;
						if (item_info[0] == 7844 || item_info[0] == 7328 || item_info[0] == 6198) {
						}
						else if (item_info[0] == 9502) {
							if (pInfo(peer)->LiyueHtouFly) {
								aaaa = true;
								goto fail_2;
							}
						}
						else if (item_info[0] == 9504) {
							if (pInfo(peer)->AbyssMageFly) {
								aaaa = true;
								goto fail_2;
							}
						}
						else if (item_info[0] == 20088) {
							if (pInfo(peer)->UuuzzFly) {
								aaaa = true;
								goto fail_2;
							}
						}
						else Inventory::Modify(peer, item_info[0], turi_dabar);
						if (turi_dabar != 0) reik_slots--;
						if (turi_dabar + item_info[1] > 200) {
							if (item_info[0] == 7844 || item_info[0] == 7328 || item_info[0] == 6198) {
							}
							else goto fail;
						}
					}
					if (turi_slots < reik_slots)
						if (item == "7844" or item == "7328" or item == "6198");
						else goto fail;
					{
						if (voucher == false and not aaaa) VarList::OnBuxGems(peer, price * -1);
						else {
							if (not aaaa) VarList::OnSetVouchers(peer, price * -1);
						}
						std::vector<std::string> received_items{}, received_items2{};
						for (std::vector<int> item_info : itemai) {
							std::uint32_t item_id = item_info[0];
							if (item_name.empty()) item_name = items[item_id].ori_name;
							int item_count = item_info[1];
							if (item_id == 7844) {
								pInfo(peer)->spring_token = pInfo(peer)->spring_token + item_count;
							}
							if (item_id == 6198) {
								pInfo(peer)->summer_token = pInfo(peer)->summer_token + item_count;
							}
							if (item_id == 7328) {
								pInfo(peer)->winter_token = pInfo(peer)->winter_token + item_count;
							}
							if (item_id == 15010) {
								WinterFest.Calendar_Sold++;
								shop_tab(peer, "tab1_15010");
							}
							if (item_id == 10450) {
								WinterFest.Bonanza_Sold++;
								shop_tab(peer, "tab1_10450");
							}
							if (item_id == 5930) {
								if (Environment()->Stock_Mag == 0) {
									goto fail_3;
								}
								else {
									Environment()->Stock_Mag--;
									shop_tab(peer, "tab6_5930");
								}
							}
							if (item_id == 9770) {
								if (Environment()->Stock_GRay == 0) {
									goto fail_3;
								}
								else {
									Environment()->Stock_GRay--;
									shop_tab(peer, "tab6_9770");
								}
							}
							if (item_id == 9778) {
								if (Environment()->Stock_ERay == 0) {
									goto fail_3;
								}
								else {
									Environment()->Stock_ERay--;
									shop_tab(peer, "tab6_9778");
								}
							}
							if (item_id == 5402) {
								if (WinterFest.Active) DailyEvent_Task::WinterFest(peer, "1", 1);
							}
							if (item_id == 9018) {
								if (Event()->Halloween) DailyEvent_Task::Halloween(peer, "2", 1);
							}
							if (item_id == 10386) {
								if (Event()->Halloween) DailyEvent_Task::Halloween(peer, "3", 1);
							}
							if (item_id == 12408) {
								if (Event()->Halloween) DailyEvent_Task::Halloween(peer, "4", 1);
							}
							if (item_id == 12658) {
								if (Event()->Halloween) DailyEvent_Task::Halloween(peer, "8", 1);
							}
							if (item_id == 4184) Epic_Quest::Add(peer, "Find a Riding Bumblebee or Buy a Riding Raven", pInfo(peer)->epicq_riding, 1, 1);
							if (item_id == 9502) {
								if (not pInfo(peer)->LiyueHtouFly) {
									if (pInfo(peer)->show_pets) {
										pInfo(peer)->pet_ID = 0;
										pInfo(peer)->show_pets = false;
										for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
											if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(cp_)->world) {
												VarList::OnRemove(cp_, pInfo(peer)->pet_netID, 0);
											}
										}
									}
									pInfo(peer)->show_pets = true;
									pInfo(peer)->LiyueHtouFly = true;
									pInfo(peer)->pet_name = (pInfo(peer)->pet_name.empty() or pInfo(peer)->pet_name == "`b@Uuuzz_Fly" or pInfo(peer)->pet_name == "`e@AbyssMage_Fly" ? "`4@Liyue_HTouFly" : pInfo(peer)->pet_name);
									pInfo(peer)->pet_type = 1;
									pInfo(peer)->pet_ID = 9502;
									for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; cp_++) {
										if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL) continue;
										if (pInfo(peer)->world == pInfo(cp_)->world) Pet_Ai::Create(cp_);
									}
									shop_tab(peer, "tab1_9502");
								}
								else {
									aaaa = true;
									goto fail_2;
								}
							}
							if (item_id == 9504) {
								if (not pInfo(peer)->AbyssMageFly) {
									if (pInfo(peer)->show_pets) {
										pInfo(peer)->pet_ID = 0;
										pInfo(peer)->show_pets = false;
										for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
											if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(cp_)->world) {
												VarList::OnRemove(cp_, pInfo(peer)->pet_netID, 0);
											}
										}
									}
									pInfo(peer)->show_pets = true;
									pInfo(peer)->AbyssMageFly = true;
									pInfo(peer)->pet_name = (pInfo(peer)->pet_name.empty() or pInfo(peer)->pet_name == "`b@Uuuzz_Fly" or pInfo(peer)->pet_name == "`4@Liyue_HTouFly" ? "`e@AbyssMage_Fly" : pInfo(peer)->pet_name);
									pInfo(peer)->pet_type = 1;
									pInfo(peer)->pet_ID = 9504;
									for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; cp_++) {
										if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL) continue;
										if (pInfo(peer)->world == pInfo(cp_)->world) Pet_Ai::Create(cp_);
									}
									shop_tab(peer, "tab1_9504");
								}
								else {
									aaaa = true;
									goto fail_2;
								}
							}
							if (item_id == 20088) {
								if (not pInfo(peer)->UuuzzFly) {
									if (pInfo(peer)->show_pets) {
										pInfo(peer)->pet_ID = 0;
										pInfo(peer)->show_pets = false;
										for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
											if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
											if (pInfo(peer)->world == pInfo(cp_)->world) {
												VarList::OnRemove(cp_, pInfo(peer)->pet_netID, 0);
											}
										}
									}
									pInfo(peer)->show_pets = true;
									pInfo(peer)->UuuzzFly = true;
									pInfo(peer)->pet_name = (pInfo(peer)->pet_name.empty() or pInfo(peer)->pet_name == "`4@Liyue_HTouFly" or pInfo(peer)->pet_name == "`e@AbyssMage_Fly" ? "`b@Uuuzz_Fly" : pInfo(peer)->pet_name);
									pInfo(peer)->pet_type = 1;
									pInfo(peer)->pet_ID = 20088;
									for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; cp_++) {
										if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL) continue;
										if (pInfo(peer)->world == pInfo(cp_)->world) Pet_Ai::Create(cp_);
									}
									shop_tab(peer, "tab1_20088");
								}
								else {
									aaaa = true;
									goto fail_2;
								}
							}
							else {
								if (item_id == 20088 or item_id == 9504 or item_id == 9502 or item_id == 7844 or item_id == 7328 or item_id == 6198) {

								}
								else Inventory::Modify(peer, item_id, item_count);
							}
							if (item_id > items.size()) continue;
							received_items.emplace_back("Got " + to_string(item_info[1]) + " `#" + items[item_id].ori_name + "``."), received_items2.emplace_back(to_string(item_info[1]) + " " + items[item_id].ori_name);
						}
						if (not aaaa) {
							CAction::Positioned(peer, pInfo(peer)->netID, "audio/piano_nice.wav", 0);
							VarList::OnConsoleMessage(peer, "You've purchased `o" + item_name + "`` for `$" + Set_Count(price) + "`` " + (voucher == false ? "Gems" : "Vouchers") + ".\nYou have `$" + Set_Count((voucher == false ? pInfo(peer)->gems : pInfo(peer)->voucher)) + "`` " + (voucher == false ? "Gems" : "Vouchers") + " left." + "\n" + join(received_items, "\n"));
							VarList::OnStorePurchaseResult(peer, "You've purchased `o" + item_name + "`` for `$" + Set_Count(price) + "`` " + (voucher == false ? "Gems" : "Vouchers") + ".\nYou have `$" + Set_Count((voucher == false ? pInfo(peer)->gems : pInfo(peer)->voucher)) + "`` " + (voucher == false ? "Gems" : "Vouchers") + " left." + "\n\n`5Received: ``" + join(received_items2, ", ") + "\n");
						}
						return;
					}
				fail:
					CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
					VarList::OnStorePurchaseResult(peer, "You don't have enough space in your inventory to buy that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
					return;
				fail_2:
					CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
					VarList::OnStorePurchaseResult(peer, "You already have this Pet-Ai");
					return;
				fail_3:
					CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
					VarList::OnStorePurchaseResult(peer, "OUT OF STOCK");
					return;
				}
				list = j["i"].get<std::vector<int>>();
				getcount = j["h"].get<int>();
				get_counted = j["h"].get<int>();
				slot = j["c"].get<int>();
				token = j["t"].get<int>();
				random_pack = j["random"].get<int>();
				int totaltoken = 0, tokencount = 0, mega_token = 0, inventoryfull = 0;
				Inventory::Modify(peer, 1486, tokencount);
				Inventory::Modify(peer, 6802, mega_token);
				totaltoken = tokencount + (mega_token * 100);
				std::vector<std::pair<int, int>> receivingitems;
				if (token == 0 ? price > pInfo(peer)->gems : totaltoken < token) {
					CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
					VarList::OnStorePurchaseResult(peer, "You can't afford `o" + item_name + "``!  You're `$" + (token == 0 ? "" + Set_Count(price - pInfo(peer)->gems) + "`` Gems short." : "" + Set_Count(token - totaltoken) + "`` Growtokens short."));
				}
				else {
					if (free >= slot) {
						std::string received = "", received2 = "";
						if (item == "basic_splice") {
							slot++;
							receivingitems.emplace_back(11, 10);
						}
						if (item == "race_packa") {
							slot++;
							receivingitems.emplace_back(11, 10);
						}
						for (int i = 0; i < slot; i++) receivingitems.emplace_back((random_pack == 1 ? list[rand() % list.size()] : list[i]), getcount);
						for (int i = 0; i < slot; i++) {
							int itemcount = 0;
							if (receivingitems[i].first == 1438) Epic_Quest::Add(peer, "Buy a Golden Pickaxe with Growtokens", pInfo(peer)->epicq_goldenaxe, 1, 1);
							Inventory::Modify(peer, receivingitems[i].first, itemcount);
							if (itemcount + getcount > 200) inventoryfull = 1;
						}
						if (inventoryfull == 0) {
							int i = 0;
							for (i = 0; i < slot; i++) {
								received += (i != 0 ? ", " : "") + items[receivingitems[i].first].ori_name;
								received2 += "Got " + to_string(receivingitems[i].second) + " `#" + items[receivingitems[i].first].ori_name + "``." + (i == (slot - 1) ? "" : "\n") + "";
								if (receivingitems[i].first == 1438) Epic_Quest::Add(peer, "Buy a Golden Pickaxe with Growtokens", pInfo(peer)->epicq_goldenaxe, 1, 1);
								Inventory::Modify(peer, receivingitems[i].first, receivingitems[i].second);
							}
							if (not aaaa) {
								VarList::OnConsoleMessage(peer, "You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + Set_Count(price) + "`` Gems." : "" + Set_Count(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + Set_Count(pInfo(peer)->gems - price) + "`` Gems left." : "" + Set_Count(totaltoken - token) + "`` Growtokens left.") + "\n" + received2);
								VarList::OnStorePurchaseResult(peer, "You've purchased `o" + received + "`` for `$" + (token == 0 ? "" + Set_Count(price) + "`` Gems." : "" + Set_Count(token) + "`` Growtokens.") + "\nYou have `$" + (token == 0 ? "" + Set_Count(pInfo(peer)->gems - price) + "`` Gems left." : "" + Set_Count(totaltoken - token) + "`` Growtokens left.") + "\n\n`5Received: ``" + (get_counted <= 1 ? "" : "`0" + to_string(get_counted)) + "`` " + received + "\n");
							}
							if (token == 0 and not aaaa) VarList::OnBuxGems(peer, price * -1);
							else {
								if (tokencount >= token) Inventory::Modify(peer, 1486, token *= -1);
								else {
									Inventory::Modify(peer, 1486, tokencount *= -1);
									Inventory::Modify(peer, 6802, mega_token *= -1);
									int givemegatoken = (totaltoken - token) / 100;
									int givetoken = (totaltoken - token) - (givemegatoken * 100);
									Inventory::Modify(peer, 1486, givetoken);
									Inventory::Modify(peer, 6802, givemegatoken);
								}
							}
							CAction::Positioned(peer, pInfo(peer)->netID, "audio/piano_nice.wav", 0);
						}
						else {
							CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
							VarList::OnStorePurchaseResult(peer, "You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
						}
					}
					else {
						CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
						VarList::OnStorePurchaseResult(peer, slot > 1 ? "You'll need " + to_string(slot) + " slots free to buy that! You have " + to_string(free) + " slots." : "You don't have enough space in your inventory that. You may be carrying to many of one of the items you are trying to purchase or you don't have enough free spaces to fit them all in your backpack!");
					}
				}
			}
			else {
				CAction::Positioned(peer, pInfo(peer)->netID, "audio/bleep_fail.wav", 0);
				VarList::OnStorePurchaseResult(peer, "This item was not found. Server error.");
			}
		}
	}
	static void killstore(ENetPeer* peer, std::string cch) {
		pInfo(peer)->Is_In_Dialog = false;
	}
	static void respawn(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->trading_with != -1) cancel_trade(peer, false);
		chrono::steady_clock::time_point lastCheckTime = chrono::steady_clock::now();
		auto now = chrono::steady_clock::now();
		auto elapsedTime = chrono::duration_cast<chrono::seconds>(now - lastCheckTime).count();
		if (elapsedTime >= 2) {
			lastCheckTime = now;
			pInfo(peer)->WarnRespawn = 0;
		}
		pInfo(peer)->WarnRespawn++;
		if (pInfo(peer)->WarnRespawn >= 25) {
			VarList::OnConsoleMessage(peer, "`4SPAM RESPAWN DETECTED!`o, have a nice day.");
			Punishment::Banned(peer, 6.307e+7, "Are you trying to crash the server?", "AUTO-BANNED BY SYSTEM", 76, true);
		}
		Player_Respawn(peer, false, 0, (cch.find("action|respawn_spike") != string::npos) ? false : true);
	}
	static void validate_world(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", replace_str2(cch, "\n", "|"));
		if (t_.size() < 3) return;
		std::string Name = t_[3];
		transform(Name.begin(), Name.end(), Name.begin(), ::toupper);
		int Available = 0;
		if (fs::is_directory("database/worlds/" + Name + "_.json")) Available = 1;
		CAction::Log(peer, "action|world_validated\navailable|" + to_string(Available) + "\nworld_name|" + Name + "\n");
	}
	static void inventoryfavuitrigger(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->Fav_Items.empty()) {
			VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wFavorited Items``|left|13814|\nadd_spacer|small|\nadd_textbox|You have not favorited any item yet.|left|\nadd_spacer|small|\nend_dialog|unfavorite_items_dialog|Close||\n");
		}
		if (not pInfo(peer)->Fav_Items.empty()) {
			bool hasall = false;
			std::vector<int> rnm{};
			for (int i = 0; i < pInfo(peer)->Fav_Items.size(); i++) {
				int fm = 0;
				Inventory::Modify(peer, pInfo(peer)->Fav_Items[i], fm);
				if (fm == 0) rnm.emplace_back(pInfo(peer)->Fav_Items[i]);
			}
			if (rnm.empty()) hasall = true;
			if (hasall) {
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wFavorited Items``|left|13814|\nadd_spacer|small|\nadd_textbox|All favorited items are currently in your inventory. They can be unfavorited by tapping on the UNFAV button while having the item selected in your inventory.|left|\nadd_spacer|small|\nend_dialog|unfavorite_items_dialog|Close||\n");
			}
			else {
				std::string dance4me = "";
				for (int i = 0; i < rnm.size(); i++) {
					dance4me += "\nadd_checkicon|unfav_" + to_string(rnm[i]) + "|" + items[rnm[i]].name + "|frame|" + to_string(rnm[i]) + "||0|\n";
				}
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wFavorited Items``|left|13814|\nadd_spacer|small|\nadd_textbox|The following are all items you currently have favorited but are not in your inventory.|left|\nadd_textbox|Select the ones you want to unfavorite:|left|\nadd_spacer|small|\nmax_checks|" + to_string(rnm.size()) + "|\ntext_scaling_string|DEFIBRILLATOR|" + dance4me + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|unfavorite_items_dialog|Close|Unfavorite|\n");
			}
		}
	}
	static void itemfavourite(ENetPeer* peer, std::string cch) {
		std::vector<std::string> t_ = explode("|", cch);
		if (t_.size() < 4) return;
		int id_ = std::atoi(explode("\n", t_[3])[0].c_str()), got = 0;
		if (id_ > items.size() || id_ <= 0) return;
		Inventory::Modify(peer, id_, got);
		if (got == 0) return;
		bool found = false;
		for (int i = 0; i < pInfo(peer)->Fav_Items.size(); i++) {
			if (pInfo(peer)->Fav_Items[i] == id_) {
				pInfo(peer)->Fav_Items.erase(pInfo(peer)->Fav_Items.begin() + i);
				found = true;
				continue;
			}
		}
		if (!found) {
			if (pInfo(peer)->Fav_Items.size() >= 20) {
				VarList::OnConsoleMessage(peer, "You cannot favorite any more items. Remove some from your list and try again.");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You cannot favorite any more items. Remove some from your list and try again.", 0, 1);
				return;
			}
			else pInfo(peer)->Fav_Items.emplace_back(id_);
		}
		VarList::OnFavItemUpdated(peer, id_, (found ? 0 : 1));
	}
	static void store(ENetPeer* peer, std::string cch) {
		if (cch.find("location|bottommenu") != string::npos || cch.find("location|gem") != string::npos || cch.find("location|pausemenu") != string::npos) shop_tab(peer, "tab1");
	}
	static void communitytabs(ENetPeer* peer, std::string cch) {
		if (cch.find("type|community_official") != string::npos) {
			DialogHandle::Community_Hub(peer, "community_official");
			return;
		}
		if (cch.find("type|community_influencervideos") != string::npos) {
			DialogHandle::Community_Hub(peer, "community_influencervideos");
			return;
		}
	}
	static void dailychallengemenu(ENetPeer* peer, std::string cch) {
		EventPool::Load::DailyC_Leaderboard();
		std::string top = "", claimed = "", banner = ""; int id = 0, ranks = 0;
		if (Event()->dailyc_name == "Fish Frenzy") {
			id = 7072;
			banner = "\nadd_image_button||interface/large/gui_event_fishing.rttex|bannerlayout|||";
		}
		if (Event()->dailyc_name == "Surgeon") {
			id = 7068;
			banner = "\nadd_image_button||interface/large/gui_event_surgery_info.rttex|bannerlayout|||";
		}
		if (Event()->dailyc_name == "Geiger") {
			id = 2204;
			banner = "\nadd_image_button||interface/large/gui_event_geigar.rttex|bannerlayout|||";
		}
		if (Event()->dailyc_name == "Crimewave") {
			id = 2302;
			banner = "\nadd_image_button||interface/large/gui_event_crimewave.rttex|bannerlayout|||";
		}
		if (Event()->dailyc_name == "Mining") {
			id = 14526;
			banner = "\nadd_image_button||interface/large/gui_mining_banner1.rttex|bannerlayout|||";
		}
		std::vector<std::pair<long long int, string>>::iterator pa = find_if(Event()->top_dailyc.begin(), Event()->top_dailyc.end(), [&](const pair < long long int, string>& element) { return element.second == pInfo(peer)->tankIDName; });
		if (pa != Event()->top_dailyc.end()) {
			ranks = distance(Event()->top_dailyc.begin(), pa) + 1;
			if (Event()->DailyChallenge == false) claimed = "\nadd_button|claim_dailyc_rewards|Claim Rewards|0|0|\nadd_custom_textbox|`3Reward`o: " + a + (ranks == 1 ? "1 Challenge Crown, 5 Diamond Locks and 50 World Locks" : ranks == 2 ? "1 Flaming Aura, 4 Diamond Locks and 50 World Locks" : ranks == 3 ? "1 Crystal Cape, 3 Diamond Locks and 50 World Locks" : ranks == 4 ? "2 Diamond Locks and 50 World Locks" : "1 Diamond Locks and 50 World Locks") + ".|size:small;color:255,255,255,255;icon:1796;|";
			if (Event()->top_dailyc[pa - Event()->top_dailyc.begin()].first > 0) top = "\nadd_smalltext|`3Your Rank`o: " + to_string(distance(Event()->top_dailyc.begin(), pa) + 1) + "    `3Total Points`o: " + Set_Count(Event()->top_dailyc[pa - Event()->top_dailyc.begin()].first) + "|";
		}
		long long time_ = time(nullptr);
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|Daily Challenge|left|3142|\nadd_spacer|small|\nadd_textbox|`o" + (Event()->DailyChallenge ? "Daily Challenge time remaining : " + Time::Playmod(Event()->daily_current_time - time_) + "." : "The next Daily Challenge is in " + Time::Playmod(Event()->daily_wait_time - time_) + ".") + "|left|" + (Event()->DailyChallenge ? "\nadd_label_with_icon|small|`oThe Daily Challenge is `2" + Event()->dailyc_name + "``.|left|" + to_string(id) + "|" + banner + "\nadd_textbox|`oYou need to be a `5Supporter`` or `5Super Supporter`` to participate in the daily challenge|left|\nadd_spacer|small|\nadd_textbox|`oThe top players today are:|left|\nadd_spacer|small|" + Event()->top_dailyc_list + "|\nadd_spacer|small|\nadd_smalltext|`#(Scores are updated every 20 seconds)|left|\nadd_spacer|small|\nadd_button|dailyc_reward|`oRewards|0|0|" : "\nadd_spacer|small|" + (ranks == 0 ? "" : top + claimed)) + "\nend_dialog|dailyc|Close||\nadd_quick_exit|");
	}
	static void iotm_shop(ENetPeer* peer, std::string cch) {
		DialogHandle::Iotm_Shop(peer);
	}
	static void opc_shop(ENetPeer* peer, std::string cch) {
		DialogHandle::Opc_Shop(peer);
	}
	static void storenavigate(ENetPeer* peer, std::string cch) {
		if (cch.find("item|locks\nselection|upgrade_backpack") != string::npos) shop_tab(peer, "tab4_upgrade_backpack");
		if (cch.find("item|main") != string::npos) shop_tab(peer, "tab1_gatling_gum");
		if (cch.find("item|main\nselection|gems_bundle06") != string::npos) shop_tab(peer, "tab1_gems_shop");
		if (cch.find("item|token\nselection|megaphone") != string::npos) shop_tab(peer, "tab5_megaphone");
		if (cch.find("item|main\nselection|deposit") != string::npos) DialogHandle::Deposit(peer);
	}
	static void eventmenu(ENetPeer* peer, std::string cch) {
		DialogHandle::Event_Leaderboard(peer, "Seasonal_Clash", 500);
	}
	static void showredeemcodewindow(ENetPeer* peer, std::string cch) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wRedeem Your Code!``|left|982|\nadd_spacer|small|\nadd_textbox|ABOUT CODE REDEMPTION|left|\nadd_smalltext|- Pay attention to the redemption conditions and validity period. A code cannot be redeemed after it expires.|left|\nadd_smalltext|- Each redemption code can only be used once.|left|\nadd_smalltext|- After successful code redemption, your redeemed item will be delivered to your Inventory. For issues, contact Owner Server.|left|\nadd_smalltext|- The Redemption Code has 10 characters, a combination of capital letters and numbers.|left|\nadd_spacer|small|\nadd_text_input|redeemcode|||16|\nadd_spacer|small|\nadd_button|cancel|`wCancel|noflags|\nadd_custom_button|redeem_code_button|textLabel:`wRedeem;anchor:_button_cancel;left:1;margin:40,0;|\nadd_spacer|small|\nend_dialog|redeem_code|||", 500);
	}
	static void friends(ENetPeer* peer, std::string cch) {
		DialogHandle::Social_Portal(peer);
	}
	static void handle_gems_shop(ENetPeer* peer, std::string cch) {
		shop_tab(peer, "tab1");
	}
	static void openPiggyBank(ENetPeer* peer, std::string cch) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`w Piggy Bank``|left|14588|\nadd_image_button||interface/large/gui_shop_buybanner3.rttex|bannerlayout|flag_frames:4,10,0,9|flag_surfsize:512,200|\nadd_spacer|small|\nadd_textbox|You have banked: " + Set_Count(pInfo(peer)->Banked_Piggy) + " / 350,000 Gems.|left|\nadd_spacer|small|\nadd_textured_progress_bar|interface/large/gui_event_bar2.rttex|0|4||" + to_string(pInfo(peer)->Banked_Piggy) + "|350000|relative|0.8|0.02|0.07|1000|64|0.007|barBG_2|\nadd_spacer|small|\nadd_custom_button|piggy_bank_bg_img_0|image:game/tiles_page1.rttex;image_size:32,32;frame:22,1;width:0.05;state:disabled;preset:listitem;margin_rself:0,0;anchor:barBG_2;top:0;left:-0.005;display:inline_free;|\nadd_custom_button|piggy_bank_bg_img_150|image:game/tiles_page16.rttex;image_size:32,32;frame:22,26;width:0.07;state:disabled;preset:listitem;margin_rself:0.2,0;anchor:barBG_2;top:0;left:0.5;display:inline_free;|\nadd_custom_button|piggy_bank_bg_img_300|image:game/tiles_page16.rttex;image_size:32,32;frame:23,26;width:0.07;state:disabled;preset:listitem;margin_rself:0.6,0;anchor:barBG_2;top:0;left:1;display:inline_free;|\nadd_custom_label|0|target:barBG_2;top:1.35;left:0.01;size:small;|\nadd_custom_label|175K|target:barBG_2;top:1.35;left:0.5;size:small;|\nadd_custom_label|350K|target:barBG_2;top:1.35;left:1;size:small;|\nreset_placement_x|\nadd_spacer|small|\nadd_textbox|Complete Life Goals, Daily Bonuses and Daily Quests to add gems to your Piggy Bank!|left|\nadd_textbox|- Life Goals - 15K Gems|left|\nadd_textbox|- Daily Bonuses - 10K Gems|left|\nadd_textbox|- Daily Quests - 20K Gems|left|\nadd_spacer|small|\nreset_placement_x|" + (pInfo(peer)->pg_bank == 0 ? "\nadd_custom_button|Buy_Piggy|textLabel:BUY FOR 400 COIN;middle_colour:431888895;border_colour:431888895;margin:280,0;|" : "\nadd_custom_button|Claim_Piggy_Bank|textLabel:CLAIM YOUR GEMS;middle_colour:431888895;border_colour:431888895;margin:260,0;" + a + (pInfo(peer)->Banked_Piggy >= 350000 ? "state:enable;" : "state:disabled;") + "|") + "\nadd_spacer|small|\nadd_spacer|small|\nend_dialog|Piggy_Bank|||\nadd_quick_exit|", 500);
	}
	static void openPageFreeGems(ENetPeer* peer, std::string cch) {
		DialogHandle::EarnFreeGems(peer);
	}
	static void showdungeonsui(ENetPeer* peer, std::string cch) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wDungeons``|left||image:game/tiles_page17.rttex;frame:4,30;frameSize:32;|\nadd_spacer|small|\nadd_textbox|Go on an adventure, explore dungeons and use their unique currency to upgrade your abilities. Just remember, what happens in the dungeon stays in the dungeon!|left|\nadd_spacer|small|\nadd_custom_button|showdungeoninvitefriends|image:game/tiles_page17.rttex;image_size:32,32;frame:4,31;margin_rself:0.15,0;width:0.09;|\nadd_custom_label|Invite Friends|target:showdungeoninvitefriends;top:0.5;left:2.5;size:medium;|\nreset_placement_x|\nadd_textbox| |left|\nadd_textbox| |left|\nadd_textbox| |left|\nadd_custom_margin|x:0;y:16|\nadd_custom_button|startdungeonbtn|textLabel:Start (5 Scrolls);middle_colour:3389566975;border_colour:3389566975;display:block;|\nreset_placement_x|\nadd_custom_margin|x:0;y:16|\nadd_spacer|small|\nadd_smalltext|`6Warning: Leaving the Dungeon at any point will prevent re-entry into the same world. All ability upgrades will be lost as well.``|left|\nadd_spacer|small|\nadd_label_with_icon|small|Scrolls: 20/20|left|14730|\nadd_smalltext|`#More in: `#--``|left|\nadd_spacer|small|\nadd_custom_margin|x:0;y:16|\nadd_custom_button|purchasescrollsbtn|textLabel:Purchase Scrolls;middle_colour:431888895;border_colour:431888895;display:block;|\nreset_placement_x|add_custom_margin|x:0;y:16|\nadd_spacer|small|\nadd_image_button|noclick|interface/large/gui_dungeons_banner.rttex|bannerlayout|flag_frames:3,2,0,0|flag_surfsize:512,150|\nadd_spacer|small|\nadd_custom_margin|x:0;y:16|\nadd_custom_button|dungeonplayerankinformation|textLabel:League Standings;middle_colour:3434645503;border_colour:3434645503;display:block;|\nreset_placement_x|\nadd_spacer|small|\nadd_custom_margin|x:0;y:16|\nadd_custom_margin|x:0;y:16|\nadd_custom_button|dungeoninformationbtn|textLabel:Dungeon Information;middle_colour:3434645503;border_colour:3434645503;display:block;|reset_placement_x|\nadd_spacer|small|\nadd_custom_margin|x:0;y:16|\nreset_placement_x|\nend_dialog|handledungeonsui|Close||\nadd_quick_exit|");
	}
	static void leaderboardBtnClicked(ENetPeer* peer, std::string cch) {
		EventPool::Load::Anniversary_Leaderboard();
		std::string contribute = "";
		std::vector<std::pair<long long int, std::string>>::iterator pa2 = find_if(Event()->top_anniversary.begin(), Event()->top_anniversary.end(), [&](const pair < long long int, string>& element) { return to_lower(element.second) == to_lower(pInfo(peer)->tankIDName); });
		if (pa2 != Event()->top_anniversary.end()) contribute = "\nadd_textbox|Your rank: `9" + to_string(distance(Event()->top_anniversary.begin(), pa2) + 1) + "``|left|\nadd_textbox|Your Points: `9" + Set_Count(Event()->top_anniversary[pa2 - Event()->top_anniversary.begin()].first) + "``|left|";
		else contribute = "\nadd_textbox|Your rank: `9---``|left|\nadd_textbox|Your Points: `90``|left|";
		if (Event()->Anniversary) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`w\nadd_label|big|`8Anniversary Global Leaderboard``|left|\nadd_spacer|small|\nadd_textbox|Time Remaining: `2" + Time::Event(Event()->Anniversary_Time - time(nullptr)) + "``|left|\nadd_spacer|small|\nadd_textbox|The best party hosts will be awarded the title of `5PA```9RTY`` `eAN```5IM```9AL``!|left|\nadd_spacer|small|" + contribute + "\nadd_spacer|small|" + Event()->top_anniversary_list + "\nadd_spacer|small|\nadd_smalltext|`8NOTE: Scores are updated every 20 seconds.``|\nadd_spacer|small|\nadd_button|info_btn1|Information|no_flags|0|0|\nadd_spacer|small|\nadd_custom_button|rewards_info_btn|textLabel:Rewards;middle_colour:-2043447809;border_colour:-2043447809;|\nadd_custom_break|\nadd_spacer|small|\nend_dialog|euphoriaEventUI|Close||\nadd_quick_exit|\n", 500);
	}
	static void euphoriaBtnClicked(ENetPeer* peer, std::string cch) {
		if (Event()->Anniversary) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_image_button|noclick|interface/large/anni_toparty.rttex|bannerlayout|||\nadd_spacer|small|\nadd_textbox|The current world is `10%`` of the way towards starting the party. To help the world reach 100% and start the party, let's get creative and use some fun party items!|left|\nadd_spacer|small|\nadd_textbox|Remember, the points you gain count towards your personal rank, so let's make this party as fun and memorable as possible!|left|\nadd_spacer|small|\nadd_button|info_btn|Information|no_flags|0|0|\nadd_spacer|small|\nend_dialog|euphoriaEventUI|Close||\nadd_quick_exit|\n", 500);
	}
	static void trade_started(ENetPeer* peer, std::string cch) {
		try {
			std::vector<std::string> t_ = explode("|", cch);
			if (t_.size() < 4) return;
			int netID = std::atoi(explode("\n", t_[3])[0].c_str());
			if (netID == -1) return;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != pInfo(peer)->world or pInfo(cp_)->tankIDName == pInfo(peer)->tankIDName) continue;
				if ((to_lower(pInfo(cp_)->tankIDName).find(to_lower(pInfo(peer)->last_wrenched)) != std::string::npos && pInfo(peer)->last_wrenched.length() >= 3 && pInfo(peer)->last_wrenched.length() != pInfo(cp_)->tankIDName.length()) || to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched) || (not pInfo(cp_)->d_name.empty() && (to_lower(pInfo(cp_)->d_name).find(to_lower(pInfo(peer)->last_wrenched)) != std::string::npos && pInfo(peer)->last_wrenched.length() >= 3 && pInfo(peer)->last_wrenched.length() != pInfo(cp_)->d_name.length()) || to_lower(pInfo(cp_)->d_name) == to_lower(pInfo(peer)->last_wrenched))) {
					for (int c_ = 0; c_ < pInfo(cp_)->friends.size(); c_++) {
						if (to_lower(pInfo(cp_)->friends[c_].name) == to_lower(pInfo(peer)->tankIDName)) {
							if (pInfo(cp_)->friends[c_].block_trade) return;
						}
					}
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->tankIDName)) {
						VarList::OnConsoleMessage(peer, "You trade all your stuff to yourself in exchange for all your stuff.");
						return;
					}
					if (pInfo(cp_)->trading_with != -1 and pInfo(cp_)->trading_with != pInfo(peer)->netID) {
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That person is busy.", 0, 0);
						pInfo(peer)->block_trade = false, pInfo(peer)->trading_with = -1;
						VarList::OnForceTradeEnd(peer);
						return;
					}
					pInfo(peer)->trading_with = pInfo(cp_)->netID;
					pInfo(peer)->trade_accept = 0;
					pInfo(cp_)->trade_accept = 0;
					gamepacket_t p;
					p.Insert("OnStartTrade");
					p.Insert(fixchar2(get_player_nick(cp_))), p.Insert(pInfo(cp_)->netID), p.CreatePacket(peer);
					if (pInfo(cp_)->trading_with != -1) {
						VarList::OnTradeStatus(peer, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "'s offer.``", "locked|0\nreset_locks|1\naccepted|0");
						VarList::OnTradeStatus(peer, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "'s offer.``", "locked|0\naccepted|1");
						VarList::OnTradeStatus(peer, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "'s offer.``", "locked|0\nreset_locks|1\naccepted|0");
						VarList::OnTradeStatus(peer, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "'s offer.``", make_trade_offer(pInfo(cp_), true) + "locked|0\nreset_locks|1\naccepted|0");
						VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "'s offer.``", "locked|0\nreset_locks|1\naccepted|0");
						VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "'s offer.``", "locked|0\naccepted|1");
						VarList::OnTradeStatus(cp_, pInfo(cp_)->netID, "", "`o" + get_player_nick(cp_) + "'s offer.``", make_trade_offer(pInfo(cp_), true) + "locked|0\nreset_locks|1\naccepted|0");
						VarList::OnTradeStatus(cp_, pInfo(peer)->netID, "", "`o" + get_player_nick(peer) + "'s offer.``", make_trade_offer(pInfo(peer), true) + "locked|0\nreset_locks|1\naccepted|0");
						return;
					}
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/cash_register.wav", 0);
					VarList::OnConsoleMessage(cp_, "`#TRADE ALERT:`` `w" + get_player_nick(peer) + "`` wants to trade with you!  To start, use the `wWrench`` on that person's wrench icon, or type `w/trade " + get_player_nick(peer));
					return;
				}
			}
		}
		catch (const std::out_of_range& e) {
			std::cout << e.what() << std::endl;
		}
	}
	static void dialog_return(ENetPeer* peer, std::string cch) {
		TextScanner parser(cch);
		std::string dialog = "";
		if (parser.try_get("dialog_name", dialog)) {
			if (dialogMap.find(dialog) != dialogMap.end()) {
				if (pInfo(peer)->trading_with != -1 and cch.find("trade_") == string::npos) {
					cancel_trade(peer, false, true);
					return;
				}
				dialogMap[dialog](peer, cch);
			}
			else {
				if (cch.find("dialog_name|dispshelf") != string::npos or cch.find("dialog_name|abondonguild") != string::npos or cch.find("dialog_name|portrait") != string::npos or cch.find("dialog_name|artcanvas") != string::npos or cch.find("dialog_name|mannequin_edit") != string::npos or cch.find("dialog_name|vip_edit") != string::npos or cch.find("dialog_name|weatherspcl") != string::npos or cch.find("dialog_name|itemaddedtosucker") != string::npos or cch.find("dialog_name|itemremovedfromsucker") != string::npos or cch.find("dialog_name|itemsucker_block") != string::npos or cch.find("dialog_name|autoactionblock") != string::npos or cch.find("dialog_name|blaster") != string::npos or cch.find("dialog_name|switcheroo_edit") != string::npos or cch.find("dialog_name|door_edit") != string::npos or cch.find("dialog_name|vending") != string::npos or cch.find("dialog_name|displayblock") != string::npos or cch.find("dialog_name|friends_ignore") != string::npos or cch.find("dialog_name|mute_friend") != string::npos or cch.find("dialog_name|block_friend") != string::npos or cch.find("dialog_name|friends_message") != string::npos or cch.find("dialog_name|friends_edit") != string::npos or cch.find("dialog_name|friends_options") != string::npos or cch.find("dialog_name|send_mailbox") != string::npos or cch.find("dialog_name|mute_all_friends") != string::npos or cch.find("dialog_name|remove_all_friends") != string::npos or cch.find("dialog_name|block_all_friends") != string::npos or cch.find("dialog_name|all_friends") != string::npos or cch.find("dialog_name|show_guild_logs") != string::npos or cch.find("dialog_name|guild_statement_edit") != string::npos or cch.find("dialog_name|guild_members_options") != string::npos or cch.find("dialog_name|guildmembers") != string::npos or cch.find("dialog_name|leave_guild") != string::npos or cch.find("dialog_name|Guild_Notebook") != string::npos or cch.find("dialog_name|guild_member_role_change_finish") != string::npos or cch.find("dialog_name|guild_member_role_change") != string::npos or cch.find("dialog_name|guild_member_remove_finish") != string::npos or cch.find("dialog_name|guild_member_remove") != string::npos or cch.find("dialog_name|guild_member_edit") != string::npos or cch.find("dialog_name|friends") != string::npos or cch.find("dialog_name|unaccess") != string::npos or cch.find("dialog_name|confirmguild") != string::npos or cch.find("dialog_name|createguild") != string::npos or cch.find("dialog_name|requestcreateguildpage") != string::npos or cch.find("dialog_name|acceptaccess") != string::npos or cch.find("dialog_name|worlds_list") != string::npos or cch.find("dialog_name|lock_edit") != string::npos or cch.find("dialog_name|editguildlock") != string::npos or cch.find("dialog_name|create_guild_mascot") != string::npos or cch.find("dialog_name|trash_item") != string::npos or cch.find("dialog_name|drop_item") != string::npos or cch.find("dialog_name|trash_item2") != string::npos) call_dialog(peer, cch);
				else {
					const seconds cooldownDuration(5);
					auto now = steady_clock::now();
					if (duration_cast<seconds>(now - pInfo(peer)->lastPacketTime) < cooldownDuration) {
						VarList::OnAddNotification(peer, "`wWarning from `4System`w: You were `4DETECTED`` using a script!", "interface/atomic_button.rttex", "audio/hub_open.wav");
						Peer_Disconnect(peer, 0);
						return;
					}
					pInfo(peer)->lastPacketTime = now;
					Logger::Info("WARNING", "Unhandle DIALOG_RETURN -> [" + cch + "] Sent by " + pInfo(peer)->tankIDName);	
					SystemPool::SaveLogsUnhandle_Packet("DIALOG_RETURN -> [" + cch + "] Sent by " + pInfo(peer)->tankIDName);
				}
			}
		}
	}
	static void quit(ENetPeer* peer, std::string cch) {
		Peer_Disconnect(peer, 0);
	}
	static void quit_to_exit(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->world != "") {
			ServerPool::SaveDatabase::Players(pInfo(peer), false);
			Exit_World(peer);
		}
	}
	static void gohomeworld(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->world.empty()) {
			if (pInfo(peer)->home_world.empty()) {
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`9No Home World Set ``|left|1432|\nadd_spacer|small|\nadd_textbox|Use /sethome to assign the current world as your home world.|left|\nadd_spacer|small|\nend_dialog||OK||");
				VarList::OnFailedToEnterWorld(peer);
			}
			else {
				VarList::OnConsoleMessage(peer, "VallenSasukely warping to home world `5" + pInfo(peer)->home_world + "``...");
				std::string world_name = pInfo(peer)->home_world;
				Enter_World(peer, world_name);
			}
		}
	}
	static void join_request(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->tankIDName.empty() and pInfo(peer)->tankIDPass.empty()) {
			VarList::OnFailedToEnterWorld(peer);
			return;
		}
		if (pInfo(peer)->world.empty()) {
			if (pInfo(peer)->last_world_enter + 500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				pInfo(peer)->last_world_enter = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				std::vector<std::string> t_ = explode("|", cch);
				if (t_.size() < 3) return;
				std::string world_name = explode("\n", t_[2])[0];
				transform(world_name.begin(), world_name.end(), world_name.begin(), ::toupper);
				Enter_World(peer, world_name);
			}
		}
	}
	static void world_button(ENetPeer* peer, std::string cch) {
		if (pInfo(peer)->world.empty()) {
			std::vector<std::string> t_ = explode("|", cch);
			if (t_.size() < 3) return;
			std::string dialog = explode("\n", t_[2])[0];
			if (dialog == "w1_") world_menu(peer, false);
			else {
				std::string c_active_worlds = "", world_category_list = "";
				if (dialog == "_catselect_") {
					world_category_list = "\nadd_button|Default|w1_|0.7|3529161471|\nadd_button|Top Worlds|w2_|0.7|3529161471|\nadd_button|Random|w1_|0.7|3529161471|\nadd_button|Your Worlds|w3_|0.7|3529161471|";
					for (int i = 1; i < Environment()->world_rate_types.size(); i++) world_category_list += "\nadd_button|" + (world_category(i)) + "|w" + to_string(i + 3) + "_|0.7|3529161471|";
				}
				else {
					if (dialog == "w2_") c_active_worlds = a + "\nadd_heading|" + (Environment()->List_World_Menu.empty() ? "The list should update in few minutes" : "Top Worlds") + "|", c_active_worlds += Environment()->List_World_Menu;
					else if (dialog == "w3_") {
						c_active_worlds = pInfo(peer)->worlds_owned.size() != 0 ? "\nadd_heading|Your Worlds (" + to_string(pInfo(peer)->worlds_owned.size()) + ")|" : "\nadd_heading|You don't have any worlds.<CR>|";
						for (int w_ = 0; w_ < (pInfo(peer)->worlds_owned.size() >= 32 ? 32 : pInfo(peer)->worlds_owned.size()); w_++) c_active_worlds += "\nadd_floater|" + pInfo(peer)->worlds_owned[w_] + "|0|0.5|2147418367";
					}
					else {
						int world_rateds = std::atoi(dialog.substr(1, dialog.length() - 1).c_str()) - 3;
						if (world_rateds > Environment()->world_rate_types.size()) return;
						c_active_worlds = "\nadd_heading|" + (world_category(world_rateds)) + " Worlds|\nset_max_rows|4|";
						bool added_ = false;
						for (int i = 0; i < (Environment()->world_rate_types[world_rateds].size() > 5 ? 6 : Environment()->world_rate_types[world_rateds].size()); i++) {
							std::string world = Environment()->world_rate_types[world_rateds][i].substr(0, Environment()->world_rate_types[world_rateds][i].find("|"));
							c_active_worlds += "\nadd_floater|" + world + "|" + to_string((i + 1) * -1) + "|0.5|3417414143";
							added_ = true;
						}
						if (added_ == false) c_active_worlds += "\nadd_heading|There isn't any active worlds yet.<CR>|";
					}
					if (dialog != "w3_") {
						std::string recently_visited = "\nset_max_rows|-1|";
						for (auto it = pInfo(peer)->last_visited_worlds.rbegin(); it != pInfo(peer)->last_visited_worlds.rend(); ++it) recently_visited += "\nadd_floater|" + *it + "|0|0.5|3417414143";
						c_active_worlds += "\nadd_heading|Recently Visited Worlds<CR>|" + recently_visited;
					}
				}
				VarList::OnRequestWorldSelectMenu(peer, (dialog == "_catselect_" ? world_category_list : "add_filter|" + c_active_worlds));
			}
		}
	}
};