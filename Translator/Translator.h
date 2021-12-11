#pragma once

#include "Lexer.h"
#include <exception>

namespace Translator {
	public ref class Program
	{
	public:
		static void main() {
			setlocale(LC_ALL, "ru");
			auto tokens = Lexer::LexicParser::ParseFile("D:\\Le projects\\Thulan\\Translator\\Source.txt");
			for (auto& it : tokens) {
				std::cout << Type2string(it.type) << " -> " << it.value << "\n";
			}
		}
	};
}
