#pragma once

#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>

#include "Translator.h"
#include "Token.h"

namespace Translator {
	namespace Lexer {
		static class LexicParser {
		public:
			static std::vector<Token> Parse(const std::string& doc);
			static std::vector<Token> ParseFile(const std::string& path);
		};

		std::vector<Token> LexicParser::Parse(const std::string& doc) {
			// Join without shielding several strings to use as regex
			auto Join = [](const std::vector<std::string>& dict) {
				std::string joined = "";
				for (int i = 0; i < dict.size(); ++i) {
					joined += "(" + dict[i] + ")" + (i == dict.size() - 1 ? "" : "|");
				}
				return joined;
			};
			// Join with shielding several strings to use as regex
			auto SJoin = [](const std::vector<std::string>& dict) {
				auto Shield = [](const std::string& line) {
					std::string shielded = "";
					for (auto& it : line) {
						shielded = shielded + "\\" + it;
					}
					return shielded;
				};
				std::string joined = "";
				for (int i = 0; i < dict.size(); ++i) {
					joined += "(" + Shield(dict[i]) + ")" + (i == dict.size() - 1 ? "" : "|");
				}
				return joined;
			};
			auto keywords = std::vector<std::string> {
				"чётк..",		// const
				"оч",			// array dimension
				"широк..",		// array
				"блатн..",		// unsigned
				"посыльн..",	// pointer

				"лапша",		// func
				"прогнать",		// for
				"до",			// for
				"шаг",			// for
				"пока",			// while
				"юмать",		// do
				"пояснить",		// output
				"за",			// output
				"и",			// output
				"гоп",			// input
				"атас",			// break
				"сачковать",	// continue
				"липа",			// null
				"стрела",		// if
				"забить",		// then
				"жиган",		// true
				"фраер",		// false
				"забить",		// then
				"хапнуть",		// new
				"вальнуть",		// delete
				"малина"		// struct
			};
			auto systemTypes = std::vector<std::string>{
				"погоняло",		// string
				"шифер",		// int
				"колонна",		// long
				"плавник",		// float
				"двойник",		// double
				"гудрон",		// char
				"чубрик",		// bool
			};
			auto operations = std::vector<std::string>{
				"внатуре",	// '=='
				"<=",
				">=",
				"поболее",	// >
				"поменее",	// <
				"++",
				"--",
				"полевее",	// <<
				"поправее",	// >>
				"по масти", // init
				"припрячь", // set
				"-",		//
				"/",
				"*",
				"%",
				"&",
				"!",
				"+"
			};
			auto grammar = std::vector<std::string>{
				":",
				","
			};
			auto expr = std::vector<std::pair<Types, std::string>>{
				{VALUE, R"(\d+\.\d*|\d+)"},
				{BRACKETS, R"(\(|\))"},
				{BLOCK, R"(Хы|Же)"},
				{COMMENT, R"(\/\/.*|\/\*[\s\S]*?\*\/)"},
				{STRING, R"(\'(\\.|[^'\\])*\'|\"(\\.|[^"\\])*\")"},
				{KEYWORD, Join(keywords)},
				{TYPE, Join(systemTypes)},
				{OPERATION, SJoin(operations)},
				{GRAMMAR, SJoin(grammar)},
				{SPACE, R"([\ \t]+)"},
				{ENDLINE, R"(\n|\n\r)"},
				{ID, R"([_a-zA-Zа-яА-Я][_a-zA-Zа-яА-Я0-9]*)"}
			};

			std::string joined = "";
			for (int i = 0; i < expr.size(); ++i) {
				joined += "(" + expr[i].second + ")" + (i == expr.size() - 1 ? "" : "|");
			}
			//std::cout << joined;
			std::regex joinedRegex(joined);
			auto words_begin =
				std::sregex_iterator(doc.begin(), doc.end(), joinedRegex);
			auto words_end = std::sregex_iterator();

			std::vector<Token> tokens;

			for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
				std::smatch match = *i;
				int index = -1;
				for (auto& it : expr) {
					if (std::regex_match(match.str(), std::regex(it.second))) {
						index = it.first;
						break;
					}
				}
				tokens.push_back(Token{ (Types)index, match.str() });
			}
			if (std::regex_replace(doc, joinedRegex, "").size() > 0)
				throw std::exception("Sussy balls");
			return tokens;
		}

		std::vector<Token> LexicParser::ParseFile(const std::string& path) {
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return Parse(buffer.str());
		}
	}
}