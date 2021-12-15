#pragma once

#include <exception>

#include "Lexer.h"
#include "Token.h"

namespace Translator {
	public ref class Program
	{
	public:
		static void main() {
			setlocale(LC_ALL, "ru");
			auto tokens = Lexer::LexicParser::ParseFile(R"(C:\My Files\Sus\Thulan\Translator\Source.txt)");
			for (auto& it : tokens) {
				std::cout << Type2string(it.type);
				if (it.type != Lexer::ENDLINE && it.type != Lexer::SPACE)
					std::cout << " -> " << it.value;
				std::cout << "\n";
			}
		}
	};
}
