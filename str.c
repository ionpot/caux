#include "def.h"
#include "str.h"

int
is_upper(byte b)
{
	return ASC('A', b, 'Z');
}

int
is_lower(byte b)
{
	return ASC('a', b, 'z');
}

int
is_alpha(byte b)
{
	return is_upper(b)
		|| is_lower(b)
		|| (b == '_');
}

int
is_num(byte b)
{
	return ASC('0', b, '9');
}

int
is_alphanum(byte b)
{
	return is_alpha(b) || is_num(b);
}

int
is_ws(byte b)
{
	return (b == ' ') || (b == '\t');
}

int
utf8_trailing(byte b)
{
	if (b < 0x80) {
		return 0;
	}

	if (b < 0xE0) {
		return 1;
	}

	if (b < 0xF0) {
		return 2;
	}

	if (b < 0xF8) {
		return 3;
	}

	return 0;
}

int
utf8_continuation(byte b)
{
	return ASC(0x80, b, 0xBF);
}
