#pragma once
#define _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
#include <PlayerInfo.h>
#include <iostream>
#include <xlnt/xlnt.hpp>

class XLNT {
public:
    static void Save_Database(ENetPeer* peer, bool online = false) {
        xlnt::workbook wb;
        xlnt::worksheet ws = wb.active_sheet();
        bool booleanValue = true;
        std::string stringValue = "Hello, World!";
        int intValue = 42;
        long long int longLongValue = 1234567890123456789LL;

        // Menyimpan data ke dalam sel
        ws.cell("A1").value("Boolean");
        ws.cell("B1").value(booleanValue);
        ws.cell("A2").value("String");
        ws.cell("B2").value(stringValue);
        ws.cell("A3").value("Integer");
        ws.cell("B3").value(intValue);
        ws.cell("A4").value("Long Long Integer");
        ws.cell("B4").value(longLongValue);

        // Menyimpan vector
        std::vector<int> intVector = { 1, 2, 3, 4, 5 };
        ws.cell("A6").value("Vector of Integers");
        for (size_t i = 0; i < intVector.size(); ++i) {
            ws.cell("B" + std::to_string(6 + i)).value(intVector[i]);
        }
        std::vector<std::pair<std::string, int>> pairVector = { {"Alice", 30}, {"Bob", 25} };
        ws.cell("A12").value("Vector of Pairs");
        for (size_t i = 0; i < pairVector.size(); ++i) {
            ws.cell("B" + std::to_string(12 + i)).value(pairVector[i].first);
            ws.cell("C" + std::to_string(12 + i)).value(pairVector[i].second);
        }

        // Menyimpan vector<tuple>    
        std::vector<std::tuple<std::string, int, double>> tupleVector = { {"Alice", 30, 5.5}, {"Bob", 25, 6.0} };
        ws.cell("A16").value("Vector of Tuples");
        for (size_t i = 0; i < tupleVector.size(); ++i) {
            ws.cell("B" + std::to_string(16 + i)).value(std::get<0>(tupleVector[i])); // String
            ws.cell("C" + std::to_string(16 + i)).value(std::get<1>(tupleVector[i])); // Integer
            ws.cell("D" + std::to_string(16 + i)).value(std::get<2>(tupleVector[i])); // Double
        }
        // Menyimpan workbook ke file
        wb.save("XLNT/Tianvan.xlsx");
        std::cout << "Data berhasil disimpan ke data.xlsx" << std::endl;
    }
};