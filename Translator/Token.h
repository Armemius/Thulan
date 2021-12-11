#pragma once

#include <string>

namespace Translator {
	namespace Lexer {
		enum Types {
			VALUE,
			ID,
			BRACKETS,
			BLOCK,
			COMMENT,
			STRING,
			KEYWORD,
			OPERATION,
			GRAMMAR,
			ENDLINE
		};

		std::string Type2string(Types type) {
			switch (type)
			{
			case VALUE:
				return "Value";
				break;
			case ID:
				return "Name";
				break;
			case BRACKETS:
				return "Brackets";
				break;
			case BLOCK:
				return "Block";
				break;
			case COMMENT:
				return "Comment";
				break;
			case STRING:
				return "String";
				break;
			case KEYWORD:
				return "Keyword";
				break;
			case OPERATION:
				return "Operation";
				break;
			case GRAMMAR:
				return "Grammar";
				break;
			case ENDLINE:
				return "Endline";
				break;
			default:
				return "NULL";
				break;
			}
		}

		public struct Token {
			Types type;
			const std::string value;
		};
	}
}