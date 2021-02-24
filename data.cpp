#include "data.h"

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}

void iex::getRequest(json& jsonData, const std::string url) {
	CURL* curl = curl_easy_init();

	//Set remote URL.
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	//IPV4 over IPV6 due to faster DNS resolution time.
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

	//Timeout after 10 seconds.
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

	//Follow HTTP redirects.
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	//Response information.
	long httpCode(0);
	std::unique_ptr<std::string> httpData(new std::string());

	//Data handling function.
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

	//Connect data container.
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());


	//Run HTTP GET command, capture HTTP response code, cleanup.
	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	curl_easy_cleanup(curl);

	if (httpCode == 200) {
		std::cout << "\nGot successful response from " << url << std::endl;

		jsonData = json::parse(*httpData);
		std::cout << "Printing from getRequest: " << jsonData << std::endl;
	}

}

void iex::parseSymbolData(const json& IEXdata, std::vector<std::string>& symbolVec) {
	int i = 0;

	//step through JSON file until the end is reached
	while(i < IEXdata.size()) {
		symbolVec.push_back(IEXdata[i]["symbol"].dump());
		i++;
	}
}

//Returns a vector of available symbols.
/*
std::vector<std::string> iex::getSymbolList() {
	json jsonData;
	std::string url(IEX_ENDPOINT);
	std::vector<std::string> symbolList;
	std::string key(SANDBOX_KEY);
	url += "/ref-data/symbols?token=" + key;
	iex::getRequest(jsonData, url);
	//assert(jsonData.is_array());
	//Pushes all of the symbols into the vector symbolList.
	parseSymbolData(jsonData, symbolList);
	return symbolList;
}
*/

/*bool iex::isValidSymbol(const std::string& symbol) {
	std::vector<std::string> symbolList = getSymbolList();
	std::string symbolCopy = symbol;
	//locale::to_upper(symbolCopy);
	if(std::find(symbolList.begin(), symbolList.end(), symbolCopy) != symbolList.end()) {
		return true;
	}

	return true;
}
*/
//---ADVANCED FUNDAMENTALS---//
//Learn more: https://iexcloud.io/docs/api/#advanced-fundamentals. 
json iex::stocks::advancedFundamentals(const std::string& symbol, const std::string& period) {
	json jsonData;
	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	if (period == "annual" || period == "quarterly" || period == "ttm") {
		url += "/time-series/fundamentals/" + symbol + "/" + period + "?token=" + key;
		iex::getRequest(jsonData, url);

		std::cout << "Advanced Fundamentals: " << jsonData << std::endl;
	} else {
		std::cout << "Period provided is not a valid option. Valid options are: \"annual\", \"quarterly\", or \"ttm\"."	<< std::endl;
		exit(1);
	}

	return jsonData;
}

//---ADVANCED STATS---//
//Learn more: https://iexcloud.io/docs/api/#advanced-stats
json iex::stocks::advancedStats(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);
	url += "/stock/" + symbol + "/advanced-stats?token=" + key;
	iex::getRequest(jsonData, url);

	return jsonData;
}

//---BALANCE SHEET---//
//Learn more: https://iexcloud.io/docs/api/#balance-sheet
json iex::stocks::balanceSheet(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/balance-sheet?token=" + key;
	getRequest(jsonData, url);

	return jsonData;
}

//---BOOK---//
//Learn more: https://iexcloud.io/docs/api/#book
json iex::stocks::book(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/book?token=" + key;
	getRequest(jsonData, url);
	
	return jsonData;
}

//---CASH FLOW---//
//Learn more: https://iexcloud.io/docs/api/#cash-flow

json iex::cashFlow(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/cash-flow?token=" + key;
	getRequest(jsonData, url);

	return jsonData;
}

//---COMPANY---//
//Learn more: https://iexcloud.io/docs/api/#company
json iex::company(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/company?token=" + key;
	getRequest(jsonData, url);

	return jsonData;
}

//---DELAYED QUOTE---//
//Learn more: https://iexcloud.io/docs/api/#delayed-quote
json iex::delayedQuote(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/delayed-quote?token=" key;
	getRequest(jsonData, url);

	return jsonData;
}

//---DIVIDENDS---//
//Learn more: https://iexcloud.io/docs/api/#dividends-basic
json iex::dividends(const std::string& symbol, const std::string& range) {
	json jsonData;

	if (range == "next" || range == "1m" || range == "3m" || range == "6m" || range == "ytd" || range == "1y" || range == "2y" || range == "5y") {
		std::string url(IEX_ENDPOINT);
		std::string key(SANDBOX_KEY);

		url += "/stock/" + symbol + "/dividends/" + rage + "?token=" + key;
	} else {
		std::cout << "Period provided is not a valid option. Valid options are: \"next\", \"1m\", \"3m\", \"6m\", \"ytd\", \"1y\", \"2y\", or \"5y\"." << std::endl;
		exit(1);
	}
}

//---FINANCIALS---//
//Learn more: https://iexcloud.io/docs/api/#financials
//This endpointn is from IEX 1.0 API, use the new API calls 'cash-flow, 'income' statement, and 'balance-sheet' for new data.
json iex::financials(const std::string& symbol) {
	json jsonData;

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);

	url += "/stock/" + symbol + "/financials?token=" + key;
	getRequest(jsonData, url);

	return jsonData;
}


//---QUOTE---//
//Learn more: https://iexcloud.io/docs/api/#quote
json iex::stocks::quote(const std::string& symbol) {
	json jsonData;
	

/*	if (!isValidSymbol(symbol)) {
		std::cout << "Invalid symbol! I am returning an uninitialized JSON object!";
		return jsonData;
	}*/

	std::string url(IEX_ENDPOINT);
	std::string key(SANDBOX_KEY);
	url += "/stock/" + symbol + "/quote?" + "token=" + key; 
	std::cout << "This is URL: " + url << std::endl;
//Example: https://sandbox.iexapis.com/stable/stock/AAPL/quote?token=YOUR_TOKEN_HERE
//sandbox.iexapis.com/stable/stock/AAPL/quote?token=Tpk_be926f15c3174db09b1a4a349fca9db3
	iex::getRequest(jsonData, url);
	//assert(jsonData.is_array());
	std::cout << jsonData << std::endl;
	return jsonData;
}



