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
			auto keywords = std::vector<std::string>{
				"чЄтк..",
				"оч",
				"широк..",
				"блатн.."
			};
			auto operations = std::vector<std::string>{
				"==",
				"<=",
				">=",
				"++",
				"--",
				"<<",
				">>",
				"=",
				"-",
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
				{BLOCK, R"(’ы|∆ых)"},
				{COMMENT, R"(\/\/.*|\/\*[\s\S]*?\*\/)"},
				{STRING, R"(\'(\\.|[^'\\])*\'|\"(\\.|[^"\\])*\")"},
				{KEYWORD, Join(keywords)},
				{OPERATION, SJoin(operations)},
				{GRAMMAR, SJoin(grammar)},
				{ID, R"([_a-zA-Zа-€ј-я][_a-zA-Zа-€ј-я0-9]*)"}
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