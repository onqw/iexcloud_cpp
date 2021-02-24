#ifndef data_h
#define data_h

#include "json.hpp"
//#include <json/json.h>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>

using json = nlohmann::json;

//https://cloud.iexapis.com/
#define IEX_ENDPOINT "https://sandbox.iexapis.com/stable"
//#define KEY "YOUR_TOKEN_HERE"
#define SANDBOX_KEY "YOUR_TOKEN_HERE"

namespace iex {
	void getRequest(json& jsonData, const std::string url);
	bool isValidSymbol(const std::string& symbol);

	std::vector<std::string> getSymbolList();

	void parseSymbolData(const json& jsonData, std::vector<std::string>& symbolVec);

	namespace stocks {
		json advancedFundamentals(const std::string& symbol, const std::string& period);
		json advancedStats(const std::string& symbol);
		json balanceSheet(const std::string& symbol);
		json book(const std::string& book);
		json cashFlow(const std::string& symbol);
		json company(const std::string& symbol);
		json delayedQuote(const std::string& symbol);
		json dividends(const std::string& symbol, const std::string& range);
		json financials(const std::string& symbol);
		json quote(const std::string& symbol);

	}
}
	
#endif
