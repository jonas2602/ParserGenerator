#pragma once

enum ETokenType {
	CHAR = 0,
	ESCAPED = 1,
	MINUS = 2,
};

enum ERuleType {
	ELEMENTS = 0,
	RANGE = 1,
	RANGE2 = 2,
	SYMBOL = 3,
};