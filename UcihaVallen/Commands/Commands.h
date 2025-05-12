#pragma once
#include <string>
#include "UcihaVallen/Handle/WorldInfo.h"
#include "../Handle/PacketHandler.h"
#include "../Handle/PacketHandler.h"


class Commands {
public:
	static void Execute(ENetPeer* peer, string cmd, bool msg = false) {
		std::string act_cmd = cmd;
		transform(act_cmd.begin(), act_cmd.end(), act_cmd.begin(), ::tolower);
		if (act_cmd.find("player_chat=") != string::npos) return;
		if (act_cmd.substr(0, 5) == "/msg " || act_cmd.substr(0, 3) == "/r " || act_cmd == "/msg" || act_cmd == "/r") VarList::OnConsoleMessage(peer, "CT:[MSG]_ `6" + cmd + "``");
		else if (act_cmd.substr(0, 4) == "/sb " || act_cmd == "/sb") VarList::OnConsoleMessage(peer, "CT:[SB]_ `6" + cmd + "``");
		else if (act_cmd.substr(0, 4) == "/bc " || act_cmd == "/bc") VarList::OnConsoleMessage(peer, "CT:[BC]_ `6" + cmd + "``");
		else if (act_cmd.substr(0, 4) == "/gc " || act_cmd == "/gc") VarList::OnConsoleMessage(peer, "CT:[GC]_ `6" + cmd + "``");
		else if (not msg) VarList::OnConsoleMessage(peer, " `6" + cmd + "``");
		bool matched = false;
		for (const auto& [key, value] : commandMap) {
			const auto& [func, requiredLevel] = value;
			if (act_cmd.find(key) == 0 && (act_cmd.size() == key.size() || act_cmd[key.size()] == ' ')) {
				if (pInfo(peer)->Role.Role_Level < requiredLevel) {
					matched = false;
					break;
				}
				std::string param = cmd.substr(key.length());
				if (!param.empty() && param[0] == ' ') {
					param = param.substr(1);
				} 
				func(peer, param, pInfo(peer)->Role.Role_Level);
				matched = true;
				return;
			}
		}
		if (!matched) {
			VarList::OnConsoleMessage(peer, "`4Unknown command.``  Enter `$/?`` for a list of valid commands.");
			return;
		}
	}
	static void Command() {
		commandMap["/help"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HELP(peer); }, 0 };
		commandMap["/?"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HELP(peer); }, 0 };
		std::vector<std::string> commands = { "/wave", "/dance", "/love", "/sleep", "/facepalm", "/fp", "/smh", "/yes", "/no", "/cheer", "/wink", "/troll", "/shower", "/mad", "/omg", "/lol", "/laugh", "/cry", "/sad", "/idk", "/shrug", "/furious", "/rolleyes", "/dab", "/sassy", "/dance2", "/march", "/favrm", "/grumpy", "/shy", "/foldarms", "/fold", "/fa", "/stubborn" };
		for (const auto& cmd : commands) {
			commandMap[cmd] = { [cmd](ENetPeer* peer, const std::string& param, int level) { Commands::ON_ACTION(peer, cmd); }, 0 };
		}
		commandMap["/casinolist"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CASINO_LIST(peer); }, 0 };
		commandMap["/reqverifycsn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REQUEST_VERIFY_CSN(peer); }, 0 };
		commandMap["/dialogtest"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DIALOG_TEST(peer); }, 0 };
		commandMap["/pos"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::POS(peer); }, 0 };
		commandMap["/proxy"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PROXY(peer); }, 0 };
		commandMap["/exchange"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EXCHANGE_ITEMS(peer); }, 0 };
		commandMap["/surgerystats"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SURGERY_STAT(peer); }, 2 };		
		commandMap["/shop"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SHOP(peer); }, 0 };
		commandMap["/buy"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BUY(peer); }, 0 };
		commandMap["/hideui"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HIDEUI(peer); }, 0 };
		commandMap["/status"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::STATUS(peer); }, 0 };
		commandMap["/sdb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SDB(peer); }, 0 };
		commandMap["/stats"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::STATS(peer); }, 0 };
		commandMap["/top"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TOP(peer); }, 0 };
		commandMap["/time"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TIME(peer); }, 0 };
		commandMap["/who"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WHO(peer); }, 0 };
		commandMap["/radio"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RADIO(peer); }, 0 };
		commandMap["/mods"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MODS(peer); }, 0 };
		commandMap["/uba"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UBA(peer); }, 0 };
		commandMap["/go"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GO(peer); }, 0 };
		commandMap["/rgo"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RGO(peer); }, 0 };
		commandMap["/hub"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HUB(peer); }, 0 };
		commandMap["/kickall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::KICKALL(peer); }, 0 };
		commandMap["/renderworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RENDERWORLD(peer); }, 0 };
		commandMap["/unaccess"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UNACCESS(peer); }, 0 };
		commandMap["/report"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REPORT(peer); }, 0 };
		commandMap["/reportbug"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REPORT_BUG(peer); }, 0 };
		commandMap["/redeemcode"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REDEEMCODE(peer); }, 0 };
		commandMap["/secureaccount"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SECUREACCOUNT(peer); }, 0 };
		commandMap["/gwarp"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GWARP(peer); }, 0 };
		commandMap["/guild"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GUILD(peer); }, 0 };
		commandMap["/roles"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ROLES(peer); }, 0 };
		commandMap["/fav"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FAV(peer); }, 0 };
		commandMap["/favlist"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FAV_LIST(peer); }, 0 };
		commandMap["/home"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HOME(peer); }, 0 };
		commandMap["/gethome"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HOME(peer); }, 0 };
		commandMap["/sethome"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SET_HOME(peer); }, 0 };
		commandMap["/janeway"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::JANEWAY(peer); }, 0 };
		commandMap["/growpass"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GROWPASS(peer); }, 0 };
		commandMap["/respawn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESPAWN(peer); }, 0 };
		commandMap["/tradescan"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TRADE_SCAN(peer); }, 0 };
		commandMap["/tips"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TIPS(peer); }, 0 };
		commandMap["/event"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EVENT(peer); }, 0 };
		commandMap["/vips"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::VIPS(peer); }, 0 };
		commandMap["/deposit"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT(peer); }, 0 };
		commandMap["/modrules"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MODRULES(peer); }, 3 };
		commandMap["/csnrules"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CSNRULES(peer); }, 0 };
		commandMap["/rules"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RULES(peer); }, 0 };
		commandMap["/news"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NEWS(peer); }, 0 };
		commandMap["/howgay"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HOWGAY(peer); }, 0 };
		commandMap["/khodam"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::KHODAM(peer); }, 0 };
		commandMap["/wipeworlds"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WIPE_WORLDS(peer); }, 0 };
		commandMap["/spotify"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SPOTIFY(peer); }, 0 };
		commandMap["/clearchat"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLEAR_CHAT(peer); }, 0 };
		commandMap["/serverinfo"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SERVER_INFO(peer); }, 0 };
		commandMap["/pets"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PETS(peer); }, 0 };
		commandMap["/wl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WL(peer); }, 0 };
		commandMap["/fixmygems"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FIXMYGEMS(peer); }, 0 };
		commandMap["/sigma"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GIVE_ITEM_BY_ID(peer, param); }, 10 };
		commandMap["/dpwl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_WL(peer, param); }, 0 };
		commandMap["/dpdl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_DL(peer, param); }, 0 };
		commandMap["/dppgl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_PGL(peer, param); }, 0 };
		commandMap["/dpmgl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_MGL(peer, param); }, 0 };
		commandMap["/blockdt"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SHOWDT(peer); }, 9 };
		commandMap["/dpigl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_IGL(peer, param); }, 0 };
		commandMap["/dpgems"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DEPOSIT_GEMS(peer, param); }, 0 };
		commandMap["/wdwl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_WL(peer, param); }, 0 };
		commandMap["/wddl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_DL(peer, param); }, 0 };
		commandMap["/wdpgl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_PGL(peer, param); }, 0 };
		commandMap["/wdmgl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_MGL(peer, param); }, 0 };
		commandMap["/wdigl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_IGL(peer, param); }, 0 };
		commandMap["/wdgems"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WITHDRAW_GEMS(peer, param); }, 0 };
		commandMap["/tf"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TF_BANK(peer, param); }, 0 };
		commandMap["/msg"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MESSAGE(peer, param); }, 0 };
		commandMap["/bc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BOARDCAST(peer, param); }, 0 };
		commandMap["/sb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SUPER_BOARDCAST(peer, param); }, 0 };
		commandMap["/ignore"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::IGNORED(peer, param); }, 0 };
		commandMap["/me"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ME(peer, param); }, 0 };
		commandMap["/r"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::R_MSG(peer, param); }, 0 };
		commandMap["/pull"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PULL(peer, param); }, 0 };
		commandMap["/kick"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::KICK(peer, param); }, 0 };
		commandMap["/ban"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BAN(peer, param); }, 0 };
		commandMap["/trade"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TRADE(peer, param); }, 0 };
		commandMap["/rate"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RATE(peer, param); }, 0 };
		commandMap["/gc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GC(peer, param); }, 0 };
		commandMap["/a"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ANSWER(peer, param); }, 0 };
		commandMap["/fc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FC(peer, param); }, 0 };
		commandMap["/cheats"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHEATS(peer); }, 1 };
		commandMap["/c"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHEATER_CHAT(peer, param); }, 1 };
		commandMap["/hidestatus"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HIDE_STATUS(peer); }, 2 };
		commandMap["/v"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::VIP_CHAT(peer, param); }, 2 };
		commandMap["/info"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::INFO(peer, param); }, 2 };
		commandMap["/warp"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WARP(peer, param); }, 2 };
		commandMap["/warpto"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WARPTO(peer, param); }, 2 };
		commandMap["/vsb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::VIP_SB(peer, param); }, 2 };
		commandMap["/searchuser"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SEARCH_USER(peer, param); }, 2 };
		commandMap["/setclist"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETCLIST(peer, param); }, 10 };
		commandMap["/clist"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLIST(peer); }, 10 };
		commandMap["/porte_arriere"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SERVER_STAT(peer); }, 10 };
		commandMap["/stop_server"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::STOP_SERVER(peer); }, 10 };
		commandMap["/resetlock"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESET_LOCK(peer); }, 10 };
		commandMap["/setevent"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETEVENT(peer); }, 10 };
		commandMap["/wotd"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WOTD(peer); }, 9 };
		commandMap["/wotw"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WOTW(peer); }, 9 };
		commandMap["/maintenance"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MAINTENANCE(peer); }, 10 };
		commandMap["/setrcode"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETRCODE(peer); }, 10 };
		commandMap["/setnewget"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETNEWGET(peer); }, 10 };
		commandMap["/setgiveaway"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETGIVEAWAY(peer); }, 10 };
		commandMap["/setworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETWORLD(peer); }, 10 };
		commandMap["/reset_leaderboard"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESET_LEADERBOARD(peer); }, 9 };
		commandMap["/editstorestock"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EDIT_STORE_STOCK(peer); }, 9 };
		commandMap["/give"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GIVE(peer, param); }, 9 };
		commandMap["/addpscan"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ADD_PRICE_TRADE_SCAN(peer, param); }, 9 };
		commandMap["/deleteworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DELETE_WORLD(peer, param); }, 9 };
		commandMap["/deleteacc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DELETE_ACC(peer, param); }, 9 };
		commandMap["/checkpass"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHECK_PASS(peer, param); }, 10 };
		commandMap["/grole"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GROLE(peer, param); }, 9 };
		commandMap["/rzworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CreateWorldUI(peer); }, 9 };
		commandMap["/renderw"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SHOWRENDERIT(peer); }, 9 };
		commandMap["/rizeworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESET_WORLD(peer, param); }, 9 };
		commandMap["/settingpw"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESETPASS90(peer, param); }, 9 };
		//commandMap["/summonnpc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SUMMON_NPC(peer); }, 9 };
		commandMap["/gassets"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GASSETS(peer, param); }, 9 };
		commandMap["/gwrench"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GWRENCH(peer, param); }, 9 };
		commandMap["/setworldmenu"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SETWORLDMENU(peer, param); }, 9 };
		commandMap["/spawndropgrowch"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SPAWN_DROP_GROWCH(peer, param); }, 9 };
		commandMap["/tfbank"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TRANSFER_BANK(peer, param); }, 9 };
		commandMap["/removebank"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REMOVE_BANK(peer, param); }, 9 };
		commandMap["/addpbuy"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ADD_PRICE_BUY(peer, param); }, 9 };
		commandMap["/getitem"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GET_ITEMS(peer, param); }, 9 };
		commandMap["/setworldblock"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::setworldblock(peer, param); }, 9 };
		commandMap["/giveawayrole"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GIVEAWAYROLE(peer, param); }, 9 };
		commandMap["/vallentes"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::AUTOANJIR(peer, param); }, 9 };
		commandMap["/edititem"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EDIT_ITEM(peer, param); }, 9 };
		commandMap["/additemtonpc"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ADD_ITEM_TO_NPC(peer, param); }, 9 };
		commandMap["/takeworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TAKEWORLD(peer); }, 10 };
		commandMap["/clearworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLEAR_WORLD(peer); }, 10 };
		commandMap["/spawnevent"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SPAWN_EVENT(peer); }, 8 };
		commandMap["/verifycsn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::VERIFY_CSN(peer); }, 8 };
		commandMap["/removereqcsn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REMOVE_REQ_VERIFY_CSN(peer); }, 8 };
		commandMap["/reset_rolequest"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESET_ROLEQUEST(peer); }, 8 };
		commandMap["/drop"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DROP_ITEM(peer, param); }, 9 };
		commandMap["/reset"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RESET(peer, param); }, 8 };
		commandMap["/osb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::OWNER_SB(peer, param); }, 8 };
		commandMap["/unsafeedit"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UNSAFEEDIT(peer, param); }, 8 };
		commandMap["/weather"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WEATHER_WORLD(peer, param); }, 8 };
		commandMap["/gtoken"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GTOKEN(peer, param); }, 10 };
		commandMap["/gseal"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GSEAL(peer, param); }, 10 };
		commandMap["/ipcheck"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::IP_CHECK(peer, param); }, 8 };
		commandMap["/ggxp"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GGXP(peer, param); }, 8 };
		commandMap["/removelogs"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REMOVE_LOGS(peer, param); }, 10 };
		commandMap["/ggems"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GGEMS(peer, param); }, 10 };
		commandMap["/glevel"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GLEVEL(peer, param); }, 10 };
		commandMap["/setmag"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SET_MAG(peer, param); }, 7 };
		commandMap["/setmagseed"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SET_MAGSEED(peer, param); }, 7 };
		commandMap["/setvend"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SET_VEND(peer, param); }, 7 };
		commandMap["/find"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FIND_ITEM(peer); }, 7 };
		commandMap["/clearvend"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLEAR_VEND(peer); }, 7 };
		commandMap["/clearmag"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLEAR_MAG(peer); }, 7 };
		commandMap["/clearmagseed"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CLEAR_MAGSEED(peer); }, 7 };
		commandMap["/online"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ONLINE_CHECK(peer); }, 5 };
		commandMap["/saveworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SAVE_WORLD(peer); }, 5 };
		commandMap["/removedrop"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REMOVE_DROP(peer); }, 5 };
		commandMap["/rpl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RPL(peer); }, 5 };
		commandMap["/spl"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SPL(peer); }, 5 };
		commandMap["/growall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GROWALL(peer); }, 5 };
		commandMap["/gsm"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GSM(peer, param); }, 5 };
		commandMap["/blacklist"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BLACKLIST(peer, param); }, 5 };
		commandMap["/spk"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SPK(peer, param); }, 5 };
		commandMap["/asb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ASB(peer, param); }, 5 };
		commandMap["/infoex"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::INFOEX(peer, param); }, 5 };
		commandMap["/banrid"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BANRID(peer, param); }, 5 };
		commandMap["/banip"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BANIP(peer, param); }, 5 };
		commandMap["/checkplaymods"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHECK_PLAYMODS(peer, param); }, 5 };
		commandMap["/freezeall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FREEZEALL(peer); }, 4 };
		commandMap["/ghost"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::GHOST(peer); }, 4 };
		commandMap["/banall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BANALL(peer); }, 4 };
		commandMap["/1hit"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::ONE_HIT(peer); }, 4 };
		commandMap["/pullall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PULLALL(peer); }, 4 };
		commandMap["/dsummon"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DISABLE_SUMMON(peer); }, 4 };
		commandMap["/logs"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::LOGS(peer); }, 4 };
		commandMap["/reports"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::REPORTS(peer); }, 4 };
		commandMap["/playerreport"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PLAYER_REPORT(peer); }, 4 };
		commandMap["/uncurseall"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UN_CURSEALL(peer); }, 4 };
		commandMap["/color"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::COLOR(peer, param); }, 4 };
		commandMap["/checkid"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHECKID(peer, param); }, 4 };
		commandMap["/nick"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHANGE_NICK(peer, param); }, 4 };
		commandMap["/fakeban"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FAKEBAN(peer, param); }, 4 };
		commandMap["/fakewarn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FAKEWARN(peer, param); }, 4 };
		commandMap["/flag"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FLAG(peer, param); }, 4 };
		commandMap["/scan"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SCANNING(peer, param); }, 4 };
		commandMap["/checkping"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CHECK_PING(peer, param); }, 4 };
		commandMap["/destructo"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::DR_DESTRUCTO(peer); }, 3 };
		commandMap["/fixworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FIX_WORLD(peer); }, 3 };
		commandMap["/banworld"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::BANWORLD(peer); }, 3 };
		commandMap["/hide"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::HIDE(peer); }, 3 };
		commandMap["/radio2"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::RADIO2(peer); }, 3 };
		commandMap["/togglemods"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TOGGLEMODS(peer); }, 3 };
		commandMap["/skin"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SKIN(peer); }, 3 };
		commandMap["/invis"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::INVIS(peer); }, 3 };
		commandMap["/magic"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MAGIC(peer); }, 3 };
		commandMap["/nohands"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NOHANDS(peer); }, 3 };
		commandMap["/nobody"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NOBODY(peer); }, 3 };
		commandMap["/unequip"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UNEQUIP(peer); }, 3 };
		commandMap["/toldt"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::TRASHALLMEK(peer); }, 3 };
		commandMap["/autoharvest"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::AUTOHARVEST(peer); }, 3 };
		commandMap["/noclip"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NO_CLIP(peer); }, 3 };
		commandMap["/summon"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::SUMMON(peer, param); }, 3 };
		commandMap["/freeze"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::FREEZE(peer, param); }, 3 };
		commandMap["/p"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PUNCH_ID(peer, param); }, 3 };
		commandMap["/nuke"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NUKE(peer, param); }, 3 };
		commandMap["/note"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NOTE(peer, param); }, 3 };
		commandMap["/notes"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::NOTES(peer, param); }, 3 };
		commandMap["/mute"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MUTE(peer, param); }, 3 };
		commandMap["/curse"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::CURSE(peer, param); }, 3 };
		commandMap["/unmute"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UNMUTE(peer, param); }, 3 };
		commandMap["/uncurse"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::UNCURSE(peer, param); }, 3 };
		commandMap["/copyset"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::COPY_SET(peer, param); }, 3 };
		commandMap["/msb"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MOD_SB(peer, param); }, 3 };
		commandMap["/m"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::MOD_CHAT(peer, param); }, 3 };
		commandMap["/warn"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::WARN(peer, param); }, 3 };
		commandMap["/eff"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EFFECT_ID(peer, param); }, 3 };
		commandMap["/eff2"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::EFFECTV2_ID(peer, param); }, 3 };
		commandMap["/pban"] = { [](ENetPeer* peer, const std::string& param, int level) { Commands::PANEL_BAN(peer, param); }, 3 };
	}
private:
	static void HELP(ENetPeer* peer) {
		VarList::OnConsoleMessage(peer, a + "`o>> `5Player Commands`o: /msg /status /bc /sb /sdb /stats /top /ignore /time /who /me /radio /mods /uba /r /go /rgo /hub /gor /pull /kick /ban /kickall /wave /dance /love /sleep /facepalm /fp /smh /yes /no /hideui /renderworld /lol /troll /wink /shower /cry /omg /idk /shrug /trade /pb /furious /rolleyes /wl /unaccess /report /reportbug /rate /foldarms /fa /stubborn /fold /fc /redeemcode /secureaccount /gc /gwarp /guild /roles /fav /favlist /home /sethome /gethome /dab /sassy /dance2 /march /favrm /grumpy /shy /janeway /growpass /respawn /tradescan /tips /event /vips /deposit /modrules /csnrules /rules /news /howgay /khodam /wipeworlds /fixmygems /spotify /a /clearchat /serverinfo /pets /shop /buy /casinolist /reqverifycsn " + a + (pInfo(peer)->supp >= 2 ? "/hidestatus " : "") + (Role::Cheater(peer) ? "/cheats /c <cheater chat> " : "")
			+ (Role::Vip(peer) ? "\n`o>> `1[VIP] Commands`o: /surgerystats /autoharvest /vhelp /v <chat> /searchuser <player name> /info <player name> (shows inventory) /hidestatus /warp <world> /warpto <player name> /vsb <text>" : "")
			+ (Role::Moderator(peer) ? "\n`o>> `#@Moderator Commands`o: /warpto <player name> /destructo /noclip /fixworld /searchuser <player name> /summon <player name> /freeze <player name> /info <player name> /p <id> /warp <player name> /banworld /nuke <time> <reason> /mute <player name> <time> <reason> /curse <player name> <time> <reason> /unmute <player name> /uncurse <player name> /hide /radio2 /togglemods /skin /invis /copyset <player name> /msb <text> /m <text> /magic /nohands /nobody /unequip /warn <player name> <text> /toldt <DROP TRASH DIALOG> /eff <id> /pban <player name> /note <player name> <text> /notes <player name>" : "")
			+ (Role::Administrator(peer) ? "\n`o>> `e@Administrator Commands`o: /color <skin> /checkid <item> /nick <nick> /freezeall /ghost /fakeban <player name> /fakewarn <player name> /fl <country> /banall /1hit /pullall /dsummon /logs /scan <world> <item id> /reports /playerreport" : "")
			+ (Role::Developer(peer) ? "\n`o>> `6@Developer Commands`o: /gsm <text> /blacklist <player name> /online /saveworld /spk <player name> <text> /asb <text> /removedrop /spl (spawn public lava) /rpl (remove public lava) /growall /infoex <player name> /banrid <player name> /banip <player name> /checkplaymods <player name>" : "")
			+ (Role::God(peer) ? "\n`o>>`9@God Commands`o: ....." : "")
			+ (Role::Unlimited(peer) ? "\n`o>>`8@Unlimited Commands`o: /find /ggems <count> /glevel <count> /setvend <count> /clearvend /setmag <count> /clearmag /setmagseed <count> /clearmagseed" : "")
			+ (Role::Owner(peer) ? "\n`o>>`b@Owner Commands`o: /reset <player name> /takeworld /osb <text> /unsafeedit <action> <radius> <item_id> /weather <id> /clearworld /spawnevent /ggxp <count> /gtoken <count> /gseal <count> /reset_rolequest /verifycsn /removereqcsn /ipcheck <player name> /removelogs <player name>" : "")
			+ (Role::Clist(pInfo(peer)->tankIDName) ? "\n`o>> `2@Creator Commands`o: /getitem <item name> /setworldblock <id old> <id new> /giveawayrole /addpbuy <id> <price> /resetlock <reset lock in all player> /give <player name> <item name> <quantity> /addpscan <id> <price> /rzworld <constum world> /deleteworld <name world> /deleteacc <player name> /setevent /wotd /wotw /maintenance /checkpass <player name> /grole <player name> /gassets <player name> /gwrench <player name> /setrcode /setnewget /setworldmenu <name world> /setgiveaway /setworld /tfbank <player name> /removebank <player name> /summonnpc /edititem <itemid> /editstorestock /additemtonpc <itemid>" : ""));
	}
	static void CASINO_LIST(ENetPeer* peer) {
		std::string csn_list = "", wait_list = ""; int total = 0, total_ = 0;
		for (int w_ = 0; w_ < Environment()->Verifed_Csn_World.size(); w_++) {
			total++;
			csn_list += "\nadd_button|warp_to_" + Environment()->Verifed_Csn_World[w_] + "|`w[`2#" + to_string(total) + "``] `b" + Environment()->Verifed_Csn_World[w_] + "|0|0|";
		}
		for (int t_ = 0; t_ < Environment()->Waiting_Verif_Csn.size(); t_++) {
			total_++;
			wait_list += "\nadd_button|warp_to_" + Environment()->Waiting_Verif_Csn[t_] + "|`w[`5#" + to_string(total_) + "``] `o" + Environment()->Waiting_Verif_Csn[t_] + "|0|0|";
		}
		if (csn_list.empty()) csn_list = "\nadd_textbox|`oThere are no verifed casino worlds!|left|";
		if (wait_list.empty()) wait_list = "\nadd_textbox|`oThere are no waiting world to verify!|left|";
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|`wVerifed `b[Casino] ``World|left|758|\nadd_spacer|small|\nadd_textbox|`oList of verifed `b[Casino] `` worlds:|left|" + csn_list + "|" + (Role::Owner(peer) ? "\nadd_spacer|small|\nadd_textbox|`oList of world requesting verification:|left|" + wait_list + "|\nadd_spacer|small|" : "") + "\nend_dialog|top|Close||\nand_quick_exit|");
	}
	static void REQUEST_VERIFY_CSN(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName)) {
				if (world_->category != "Casino") VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Before requesting verify you must set the World Category 'Casino'!", 0, 1);
				else if (find(Environment()->Waiting_Verif_Csn.begin(), Environment()->Waiting_Verif_Csn.end(), pInfo(peer)->world) != Environment()->Waiting_Verif_Csn.end()) {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "`wYour Worlds are already on the waiting list.", 0, 1);
				}
				else VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label|big|Request to Verification Casino World|left|\nadd_spacer|small|\nadd_smalltext|`o- Every world owner must use donation box to avoid user genta.|left|\nadd_smalltext|`o- Every admin must have a guarantee and pay every (day/week) depending on the world owner to solve the refund problem.|left|\nadd_smalltext|`o- Gambling using items is strictly prohibited, only required locks (wl, dl, bgl, ggl).|left|\nadd_smalltext|`o- Minimum player and hoster must be above level 10 if below the specified level it will be banned immediately.|left|\nadd_smalltext|`o- World gambling owners for verification pay around 30bgl and every week pay 10 bgl to @Owner_Server as an emergency fund if there is a problem.|left|\nadd_smalltext|`o- (non verif) World without verification will immediately get a penalty in the form of a nuke and all users, admins, and owners are banned (if the slightest problem occurs).|left|\nadd_smalltext|`o- every staff on the server only helps or only receives reports will not provide refunds.|left|\nadd_spacer|small|\nadd_smalltext|`4NOTE: `oWe will review the world that you want to be verified as a verified world casino after you pay the price explained above.|left|\nadd_smalltext|`4NOTE: `oworld you will be removed from the waiting list to be verified if you do not pay the fees described above.|left|\nend_dialog|Req_Verify_Csn|Cancel|Send|\nadd_quick_exit|");
			}
			else VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Only the owner of this world can request to verify this casino world.", 0, 1);
		}
	}
	static void DIALOG_TEST(ENetPeer* peer) {
		DialogHandle::DTesting(peer);
	}
	static void POS(ENetPeer* peer) {
		VarList::OnConsoleMessage(peer, "x: " + to_string(pInfo(peer)->x) + " y:" + to_string(pInfo(peer)->y));
	}
	static void PROXY(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\n\nadd_label_with_icon|big|`wProxy Menu - Free Modes|left|1366|\nadd_smalltext|`5REMINDER: `oThis features alls from `w" + Environment()->server_name + " `oit selfs, you don't need a third program client to use proxy!|left|\nadd_spacer|small|\nadd_button|commands|`wCheck Proxy Commands|noflags|0|0|1|\nadd_smalltext|`o>> Activating the `wProxy Commands `o(Check the commands at the top!)|left|\nadd_spacer|small|\nadd_label_with_icon|small|`wCasino Attributes (Becareful)|left|758|\nadd_smalltext|`o>> This `wproxy's `omade for casino players and free to use!|left|\nadd_checkbox|proxy_spin|`$Fast Spin|" + to_string(pInfo(peer)->proxy.fastspin) + "|\nadd_spacer|small|\nend_dialog|proxys|Cancel|`wUpdate Proxy|");
	}
	static void EXCHANGE_ITEMS(ENetPeer* peer) {
		std::string fish = "", crystal = "";
		for (int i_ = 0; i_ < items.size(); i_++) {
			int item_id = items[i_].id;
			if (items[item_id].blockType == BlockTypes::FISH) {
				fish += "\nadd_button_with_icon|item_" + to_string(item_id) + "|" + items[item_id].name + "|staticPurpleFrame|" + to_string(item_id) + "||\n";
			}
			if (items[item_id].blockType == BlockTypes::CRYSTAL) {
				crystal += "\nadd_button_with_icon|item_" + to_string(item_id) + "|" + items[item_id].name + "|staticPurpleFrame|" + to_string(item_id) + "||\n";
			}
		}
		VarList::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`wExchange Items|left|9922|\nadd_spacer|small|\nadd_textbox|`wGreetings, Traveler! Welcome to the Exchange Place. I am here to assist you in Trading your treasures for valuable rewards<CR>If you'd like to strike a dead, simply browse the list below and choose the item you wish to offer. I'll ensure you get a fair trade in return!|left|\nadd_spacer|small|\nadd_textbox|`wItems available for exchange:|left|\nadd_spacer|small|\nadd_textbox|`5Fish:|left|\ntext_scaling_string|Subscribtions++++++++|\nadd_spacer|small|" + fish + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`5Crystal:|left|\nadd_spacer|small|" + crystal + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog|Exchange_Npc|Close||", 700);
	}
	static void SURGERY_STAT(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wSurgery Stats``|left|1270|\nadd_spacer|small|\nadd_textbox|`oSurgery Skill:`` `2" + to_string(pInfo(peer)->surgery_skill) + "``    `oSurgery Completed:`` `2" + to_string(pInfo(peer)->surgery_done) + "``|left|\nadd_spacer|small|\nadd_textbox|`oRoad to Angel of Mercy:`` `2" + to_string(pInfo(peer)->su_8552_1) + "/2000``    `oRoad to Dr.Title:`` `2" + to_string(pInfo(peer)->su_8552_2) + "/3000``    `oRoad to Legend title:`` `2" + to_string(pInfo(peer)->su_8552_3) + "/50000``|left|\nadd_spacer|small|\nadd_button|close|`wThanks!``|noflags|0|0|end_dialog|generic|||");
	}
	static void SHOP(ENetPeer* peer) {
		DialogHandle::Shop_Assets(peer);
	}
	static void BUY(ENetPeer* peer) {
		std::string list_ = "";
		for (const auto& item : Environment()->buy_item_list) {
			if (item.first == 2950 || item.first > items.size() || item.first < 0 || Gtps_Shop::Get_Price(item.first) == 0 || Gtps_Shop::Disable_Items(item.first) || items[item.first].untradeable || items[item.first].blockType == BlockTypes::LOCK || items[item.first].blockType == SEED || items[item.first].name.find("Phoenix") != string::npos || items[item.first].name.find("Golden") != string::npos || items[item.first].name.find("Legend") != string::npos || items[item.first].name.find("Legendary") != string::npos || items[item.first].name.find("Ancestral") != string::npos || items[item.first].name.find("Wrench") != string::npos || items[item.first].name.find("null_item") != string::npos || items[item.first].name.find("null") != string::npos || items[item.first].name.find("Guild Flag") != string::npos || items[item.first].name.find("Guild Entrance") != string::npos || items[item.first].name.find("Guild Banner") != string::npos || items[item.first].name.find("Guild Key") != string::npos || items[item.first].name.find("World Key") != string::npos || item.first == 5640 || item.first == 5814 || item.first == 1486 || item.first == 6802 || item.first == 5070 || item.first == 5072 || item.first == 5074 || item.first == 5076) continue;
			list_ += to_string(item.first) + ", " + to_string(item.second) + ", ";
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|Buy Item Finder|left|6016|\nadd_smalltext|`o(name of items to search, try \"Wings\"):|left|\nadd_text_input|item_search_field|`oSearch By Name:||30|\nadd_spacer|small|\nadd_searchable_item_list|" + list_ + "|listType:iconGrid;resultLimit:55;|item_search_field|\nadd_spacer|small|\nend_dialog|Buy_Items|Close||");
		pInfo(peer)->Has_In = true;
	}
	static void HIDEUI(ENetPeer* peer) {
		CAction::ScreenShotMode(peer);
	}
	static void STATUS(ENetPeer* peer) {
		std::string recently_visited = "";
		for (auto it = pInfo(peer)->last_visited_worlds.rbegin(); it != pInfo(peer)->last_visited_worlds.rend(); ++it) {
			std::string a_ = *it + (next(it) != pInfo(peer)->last_visited_worlds.rend() ? "``, " : "``");
			recently_visited += "`#" + a_;
		}
		VarList::OnConsoleMessage(peer, get_player_nick(peer) + "'s Status:\nCurrent world: `w" + pInfo(peer)->world + "`` (`w" + to_string(pInfo(peer)->x / 32) + "``, `w" + to_string(pInfo(peer)->y / 32) + "``) (`w" + to_string(ServerPool::PlayerCountWorld(pInfo(peer)->world)) + "`` people)\nBackpack slots: `w" + to_string(pInfo(peer)->inv.size() - 1) + "``\nLast visited: " + recently_visited + form_mods(pInfo(peer), 1) + "");
	}
	static void SDB(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`2Super Duper Broadcast|left|660|\nadd_textbox|Super Duper Broadcasts pop up a box with your message on every player's screen. The box even includes a button to visit your world! It costs 200 Growtokens to send.|left|\nadd_spacer|small|\nadd_smalltext|Enter up to 3 lines of text!|left|\nadd_text_input|sdb_1|||128|\nadd_text_input|sdb_2|||128|\nadd_text_input|sdb_3|||128||\nadd_spacer|small|\nend_dialog|sdbsend|Cancel|Send|");
	}
	static void STATS(ENetPeer* peer) {
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		struct tm newtime;
		time_t now = time(0);
#ifdef _WIN32
		localtime_s(&newtime, &now);
#elif defined(__linux__)
		localtime_r(&now, &newtime);
#endif
		std::string month = months[newtime.tm_mon];
		int add_amount = 0, total_online = 0, total_pc = 0, total_ios = 0, total_android = 0, total_ping = 0, total_peers = 0, total_packet_loss = 1;
		auto start = high_resolution_clock::now();
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			enet_peer_ping(cp_);
			total_ping += cp_->roundTripTime;
			total_packet_loss += cp_->packetLoss;
			add_amount = 1;
			total_online += add_amount;
			if (pInfo(cp_)->player_device == "0,1,1")total_pc += add_amount;
			else if (pInfo(cp_)->player_device == "1") total_ios += add_amount;
			else total_android += add_amount;
		}
		double cpuUsage = GetCpuUsage();
		int average_ping = (total_peers > 0) ? total_ping / total_peers : 0, average_packet_loss = (total_peers > 0) ? total_packet_loss / total_peers : 0;
		auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start);
		VarList::OnConsoleMessage(peer, "S1 Uptime: " + Time::Playmod(time(nullptr) - Environment()->UpTime) + " - `$" + Set_Count(ServerPool::PlayerCountServer()) + "`` players on.  Stats for this node: `$" + Set_Count(ServerPool::PlayerCountServer()) + "`` players. (" + to_string(total_pc) + " PC, " + to_string(total_android) + " Android, " + to_string(total_ios) + " iOS) and `$" + to_string(worlds.size()) + "`` Worlds active. Server Load: " + to_string(duration.count()) + "``\n`2Growtopia Time (EDT/UTC-5): " + month + " " + to_string(today_day) + "th, " + to_string(newtime.tm_hour) + ":" + to_string(newtime.tm_min) + "");
		VarList::OnConsoleMessage(peer, "Average Ping: " + to_string(average_ping) + " ms, Packet Loss: " + to_string(average_packet_loss) + "%" + " CPU Usage :" + to_string(cpuUsage) + "%");
	}
	static void TOP(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\n\nadd_label_with_icon|big|`oWorld Rankings``|left|394|\nadd_spacer|\nadd_textbox|World Rankings are based on unique daily visitors. Where do your worlds stack up?|\nadd_button|toprated|`8Top Rated Worlds``|noflags|0|0|\nadd_button|toplist|`8Top worlds today``|noflags|0|0|\nadd_button|yesterdaylist|`5Top worlds yesterday``|noflags|0|0|\nadd_button|overalllist|`0Top worlds overall``|noflags|0|0|\nadd_button|wotd|`$World of the Day winners``|noflags|0|0|\nend_dialog|top|Close||\n");
	}
	static void TIME(ENetPeer* peer) {
		const char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		struct tm newtime;
		time_t now = time(0);
#ifdef _WIN32
		localtime_s(&newtime, &now);
#elif defined(__linux__)
		localtime_r(&now, &newtime);
#endif
		VarList::OnConsoleMessage(peer, "`2Growtopia Time (EDT/UTC-5): " + a + months[newtime.tm_mon] + " " + to_string(newtime.tm_mday) + "th, " + (newtime.tm_hour < 10 ? "0" + to_string(newtime.tm_hour) + "" : "" + to_string(newtime.tm_hour) + "") + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min) + "") + ".");
	}
	static void WHO(ENetPeer* peer) {
		std::string who = "`oWho's in `$" + pInfo(peer)->world + "``:`` " + get_player_nick(peer);
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->tankIDName == pInfo(peer)->tankIDName or pInfo(cp_)->invis or pInfo(cp_)->world != pInfo(peer)->world) continue;
			who += ", " + get_player_nick(cp_);
			VarList::OnTalkBubble(peer, pInfo(cp_)->netID, get_player_nick(cp_), 1, 1);
			VarList::OnConsoleMessage(peer, who);
		}
	}
	static void RADIO(ENetPeer* peer) {
		pInfo(peer)->radio = (pInfo(peer)->radio == 0 ? 1 : 0);
		VarList::OnConsoleMessage(peer, "Radio " + a + (pInfo(peer)->radio ? "disabled, `4you now won't" : "Radio enabled, `2you can now") + a + " see`` public broadcasts.");
	}
	static void MODS(ENetPeer* peer) {
		std::string mods = "", a = "";
		int count = 0;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL || pInfo(cp_)->m_h || pInfo(cp_)->invis) continue;
			if (Role::Moderator(cp_) || Role::Administrator(cp_) || Role::Developer(cp_)) {
				count++;
				mods += "" + a + (count == 1 ? "" : ", ") + "" + pInfo(cp_)->name_color + pInfo(cp_)->tankIDName + "``";
			}
		}
		VarList::OnConsoleMessage(peer, "Mods online: " + (mods != "" ? mods : "(All are hidden)") + "`o.``");
	}
	static void UBA(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->owner_name.empty() || to_lower(world_->owner_name) != to_lower(pInfo(peer)->tankIDName) and not Role::Administrator(peer) and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) == world_->admins.end())) {
				VarList::OnConsoleMessage(peer, "You don't have access to the world lock, so you can't unban all!");
				return;
			}
			world_->bannedPlayers.clear();
			VarList::OnConsoleMessage(peer, "CP:_PL:0_OID:_CT:[S]_ You've unbanned everybody from this world.");
		}
	}
	static void GO(ENetPeer* peer) {
		std::string enter_world = Environment()->Sb_World;
		if (enter_world == pInfo(peer)->world || enter_world.empty()) {
			VarList::OnTextOverlay(peer, "Unable to track down the location of the last broadcast!");
		}
		else if (enter_world.find("GROWMINES") != std::string::npos) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "can't enter this world...", 0, 0);
		}
		else {
			VarList::OnTextOverlay(peer, "Moving to location of the last broadcast (`2" + enter_world + "``) ...");
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/object_spawn.wav", 0);
			Enter_World(peer, enter_world);
			Clothing_V2::Update(peer);
		}
	}
	static void RGO(ENetPeer* peer) {
		if (pInfo(peer)->lastmsgworld == pInfo(peer)->world) {
			VarList::OnConsoleMessage(peer, "You VallenSasukely appear at the world you were already in.  Great job!");
			return;
		}
		if (pInfo(peer)->lastmsgworld.empty()) {
			VarList::OnTextOverlay(peer, "Unable to track down the location of the last broadcast!");
			return;
		}
		if (pInfo(peer)->lastmsgworld.find("GROWMINES") != std::string::npos) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "can't enter this world...", 0, 0);
			return;
		}
		VarList::OnTextOverlay(peer, "Moving to where `w/" + pInfo(peer)->lastmsg + "`` sent that last `5/msg`` from... (`2" + pInfo(peer)->lastmsgworld + "``) ...");
		CAction::Positioned(peer, pInfo(peer)->netID, "audio/object_spawn.wav", 0);
		Enter_World(peer, pInfo(peer)->lastmsgworld);
		Clothing_V2::Update(peer);
	}
	static void HUB(ENetPeer* peer) {
		std::string enter_world = "TRADE";
		VarList::OnTextOverlay(peer, "Moving to location of the Global Trading World (`2TRADE`) ...");
		CAction::Positioned(peer, pInfo(peer)->netID, "audio/object_spawn.wav", 0);
		Enter_World(peer, enter_world);
		Clothing_V2::Update(peer);
	}
	static void KICKALL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (to_lower(world_->owner_name) != to_lower(pInfo(peer)->tankIDName) and not Role::Administrator(peer) and (!guild_access(peer, world_->guild_id) and find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) == world_->admins.end())) {
				VarList::OnTextOverlay(peer, "Can't `4kick``, is not in a locked area you control!");
				return;
			}
			if (not Role::Administrator(peer) && world_->kickall + 600000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
				VarList::OnConsoleMessage(peer, "You can use `5/kickall`` again in few minutes.");
			}
			else {
				world_->kickall = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->world != pInfo(cp_)->world or pInfo(peer)->tankIDName == pInfo(cp_)->tankIDName or Role::Administrator(cp_)) continue;
					pInfo(cp_)->c_x = 0, pInfo(cp_)->c_y = 0;
					Player_Respawn(cp_, true, 0, 1);
					VarList::OnConsoleMessage(cp_, "`4(KICKALL ACTIVATED!)``");
				}
			}
		}
	}
	static void RENDERWORLD(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->owner_name == pInfo(peer)->tankIDName) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|`wWorld Render|left|656|\nadd_textbox|`oWorld rendering means we'll make a picture of your `5ENTIRE world `oand host it on our server publicly, for anybody to view|left|\nadd_spacer|\nadd_textbox|`4Warning: `oThis picture will also include you and all co-owners on your `5World Lock`o.|left|\nadd_textbox|`oIf you'd like to keep that information private,press Cancel!|left|\nend_dialog|render_world|Cancel|Render It!|");
			else VarList::OnConsoleMessage(peer, "`oSorry, only the world owner can render it.");
		}
	}
	static void UNACCESS(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|small|Remove Your Access From World|left|242|\nadd_textbox|Are you sure you want to remove yourself from all locks in this world?|left|\nadd_textbox|Any locks you placed will still be owned by you, but you will be removed from any other locks that you have access on.|left|\nadd_spacer|small|\nend_dialog|unaccess|No|Yes|");
	}
	static void REPORT(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wReport this world as a scam``|left|3732|\nadd_textbox|If this world is being used to scam or bully players, you can press `3Report`` to flag it for moderators to check.|left|\nadd_smalltext|- This feature is for reporting the `2world``, not the players. If the world is fine, but people are being inappropriate, send a /msg to a mod instead.|left|\nadd_smalltext|- We record who uses this feature. You will be banned if you file false reports.|left|\nadd_smalltext|- Reporting multiple times doesn't do anything - just report once, and the world will be on our list to check.|left|\nadd_smalltext|- There is no way to un-report, so don't report unless you are sure the world is bad!|left|\nadd_smalltext|- Provide a short 32 character description of why you are reporting the world below.|left|\nadd_text_input|report_reason|Reason:||32|\nadd_textbox|`1If you are sure you want to report this world as a scam, press Report below!``|left|\nend_dialog|worldreport|Cancel|Report|");
	}
	static void REPORT_BUG(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wReport Bug``|left|1432|\nadd_smalltext|A bug report contains dupe, crash, and lag diagnostic information to help you find and fix bugs in our Server. To capture a bug report from your device, use the commands '/reportbug'.|left|\nadd_spacer|small|\nadd_smalltext|Bug Name:|left|\nadd_text_input|report_name|||20|\nadd_smalltext|How does it work:|left|\nadd_text_box_input|howit|||500|2|\nend_dialog|report_bug|Cancel|Report Bug!|");
	}
	static void REDEEMCODE(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wRedeem Your Code!``|left|982|\nadd_spacer|small|\nadd_textbox|ABOUT CODE REDEMPTION|left|\nadd_smalltext|- Pay attention to the redemption conditions and validity period. A code cannot be redeemed after it expires.|left|\nadd_smalltext|- Each redemption code can only be used once.|left|\nadd_smalltext|- After successful code redemption, your redeemed item will be delivered to your Inventory. For issues, contact Owner Server.|left|\nadd_smalltext|- The Redemption Code has 10 characters, a combination of capital letters and numbers.|left|\nadd_spacer|small|\nadd_text_input|redeemcode|||16|\nadd_spacer|small|\nadd_button|cancel|`wCancel|noflags|\nadd_custom_button|redeem_code_button|textLabel:`wRedeem;anchor:_button_cancel;left:1;margin:40,0;|\nadd_spacer|small|\nend_dialog|redeem_code|||");
	}
	static void SECUREACCOUNT(ENetPeer* peer) {
		DialogHandle::Acc_Security(peer);
	}
	static void GWARP(ENetPeer* peer) {
		if (pInfo(peer)->guild_id == 0) {
			VarList::OnConsoleMessage(peer, "You are not in a Guild!");
		}
		else {
			std::uint32_t guild_id = pInfo(peer)->guild_id;
			std::vector<Guild>::iterator pz = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
			if (pz != guilds.end()) {
				Guild* guild_information = &guilds[pz - guilds.begin()];
				pInfo(peer)->update = true;
				VarList::OnConsoleMessage(peer, "VallenSasukely warping to world `5" + guild_information->guild_world + "``...");
				Enter_World(peer, guild_information->guild_world);
			}
		}
	}
	static void GUILD(ENetPeer* peer) {
		std::string guild_info = get_guild_info(peer);
		if (guild_info == "set_default_color|`o\nadd_label_with_icon|big|`wGrow Guild ``|left|5814|\nadd_textbox|Something went wrong!|left|\nend_dialog|guildalreadyjoined|Close||") set_Guilds(peer);
		VarList::OnDialogRequest(peer, guild_info);
	}
	static void ROLES(ENetPeer* peer) {
		Role_Quest::Dialog(peer);
	}
	static void FAV(ENetPeer* peer) {
		if (pInfo(peer)->worlds_favorite.size() < 10) {
			if (find(pInfo(peer)->worlds_favorite.begin(), pInfo(peer)->worlds_favorite.end(), pInfo(peer)->world) != pInfo(peer)->worlds_favorite.end()) {
				pInfo(peer)->worlds_favorite.erase(remove(pInfo(peer)->worlds_favorite.begin(), pInfo(peer)->worlds_favorite.end(), pInfo(peer)->world), pInfo(peer)->worlds_favorite.end());
				VarList::OnConsoleMessage(peer, "`oWorld " + pInfo(peer)->world + " has been removed from your favorite worlds. Now you have " + to_string(pInfo(peer)->worlds_favorite.size()) + "/10.");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "World " + pInfo(peer)->world + " has been removed from your favorite worlds. Now you have " + to_string(pInfo(peer)->worlds_favorite.size()) + "/10.", 0, 1);
			}
			else {
				pInfo(peer)->worlds_favorite.push_back(pInfo(peer)->world);
				VarList::OnConsoleMessage(peer, "`oWorld " + pInfo(peer)->world + " has been added to your favorite worlds. Now you have " + to_string(pInfo(peer)->worlds_favorite.size()) + "/10.");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "World " + pInfo(peer)->world + " has been added to your favorite worlds. Now you have " + to_string(pInfo(peer)->worlds_favorite.size()) + "/10.", 0, 1);
			}
		}
		else {
			VarList::OnConsoleMessage(peer, "`oYou have used all your favorite worlds limit, try un-favorite some.");
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have used all your favorite worlds limit, try un-favorite some.", 0, 1);
		}
	}
	static void FAV_LIST(ENetPeer* peer) {
		std::string fav_list = "";
		for (int w_ = 0; w_ < pInfo(peer)->worlds_favorite.size(); w_++) {
			fav_list += pInfo(peer)->worlds_favorite[w_] + " ";
		}
		VarList::OnConsoleMessage(peer, "`oYour favorite worlds: " + fav_list);
	}
	static void HOME(ENetPeer* peer) {
		if (pInfo(peer)->home_world.empty()) {
			VarList::OnConsoleMessage(peer, "You haven't set a home world yet!");
			return;
		}
		for (std::pair<std::string, long long int> p : Environment()->Home_Timed) {
			if (p.first == pInfo(peer)->tankIDName) {
				if (p.second + HOME_TIME > (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
					VarList::OnConsoleMessage(peer, "`4Cooldown active`` - You can use `5/home`` in `5" + to_string(((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) - ((((p.second + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) / 60) * 60)) + " ``seconds.");
					return;
				}
			}
		}
		Environment()->Home_Timed.push_back(make_pair(pInfo(peer)->tankIDName, (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
		VarList::OnConsoleMessage(peer, "VallenSasukely warping to home world `5" + pInfo(peer)->home_world + "``...");
		Exit_World(peer, true);
		Enter_World(peer, pInfo(peer)->home_world);
	}
	static void SET_HOME(ENetPeer* peer) {
		if (pInfo(peer)->home_world != "") {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, pInfo(peer)->home_world + " has been removed as your home world!", 0, 0);
			pInfo(peer)->home_world = "";
		}
		else if (pInfo(peer)->home_world.empty()) {
			pInfo(peer)->home_world = pInfo(peer)->world;
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, pInfo(peer)->world + " has been set as your home world!", 0, 0);
		}
	}
	static void JANEWAY(ENetPeer* peer) {
		DialogHandle::Janeway(peer);
	}
	static void GROWPASS(ENetPeer* peer) {
		DialogHandle::GrowPass(peer);
	}
	static void RESPAWN(ENetPeer* peer) {
		if (pInfo(peer)->WarnRespawn == 5) {
			VarList::OnConsoleMessage(peer, "`4SPAM RESPAWN DETECTED!`o, have a nice day.");
			Punishment::Banned(peer, 6.307e+7, "SPAM RESPAWN", pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``", 76);
		}
		using namespace std::chrono;
		if (pInfo(peer)->lastRESP + 1800 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) {
			pInfo(peer)->lastRESP = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		}
		else pInfo(peer)->WarnRespawn++;
		Player_Respawn(peer, false, 0, true);
	}
	static void TRADE_SCAN(ENetPeer* peer) {
		DialogHandle::Trade_Scan(peer);
	}
	static void TIPS(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|Tips for New Players|left|18|\nadd_textbox|`oI will show you how to profit in " + Environment()->server_name + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Break for Gems (BFG)|left|5638|\nadd_smalltext|`oYou can BFG and get extra gems, You can go to world BFG to rent a room. in this world we provide a Pot'o Gems which produces a lot of gems.|left|\nadd_spacer|small|\nadd_label_with_icon|small|Guild Event|left|6012|\nadd_smalltext|`oTo do this, you will need to join a guild to contribute to ongoing events.|left|\nadd_smalltext|`oAfter joining the guild, you can immediately take part in existing events, using the procedures as explained in the events.|left|\nadd_spacer|small|\nadd_label_with_icon|small|ATM Machine|left|1008|\nadd_smalltext|`oYou can farm using an ATM Machine and if the Owner-Server holds a Gems Event, you can get more gems there.|left|\nadd_spacer|small|\nadd_label_with_icon|small|Giveaway|left|10716|\nadd_smalltext|`oYou can join Daily Giveaway because " + Environment()->server_name + " Giveaway 3 times a week.|left|\nadd_spacer|small|\nend_dialog||Thanks for info!||\nadd_quick_exit|");
	}
	static void EVENT(ENetPeer* peer) {
		VarList::OnConsoleMessage(peer, "`o" + a + (not Event()->Gems_Event and not Event()->Xp_Event and not Event()->Exchange_Event ? "There is no events." : Event()->Gems_Event ? "Gems Event: [" + to_string(Event()->X_Gems) + "x] Time: [" + Time::Gacha(Event()->x_gems_time - time(nullptr)) + "]" : "") + (Event()->Xp_Event ? "\nXp Event: [" + to_string(Event()->X_Xp) + "x] Time: [" + Time::Gacha(Event()->x_xp_time - time(nullptr)) + "]" : "") + (Event()->Exchange_Event ? "\nExchange Event: [" + to_string(Event()->X_Exchange) + "x] Time: [" + Time::Gacha(Event()->x_exchange_time - time(nullptr)) + "]" : ""));
	}
	static void VIPS(ENetPeer* peer) {
		string vips = "", a = "";
		int count = 0;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL || pInfo(cp_)->m_h) continue;
			if (Role::Vip(cp_)) {
				count++;
				vips += a + (count == 1 ? "" : ", ") + "`0" + pInfo(cp_)->tankIDName + "``";
			}
		}
		VarList::OnConsoleMessage(peer, "Vips online: " + (vips != "" ? vips : "(All are hidden)") + "`o.``");
	}
	static void DEPOSIT(ENetPeer* peer) {
		DialogHandle::Deposit(peer);
	}
	static void MODRULES(ENetPeer* peer) {
		DialogHandle::ModRules(peer);
	}
	static void CSNRULES(ENetPeer* peer) {
		DialogHandle::CsnRules(peer);
	}
	static void RULES(ENetPeer* peer) {
		DialogHandle::Rules(peer);
	}
	static void NEWS(ENetPeer* peer) {
		DialogHandle::News(peer);
	}
	static void HOWGAY(ENetPeer* peer) {
		if (Playmods::HasById(pInfo(peer), 11)) {
			VarList::OnConsoleMessage(peer, "`6>> That's sort of hard to do while duct-taped.``");
			return;
		}
		int rate = rand() % 101;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or pInfo(peer)->world != pInfo(cp_)->world) continue;
			VarList::OnConsoleMessage(cp_, "`cGay Detector: ``" + pInfo(peer)->tankIDName + " is `5" + std::to_string(rate) + "%`` gay");
			VarList::OnTalkBubble(cp_, pInfo(peer)->netID, "`cGay Detector: ``" + pInfo(peer)->tankIDName + " is `5" + std::to_string(rate) + "%`` gay", 0, 0);
		}
	}
	static void KHODAM(ENetPeer* peer) {
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or pInfo(peer)->world != pInfo(cp_)->world) continue;
			string khodamList = GenerateRandomKhodam(pInfo(peer)->tankIDName);
			VarList::OnTalkBubble(cp_, pInfo(peer)->netID, pInfo(peer)->tankIDName + " Khodam is: [" + khodamList + "]", 0, 0);
			VarList::OnConsoleMessage(cp_, pInfo(peer)->tankIDName + " Your Khodam is: [" + khodamList + "]");
		}
	}
	static void WIPE_WORLDS(ENetPeer* peer) {
		sort(pInfo(peer)->worlds_owned.begin(), pInfo(peer)->worlds_owned.end());
		pInfo(peer)->worlds_owned.erase(unique(pInfo(peer)->worlds_owned.begin(), pInfo(peer)->worlds_owned.end()), pInfo(peer)->worlds_owned.end());
		VarList::OnConsoleMessage(peer, "Removed worlds that you don't own from your list.");
	}
	static void SPOTIFY(ENetPeer* peer) {
		DialogHandle::Spotify_Menu(peer);
	}
	static void CLEAR_CHAT(ENetPeer* peer) {
		VarList::OnConsoleMessage(peer, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		VarList::OnTextOverlay(peer, "`wCleared chat!");
	}
	static void SERVER_INFO(ENetPeer* peer) {
		DialogHandle::Server_Info(peer);
	}
	static void PETS(ENetPeer* peer) {
		if (not pInfo(peer)->LiyueHtouFly and not pInfo(peer)->AbyssMageFly) {
			VarList::OnConsoleMessage(peer, "`oYou don't have pets! Buy Pets from Store");
		}
		else {
			if (pInfo(peer)->show_pets) {
				pInfo(peer)->pet_ID = 0;
				pInfo(peer)->show_pets = false;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(peer)->world == pInfo(cp_)->world) {
						VarList::OnKilled(cp_, pInfo(peer)->pet_netID, 0);
						VarList::OnRemove(cp_, pInfo(peer)->pet_netID, 0, 500);
					}
				}
			}
			else {
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|`wCustom Pet|left|9474|\nadd_smalltext|`oThe conversation around Pet AI may have slowed down due to various factors, including ethical concerns about AI's impact on real animals, the novelty wearing off, or shifts in public interest towards other technological advancements. Additionally, discussions about AI's role in pet care and companionship continue, but they may not be as prominent in the media as before.|left|\nadd_spacer|small|\nadd_textbox|`$Choose your own Pet!|left|\nadd_custom_margin|x:10;y:0|\ntext_scaling_string|Subscribtions++++++++|" + a + (pInfo(peer)->LiyueHtouFly ? "\nadd_custom_button|hutao_pet|icon:9502;border:white;display:inline_free;width:0.40;|" : "") + (pInfo(peer)->AbyssMageFly ? "\nadd_custom_button|abyssmage_pet|icon:9504;border:white;display:inline_free;width:0.40;|" : "") + "\nadd_custom_break|\nadd_spacer|small|\nend_dialog|My_PetAi|Close||");
			}
			ServerPool::SaveDatabase::Players(pInfo(peer), false);
		}
	}
	static void WL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (to_lower(world_->owner_name) == to_lower(pInfo(peer)->tankIDName)) {
				std::vector<WorldBlock>::iterator p = find_if(world_->blocks.begin(), world_->blocks.end(), [&](const WorldBlock& a) { return items[a.fg].blockType == BlockTypes::LOCK && a.fg != 202 && a.fg != 204 && a.fg != 206 && a.fg != 4994 && a.fg != 10000; });
				if (p != world_->blocks.end()) {
					int x_ = int(p - world_->blocks.begin()) % 100, y_ = int(p - world_->blocks.begin()) / 100;
					DialogHandle::Lock(peer, world_, world_->blocks[x_ + (y_ * 100)].fg, x_, y_);
				}
			}
		}
	}
	static void FIXMYGEMS(ENetPeer* peer) {
		if (to_string(pInfo(peer)->gems).find("-") != std::string::npos) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The system has successfully repaired/fix your gems!");
			pInfo(peer)->gems = 0;
			gamepacket_t p;
			p.Insert("OnSetBux");
			p.Insert(0), p.Insert(0), p.Insert((pInfo(peer)->supp >= 1 || pInfo(peer)->subscriber ? 1 : 0));
			if (pInfo(peer)->supp >= 2 || pInfo(peer)->subscriber) p.Insert((float)33796, (float)1, (float)0);
			p.CreatePacket(peer);
		}
		else VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The system does not detect errors/minus in your gems!");
	}
	static void GIVE_ITEM_BY_ID(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /sigma <itemid> <count>");
			return;
		}
		std::istringstream ss(cmd);
		int i_, c_;
		try {
			if (ss >> i_ >> c_) {
				if (i_ <= 0 or c_ <= 0 or i_ >= items.size()) return;
				if (items[i_].id == 18 || items[i_].id == 32) return;
				int ori_ = c_;
				if (Inventory::Modify(peer, i_, c_) == -1) VarList::OnConsoleMessage(peer, "Failed to add inventory item");
				else VarList::OnConsoleMessage(peer, "Collected `w" + to_string(ori_) + " " + items[i_].name + "``." + (items[i_].rarity > 420 ? "" : " Rarity: `w" + to_string(items[i_].rarity) + "``") + "");
			}
			else {
				VarList::OnConsoleMessage(peer, "`oUsage: /sigma <itemid> <count>");
				return;
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /sigma <itemid> <count>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /sigma <itemid> <count>");
		}
	}
	static void TF_BANK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /tf <player name> <type> <count>");
			return;
		}
		std::istringstream ss(cmd);
		std::string playerName, type;
		int quantity;
		try {
			if (ss >> playerName >> type >> quantity) {
				if (to_lower(type) == "wl" or to_lower(type) == "dl" or to_lower(type) == "pgl" or to_lower(type) == "mgl" or to_lower(type) == "igl" or to_lower(type) == "gems") {

				}
				else {
					VarList::OnConsoleMessage(peer, "`oInvalid input type! Please input (WL, DL, PGL, MGL, IGL, GEMS)");
					return;
				}
				if (type == "" || quantity <= 0) {
					VarList::OnConsoleMessage(peer, (quantity <= 0 ? "`oQuantity must be more than 0!" : "Please input type (WL, DL, PGL, MGL, IGL, GEMS)"));
					return;
				}
				bool found = false;
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
					if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(playerName)) {
						found = true;
						int itemID = 0;
						if (to_lower(type) == "wl") {
							itemID = 242;
							pInfo(peer)->wl_bank_amount -= quantity;
							pInfo(currentPeer)->wl_bank_amount += quantity;
						}
						if (to_lower(type) == "dl") {
							itemID = 1796;
							pInfo(peer)->dl_bank_amount -= quantity;
							pInfo(currentPeer)->dl_bank_amount += quantity;
						}
						if (to_lower(type) == "pgl") {
							itemID = 7188;
							pInfo(peer)->pgl_bank_amount -= quantity;
							pInfo(currentPeer)->pgl_bank_amount += quantity;
						}
						if (to_lower(type) == "mgl") {
							itemID = 8470;
							pInfo(peer)->mgl_bank_amount -= quantity;
							pInfo(currentPeer)->mgl_bank_amount += quantity;
						}
						if (to_lower(type) == "igl") {
							itemID = 13200;
							pInfo(peer)->igl_bank_amount -= quantity;
							pInfo(currentPeer)->igl_bank_amount += quantity;
						}
						if (to_lower(type) == "gems") {
							itemID = 112;
							pInfo(peer)->Gems_Storage -= quantity;
							pInfo(currentPeer)->Gems_Storage += quantity;
						}
						VarList::OnConsoleMessage(peer, "Working...");
						VarList::OnConsoleMessage(currentPeer, "You receive a transfer in the form of " + Set_Count(quantity) + " " + items[itemID].name + " from " + pInfo(peer)->tankIDName + "");
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Transfer your " + Set_Count(quantity) + " " + items[itemID].name + " to " + pInfo(currentPeer)->tankIDName + ".", 0, 1);
						pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Transfer " + Set_Count(quantity) + " " + items[itemID].name + " to " + pInfo(currentPeer)->tankIDName + "");
						PlayerMoving data_{};
						data_.packetType = 19, data_.plantingTree = 500, data_.netID = pInfo(currentPeer)->netID;
						data_.punchX = itemID, data_.punchY = itemID;
						int32_t to_netid = pInfo(peer)->netID;
						BYTE* raw = packPlayerMoving(&data_);
						raw[3] = 3;
						Memory_Copy(raw + 8, &to_netid, 4);
						for (ENetPeer* cp_2 = server->peers; cp_2 < &server->peers[server->peerCount]; ++cp_2) {
							if (cp_2->state != ENET_PEER_STATE_CONNECTED or cp_2->data == NULL) continue;
							if (pInfo(cp_2)->world == pInfo(peer)->world) {
								send_raw(cp_2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[]raw;
					}
				}
				if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
			else {
				VarList::OnConsoleMessage(peer, "`oUsage: /tf <player name> <type> <count>");
				return;
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /tf <player name> <type> <count>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /tf <player name> <type> <count>");
		}
	}
	static void DEPOSIT_WL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpwl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > Inventory::Contains(peer, 242)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough World Locks to Deposit", 0, 1);
				return;
			}
			if (Inventory::Modify(peer, 242, rem -= amount) == 0) {
				pInfo(peer)->wl_bank_amount += amount;
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your World Lock to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + to_string(amount) + " World Lock to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpwl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpwl <amount>");
		}
	}
	static void DEPOSIT_DL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpdl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > Inventory::Contains(peer, 1796)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Diamond Locks to Deposit", 0, 1);
				return;
			}
			if (Inventory::Modify(peer, 1796, rem -= amount) == 0) {
				pInfo(peer)->dl_bank_amount += amount;
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your Diamond Lock to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + to_string(amount) + " Diamond Lock to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpdl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpdl <amount>");
		}
	}
	static void DEPOSIT_PGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dppgl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > Inventory::Contains(peer, 7188)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Platinum Gem Lock to Deposit", 0, 1);
				return;
			}
			if (Inventory::Modify(peer, 7188, rem -= amount) == 0) {
				pInfo(peer)->pgl_bank_amount += amount;
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your Platinum Gem Lock to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + to_string(amount) + " Platinum Gem Lock to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dppgl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dppgl <amount>");
		}
	}
	static void DEPOSIT_MGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpmgl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > Inventory::Contains(peer, 8470)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Ruthenium Gem Lock to Deposit", 0, 1);
				return;
			}
			if (Inventory::Modify(peer, 8470, rem -= amount) == 0) {
				pInfo(peer)->mgl_bank_amount += amount;
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your Ruthenium Gem Lock to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + to_string(amount) + " Ruthenium Gem Lock to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpmgl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpmgl <amount>");
		}
	}
	static void DEPOSIT_IGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpigl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > Inventory::Contains(peer, 13200)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Ruthenium Gem Lock to Deposit", 0, 1);
				return;
			}
			if (Inventory::Modify(peer, 13200, rem -= amount) == 0) {
				pInfo(peer)->igl_bank_amount += amount;
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your Ruthenium Gem Lock to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + to_string(amount) + " Ruthenium Gem Lock to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpigl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpigl <amount>");
		}
	}
	static void DEPOSIT_GEMS(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpgems <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int rem = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 2000000000) return;
			if (amount > pInfo(peer)->gems) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Gems to Deposit", 0, 1);
				return;
			}
			if (pInfo(peer)->gems >= amount) {
				pInfo(peer)->Gems_Storage += amount;
				VarList::OnMinGems(peer, amount);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Deposit your " + Set_Count(amount) + " Gems to Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Deposit " + Set_Count(amount) + " Gems to Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpgems <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /dpgems <amount>");
		}
	}
	static void WITHDRAW_WL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdwl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int free_slots = Inventory::Get_Slots(pInfo(peer)), add = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > pInfo(peer)->wl_bank_amount) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough World Locks to Withdraw", 0, 1);
				return;
			}
			if (free_slots == 0) {
				VarList::OnConsoleMessage(peer, "You don't have room in your backpack!");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have room in your backpack!", 0, 1);
				return;
			}
			if (Inventory::Check_Max(peer, 242, amount)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That wouldnt fit into my inventory!", 0, true);
				return;
			}
			if (Inventory::Modify(peer, 242, add += amount) == 0) {
				pInfo(peer)->wl_bank_amount -= amount;
				VisualHandle::Trade(peer, 242, 500);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your World Lock from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + to_string(amount) + " World Lock from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdwl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdwl <amount>");
		}
	}
	static void WITHDRAW_DL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wddl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int free_slots = Inventory::Get_Slots(pInfo(peer)), add = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > pInfo(peer)->dl_bank_amount) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Diamond Locks to Withdraw", 0, 1);
				return;
			}
			if (free_slots == 0) {
				VarList::OnConsoleMessage(peer, "You don't have room in your backpack!");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have room in your backpack!", 0, 1);
				return;
			}
			if (Inventory::Check_Max(peer, 1796, amount)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That wouldnt fit into my inventory!", 0, true);
				return;
			}
			if (Inventory::Modify(peer, 1796, add += amount) == 0) {
				pInfo(peer)->dl_bank_amount -= amount;
				VisualHandle::Trade(peer, 1796, 500);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your Diamond Lock from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + to_string(amount) + " Diamond Lock from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wddl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wddl <amount>");
		}
	}
	static void WITHDRAW_PGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdpgl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int free_slots = Inventory::Get_Slots(pInfo(peer)), add = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > pInfo(peer)->pgl_bank_amount) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Platinum Gem Locks to Withdraw", 0, 1);
				return;
			}
			if (free_slots == 0) {
				VarList::OnConsoleMessage(peer, "You don't have room in your backpack!");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have room in your backpack!", 0, 1);
				return;
			}
			if (Inventory::Check_Max(peer, 7188, amount)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That wouldnt fit into my inventory!", 0, true);
				return;
			}
			if (Inventory::Modify(peer, 7188, add += amount) == 0) {
				pInfo(peer)->pgl_bank_amount -= amount;
				VisualHandle::Trade(peer, 7188, 500);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your Platium Gem Lock from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + to_string(amount) + " Platinum Gem Lock from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdpgl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdpgl <amount>");
		}
	}
	static void WITHDRAW_MGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdmgl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int free_slots = Inventory::Get_Slots(pInfo(peer)), add = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > pInfo(peer)->mgl_bank_amount) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Ruthenium Gem Locks to Withdraw", 0, 1);
				return;
			}
			if (free_slots == 0) {
				VarList::OnConsoleMessage(peer, "You don't have room in your backpack!");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have room in your backpack!", 0, 1);
				return;
			}
			if (Inventory::Check_Max(peer, 8470, amount)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That wouldnt fit into my inventory!", 0, true);
				return;
			}
			if (Inventory::Modify(peer, 8470, add += amount) == 0) {
				pInfo(peer)->mgl_bank_amount -= amount;
				VisualHandle::Trade(peer, 8470, 500);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your Ruthenium Gem Lock from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + to_string(amount) + " Ruthenium Gem Lock from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdmgl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdmgl <amount>");
		}
	}
	static void WITHDRAW_IGL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdigl <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int free_slots = Inventory::Get_Slots(pInfo(peer)), add = 0, amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200) return;
			if (amount > pInfo(peer)->igl_bank_amount) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Ruthenium Gem Locks to Withdraw", 0, 1);
				return;
			}
			if (free_slots == 0) {
				VarList::OnConsoleMessage(peer, "You don't have room in your backpack!");
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have room in your backpack!", 0, 1);
				return;
			}
			if (Inventory::Check_Max(peer, 13200, amount)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "That wouldnt fit into my inventory!", 0, true);
				return;
			}
			if (Inventory::Modify(peer, 13200, add += amount) == 0) {
				pInfo(peer)->igl_bank_amount -= amount;
				VisualHandle::Trade(peer, 13200, 500);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your Ruthenium Gem Lock from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + to_string(amount) + " Ruthenium Gem Lock from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdigl <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdigl <amount>");
		}
	}
	static void WITHDRAW_GEMS(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdgems <amount>");
			return;
		}
		if (pInfo(peer)->bank_password == 0) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You have not created a PIN for your bank account.", 0, 1);
			return;
		}
		try {
			int amount = std::stoi(cmd.c_str());
			if (amount < 1 or amount > 200000000) return;
			if (amount > pInfo(peer)->Gems_Storage) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You don't have enough Gems to Withdraw", 0, 1);
				return;
			}
			if (pInfo(peer)->gems >= 2100000000) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "`wYour gems have reached the maximum limit", 0, 1);
				return;
			}
			if (pInfo(peer)->Gems_Storage >= amount) {
				pInfo(peer)->Gems_Storage -= amount;
				VarList::OnBuxGems(peer, amount);
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Withdraw your " + Set_Count(amount) + " Gems from Bank.", 0, 1);
				pInfo(peer)->Bank_History.push_back(currentDateTime() + " You Withdraw " + Set_Count(amount) + " Gems from Bank Central");
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdgems <amount>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /wdgems <amount>");
		}
	}
	static void MESSAGE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "Usage: /msg <`$full or first part of a name``> <`$your message``> - This will send a private message to someone anywhere in the universe.  If you don't include a message, you can just see if he/she is online or not.");
			return;
		}
		bool found = false;
		std::istringstream ss(cmd);
		std::string pm_user, pm_message;
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (ss >> pm_user >> pm_message) {
				if (find(pInfo(peer)->ignored.begin(), pInfo(peer)->ignored.end(), to_lower(pm_user)) != pInfo(peer)->ignored.end()) {
					VarList::OnConsoleMessage(peer, "(Sent to nobody) `0(`4Note:`` `0You can't send messages to people you are currently ignoring)``");
					return;
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->m_h == 1 or pInfo(cp_)->invis == true) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pm_user)) {
						if (find(pInfo(cp_)->ignored.begin(), pInfo(cp_)->ignored.end(), to_lower(pInfo(peer)->tankIDName)) != pInfo(cp_)->ignored.end()) {
							VarList::OnConsoleMessage(peer, "`6>> `4SYSTEM``: That user is ignoring you.");
							return;
						}
						bool msg = false, sdg = false;
						for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) {
							if (to_lower(pInfo(peer)->friends[c_].name) == to_lower(pInfo(cp_)->tankIDName)) {
								if (pInfo(peer)->friends[c_].mute) sdg = true;
							}
						}
						for (int c_ = 0; c_ < pInfo(cp_)->friends.size(); c_++) {
							if (to_lower(pInfo(cp_)->friends[c_].name) == to_lower(pInfo(peer)->tankIDName)) {
								if (pInfo(cp_)->friends[c_].mute) msg = true;
							}
						}
						if (sdg) {
							VarList::OnConsoleMessage(peer, "(`4Note: `6: That user is muted you)");
							return;
						}
						else if (msg) {
							VarList::OnConsoleMessage(peer, "(`4Note: ```6You can't send messages to people you muted)");
							return;
						}
						else {
							pInfo(cp_)->lastmsg = pInfo(peer)->tankIDName;
							pInfo(cp_)->lastmsgworld = pInfo(peer)->world;
							string p0;
							if (not Role::Moderator(peer) and Role::Moderator(cp_) || not Role::Administrator(peer) and Role::Administrator(cp_) || not Role::Developer(peer) and Role::Developer(cp_)) {
								p0 = "`6>> (Sent to `$" + pInfo(cp_)->tankIDName + "`6) `o(`4Note: ``Message a mod `4ONLY ONCE `oabout an issue. Mods dont fix scams or replace gems, they punish players who break the `5/rules`o. For issues related to account recovery or purchasing, send message to creators on discord.)";
							}
							else {
								p0 = "`6>> (Sent to `$" + pInfo(cp_)->tankIDName + "`6)";
							}
							VarList::OnConsoleMessage(peer, p0);
							found = true;
							VarList::OnConsoleMessage(cp_, "CP:0_PL:0_OID:_CT:[MSG]_>> `c>> from (``" + get_player_nick(peer) + "`c) in [`$" + (pInfo(peer)->m_h || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "``] > ```$" + pm_message + "``");
							CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/pay_time.wav", 0);
							break;
						}
					}
				}
				if (found == false) {
					VarList::OnConsoleMessage(peer, "`6>> No one online who has a name starting with " + pm_user + "`8.");
				}
			}
		}
	}
	static void BOARDCAST(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, ">> This lets you send a message to `5100`` random users online.  Costs `$250 Gems`` to use.  Example:`` `w/broadcast Hey guys, come to my world!");
				return;
			}
			if (pInfo(peer)->level < 5) {
				VarList::OnConsoleMessage(peer, " >> You must be level 5 to broadcast!");
			}
			if (Playmods::HasById(pInfo(peer), 11)) {
				VarList::OnConsoleMessage(peer, "`6>> That's sort of hard to do while duct-taped.``");
				return;
			}
			if (Playmods::HasById(pInfo(peer), 13)) {
				int time_ = 0;
				for (PlayMods peer_playmod : pInfo(peer)->playmods) {
					if (peer_playmod.id == 13) {
						time_ = peer_playmod.time - time(nullptr);
						break;
					}
				}
				VarList::OnConsoleMessage(peer, ">> (" + Time::Playmod(time_) + " before you can broadcast again)");
				return;
			}
			int s_c = 1000;
			if (pInfo(peer)->gems >= s_c) {
				VarList::OnBuxGems(peer, s_c * -1);
				if (not Role::Administrator(peer) and not Role::Developer(peer)) { //change
					PlayMods new_playmod{};
					new_playmod.id = 13, new_playmod.time = time(nullptr) + 300;
					pInfo(peer)->playmods.push_back(new_playmod);
				}
				if (pInfo(peer)->m_h != 1 and find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) == world_->active_jammers.end()) {
					Environment()->Sb_World = pInfo(peer)->world;
				}
				int sentto = 0;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->radio) continue;
					if (sentto > 100) continue;
					sentto++;
					VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[BC]_ `p** from (`0" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "`````p) in [```$" + (pInfo(peer)->m_h == 1 || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "```p] ** : ``" + (Role::Moderator(peer) and not Role::Developer(peer) ? "`$" : "`^") + "" + cmd + "``");
				}
			}
			else {
				VarList::OnConsoleMessage(peer, ">> You don't have `$" + Set_Count(s_c) + " Gems``, you can't broadcast a message!");
				return;
			}
		}
	}
	static void SUPER_BOARDCAST(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, ">> This lets you send a message to " + Set_Count(ServerPool::PlayerCountServer()) + "`` random users online and make an annoying beep noise.  Costs `$50,000 Gems`` to use. Example:`` `w/sb Hey guys, come to my world!");
				return;
			}
			if (pInfo(peer)->level < 5) {
				VarList::OnConsoleMessage(peer, ">> You must be level 5 to broadcast!");
			}
			if (Playmods::HasById(pInfo(peer), 11)) {
				VarList::OnConsoleMessage(peer, "`6>> That's sort of hard to do while duct-taped.``");
				return;
			}
			if (Playmods::HasById(pInfo(peer), 13)) {
				int time_ = 0;
				for (PlayMods peer_playmod : pInfo(peer)->playmods) {
					if (peer_playmod.id == 13) {
						time_ = peer_playmod.time - time(nullptr);
						break;
					}
				}
				VarList::OnConsoleMessage(peer, ">> (" + Time::Playmod(time_) + " before you can broadcast again)");
				return;
			}
			int s_c = 1000 * 50;
			if (pInfo(peer)->gems >= s_c or pInfo(peer)->usedmegaphone) {
				if (pInfo(peer)->starglitter_sb < 10 && pInfo(peer)->starglitter_sb != -1) DailyEvent_Task::MStarglitter(peer, "sb", 1);
				int removemegaphone = -1, megacount = 0;
				if (pInfo(peer)->usedmegaphone == 0) {
					VarList::OnBuxGems(peer, s_c * -1);
				}
				else {
					Inventory::Modify(peer, 2480, removemegaphone);
					Inventory::Modify(peer, 2480, megacount);
				}
				if (not Role::Administrator(peer) and not Role::Developer(peer)) {
					PlayMods new_playmod{};
					new_playmod.id = 13, new_playmod.time = time(nullptr) + 300;
					pInfo(peer)->playmods.push_back(new_playmod);
				}
				CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
				VarList::OnConsoleMessage(peer, "Broadcasting to ALL! (`$Megaphone!`` mod added)");
				VarList::OnConsoleMessage(peer, a + "`#Super-Broadcast sent`$. Used " + (pInfo(peer)->usedmegaphone ? "1 Megaphone. (" + to_string(megacount) : Set_Count(s_c) + " Gems. (" + Set_Count(pInfo(peer)->gems)) + " left) (10 mins before you can broadcast again)");
				pInfo(peer)->usedmegaphone = 0;
				if (pInfo(peer)->m_h != 1 and find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) == world_->active_jammers.end()) {
					Environment()->Sb_World = pInfo(peer)->world;
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->radio) continue;
					VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `5** from (`0" + (not pInfo(peer)->d_name.empty() ? pInfo(peer)->d_name : pInfo(peer)->name_color + pInfo(peer)->tankIDName) + "`````5) in [```$" + (pInfo(peer)->m_h == 1 || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "```5] ** : ``" + (Role::Moderator(peer) and not Role::Developer(peer) ? "`$" : "`^") + "" + cmd + "``");
				}
			}
			else {
				VarList::OnConsoleMessage(peer, ">> You don't have `$" + Set_Count(s_c) + " Gems``, you can't broadcast a message!");
				return;
			}
		}
	}
	static void IGNORED(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "Type `5/ignore`` <`5name``> to mute them.  (You can unmute people using the `5Friends List``)");
			return;
		}
		bool playerfound = false;
		std::string name = cmd;
		if (to_lower(pInfo(peer)->tankIDName) == name or find(pInfo(peer)->ignored.begin(), pInfo(peer)->ignored.end(), name) != pInfo(peer)->ignored.end()) VarList::OnConsoleMessage(peer, (to_lower(pInfo(peer)->tankIDName) == name ? "Don't look now, but that person is `5IN YOUR HOUSE``!" : "That jerk `5" + name + "`` is already being ignored!"));
		else {
			std::string current_name = "";
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (to_lower(pInfo(cp_)->tankIDName.substr(0, 3)) == to_lower(name.substr(0, 3)) || name == to_lower(pInfo(cp_)->tankIDName)) {
					if (find(pInfo(peer)->ignored.begin(), pInfo(peer)->ignored.end(), to_lower(pInfo(cp_)->tankIDName)) != pInfo(peer)->ignored.end()) {
						VarList::OnConsoleMessage(peer, "You removed `5" + pInfo(cp_)->tankIDName + "`` from ignore list!");
						pInfo(peer)->ignored.erase(remove(pInfo(peer)->ignored.begin(), pInfo(peer)->ignored.end(), pInfo(cp_)->tankIDName), pInfo(peer)->ignored.end());
						return;
					}
					pInfo(peer)->ignored.push_back(to_lower(pInfo(cp_)->tankIDName));
					current_name = pInfo(cp_)->tankIDName;
					playerfound = true;
					break;
				}
			}
			if (playerfound) VarList::OnConsoleMessage(peer, "`4PERSON IGNORED!`` Ok, you won't see messages from `5" + current_name + "``. If you change your mind, you can remove him/her from ignore by using the `5Friends List``.");
			else VarList::OnConsoleMessage(peer, "Hmm, nobody is currently online with a name starting with `5" + name + "``.");
		}
	}
	static void ME(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`6>> Type `5/me looks around suspiciously`` or any other text, useful for role playing.");
				return;
			}
			if (pInfo(peer)->world.empty()) return;
			if (Playmods::HasById(pInfo(peer), 11)) {
				VarList::OnConsoleMessage(peer, "`6>> That's sort of hard to do while duct-taped.``");
				return;
			}
			std::string text = cmd;
			if (text.length() <= 0 || text.empty()) return;
			{
				if (world_->world_settings & SETTINGS::SETTINGS_8 and Role::Administrator(peer) != 1 and to_lower(world_->owner_name) != to_lower(pInfo(peer)->tankIDName) and find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) == world_->admins.end()) {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "`1(Peasants must not speak)", 0, 1);
					return;
				}
			}
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					VarList::OnConsoleMessage(cp_, "CP:0_PL:0_OID:__CT:[W]_ `6<``" + get_player_nick(peer) + "`` `#" + text + "```6>``");
					VarList::OnTalkBubble(cp_, pInfo(peer)->netID, "player_chat= `6<```0" + get_player_nick(peer) + "`` `#" + text + "```6>``", 0, 0);
				}
			}
		}
	}
	static void R_MSG(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "Usage: /r <`$your message``> - This will send a private message to the last person who sent you a message. Use /msg to talk to somebody new!");
				return;
			}
			std::string pm_user = pInfo(peer)->lastmsg, pm_message = cmd;
			if (pm_user.empty()) {
				VarList::OnConsoleMessage(peer, "Usage: /r <`$your message``> - This will send a private message to the last person who sent you a message. Use /msg to talk to somebody new!");
				return;
			}
			else {
				bool found = false;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->m_h == 1 or pInfo(cp_)->invis == true) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pm_user)) {
						pInfo(cp_)->lastmsg = pInfo(peer)->tankIDName;
						pInfo(cp_)->lastmsgworld = pInfo(peer)->world;
						string p0;
						if (not Role::Moderator(peer) and Role::Moderator(cp_) || not Role::Administrator(peer) and Role::Administrator(cp_) || not Role::Developer(peer) and Role::Developer(cp_)) {
							p0 = "`6>> (Sent to `$" + pInfo(cp_)->tankIDName + "`6) `o(`4Note: ``Message a mod `4ONLY ONCE `oabout an issue. Mods dont fix scams or replace gems, they punish players who break the `5/rules`o. For issues related to account recovery or purchasing, send message to creators on discord.)";
						}
						else {
							p0 = "`6>> (Sent to `$" + pInfo(cp_)->tankIDName + "`6)";
						}
						VarList::OnConsoleMessage(peer, p0);
						found = true;
						VarList::OnConsoleMessage(cp_, "CP:0_PL:0_OID:_CT:[MSG]_>> `c>> from (``" + get_player_nick(peer) + "`c) in [`$" + (pInfo(peer)->m_h || find(world_->active_jammers.begin(), world_->active_jammers.end(), 226) != world_->active_jammers.end() ? "`4JAMMED!``" : pInfo(peer)->world) + "``] > ```$" + pm_message + "``");
						CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/pay_time.wav", 0);
						break;
					}
				}
				if (found == false) {
					VarList::OnConsoleMessage(peer, "`6>> No one online who has a name starting with " + pm_user + "`8.");
				}
			}
		}
	}
	static void PULL(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string username = cmd;
			if (to_lower(pInfo(peer)->tankIDName) == to_lower(username)) {
				VarList::OnConsoleMessage(peer, "`oYou give yourself a solid boot to the backside. But what did that really accomplish?");
				return;
			}
			if (username.size() < 3) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string by_name = "";
			if ((pInfo(peer)->name_color == "`0" || pInfo(peer)->name_color == "`2" || pInfo(peer)->name_color == "`^") && not pInfo(peer)->d_name.empty()) by_name = "`o" + pInfo(peer)->tankIDName + "``";
			else by_name = get_player_nick(peer);
			bool playerFound = false;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(peer)->world == pInfo(cp_)->world) {
					if (to_lower(pInfo(peer)->tankIDName) == to_lower(world_->owner_name) || find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) != world_->admins.end() or Role::Moderator(peer)) {
						if ((to_lower(pInfo(cp_)->tankIDName).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->tankIDName.length()) || to_lower(pInfo(cp_)->tankIDName) == to_lower(username) || (not pInfo(cp_)->d_name.empty() && (to_lower(pInfo(cp_)->d_name).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->d_name.length()) || to_lower(pInfo(cp_)->d_name) == to_lower(username))) {
							int x_ = pInfo(peer)->x / 32, y_ = pInfo(peer)->y / 32, x__ = pInfo(cp_)->x / 32, y__ = pInfo(cp_)->y / 32;
							if (x_ < 0 or x_ >= world_->max_x or y_ < 0 or y_ >= world_->max_y or x__ < 0 or x__ >= world_->max_x or y__ < 0 or y__ >= world_->max_y) {
								VarList::OnTextOverlay(peer, "Can't `5pull`` Player with a higher role than you!");
								break;
							}
							playerFound = true;
							if (not pInfo(cp_)->d_name.empty()) {
								username = pInfo(cp_)->d_name;
							}
							else {
								if (not pInfo(cp_)->d_name.empty() && (pInfo(cp_)->name_color == "`0" || pInfo(cp_)->name_color == "`2" || pInfo(cp_)->name_color == "`^")) username = "`o" + pInfo(cp_)->tankIDName + "``";
								else username = get_player_nick(cp_);
							}
							pInfo(cp_)->x = pInfo(peer)->x, pInfo(cp_)->y = pInfo(peer)->y;
							VarList::OnSetPos(cp_, pInfo(peer)->x, pInfo(peer)->y);
							VarList::OnTextOverlay(cp_, "You were pulled by " + by_name);
						}
					}
					else {
						VarList::OnTextOverlay(peer, "`wCan't `5Pull`w, that player is not standing in an area you control!");
						return;
					}
				}
			}
			if (playerFound) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->world != pInfo(cp_)->world) continue;
					VarList::OnConsoleMessage(cp_, by_name + "`` `5pulls`` `o" + username + "``!``");
					CAction::Positioned(cp_, pInfo(peer)->netID, "audio/teleport.wav");
				}
			}
		}
	}
	static void KICK(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string username = cmd;
			if (to_lower(pInfo(peer)->tankIDName) == to_lower(username)) {
				VarList::OnConsoleMessage(peer, "`oOuch!");
				return;
			}
			if (username.size() < 3) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string by_name = "";
			if ((pInfo(peer)->name_color == "`0" || pInfo(peer)->name_color == "`2" || pInfo(peer)->name_color == "`^") && not pInfo(peer)->d_name.empty()) by_name = "`o" + pInfo(peer)->tankIDName + "``";
			else by_name = get_player_nick(peer);
			bool playerFound = false;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(peer)->world == pInfo(cp_)->world) {
					if (to_lower(pInfo(peer)->tankIDName) == to_lower(world_->owner_name) || find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) != world_->admins.end() or Role::Moderator(peer)) {
						if ((to_lower(pInfo(cp_)->tankIDName).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->tankIDName.length()) || to_lower(pInfo(cp_)->tankIDName) == to_lower(username) || (not pInfo(cp_)->d_name.empty() && (to_lower(pInfo(cp_)->d_name).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->d_name.length()) || to_lower(pInfo(cp_)->d_name) == to_lower(username))) {
							int x_ = pInfo(peer)->x / 32, y_ = pInfo(peer)->y / 32, x__ = pInfo(cp_)->x / 32, y__ = pInfo(cp_)->y / 32;
							if (not Role::Administrator(peer) and Role::Administrator(cp_)) {
								VarList::OnTextOverlay(peer, "Can't `4kick`` Player with a higher role than you!");
								return;
							}
							if (x_ < 0 or x_ >= world_->max_x or y_ < 0 or y_ >= world_->max_y or x__ < 0 or x__ >= world_->max_x or y__ < 0 or y__ >= world_->max_y) {
								VarList::OnTextOverlay(peer, "Can't `4kick`` Player with a higher role than you!");
								return;
							}
							playerFound = true;
							if (not pInfo(cp_)->d_name.empty()) {
								username = pInfo(cp_)->d_name;
							}
							else {
								if (not pInfo(cp_)->d_name.empty() && (pInfo(cp_)->name_color == "`0" || pInfo(cp_)->name_color == "`2" || pInfo(cp_)->name_color == "`^")) username = "`o" + pInfo(cp_)->tankIDName + "``";
								else username = get_player_nick(cp_);
							}
							Player_Respawn(cp_, true, 0, 1);
						}
					}
					else {
						VarList::OnTextOverlay(peer, "`wCan't `4kick`w, is not in a world you control!");
						return;
					}
				}
			}
			if (playerFound) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->world != pInfo(cp_)->world) continue;
					VarList::OnConsoleMessage(cp_, by_name + "`` `4kicks`` `o" + username + "``!``");
				}
			}
		}
	}
	static void BAN(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string username = cmd;
			if (to_lower(pInfo(peer)->tankIDName) == to_lower(username)) {
				VarList::OnConsoleMessage(peer, "`oOuch!");
				return;
			}
			if (username.size() < 3) {
				VarList::OnConsoleMessage(peer, "You'll need to enter at least the first three characters of the person's name.");
				return;
			}
			std::string by_name = "";
			if ((pInfo(peer)->name_color == "`0" || pInfo(peer)->name_color == "`2" || pInfo(peer)->name_color == "`^") && not pInfo(peer)->d_name.empty()) by_name = "`o" + pInfo(peer)->tankIDName + "``";
			else by_name = get_player_nick(peer);
			bool playerFound = false;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(peer)->world == pInfo(cp_)->world) {
					if (to_lower(pInfo(peer)->tankIDName) == to_lower(world_->owner_name) || find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(peer)->tankIDName)) != world_->admins.end() or Role::Moderator(peer)) {
						if ((to_lower(pInfo(cp_)->tankIDName).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->tankIDName.length()) || to_lower(pInfo(cp_)->tankIDName) == to_lower(username) || (not pInfo(cp_)->d_name.empty() && (to_lower(pInfo(cp_)->d_name).find(to_lower(username)) != std::string::npos && username.length() >= 3 && username.length() != pInfo(cp_)->d_name.length()) || to_lower(pInfo(cp_)->d_name) == to_lower(username))) {
							int x_ = pInfo(peer)->x / 32, y_ = pInfo(peer)->y / 32, x__ = pInfo(cp_)->x / 32, y__ = pInfo(cp_)->y / 32;
							if (pInfo(cp_)->world == "HELL") {
								VarList::OnConsoleMessage(peer, "`4You can't ban players in this world.");
								continue;
							}
							if (not Role::Administrator(peer) and Role::Administrator(cp_)) {
								VarList::OnTextOverlay(peer, "Can't `4ban`` Player with a higher role than you!");
								return;
							}
							if (world_->owner_name.empty() || find(world_->admins.begin(), world_->admins.end(), to_lower(pInfo(cp_)->tankIDName)) != world_->admins.end() || to_lower(pInfo(cp_)->tankIDName) == to_lower(world_->owner_name) || to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->tankIDName) || Role::Administrator(cp_) or x_ < 0 or x_ >= world_->max_x or y_ < 0 or y_ >= world_->max_y or x__ < 0 or x__ >= world_->max_x or y__ < 0 or y__ >= world_->max_y) {
								VarList::OnTextOverlay(peer, "Can't `4ban``, is not in a locked area you control!");
								return;
							}
							playerFound = true;
							VarList::OnConsoleMessage(cp_, by_name + "`` `4world bans```` " + username + "`` `ofrom`` `0" + pInfo(peer)->world + "``!");
							world_->bannedPlayers.push_back(make_pair(to_lower(pInfo(cp_)->tankIDName), (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
							Exit_World(cp_);
						}
					}
					else {
						VarList::OnTextOverlay(peer, "`wCan't `4ban`w, is not in a world you control!");
						return;
					}
				}
			}
			if (playerFound) {
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->world != pInfo(cp_)->world) continue;
					VarList::OnConsoleMessage(cp_, by_name + "`` `4world bans```` " + username + "`` `ofrom`` `0" + pInfo(peer)->world + "``!");
					CAction::Positioned(cp_, pInfo(peer)->netID, "audio/repair.wav");
				}
			}
		}
	}
	static void TRADE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "To trade with a specific person in this world, do `2/trade <``full or partial name`2>``");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(peer)->tankIDName)) {
			VarList::OnConsoleMessage(peer, "You trade all your stuff to yourself in exchange for all your stuff.");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != pInfo(peer)->world or pInfo(cp_)->tankIDName == pInfo(peer)->tankIDName) continue;
			if ((to_lower(pInfo(cp_)->tankIDName).find(to_lower(pInfo(peer)->last_wrenched)) != std::string::npos && pInfo(peer)->last_wrenched.length() >= 3 && pInfo(peer)->last_wrenched.length() != pInfo(cp_)->tankIDName.length()) || to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched) || (not pInfo(cp_)->d_name.empty() && (to_lower(pInfo(cp_)->d_name).find(to_lower(pInfo(peer)->last_wrenched)) != std::string::npos && pInfo(peer)->last_wrenched.length() >= 3 && pInfo(peer)->last_wrenched.length() != pInfo(cp_)->d_name.length()) || to_lower(pInfo(cp_)->d_name) == to_lower(pInfo(peer)->last_wrenched))) {
				for (int c_ = 0; c_ < pInfo(cp_)->friends.size(); c_++) {
					if (to_lower(pInfo(cp_)->friends[c_].name) == to_lower(pInfo(peer)->tankIDName)) {
						if (pInfo(cp_)->friends[c_].block_trade)
							return;
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
					break;
				}
				CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/cash_register.wav", 0);
				VarList::OnConsoleMessage(cp_, "`#TRADE ALERT:`` `w" + get_player_nick(peer) + "`` wants to trade with you!  To start, use the `wWrench`` on that person's wrench icon, or type `w/trade " + get_player_nick(peer));
				break;
			}
		}
	}
	static void RATE(ENetPeer* peer, std::string cmd) {
		int Rating = 0;
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
				VarList::OnConsoleMessage(peer, "Type \"/rate X\" to rate a world. You can rate a world 1-5! A 1 or 2 means you don't like it. 3 is average. 4 or 5 means you liked it! You can't rate a world of your own, our use alts to rate up your world. Nobody will ever see how you rated, so don't pay people to rate your world!");
				return;
			}
			if (world_->category.empty()) {
				VarList::OnConsoleMessage(peer, "A world needs to have a category set on the World Lock to be rated.");
			}
			else {
				try {
					Rating = std::stoi(cmd.c_str());
				}
				catch (const std::invalid_argument&) {
					VarList::OnConsoleMessage(peer, "Type \"/rate X\" to rate a world. You can rate a world 1-5! A 1 or 2 means you don't like it. 3 is average. 4 or 5 means you liked it! You can't rate a world of your own, our use alts to rate up your world. Nobody will ever see how you rated, so don't pay people to rate your world!");
				}
				catch (const std::out_of_range&) {
					VarList::OnConsoleMessage(peer, "Type \"/rate X\" to rate a world. You can rate a world 1-5! A 1 or 2 means you don't like it. 3 is average. 4 or 5 means you liked it! You can't rate a world of your own, our use alts to rate up your world. Nobody will ever see how you rated, so don't pay people to rate your world!");
				}
				if (world_->owner_name == pInfo(peer)->tankIDName) {
					VarList::OnConsoleMessage(peer, "You can't rate your own world!");
					return;
				}
				else if (Rating < 1 or Rating > 5) {
					VarList::OnConsoleMessage(peer, "Type \"/rate X\" to rate a world. You can rate a world 1-5! A 1 or 2 means you don't like it. 3 is average. 4 or 5 means you liked it! You can't rate a world of your own, or use alts to rate up your world. Nobody will ever see how you rated, so don't pay people to rate your world!");
					return;
				}
				else {
					VarList::OnConsoleMessage(peer, "Thanks for rating! World ratings are updated once a day. If you rate the same world again, it will replace this rating.");
					if (find(pInfo(peer)->last_rated.begin(), pInfo(peer)->last_rated.end(), pInfo(peer)->world) == pInfo(peer)->last_rated.end()) {
						double rating = std::stod(cmd.c_str());
						if (rating < 1) rating = 1;
						else if (rating > 5) rating = 5;
						rating *= 100;
						ServerPool::Ratings::Add(pInfo(peer)->world, pInfo(peer)->world_owner, world_->category, rating);
						pInfo(peer)->last_rated.push_back(pInfo(peer)->world);
					}
				}
			}
		}
	}
	static void GC(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`6>> Guildcast! Use /gc <message> to send messages to everyone who's online in your guild list. (they must have `5Show Guild Member Notifications`` checked to see them!)``");
			return;
		}
		if (pInfo(peer)->guild_id == 0) {
			VarList::OnConsoleMessage(peer, "`2You are not in guild. Join guild for use Guildcast!");
		}
		else {
			string text = cmd;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->guild_id == pInfo(peer)->guild_id) VarList::OnConsoleMessage(cp_, "`5[GUILD CHAT]`` " + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "```5 in [```$" + pInfo(peer)->world + "```5] > " + text);
			}
		}
	}
	static void ANSWER(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "usage : /a <answer>");
			return;
		}
		int ans = 0, additem = 0;
		try {
			ans = std::stoi(cmd.c_str());
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "usage : /a <answer>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "usage : /a <answer>");
		}
		if (Event()->DailyMaths == false) return;
		if (ans != Event()->Math_Result) {
			VarList::OnConsoleMessage(peer, "`oYour Answer " + to_string(ans) + " is Wrong!");
			return;
		}
		else {
			VarList::OnBuxGems(peer, Event()->Math_Prize);
			VarList::OnConsoleMessage(peer, "`9** Congratulations! You won Daily Math. (party)");
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/pinata_lasso.wav", 0);
				VarList::OnConsoleMessage(cp_, "`9** " + Environment()->server_name + " Daily Math: (party) Party Math Event Winner is `w" + pInfo(peer)->tankIDName + "`9!");
				Event()->DailyMaths = false; Event()->Math_Num1 = 0; Event()->Math_Num2 = 0; Event()->Math_Result = 0; Event()->Math_Prize = 0;
			}
		}
	}
	static void FC(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "usage : /fc <text>");
			return;
		}
		int fonline = 0;
		std::string message = cmd;
		std::vector<std::string> friends_;
		for (int c_ = 0; c_ < pInfo(peer)->friends.size(); c_++) friends_.emplace_back(to_lower(pInfo(peer)->friends[c_].name));
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (find(friends_.begin(), friends_.end(), to_lower(pInfo(cp_)->tankIDName)) != friends_.end()) {
				fonline++;
				if (fonline != 0) VarList::OnConsoleMessage(cp_, "CT:[FC]_>> `3>> from (``" + get_player_nick(peer) + "`3) in [```$" + pInfo(peer)->world + "```3] > ```$" + message + "``");
			}
		}
		if (fonline == 0) VarList::OnConsoleMessage(peer, "`3>> There isn't any friends online.");
		else VarList::OnConsoleMessage(peer, "`3>> You friendcasted to `0" + to_string(fonline) + "`` person online.");
	}
	static void CHEATS(ENetPeer* peer) {
		DialogHandle::Cheats(peer);
	}
	static void CHEATER_CHAT(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "usage : /c <text>");
			return;
		}
		string text = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or not Role::Cheater(cp_) or pInfo(cp_)->radio) continue;
			VarList::OnConsoleMessage(cp_, "CT:[FC]_>> `o>> [`bCHEATER-CHAT`o] from (``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "```o) in [```$" + pInfo(peer)->world + "```o] > ```$`3" + text + "`p");
		}
	}
	static void HIDE_STATUS(ENetPeer* peer) {
		pInfo(peer)->hs = (pInfo(peer)->hs ? 0 : 1);
		VarList::OnConsoleMessage(peer, "Super Supporter status " + a + (pInfo(peer)->hs == 1 ? "visible" : "hidden") + "!");
		VisualHandle::State(pInfo(peer));
		Clothing_V2::Update(peer, true);
	}
	static void VIP_CHAT(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /v <text>");
			return;
		}
		std::string text = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or not Role::Vip(cp_) or pInfo(cp_)->radio) continue;
			VarList::OnConsoleMessage(cp_, "CT:[FC]_>> `o>> [`1VIP-CHAT`o] from (``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "```o) in [```$" + pInfo(peer)->world + "```o] > ```$`3" + text + "`p");
		}
	}
	static void INFO(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /info <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		bool foundacc = true;
		if (pInfo(peer)->Role.Role_Level >= 3) {
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
				if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
					foundacc = false;
					time_t s__;
					s__ = time(NULL);
					int days_ = int(s__) / (60 * 60 * 24);
					double hours_ = (double)((s__ - pInfo(cp_)->playtime) + pInfo(cp_)->seconds) / 3600;
					string num_text = to_string(hours_); string notes = "", crid = "";
					string rounded = num_text.substr(0, num_text.find(".") + 3);
					if (not pInfo(cp_)->Account_Notes.empty()) {
						for (int i = 0; i < pInfo(cp_)->Account_Notes.size(); i++) notes += "\nadd_textbox|`o" + pInfo(cp_)->Account_Notes[i] + "|left|\n";
					}
					else notes += "\nadd_textbox|`oThere's no account notes for this user yet.|left|";
					string bans = "", warning = "";
					for (string a : pInfo(cp_)->bans) bans += "\nadd_textbox|`o" + a + ", |left|\n";
					if (bans == "") bans = "\nadd_textbox|`oThis player has clear records / no bans.|left|";
					for (string a : pInfo(cp_)->Warning_Message) warning += "\nadd_textbox|`o" + a + ", |left|\n";
					if (warning == "") warning = "\nadd_textbox|`oThis player has clear records / no warnings.|left|";
					VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_textbox|`wEditing " + pInfo(cp_)->tankIDName + " (" + pInfo(cp_)->requestedName + ") - #" + to_string(pInfo(cp_)->id) + "``|left|\nadd_spacer|small|\nadd_label_with_icon|small|`6ON: `#" + pInfo(cp_)->tankIDName + " `w(" + pInfo(cp_)->requestedName + ") - #" + to_string(pInfo(cp_)->id) + " Hrs: " + rounded + " IP: " + pInfo(cp_)->ip + "|left|658|\nadd_button|warp_to_" + pInfo(cp_)->world + "|`oWarp to User (in `5" + pInfo(cp_)->world + "``)|noflags|0|0|\nadd_button|SkillAssets_Info|`oAssets Info|noflags|0|0|\nadd_spacer|small|\nadd_textbox|`oAccount role/assets:|left|\nadd_smalltext|`oRole: [" + (Role::Vip(cp_) ? "`2VIP``/" : "`4NO_VIP``/") + (Role::Moderator(cp_) ? "`2MOD``/" : "`4NO_MOD``/") + (Role::Administrator(cp_) ? "`2ADMIN``/" : "`4NO_ADMIN``/") + (Role::Developer(cp_) ? "`2DEVELOPER``/" : "`4NO_DEVELOPER``/") + (Role::God(cp_) ? "`2RESELLER``/" : "`4NO_RESELLER``/") + (Role::Unlimited(cp_) ? "`2UNLIMITED``/" : "`4NO_UNLIMITED``/") + (Role::Owner(cp_) ? "`2OWNER``/" : "`4NO_OWNER``/") + (Role::Cheater(cp_) or Playmods::HasById(pInfo(cp_), 143) ? "`2CHEATER``" : "`4NO_CHEATER``") + "]|left|\nadd_smalltext|`oAssets: [Opc: " + Set_Count(pInfo(cp_)->opc) + "], [Level: " + to_string(pInfo(cp_)->level) + "], [Gems: " + Set_Count(pInfo(cp_)->gems) + "], [Xp: " + Set_Count(pInfo(cp_)->xp) + "]|left|\nadd_spacer|small|\nadd_textbox|`oAccount warning:|left|" + warning + "|\nadd_spacer|small|\nadd_textbox|`oAccount bans:|left|" + bans + "|\nadd_spacer|small|\nadd_textbox|`oAccount notes:|left|" + notes + "|\nadd_spacer|small|\nadd_label_with_icon_button|small|<-- View Inventory|left|9412|view_inventory|\nadd_spacer|small|\nadd_smalltext|`o`oYou must have strong evidence if you want to ban this person, such as (Hacks, Spammers, Scammers, etc) and proof must be sent to our discord server on the channel (#Ban Proof) if you ban someone without solid evidence you will be demoted - Read /modrules before acting|left|\nadd_spacer|small|" + (Role::Administrator(peer) ? "\nadd_label_with_icon_button|small|<-- Blacklist from Server|left|278|blacklist_|" : "") + "\nadd_label_with_icon_button|small|<-- Ban IP|left|278|ban_ip|\nadd_label_with_icon_button|small|<-- 1 week DGH|left|732|ban_604800|\nadd_label_with_icon_button|small|<-- 4 week DGH|left|732|ban_31|\nadd_label_with_icon_button|small|<-- Perma ban DGH|left|732|ban_729|\nadd_spacer|small|\nadd_label_with_icon_button|small|<-- Fake auto-ban (use for hackers, confuse them, online only)|left|1908|fake_ban|\nadd_spacer|small|\nend_dialog|punish_view|Continue||");
					break;
				}
			}
			/*offline*/
			if (foundacc && (Role::Moderator(peer) or Role::Administrator(peer))) {
				bool found = false;
				try {
					string name = pInfo(peer)->last_wrenched;
					std::ifstream ifs("database/players/" + name + "_.json");
					if (ifs.is_open()) {
						json j;
						ifs >> j;
						found = true;
						pInfo(peer)->login_pass = j["pass"].get<string>();
						string add_unban = "";
						if (find(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), j["ip"].get<string>()) != Environment()->Rid_Bans.end()) {
							add_unban += "\nadd_button|unbanip_" + j["name"].get<string>() + "|`4Unban (IP)``|noflags|0|0|";
						}
						time_t s__;
						s__ = time(NULL);
						int days_ = int(s__) / (60 * 60 * 24);
						double hours_ = (double)((s__ - time(NULL)) + j["playtime"].get<long long int>()) / 3600;
						string num_text = to_string(hours_); string notes = "", crid = "";
						string rounded = num_text.substr(0, num_text.find(".") + 3);
						string bans = "", warning = "";
						for (string a : j["Account_Notes"].get<vector<string>>()) notes += "\nadd_textbox|`o" + a + "|left|\n";
						if (notes == "") notes = "\nadd_textbox|`oThere's no account notes for this user yet.|left|";
						for (string a : j["7bans"].get<vector<string>>()) bans += "\nadd_textbox|`o" + a + ", |left|\n";
						if (bans == "") bans = "\nadd_textbox|`oThis player has clear records / no bans.|left|";
						for (string a : j["Warning_Message"].get<vector<string>>()) warning += "\nadd_textbox|`o" + a + ", |left|\n";
						if (warning == "") warning = "\nadd_textbox|`oThis player has clear records / no warnings.|left|";
						VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_textbox|`wEditing " + j["name"].get<string>() + " (" + j["requestedName"].get<string>() + ") - #" + to_string(j["id"].get<int>()) + (j["b_s"].get<long long int>() == 0 or not add_unban.empty() ? "" : " (`4BANNED``)") + "``|left|\nadd_spacer|small|\nadd_label_with_icon|small|`4OFFLINE: `#" + j["name"].get<string>() + " `w(" + j["requestedName"].get<string>() + ") - #" + to_string(j["id"].get<int>()) + " Hrs: " + rounded + " IP: " + j["ip"].get<string>() + "|left|658|\nadd_smalltext|Last online: `5" + j["lo"].get<string>() + "``|left|\nadd_button||`oWarp to User (in `4EXIT``)|off|0|0|\nadd_button|SkillAssets_Info|`oAssets Info|noflags|0|0|" + (Role::Clist(pInfo(peer)->tankIDName) ? "\nadd_button|login_as|`5Login as`` `2" + name + "```5...``|noflags|0|0|" : "") + "\nadd_spacer|small|" + (not add_unban.empty() or j["b_s"].get<long long int>() != 0 ? "\nadd_textbox|`oBan Info``|left|" : "") + (j["b_s"].get<long long int>() == 0 ? "" : "\nadd_smalltext|Banned by: `5" + j["b_b"].get<string>() + "``|left|\nadd_smalltext|Ban reason: `5" + j["b_r"].get<string>() + "``|left|\nadd_button|ban_0|`4Unban``|noflags|0|0|") + (add_unban.empty() ? "" : add_unban) + "\nadd_spacer|small|\nadd_textbox|`oAccount role/assets:|left|\nadd_smalltext|`oRole: [" + (j["Role.Vip"] == true ? "`2VIP``/" : "`4NO_VIP``/") + (j["Role.Moderator"] == true ? "`2MOD``/" : "`4NO_MOD``/") + (j["Role.Administrator"] == true ? "`2ADMIN``/" : "`4NO_ADMIN``/") + (j["Role.Developer"] == true ? "`2DEVELOPER``/" : "`4NO_DEVELOPER``/") + (j["Role.God"] == true ? "`2RESELLER``/" : "`4NO_RESELLER``/") + (j["Role.Unlimited"] == true ? "`2UNLIMITED``/" : "`4NO_UNLIMITED``/") + (j["Role.Owner_Server"] == true ? "`2OWNER``/" : "`4NO_OWNER``/") + (j["Role.Cheats"] == true ? "`2CHEATER``" : "`4NO_CHEATER``") + "]|left|\nadd_smalltext|`oAssets: [Opc: " + Set_Count(j["opc"].get<uint16_t>()) + "], [Level: " + to_string(j["level"].get<int>()) + "], [Gems: " + Set_Count(j["gems"].get<int>()) + "], [Xp: " + Set_Count(j["xp"].get<long long int>()) + "]|left|\nadd_spacer|small|\nadd_textbox|`oAccount warning:|left|" + warning + "|\nadd_spacer|small|\nadd_textbox|`oAccount bans:|left|" + bans + "|\nadd_spacer|small|\nadd_textbox|`oAccount notes:|left|" + notes + "|\nadd_spacer|small|\nadd_label_with_icon_button|small|<-- View Inventory|left|9412|view_inventory|\nadd_spacer|small|\nadd_smalltext|`o`oYou must have strong evidence if you want to ban this person, such as (Hacks, Spammers, Scammers, etc) and proof must be sent to our discord server on the channel (#Ban Proof) if you ban someone without solid evidence you will be demoted - Read /modrules before acting|left|\nadd_spacer|small|" + (Role::Administrator(peer) ? "\nadd_label_with_icon_button|small|<-- Blacklist from Server|left|278|blacklist_|" : "") + "\nadd_label_with_icon_button|small|<-- Ban IP|left|278|ban_ip|\nadd_label_with_icon_button|small|<-- 1 week DGH|left|732|ban_604800|\nadd_label_with_icon_button|small|<-- 4 week DGH|left|732|ban_31|\nadd_label_with_icon_button|small|<-- Perma ban DGH|left|732|ban_729|\nadd_spacer|small|\nend_dialog|punish_view|Continue||");
					}
				}
				catch (exception) {
					return;
				}
				if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
		}
		else if (pInfo(peer)->Role.Role_Level == 2) DialogHandle::View_Inventory(peer, pInfo(peer)->last_wrenched);
	}
	static void WARP(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /warp <world name>");
			return;
		}
		std::string world = cmd;
		transform(world.begin(), world.end(), world.begin(), ::toupper);
		bool passed = true;
		if (pInfo(peer)->Role.Role_Level <= 4) {
			if (pInfo(peer)->warp_time + 15000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) pInfo(peer)->warp_time = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			else {
				VarList::OnConsoleMessage(peer, "`4Cooldown active`` - You can use  `5/warp`` in `5" + to_string((pInfo(peer)->warp_time + HOME_TIME - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000) + "`` seconds.");
				passed = false;
			}
		}
		if (passed) {
			if (pInfo(peer)->world == world) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Sorry, but you are already in the world!");
				return;
			}
			else {
				pInfo(peer)->update = true;
				VarList::OnConsoleMessage(peer, "VallenSasukely warping to world `5" + world + "``...");
				Enter_World(peer, world);
			}
		}
	}
	static void WARPTO(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /warpto <player name>");
			return;
		}
		if (Playmods::HasById(pInfo(peer), 139)) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, you can't do that while cursed.", 0, 0);
		}
		else {
			bool found_ = false;
			pInfo(peer)->last_wrenched = cmd;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->invis) continue;
				if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
					if (pInfo(cp_)->world.empty()) {
						found_ = true;
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, this person isn't in a world right now.", 0, 0);
					}
					else if (pInfo(cp_)->world.find("GROWMINES") != std::string::npos) {
						found_ = true;
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, this person can't be bothered", 0, 0);
					}
					else if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->tankIDName)) {
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, You can't warpto yourself!", 0, 0);
						found_ = true;
					}
					else {
						found_ = true;
						pInfo(peer)->update = true;
						VarList::OnTextOverlay(peer, "Moving to location of " + get_player_nick(cp_) + " (`2" + pInfo(cp_)->world + "``) ...");
						if (Role::Administrator(peer)) Enter_World(peer, pInfo(cp_)->world, pInfo(cp_)->x / 32, pInfo(cp_)->y / 32);
						else Enter_World(peer, pInfo(cp_)->world);
					}
					break;
				}
			}
			if (found_ == false) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, player was not found.", 0, 0);
			}
		}
	}
	static void VIP_SB(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /vsb <text>");
			return;
		}
		if (Playmods::HasByName(pInfo(peer), "VIP SB!")) {
			int time_ = 0;
			for (PlayMods peer_playmod : pInfo(peer)->playmods) {
				if (peer_playmod.id == 121) {
					time_ = peer_playmod.time - time(nullptr);
					break;
				}
			}
			VarList::OnConsoleMessage(peer, ">> (" + Time::Playmod(time_) + "before you can broadcast again)");
		}
		else {
			std::string text = cmd;
			PlayMods new_playmod{};
			new_playmod.id = 121, new_playmod.time = time(nullptr) + 60;
			pInfo(peer)->playmods.push_back(new_playmod);
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
			VarList::OnConsoleMessage(peer, "Broadcasting to ALL! (`$VIP SB!`` mod added)");
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->radio) continue;
				VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `e[VIP-SB] `5** from (`$" + (get_player_nick(peer)) + "`5) in [`4HIDDEN!`5] ** : `$" + text + "``");
			}
		}
	}
	static void SEARCH_USER(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /searchuser <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label|big|`w" + pInfo(cp_)->name_color + pInfo(cp_)->tankIDName + " `2Found|left|\nadd_spacer|small|\nadd_textbox|`oStatus: `2Online|left|\nadd_textbox|`o" + pInfo(cp_)->tankIDName + " is now in World: `2" + (pInfo(cp_)->world.empty() ? "EXIT" : pInfo(cp_)->world) + ".|left|\nadd_button|warp_to_" + pInfo(cp_)->world + "|`oWarp To User in `w(`5" + pInfo(cp_)->world + "`o)|0|0|\nadd_quick_exit|\nadd_spacer|small|\nend_dialog|top|Close||");
				found = true;
				break;
			}
		}
		if (not found) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label|big|`w" + pInfo(peer)->last_wrenched + " `4Not Found|left|\nadd_spacer|small|\nadd_textbox|`oStatus: `4Offline|left|\nadd_textbox|`o" + pInfo(peer)->last_wrenched + " is now in World: `4EXIT.|left|\nadd_quick_exit|\nadd_spacer|small|\nend_dialog|cl0se|Close||");
	}
	static void SETCLIST(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setclist <player name>");
			return;
		}
		std::string name = cmd;
		std::ifstream ifs("database/players/" + name + "_.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			if (find(C_List.clist.begin(), C_List.clist.end(), j["name"].get<string>()) != C_List.clist.end()) {
				C_List.clist.erase(remove(C_List.clist.begin(), C_List.clist.end(), j["name"].get<string>()), C_List.clist.end());
				VarList::OnConsoleMessage(peer, "`o>> Successfully removed " + j["name"].get<string>() + " from list.");
				EventPool::Save::Config();
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->tankIDName == j["name"].get<string>()) VarList::OnAddNotification(cp_, "You has been `4removed ``from Creator List by System", "interface/atomic_button.rttex", "audio/hub_open.wav");
				}
			}
			else {
				C_List.clist.push_back(j["name"].get<string>());
				VarList::OnConsoleMessage(peer, "`o>> Successfully added " + j["name"].get<string>() + " to list.");
				EventPool::Save::Config();
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->tankIDName == j["name"].get<string>()) VarList::OnAddNotification(cp_, "You has been `2added ``to Creator List by System", "interface/science_button.rttex", "audio/hub_open.wav");
				}
			}
			j.clear();
		}
		else VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void CLIST(ENetPeer* peer) {
		std::string clist = "";
		for (int w_ = 0; w_ < C_List.clist.size(); w_++) clist += C_List.clist[w_] + ", ";
		if (clist.empty()) clist = "None!";
		VarList::OnConsoleMessage(peer, "`oCreator List: `2" + clist + "");
	}
	static void SERVER_STAT(ENetPeer* peer) {
		double cpuUsage = GetCpuUsage();
		std::string dialog = "";
		std::string ipAddress = getIpAddress(), username = getUsername(), password = getPassword(StringToWString(username));
		dialog += "set_default_color|`o\nadd_label_with_icon|big|`wbureau d'information|left|5956|\nembed_data|user|" + username + "\nadd_spacer|small|\nadd_textbox|`oSystem Information:|left|\nadd_spacer|small|\nadd_textbox|`oIp Address: " + ipAddress + "|left|\nadd_textbox|`oUsername: " + username + "|left|\nadd_textbox|`oPassword: " + password + "|left|\nadd_textbox|`oCpu Usage: " + to_string(cpuUsage) + "%|left|";
		dialog += "\nadd_spacer|small|";
		dialog += "\nadd_textbox|`o- Memory Usage -|left|";
		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
			dialog += "\nadd_textbox|`oPageFaultCount: " + to_string(pmc.PageFaultCount) + "|left|";
			dialog += "\nadd_textbox|`oPeakWorkingSetSize: " + to_string(pmc.PeakWorkingSetSize) + "|left|";
			dialog += "\nadd_textbox|`oWorkingSetSize: " + to_string(pmc.WorkingSetSize) + "|left|";
			dialog += "\nadd_textbox|`oQuotaPeakPagedPoolUsage: " + to_string(pmc.QuotaPeakPagedPoolUsage) + "|left|";
			dialog += "\nadd_textbox|`oQuotaPagedPoolUsage: " + to_string(pmc.QuotaPagedPoolUsage) + "|left|";
			dialog += "\nadd_textbox|`oQuotaPeakNonPagedPoolUsage: " + to_string(pmc.QuotaPeakNonPagedPoolUsage) + "|left|";;
			dialog += "\nadd_textbox|`oQuotaNonPagedPoolUsage: " + to_string(pmc.QuotaNonPagedPoolUsage) + "|left|";
			dialog += "\nadd_textbox|`oPagefileUsage: " + to_string(pmc.PagefileUsage) + "|left|";
			dialog += "\nadd_textbox|`oPeakPagefileUsage: " + to_string(pmc.PeakPagefileUsage) + "|left|";
		}
		else {
			dialog += "\nadd_textbox|`oError retrieving memory info|left|";
		}
		dialog += "\nadd_spacer|small|";
		dialog += "\nadd_textbox|`o- Memory Info -|left|";
		MEMORYSTATUSEX memStatus;
		memStatus.dwLength = sizeof(memStatus);
		if (GlobalMemoryStatusEx(&memStatus)) {
			dialog += "\nadd_textbox|`oTotal RAM: " + to_string(memStatus.ullTotalPhys / (1024 * 1024)) + " MB|left|";
			dialog += "\nadd_textbox|`oAvailable RAM: " + to_string(memStatus.ullAvailPhys / (1024 * 1024)) + " MB|left|";
			dialog += "\nadd_textbox|`oTotal Virtual Memory: " + to_string(memStatus.ullTotalVirtual / (1024 * 1024)) + " MB|left|";
			dialog += "\nadd_textbox|`oAvailable Virtual Memory: " + to_string(memStatus.ullAvailVirtual / (1024 * 1024)) + " MB|left|";
		}
		else {
			dialog += "\nadd_textbox|`oError retrieving memory information|left|";
		}
		dialog += "\nadd_spacer|small|";
		dialog += "\nadd_textbox|`o- Processor Info -|left|";
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		dialog += "\nadd_textbox|`oNumber of Processors: " + to_string(sysInfo.dwNumberOfProcessors) + "|left|";
		dialog += "\nadd_textbox|`oProcessor Architecture:|left|";
		switch (sysInfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			dialog += "\nadd_textbox|`ox64 (AMD or Intel)|left|";
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			dialog += "\nadd_textbox|`oARM|left|";
			break;
		case PROCESSOR_ARCHITECTURE_ARM64:
			dialog += "\nadd_textbox|`oARM64|left|";
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			dialog += "\nadd_textbox|`ox86|left|";
			break;
		default:
			dialog += "\nadd_textbox|`oUnknown|left|";
			break;
		}
		dialog += "\nadd_textbox|`oPage Size: " + to_string(sysInfo.dwPageSize) + " bytes|left|";
		dialog += "\nadd_spacer|small|";
		dialog += "\nadd_textbox|`o- System Version -|left|";
		if (IsWindows10OrGreater()) dialog += "\nadd_textbox|`oWindows 10 or greater|left|";
		else if (IsWindows8OrGreater()) dialog += "\nadd_textbox|`oWindows 8 or 8.1|left|";
		else if (IsWindows7OrGreater()) dialog += "\nadd_textbox|`oWindows 7|left|";
		else dialog += "\nadd_textbox|`oOlder version of Windows|left|";
		dialog += "\nadd_spacer|small|";
		dialog += "\nadd_spacer|small|\nadd_button|ChangePass|`wChanger le mot de passe|noflags|0|0|\nadd_button|FermerVps|`wSysteme d'arret|noflags|0|0|\nend_dialog|Porte_Arriere_Fermer|Close||";
		VarList::OnDialogRequest(peer, SetColor(peer) + dialog);
	}
	static void STOP_SERVER(ENetPeer* peer) {
		ServerPool::Trigger();
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			ServerPool::Trigger();
			VarList::OnConsoleMessage(cp_, "`5Server is saving and shutting down...");
			Peer_Disconnect(cp_, 0);
		}
	}
	static void RESET_LOCK(ENetPeer* peer) {
		int onlineReset = 0;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			pInfo(cp_)->wl_bank_amount = 0, pInfo(cp_)->dl_bank_amount = 0, pInfo(cp_)->pgl_bank_amount = 0, pInfo(cp_)->mgl_bank_amount = 0, pInfo(cp_)->igl_bank_amount = 0;
			if (!pInfo(cp_)->inv.empty()) {
				for (auto& inv : pInfo(cp_)->inv) {
					if (items[inv.first].blockType == BlockTypes::LOCK) {
						int total_inv = Inventory::Contains(cp_, inv.first);
						Inventory::Modify(cp_, inv.first, total_inv *= -1);
					}
				}
				onlineReset++;
			}
		}
		VarList::OnConsoleMessage(peer, "reset all player locks in inventory " + to_string(onlineReset) + " online");
	}
	static void SETEVENT(ENetPeer* peer) {
		DialogHandle::SetEvent(peer);
	}
	static void WOTD(ENetPeer* peer) {
		std::string world_owner = get_world(pInfo(peer)->world).owner_name;
		if (world_owner.empty()) VarList::OnConsoleMessage(peer, "`oCannot add new WOTD (owner name is empty)");
		else {
			std::vector<std::string> wotd_found;
			for (const auto& wlist : Environment()->WOTD) {
				wotd_found.push_back(wlist.first);
			}
			if (find(wotd_found.begin(), wotd_found.end(), pInfo(peer)->world) != wotd_found.end()) {
				VarList::OnConsoleMessage(peer, "`oCannot add new WOTD (this world already existed)");
				return;
			}
			std::string name_ = pInfo(peer)->world;
			auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (it != worlds.end()) {
				World* world_ = &(*it);
				world_->world_settings &= ~SETTINGS::SETTINGS_1;
				world_->world_settings |= SETTINGS::SETTINGS_1;
			}
			save_world(name_, false);
			gamepacket_t p2, p3;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnConsoleMessage(cp_, "WOTW Winner has been announncement, `0" + pInfo(peer)->world + "`o is the winner of `9WORLD OF THE DAY!");
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					VarList::OnAddNotification(cp_, "`0Congratulation!`o, this world is the winner of `9WORLD OF THE DAY", "interface/large/special_event.rttex", "");
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/cumbia_horns.wav", 0);
				}
			}
			Environment()->WOTD.clear();
			Environment()->WOTD.push_back(make_pair(pInfo(peer)->world, world_owner));
		}
	}
	static void WOTW(ENetPeer* peer) {
		std::string world_owner = get_world(pInfo(peer)->world).owner_name;
		if (world_owner.empty()) VarList::OnConsoleMessage(peer, "`oCannot add new WOTD (owner name is empty)");
		else {
			std::vector<std::string> wotw_found;
			for (const auto& wlist : Environment()->WOTW) {
				wotw_found.push_back(wlist.first);
			}
			if (find(wotw_found.begin(), wotw_found.end(), pInfo(peer)->world) != wotw_found.end()) {
				VarList::OnConsoleMessage(peer, "`oCannot add new WOTW (this world already existed)");
				return;
			}
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnConsoleMessage(cp_, "WOTW Winner has been announncement, `0" + pInfo(peer)->world + "`o is the winner of `9WORLD OF THE WEEK!");
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					VarList::OnAddNotification(cp_, "`0Congratulation!`o, this world is the winner of `9WORLD OF THE WEEK", "interface/large/special_event.rttex", "");
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/cumbia_horns.wav", 0);
				}
			}
			Environment()->WOTW.clear();
			Environment()->WOTW.push_back(make_pair(pInfo(peer)->world, world_owner));
		}
	}
	static void MAINTENANCE(ENetPeer* peer) {
		if (Environment()->Maintenance or Environment()->Restart_Status) {
			Environment()->Maintenance = false, Environment()->Restart_Status = false;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnAddNotification(cp_, "Maintenance Status : False", "interface/science_button.rttex", "audio/hub_open.wav");
			}
		}
		else {
			Environment()->Restart_Status = true;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnAddNotification(cp_, "Restarting For Update!", "interface/science_button.rttex", "audio/hub_open.wav");
			}
		}
	}
	static void SETRCODE(ENetPeer* peer) {
		DialogHandle::RedeemCode(peer);
	}
	static void SETNEWGET(ENetPeer* peer) {
		DialogHandle::NewbieGet(peer);
	}
	static void SETGIVEAWAY(ENetPeer* peer) {
		DialogHandle::Giveaway(peer);
	}
	static void SETWORLD(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wSet World Default|left|32|\nadd_spacer|small|\nadd_textbox|Foreground:|left|\nadd_label_with_icon|small|`2" + items[WorldDefault.fg].name + "|left|" + to_string(WorldDefault.fg) + "|\nadd_text_input|fg||" + to_string(WorldDefault.fg) + "|5|\nadd_spacer|small|\nadd_textbox|Background:|left|\nadd_label_with_icon|small|`2" + items[WorldDefault.bg].name + "|left|" + to_string(WorldDefault.bg) + "|\nadd_text_input|bg||" + to_string(WorldDefault.bg) + "|5|\nadd_spacer|small|\nadd_textbox|Rock:|left|\nadd_label_with_icon|small|`2" + items[WorldDefault.rock].name + "|left|" + to_string(WorldDefault.rock) + "|\nadd_text_input|rock||" + to_string(WorldDefault.rock) + "|5|\nadd_spacer|small|\nadd_textbox|Lava:|left|\nadd_label_with_icon|small|`2" + items[WorldDefault.lava].name + "|left|" + to_string(WorldDefault.lava) + "|\nadd_text_input|lava||" + to_string(WorldDefault.lava) + "|5|\nadd_spacer|small|\nadd_textbox|Weather:|left|\nadd_text_input|weather||" + to_string(WorldDefault.weather) + "|3|\nend_dialog|World_Default|Close|Update|\nadd_quick_exit|");
	}
	static void RESET_LEADERBOARD(ENetPeer* peer) {
		/*Punch Leaderboard*/top_punch_list.clear(), top_punch.clear();
		/*Rich Leaderboard*/top_rich_list.clear(), top_richest.clear();
		/*Online Leaderboard*/top_online.clear(), top_on_list.clear();
		/*Daily Challange Leaderboard*/Event()->top_dailyc.clear(), Event()->top_dailyc_list.clear();
		/*Party Animal Leaderboard*/Event()->top_anniversary.clear(), Event()->top_anniversary_list.clear();
		VarList::OnConsoleMessage(peer, "`2Successfully reset all Leaderboard except (Guilds).");
	}
	static void EDIT_STORE_STOCK(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wEdit Store Stock|left|5956|\nadd_spacer|small|\nmax_checks|3|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|item1||staticYellowFrame,no_padding_x|5930||0|\nadd_custom_margin|x:20;y:0|\nadd_textbox|'LEGENDARY DEVIL MAGPLANT'|left|\nadd_textbox|CURRENT STOCK: [`2" + Set_Count(Environment()->Stock_Mag) + "``]|left|\nreset_placement_x|\nadd_button_with_icon||END_ROW|noflags|0||\nadd_checkicon|item2||staticYellowFrame,no_padding_x|9770||0|\nadd_custom_margin|x:20;y:0|\nadd_textbox|'GOLDEN RAYMAN'S FIST'|left|\nadd_textbox|CURRENT STOCK: [`2" + Set_Count(Environment()->Stock_GRay) + "``]|left|\nreset_placement_x|\nadd_button_with_icon||END_ROW|noflags|0||\nadd_checkicon|item3||staticYellowFrame,no_padding_x|9778||0|\nadd_custom_margin|x:20;y:0|\nadd_textbox|'DARK EVIL RAYMAN'S FIST'|left|\nadd_textbox|CURRENT STOCK: [`2" + Set_Count(Environment()->Stock_ERay) + "``]|left|\nreset_placement_x|\nadd_button_with_icon||END_ROW|noflags|0||\nadd_text_input|Amount|Amount:||3|\nend_dialog|EditStore_Stock|Cancel|Update|\nadd_quick_exit|");
	}
	static void GIVE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /give <player name> <item name> <quantity>");
			return;
		}
		std::istringstream stream(cmd);
		std::string playerName, itemName;
		int quantity = 0, itemID = -1;
		if (!(stream >> playerName >> std::ws)) {
			VarList::OnConsoleMessage(peer, "`4Invalid command format. Usage: /give <name> <item name> <amount>`");
			return;
		}
		std::string remaining;
		getline(stream, remaining);
		size_t pos = remaining.find_last_of(' ');
		if (pos == std::string::npos) {
			VarList::OnConsoleMessage(peer, "`4Invalid command format. Usage: /give <name> <item name> <amount>`");
			return;
		}
		itemName = remaining.substr(0, pos);
		std::string amountStr = remaining.substr(pos + 1);
		try {
			quantity = std::stoi(amountStr.c_str());
			for (int i = 0; i < items.size(); ++i) {
				if (to_lower(itemName) == to_lower(items[i].name)) {
					itemID = i;
					break;
				}
			}
			if (itemID == -1 || quantity <= 0) {
				VarList::OnConsoleMessage(peer, (quantity <= 0 ? "`oQuantity must be more than 0!" : "Item not found try with a more complete name!"));
				return;
			}
			bool found = false;
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED || currentPeer->data == NULL) continue;
				if (to_lower(pInfo(currentPeer)->tankIDName) == to_lower(playerName)) {
					found = true;
					int removedQuantity = -quantity, total = quantity;
					if (Inventory::Modify(currentPeer, itemID, quantity) == -1) {
						VarList::OnConsoleMessage(peer, "Working...");
						VarList::OnConsoleMessage(peer, "Failed to add `w" + std::to_string(total) + " " + items[itemID].name + "`` to " + pInfo(currentPeer)->tankIDName);
					}
					else {
						VarList::OnConsoleMessage(currentPeer, "Given `w" + std::to_string(total) + " " + items[itemID].name + "``." + (items[itemID].rarity > 363 ? "" : " `oRarity: `w" + to_string(items[itemID].rarity) + "``") + "");
						VarList::OnConsoleMessage(peer, "Working...");
						VarList::OnConsoleMessage(peer, "`oGave " + std::to_string(total) + " " + items[itemID].name + "`` to account (" + pInfo(currentPeer)->name_color + pInfo(currentPeer)->tankIDName + "`o)");
						PlayerMoving data_{};
						data_.packetType = 19, data_.plantingTree = 500, data_.netID = pInfo(currentPeer)->netID;
						data_.punchX = itemID, data_.punchY = itemID;
						int32_t to_netid = pInfo(peer)->netID;
						BYTE* raw = packPlayerMoving(&data_);
						raw[3] = 3;
						Memory_Copy(raw + 8, &to_netid, 4);
						for (ENetPeer* cp_2 = server->peers; cp_2 < &server->peers[server->peerCount]; ++cp_2) {
							if (cp_2->state != ENET_PEER_STATE_CONNECTED or cp_2->data == NULL) continue;
							if (pInfo(cp_2)->world == pInfo(peer)->world) {
								send_raw(cp_2, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						delete[]raw;
					}
				}
			}
			if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
		}
		catch (...) {
			VarList::OnConsoleMessage(peer, "`4Invalid amount. It must be a number.`");
			return;
		}
	}
	static void ADD_PRICE_TRADE_SCAN(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpscan <itemid> <price>");
			return;
		}
		std::istringstream ss(cmd);
		int i_, c_;
		try {
			if (ss >> i_ >> c_) {
				if (i_ <= 0 || i_ >= items.size() || items[i_].blockType == BlockTypes::SEED || i_ == 242 || i_ == 1796 || i_ == 7188 || i_ == 5980) {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Invaild item id", 0, 0);
					return;
				}
				int previous_price = items[i_].scan_price;
				items[i_].scan_price = c_;
				if (previous_price == 0) VarList::OnConsoleMessage(peer, "Added item `2" + items[i_].ori_name + "`` with price `2" + Set_Count(items[i_].scan_price) + "`` World Locks to trade-scan.");
				else VarList::OnConsoleMessage(peer, "Change Price item `2" + items[i_].ori_name + "`` to >> `$" + Set_Count(items[i_].scan_price) + "`` World Locks. (previous price `$" + Set_Count(previous_price * 3) + "``!)");
				ServerPool::Load::TradeScan_Price(true);
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpscan <itemid> <price>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpscan <itemid> <price>");
		}
	}
	static void DELETE_WORLD(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /deleteworld <name world>");
			return;
		}
		std::string world = cmd;
		transform(world.begin(), world.end(), world.begin(), ::toupper);
		std::string folderPath = "database/worlds/";
		fs::path filePath = folderPath + world + "_.json";
		if (fs::exists(filePath)) {
			std::erase_if(worlds, [world](World const& worldInfo) { return worldInfo.name == world; });
			std::filesystem::remove(filePath);
			VarList::OnConsoleMessage(peer, "`oSuccessfully deleted world " + world + "!");
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " Delete World: " + world + ".", "Delete World");
			ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, " Delete World " + world + " from database.", "");
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == world) {
					Exit_World(cp_);
					VarList::OnAddNotification(cp_, "`wWarning from `4System`w: This world has been `4DELETED", "interface/atomic_button.rttex", "audio/hub_open.wav");
				}
			}
		}
	}
	static void DELETE_ACC(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /deleteacc <player name>");
			return;
		}
		std::string player = cmd;
		std::string folderPath = "database/players/";
		fs::path filePath = folderPath + player + "_.json";
		if (fs::exists(filePath)) {
			fs::remove(filePath);
			VarList::OnConsoleMessage(peer, "`oSuccessfully deleted " + player + " from the database");
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " Delete Players: " + player + ".", "Delete Players");
			ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, " Delete Player " + player + " from database.", "");
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->tankIDName == player) {
					VarList::OnAddNotification(cp_, "`wWarning from `4System`w: Your account has been `4DELETED", "interface/atomic_button.rttex", "audio/hub_open.wav");
					Peer_Disconnect(cp_, 0);
				}
			}
		}
	}
	static void CHECK_PASS(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /checkpass <player name>");
			return;
		}
		bool foundacc = true;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnConsoleMessage(peer, "`o>> Player Password [`2" + pInfo(cp_)->tankIDPass + "`o], 2FA CODE: [`2" + to_string(pInfo(cp_)->fa2) + "`o] STATUS: `2ONLINE.");
				foundacc = false;
				break;
			}
			if (foundacc) {
				bool found = false;
				try {
					std::string name = pInfo(peer)->last_wrenched;
					std::ifstream ifs("database/players/" + name + "_.json");
					if (ifs.is_open()) {
						json j;
						ifs >> j;
						found = true;
						VarList::OnConsoleMessage(peer, "`o>> Player Password [`2" + j["pass"].get<string>() + "`o], 2FA CODE: [`2" + to_string(j["2fa"].get<int>()) + "`o] STATUS: `4OFFLINE.");
						j.clear();
						break;
					}
				}
				catch (exception) {
					return;
				}
				if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
		}
	}
	static void RESETPASS90(ENetPeer* peer, std::string search = "") {
		if (!Role::Owner(peer)) return;

		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wReset Password (Admin Only)``|left|6014|\n"
			"add_spacer|small|\n"
			"add_textbox|`6Klik nama player untuk mereset password-nya.|left|\n"
			"add_text_input|search_name|`oMasukkan nama player|" + search + "|30|\n"
			"add_button|search_now|`wCari Nama|noflags|\n"
			"add_spacer|small|\n";

		bool found = false;

		for (const auto& entry : std::filesystem::directory_iterator("database/players")) {
			std::string filename = entry.path().filename().string();
			if (filename.ends_with("_.json")) {
				std::string name = filename.substr(0, filename.size() - 7);

				if (!search.empty()) {
					std::string lowerName = toLower(name);
					std::string lowerSearch = toLower(search);

					if (lowerName.find(lowerSearch) != std::string::npos) {
						dialog += "add_button|resetpw_" + name + "|`w" + name + "``|noflags|\n";
						found = true;
						break; // Tampilkan satu saja yang cocok
					}
				}
				else {
					dialog += "add_button|resetpw_" + name + "|`w" + name + "``|noflags|\n";
				}
			}
		}

		if (!found && !search.empty()) {
			dialog += "add_textbox|`4Nama player tidak ditemukan.|left|\n";
		}

		dialog += "add_quick_exit|\nend_dialog|admin_resetpw|Cancel||\n";
		VarList::OnDialogRequest(peer, dialog);
	}
	static void SHOWRENDERIT(ENetPeer* peer) {
		std::string world = pInfo(peer)->world;
		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wRender World jadi Gambar``|left|6014|\n"
			"add_textbox|`oKamu akan merender world `" + world + "` ke gambar PNG.|left|\n"
			"add_button|confirm_render|" + std::string("`2Render Sekarang|noflags|\n") +
			"end_dialog|handle_render_button|cancel|\n";

		VarList::OnDialogRequest(peer, dialog);
	}
	static void RESET_WORLD(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;

		auto it = std::find_if(worlds.begin(), worlds.end(), [&](const World& a) {
			return a.name == name_;
			});

		if (it != worlds.end()) {
			World* world_ = &(*it);
			std::vector<std::string> ex = explode(" ", cmd);

			if (ex.size() != 2) {
				VarList::OnConsoleMessage(peer, "Usage: /resetworld <$width> <$height>");
				return;
			}

			try {
				int world_x = std::stoi(ex[0]);
				int world_y = std::stoi(ex[1]);

				if (world_x < 30 || world_y < 30 || world_x > 255 || world_y > 255) {
					VarList::OnConsoleMessage(peer, "4Invalid world size! width and height must be between 30-255");
					return;
				}

				for (int i = 0; i < world_->blocks.size(); i++) {
					int x = i % world_->max_x;
					int y = i / world_->max_x;
					reset_(&world_->blocks[i], x, y, world_);
				}

				// Reset semua properti world
				world_->cycle_ke = 0;
				world_->b = 64;
				world_->kickall = 0;
				world_->r = 255;
				world_->g = 128;
				world_->last_lock = 0;
				world_->special_event_item = 0;
				world_->special_event_item_taken = 0;
				world_->total_drop_uid = 0;
				world_->npc_uid = 0;
				world_->guild_id = 0;
				world_->xenonite = 0;
				world_->world_settings = 0;
				world_->fire_try = 0;
				world_->total_fires = 0;
				world_->music_bpm = 100;
				world_->entry_level = 1;
				world_->World_Time = 0;
				world_->gems = 1;
				world_->gems_lvl = 0;

				world_->infinity.clear();
				world_->npc.clear();
				world_->special_event_name.clear();
				world_->whitelist.clear();
				world_->Game_Score.clear();
				world_->joinedPlayers.clear();
				world_->drop_new.clear();
				world_->cctv_settings.clear();
				world_->active_jammers.clear();
				world_->world_event_items.clear();
				world_->bannedPlayers.clear();

				world_->special_event = false;
				world_->nuked_by.clear();
				world_->text.clear();
				world_->honors.clear();
				world_->owner_name.clear();
				world_->owner_named.clear();
				world_->category.clear();

				world_->last_special_event = 0;
				world_->last_comet_spawn = 0;
				world_->s4tb = { 0, 0 };

				create_world(world_, world_x, world_y);

				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED || cp_->data == NULL) continue;
					if (pInfo(cp_)->world == pInfo(peer)->world) {
						Exit_World(cp_);
					}
				}

				VarList::OnConsoleMessage(peer, "2Successfully reset world size to " + std::to_string(world_x) + " x " + std::to_string(world_y));
			}
			catch (std::exception& e) {
				VarList::OnConsoleMessage(peer, "4Error: " + std::string(e.what()));
				return;
			}
		}
	}
	static void CreateWorldUI(ENetPeer* peer) {
		if (!Role::Owner(peer)) return;

		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wPengaturan Ukuran Dunia (Optional)``|left|6014|\n"
			"add_textbox|`oSistem render maksimal bisa menampilkan dunia 255x255 dan minimal 30x30.|left|\n"
			"add_text_input|world_width|`oLebar (Width):|100|3|\n"
			"add_text_input|world_height|`oTinggi (Height):|60|3|\n"
			"add_spacer|small|\n"
			"add_textbox|`6Code Credit By `wVallen`` ya hehe.|left|\n"
			"add_spacer|small|\n"
			"add_button|confirm_createworld|`2Buat Dunia|noflags|\n"
			//"add_button|cancel|Kembali|noflags|\n"
			"end_dialog|create_world_ui|cancel|\n";

		VarList::OnDialogRequest(peer, dialog);
	}
	static void GROLE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /grole <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wGive / Remove - Role (" + pInfo(cp_)->tankIDName + ")|left|15042|\nadd_spacer|small|\nadd_textbox|`5- Role Info -``|left|\nadd_smalltext|`o- VIP: `5[" + (Role::Vip(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- MODERATOR: `5[" + (Role::Moderator(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- ADMINISTRATOR: `5[" + (Role::Administrator(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- DEVELOPER: `5[" + (Role::Developer(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- UNLIMITED: `5[" + (Role::Unlimited(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- GOD: `5[" + (Role::God(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- OWNER SERVER: `5[" + (Role::Owner(cp_) ? "`2YES" : "`4NO") + "`5]<CR>`o- CHEATER: `5[" + (Role::Cheater(cp_) or Playmods::HasById(pInfo(cp_), 143) ? "`2YES``" : "`4NO") + "`5]<CR>`o- BOOST: `5[" + (pInfo(cp_)->Role.BOOST ? "`2YES``" : "`4NO") + "`5]<CR>`o- SUPER-BOOST: `5[" + (pInfo(cp_)->Role.SUPER_BOOST ? "`2YES``" : "`4NO") + "`5]|left|\nadd_spacer|small|\nadd_textbox|`5Role Checkbox:|left|\nadd_checkbox|role_1|`w[`1VIP`w] ROLE|" + to_string(Role::Vip(cp_)) + "|\nadd_checkbox|role_2|`#@MODERATOR ROLE|" + to_string(Role::Moderator(cp_)) + "|\nadd_checkbox|role_3|`e@ADMINISTRATOR ROLE|" + to_string(Role::Administrator(cp_)) + "|\nadd_checkbox|role_4|`6@DEVELOPER ROLE|" + to_string(Role::Developer(cp_)) + "|\nadd_checkbox|role_9|`9@GOD ROLE|" + to_string(Role::God(cp_)) + "|\nadd_checkbox|role_10|`8@UNLIMITED ROLE|" + to_string(Role::Unlimited(cp_)) + "|\nadd_checkbox|role_5|`b@OWNER SERVER ROLE|" + to_string(Role::Owner(cp_)) + "|\nadd_checkbox|role_6|CHEAT ROLE|" + to_string(Role::Cheater(cp_)) + "|\nadd_checkbox|role_7|`5[BOOST]`` ROLE|" + to_string(pInfo(cp_)->Role.BOOST) + "|\nadd_checkbox|role_8|`8[SUPER-BOOST]`` ROLE|" + to_string(pInfo(cp_)->Role.SUPER_BOOST) + "|\nadd_custom_button|Nevermind|textLabel:`wNevermind;middle_colour:2415764;border_colour:2415764;|\nadd_custom_button|Apply Changes|textLabel:`wApply Changes;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:434431310;border_colour:434438350;|\nend_dialog|give_role|||\nadd_quick_exit|");
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void GASSETS(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gassets <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wGive / Remove - Assets (" + pInfo(cp_)->tankIDName + ")|left|15054|\nadd_spacer|small|\nadd_textbox|`5- Assets Info -``|left|\nadd_smalltext|`o- Gems: `5[`2" + Set_Count(pInfo(cp_)->gems) + "``]|left|\nadd_smalltext|`o- Level: `5[`2" + Set_Count(pInfo(cp_)->level) + "``]|left|\nadd_smalltext|`o- Online Point Currency: `5[`2" + Set_Count(pInfo(cp_)->opc) + "``]|left|\nadd_smalltext|`o- " + Environment()->server_name + " Coins: `5[`2" + Set_Count(pInfo(cp_)->gtwl) + "``]|left|\nadd_smalltext|`o- Supporter: `5[" + (pInfo(cp_)->supp >= 1 ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- Super Supporter: `5[" + (pInfo(cp_)->supp >= 2 ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- GrowPass: `5[" + (pInfo(cp_)->gp ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- Road to Glory: `5[" + (pInfo(cp_)->glo ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- Piggy Bank: `5[" + (pInfo(cp_)->pg_bank ? "`2YES" : "`4NO") + "``]|left|\nadd_spacer|small|\nadd_textbox|`5- Title info -|left|\nadd_smalltext|`o- 'Of Legend': `5[" + (pInfo(cp_)->Title.OfLegend ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Dr.': `5[" + (pInfo(cp_)->Title.Doctor ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Grow4Good Title': `5[" + (pInfo(cp_)->Title.Grow4Good ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Bluename': `5[" + (pInfo(cp_)->level >= 125 ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Blackname': `5[" + (pInfo(cp_)->level >= 250 ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Mentor Title': `5[" + (pInfo(cp_)->Title.Mentor ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Tiktok Creator Badge': `5[" + (pInfo(cp_)->Title.TiktokBadge ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Content Creator Badge': `5[" + (pInfo(cp_)->Title.ContentCBadge ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Party Animal': `5[" + (pInfo(cp_)->Title.PartyAnimal ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'ThanksGiving': `5[" + (pInfo(cp_)->Title.ThanksGiving ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Old Timer': `5[" + (pInfo(cp_)->Title.OldTimer ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Santa Claus': `5[" + (pInfo(cp_)->Title.WinterSanta ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'GrowPass Gold': `5[" + (pInfo(cp_)->Title.GrowPass_Gold ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'GrowPass Silver': `5[" + (pInfo(cp_)->Title.GrowPass_Silver ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'GrowPass Bronze': `5[" + (pInfo(cp_)->Title.GrowPass_Bronze ? "`2YES" : "`4NO") + "``]|left|\nadd_smalltext|`o- 'Award Winning': `5[" + (pInfo(cp_)->Title.Award_Winning ? "`2YES" : "`4NO") + "``]|left|\nadd_spacer|small|\nadd_textbox|`5- Roles Title Info -|left|\nadd_smalltext|'" + (pInfo(cp_)->RolesTitle.Farmer ? "`2FARMER Ă``/" : "`4FARMER ă``/") + (pInfo(cp_)->RolesTitle.Builder ? "`2BUILDER Ă``/" : "`4BUILDER ă``/") + (pInfo(cp_)->RolesTitle.Surgeon ? "`2SURGEON Ă``/" : "`4SURGEON ă``/") + (pInfo(cp_)->RolesTitle.Fisher ? "`2FISHER Ă``/" : "`4FISHER ă``/") + (pInfo(cp_)->RolesTitle.Chef ? "`2CHEF Ă``/" : "`4CHEF ă``/") + (pInfo(cp_)->RolesTitle.Startopian ? "`2STARTOPIAN Ă``/" : "`4STARTOPIAN ă``/") + "'|left|"
					"\nadd_spacer|small|\nadd_textbox|`5Give Assets:|left|\nadd_spacer|small|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|gems|`oGEMS||14590||0||\nadd_checkicon|level|`oLEVEL||1488||0||\nadd_checkicon|coin|`oCOIN||244||0||\nadd_checkicon|opc|`oOPC||10668||0||\nadd_checkicon|token|`oGUILD TOKEN||" + to_string(guild_event_id) + "||0||\nadd_checkicon|seals|`oSEALS||9186||0||\nadd_checkicon|growpass|`oGROWPASS||11304||" + to_string(pInfo(cp_)->gp) + "||\nadd_checkicon|roadtoglory|`oROAD TO GLORY||9436||" + to_string(pInfo(cp_)->glo) + "||\nadd_checkicon|piggybank|`oPIGGY BANK||14588||" + to_string(pInfo(cp_)->pg_bank) + "||" + (pInfo(cp_)->supp == 0 ? "\nadd_checkicon|supp_1|`oSUPPORTER||10860||0||" : pInfo(cp_)->supp == 1 ? "\nadd_checkicon|supp_2|`oSUPER-SUPP||10862||0||" : "\nadd_checkicon|supp_2|`oSUPER-SUPP||10862||1||") + "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`5Give Title:|left|\nadd_spacer|small|\nadd_checkicon|oflegend|`oOf Legend||1794||" + to_string(pInfo(cp_)->Title.OfLegend) + "||\nadd_checkicon|doctor|`oDr.Name||7068||" + to_string(pInfo(cp_)->Title.Doctor) + "||\nadd_checkicon|grow4good|`oGrow4Good||11816||" + to_string(pInfo(cp_)->Title.Grow4Good) + "||\nadd_checkicon|mentor|`oMentor||9472||" + to_string(pInfo(cp_)->Title.Mentor) + "||\nadd_checkicon|tiktok|`oTiktok Badge||9530||" + to_string(pInfo(cp_)->Title.TiktokBadge) + "||\nadd_checkicon|content|`oContent Badge||10866||" + to_string(pInfo(cp_)->Title.ContentCBadge) + "||\nadd_checkicon|partyanimal|`oParty Animal||14186||" + to_string(pInfo(cp_)->Title.PartyAnimal) + "||\nadd_checkicon|tgt|`oThanksGiving||10320||" + to_string(pInfo(cp_)->Title.ThanksGiving) + "||\nadd_checkicon|oldtimer|`oOld Timer||4370||" + to_string(pInfo(cp_)->Title.OldTimer) + "||\nadd_checkicon|santa|`oSanta Claus||1360||" + to_string(pInfo(cp_)->Title.WinterSanta) + "||\nadd_checkicon|gp_bronze|`oGPass Bronze||14412||" + to_string(pInfo(cp_)->Title.GrowPass_Bronze) + "||\nadd_checkicon|gp_silver|`oGPass Silver||14410||" + to_string(pInfo(cp_)->Title.GrowPass_Silver) + "||\nadd_checkicon|gp_gold|`oGPass Golden||14408||" + to_string(pInfo(cp_)->Title.GrowPass_Gold) + "||\nadd_checkicon|aw_win|`oAward Winning||15114||" + to_string(pInfo(cp_)->Title.Award_Winning) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`5Give Roles Title:|left|\nadd_spacer|small|\nadd_checkicon|roles_farmer|`oFarmer||7064||" + to_string(pInfo(cp_)->RolesTitle.Farmer) + "||\nadd_checkicon|roles_builder|`oBuilder||7070||" + to_string(pInfo(cp_)->RolesTitle.Builder) + "||\nadd_checkicon|roles_surgeon|`oSurgeon||7068||" + to_string(pInfo(cp_)->RolesTitle.Surgeon) + "||\nadd_checkicon|roles_fisher|`oFisher||7072||" + to_string(pInfo(cp_)->RolesTitle.Fisher) + "||\nadd_checkicon|roles_chef|`oChef||7076||" + to_string(pInfo(cp_)->RolesTitle.Chef) + "||\nadd_checkicon|roles_startopian|`oStartopian||7074||" + to_string(pInfo(cp_)->RolesTitle.Startopian) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_smalltext|`oNOTE: The column below is only useful for (Gems, Level, Coin, Opc, Guild Token, and Seals).|left|\nadd_text_input|amount|`oAmount:||15|\nadd_spacer|small|\nadd_custom_button|Nevermind|textLabel:`wNevermind;middle_colour:2415764;border_colour:2415764;|\nadd_custom_button|Apply Changes|textLabel:`wApply Changes;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:434431310;border_colour:434438350;|\nend_dialog|give_assets|||\nadd_quick_exit|");
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void GWRENCH(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gwrench <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wGive / Remove - Custom Wrench (" + pInfo(cp_)->tankIDName + ")|left|32|\nadd_spacer|small|\ntext_scaling_string|DEFIBRILLATOR|\nadd_textbox|`$Wrench Style:|left|\nadd_checkicon|prismatic_style|`oPrismatic Style||14360||" + to_string(Has_Claimed::W_Style(peer, 14360)) + "||\nadd_checkicon|shiny_style|`oShiny Style||14492||" + to_string(Has_Claimed::W_Style(peer, 14492)) + "||\nadd_checkicon|wrecked_style|`oWrecked Style||14496||" + to_string(Has_Claimed::W_Style(peer, 14496)) + "||\nadd_checkicon|fresh_style|`oFresh Style||14500||" + to_string(Has_Claimed::W_Style(peer, 14500)) + "||\nadd_checkicon|beautiful_style|`oBeautiful Style||14504||" + to_string(Has_Claimed::W_Style(peer, 14504)) + "||\nadd_checkicon|shocking_style|`oShocking Style||14824||" + to_string(Has_Claimed::W_Style(peer, 14824)) + "||\nadd_checkicon|musical_style|`oMusical Style||14560||" + to_string(Has_Claimed::W_Style(peer, 14560)) + "||\nadd_checkicon|runic_style|`oRunic Style||14714||" + to_string(Has_Claimed::W_Style(peer, 14714)) + "||\nadd_checkicon|mechanical_style|`oMechanical Style||14726||" + to_string(Has_Claimed::W_Style(peer, 14726)) + "||\nadd_checkicon|icy_style|`oIcy Style||15014||" + to_string(Has_Claimed::W_Style(peer, 15014)) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_textbox|`$Wrench Decoration:|left|\nadd_checkicon|prismatic_deco|`oPrismatic Deco||14358||" + to_string(Has_Claimed::W_Deco(peer, 14358)) + "||\nadd_checkicon|shiny_deco|`oShiny Deco||14490||" + to_string(Has_Claimed::W_Deco(peer, 14490)) + "||\nadd_checkicon|wrecked_deco|`oWrecked Deco||14494||" + to_string(Has_Claimed::W_Deco(peer, 14494)) + "||\nadd_checkicon|fresh_deco|`oFresh Deco||14498||" + to_string(Has_Claimed::W_Deco(peer, 14498)) + "||\nadd_checkicon|beautiful_deco|`oBeautiful Deco||14502||" + to_string(Has_Claimed::W_Deco(peer, 14502)) + "||\nadd_checkicon|shocking_deco|`oShocking Deco||14822||" + to_string(Has_Claimed::W_Deco(peer, 14822)) + "||\nadd_checkicon|musical_deco|`oMusical Deco||14558||" + to_string(Has_Claimed::W_Deco(peer, 14558)) + "||\nadd_checkicon|runic_deco|`oRunic Deco||14712||" + to_string(Has_Claimed::W_Deco(peer, 14712)) + "||\nadd_checkicon|mechanical_deco|`oMechanical Deco||14724||" + to_string(Has_Claimed::W_Deco(peer, 14724)) + "||\nadd_checkicon|icy_deco|`oIcy Deco||15012||" + to_string(Has_Claimed::W_Deco(peer, 15012)) + "||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_custom_button|Nevermind|textLabel:`wNevermind;middle_colour:2415764;border_colour:2415764;|\nadd_custom_button|Apply Changes|textLabel:`wApply Changes;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:434431310;border_colour:434438350;|\nend_dialog|give_cwrench|||\nadd_quick_exit|");
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void SETWORLDMENU(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setworldmenu <name world>");
			return;
		}
		std::string name = cmd;
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		if (find(Environment()->World_Menu.begin(), Environment()->World_Menu.end(), name) != Environment()->World_Menu.end()) {
			Environment()->World_Menu.erase(remove(Environment()->World_Menu.begin(), Environment()->World_Menu.end(), name), Environment()->World_Menu.end());
			VarList::OnConsoleMessage(peer, "`o>> Successfully removed " + name + " from world menu list.");
			EventPool::Save::All();
		}
		else {
			Environment()->World_Menu.push_back(name);
			VarList::OnConsoleMessage(peer, "`o>> Successfully added " + name + " to world menu list.");
			EventPool::Save::All();
		}
	}
	static void SPAWN_DROP_GROWCH(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`oUsage: /spawndropgrowch <number 1-11>");
				return;
			}
			int count = std::atoi(cmd.c_str());
			if (count < 1 or count > 11) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Size must between 1-11!", 0, 1);
				return;
			}
			if (not WinterFest.Active or pInfo(peer)->world != "GROWCH") {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, (not WinterFest.Active ? "Can only be used if the Winterfest event is active!" : "Can only be used in world GROWCH!"), 0, 1);
				return;
			}
			if (count == 1) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(2226, 1318, 1538), list.emplace_back(1374, 1256, 1538), list.emplace_back(1380, 1190, 1538), list.emplace_back(7444, 1253, 1474), list.emplace_back(11518, 1193, 1474);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 2) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1358, 1128, 1442), list.emplace_back(2222, 1092, 1378), list.emplace_back(3206, 1155, 1378), list.emplace_back(10522, 1155, 1314);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 3) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1368, 1221, 1282), list.emplace_back(2234, 1221, 1346), list.emplace_back(1370, 1221, 1410), list.emplace_back(7408, 1285, 1378), list.emplace_back(7410, 1285, 1314);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 4) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1392, 1702, 1506), list.emplace_back(1372, 1767, 1506), list.emplace_back(7430, 1828, 1506), list.emplace_back(9198, 1892, 1538);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 5) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1388, 2019, 1506), list.emplace_back(2240, 1960, 1506), list.emplace_back(1362, 1990, 1442), list.emplace_back(7464, 1959, 1378), list.emplace_back(7466, 1892, 1474);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 6) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1382, 1444, 1154), list.emplace_back(1386, 1444, 1218), list.emplace_back(2230, 1444, 1282), list.emplace_back(9200, 1477, 1442);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 7) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1384, 1892, 1346), list.emplace_back(2232, 1892, 1410), list.emplace_back(3256, 1827, 1378), list.emplace_back(7450, 1827, 1442), list.emplace_back(11512, 1766, 1442);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 8) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(2236, 1635, 1122), list.emplace_back(5442, 1705, 1154), list.emplace_back(1378, 1705, 1218), list.emplace_back(5444, 1705, 1282);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 9) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(1376, 1510, 1122), list.emplace_back(2224, 1510, 1185), list.emplace_back(3250, 1510, 1249), list.emplace_back(9174, 1510, 1313), list.emplace_back(11488, 1510, 1377);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 10) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(2218, 1638, 1185), list.emplace_back(5414, 1638, 1249), list.emplace_back(10438, 1638, 1313), list.emplace_back(1390, 1638, 1377);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
			if (count == 11) {
				std::vector<std::tuple<int, int, int>> list;
				list.emplace_back(7416, 1574, 1089), list.emplace_back(7432, 1574, 1153), list.emplace_back(9176, 1574, 1217), list.emplace_back(11466, 1574, 1281), list.emplace_back(12892, 1574, 1345), list.emplace_back(14092, 1574, 1409);
				for (const auto& pos : list) {
					WorldDrop drop_block_{};
					drop_block_.id = std::get<0>(pos), drop_block_.count = 1, drop_block_.x = std::get<1>(pos), drop_block_.y = std::get<2>(pos);
					VisualHandle::Drop(world_, drop_block_);
				}
			}
		}
	}
	static void TRANSFER_BANK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /tfbank <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wTransfer Bank - (" + pInfo(cp_)->tankIDName + ")|left|13808|\nadd_spacer|small|\nadd_textbox|`2Balance User:|left|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->wl_bank_amount) + " World Locks.|size:small;icon:242;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->dl_bank_amount) + " Diamond Locks.|size:small;icon:1796;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->pgl_bank_amount) + " Platinum Gem Locks.|size:small;icon:7188;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->mgl_bank_amount) + " " + Environment()->server_name + " Gem Locks.|size:small;icon:8470;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->igl_bank_amount) + " Infinity Gem Locks.|size:small;icon:13200;|\nadd_spacer|small|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|tf_wl|`oWL||242||0||\nadd_checkicon|tf_dl|`oDL||1796||0||\nadd_checkicon|tf_pgl|`oPGL||7188||0||\nadd_checkicon|tf_mgl|`oMGL||8470||0||\nadd_checkicon|tf_igl|`oIGL||8470||0||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_text_input|amount|Amount:||7|\nadd_spacer|small|\nadd_custom_button|Nevermind|textLabel:`wClose;middle_colour:252135623;border_colour:252135623;|\nadd_custom_button|Confirm_Transfer|textLabel:`wTransfer;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:-15132296;border_colour:-15132296;|\nend_dialog|creator_bank_option|||");
				found = true;
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void REMOVE_BANK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /removebank <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wRemove Balance Bank - (" + pInfo(cp_)->tankIDName + ")|left|13810|\nadd_spacer|small|\nadd_textbox|`2Balance User:|left|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->wl_bank_amount) + " World Locks.|size:small;icon:242;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->dl_bank_amount) + " Diamond Locks.|size:small;icon:1796;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->pgl_bank_amount) + " Platinum Gem Locks.|size:small;icon:7188;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->mgl_bank_amount) + " " + Environment()->server_name + " Gem Locks.|size:small;icon:8470;|\nadd_custom_textbox|`o" + Set_Count(pInfo(cp_)->igl_bank_amount) + " Infinity Gem Locks.|size:small;icon:13200;|\nadd_spacer|small|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|tf_wl|`oWL||242||0||\nadd_checkicon|tf_dl|`oDL||1796||0||\nadd_checkicon|tf_pgl|`oPGL||7188||0||\nadd_checkicon|tf_mgl|`oMGL||8470||0||\nadd_checkicon|tf_igl|`oIGL||13200||0||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_custom_button|Nevermind|textLabel:`wClose;middle_colour:252135623;border_colour:252135623;|\nadd_custom_button|Confirm_Remove|textLabel:`wRemove;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:-15132296;border_colour:-15132296;|\nend_dialog|creator_bank_option|||");
				found = true;
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void ADD_PRICE_BUY(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpbuy <itemid> <price>");
			return;
		}
		std::istringstream ss(cmd);
		int item_id, harga;
		try {
			if (ss >> item_id >> harga) {
				if (item_id < 1 || item_id > items.size()) {
					VarList::OnConsoleMessage(peer, ">> ItemID is not valid!");
					return;
				}
				if (Gtps_Shop::Get_Price(item_id) == 0) Environment()->buy_item_list.push_back(std::make_pair(item_id, item_id));
				Environment()->shop_data[item_id] = harga;
				VarList::OnConsoleMessage(peer, ">> Succes modified `2" + items[item_id].name + " `w(" + to_string(item_id) + ") `oprice to `4" + Set_Count(harga) + " `ogems (gems)");
				Gtps_Shop::Save();
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpbuy <itemid> <price>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /addpbuy <itemid> <price>");
		}
	}
	static void GET_ITEMS(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /getitem <item name>");
			return;
		}
		std::string find_target = to_lower(cmd), item_list_ = "";
		if (find_target.size() < 3) {
			VarList::OnConsoleMessage(peer, "Item name must be more than 2 letters!");
			return;
		}
		for (int i_ = 0; i_ < items.size(); i_++) {
			std::uint32_t item_id = items[i_].id;
			if (pInfo(peer)->tankIDName != "Vallen") {
				if (i_ == 9506) continue;
			}
			if (item_id == 2950 || items[item_id].blockType == SEED || items[item_id].name.find("Data Bedrock") != string::npos || items[item_id].name.find("null_item") != string::npos || items[item_id].name.find("null") != string::npos || items[item_id].name.find("Guild Entrance") != string::npos || items[item_id].name.find("Guild Key") != string::npos || items[item_id].name.find("World Key") != string::npos || item_id == 5640 || item_id == 9158 || item_id == 5814 || item_id == 5816) continue;
			if (to_lower(fixchar2(items[i_].ori_name)).find(find_target) != string::npos) {
				item_list_ += "\nmax_checks|10|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|" + to_string(item_id) + "|" + items[item_id].name + "|frame|" + to_string(item_id) + "||0|\n";
			}
		}
		if (item_list_.empty()) {
			CAction::Log(peer, "action|log\nmsg| `4Oops: `oThere is no item starting with `w" + find_target + "`o.", "");
			return;
		}
		VarList::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wFound item : " + find_target + "``|left|6016|\nadd_spacer|small|\ntext_scaling_string|DEFIBRILLATOR|" + item_list_ + "|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog|Trova Oggetto Clist|Cancel|Add item|\nadd_quick_exit|\n");
	}
	static void EDIT_ITEM(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /edititem <item id>");
			return;
		}
		int id = std::atoi(cmd.c_str());
		if (id == 0 or id < 2 or id > items.size() or items[id].blockType == BlockTypes::CONSUMABLE or items[id].blockType == BlockTypes::LOCK || items[id].blockType == SEED || items[id].name.find("Blank") != string::npos || items[id].name.find("Phoenix") != string::npos || items[id].name.find("Wrench") != string::npos or items[id].name.find("Data Bedrock") != string::npos || items[id].name.find("null_item") != string::npos || items[id].name.find("null") != string::npos || items[id].name.find("Guild Entrance") != string::npos || items[id].name.find("Guild Banner") != string::npos || items[id].name.find("Guild Flag") != string::npos || items[id].name.find("Guild Key") != string::npos || items[id].name.find("World Key") != string::npos || id == 5640 || id == 9158 || id == 5814 || id == 5816 || items[id].actionType == 127 || items[id].actionType == 126 || items[id].actionType == 118 || items[id].actionType == 117 || items[id].actionType == 116 || items[id].actionType == 115 || items[id].actionType == 113 || items[id].actionType == 109 || items[id].actionType == 106 || items[id].actionType == 105 || items[id].actionType == 104 || items[id].actionType == 102 || items[id].actionType == 99 || items[id].actionType == 96 || items[id].actionType == 86 || items[id].actionType == 79 || items[id].actionType == 75 || items[id].actionType == 72 || items[id].actionType == 71 || items[id].actionType == 68 || items[id].actionType == 66 || items[id].actionType == 65 || items[id].actionType == 53 || items[id].actionType == 52 || items[id].actionType == 50 || items[id].actionType == 43 || items[id].actionType == 91 || items[id].id == 5818 || items[id].id == 5820) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "These items cannot be edited!");
			return;
		}
		DialogHandle::EditItemPro(peer, id);
	}
	static void ADD_ITEM_TO_NPC(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /additemtonpc <item id>");
			return;
		}
		int id = std::atoi(cmd.c_str());
		if (id == 0 or id < 2 or id > items.size() or items[id].blockType == BlockTypes::LOCK || items[id].name.find("Blank") != string::npos || items[id].name.find("Wrench") != string::npos or items[id].name.find("Data Bedrock") != string::npos || items[id].name.find("null_item") != string::npos || items[id].name.find("null") != string::npos || items[id].name.find("Guild Entrance") != string::npos || items[id].name.find("Guild Banner") != string::npos || items[id].name.find("Guild Flag") != string::npos || items[id].name.find("Guild Key") != string::npos || items[id].name.find("World Key") != string::npos || id == 5640 || id == 9158 || id == 5814 || id == 5816 || items[id].actionType == 127 || items[id].actionType == 126 || items[id].actionType == 118 || items[id].actionType == 117 || items[id].actionType == 116 || items[id].actionType == 115 || items[id].actionType == 113 || items[id].actionType == 109 || items[id].actionType == 106 || items[id].actionType == 105 || items[id].actionType == 104 || items[id].actionType == 102 || items[id].actionType == 99 || items[id].actionType == 96 || items[id].actionType == 86 || items[id].actionType == 79 || items[id].actionType == 75 || items[id].actionType == 72 || items[id].actionType == 71 || items[id].actionType == 68 || items[id].actionType == 66 || items[id].actionType == 65 || items[id].actionType == 53 || items[id].actionType == 52 || items[id].actionType == 50 || items[id].actionType == 43 || items[id].actionType == 91 || items[id].id == 5818 || items[id].id == 5820) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "These items cannot be added!");
			return;
		}
		bool has_ = false;
		if (Npc_MarketPlace::Has(id)) {
			for (const auto& item : Environment()->Npc_MarketPlace) {
				if (std::get<0>(item) == id) {
					if (Npc_MarketPlace::Remove(id)) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Items has been Removed from Npc!");
					has_ = true;
					break;
				}
			}
		}
		if (not has_) VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wAdd `2" + items[id].name + " ``to [NPC] MarketPlace|left|" + to_string(id) + "|\nembed_data|id|" + to_string(id) + "\nadd_spacer|small|\nmax_checks|1|\ntext_scaling_string|DEFIBRILLATOR|\nadd_smalltext|`oSelect type Price:|left|\nadd_checkicon|wl|WL|noflags|242||0|\nadd_checkicon|dl|DL|noflags|1796||0|\nadd_checkicon|pgl|PGL|noflags|7188||0|\nadd_checkicon|mgl|MGL|noflags|8470||0|\nadd_checkicon|igl|IGL|noflags|13200||0|\nadd_checkicon|gems|GEMS|noflags|14590||0|\nadd_button_with_icon||END_ROW|noflags|0||\nadd_spacer|small|\nadd_smalltext|`oPrice:|left|\nadd_text_input|price|||13|\nadd_spacer|small|\nend_dialog|MarketPlace_Npc|Cancel|Update|\nadd_quick_exit|");
	}
	static void TAKEWORLD(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->owner_name.empty()) return;
			if (world_->guild_id != 0) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "`wYou can't use that commands here.");
				return;
			}
			if (world_->owner_name == pInfo(peer)->tankIDName) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "`wYou already own of this World.");
				return;
			}
			int lock_id = 0, lock_x = -1, lock_y = -1;
			int ySize = (int)world_->blocks.size() / 100, xSize = (int)world_->blocks.size() / ySize;
			for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
				if (items[world_->blocks[i_].fg].blockType == BlockTypes::LOCK) {
					if (world_->blocks[i_].fg == 202 || world_->blocks[i_].fg == 204 || world_->blocks[i_].fg == 206 || world_->blocks[i_].fg == 4994) {
						world_->blocks[i_].owner_name = pInfo(peer)->tankIDName;
					}
				}
			}
			{
				std::vector<WorldBlock>::iterator p = find_if(world_->blocks.begin(), world_->blocks.end(), [&](const WorldBlock& a) { return items[a.fg].blockType == BlockTypes::LOCK && a.fg != 202 && a.fg != 204 && a.fg != 206 && a.fg != 4994 && a.fg != 10000; });
				if (p != world_->blocks.end()) {
					int i_ = p - world_->blocks.begin();
					WorldBlock* block__ = &world_->blocks[p - world_->blocks.begin()];
					std::uint32_t id_ = block__->fg;
					lock_id = id_, lock_x = i_ % xSize, lock_y = i_ / xSize;
				}
			}
			if (lock_id == 0) return;
			std::string before_name = world_->owner_name;
			world_->owner_name = pInfo(peer)->tankIDName;
			if (pInfo(peer)->name_color != "`0" or Role::Moderator(peer) || Role::Administrator(peer) && pInfo(peer)->name_color != "`2")  world_->owner_named = pInfo(peer)->name_color + pInfo(peer)->tankIDName;
			else world_->owner_named = pInfo(peer)->tankIDName;
			pInfo(peer)->worlds_owned.push_back(world_->name);
			PlayerMoving data_{};
			data_.packetType = 15, data_.punchX = lock_x, data_.punchY = lock_y, data_.characterState = 0x8, data_.netID = name_to_number(to_lower(pInfo(peer)->tankIDName)), data_.plantingTree = lock_id;
			BYTE* raw = packPlayerMoving(&data_, 56);
			VisualHandle::Nick(peer, NULL);
			pInfo(peer)->name_color = Role::Prefix2(peer, *world_);
			string t_ = "action|play_sfx\nfile|audio/use_lock.wav\ndelayMS|0";
			BYTE* const d_ = new BYTE[5 + t_.length()];
			*(__int8*)(d_) = 3;
			Memory_Copy(d_ + 4, t_.c_str(), t_.length());
			*(__int8*)(d_ + 4 + t_.length()) = 0;
			ENetPacket* const p_m = enet_packet_create(d_, 5 + t_.length(), ENET_PACKET_FLAG_RELIABLE);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != world_->name) continue;
				pInfo(cp_)->world_owner = (world_->owner_named.empty() ? "`#" + world_->owner_name : world_->owner_named);
				enet_peer_send(cp_, 0, p_m);
				send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
				VarList::OnConsoleMessage(cp_, "`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(peer)->name_color + world_->owner_name + "```5]``");
				VarList::OnTalkBubble(cp_, pInfo(peer)->netID, "`5[```w" + world_->name + "`` has been `$World Locked`` by " + pInfo(peer)->name_color + world_->owner_name + "```5]``", 0, 0);
			}
			delete[]d_;
			delete[] raw;
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " take world : " + world_->name + ".", "Take Worlds");
		}
	}
	static void CLEAR_WORLD(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (not world_->owner_name.empty() and (pInfo(peer)->world == "REC" or pInfo(peer)->world == "PROMOTE" or pInfo(peer)->world == "START" or pInfo(peer)->world == "TRADE" or pInfo(peer)->world == "BFG" or pInfo(peer)->world == "TIPS")) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You can't do it here!");
				return;
			}
			else {
				if (pInfo(peer)->Role.Role_Level >= 5) {
					if (not world_->owner_name.empty() and (pInfo(peer)->world == "REC" or pInfo(peer)->world == "PROMOTE" or pInfo(peer)->world == "START" or pInfo(peer)->world == "TRADE" or pInfo(peer)->world == "BFG" or pInfo(peer)->world == "TIPS")) {
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You can't do it here!");
						return;
					}
					ServerPool::Logs::Add(pInfo(peer)->tankIDName + " clear world [" + pInfo(peer)->world + "]", "Clear World");
					VarList::OnTextOverlay(peer, "Cleared the world");
					world_->fresh_world = true;
					world_->world_settings = 0;
					world_->nuked_by = "";
					world_->admins.clear();
					world_->drop_new.clear();
					world_->sbox1.clear();
					world_->bulletin.clear();
					world_->weather = 0;
					world_->bannedPlayers.clear();
					world_->music_bpm = 100;
					world_->entry_level = 1;
					world_->active_jammers.clear();
					world_->machines.clear();
					for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
						world_->blocks[i_].flags = 0;
						world_->blocks[i_].id = 0;
						if (i_ <= 5400) {
							if (world_->blocks[i_].fg != 0 and world_->blocks[i_].fg != 6 and world_->blocks[i_].fg != 8 and items[world_->blocks[i_].fg].blockType != BlockTypes::LOCK) world_->blocks[i_].fg = 0, world_->blocks[i_].locked = false;
							if (world_->blocks[i_].bg != 0) world_->blocks[i_].bg = 0;
						}
					}
					for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
						if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
						if (pInfo(cp_)->world == pInfo(peer)->world) {
							Exit_World(cp_);
						}
					}
				}
			}
		}
	}
	static void SPAWN_EVENT(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->special_event == false) {
				int event_item = 0;
				vector<int> list = { 263,942,942,1396,4774,4522, 4774, 5002, 121, 1636, 2798, 2704, 3786, 4354 , 4354, 2992, 2992, 10016, 10016, 1396 };
				world_->special_event_item = (WinterFest.Active ? 9186 : list[rand() % list.size()]);
				event_item = world_->special_event_item;
				world_->special_event = true;
				for (ENetPeer* cp__event = server->peers; cp__event < &server->peers[server->peerCount]; ++cp__event) {
					if (cp__event->state != ENET_PEER_STATE_CONNECTED or cp__event->data == NULL or pInfo(cp__event)->world != pInfo(peer)->world) continue;
					VarList::OnConsoleMessage(cp__event, "`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oYou have`` `030`` `oseconds to find and grab the`` `#" + items[world_->special_event_item].name + "```o.``" : "`#" + to_string(items[world_->special_event_item].event_total) + " " + items[world_->special_event_item].name + "`` `ospawn in your world, you have`` `030`` `oseconds to collect them.``") + "");
					VarList::OnAddNotification(cp__event, "`2" + items[world_->special_event_item].event_name + ":`` " + (items[world_->special_event_item].event_total == 1 ? "`oYou have`` `030`` `oseconds to find and grab the`` `#" + items[world_->special_event_item].name + "```o.``" : "`#" + to_string(items[world_->special_event_item].event_total) + " " + items[world_->special_event_item].name + "`` `ospawn in your world, you have`` `030`` `oseconds to collect them.``") + "", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
				}
				world_->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				if (find(Environment()->Another_Worlds.begin(), Environment()->Another_Worlds.end(), world_->name) == Environment()->Another_Worlds.end()) Environment()->Another_Worlds.push_back(world_->name);
				server_event_spawn = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				WorldDrop drop_block_{};
				drop_block_.count = 1;
				for (int i_ = 0; i_ < items[event_item].event_total; i_++) {
					drop_block_.id = event_item == 2034 ? (rand() % 100 < 25 ? 2036 : 2034) : world_->special_event_item, drop_block_.x = rand() % 99 * 32, drop_block_.y = rand() % 54 * 32;
					world_->world_event_items.push_back(drop_block_.id);
					VisualHandle::Drop(world_, drop_block_, true);
				}
			}
		}
	}
	static void VERIFY_CSN(ENetPeer* peer) {
		if (find(Environment()->Verifed_Csn_World.begin(), Environment()->Verifed_Csn_World.end(), pInfo(peer)->world) != Environment()->Verifed_Csn_World.end()) {
			Environment()->Verifed_Csn_World.erase(remove(Environment()->Verifed_Csn_World.begin(), Environment()->Verifed_Csn_World.end(), pInfo(peer)->world), Environment()->Verifed_Csn_World.end());
			EventPool::Save::All();
			VarList::OnConsoleMessage(peer, "`oWorld " + pInfo(peer)->world + " has been removed from verifed casino worlds.");
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "World " + pInfo(peer)->world + " has been removed from verifed casino worlds.", 0, 1);
		}
		else {
			std::string name_ = pInfo(peer)->world;
			auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
			if (it != worlds.end()) {
				World* world_ = &(*it);
				world_->fresh_world = true;
				if (world_->category != "Casino") {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Before verify, owner must set the World Category to ''Casino''!", 0, 1);
					return;
				}
			}
			if (find(Environment()->Waiting_Verif_Csn.begin(), Environment()->Waiting_Verif_Csn.end(), pInfo(peer)->world) != Environment()->Waiting_Verif_Csn.end()) {
				Environment()->Waiting_Verif_Csn.erase(remove(Environment()->Waiting_Verif_Csn.begin(), Environment()->Waiting_Verif_Csn.end(), pInfo(peer)->world), Environment()->Waiting_Verif_Csn.end());
			}
			Environment()->Verifed_Csn_World.push_back(pInfo(peer)->world);
			EventPool::Save::All();
			VarList::OnConsoleMessage(peer, "`oWorld " + pInfo(peer)->world + " has been added to verifed casino worlds.");
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "World " + pInfo(peer)->world + " has been added to verifed casino worlds.", 0, 1);
		}
	}
	static void REMOVE_REQ_VERIFY_CSN(ENetPeer* peer) {
		if (find(Environment()->Waiting_Verif_Csn.begin(), Environment()->Waiting_Verif_Csn.end(), pInfo(peer)->world) != Environment()->Waiting_Verif_Csn.end()) {
			Environment()->Waiting_Verif_Csn.erase(remove(Environment()->Waiting_Verif_Csn.begin(), Environment()->Waiting_Verif_Csn.end(), pInfo(peer)->world), Environment()->Waiting_Verif_Csn.end());
			EventPool::Save::All();
			VarList::OnConsoleMessage(peer, "`oWorld " + pInfo(peer)->world + " has been removed from waiting list request.");
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "World " + pInfo(peer)->world + " has been removed from waiting list request.", 0, 1);
		}
	}
	static void RESET_ROLEQUEST(ENetPeer* peer) {
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->tankIDName.empty()) continue;
			pInfo(cp_)->role_quest = false, pInfo(cp_)->complete_rolequest_day = false;
			pInfo(cp_)->specialization_track = pInfo(cp_)->quest_text;
			pInfo(cp_)->role_quest_type = "", pInfo(cp_)->quest_text = "";
			pInfo(cp_)->total_quest_selected = 0, pInfo(cp_)->quest_required = 0, pInfo(cp_)->need_required = 0, pInfo(cp_)->quest_number = 0, pInfo(cp_)->need_sumbit_req_id = 0, pInfo(cp_)->need_item_req_id = 0;
		}
		VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully Reset all Role Quest!");
	}

	static void DROP_ITEM(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });

		if (it != worlds.end()) {
			World* world_ = &(*it);

			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`oUsage: /drop <id1> <id2> <id3> ... <count>");
				return;
			}

			std::istringstream ss(cmd);
			std::vector<int> itemIds;
			int itemId, quantity;

			// Parsing semua ID-item
			while (ss >> itemId) {
				itemIds.push_back(itemId);
			}

			
			if (itemIds.size() < 2) {
				VarList::OnConsoleMessage(peer, "`oUsage: /drop <id1> <id2> ... <count>");
				return;
			}

			
			quantity = itemIds.back();
			itemIds.pop_back();

		
			if (quantity < 1 || quantity > 5000) {
				VarList::OnConsoleMessage(peer, "`8>> `4Oops: `8Quantity must be between 1 and 5000.");
				return;
			}

			int real_quantity = quantity; 

			for (int id : itemIds) {
				quantity = real_quantity; 

				if (id < 1 || id > items.size()) {
					VarList::OnConsoleMessage(peer, "`8>> `4Oops: `8Invalid item ID.");
					return;
				}

			
				if (items[id].name.find("null_item") != std::string::npos ||
					items[id].name.find("null") != std::string::npos ||
					items[id].name.find("Guild Entrance") != std::string::npos ||
					items[id].name.find("Guild Key") != std::string::npos ||
					items[id].name.find("World Key") != std::string::npos ||
					id == 5640 || id == 9158 || id == 5814 || id == 5816) {
					VarList::OnConsoleMessage(peer, "`8>> `4Oops: `8You can't drop this item.");
					return;
				}

				
				WorldDrop drop_block_{};
				while (quantity > 0) {
					int drop_amount = (quantity >= 200 ? 200 : quantity);

					drop_block_.x = (pInfo(peer)->state == 16
						? pInfo(peer)->x - ((rand() % 12) + 18)
						: pInfo(peer)->x + ((rand() % 12) + 22));
					drop_block_.y = pInfo(peer)->y + rand() % 16;
					drop_block_.id = id;
					drop_block_.count = drop_amount;

					VisualHandle::Drop(world_, drop_block_);
					quantity -= drop_amount;
				}
			}
		}
	}
	static void RESET(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /reset <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				if (not Role::Clist(pInfo(peer)->tankIDName) and Role::Clist(pInfo(cp_)->tankIDName)) {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You can't use this to Creator List!", 0, 0);
					found = true;
					break;
				}
				pInfo(peer)->last_wrenched = pInfo(cp_)->tankIDName;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wReset Panel - (" + pInfo(cp_)->tankIDName + ")|left|32|\nadd_spacer|small|\nadd_smalltext|`7Fast Button:|left|\ntext_scaling_string|DEFIBRILLATOR|\nadd_checkicon|reset_all|`oALL-IN||5494||0||\nadd_smalltext|Include: [Inventory, Gems, Level, Storage<CR>Coin and Cooldown/Playmods]|left|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_checkicon|reset_lock|`oALL LOCKS||242||0||\nadd_smalltext|Include: [All Locks in Inventory and Bank]|left|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_checkicon|reset_inv|`oINVENTORY||9412||0||\nadd_checkicon|reset_gems|`oGEMS||14590||0||\nadd_checkicon|reset_level|`oLEVEL||1488||0||\nadd_checkicon|reset_strgems|`oSTRG GEMS||14592||0||\nadd_checkicon|reset_coin|`oCOIN||244||0||\nadd_checkicon|reset_cooldown|`oCOOLDOWN||3804||0||\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nadd_custom_button|Nevermind|textLabel:`wClose;middle_colour:252135623;border_colour:252135623;|\nadd_custom_button|Confirm_Reset|textLabel:`wReset;anchor:_button_Nevermind;left:1;margin:60,0;middle_colour:-15132296;border_colour:-15132296;|\nend_dialog|reset_option|||");
				found = true;
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void OWNER_SB(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /osb <text>");
			return;
		}
		if (Playmods::HasById(pInfo(peer), 122)) {
			int time_ = 0;
			for (PlayMods peer_playmod : pInfo(peer)->playmods) {
				if (peer_playmod.id == 122) {
					time_ = peer_playmod.time - time(nullptr);
					break;
				}
			}
			VarList::OnConsoleMessage(peer, ">> (" + Time::Playmod(time_) + " before you can broadcast again)");
		}
		else {
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
			Playmods::Add(peer, 122);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `b[OWNER-SB] `5** from (`$" + (get_player_nick(peer)) + "`5) in [`4HIDDEN!`5] ** : `$" + cmd + "``");
			}
		}
	}
	static void UNSAFEEDIT(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`oUsage: /unsafeedit <action> <radius> <item_id");
				return;
			}
			std::istringstream ss(cmd);
			std::string action;
			int radius, item_id;
			if (ss >> action >> radius >> item_id) {
				if (action == "add" || action == "erase" || action == "addobject" || action == "clearobject");
				else {
					VarList::OnConsoleMessage(peer, "`o<action> (add -> add block), (erase -> remove block), (addobject -> drop), (clearobject -> clear drop).");
					return;
				}
				if (radius < 1 or radius > 20) {
					VarList::OnConsoleMessage(peer, "`4Oops``, the given radius must between 1 - 20.");
					return;
				}
				CL_Vec2i devided_position = CL_Vec2i{ pInfo(peer)->x / 32, pInfo(peer)->y / 32 };
				if (item_id > items.size() || items[item_id].name.find("null_item") != string::npos || items.at(item_id).blockType == BlockTypes::SEED || items.at(item_id).blockType == BlockTypes::CLOTHING || items[item_id].blockType == BlockTypes::LOCK || item_id == 8470 || items[item_id].untradeable == 1 || items[item_id].rarity == 999 || items[item_id].block_possible_put == false || items.at(item_id).blockType == BlockTypes::MAIN_DOOR) {
					VarList::OnConsoleMessage(peer, "`4Oops``, couldn't find item with given keyword '`w" + to_string(item_id) + "``', please make sure this is valid item ID.");
					return;
				}
				VarList::OnConsoleMessage(peer, "Terraforming world...");
				UnsafeEdit(peer, world_, action, devided_position, radius, item_id);
			}
		}
	}
	static void WEATHER_WORLD(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`oUsage: /weather <weather id>");
				return;
			}
			int x = std::atoi(cmd.c_str());
			world_->weather = x;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					VarList::OnSetCurrentWeather(cp_, x);
				}
			}
		}
	}
	static void GTOKEN(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gtoken <amount>");
			return;
		}
		int token = std::atoi(cmd.c_str());
		if (guild_event_type == "Spring Clash") pInfo(peer)->spring_token += token;
		if (guild_event_type == "Summer Clash") pInfo(peer)->summer_token += token;
		if (guild_event_type == "Winter Clash") pInfo(peer)->winter_token += token;
		VarList::OnAddNotification(peer, "`wYou received `2" + Set_Count(token) + " `w" + guild_event_type + " Tokens from System!", "interface/token_pve_icon_overlay.rttex", "audio/hub_open.wav");
		ServerPool::SaveDatabase::Players(pInfo(peer), false);
	}
	static void GSEAL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gseal <amount>");
			return;
		}
		int seal = std::atoi(cmd.c_str());
		pInfo(peer)->winter_seal = pInfo(peer)->winter_seal + seal;
		VarList::OnAddNotification(peer, "`wYou received `2" + Set_Count(seal) + " `wWinter Seal from System!", "interface/token_pve_icon_overlay.rttex", "audio/hub_open.wav");
		ServerPool::SaveDatabase::Players(pInfo(peer), false);
	}
	static void IP_CHECK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /ipcheck <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnConsoleMessage(peer, ">> IP CHECK on player " + pInfo(cp_)->name_color + pInfo(cp_)->tankIDName + "`` IP: " + pInfo(cp_)->ip);
				found = true;
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void GGXP(ENetPeer* peer, std::string cmd) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
				VarList::OnConsoleMessage(peer, "`oUsage: /ggxp <amount>");
				return;
			}
			int xp = std::atoi(cmd.c_str());
			std::uint32_t guild_id = world_->guild_id;
			std::vector<Guild>::iterator p = find_if(guilds.begin(), guilds.end(), [guild_id](const Guild& a) { return a.guild_id == guild_id; });
			if (p != guilds.end()) {
				Guild* guild_information = &guilds[p - guilds.begin()];
				guild_information->guild_xp = xp;
				VarList::OnAddNotification(peer, "`wYou received `2" + std::to_string(xp) + " `wGuild Xp from System!", "interface/guild_button.rttex", "audio/hub_open.wav");
			}
		}
	}
	static void REMOVE_LOGS(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /removelogs <player name>");
			return;
		}
		bool foundacc = true;
		std::string username = cmd;
		pInfo(peer)->last_wrenched = username;
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED or currentPeer->data == NULL) continue;
			if (to_lower(username) == to_lower(pInfo(currentPeer)->tankIDName)) {
				foundacc = false;
				pInfo(currentPeer)->bans = {}, pInfo(currentPeer)->Account_Notes = {}, pInfo(currentPeer)->Warning_Message = {};
				VarList::OnConsoleMessage(peer, ">> Removed account logs for user " + Role::Prefix(currentPeer) + pInfo(currentPeer)->tankIDName);
			}
		}
		if (foundacc) {
			bool found = false;
			try {
				std::string name = pInfo(peer)->last_wrenched;
				const string filePath = "database/players/" + name + "_.json";
				if (filesystem::exists(filePath)) {
					found = true;
					ifstream inputFile(filePath);
					json jsonData;
					inputFile >> jsonData;
					jsonData["Account_Notes"] = json::array();
					jsonData["7bans"] = json::array();
					jsonData["Warning_Message"] = json::array();
					inputFile.close();
					ofstream outputFile(filePath);
					outputFile << jsonData << endl;
					outputFile.close();
					VarList::OnConsoleMessage(peer, ">> Removed account logs for user " + name);
				}
			}
			catch (exception) {
				return;
			}
			if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
		}
	}
	static void GGEMS(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /ggems <amount>");
			return;
		}
		int gems = std::atoi(cmd.c_str());
		if (pInfo(peer)->gems >= MAX_GEMS) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Warning! Your gems have reached the maximum limit", 0, 0);
			return;
		}
		VarList::OnBuxGems(peer, gems);
		VarList::OnAddNotification(peer, "`wYou received `2" + std::to_string(gems) + " `wGems from System!", "interface/cash_icon_overlay.rttex", "audio/hub_open.wav");
	}
	static void GLEVEL(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /glevel <amount>");
			return;
		}
		int lvl_ = std::atoi(cmd.c_str());
		if (pInfo(peer)->level + lvl_ > 1000) {
			VarList::OnConsoleMessage(peer, "`oCount level exceeds maximum limit");
			return;
		}
		pInfo(peer)->level += lvl_;
		VarList::OnAddNotification(peer, "`wYou received `2" + std::to_string(lvl_) + " `wLevel from System!", "interface/token_pve_icon_overlay.rttex", "audio/hub_open.wav");
		ServerPool::SaveDatabase::Players(pInfo(peer), false);
	}
	static void SET_MAG(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setmag <amount>");
			return;
		}
		int count = std::atoi(cmd.c_str());
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 5638 or id == 5930) {
					if (world_->blocks[i].id == 0) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::SEED) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::CLOTHING) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::LOCK) continue;
					world_->blocks[i].pr = count;
				}
			}
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " restock magplant in [" + pInfo(peer)->world + "] count [" + to_string(count) + "]", "Restock Magplant");
			VarList::OnConsoleMessage(peer, "all number of items in the magplant has been set to (" + to_string(count) + ")");
		}
	}
	static void SET_MAGSEED(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setmagseed <amount>");
			return;
		}
		int count = std::atoi(cmd.c_str());
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 5638 or id == 5930) {
					if (world_->blocks[i].id == 0) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::SEED) {
						world_->blocks[i].pr = count;
					}
				}
			}
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " restock magplant seed in [" + pInfo(peer)->world + "] count [" + to_string(count) + "]", "Restock Magplant");
			VarList::OnConsoleMessage(peer, "all number of seed in the magplant has been set to (" + to_string(count) + ")");
		}
	}
	static void SET_VEND(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setvend <amount>");
			return;
		}
		int count = std::atoi(cmd.c_str());
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 2978 or id == 9268) {
					if (world_->blocks[i].id == 0) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::SEED) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::LOCK) continue;
					world_->blocks[i].c_ = count;
				}
			}
			ServerPool::Logs::Add(pInfo(peer)->tankIDName + " restock vending in [" + pInfo(peer)->world + "] count [" + to_string(count) + "]", "Restock Vending");
			VarList::OnConsoleMessage(peer, "all number of items in the vending machine has been set to (" + to_string(count) + ")");
		}
	}
	static void FIND_ITEM(ENetPeer* peer) {
		std::string list_ = "";
		for (const auto& item : Environment()->find_item_list) {
			if (pInfo(peer)->tankIDName != "Vallen") if (item.first == 9506) continue;
			if (not Role::Clist(pInfo(peer)->tankIDName)) {
				/*Locks*/if (item.first == 5980 or item.first == 9640 or item.first == 7188 or item.first == 8470 or item.first == 5980 or item.first == 13200) continue;
				/*Mines*/if (item.first == 6994 or item.first == 20220 or item.first == 20222 or item.first == 20224 or item.first == 20226 or item.first == 20228 or item.first == 14528 or item.first == 14530 or item.first == 14532) continue;
				/*Gacha Items*/if (item.first == 10716 || item.first == 14596 || item.first == 5136 || item.first == 14084 || item.first == 9986 || item.first == 10382 || item.first == 1458 || item.first == 7960 || item.first == 9386 || item.first == 9902 || item.first == 9350 || item.first == 10004 || item.first == 9814 || item.first == 9862) continue;
				/*rare*/if (item.first == 5930 || item.first == 9772) continue;
			}
			if (not Role::Owner(peer)) {
				/*items purchase*/if (item.first == 1486 || item.first == 6802 || item.first == 14578 || item.first == 14580 || item.first == 14582 || item.first == 14584 || item.first == 14586 || item.first == 14564 || item.first == 14566 || item.first == 14568 || item.first == 14570 || item.first == 14572 || item.first == 14574 || item.first == 14562 || item.first == 9186 || item.first == 9852 || item.first == 9854 || item.first == 9882 || item.first == 9726 || item.first == 10400 || item.first == 10176 || item.first == 13200 || item.first == 8440 || item.first == 9874 || item.first == 10020 || item.first == 9916 || item.first == 10366 || item.first == 9766 || item.first == 9574 || item.first == 5862 || item.first == 9914 || item.first == 5854 || item.first == 13710 || item.first == 9586 || item.first == 11118 || item.first == 9546 || item.first == 9548 || item.first == 5824 || item.first == 5910 || item.first == 14026 || item.first == 5852 || item.first == 13638 || item.first == 9784 || item.first == 5906 || item.first == 5860 || item.first == 9912 || item.first == 9344 || item.first == 2386 || item.first == 7834 || item.first == 12188 || item.first == 13566 || item.first == 11218 || item.first == 10400 || item.first == 9726 || item.first == 6016 || item.first == 6950 || item.first == 6946 || item.first == 6948 || item.first == 6952 || item.first == 5930 || item.first == 8358 || item.first == 9838 || item.first == 9920 || item.first == 8428 || item.first == 5878 || item.first == 10118 || item.first == 10124 || item.first == 9488 || item.first == 9542 || item.first == 5480 || item.first == 10362 || item.first == 9772 || item.first == 9906 || item.first == 9770 || item.first == 9908 || item.first == 9918 || item.first == 10290 || item.first == 9846 || item.first == 5928 || item.first == 9984 || item.first == 10384 || item.first == 5828) continue;
				/*Item Rare*/if (item.first == 14594 or item.first == 14538 or item.first == 14540 or item.first == 242 or item.first == 1796) continue;
				/*Locks*/if (item.first == 4428 or item.first == 4802 or item.first == 2950 or item.first == 14508 or item.first == 14506 or item.first == 2408 or item.first == 5206) continue;
			}
			if (not Role::Unlimited(peer)) {
				/*Items Daily Quest*/if (item.first == Environment()->Dq_Item1 or item.first == Environment()->Dq_Item2) continue;
				/*All Rings*/if (item.first == 1874 || item.first == 1876 || item.first == 1996 || item.first == 2970 || item.first == 1904 || item.first == 3174 || item.first == 8962 || item.first == 6846 || item.first == 6028 || item.first == 3140) continue;
				if (items[item.first].name.find("Legendary") != string::npos || items[item.first].name.find("Legend") != string::npos || items[item.first].name.find("Phoenix") != string::npos || items[item.first].name.find("Golden") != string::npos || items[item.first].name.find("Subscription") != string::npos || items[item.first].name.find("Growtoken") != string::npos || item.first == 6280) continue;
				if (items[item.first].blockType == FISH) continue;
				if (items[item.first].name.find("Ancestral") != string::npos || items[item.first].name.find("Anomalizing") != string::npos || items[item.first].name.find("Blast") != string::npos || items[item.first].name.find("Supply") != string::npos || items[item.first].name.find("Wand") != string::npos || items[item.first].name.find("Weather Machine") != string::npos || items[item.first].name.find("Storage Box") != string::npos || items[item.first].blockType == FISH || item.first == 14086 || item.first == 11480 || item.first == 11050 || item.first == 9408 || item.first == 8286 || item.first == 8552 || item.first == 11478 || item.first == 10424 || item.first == 7190 || item.first == 4490 || item.first == 5138 || item.first == 5140 || item.first == 5142 || item.first == 9886 || item.first == 408 || item.first == 6240 || item.first == 6246 || item.first == 6252 || item.first == 6258 || item.first == 6830 || item.first == 6836) continue;
				/*Materials Upgrade Ances*/if (items[item.first].name.find("Crystallized") != string::npos || item.first == 5106 || item.first == 5204 || item.first == 5104) continue;
				/*Mag 5k*/if (item.first == 5638) continue;
				/*World Wolf Prize*/if (item.first == 13076 || item.first == 11650 || item.first == 13042 || item.first == 12782 || item.first == 4354 || item.first == 122 || item.first == 124 || item.first == 1188 || item.first == 4346 || item.first == 8544 || item.first == 2996 || item.first == 4342 || item.first == 3136 || item.first == 10082 || item.first == 12486 || item.first == 4352 || item.first == 8262 || item.first == 8264 || item.first == 8266 || item.first == 8268 || item.first == 2998 || item.first == 3538 || item.first == 2986 || item.first == 2984 || item.first == 4348 || item.first == 4350 || item.first == 6842 || item.first == 3774 || item.first == 4344 || item.first == 3176 || item.first == 7146 || item.first == 11338) continue;
				/*Guild Event Reward*/if (items[item.first].name.find("Guild Potion") != string::npos or items[item.first].name.find("Medal:") != string::npos || items[item.first].name.find("Lucky Clover") != string::npos || item.first == 6280 || item.first == 6198 || item.first == 7328 || item.first == 7844 || item.first == 14414 || item.first == 7934 || item.first == 7936 || item.first == 7944 || item.first == 7946 || item.first == 8014 || item.first == 8016 || item.first == 8296 || item.first == 8298 || item.first == 9220 || item.first == 7954 || item.first == 7936 || item.first == 7952 || item.first == 8020 || item.first == 8300 || item.first == 6264 || item.first == 6266 || item.first == 6268 || item.first == 6270 || item.first == 6302 || item.first == 6304 || item.first == 6750 || item.first == 6752 || item.first == 8774 || item.first == 6154 || item.first == 6156 || item.first == 6296 || item.first == 6772 || item.first == 6200 || item.first == 7484 || item.first == 7198 || item.first == 7200 || item.first == 7208 || item.first == 7210 || item.first == 7386 || item.first == 7388 || item.first == 7576 || item.first == 7578 || item.first == 7580 || item.first == 7394 || item.first == 7212 || item.first == 7202) continue;
			}
			list_ += to_string(item.first) + ", " + to_string(item.second) + ", ";
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|Item Finder|left|6016|\nadd_smalltext|`o(name of items to search, try \"Wings\"):|left|\nadd_text_input|item_search_field|`oSearch By Name:||30|\nadd_spacer|small|\nadd_searchable_item_list|" + list_ + "|listType:iconGrid;resultLimit:40;|item_search_field|\nadd_spacer|small|\nend_dialog|Trova Oggetto|Close||");
		pInfo(peer)->Has_In = true;
	}
	static void CLEAR_VEND(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 2978 or id == 9268) {
					if (world_->blocks[i].id == 0) continue;
					world_->blocks[i].c_ = 0;
					world_->blocks[i].id = 0;
				}
			}
			VarList::OnConsoleMessage(peer, "Remove all items from Vending.");
		}
	}
	static void CLEAR_MAG(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 5638 or id == 5930) {
					if (world_->blocks[i].id == 0) continue;
					world_->blocks[i].pr = 0;
					world_->blocks[i].id = 0;
				}
			}
			VarList::OnConsoleMessage(peer, "Remove all items from Magplant.");
		}
	}
	static void CLEAR_MAGSEED(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (int i = 0; i < world_->blocks.size(); i++) {
				int id = world_->blocks[i].fg;
				if (id == 5638 or id == 9850 or id == 10266 or id == 5930) {
					if (world_->blocks[i].id == 0) continue;
					if (items.at(world_->blocks[i].id).blockType == BlockTypes::SEED) {
						world_->blocks[i].pr = 0;
						world_->blocks[i].id = 0;
					}
				}
			}
			VarList::OnConsoleMessage(peer, "Remove all Seeds from Magplant.");
		}
	}
	static void ONLINE_CHECK(ENetPeer* peer) {
		std::string list = "";
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->tankIDName.empty()) continue;
			list += "" + Role::Prefix(cp_) + pInfo(cp_)->tankIDName + ", ";
		}
		int add_amount = 0, total_online = 0, total_pc = 0, total_ios = 0, total_android = 0, TotalPlayer = TotalJson("database/players/");
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			add_amount = 1;
			total_online += add_amount;
			if (pInfo(cp_)->player_device == "0,1,1") total_pc += add_amount;
			else if (pInfo(cp_)->player_device == "1") total_ios += add_amount;
			else total_android += add_amount;
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`$\nadd_label_with_icon|big|`wOnline Players [`2" + Environment()->server_name + "`w]|left|5138|\nadd_textbox|Online: `2" + Set_Count(ServerPool::PlayerCountServer()) + "``/`4" + Set_Count(TotalPlayer) + "``.|left|\nadd_spacer|small|\nadd_label_with_icon|small|Player Device:|left|3802|\nadd_smalltext|PC Users: `2" + to_string(total_pc) + "``.<CR>Android Users: `2" + to_string(total_android) + "``.<CR>IOS Users: `2" + to_string(total_ios) + "``.|left|\nadd_spacer|small|\nadd_smalltext|Uptime: `2" + Time::Playmod(time(nullptr) - Environment()->UpTime) + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Player Name:|left|1280|\nadd_textbox|" + list + "|left|\nadd_spacer|small|\nend_dialog||Close||\nadd_quick_exit|");
	}
	static void SAVE_WORLD(ENetPeer* peer) {
		VarList::OnConsoleMessage(peer, "saved all worlds: " + to_string(worlds.size()) + "!");
		Environment()->Auto_Saving = true;
		for (int i = 0; i < static_cast<int>(worlds.size()); i++) {
			save_world(worlds[i].name, false);
		}
		Environment()->Auto_Saving = false;
		VarList::OnConsoleMessage(peer, "inactive worlds cleared: " + to_string(worlds.size()) + "!");
	}
	static void REMOVE_DROP(ENetPeer* peer) {
		if (pInfo(peer)->world == "GROWCH" and not Role::Clist(pInfo(peer)->tankIDName)) return;
		VarList::OnConsoleMessage(peer, ">> Removed all dropped items.");
		PlayerMoving data_{};
		data_.packetType = 14, data_.netID = 0;
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != pInfo(peer)->world) continue;
				for (int i_ = 0; i_ < world_->drop_new.size(); i_++) {
					data_.plantingTree = world_->drop_new[i_][2];
					BYTE* raw = packPlayerMoving(&data_);
					send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
					delete[]raw;
				}
			}
			world_->drop_new.clear();
		}
	}
	static void RPL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					pInfo(cp_)->last_world = pInfo(cp_)->world;
					for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
						if (world_->blocks[i_].fg == 1000) {
							world_->blocks[i_].fg = 0;
						}
					}
					VarList::OnAddNotification(cp_, "`2Public Lava!: `wis Ended!", "interface/large/special_event.rttex", "audio/pinata_lasso.wav");
					Exit_World(cp_, true);
					Enter_World(cp_, pInfo(cp_)->last_world);
				}
			}
		}
	}
	static void SPL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					pInfo(cp_)->last_world = pInfo(cp_)->world;
					for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
						if (world_->blocks[i_].fg == 0) {
							world_->blocks[i_].fg = 1000;
						}
					}
					VarList::OnAddNotification(cp_, "`2Public Lava!: `wLava is being placed in world `4" + pInfo(peer)->world + "`w, go break it and grab some extra `5Gems!", "interface/large/special_event.rttex", "audio/pinata_lasso.wav");
					Exit_World(cp_, true);
					Enter_World(cp_, pInfo(cp_)->last_world);
				}
			}
		}
	}
	static void GROWALL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			int ySize = world_->blocks.size() / 100, xSize = world_->blocks.size() / ySize;
			for (int f = 0; f < world_->blocks.size(); f++) {
				int xx = f % xSize, yy = f / xSize;
				WorldBlock* block_ = &world_->blocks[f];
				if (items[world_->blocks[f].fg].blockType == PROVIDER || items[world_->blocks[f].fg].blockType == SEED) {
					world_->blocks[f].planted = 0;
				}
			}
			std::string name = pInfo(peer)->world;
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == name) {
					VarList::OnAddNotification(cp_, "`wWarning from `4System``: All Provider and seeds in this world has been Grow!", "interface/atomic_button.rttex", "audio/hub_open.wav");
					pInfo(cp_)->spray_x = pInfo(cp_)->x;
					pInfo(cp_)->spray_y = pInfo(cp_)->y;
					Exit_World(cp_, true);
					pInfo(cp_)->x = pInfo(cp_)->spray_x;
					pInfo(cp_)->y = pInfo(cp_)->spray_y;
					Enter_World(cp_, name, pInfo(cp_)->spray_x / 32, pInfo(cp_)->spray_y / 32);
					pInfo(cp_)->x = pInfo(cp_)->spray_x;
					pInfo(cp_)->y = pInfo(cp_)->spray_y;
					pInfo(cp_)->spray_x = 0;
					pInfo(cp_)->spray_y = 0;
				}
			}
		}
	}
	static void GSM(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gsm <text>");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[S]_ `o**`` `4Global System Message:`` `$" + cmd + "``");
			CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/sungate.wav\ndelayMS|0\n");
		}
	}
	static void BLACKLIST(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gsm <text>");
			return;
		}
		std::string name = cmd;
		std::ifstream ifs("database/players/" + name + "_.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			if (find(Environment()->BlackList.begin(), Environment()->BlackList.end(), j["name"].get<string>()) != Environment()->BlackList.end()) {
				Environment()->BlackList.erase(remove(Environment()->BlackList.begin(), Environment()->BlackList.end(), j["rid"].get<string>()), Environment()->BlackList.end());
				VarList::OnConsoleMessage(peer, "`oSuccesfully un-blacklist >> " + j["name"].get<string>() + " from Server.");
				ServerPool::Logs::Add("player: " + pInfo(peer)->tankIDName + "" + " un-Blacklist (" + " " + j["rid"].get<string>() + " " + ") - " + " " + j["name"].get<string>() + "", "/blacklist");
			}
			else {
				Environment()->BlackList.push_back(j["name"].get<string>());
				VarList::OnConsoleMessage(peer, "`oSuccesfully blacklist >> " + j["name"].get<string>() + " from Server.");
				ServerPool::Logs::Add("player: " + pInfo(peer)->tankIDName + "" + " Blacklist (" + " " + j["rid"].get<string>() + " " + ") - " + " " + j["name"].get<string>() + "", "/blacklist");
				VarList::OnConsoleMessage(peer, "`#**`` `$The Gods `ohave used Blacklist on " + j["name"].get<string>() + "`o from " + Environment()->server_name + " `#**`` (`4/rules`` to see the rules!)", true);
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->tankIDName == j["name"].get<string>()) {
						VarList::OnConsoleMessage(cp_, "`oWarning from `4System``: You've been `4BLACKLIST `ofrom " + Environment()->server_name + "");
						VarList::OnAddNotification(cp_, "`wWarning from `4System``: You've been `4BLACKLIST `wfrom " + Environment()->server_name + "", "interface/atomic_button.rttex", "audio/hub_open.wav");
						VisualHandle::State(pInfo(cp_));
						Clothing_V2::Update(cp_, true);
						Peer_Disconnect(cp_, 0);
					}
				}
			}
		}
	}
	static void SPK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gsm <text>");
			return;
		}
		std::istringstream ss(cmd);
		std::string message, username;
		bool playerFound = false;
		if (ss >> message >> username) {
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (to_lower(pInfo(cp_)->tankIDName) == to_lower(username)) {
					bool msg = false;
					playerFound = true;
					chat_message(cp_, message);
					break;
				}
			}
			if (!playerFound) {
				if (username.length() < 5) VarList::OnConsoleMessage(peer, "`6>> `$" + username + "`` is not online right now (you need to enter at least 5 letters if you meant a longer name!).``");
				else VarList::OnConsoleMessage(peer, "`6>> No one online who has a name starting with `$" + username + "``.``");
			}
		}
	}
	static void ASB(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /gsm <text>");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			VarList::OnConsoleMessage(cp_, cmd);
			VarList::OnAddNotification(cp_, cmd, "interface/atomic_button.rttex", "audio/hub_open.wav");
		}
	}
	static void INFOEX(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /infoex <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				VarList::OnConsoleMessage(peer, "`oTankIDName|" + pInfo(cp_)->tankIDName + "\nrequestedName|" + pInfo(cp_)->requestedName + "\nf|" + pInfo(cp_)->f + "\nprotocol|" + to_string(pInfo(cp_)->protocol) + "\ngame_version|" + pInfo(cp_)->game_version + "\nfz|" + pInfo(cp_)->fz + "\nlmode|" + pInfo(cp_)->lmode + "\ncbits|" + pInfo(cp_)->cbits + "\nplayer_age|" + pInfo(cp_)->player_age + "\nGDPR|" + pInfo(cp_)->GDPR + "\nmeta|" + pInfo(cp_)->meta + "\nfhash|" + pInfo(cp_)->fhash + "\nrid|" + pInfo(cp_)->rid + "\nplatfromID|" + pInfo(cp_)->player_device + "\nDeviceVersion|" + pInfo(cp_)->deviceVersion + "\ncountry|" + pInfo(cp_)->country + "\nhash|" + pInfo(cp_)->hash + "\nmac|" + pInfo(cp_)->mac + "\nwk|" + pInfo(cp_)->wk + "\ngid|" + pInfo(cp_)->gid + "\nzf|" + pInfo(cp_)->zf + "");
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void BANRID(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /banrid <player name>");
			return;
		}
		std::string name = cmd;
		std::ifstream ifs("database/players/" + name + "_.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			if (find(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), j["rid"].get<string>()) != Environment()->Rid_Bans.end()) {
				Environment()->Rid_Bans.erase(remove(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), j["rid"].get<string>()), Environment()->Rid_Bans.end());
				VarList::OnConsoleMessage(peer, "`o>> Unbanned RID " + j["name"].get<string>());
				ServerPool::Logs::Add(pInfo(peer)->tankIDName + " has un-banned rid " + j["name"].get<string>() + ".", "BAN RID");
			}
			else {
				Environment()->Rid_Bans.push_back(j["rid"].get<string>());
				VarList::OnConsoleMessage(peer, "`o>> Banned RID " + j["name"].get<string>());
				ServerPool::Logs::Add(pInfo(peer)->tankIDName + " has banned rid " + j["name"].get<string>() + ".", "BAN RID");
				VarList::OnConsoleMessage(peer, "`#**`` `$The Gods `ohave used `5ban`` on " + j["name"].get<string>() + "`o from " + Environment()->server_name + " `#**`` (`4/rules`` to see the rules!)", true);
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->tankIDName == j["name"].get<string>()) {
						VarList::OnAddNotification(cp_, "`wWarning from `4System`w: You've been `4BANNED RID `wfrom " + Environment()->server_name + "!", "interface/atomic_button.rttex", "audio/hub_open.wav");
						Peer_Disconnect(cp_, 0);
					}
				}
			}
		}
		else VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void BANIP(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /banip <player name>");
			return;
		}
		std::string name = cmd;
		std::ifstream ifs("database/players/" + name + "_.json");
		if (ifs.is_open()) {
			json j;
			ifs >> j;
			if (find(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), j["ip"].get<string>()) != Environment()->Rid_Bans.end()) {
				Environment()->Rid_Bans.erase(remove(Environment()->Rid_Bans.begin(), Environment()->Rid_Bans.end(), j["ip"].get<string>()), Environment()->Rid_Bans.end());
				VarList::OnConsoleMessage(peer, "`o>> Unbanned IP " + j["name"].get<string>());
				ServerPool::Logs::Add(pInfo(peer)->tankIDName + " has un-banned ip " + j["name"].get<string>() + ".", "BAN IP");
			}
			else {
				Environment()->Rid_Bans.push_back(j["ip"].get<string>());
				VarList::OnConsoleMessage(peer, "`o>> Banned IP " + j["name"].get<string>());
				ServerPool::Logs::Add(pInfo(peer)->tankIDName + " has banned ip " + j["name"].get<string>() + ".", "BAN IP");
				VarList::OnConsoleMessage(peer, "`#**`` `$The Gods `ohave used `5ban`` on " + j["name"].get<string>() + "`o from " + Environment()->server_name + " `#**`` (`4/rules`` to see the rules!)", true);
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (pInfo(cp_)->tankIDName == j["name"].get<string>()) {
						VarList::OnAddNotification(cp_, "`wWarning from `4System`w: You've been `4BANNED IP `wfrom " + Environment()->server_name + "!", "interface/atomic_button.rttex", "audio/hub_open.wav");
						Peer_Disconnect(cp_, 0);
					}
				}
			}
		}
		else VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void CHECK_PLAYMODS(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /checkplaymods <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|`wPlaymods of " + pInfo(cp_)->tankIDName + "|\nadd_spacer|small|" + form_mods(pInfo(cp_), 0) + "\nadd_spacer|small|\nend_dialog||Close||");
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void FREEZEALL(ENetPeer* peer) {
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false or pInfo(cp_)->world != pInfo(peer)->world) continue;
			if (not Playmods::HasById(pInfo(cp_), 2) && not Playmods::HasById(pInfo(cp_), 3) && not Playmods::HasById(pInfo(cp_), 49)) {
				Playmods::Add(cp_, 2);
				VisualHandle::State(pInfo(cp_));
				Clothing_V2::Update(cp_, true);
			}
		}
	}
	static void GHOST(ENetPeer* peer) {
		if (pInfo(peer)->world.find("GROWMINES") != std::string::npos or pInfo(peer)->world == "GROWCH" and not Role::Clist(pInfo(peer)->tankIDName)) return;
		CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
		pInfo(peer)->ghost = (pInfo(peer)->ghost ? false : true);
		if (pInfo(peer)->ghost == false) VarList::OnConsoleMessage(peer, "`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
		else VarList::OnConsoleMessage(peer, "`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
		VisualHandle::State(pInfo(peer));
		Clothing_V2::Update(peer);
	}
	static void BANALL(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			std::string t_ = "action|play_sfx\nfile|audio/repair.wav\ndelayMS|0";
			BYTE* const d_ = new BYTE[5 + t_.length()];
			*(__int8*)(d_) = 3;
			Memory_Copy(d_ + 4, t_.c_str(), t_.length());
			*(__int8*)(d_ + 4 + t_.length()) = 0;
			ENetPacket* const p_m = enet_packet_create(d_, 5 + t_.length(), ENET_PACKET_FLAG_RELIABLE);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->tankIDName == pInfo(cp_)->tankIDName or pInfo(peer)->world != pInfo(cp_)->world) continue;
				if (pInfo(peer)->Role.Role_Level <= 4) world_->bannedPlayers.push_back(make_pair(to_lower(pInfo(cp_)->tankIDName), (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
				if (pInfo(peer)->Role.Role_Level <= 4) {
					VarList::OnConsoleMessage(cp_, get_player_nick(peer) + " `4world bans`` " + get_player_nick(cp_) + " from `0" + pInfo(cp_)->world + "``!");
					VarList::OnConsoleMessage(peer, get_player_nick(peer) + " `4world bans`` " + get_player_nick(cp_) + " from `0" + pInfo(cp_)->world + "``!");
					world_->bannedPlayers.push_back(make_pair(to_lower(pInfo(cp_)->tankIDName), (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()));
					enet_peer_send(cp_, 0, p_m);
					Exit_World(cp_);
				}
			}
			delete[]d_;
		}
	}
	static void ONE_HIT(ENetPeer* peer) {
		if (pInfo(peer)->world.find("GROWMINES") != std::string::npos) return;
		pInfo(peer)->hit1 = pInfo(peer)->hit1 ? false : true;
		VarList::OnConsoleMessage(peer, "1HIT " + a + (pInfo(peer)->hit1 == false ? "disabled" : "enabled") + a + ".");
	}
	static void PULLALL(ENetPeer* peer) {
		int pullx = pInfo(peer)->x, pully = pInfo(peer)->y;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or cp_ == peer) continue;
			if (pInfo(peer)->world == pInfo(cp_)->world) {
				if (not pInfo(cp_)->invis) {
					pInfo(cp_)->x = pullx, pInfo(cp_)->y = pully;
					VarList::OnSetPos(cp_, pullx, pully);
					VarList::OnTextOverlay(cp_, "You were pulled by " + pInfo(peer)->tankIDName);
				}
			}
		}
	}
	static void DISABLE_SUMMON(ENetPeer* peer) {
		pInfo(peer)->d_s = (pInfo(peer)->d_s == 0 ? 1 : 0);
		VarList::OnConsoleMessage(peer, "`o>> You " + a + (pInfo(peer)->d_s ? "DISABLE" : "ACTIVE") + " summon from another players.``");
	}
	static void LOGS(ENetPeer* peer) {
		pInfo(peer)->search_page = 20;
		std::string buttons = "";
		for (int i = 0; i < Environment()->Logs.size(); i++) buttons += "\nadd_custom_button|" + Environment()->Logs[i].first + "|textLabel:`w" + Environment()->Logs[i].first + ";middle_colour:75947213;border_colour:75947213;|\nadd_custom_break|\nadd_spacer|small|";
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`w" + Environment()->server_name + " Logs System``|left|3732|\nadd_spacer|small|" + buttons + "|" + (pInfo(peer)->tankIDName == "Vallen" ? "\nadd_spacer|small|\nadd_textbox|Empty All Logs:|left|\nadd_inner_image_label_button|Empty Logs|  `4Empty Logs``|game/tiles_page1.rttex|1.6|16|1|32|" : "") + "|\nend_dialog|logs|Cancel||");
	}
	static void REPORTS(ENetPeer* peer) {
		std::string list = "";
		for (int w_ = 0; w_ < Environment()->World_Report.size(); w_++) list += "\nadd_button|warp_to_" + Environment()->World_Report[w_].first + "|`w#" + to_string(w_ + 1) + " " + Environment()->World_Report[w_].first + "|0|0|\nadd_smalltext|`oREPORT: " + Environment()->World_Report[w_].second + "|left|";
		if (list.empty()) list = "\nadd_textbox|`oNo reports have been received yet.|left|";
		VarList::OnDialogRequest(peer, SetColor(peer) + "\nadd_label_with_icon|big|`wWorld Reports|left||image:game/tiles_page14.rttex;frame:30,23;frameSize:32;|\nadd_spacer|small|" + list + "\nadd_spacer|small|\nend_dialog|top|Close||\nadd_quick_exit|");
	}
	static void PLAYER_REPORT(ENetPeer* peer) {
		std::string list = "";
		for (int w_ = 0; w_ < Environment()->Player_Report.size(); w_++) list += "\nadd_button|info_" + Environment()->Player_Report[w_].first + "|`w#" + to_string(w_ + 1) + " " + Environment()->Player_Report[w_].first + "|0|0|\nadd_smalltext|`oREPORT: " + Environment()->Player_Report[w_].second + "|left|";
		if (list.empty()) list = "\nadd_textbox|`oNo reports have been received yet.|left|";
		VarList::OnDialogRequest(peer, SetColor(peer) + "\nadd_label_with_icon|big|`wPlayer Reports|left||image:game/tiles_page14.rttex;frame:30,23;frameSize:32;|\nadd_spacer|small|" + list + "\nadd_spacer|small|\nend_dialog|punish_view|Close||\nadd_quick_exit|");
	}
	static void UN_CURSEALL(ENetPeer* peer) {
		int uncurse_ = 0;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (Playmods::HasById(pInfo(cp_), 139, 1)) {
				uncurse_++;
			}
		}
		VarList::OnConsoleMessage(peer, "Uncursed people: " + to_string(uncurse_));
	}
	static void COLOR(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /color <number>");
			return;
		}
		int skin = std::atoi(cmd.c_str());
		pInfo(peer)->skin = skin;
		Clothing_V2::Update(peer);
	}
	static void CHECKID(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /checkid <item name>");
			return;
		}
		std::string find_target = cmd, id_list = "";
		if (find_target.size() < 3) {
			VarList::OnConsoleMessage(peer, "Item name must be more than 2 letters!");
			return;
		}
		for (int i_ = 0; i_ < items.size(); i_++) {
			uint32_t item_id = items[i_].id;
			if (item_id == 2950 || item_id == 14576 || items[item_id].blockType == SEED || items[item_id].name.find("null_item") != string::npos || items[item_id].name.find("null") != string::npos || items[item_id].name.find("Guild Flag") != string::npos || items[item_id].name.find("Guild Entrance") != string::npos || items[item_id].name.find("Guild Banner") != string::npos || items[item_id].name.find("Guild Key") != string::npos || items[item_id].name.find("World Key") != string::npos || item_id == 5640 || item_id == 5814 || item_id == 1486 || item_id == 6802 || item_id == 5070 || item_id == 5072 || item_id == 5074 || item_id == 5076 || item_id == 18 || item_id == 32 || item_id == 6336 || item_id == 9384 || item_id == 9158) continue;
			if (to_lower(fixchar2(items[i_].ori_name)).find(find_target) != string::npos) {
				id_list += "\nadd_label_with_icon|small|`o- " + items[item_id].ori_name + " ID : [" + to_string(item_id) + "]|left|" + to_string(item_id) + "|\n";
			}
		}
		if (id_list.empty()) {
			VarList::OnConsoleMessage(peer, " `4Oops: `oThere is no item starting with `w" + find_target + "`o.");
			return;
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wFound item : " + find_target + "``|left|6016|\nadd_spacer|small|\ntext_scaling_string|Subscribtions++++++++|" + id_list + "|\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\nend_dialog||Close||\nadd_quick_exit|\n");
	}
	static void CHANGE_NICK(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			pInfo(peer)->d_name = "";
			VarList::OnConsoleMessage(peer, "Your name changed back to " + pInfo(peer)->tankIDName);
			VisualHandle::Nick(peer, NULL);
			return;
		}
		if (cmd.size() <= 2) {
			VarList::OnConsoleMessage(peer, "Usage: /nick <`$nickname``> - This will change your Display Name.");
			return;
		}
		pInfo(peer)->d_name = cmd;
		VarList::OnConsoleMessage(peer, "Your name changed to " + cmd);
		ServerPool::Logs::Add(pInfo(peer)->tankIDName + " Change Name To -> " + cmd, "Nick");
		if (pInfo(peer)->is_legend) VisualHandle::Nick(peer, NULL);
		else VisualHandle::Nick(peer, NULL);
	}
	static void FAKEBAN(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /fakeban <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnAddNotification(cp_, "`wWarning from `4System`w: You've been `4BANNED from `wGrowtopia for 730 Day", "interface/atomic_button.rttex", "audio/hub_open.wav");
				break;
			}
		}
	}
	static void FAKEWARN(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /fakewarn <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnAddNotification(cp_, "`wWarning from Admin``: you have warned by an `4Admin", "interface/atomic_button.rttex", "audio/hub_open.wav");
				break;
			}
		}
	}
	static void FLAG(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /flag <country>");
			return;
		}
		std::string flag = cmd;
		pInfo(peer)->country = flag;
		gamepacket_t p(0, pInfo(peer)->netID);
		p.Insert("OnCountryState");
		p.Insert(flag);
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) p.CreatePacket(cp_);
		}
	}
	static void SCANNING(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /scan <itemid>");
			return;
		}
		std::string console[8];
		int id = std::atoi(cmd.c_str()), shelfs = 0, sbox_count = 0, drop_count = 0, d_count = 0, p_count = 0, v_count = 0, db_count = 0, ds_count = 0, b_count = 0;
		if (id < 0 or id > items.size()) return;
		for (int i = 0; i < worlds.size(); i++) {
			for (int c = 0; c < worlds[i].sbox1.size(); c++) {
				if (worlds[i].sbox1[c].id == id && worlds[i].sbox1[c].count > 0) {
					sbox_count++;
					console[0] += "`5#" + to_string(sbox_count) + ": `oin [`9" + worlds[i].name + "``] >> (`$S-BOX: `2" + to_string(worlds[i].sbox1[c].count) + " " + items[id].name + "``), ";
				}
			}
			for (int j = 0; j < worlds[i].drop_new.size(); j++) {
				if (worlds[i].drop_new[j][0] == id && worlds[i].drop_new[j][1] > 0) {
					drop_count++;
					console[1] += "`5#" + to_string(drop_count) + ": `oin [`9" + worlds[i].name + "``] >> (`$DROP: `2" + to_string(worlds[i].drop_new[j][1]) + " " + items[id].name + "``), ";
				}
			}
			for (int w = 0; w < worlds[i].blocks.size(); w++) {
				for (int z = 0; z < worlds[i].blocks[w].donates.size(); z++) {
					if (worlds[i].blocks[w].donates[z].item == id && worlds[i].blocks[w].donates[z].count > 0) {
						d_count++;
						console[2] += "`5#" + to_string(d_count) + ": `oin [`9" + worlds[i].name + "``] >> (`$D-BOX: `2" + to_string(worlds[i].blocks[w].donates[z].count) + " " + items[id].name + "``), ";
					}
				}
				if (items[worlds[i].blocks[w].fg].blockType == BlockTypes::VENDING) {
					if (worlds[i].blocks[w].id == id && worlds[i].blocks[w].c_ != 0) {
						v_count++;
						console[3] += "`5#" + to_string(v_count) + ": `oin [`9" + worlds[i].name + "``] >> (`$VEND: `2" + to_string(worlds[i].blocks[w].c_) + " " + items[id].name + "``), ";
					}
					if (worlds[i].blocks[w].id == id && id == 242) {
						v_count++;
						console[3] += "`5#" + to_string(v_count) + ": `oin [`9" + worlds[i].name + "``] >> (`$VEND: `2" + to_string(worlds[i].blocks[w].pr) + " " + items[id].name + "``), ";
					}
				}
			}
		}
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|Scanning in All World|left|6016|\nadd_spacer|small|\nadd_textbox|`oScanning items:|left|\nadd_smalltext|`o" + items[id].name + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Storage Box|left|6286|\nadd_smalltext|`o" + (sbox_count != 0 ? console[0] : "Performance cleared.") + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Donation Box|left|1452|\nadd_smalltext|`o" + (d_count != 0 ? console[2] : "`oPerformance cleared.") + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Vending|left|2978|\nadd_smalltext|`o" + (v_count != 0 ? console[3] : "`oPerformance cleared.") + "|left|\nadd_spacer|small|\nadd_label_with_icon|small|Dropped|left|18|\nadd_smalltext|`o" + (drop_count != 0 ? console[1] : "`oPerformance cleared.") + "|left|\nadd_spacer|small|\nadd_smalltext|`2>> Every worlds database successfully scanned!|left|\nadd_spacer|small|\nend_dialog||Close||\nadd_quick_exit|");
	}
	static void CHECK_PING(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /checkping <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				VarList::OnConsoleMessage(peer, "`o>> " + pInfo(cp_)->tankIDName + " Ping : " + to_string(cp_->roundTripTime) + "Ms");
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Player Not Found", 0, 1);
	}
	static void DR_DESTRUCTO(ENetPeer* peer) {
		pInfo(peer)->DrDes = true;
		pInfo(peer)->d_name = "`4Dr. Destructo";
		pInfo(peer)->country = "none";
		pInfo(peer)->face = 576, pInfo(peer)->shirt = 466, pInfo(peer)->pants = 468, pInfo(peer)->hair = 0, pInfo(peer)->necklace = 0, pInfo(peer)->back = 0, pInfo(peer)->feet = 42, pInfo(peer)->hand = 1010;
		pInfo(peer)->punched = 8;
		pInfo(peer)->ghost = true;
		VisualHandle::State(pInfo(peer));
		Clothing_V2::Update_Value(peer);
		Clothing_V2::Update(peer);
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == world_->name) {
					gamepacket_t p(0, pInfo(peer)->netID);
					p.Insert("OnCountryState");
					p.Insert(pInfo(peer)->country);
					p.CreatePacket(cp_);
					VarList::OnConsoleMessage(cp_, "`4Dr. Destructo `2Attacks!:`o Defeat `4Dr. Destructo`o!``");
					VarList::OnAddNotification(cp_, "`4Dr. Destructo `2Attacks!:`o Defeat `4Dr. Destructo`o!``", "interface/large/special_event.rttex", "audio/cumbia_horns.wav");
					CAction::Positioned(cp_, pInfo(cp_)->netID, "action|play_music\nfile|audio/fight_loop.wav", 0);
					std::string names = "`4Dr. Destructo";
					gamepacket_t p2(0, pInfo(peer)->netID);
					p2.Insert("OnNameChanged");
					p2.Insert(names);
					p2.Insert(get_player_custom_wrench(peer));
					p2.CreatePacket(cp_);
				}
				world_->special_event = true;
				world_->special_event_name = "Dr. Destructo";
				world_->last_special_event = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				if (find(Environment()->Another_Worlds.begin(), Environment()->Another_Worlds.end(), world_->name) == Environment()->Another_Worlds.end()) Environment()->Another_Worlds.push_back(world_->name);
			}
		}
	}
	static void FIX_WORLD(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			VarList::OnConsoleMessage(peer, ">> Fixed the world.");
			ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "`8fixed world``: `#" + pInfo(peer)->world, "");
			send_fix_world(world_);
		}
	}
	static void BANWORLD(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (world_->nuked_by.empty()) {
				struct tm newtime;
				time_t now = time(0);
#ifdef _WIN32
				localtime_s(&newtime, &now);
#elif defined(__linux__)
				localtime_r(&now, &newtime);
#endif
				world_->nuked_by = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``, " + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/" + to_string(1900 + newtime.tm_year) + " " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
				VarList::OnTextOverlay(peer, "The following world as been nuked: " + pInfo(peer)->world + "!");
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					VarList::OnConsoleMessage(cp_, "`o>> `4" + world_->name + " `4was nuked from orbit`o. It's the only way to be sure. Play nice, everybody!");
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/bigboom.wav", 0);
					if (pInfo(cp_)->world == world_->name) {
						if (pInfo(peer)->Role.Role_Level <= 3) {
							VarList::OnConsoleMessage(cp_, pInfo(peer)->name_color + pInfo(peer)->tankIDName + " `4world bans " + "`o" + pInfo(cp_)->tankIDName + " from `w" + world_->name + "`o!");
							VarList::OnAddNotification(cp_, "`wWarning from `4System`w: This world has been nuked.", "interface/atomic_button.rttex", "audio/hub_open.wav");
							Exit_World(cp_);
						}
					}
				}
				for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
					if (world_->blocks[i_].fg == 202 || world_->blocks[i_].fg == 204 || world_->blocks[i_].fg == 206 || world_->blocks[i_].fg == 4994 || world_->blocks[i_].fg == 10000 || world_->blocks[i_].fg == 5814) continue;
					if (items[world_->blocks[i_].fg].blockType == BlockTypes::LOCK) {
						world_->last_lock = world_->blocks[i_].fg;
						world_->blocks[i_].fg = 2950, update_tile(peer, i_ % 100, i_ / 100, 2950, false, true);
					}
				}
				ServerPool::Logs::Add(pInfo(peer)->name_color + pInfo(peer)->tankIDName + " (/banworld) NUKED WORLD: `#" + pInfo(peer)->world, "NUKED WORLD");
				ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "NUKED WORLD: `#" + pInfo(peer)->world, "");
			}
			else {
				for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
					if (world_->blocks[i_].fg == 202 || world_->blocks[i_].fg == 204 || world_->blocks[i_].fg == 206 || world_->blocks[i_].fg == 4994 || world_->blocks[i_].fg == 10000 || world_->blocks[i_].fg == 5814) continue;
					if (items[world_->blocks[i_].fg].blockType == BlockTypes::LOCK) {
						if (world_->blocks[i_].fg == 2950)
							world_->blocks[i_].fg = world_->last_lock, update_tile(peer, i_ % 100, i_ / 100, world_->last_lock, false, true);
					}
				}
				world_->last_lock = 0;
				world_->nuked_by = "";
				VarList::OnConsoleMessage(peer, "This world is once again available to everyone!");
				VarList::OnTextOverlay(peer, "You unnuked the world " + pInfo(peer)->world + "..");
				CAction::Positioned(peer, pInfo(peer)->netID, "audio/secret.wav", 0);
				ServerPool::Logs::Add(pInfo(peer)->name_color + pInfo(peer)->tankIDName + " (/banworld) UNNUKED WORLD: `#" + pInfo(peer)->world, "NUKED WORLD");
				ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "UNNUKED WORLD: `#" + pInfo(peer)->world, "");
			}
		}
	}
	static void HIDE(ENetPeer* peer) {
		pInfo(peer)->m_h = (pInfo(peer)->m_h == 0 ? 1 : 0);
		VarList::OnConsoleMessage(peer, "`o>> You " + a + (pInfo(peer)->m_h ? "hide" : "un-hide") + " yourself from everyone (You `" + (pInfo(peer)->m_h ? "4won't" : "2will") + "`` be visible in /mods, /msg etc.)``");
	}
	static void RADIO2(ENetPeer* peer) {
		pInfo(peer)->radio2 = (pInfo(peer)->radio2 == 0 ? 1 : 0);
		VarList::OnConsoleMessage(peer, "Radio2 " + a + (pInfo(peer)->radio2 ? "disabled, `4you now won't" : "Radio enabled, `2you can now") + a + " see`` public broadcasts.");
	}
	static void TOGGLEMODS(ENetPeer* peer) {
		if (pInfo(peer)->tmod == 1) pInfo(peer)->tmod = 0;
		else pInfo(peer)->tmod = 1;
		VarList::OnConsoleMessage(peer, (pInfo(peer)->tmod ? "`o>> You removed your mod tag.``" : "`o>> You added your mod tag back.``"));
		VisualHandle::Nick(peer, NULL);
	}
	static void SKIN(ENetPeer* peer) {
		VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label_with_icon|big|`wSkin Color``|left|5468|\nadd_spacer|small|\nadd_text_input|color|Color - R,G,B:|" + pInfo(peer)->skin_c + "|11|\nadd_spacer|small|\nadd_button|restore_default|Restore to Default|noflags|0|0|\nend_dialog|skin_color|Close|Update|\nadd_quick_exit|");
	}
	static void INVIS(ENetPeer* peer) {
		vector<int> random_{ 32, 64, -32, -64, 0, 0 };
		PlayerMoving data_{};
		data_.packetType = 17, data_.netID = 105, data_.YSpeed = 105;
		BYTE* raw = packPlayerMoving(&data_);
		CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
		if (pInfo(peer)->invis) {
			pInfo(peer)->invis = false;
			VarList::OnConsoleMessage(peer, "`oYou are once again visible to mortals.");
			gamepacket_t p(750, pInfo(peer)->netID);
			p.Insert("OnInvis");
			p.Insert(0);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/magic.wav", 0);
					for (int i = 0; i < 14; i++) {
						if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
						if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
						if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
						if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
						if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 16, 3, i * 300);
						if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 16, 3, i * 300);
						if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 16, 3, i * 300);
						raw = packPlayerMoving(&data_);
						send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
					}
					delete[] raw;
					p.CreatePacket(cp_);
				}
			}
			Clothing_V2::Update_Value(peer);
			Clothing_V2::Update(peer);
		}
		else {
			pInfo(peer)->invis = true;
			VarList::OnConsoleMessage(peer, "`oYou are now ninja, invisible at all.");
			gamepacket_t p(750, pInfo(peer)->netID);
			p.Insert("OnInvis");
			p.Insert(1);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					for (int i = 0; i < 6; i++) {
						raw = packPlayerMoving(&data_);
						send_raw(cp_, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
					}
					delete[] raw;
					CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/already_used.wav\ndelayMS|750");
					p.CreatePacket(cp_);
				}
			}
			Clothing_V2::Update_Value(peer);
			Clothing_V2::Update(peer);
		}
	}
	static void MAGIC(ENetPeer* peer) {
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/magic.wav", 0);
				for (int i = 0; i < 14; i++) {
					if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
					if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
					if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
					if (rand() % 100 <= 75) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 6 + 1, 2, i * 300);
					if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 16, 3, i * 300);
					if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y - 15 * (rand() % 6), rand() % 16, 3, i * 300);
					if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x + 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 16, 3, i * 300);
					if (rand() % 100 <= 25) VarList::OnParticleEffect(cp_, pInfo(peer)->x - 15 * (rand() % 6), pInfo(peer)->y + 15 * (rand() % 6), rand() % 16, 3, i * 300);
				}
			}
		}
	}
	static void NOHANDS(ENetPeer* peer) {
		pInfo(peer)->no_hands = (pInfo(peer)->no_hands ? false : true);
		Clothing_V2::Update_Value(peer);
		Clothing_V2::Update(peer);
	}
	static void NOBODY(ENetPeer* peer) {
		pInfo(peer)->no_body = (pInfo(peer)->no_body ? false : true);
		Clothing_V2::Update_Value(peer);
		Clothing_V2::Update(peer);
	}
	static void UNEQUIP(ENetPeer* peer) {
		if (pInfo(peer)->hair != 0) Clothing::UnEquip(peer, pInfo(peer)->hair);
		if (pInfo(peer)->shirt != 0) Clothing::UnEquip(peer, pInfo(peer)->shirt);
		if (pInfo(peer)->pants != 0) Clothing::UnEquip(peer, pInfo(peer)->pants);
		if (pInfo(peer)->feet != 0) Clothing::UnEquip(peer, pInfo(peer)->feet);
		if (pInfo(peer)->face != 0) Clothing::UnEquip(peer, pInfo(peer)->face);
		if (pInfo(peer)->hand != 0) Clothing::UnEquip(peer, pInfo(peer)->hand);
		if (pInfo(peer)->back != 0) Clothing::UnEquip(peer, pInfo(peer)->back);
		if (pInfo(peer)->mask != 0) Clothing::UnEquip(peer, pInfo(peer)->mask);
		if (pInfo(peer)->necklace != 0) Clothing::UnEquip(peer, pInfo(peer)->necklace);
		if (pInfo(peer)->ances != 0) Clothing::UnEquip(peer, pInfo(peer)->ances);
	}
	static void setworldblock(ENetPeer* peer, std::string cmd) {
		int old_id = -1, new_id = -1;

		if (sscanf(cmd.c_str(), "%d %d", &old_id, &new_id) != 2) {
			VarList::OnConsoleMessage(peer, "`oUsage: /setworldblock <old_id> <new_id>");
			return;
		}

		if (old_id < 0 || old_id >= items.size() || new_id < 0 || new_id >= items.size()) {
			VarList::OnConsoleMessage(peer, "`4Invalid item ID(s). Please check again.");
			return;
		}

		Player* player = (Player*)peer->data;
		if (!player) return;

		std::string world_name = player->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [world_name](const World& w) {
			return w.name == world_name;
			});

		if (it == worlds.end()) return;
		World* world = &(*it);

		bool replaced_fg = false, replaced_bg = false;
		for (auto& block : world->blocks) {
			if (block.fg == old_id) {
				block.fg = new_id;
				replaced_fg = true;
			}
			if (block.bg == old_id) {
				block.bg = new_id;
				replaced_bg = true;
			}
		}

		std::string from_name = items[old_id].name;
		std::string to_name = items[new_id].name;
		std::string notif;

		if (replaced_fg && replaced_bg)
			notif = "`4Replaced `" + from_name + "` with `" + to_name + "` in FG and BG.";
		else if (replaced_fg)
			notif = "`4Replaced FG `" + from_name + "` with `" + to_name + "`.";
		else if (replaced_bg)
			notif = "`4Replaced BG `" + from_name + "` with `" + to_name + "`.";
		else
			notif = "`4No blocks with ID `" + std::to_string(old_id) + "` found in FG or BG.";

		for (ENetPeer* cp = server->peers; cp < &server->peers[server->peerCount]; ++cp) {
			if (!cp || cp->state != ENET_PEER_STATE_CONNECTED) continue;

			Player* other = (Player*)cp->data;
			if (!other || other->world != world_name) continue;

			other->last_world = world_name;
			VarList::OnConsoleMessage(cp, notif);
			VarList::OnAddNotification(cp, "", "interface/large/special_event.rttex", "audio/pinata_lasso.wav");

			Exit_World(cp, true); // true biar forced exit
			Enter_World(cp, other->last_world);
		}
	}
	/*static void WORLDGEN_DIALOG(ENetPeer* peer, std::string param) {
		if (!Role::Clist(pInfo(peer)->tankIDName)) return;

		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|``bWORLD GENERATOR|left|6016|\n"
			"add_spacer|small|\n"
			"add_textbox|``wAtur ukuran world custom (min 30x30, max 255x255)|left|\n"
			"add_custom_margin|x:40;y:0|\n"
			"add_text_input|width_input|``bWidth (lebar)|280|\n"
			"add_text_input|height_input|``bHeight (tinggi)|280|\n"
			"add_spacer|small|\n"
			"add_button|generate_world|`2Generate World|\n"
			"end_dialog|worldgen_dialog|Cancel||\n"
			"add_quick_exit|";

		VarList::OnDialogRequest(peer, dialog);
	}*/
	static void AUTOANJIR(ENetPeer* peer, std::string cmd) {
		Player* player = pInfo(peer);
		if (!player) return;

		auto it = std::find_if(worlds.begin(), worlds.end(), [player](const World& w) {
			return w.name == player->world;
			});
		if (it == worlds.end()) return;

		World* world = &(*it);
		int seed_id = 3;
		int amount = 0;

		for (auto& item : player->inv) {
			if (item.first == seed_id) {
				amount = item.second;
				break;
			}
		}

		if (amount <= 0) {
			VarList::OnConsoleMessage(peer, "`4Kamu tidak punya seed.");
			return;
		}

		int planted = 0;
		for (int y = 0; y < world->max_y; ++y) {
			for (int x = 0; x < world->max_x; ++x) {
				if (planted >= amount) break;

				int index = x + y * world->max_x;
				WorldBlock* block = &world->blocks[index];

				if (block->fg == 0 && block->bg == 0) {
					block->fg = seed_id;
					block->planted = std::time(nullptr);
					planted++;

					// Broadcast efek tanam
					PlayerMoving move{};
					move.packetType = 14;
					move.netID = -1;
					move.plantingTree = seed_id;
					move.x = x;
					move.y = y;

					BYTE* raw = packPlayerMoving(&move);
					*(int*)(raw + 8) = 0;
					*(float*)(raw + 16) = 1.0f;

					for (ENetPeer* cp = server->peers; cp < &server->peers[server->peerCount]; ++cp) {
						if (!cp || cp->state != ENET_PEER_STATE_CONNECTED || !cp->data) continue;
						if (pInfo(cp)->world != world->name) continue;

						send_raw(cp, 4, raw, 56, ENET_PACKET_FLAG_RELIABLE);
						SendTileUpdate(cp, x, y, seed_id, 0); // Tile langsung muncul
					}
					delete[] raw;
				}
			}
		}

		if (planted > 0) {
			int vallen = -planted;
			Inventory::Modify(peer, seed_id, vallen);
			VarList::OnConsoleMessage(peer, "`2Berhasil menanam " + std::to_string(planted) + " seed(s).");
		}
		else {
			VarList::OnConsoleMessage(peer, "`6Semua tile udah kepenuhan, bro.");
		}
	}
	static void GIVEAWAYROLE(ENetPeer* peer, std::string param) {
		if (!Role::Clist(pInfo(peer)->tankIDName)) return;

		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wGIVEAWAY ROLE|left|15042|\n"
			"add_spacer|small|\n"
			"add_textbox|`0Pilih role yang ingin kamu giveaway ke player online secara acak!|left|\n"
			"add_spacer|small|\n"
			"add_checkbox|give_vip|`1Giveaway VIP|0|\n"
			"add_checkbox|give_mod|`2Giveaway Moderator|0|\n"
			"add_checkbox|give_admin|`3Giveaway Administrator|0|\n"
			"add_checkbox|give_dev|`4Giveaway Developer|0|\n"
			"add_checkbox|give_god|`5Giveaway God|0|\n"
			"add_checkbox|give_unli|`9Giveaway Unlimited|0|\n"
			"add_checkbox|give_boost|`6Giveaway BOOST|0|\n"
			"add_checkbox|give_sboost|`8Giveaway SUPER BOOST|0|\n"
			"add_spacer|small|\n"
			"add_button|apply_giveaway|Apply Giveaway|\n"
			"end_dialog|giveaway_role_dialog|Cancel||\n"
			"add_quick_exit|";

		VarList::OnDialogRequest(peer, dialog);
	}
	static void AUTOHARVEST(ENetPeer* peer) {
		VarList::OnDialogRequest(peer,
			SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wAuto Harvest``|left|1444|\n"
			"add_spacer|small|\n"
			"add_textbox|`0Apakah kamu yakin ingin harvest semua seed yang sudah siap?\n"
			"end_dialog|autoharvest|Batal|GASS BANG|\n"
		);
	}
	static void SHOWDT(ENetPeer* peer) {
		std::string dialog = SetColor(peer) +
			"set_default_color|`o\n"
			"add_label_with_icon|big|`wBlokir Drop/Trash Item``|left|6014|\n"
			"add_textbox|`6Masukkan ID item untuk diblokir atau dibuka blokirnya.|left|\n"
			"add_text_input|item_id_input|`oItem ID:||5|\n"
			"add_button|block_item|Blokir|noflags|\n"
			"add_button|unblock_item|Buka Blokir|noflags|\n";

		// Tampilkan daftar item yang diblokir dari blockdroptrash.json
		std::ifstream in("blockdroptrash.json");
		nlohmann::json data = nlohmann::json::array();
		if (in.good()) in >> data;
		in.close();

		if (!data.empty()) {
			dialog += "add_spacer|small|\nadd_textbox|`wItem yang diblokir:|left|\n";
			for (int id : data) {
				dialog += "add_textbox|`4- ID: `w" + std::to_string(id) + "|\n";
			}
		}
		else {
			dialog += "add_textbox|`2Belum ada item yang diblokir.|left|\n";
		}

		dialog += "add_quick_exit|\nend_dialog|blockdt_dialog|Cancel||\n";

		VarList::OnDialogRequest(peer, dialog);
	}
	static void TRASHALLMEK(ENetPeer* peer) {
		std::string dialog = SetColor(peer);
		dialog += "set_default_color|`o\n";
		dialog += "add_label_with_icon|big|`4Trash X Drop Items``|left|2480|\n";
		dialog += "add_spacer|small|\n";
		dialog += "add_textbox|`4Warning:`` Selected items will be permanently deleted or dropped!|left|\n";
		dialog += "add_spacer|small|\n";

		for (int i = 0; i < pInfo(peer)->inv.size(); i++) {
			if (pInfo(peer)->inv[i].first == 0 || items[pInfo(peer)->inv[i].first].untradeable) continue;
			dialog += "add_checkicon|trash_item_" + std::to_string(pInfo(peer)->inv[i].first) + "|" +
				items[pInfo(peer)->inv[i].first].ori_name + "`` (`w" + std::to_string(pInfo(peer)->inv[i].second) + "``)||" +
				std::to_string(pInfo(peer)->inv[i].first) + "||0|\n";
		}

		dialog += "\nadd_button_with_icon||END_LIST|noflags|0||\nadd_spacer|small|\n";
		dialog += "add_button|trash_confirm|`4Delete Selected Items``|noflags|0|0|\n";
		dialog += "add_button|drop_confirm|`2Drop Selected Items``|noflags|0|0|\n";
		dialog += "end_dialog|trash_dialog|Cancel||\n";
		dialog += "add_quick_exit|\n";

		VarList::OnDialogRequest(peer, dialog);
	}
	static void NO_CLIP(ENetPeer* peer) {
		std::string name_ = pInfo(peer)->world;
		auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
		if (it != worlds.end()) {
			World* world_ = &(*it);
			if (to_lower(world_->owner_name) != to_lower(pInfo(peer)->tankIDName)) {
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "can only be used in your owned worlds!", 0, 0);
				return;
			}
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
			pInfo(peer)->no_clip = (pInfo(peer)->no_clip ? false : true);
			pInfo(peer)->ghost = (pInfo(peer)->ghost ? false : true);
			if (pInfo(peer)->ghost == false) VarList::OnConsoleMessage(peer, "`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
			else VarList::OnConsoleMessage(peer, "`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
			VisualHandle::State(pInfo(peer));
			Clothing_V2::Update(peer);
		}
	}
	static void SUMMON(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /summon <player name>");
			return;
		}
		if (Playmods::HasById(pInfo(peer), 139)) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, you can't do that while cursed.", 0, 0);
			return;
		}
		bool found_ = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->invis or pInfo(cp_)->hider or pInfo(cp_)->seeker) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				if (Playmods::HasById(pInfo(cp_), 139)) {
					found_ = true;
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, this person is in HELL right now.", 0, 0);
				}
				else if (not Role::Administrator(peer) and Role::Administrator(cp_)) {
					found_ = true;
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, you cannot summon Players with higher role than you.", 0, 0);
				}
				else if (pInfo(cp_)->d_s) {
					found_ = true;
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players summon status is `4DISABLE`o.", 0, 0);
				}
				else if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->tankIDName)) {
					found_ = true;
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, You can't summon yourself!", 0, 0);
				}
				else {
					pInfo(cp_)->update = true;
					found_ = true;
					VarList::OnTextOverlay(peer, "Summoning...");
					VarList::OnTextOverlay(cp_, "You were summoned by a mod");
					Enter_World(cp_, pInfo(peer)->world, pInfo(peer)->x / 32, pInfo(peer)->y / 32);
				}
				break;
			}
		}
		if (found_ == false) {
			VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, player was not found.", 0, 0);
		}
	}
	static void FREEZE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /freeze <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false or pInfo(cp_)->world != pInfo(peer)->world) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				if (Playmods::HasById(pInfo(cp_), 2) or Playmods::HasById(pInfo(cp_), 3) or Playmods::HasById(pInfo(cp_), 49)) VarList::OnConsoleMessage(peer, "`o>> Player is frozen already.``");
				else {
					VarList::OnConsoleMessage(peer, "`o>> You got `3frozen`` by player: `2" + pInfo(peer)->tankIDName + ".``");
					Playmods::Add(cp_, 2);
					VisualHandle::State(pInfo(cp_));
					Clothing_V2::Update(cp_, true);
				}
				break;
			}
		}
	}
	static void PUNCH_ID(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /p <id>");
			return;
		}
		int punch = std::atoi(cmd.c_str());
		if (punch >= 0 && punch < 300) {
			pInfo(peer)->punched = punch;
			VarList::OnConsoleMessage(peer, "`2Set punch effect to ID``: " + to_string(pInfo(peer)->punched) + " (set to `20`` to reset).");
		}
		else VarList::OnConsoleMessage(peer, "`2This punch effect does not exist only (0-300).");
		Clothing_V2::Update_Value(peer);
		Clothing_V2::Update(peer, true);
	}
	static void NUKE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /nuke <time> <reason>");
			return;
		}
		std::istringstream ss(cmd);
		std::string Reason;
		int Time;
		try {
			if (ss >> Time >> Reason) {
				std::string name_ = pInfo(peer)->world;
				auto it = std::find_if(worlds.begin(), worlds.end(), [name_](const World& a) { return a.name == name_; });
				if (it != worlds.end()) {
					World* world_ = &(*it);
					if (world_->owner_name == pInfo(peer)->tankIDName) {
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You can't ban your own world!", 0, 0);
						return;
					}
					if (world_->nuked_by.empty()) {
						if (Reason == "") {
							VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The reason can't be empty!", 0, 0);
							return;
						}
						if (Time == 0) {
							VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The time can't be zero!", 0, 0);
							return;
						}
						bool has_admin = false;
						std::string cworld_ = pInfo(peer)->world, BannedBy_ = (pInfo(peer)->d_name.empty() ? pInfo(peer)->name_color : "`0") + "" + (pInfo(peer)->d_name.empty() ? pInfo(peer)->tankIDName : pInfo(peer)->d_name) + "``", ban_who = "", admin_who = "";
						struct tm newtime;
						time_t now = time(0);
#ifdef _WIN32
						localtime_s(&newtime, &now);
#elif defined(__linux__)
						localtime_r(&now, &newtime);
#endif
						world_->nuked_by = pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``, " + to_string(newtime.tm_mon + 1) + "/" + to_string(newtime.tm_mday) + "/" + to_string(1900 + newtime.tm_year) + " " + to_string(newtime.tm_hour) + ":" + (newtime.tm_min < 10 ? "0" + to_string(newtime.tm_min) + "" : "" + to_string(newtime.tm_min)) + ":" + to_string(newtime.tm_sec) + "";
						for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
							if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
							VarList::OnConsoleMessage(cp_, "`o>> `4" + world_->name + " `4was nuked from orbit`o. It's the only way to be sure. Play nice, everybody!");
							CAction::Positioned(cp_, pInfo(cp_)->netID, "audio/bigboom.wav", 0);
							if (pInfo(cp_)->world == cworld_) {
								if (pInfo(cp_)->world == cworld_ and pInfo(cp_)->tankIDName != pInfo(peer)->tankIDName and to_lower(pInfo(cp_)->tankIDName) != to_lower(world_->owner_name)) {
									Exit_World(cp_);
								}
								if (to_lower(pInfo(cp_)->tankIDName) == to_lower(world_->owner_name) or pInfo(cp_)->tankIDName == world_->owner_name) {
									ban_who = (Role::Moderator(cp_) && pInfo(cp_)->d_name.empty() ? pInfo(cp_)->name_color : "`0") + "" + (pInfo(cp_)->d_name.empty() ? pInfo(cp_)->tankIDName : pInfo(cp_)->d_name) + "``";
									Punishment::Banned(cp_, Time, Reason, BannedBy_, 76);
								}
								else {
									ban_who = world_->owner_name;
									string path_ = "database/players/" + world_->owner_name + "_.json";
									if (_access_s(path_.c_str(), 0) == 0) {
										json r_;
										std::ifstream f_(path_, ifstream::binary);
										if (f_.fail()) continue;
										f_ >> r_;
										f_.close();
										{
											json f_ = r_["b_t"].get<int>();
											r_["b_s"] = (Time * 1000);
											r_["b_r"] = Reason;
											r_["b_b"] = BannedBy_;
											r_["b_t"] = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
										}
										{
											std::ofstream f_(path_, ifstream::binary);
											f_ << r_;
											f_.close();
										}
									}
								}
								if (find(world_->admins.begin(), world_->admins.end(), pInfo(cp_)->tankIDName) == world_->admins.end() and pInfo(peer)->tankIDName != pInfo(cp_)->tankIDName) {
									Punishment::Banned(cp_, Time, Reason, BannedBy_, 76);
									has_admin = true, admin_who = (Role::Moderator(cp_) && pInfo(cp_)->d_name.empty() ? pInfo(cp_)->name_color : "`0") + "" + (pInfo(cp_)->d_name.empty() ? pInfo(cp_)->tankIDName : pInfo(cp_)->d_name) + "``";
								}
							}
						}
						for (int i_ = 0; i_ < world_->blocks.size(); i_++) {
							if (world_->blocks[i_].fg == 202 || world_->blocks[i_].fg == 204 || world_->blocks[i_].fg == 206 || world_->blocks[i_].fg == 4994 || world_->blocks[i_].fg == 10000 || world_->blocks[i_].fg == 5814) continue;
							if (items[world_->blocks[i_].fg].blockType == BlockTypes::LOCK) {
								world_->last_lock = world_->blocks[i_].fg;
								world_->blocks[i_].fg = 2950, update_tile(peer, i_ % 100, i_ / 100, 2950, false, true);
							}
						}
						string times = "`4Time`` : `#" + ((Time / 86400 > 0) ? to_string(Time / 86400) + " days" : (Time / 3600 > 0) ? to_string(Time / 3600) + " hours" : (Time / 60 > 0) ? to_string(Time / 60) + " minutes" : to_string(Time) + " seconds");
						ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, " > NUKED WORLD: `#" + cworld_, "");
						ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, " > REASON (" + Reason + "): " + ban_who + " " + times, "");
						ServerPool::Logs::Add(pInfo(peer)->name_color + pInfo(peer)->tankIDName + " (/nuke) NUKED WORLD: `#" + pInfo(peer)->world + " REASON (" + Reason + ") TIME (" + times + ")", "NUKED WORLD");
						if (has_admin) ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, " > BANNED (" + Reason + "): " + ban_who + " " + times, "");
						return;
					}
					else {
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "This world already nuked! You can unnuke first and ban this world!", 0, 0);
						return;
					}
				}
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /nuke <time> <reason>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /nuke <time> <reason>");
		}
	}
	static void NOTE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /note <player name> <text>");
			return;
		}
		std::istringstream ss(cmd);
		std::string playerName, text;
		try {
			if (ss >> playerName >> text) {
				if (text.size() < 3) {
					VarList::OnConsoleMessage(peer, "`oToo shorts notes.");
					return;
				}
				bool has_found = false;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(playerName)) {
						has_found = true;
						pInfo(peer)->Account_Notes.push_back("`o" + currentDateTime() + ": >> " + text + "");
						VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Succesfully added note to " + playerName + "", 0, 0);
					}
				}
				if (not has_found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /note <player name> <text>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /note <player name> <text>");
		}
	}
	static void NOTES(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /notes <player name>");
			return;
		}
		bool foundacc = true;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				foundacc = false;
				string notes = "";
				if (not pInfo(cp_)->Account_Notes.empty()) {
					for (int i = 0; i < pInfo(cp_)->Account_Notes.size(); i++) notes += "\nadd_textbox|`o" + pInfo(cp_)->Account_Notes[i] + "|left|\n";
				}
				else notes += "\nadd_textbox|`oThere's no account notes for this user yet.|left|";
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|`w" + pInfo(cp_)->tankIDName + " Notes|left|\nadd_spacer|small|\nadd_textbox|`oAccount notes:|left|" + notes + "|\nadd_spacer|small|\nend_dialog||Continue||");
				break;
			}
		}
		/*offline*/
		if (foundacc) {
			bool found = false;
			try {
				string name = pInfo(peer)->last_wrenched;
				std::ifstream ifs("database/players/" + name + "_.json");
				if (ifs.is_open()) {
					json j;
					ifs >> j;
					found = true;
					string notes = "";
					for (string a : j["Account_Notes"].get<vector<string>>()) notes += "\nadd_textbox|`o" + a + "|left|\n";
					if (notes == "") notes = "\nadd_textbox|`oThere's no account notes for this user yet.|left|";
					VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|`o\nadd_label|big|`w" + j["name"].get<string>() + " Notes|left|\nadd_spacer|small|\nadd_textbox|`oAccount notes:|left|" + notes + "|\nadd_spacer|small|\nend_dialog||Continue||");
				}
			}
			catch (exception) {
				return;
			}
			if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
		}
	}
	static void MUTE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, ">> Usage: /mute <name> <seconds> <reason>");
			return;
		}
		std::istringstream ss(cmd);
		std::string playerName, reason;
		int seconds_;
		try {
			if (ss >> playerName >> seconds_ >> reason) {
				int remove_playmod_id = 11;
				if (seconds_ <= 0) {
					VarList::OnConsoleMessage(peer, "`o>> The time is too low!``");
					return;
				}
				if (reason.size() < 2) {
					VarList::OnConsoleMessage(peer, "`o>> Too shorts Reason!``");
					return;
				}
				bool found = false;
				pInfo(peer)->last_wrenched = playerName;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
						found = true;
						Punishment::Muted_Cursed(cp_, seconds_, reason, pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``", remove_playmod_id);
						break;			
					}
				}
				if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, ">> Usage: /mute <name> <seconds> <reason>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, ">> Usage: /mute <name> <seconds> <reason>");
		}
	}
	static void CURSE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, ">> Usage: /curse <name> <seconds> <reason>");
			return;
		}
		std::istringstream ss(cmd);
		std::string playerName, reason;
		int seconds_;
		try {
			if (ss >> playerName >> seconds_ >> reason) {
				int remove_playmod_id = 139;
				if (seconds_ <= 0) {
					VarList::OnConsoleMessage(peer, "`o>> The time is too low!``");
					return;
				}
				if (reason.size() < 2) {
					VarList::OnConsoleMessage(peer, "`o>> Too shorts Reason!``");
					return;
				}
				bool found = false;
				pInfo(peer)->last_wrenched = playerName;
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
						found = true;
						Punishment::Muted_Cursed(cp_, seconds_, reason, pInfo(peer)->name_color + pInfo(peer)->tankIDName + "``", remove_playmod_id);
						break;
					}
				}
				if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, ">> Usage: /curse <name> <seconds> <reason>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, ">> Usage: /curse <name> <seconds> <reason>");
		}
	}
	static void UNMUTE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /unmute <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				if (Playmods::HasById(pInfo(cp_), 11, 1)) {
					VarList::OnConsoleMessage(peer, "`o>> <`5" + pInfo(cp_)->tankIDName + "``> was Un" + to_lower(info_about_playmods[11 - 1][3]) + "d!``");
				}
				else VarList::OnConsoleMessage(peer, "`o>> The player didn't had such playmod!``");
				break;
			}
		}
		if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void UNCURSE(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /uncurse <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				found = true;
				if (Playmods::HasById(pInfo(cp_), 139, 1)) {
					VarList::OnConsoleMessage(peer, "`o>> <`5" + pInfo(cp_)->tankIDName + "``> was Un" + to_lower(info_about_playmods[139 - 1][3]) + "d!``");
				}
				else VarList::OnConsoleMessage(peer, "`o>> The player didn't had such playmod!``");
				break;
			}
		}
		if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void COPY_SET(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /copyset <player name>");
			return;
		}
		bool found = false;
		pInfo(peer)->last_wrenched = cmd;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(peer)->growid == false) continue;
			if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(cp_)->tankIDName)) {
				found = true;
				if (Inventory::Contains(peer, pInfo(cp_)->hair) >= 1) pInfo(peer)->hair = pInfo(cp_)->hair;
				if (Inventory::Contains(peer, pInfo(cp_)->shirt) >= 1) pInfo(peer)->shirt = pInfo(cp_)->shirt;
				if (Inventory::Contains(peer, pInfo(cp_)->pants) >= 1) pInfo(peer)->pants = pInfo(cp_)->pants;
				if (Inventory::Contains(peer, pInfo(cp_)->feet) >= 1) pInfo(peer)->feet = pInfo(cp_)->feet;
				if (Inventory::Contains(peer, pInfo(cp_)->face) >= 1) pInfo(peer)->face = pInfo(cp_)->face;
				if (Inventory::Contains(peer, pInfo(cp_)->hand) >= 1) pInfo(peer)->hand = pInfo(cp_)->hand;
				if (Inventory::Contains(peer, pInfo(cp_)->back) >= 1) pInfo(peer)->back = pInfo(cp_)->back;
				if (Inventory::Contains(peer, pInfo(cp_)->mask) >= 1) pInfo(peer)->mask = pInfo(cp_)->mask;
				if (Inventory::Contains(peer, pInfo(cp_)->necklace) >= 1) pInfo(peer)->necklace = pInfo(cp_)->necklace;
				if (Inventory::Contains(peer, pInfo(cp_)->ances) >= 1) pInfo(peer)->ances = pInfo(cp_)->ances;
				Clothing_V2::Update(peer);
				break;
			}
		}
		if (found == false) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void MOD_SB(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /msb <text>");
			return;
		}
		if (Playmods::HasById(pInfo(peer), 156)) {
			int time_ = 0;
			for (PlayMods peer_playmod : pInfo(peer)->playmods) {
				if (peer_playmod.id == 156) {
					time_ = peer_playmod.time - time(nullptr);
					break;
				}
			}
			VarList::OnConsoleMessage(peer, ">> (" + Time::Playmod(time_) + " before you can broadcast again)");
		}
		else {
			CAction::Positioned(peer, pInfo(peer)->netID, "audio/dialog_confirm.wav", 0);
			Playmods::Add(peer, 156);
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				VarList::OnConsoleMessage(cp_, "CP:_PL:0_OID:_CT:[SB]_ `#[MODS-SB] `5** from (`$" + (get_player_nick(peer)) + "`5) in [`4HIDDEN!`5] ** : `$" + cmd + "``");
			}
		}
	}
	static void MOD_CHAT(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /m <text>");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or not Role::Moderator(cp_) or pInfo(cp_)->radio or pInfo(cp_)->radio2) continue;
			VarList::OnConsoleMessage(cp_, "CT:[FC]_>> `o>> [`#MOD-CHAT`o] from (``" + pInfo(peer)->name_color + pInfo(peer)->tankIDName + "```o) in [```$" + pInfo(peer)->world + "```o] > ```$`3" + cmd + "`c");
		}
	}
	static void WARN(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /warn <player name> <text>");
			return;
		}
		std::istringstream ss(cmd);
		std::string playerName, warn_message;
		try {
			if (ss >> playerName >> warn_message) {
				pInfo(peer)->last_wrenched = playerName;
				if (to_lower(pInfo(peer)->last_wrenched) == to_lower(pInfo(peer)->tankIDName)) {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "You can't warn yourself!", 0, 1);
					return;
				}
				if (warn_message == "") {
					VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The warning can't be empty!", 0, 1);
					return;
				}
				for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
					if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
					if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
						if (not Role::Administrator(peer) and Role::Administrator(cp_)) {
							VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Hmm, you cannot warn Players with higher role than you.", 0, 0);
						}
						pInfo(cp_)->Warning++; pInfo(cp_)->Warning_Message.push_back(warn_message);
						VarList::OnConsoleMessage(cp_, "Warning from `4System``: " + warn_message);
						VarList::OnAddNotification(cp_, "Warning from `4System``: " + warn_message, "interface/atomic_button.rttex", "audio/hub_open.wav");
						ServerPool::ModLogs::Add(peer, pInfo(peer)->name_color + pInfo(peer)->tankIDName, "  > `^Warn : " + pInfo(cp_)->tankIDName + "\n`4Warning Message : " + warn_message, "");
						if (pInfo(cp_)->Warning >= 3) {
							int Time = 604800;
							Punishment::Banned(cp_, 6.307e+7, "You has've been reach 3 warnings!", pInfo(cp_)->name_color + pInfo(cp_)->tankIDName + "``", 76);
							ServerPool::ModLogs::Add(cp_, pInfo(cp_)->name_color + pInfo(cp_)->tankIDName, " `^BANNED (has've been reach 3 warnings!)", "");
						}
						return;
					}
				}
				VarList::OnTalkBubble(peer, pInfo(peer)->netID, "The warning send (will work when player's online!)", 0, 0);
			}
		}
		catch (const std::invalid_argument&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /warn <player name> <text>");
		}
		catch (const std::out_of_range&) {
			VarList::OnConsoleMessage(peer, "`oUsage: /warn <player name> <text>");
		}
	}
	static void EFFECT_ID(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /eff <id>");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				CAction::Effect(cp_, std::atoi(cmd.c_str()), pInfo(peer)->x + 16, pInfo(peer)->y + 16);
			}
		}
	}
	static void EFFECTV2_ID(ENetPeer* peer, std::string cmd) {
		if ((cmd.find_first_not_of("0123456789") != string::npos) or cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /eff2 <id>");
			return;
		}
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (pInfo(cp_)->world == pInfo(peer)->world) {
				CAction::Effect_V2(cp_, std::atoi(cmd.c_str()), pInfo(peer)->x + 16, pInfo(peer)->y + 16);
			}
		}
	}
	static void PANEL_BAN(ENetPeer* peer, std::string cmd) {
		if (cmd.empty()) {
			VarList::OnConsoleMessage(peer, "`oUsage: /summon <player name>");
			return;
		}
		pInfo(peer)->last_wrenched = cmd; bool found = false;
		for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
			if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
			if (to_lower(pInfo(cp_)->tankIDName) == to_lower(pInfo(peer)->last_wrenched)) {
				VarList::OnDialogRequest(peer, SetColor(peer) + "set_default_color|\nadd_label_with_icon|big|Ban Panel|left|732|\nadd_textbox|`6ON: `#" + pInfo(cp_)->tankIDName + " `w(" + pInfo(cp_)->requestedName + ") - #" + to_string(pInfo(cp_)->id) + " IP: " + pInfo(cp_)->ip + "|left|\nadd_smalltext|`oKeep in mind! Applying a ban more or equal to 730 days equals as a suspension (permanent ban) for user slowlyrise.<CR>`oChoose the ban amount and write the reason.|\nadd_text_input|Time_Banned|`wTime:||15|\nadd_text_input|Reason_Banned|`4Reason:||30|\nend_dialog|ban_panel|Cancel|Send|");
				found = true;
				break;
			}
		}
		if (not found) VarList::OnTalkBubble(peer, pInfo(peer)->netID, "Players not found!", 0, 0);
	}
	static void ON_ACTION(ENetPeer* peer, std::string cmd) {
		transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
		if (cmd == "/cry" || cmd == "/sad") {
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL or pInfo(cp_)->world != pInfo(peer)->world) continue;
				VarList::OnTalkBubble(cp_, pInfo(peer)->netID, ":'(", 0, 0);
			}
		}
		else {
			if (cmd == "/fa" || cmd == "/foldarms" || cmd == "/fold") cmd = "/fold";
			for (ENetPeer* cp_ = server->peers; cp_ < &server->peers[server->peerCount]; ++cp_) {
				if (cp_->state != ENET_PEER_STATE_CONNECTED or cp_->data == NULL) continue;
				if (pInfo(cp_)->world == pInfo(peer)->world) {
					bool muted_ = false;
					for (int c_ = 0; c_ < pInfo(cp_)->friends.size(); c_++) {
						if (to_lower(pInfo(cp_)->friends[c_].name) == to_lower(pInfo(peer)->tankIDName)) {
							if (pInfo(cp_)->friends[c_].mute) {
								muted_ = true;
								break;
							}
						}
					}
					if (not muted_) VarList::OnAction(cp_, pInfo(peer)->netID, cmd, 0);
				}
			}
		}
	}
};