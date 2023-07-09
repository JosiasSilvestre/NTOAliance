////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#include "otpch.h"
#include <iostream>
#include <iomanip>

#include "tools.h"
#include "md5.h"
#include "sha1.h"

#include "vocation.h"
#include "configmanager.h"
extern ConfigManager g_config;

std::string transformToSHA1(std::string plainText, bool upperCase)
{
	SHA1 sha1;
	unsigned sha1Hash[5];
	std::stringstream hexStream;

	sha1.Input((const uint8_t*)plainText.c_str(), plainText.length());
	sha1.Result(sha1Hash);

	hexStream.flags(std::ios::hex | std::ios::uppercase);
	for(uint32_t i = 0; i < 5; ++i)
		hexStream << std::setw(8) << std::setfill('0') << (uint32_t)sha1Hash[i];

	std::string hexStr = hexStream.str();
	if(!upperCase)
		toLowerCaseString(hexStr);

	return hexStr;
}

std::string transformToMD5(std::string plainText, bool upperCase)
{
	MD5_CTX m_md5;
	std::stringstream hexStream;

	MD5Init(&m_md5, 0);
	MD5Update(&m_md5, (const uint8_t*)plainText.c_str(), plainText.length());
	MD5Final(&m_md5);

	hexStream.flags(std::ios::hex | std::ios::uppercase);
	for(uint32_t i = 0; i < 16; ++i)
		hexStream << std::setw(2) << std::setfill('0') << (uint32_t)m_md5.digest[i];

	std::string hexStr = hexStream.str();
	if(!upperCase)
		toLowerCaseString(hexStr);

	return hexStr;
}

void _encrypt(std::string& str, bool upperCase)
{
	switch(g_config.getNumber(ConfigManager::ENCRYPTION))
	{
		case ENCRYPTION_MD5:
			str = transformToMD5(str, upperCase);
			break;
		case ENCRYPTION_SHA1:
			str = transformToSHA1(str, upperCase);
			break;
		default:
		{
			if(upperCase)
				std::transform(str.begin(), str.end(), str.begin(), upchar);

			break;
		}
	}
}

bool encryptTest(std::string plain, std::string& hash)
{
	std::transform(hash.begin(), hash.end(), hash.begin(), upchar);
	_encrypt(plain, true);
	return plain == hash;
}

void replaceString(std::string& text, const std::string key, const std::string value)
{
	if(value.find(key) != std::string::npos) //don't allow infinite loops
		return;

	for(std::string::size_type keyStart = text.find(key); keyStart
		!= std::string::npos; keyStart = text.find(key))
		text.replace(keyStart, key.size(), value);
}

void trim_right(std::string& source, const std::string& t)
{
	source.erase(source.find_last_not_of(t)+1);
}

void trim_left(std::string& source, const std::string& t)
{
	source.erase(0, source.find_first_not_of(t));
}

void toLowerCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), tolower);
}

void toUpperCaseString(std::string& source)
{
	std::transform(source.begin(), source.end(), source.begin(), upchar);
}

std::string asLowerCaseString(const std::string& source)
{
	std::string s = source;
	toLowerCaseString(s);
	return s;
}

std::string asUpperCaseString(const std::string& source)
{
	std::string s = source;
	toUpperCaseString(s);
	return s;
}

bool booleanString(std::string source)
{
	toLowerCaseString(source);
	return (source == "yes" || source == "true" || atoi(source.c_str()) > 0);
}

bool readXMLInteger(xmlNodePtr node, const char* tag, int& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoi(nodeValue);
	xmlFree(nodeValue);
	return true;
}

#if defined WINDOWS && !defined __GNUC__
bool readXMLInteger(xmlNodePtr node, const char* tag, int32_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoi(nodeValue);
	xmlFree(nodeValue);
	return true;
}
#endif

bool readXMLInteger64(xmlNodePtr node, const char* tag, int64_t& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atoll(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLFloat(xmlNodePtr node, const char* tag, float& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	value = atof(nodeValue);
	xmlFree(nodeValue);
	return true;
}

bool readXMLString(xmlNodePtr node, const char* tag, std::string& value)
{
	char* nodeValue = (char*)xmlGetProp(node, (xmlChar*)tag);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool readXMLContentString(xmlNodePtr node, std::string& value)
{
	char* nodeValue = (char*)xmlNodeGetContent(node);
	if(!nodeValue)
		return false;

	if(!utf8ToLatin1(nodeValue, value))
		value = nodeValue;

	xmlFree(nodeValue);
	return true;
}

bool parseXMLContentString(xmlNodePtr node, std::string& value)
{
	bool result = false;
	std::string compareValue;
	while(node)
	{
		if(xmlStrcmp(node->name, (const xmlChar*)"text") && node->type != XML_CDATA_SECTION_NODE)
		{
			node = node->next;
			continue;
		}

		if(!readXMLContentString(node, compareValue))
		{
			node = node->next;
			continue;
		}

		trim_left(compareValue, "\r");
		trim_left(compareValue, "\n");
		trim_left(compareValue, " ");
		if(compareValue.length() > value.length())
		{
			value = compareValue;
			if(!result)
				result = true;
		}

		node = node->next;
	}

	return result;
}

std::string getLastXMLError()
{
	std::stringstream ss;
	xmlErrorPtr lastError = xmlGetLastError();
	if(lastError->line)
		ss << "Line: " << lastError->line << ", ";

	ss << "Info: " << lastError->message << std::endl;
	return ss.str();
}

bool utf8ToLatin1(char* intext, std::string& outtext)
{
	outtext = "";
	if(!intext)
		return false;

	int32_t inlen = strlen(intext);
	if(!inlen)
		return false;

	int32_t outlen = inlen * 2;
	uint8_t* outbuf = new uint8_t[outlen];

	int32_t res = UTF8Toisolat1(outbuf, &outlen, (uint8_t*)intext, &inlen);
	if(res < 0)
	{
		delete[] outbuf;
		return false;
	}

	outbuf[outlen] = '\0';
	outtext = (char*)outbuf;

	delete[] outbuf;
	return true;
}

StringVec explodeString(const std::string& string, const std::string& separator)
{
	StringVec returnVector;
	size_t start = 0, end = 0;
	while((end = string.find(separator, start)) != std::string::npos)
	{
		returnVector.push_back(string.substr(start, end - start));
		start = end + separator.size();
	}

	returnVector.push_back(string.substr(start));
	return returnVector;
}

IntegerVec vectorAtoi(StringVec stringVector)
{
	IntegerVec returnVector;
	for(StringVec::iterator it = stringVector.begin(); it != stringVector.end(); ++it)
		returnVector.push_back(atoi((*it).c_str()));

	return returnVector;
}

bool hasBitSet(uint32_t flag, uint32_t flags)
{
	return ((flags & flag) == flag);
}

int32_t round(float v)
{
	int32_t t = (int32_t)std::floor(v);
	if((v - t) > 0.5)
		return t + 1;

	return t;
}

uint32_t rand24b()
{
	return ((rand() << 12) ^ (rand())) & (0xFFFFFF);
}

float box_muller(float m, float s)
{
	// normal random variate generator
	// mean m, standard deviation s
	float x1, x2, w, y1;
	static float y2;

	static bool useLast = false;
	if(useLast) // use value from previous call
	{
		y1 = y2;
		useLast = false;
		return (m + y1 * s);
	}

	do
	{
		double r1 = (((float)(rand()) / RAND_MAX));
		double r2 = (((float)(rand()) / RAND_MAX));

		x1 = 2.0 * r1 - 1.0;
		x2 = 2.0 * r2 - 1.0;
		w = x1 * x1 + x2 * x2;
	}
	while(w >= 1.0);
	w = sqrt((-2.0 * log(w)) / w);

	y1 = x1 * w;
	y2 = x2 * w;

	useLast = true;
	return (m + y1 * s);
}

int32_t random_range(int32_t lowestNumber, int32_t highestNumber, DistributionType_t type /*= DISTRO_UNIFORM*/)
{
	if(highestNumber == lowestNumber)
		return lowestNumber;

	if(lowestNumber > highestNumber)
		std::swap(lowestNumber, highestNumber);

	switch(type)
	{
		case DISTRO_UNIFORM:
			return (lowestNumber + ((int32_t)rand24b() % (highestNumber - lowestNumber + 1)));
		case DISTRO_NORMAL:
			return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * (float)std::min((float)1, std::max((float)0, box_muller(0.5, 0.25)))));
		default:
			break;
	}

	const float randMax = 16777216;
	return (lowestNumber + int32_t(float(highestNumber - lowestNumber) * float(1.f - sqrt((1.f * rand24b()) / randMax))));
}

char upchar(char character)
{
	if((character >= 97 && character <= 122) || (character <= -1 && character >= -32))
		character -= 32;

	return character;
}

bool isNumber(char character)
{
	return (character >= 48 && character <= 57);
}

bool isLowercaseLetter(char character)
{
	return (character >= 97 && character <= 122);
}

bool isUppercaseLetter(char character)
{
	return (character >= 65 && character <= 90);
}

bool isPasswordCharacter(char character)
{
	return ((character >= 33 && character <= 47) || (character >= 58 && character <= 64) || (character >= 91 && character <= 96) || (character >= 123 && character <= 126));
}

bool isValidAccountName(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]))
			return false;
	}

	return true;
}

bool isValidPassword(std::string text)
{
	toLowerCaseString(text);

	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isLowercaseLetter(text[size]) && !isNumber(text[size]) && !isPasswordCharacter(text[size]))
			return false;
	}

	return true;
}

bool isValidName(std::string text, bool forceUppercaseOnFirstLetter/* = true*/)
{
	uint32_t textLength = text.length(), lenBeforeSpace = 1, lenBeforeQuote = 1, lenBeforeDash = 1, repeatedCharacter = 0;
	char lastChar = 32;
	if(forceUppercaseOnFirstLetter)
	{
		if(!isUppercaseLetter(text[0]))
			return false;
	}
	else if(!isLowercaseLetter(text[0]) && !isUppercaseLetter(text[0]))
		return false;

	for(uint32_t size = 1; size < textLength; size++)
	{
		if(text[size] != 32)
		{
			lenBeforeSpace++;

			if(text[size] != 39)
				lenBeforeQuote++;
			else
			{
				if(lenBeforeQuote <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeQuote = 0;
			}

			if(text[size] != 45)
				lenBeforeDash++;
			else
			{
				if(lenBeforeDash <= 1 || size == textLength - 1 || text[size + 1] == 32)
					return false;

				lenBeforeDash = 0;
			}

			if(text[size] == lastChar)
			{
				repeatedCharacter++;
				if(repeatedCharacter > 2)
					return false;
			}
			else
				repeatedCharacter = 0;

			lastChar = text[size];
		}
		else
		{
			if(lenBeforeSpace <= 1 || size == textLength - 1 || text[size + 1] == 32)
				return false;

			lenBeforeSpace = lenBeforeQuote = lenBeforeDash = 0;
		}

		if(!(isLowercaseLetter(text[size]) || text[size] == 32 || text[size] == 39 || text[size] == 45
			|| (isUppercaseLetter(text[size]) && text[size - 1] == 32)))
			return false;
	}

	return true;
}

bool isNumbers(std::string text)
{
	uint32_t textLength = text.length();
	for(uint32_t size = 0; size < textLength; size++)
	{
		if(!isNumber(text[size]))
			return false;
	}

	return true;
}

bool checkText(std::string text, std::string str)
{
	trimString(text);
	return asLowerCaseString(text) == str;
}

std::string generateRecoveryKey(int32_t fieldCount, int32_t fieldLenght)
{
	std::stringstream key;
	int32_t i = 0, j = 0, lastNumber = 99, number = 0;

	char character = 0, lastCharacter = 0;
	bool madeNumber = false, madeCharacter = false;
	do
	{
		do
		{
			madeNumber = madeCharacter = false;
			if((bool)random_range(0, 1))
			{
				number = random_range(2, 9);
				if(number != lastNumber)
				{
					key << number;
					lastNumber = number;
					madeNumber = true;
				}
			}
			else
			{
				character = (char)random_range(65, 90);
				if(character != lastCharacter)
				{
					key << character;
					lastCharacter = character;
					madeCharacter = true;
				}
			}
		}
		while((!madeCharacter && !madeNumber) ? true : (++j && j < fieldLenght));
		lastCharacter = character = number = j = 0;

		lastNumber = 99;
		if(i < fieldCount - 1)
			key << "-";
	}
	while(++i && i < fieldCount);
	return key.str();
}

std::string trimString(std::string& str)
{
	str.erase(str.find_last_not_of(" ") + 1);
	return str.erase(0, str.find_first_not_of(" "));
}

std::string parseParams(tokenizer::iterator &it, tokenizer::iterator end)
{
	if(it == end)
		return "";

	std::string tmp = (*it);
	++it;
	if(tmp[0] == '"')
	{
		tmp.erase(0, 1);
		while(it != end && tmp[tmp.length() - 1] != '"')
		{
			tmp += " " + (*it);
			++it;
		}

		if(tmp.length() > 0 && tmp[tmp.length() - 1] == '"')
			tmp.erase(tmp.length() - 1);
	}

	return tmp;
}

std::string formatDate(time_t _time/* = 0*/)
{
	char buffer[21];
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	if(tms)
		sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", tms->tm_mday, tms->tm_mon + 1, tms->tm_year + 1900, tms->tm_hour, tms->tm_min, tms->tm_sec);
	else
		sprintf(buffer, "UNIX Time: %d", (int32_t)_time);

	return buffer;
}

std::string formatDateShort(time_t _time, bool detailed/* = false*/)
{
	char buffer[21];
	if(!_time)
		_time = time(NULL);

	const tm* tms = localtime(&_time);
	if(tms)
	{
		std::string format = "%d %b %Y";
		if(detailed)
			format += " %H:%M:%S";

		strftime(buffer, 25, format.c_str(), tms);
	}
	else
		sprintf(buffer, "UNIX Time: %d", (int32_t)_time);

	return buffer;
}

std::string formatTime(int32_t hours, int32_t minutes)
{
	std::stringstream time;
	if(hours)
		time << hours << " " << (hours > 1 ? "hours" : "hour") << (minutes ? " and " : "");

	if(minutes)
		time << minutes << " " << (minutes > 1 ? "minutes" : "minute");

	return time.str();
}

std::string convertIPAddress(uint32_t ip)
{
	char buffer[17];
	sprintf(buffer, "%d.%d.%d.%d", ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24));
	return buffer;
}

Skulls_t getSkull(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "black" || tmpStrValue == "5")
		return SKULL_BLACK;
	else if(tmpStrValue == "red" || tmpStrValue == "4")
		return SKULL_RED;
	else if(tmpStrValue == "white" || tmpStrValue == "3")
		return SKULL_WHITE;
	else if(tmpStrValue == "green" || tmpStrValue == "2")
		return SKULL_GREEN;
	else if(tmpStrValue == "yellow" || tmpStrValue == "1")
		return SKULL_YELLOW;

	return SKULL_NONE;
}

PartyShields_t getPartyShield(std::string strValue)
{
	std::string tmpStrValue = asLowerCaseString(strValue);
	if(tmpStrValue == "whitenoshareoff" || tmpStrValue == "10")
		return SHIELD_YELLOW_NOSHAREDEXP;
	else if(tmpStrValue == "blueshareoff" || tmpStrValue == "9")
		return SHIELD_BLUE_NOSHAREDEXP;
	else if(tmpStrValue == "yellowshareblink" || tmpStrValue == "8")
		return SHIELD_YELLOW_NOSHAREDEXP_BLINK;
	else if(tmpStrValue == "blueshareblink" || tmpStrValue == "7")
		return SHIELD_BLUE_NOSHAREDEXP_BLINK;
	else if(tmpStrValue == "yellowshareon" || tmpStrValue == "6")
		return SHIELD_YELLOW_SHAREDEXP;
	else if(tmpStrValue == "blueshareon" || tmpStrValue == "5")
		return SHIELD_BLUE_SHAREDEXP;
	else if(tmpStrValue == "yellow" || tmpStrValue == "4")
		return SHIELD_YELLOW;
	else if(tmpStrValue == "blue" || tmpStrValue == "3")
		return SHIELD_BLUE;
	else if(tmpStrValue == "whiteyellow" || tmpStrValue == "2")
		return SHIELD_WHITEYELLOW;
	else if(tmpStrValue == "whiteblue" || tmpStrValue == "1")
		return SHIELD_WHITEBLUE;

	return SHIELD_NONE;
}

Direction getDirection(std::string string)
{
	if(string == "north" || string == "n" || string == "0")
		return NORTH;
	else if(string == "east" || string == "e" || string == "1")
		return EAST;
	else if(string == "south" || string == "s" || string == "2")
		return SOUTH;
	else if(string == "west" || string == "w" || string == "3")
		return WEST;
	else if(string == "southwest" || string == "south west" || string == "south-west" || string == "sw" || string == "4")
		return SOUTHWEST;
	else if(string == "southeast" || string == "south east" || string == "south-east" || string == "se" || string == "5")
		return SOUTHEAST;
	else if(string == "northwest" || string == "north west" || string == "north-west" || string == "nw" || string == "6")
		return NORTHWEST;
	else if(string == "northeast" || string == "north east" || string == "north-east" || string == "ne" || string == "7")
		return NORTHEAST;

	return SOUTH;
}

Direction getDirectionTo(Position pos1, Position pos2, bool extended/* = true*/)
{
	Direction direction = NORTH;
	if(pos1.x > pos2.x)
	{
		direction = WEST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHWEST;
			else if(pos1.y < pos2.y)
				direction = SOUTHWEST;
		}
	}
	else if(pos1.x < pos2.x)
	{
		direction = EAST;
		if(extended)
		{
			if(pos1.y > pos2.y)
				direction = NORTHEAST;
			else if(pos1.y < pos2.y)
				direction = SOUTHEAST;
		}
	}
	else
	{
		if(pos1.y > pos2.y)
			direction = NORTH;
		else if(pos1.y < pos2.y)
			direction = SOUTH;
	}

	return direction;
}

Direction getReverseDirection(Direction dir)
{
	switch(dir)
	{
		case NORTH:
			return SOUTH;
		case SOUTH:
			return NORTH;
		case WEST:
			return EAST;
		case EAST:
			return WEST;
		case SOUTHWEST:
			return NORTHEAST;
		case NORTHWEST:
			return SOUTHEAST;
		case NORTHEAST:
			return SOUTHWEST;
		case SOUTHEAST:
			return NORTHWEST;
	}

	return SOUTH;
}

Position getNextPosition(Direction direction, Position pos)
{
	switch(direction)
	{
		case NORTH:
			pos.y--;
			break;
		case SOUTH:
			pos.y++;
			break;
		case WEST:
			pos.x--;
			break;
		case EAST:
			pos.x++;
			break;
		case SOUTHWEST:
			pos.x--;
			pos.y++;
			break;
		case NORTHWEST:
			pos.x--;
			pos.y--;
			break;
		case SOUTHEAST:
			pos.x++;
			pos.y++;
			break;
		case NORTHEAST:
			pos.x++;
			pos.y--;
			break;
	}

	return pos;
}

struct AmmoTypeNames
{
	const char* name;
	Ammo_t ammoType;
};

struct MagicEffectNames
{
	const char* name;
	MagicEffect_t magicEffect;
};

struct ShootTypeNames
{
	const char* name;
	ShootEffect_t shootType;
};

struct CombatTypeNames
{
	const char* name;
	CombatType_t combatType;
};

struct AmmoActionNames
{
	const char* name;
	AmmoAction_t ammoAction;
};

struct FluidTypeNames
{
	const char* name;
	FluidTypes_t fluidType;
};

struct SkillIdNames
{
	const char* name;
	skills_t skillId;
};

MagicEffectNames magicEffectNames[] =
{
	{"redspark",		MAGIC_EFFECT_DRAW_BLOOD},
	{"bluebubble",		MAGIC_EFFECT_LOSE_ENERGY},
	{"poff",		MAGIC_EFFECT_POFF},
	{"yellowspark",		MAGIC_EFFECT_BLOCKHIT},
	{"explosionarea",	MAGIC_EFFECT_EXPLOSION_AREA},
	{"explosion",		MAGIC_EFFECT_EXPLOSION_DAMAGE},
	{"firearea",		MAGIC_EFFECT_FIRE_AREA},
	{"yellowbubble",	MAGIC_EFFECT_YELLOW_RINGS},
	{"greenbubble",		MAGIC_EFFECT_POISON_RINGS},
	{"blackspark",		MAGIC_EFFECT_HIT_AREA},
	{"teleport",		MAGIC_EFFECT_TELEPORT},
	{"energy",		MAGIC_EFFECT_ENERGY_DAMAGE},
	{"blueshimmer",		MAGIC_EFFECT_WRAPS_BLUE},
	{"redshimmer",		MAGIC_EFFECT_WRAPS_RED},
	{"greenshimmer",	MAGIC_EFFECT_WRAPS_GREEN},
	{"fire",		MAGIC_EFFECT_HITBY_FIRE},
	{"greenspark",		MAGIC_EFFECT_POISON},
	{"mortarea",		MAGIC_EFFECT_MORT_AREA},
	{"greennote",		MAGIC_EFFECT_SOUND_GREEN},
	{"rednote",		MAGIC_EFFECT_SOUND_RED},
	{"poison",		MAGIC_EFFECT_POISON_AREA},
	{"yellownote",		MAGIC_EFFECT_SOUND_YELLOW},
	{"purplenote",		MAGIC_EFFECT_SOUND_PURPLE},
	{"bluenote",		MAGIC_EFFECT_SOUND_BLUE},
	{"whitenote",		MAGIC_EFFECT_SOUND_WHITE},
	{"bubbles",		MAGIC_EFFECT_BUBBLES},
	{"dice",		MAGIC_EFFECT_CRAPS},
	{"giftwraps",		MAGIC_EFFECT_GIFT_WRAPS},
	{"yellowfirework",	MAGIC_EFFECT_FIREWORK_YELLOW},
	{"redfirework",		MAGIC_EFFECT_FIREWORK_RED},
	{"bluefirework",	MAGIC_EFFECT_FIREWORK_BLUE},
	{"stun",		MAGIC_EFFECT_STUN},
	{"sleep",		MAGIC_EFFECT_SLEEP},
	{"watercreature",	MAGIC_EFFECT_WATERCREATURE},
	{"groundshaker",	MAGIC_EFFECT_GROUNDSHAKER},
	{"hearts",		MAGIC_EFFECT_HEARTS},
	{"fireattack",		MAGIC_EFFECT_FIREATTACK},
	{"energyarea",		MAGIC_EFFECT_ENERGY_AREA},
	{"smallclouds",		MAGIC_EFFECT_SMALLCLOUDS},
	{"holydamage",		MAGIC_EFFECT_HOLYDAMAGE},
	{"bigclouds",		MAGIC_EFFECT_BIGCLOUDS},
	{"icearea",		MAGIC_EFFECT_ICEAREA},
	{"icetornado",		MAGIC_EFFECT_ICETORNADO},
	{"iceattack",		MAGIC_EFFECT_ICEATTACK},
	{"stones",		MAGIC_EFFECT_STONES},
	{"smallplants",		MAGIC_EFFECT_SMALLPLANTS},
	{"carniphila",		MAGIC_EFFECT_CARNIPHILA},
	{"purpleenergy",	MAGIC_EFFECT_PURPLEENERGY},
	{"yellowenergy",	MAGIC_EFFECT_YELLOWENERGY},
	{"holyarea",		MAGIC_EFFECT_HOLYAREA},
	{"bigplants",		MAGIC_EFFECT_BIGPLANTS},
	{"cake",		MAGIC_EFFECT_CAKE},
	{"giantice",		MAGIC_EFFECT_GIANTICE},
	{"watersplash",		MAGIC_EFFECT_WATERSPLASH},
	{"plantattack",		MAGIC_EFFECT_PLANTATTACK},
	{"tutorialarrow",	MAGIC_EFFECT_TUTORIALARROW},
	{"tutorialsquare",	MAGIC_EFFECT_TUTORIALSQUARE},
	{"mirrorhorizontal",	MAGIC_EFFECT_MIRRORHORIZONTAL},
	{"mirrorvertical",	MAGIC_EFFECT_MIRRORVERTICAL},
	{"skullhorizontal",	MAGIC_EFFECT_SKULLHORIZONTAL},
	{"skullvertical",	MAGIC_EFFECT_SKULLVERTICAL},
	{"assassin",		MAGIC_EFFECT_ASSASSIN},
	{"stepshorizontal",	MAGIC_EFFECT_STEPSHORIZONTAL},
	{"bloodysteps",		MAGIC_EFFECT_BLOODYSTEPS},
	{"stepsvertical",	MAGIC_EFFECT_STEPSVERTICAL},
	{"yalaharighost",	MAGIC_EFFECT_YALAHARIGHOST},
	{"bats",		MAGIC_EFFECT_BATS},
	{"smoke",		MAGIC_EFFECT_SMOKE},
	{"insects",		MAGIC_EFFECT_INSECTS},
	{"efeito69",		MAGIC_EFFECT_EFEITO69},
	{"efeito70",		MAGIC_EFFECT_EFEITO70},
	{"efeito71",		MAGIC_EFFECT_EFEITO71},
	{"efeito72",		MAGIC_EFFECT_EFEITO72},
	{"efeito73",		MAGIC_EFFECT_EFEITO73},
	{"efeito74",		MAGIC_EFFECT_EFEITO74},
	{"efeito75",		MAGIC_EFFECT_EFEITO75},
	{"efeito76",		MAGIC_EFFECT_EFEITO76},
	{"efeito77",		MAGIC_EFFECT_EFEITO77},
	{"efeito78",		MAGIC_EFFECT_EFEITO78},
	{"efeito79",		MAGIC_EFFECT_EFEITO79},
	{"efeito80",		MAGIC_EFFECT_EFEITO80},
	{"efeito81",		MAGIC_EFFECT_EFEITO81},
	{"efeito82",		MAGIC_EFFECT_EFEITO82},
	{"efeito83",		MAGIC_EFFECT_EFEITO83},
	{"efeito84",		MAGIC_EFFECT_EFEITO84},
	{"efeito85",		MAGIC_EFFECT_EFEITO85},
	{"efeito86",		MAGIC_EFFECT_EFEITO86},
	{"efeito87",		MAGIC_EFFECT_EFEITO87},
	{"efeito88",		MAGIC_EFFECT_EFEITO88},
	{"efeito89",		MAGIC_EFFECT_EFEITO89},
	{"efeito90",		MAGIC_EFFECT_EFEITO90},
	{"efeito91",		MAGIC_EFFECT_EFEITO91},
	{"efeito92",		MAGIC_EFFECT_EFEITO92},
	{"efeito93",		MAGIC_EFFECT_EFEITO93},
	{"efeito94",		MAGIC_EFFECT_EFEITO94},
	{"efeito95",		MAGIC_EFFECT_EFEITO95},
	{"efeito96",		MAGIC_EFFECT_EFEITO96},
	{"efeito97",		MAGIC_EFFECT_EFEITO97},
	{"efeito98",		MAGIC_EFFECT_EFEITO98},
	{"efeito99",		MAGIC_EFFECT_EFEITO99},
	{"efeito100",		MAGIC_EFFECT_EFEITO100},
	{"efeito101",		MAGIC_EFFECT_EFEITO101},
	{"efeito102",		MAGIC_EFFECT_EFEITO102},
	{"efeito103",		MAGIC_EFFECT_EFEITO103},
	{"efeito104",		MAGIC_EFFECT_EFEITO104},
	{"efeito105",		MAGIC_EFFECT_EFEITO105},
	{"efeito106",		MAGIC_EFFECT_EFEITO106},
	{"efeito107",		MAGIC_EFFECT_EFEITO107},
	{"efeito108",		MAGIC_EFFECT_EFEITO108},
	{"efeito109",		MAGIC_EFFECT_EFEITO109},
	{"efeito110",		MAGIC_EFFECT_EFEITO110},
	{"efeito111",		MAGIC_EFFECT_EFEITO111},
	{"efeito112",		MAGIC_EFFECT_EFEITO112},
	{"efeito113",		MAGIC_EFFECT_EFEITO113},
	{"efeito114",		MAGIC_EFFECT_EFEITO114},
	{"efeito115",		MAGIC_EFFECT_EFEITO115},
	{"efeito116",		MAGIC_EFFECT_EFEITO116},
	{"efeito117",		MAGIC_EFFECT_EFEITO117},
	{"efeito118",		MAGIC_EFFECT_EFEITO118},
	{"efeito119",		MAGIC_EFFECT_EFEITO119},
	{"efeito120",		MAGIC_EFFECT_EFEITO120},
	{"efeito121",		MAGIC_EFFECT_EFEITO121},
	{"efeito122",		MAGIC_EFFECT_EFEITO122},
	{"efeito123",		MAGIC_EFFECT_EFEITO123},
	{"efeito124",		MAGIC_EFFECT_EFEITO124},
	{"efeito125",		MAGIC_EFFECT_EFEITO125},
	{"efeito126",		MAGIC_EFFECT_EFEITO126},
	{"efeito127",		MAGIC_EFFECT_EFEITO127},
	{"efeito128",		MAGIC_EFFECT_EFEITO128},
	{"efeito129",		MAGIC_EFFECT_EFEITO129},
	{"efeito130",		MAGIC_EFFECT_EFEITO130},
	{"efeito131",		MAGIC_EFFECT_EFEITO131},
	{"efeito132",		MAGIC_EFFECT_EFEITO132},
	{"efeito133",		MAGIC_EFFECT_EFEITO133},
	{"efeito134",		MAGIC_EFFECT_EFEITO134},
	{"efeito135",		MAGIC_EFFECT_EFEITO135},
	{"efeito136",		MAGIC_EFFECT_EFEITO136},
	{"efeito137",		MAGIC_EFFECT_EFEITO137},
	{"efeito138",		MAGIC_EFFECT_EFEITO138},
	{"efeito139",		MAGIC_EFFECT_EFEITO139},
	{"efeito140",		MAGIC_EFFECT_EFEITO140},
	{"efeito141",		MAGIC_EFFECT_EFEITO141},
	{"efeito142",		MAGIC_EFFECT_EFEITO142},
	{"efeito143",		MAGIC_EFFECT_EFEITO143},
	{"efeito144",		MAGIC_EFFECT_EFEITO144},
	{"efeito145",		MAGIC_EFFECT_EFEITO145},
	{"efeito146",		MAGIC_EFFECT_EFEITO146},
	{"efeito147",		MAGIC_EFFECT_EFEITO147},
	{"efeito148",		MAGIC_EFFECT_EFEITO148},
	{"efeito149",		MAGIC_EFFECT_EFEITO149},
	{"efeito150",		MAGIC_EFFECT_EFEITO150},
	{"efeito151",		MAGIC_EFFECT_EFEITO151},
	{"efeito152",		MAGIC_EFFECT_EFEITO152},
	{"efeito153",		MAGIC_EFFECT_EFEITO153},
	{"efeito154",		MAGIC_EFFECT_EFEITO154},
	{"efeito155",		MAGIC_EFFECT_EFEITO155},
	{"efeito156",		MAGIC_EFFECT_EFEITO156},
	{"efeito157",		MAGIC_EFFECT_EFEITO157},
	{"efeito158",		MAGIC_EFFECT_EFEITO158},
	{"efeito159",		MAGIC_EFFECT_EFEITO159},
	{"efeito160",		MAGIC_EFFECT_EFEITO160},
	{"efeito161",		MAGIC_EFFECT_EFEITO161},
	{"efeito162",		MAGIC_EFFECT_EFEITO162},
	{"efeito163",		MAGIC_EFFECT_EFEITO163},
	{"efeito164",		MAGIC_EFFECT_EFEITO164},
	{"efeito165",		MAGIC_EFFECT_EFEITO165},
	{"efeito166",		MAGIC_EFFECT_EFEITO166},
	{"efeito167",		MAGIC_EFFECT_EFEITO167},
	{"efeito168",		MAGIC_EFFECT_EFEITO168},
	{"efeito169",		MAGIC_EFFECT_EFEITO169},
	{"efeito170",		MAGIC_EFFECT_EFEITO170},
	{"efeito171",		MAGIC_EFFECT_EFEITO171},
	{"efeito172",		MAGIC_EFFECT_EFEITO172},
	{"efeito173",		MAGIC_EFFECT_EFEITO173},
	{"efeito174",		MAGIC_EFFECT_EFEITO174},
	{"efeito175",		MAGIC_EFFECT_EFEITO175},
	{"efeito176",		MAGIC_EFFECT_EFEITO176},
	{"efeito177",		MAGIC_EFFECT_EFEITO177},
	{"efeito178",		MAGIC_EFFECT_EFEITO178},
	{"efeito179",		MAGIC_EFFECT_EFEITO179},
	{"efeito180",		MAGIC_EFFECT_EFEITO180},
	{"efeito181",		MAGIC_EFFECT_EFEITO181},
	{"efeito182",		MAGIC_EFFECT_EFEITO182},
	{"efeito183",		MAGIC_EFFECT_EFEITO183},
	{"efeito184",		MAGIC_EFFECT_EFEITO184},
	{"efeito185",		MAGIC_EFFECT_EFEITO185},
	{"efeito186",		MAGIC_EFFECT_EFEITO186},
	{"efeito187",		MAGIC_EFFECT_EFEITO187},
	{"efeito188",		MAGIC_EFFECT_EFEITO188},
	{"efeito189",		MAGIC_EFFECT_EFEITO189},
	{"efeito190",		MAGIC_EFFECT_EFEITO190},
	{"efeito191",		MAGIC_EFFECT_EFEITO191},
	{"efeito192",		MAGIC_EFFECT_EFEITO192},
	{"efeito193",		MAGIC_EFFECT_EFEITO193},
	{"efeito194",		MAGIC_EFFECT_EFEITO194},
	{"efeito195",		MAGIC_EFFECT_EFEITO195},
	{"efeito196",		MAGIC_EFFECT_EFEITO196},
	{"efeito197",		MAGIC_EFFECT_EFEITO197},
	{"efeito198",		MAGIC_EFFECT_EFEITO198},
	{"efeito199",		MAGIC_EFFECT_EFEITO199},
	{"efeito200",		MAGIC_EFFECT_EFEITO200},
	{"efeito201",		MAGIC_EFFECT_EFEITO201},
	{"efeito202",		MAGIC_EFFECT_EFEITO202},
	{"efeito203",		MAGIC_EFFECT_EFEITO203},
	{"efeito204",		MAGIC_EFFECT_EFEITO204},
	{"efeito205",		MAGIC_EFFECT_EFEITO205},
	{"efeito206",		MAGIC_EFFECT_EFEITO206},
	{"efeito207",		MAGIC_EFFECT_EFEITO207},
	{"efeito208",		MAGIC_EFFECT_EFEITO208},
	{"efeito209",		MAGIC_EFFECT_EFEITO209},
	{"efeito210",		MAGIC_EFFECT_EFEITO210},
	{"efeito211",		MAGIC_EFFECT_EFEITO211},
	{"efeito212",		MAGIC_EFFECT_EFEITO212},
	{"efeito213",		MAGIC_EFFECT_EFEITO213},
	{"efeito214",		MAGIC_EFFECT_EFEITO214},
	{"efeito215",		MAGIC_EFFECT_EFEITO215},
	{"efeito216",		MAGIC_EFFECT_EFEITO216},
	{"efeito217",		MAGIC_EFFECT_EFEITO217},
	{"efeito218",		MAGIC_EFFECT_EFEITO218},
	{"efeito219",		MAGIC_EFFECT_EFEITO219},
	{"efeito220",		MAGIC_EFFECT_EFEITO220},
	{"efeito221",		MAGIC_EFFECT_EFEITO221},
	{"efeito222",		MAGIC_EFFECT_EFEITO222},
	{"efeito223",		MAGIC_EFFECT_EFEITO223},
	{"efeito224",		MAGIC_EFFECT_EFEITO224},
	{"efeito225",		MAGIC_EFFECT_EFEITO225},
	{"efeito226",		MAGIC_EFFECT_EFEITO226},
	{"efeito227",		MAGIC_EFFECT_EFEITO227},
	{"efeito228",		MAGIC_EFFECT_EFEITO228},
	{"efeito229",		MAGIC_EFFECT_EFEITO229},
	{"efeito230",		MAGIC_EFFECT_EFEITO230},
	{"efeito231",		MAGIC_EFFECT_EFEITO231},
	{"efeito232",		MAGIC_EFFECT_EFEITO232},
	{"efeito233",		MAGIC_EFFECT_EFEITO233},
	{"efeito234",		MAGIC_EFFECT_EFEITO234},
	{"efeito235",		MAGIC_EFFECT_EFEITO235},
	{"efeito236",		MAGIC_EFFECT_EFEITO236},
	{"efeito237",		MAGIC_EFFECT_EFEITO237},
	{"efeito238",		MAGIC_EFFECT_EFEITO238},
	{"efeito239",		MAGIC_EFFECT_EFEITO239},
	{"efeito240",		MAGIC_EFFECT_EFEITO240},
	{"efeito241",		MAGIC_EFFECT_EFEITO241},
	{"efeito242",		MAGIC_EFFECT_EFEITO242},
	{"efeito243",		MAGIC_EFFECT_EFEITO243},
	{"efeito244",		MAGIC_EFFECT_EFEITO244},
	{"efeito245",		MAGIC_EFFECT_EFEITO245},
	{"efeito246",		MAGIC_EFFECT_EFEITO246},
	{"efeito247",		MAGIC_EFFECT_EFEITO247},
	{"efeito248",		MAGIC_EFFECT_EFEITO248},
	{"efeito249",		MAGIC_EFFECT_EFEITO249},
	{"efeito250",		MAGIC_EFFECT_EFEITO250},
	{"efeito251",		MAGIC_EFFECT_EFEITO251},
	{"efeito252",		MAGIC_EFFECT_EFEITO252},
	{"efeito253",		MAGIC_EFFECT_EFEITO253},
	{"efeito254",		MAGIC_EFFECT_EFEITO254},
	{"efeito255",		MAGIC_EFFECT_EFEITO255},
	{"efeito256",		MAGIC_EFFECT_EFEITO256},
	{"efeito257",		MAGIC_EFFECT_EFEITO257},
	{"efeito258",		MAGIC_EFFECT_EFEITO258},
	{"efeito259",		MAGIC_EFFECT_EFEITO259},
	{"efeito260",		MAGIC_EFFECT_EFEITO260},
	{"efeito261",		MAGIC_EFFECT_EFEITO261},
	{"efeito262",		MAGIC_EFFECT_EFEITO262},
	{"efeito263",		MAGIC_EFFECT_EFEITO263},
	{"efeito264",		MAGIC_EFFECT_EFEITO264},
	{"efeito265",		MAGIC_EFFECT_EFEITO265},
	{"efeito266",		MAGIC_EFFECT_EFEITO266},
	{"efeito267",		MAGIC_EFFECT_EFEITO267},
	{"efeito268",		MAGIC_EFFECT_EFEITO268},
	{"efeito269",		MAGIC_EFFECT_EFEITO269},
	{"efeito270",		MAGIC_EFFECT_EFEITO270},
	{"efeito271",		MAGIC_EFFECT_EFEITO271},
	{"efeito272",		MAGIC_EFFECT_EFEITO272},
	{"efeito273",		MAGIC_EFFECT_EFEITO273},
	{"efeito274",		MAGIC_EFFECT_EFEITO274},
	{"efeito275",		MAGIC_EFFECT_EFEITO275},
	{"efeito276",		MAGIC_EFFECT_EFEITO276},
	{"efeito277",		MAGIC_EFFECT_EFEITO277},
	{"efeito278",		MAGIC_EFFECT_EFEITO278},
	{"efeito279",		MAGIC_EFFECT_EFEITO279},
	{"efeito280",		MAGIC_EFFECT_EFEITO280},
	{"efeito281",		MAGIC_EFFECT_EFEITO281},
	{"efeito282",		MAGIC_EFFECT_EFEITO282},
	{"efeito283",		MAGIC_EFFECT_EFEITO283},
	{"efeito284",		MAGIC_EFFECT_EFEITO284},
	{"efeito285",		MAGIC_EFFECT_EFEITO285},
	{"efeito286",		MAGIC_EFFECT_EFEITO286},
	{"efeito287",		MAGIC_EFFECT_EFEITO287},
	{"efeito288",		MAGIC_EFFECT_EFEITO288},
	{"efeito289",		MAGIC_EFFECT_EFEITO289},
	{"efeito290",		MAGIC_EFFECT_EFEITO290},
	{"efeito291",		MAGIC_EFFECT_EFEITO291},
	{"efeito292",		MAGIC_EFFECT_EFEITO292},
	{"efeito293",		MAGIC_EFFECT_EFEITO293},
	{"efeito294",		MAGIC_EFFECT_EFEITO294},
	{"efeito295",		MAGIC_EFFECT_EFEITO295},
	{"efeito296",		MAGIC_EFFECT_EFEITO296},
	{"efeito297",		MAGIC_EFFECT_EFEITO297},
	{"efeito298",		MAGIC_EFFECT_EFEITO298},
	{"efeito299",		MAGIC_EFFECT_EFEITO299},
	{"efeito300",		MAGIC_EFFECT_EFEITO300},
	{"efeito301",		MAGIC_EFFECT_EFEITO301},
	{"efeito302",		MAGIC_EFFECT_EFEITO302},
	{"efeito303",		MAGIC_EFFECT_EFEITO303},
	{"efeito304",		MAGIC_EFFECT_EFEITO304},
	{"efeito305",		MAGIC_EFFECT_EFEITO305},
	{"efeito306",		MAGIC_EFFECT_EFEITO306},
	{"efeito307",		MAGIC_EFFECT_EFEITO307},
	{"efeito308",		MAGIC_EFFECT_EFEITO308},
	{"efeito309",		MAGIC_EFFECT_EFEITO309},
	{"efeito310",		MAGIC_EFFECT_EFEITO310},
	{"efeito311",		MAGIC_EFFECT_EFEITO311},
	{"efeito312",		MAGIC_EFFECT_EFEITO312},
	{"efeito313",		MAGIC_EFFECT_EFEITO313},
	{"efeito314",		MAGIC_EFFECT_EFEITO314},
	{"efeito315",		MAGIC_EFFECT_EFEITO315},
	{"efeito316",		MAGIC_EFFECT_EFEITO316},
	{"efeito317",		MAGIC_EFFECT_EFEITO317},
	{"efeito318",		MAGIC_EFFECT_EFEITO318},
	{"efeito319",		MAGIC_EFFECT_EFEITO319},
	{"efeito320",		MAGIC_EFFECT_EFEITO320},
	{"efeito321",		MAGIC_EFFECT_EFEITO321},
	{"efeito322",		MAGIC_EFFECT_EFEITO322},
	{"efeito323",		MAGIC_EFFECT_EFEITO323},
	{"efeito324",		MAGIC_EFFECT_EFEITO324},
	{"efeito325",		MAGIC_EFFECT_EFEITO325},
	{"efeito326",		MAGIC_EFFECT_EFEITO326},
	{"efeito327",		MAGIC_EFFECT_EFEITO327},
	{"efeito328",		MAGIC_EFFECT_EFEITO328},
	{"efeito329",		MAGIC_EFFECT_EFEITO329},
	{"efeito330",		MAGIC_EFFECT_EFEITO330},
	{"efeito331",		MAGIC_EFFECT_EFEITO331},
	{"efeito332",		MAGIC_EFFECT_EFEITO332},
	{"efeito333",		MAGIC_EFFECT_EFEITO333},
	{"efeito334",		MAGIC_EFFECT_EFEITO334},
	{"efeito335",		MAGIC_EFFECT_EFEITO335},
	{"efeito336",		MAGIC_EFFECT_EFEITO336},
	{"efeito337",		MAGIC_EFFECT_EFEITO337},
	{"efeito338",		MAGIC_EFFECT_EFEITO338},
	{"efeito339",		MAGIC_EFFECT_EFEITO339},
	{"efeito340",		MAGIC_EFFECT_EFEITO340},
	{"efeito341",		MAGIC_EFFECT_EFEITO341},
	{"efeito342",		MAGIC_EFFECT_EFEITO342},
	{"efeito343",		MAGIC_EFFECT_EFEITO343},
	{"efeito344",		MAGIC_EFFECT_EFEITO344},
	{"efeito345",		MAGIC_EFFECT_EFEITO345},
	{"efeito346",		MAGIC_EFFECT_EFEITO346},
	{"efeito347",		MAGIC_EFFECT_EFEITO347},
	{"efeito348",		MAGIC_EFFECT_EFEITO348},
	{"efeito349",		MAGIC_EFFECT_EFEITO349},
	{"efeito350",		MAGIC_EFFECT_EFEITO350},
	{"efeito351",		MAGIC_EFFECT_EFEITO351},
	{"efeito352",		MAGIC_EFFECT_EFEITO352},
	{"efeito353",		MAGIC_EFFECT_EFEITO353},
	{"efeito354",		MAGIC_EFFECT_EFEITO354},
	{"efeito355",		MAGIC_EFFECT_EFEITO355},
	{"efeito356",		MAGIC_EFFECT_EFEITO356},
	{"efeito357",		MAGIC_EFFECT_EFEITO357},
	{"efeito358",		MAGIC_EFFECT_EFEITO358},
	{"efeito359",		MAGIC_EFFECT_EFEITO359},
	{"efeito360",		MAGIC_EFFECT_EFEITO360},
	{"efeito361",		MAGIC_EFFECT_EFEITO361},
	{"efeito362",		MAGIC_EFFECT_EFEITO362},
	{"efeito363",		MAGIC_EFFECT_EFEITO363},
	{"efeito364",		MAGIC_EFFECT_EFEITO364},
	{"efeito365",		MAGIC_EFFECT_EFEITO365},
	{"efeito366",		MAGIC_EFFECT_EFEITO366},
	{"efeito367",		MAGIC_EFFECT_EFEITO367},
	{"efeito368",		MAGIC_EFFECT_EFEITO368},
	{"efeito369",		MAGIC_EFFECT_EFEITO369},
	{"efeito370",		MAGIC_EFFECT_EFEITO370},
	{"efeito371",		MAGIC_EFFECT_EFEITO371},
	{"efeito372",		MAGIC_EFFECT_EFEITO372},
	{"efeito373",		MAGIC_EFFECT_EFEITO373},
	{"efeito374",		MAGIC_EFFECT_EFEITO374},
	{"efeito375",		MAGIC_EFFECT_EFEITO375},
	{"efeito376",		MAGIC_EFFECT_EFEITO376},
	{"efeito377",		MAGIC_EFFECT_EFEITO377},
	{"efeito378",		MAGIC_EFFECT_EFEITO378},
	{"efeito379",		MAGIC_EFFECT_EFEITO379},
	{"efeito380",		MAGIC_EFFECT_EFEITO380},
	{"efeito381",		MAGIC_EFFECT_EFEITO381},
	{"efeito382",		MAGIC_EFFECT_EFEITO382},
	{"efeito383",		MAGIC_EFFECT_EFEITO383},
	{"efeito384",		MAGIC_EFFECT_EFEITO384},
	{"efeito385",		MAGIC_EFFECT_EFEITO385},
	{"efeito386",		MAGIC_EFFECT_EFEITO386},
	{"efeito387",		MAGIC_EFFECT_EFEITO387},
	{"efeito388",		MAGIC_EFFECT_EFEITO388},
	{"efeito389",		MAGIC_EFFECT_EFEITO389},
	{"efeito390",		MAGIC_EFFECT_EFEITO390},
	{"efeito391",		MAGIC_EFFECT_EFEITO391},
	{"efeito392",		MAGIC_EFFECT_EFEITO392},
	{"efeito393",		MAGIC_EFFECT_EFEITO393},
	{"efeito394",		MAGIC_EFFECT_EFEITO394},
	{"efeito395",		MAGIC_EFFECT_EFEITO395},
	{"efeito396",		MAGIC_EFFECT_EFEITO396},
	{"efeito397",		MAGIC_EFFECT_EFEITO397},
	{"efeito398",		MAGIC_EFFECT_EFEITO398},
	{"efeito399",		MAGIC_EFFECT_EFEITO399},
	{"efeito400",		MAGIC_EFFECT_EFEITO400},
	{"efeito401",		MAGIC_EFFECT_EFEITO401},
	{"efeito402",		MAGIC_EFFECT_EFEITO402},
	{"efeito403",		MAGIC_EFFECT_EFEITO403},
	{"efeito404",		MAGIC_EFFECT_EFEITO404},
	{"efeito405",		MAGIC_EFFECT_EFEITO405},
	{"efeito406",		MAGIC_EFFECT_EFEITO406},
	{"efeito407",		MAGIC_EFFECT_EFEITO407},
	{"efeito408",		MAGIC_EFFECT_EFEITO408},
	{"efeito409",		MAGIC_EFFECT_EFEITO409},
	{"efeito410",		MAGIC_EFFECT_EFEITO410},
	{"efeito411",		MAGIC_EFFECT_EFEITO411},
	{"efeito412",		MAGIC_EFFECT_EFEITO412},
	{"efeito413",		MAGIC_EFFECT_EFEITO413},
	{"efeito414",		MAGIC_EFFECT_EFEITO414},
	{"efeito415",		MAGIC_EFFECT_EFEITO415},
	{"efeito416",		MAGIC_EFFECT_EFEITO416},
	{"efeito417",		MAGIC_EFFECT_EFEITO417},
	{"efeito418",		MAGIC_EFFECT_EFEITO418},
	{"efeito419",		MAGIC_EFFECT_EFEITO419},
	{"efeito420",		MAGIC_EFFECT_EFEITO420},
	{"efeito421",		MAGIC_EFFECT_EFEITO421},
	{"efeito422",		MAGIC_EFFECT_EFEITO422},
	{"efeito423",		MAGIC_EFFECT_EFEITO423},
	{"efeito424",		MAGIC_EFFECT_EFEITO424},
	{"efeito425",		MAGIC_EFFECT_EFEITO425},
	{"efeito426",		MAGIC_EFFECT_EFEITO426},
	{"efeito427",		MAGIC_EFFECT_EFEITO427},
	{"efeito428",		MAGIC_EFFECT_EFEITO428},
	{"efeito429",		MAGIC_EFFECT_EFEITO429},
	{"efeito430",		MAGIC_EFFECT_EFEITO430},
	{"efeito431",		MAGIC_EFFECT_EFEITO431},
    {"efeito432",		MAGIC_EFFECT_EFEITO432},
	{"efeito433",		MAGIC_EFFECT_EFEITO433},
	{"efeito434",		MAGIC_EFFECT_EFEITO434},
	{"efeito435",		MAGIC_EFFECT_EFEITO435},
	{"efeito436",		MAGIC_EFFECT_EFEITO436},
	{"efeito437",		MAGIC_EFFECT_EFEITO437},
	{"efeito438",		MAGIC_EFFECT_EFEITO438},
	{"efeito439",		MAGIC_EFFECT_EFEITO439},
	{"efeito440",		MAGIC_EFFECT_EFEITO440},
	{"efeito441",		MAGIC_EFFECT_EFEITO441},
	{"efeito442",		MAGIC_EFFECT_EFEITO442},
	{"efeito443",		MAGIC_EFFECT_EFEITO443},
	{"efeito444",		MAGIC_EFFECT_EFEITO444},
	{"efeito445",		MAGIC_EFFECT_EFEITO445},
	{"efeito446",		MAGIC_EFFECT_EFEITO446},
	{"efeito447",		MAGIC_EFFECT_EFEITO447},
	{"efeito448",		MAGIC_EFFECT_EFEITO448},
	{"efeito449",		MAGIC_EFFECT_EFEITO449},
	{"efeito450",		MAGIC_EFFECT_EFEITO450},
	{"efeito451",		MAGIC_EFFECT_EFEITO451},
	{"efeito452",		MAGIC_EFFECT_EFEITO452},
	{"efeito453",		MAGIC_EFFECT_EFEITO453},
	{"efeito454",		MAGIC_EFFECT_EFEITO454},
	{"efeito455",		MAGIC_EFFECT_EFEITO455},
	{"efeito456",		MAGIC_EFFECT_EFEITO456},
	{"efeito457",		MAGIC_EFFECT_EFEITO457},
	{"efeito458",		MAGIC_EFFECT_EFEITO458},
	{"efeito459",		MAGIC_EFFECT_EFEITO459},
	{"efeito460",		MAGIC_EFFECT_EFEITO460},
	{"efeito461",		MAGIC_EFFECT_EFEITO461},
	{"efeito462",		MAGIC_EFFECT_EFEITO462},
	{"efeito463",		MAGIC_EFFECT_EFEITO463},
	{"efeito464",		MAGIC_EFFECT_EFEITO464},
	{"efeito465",		MAGIC_EFFECT_EFEITO465},
	{"efeito466",		MAGIC_EFFECT_EFEITO466},
	{"efeito467",		MAGIC_EFFECT_EFEITO467},
	{"efeito468",		MAGIC_EFFECT_EFEITO468},
	{"efeito469",		MAGIC_EFFECT_EFEITO469},
	{"efeito470",		MAGIC_EFFECT_EFEITO470},
	{"efeito471",		MAGIC_EFFECT_EFEITO471},
	{"efeito472",		MAGIC_EFFECT_EFEITO472},
	{"efeito473",		MAGIC_EFFECT_EFEITO473},
	{"efeito474",		MAGIC_EFFECT_EFEITO474},
	{"efeito475",		MAGIC_EFFECT_EFEITO475},
	{"efeito476",		MAGIC_EFFECT_EFEITO476},
	{"efeito477",		MAGIC_EFFECT_EFEITO477},
	{"efeito478",		MAGIC_EFFECT_EFEITO478},
	{"efeito479",		MAGIC_EFFECT_EFEITO479},
	{"efeito480",		MAGIC_EFFECT_EFEITO480},
	{"efeito481",		MAGIC_EFFECT_EFEITO481},
	{"efeito482",		MAGIC_EFFECT_EFEITO482},
	{"efeito483",		MAGIC_EFFECT_EFEITO483},
	{"efeito484",		MAGIC_EFFECT_EFEITO484},
	{"efeito485",		MAGIC_EFFECT_EFEITO485},
	{"efeito486",		MAGIC_EFFECT_EFEITO486},
	{"efeito487",		MAGIC_EFFECT_EFEITO487},
	{"efeito488",		MAGIC_EFFECT_EFEITO488},
	{"efeito489",		MAGIC_EFFECT_EFEITO489},
	{"efeito490",		MAGIC_EFFECT_EFEITO490},
	{"efeito491",		MAGIC_EFFECT_EFEITO491},
	{"efeito492",		MAGIC_EFFECT_EFEITO492},
	{"efeito493",		MAGIC_EFFECT_EFEITO493},
	{"efeito494",		MAGIC_EFFECT_EFEITO494},
	{"efeito495",		MAGIC_EFFECT_EFEITO495},
	{"efeito496",		MAGIC_EFFECT_EFEITO496},
	{"efeito497",		MAGIC_EFFECT_EFEITO497},
	{"efeito498",		MAGIC_EFFECT_EFEITO498},
	{"efeito499",		MAGIC_EFFECT_EFEITO499},
	{"efeito500",		MAGIC_EFFECT_EFEITO500},
	{"efeito501",		MAGIC_EFFECT_EFEITO501},
	{"efeito502",		MAGIC_EFFECT_EFEITO502},
	{"efeito503",		MAGIC_EFFECT_EFEITO503},
	{"efeito504",		MAGIC_EFFECT_EFEITO504},
	{"efeito505",		MAGIC_EFFECT_EFEITO505},
	{"efeito506",		MAGIC_EFFECT_EFEITO506},
	{"efeito507",		MAGIC_EFFECT_EFEITO507},
	{"efeito508",		MAGIC_EFFECT_EFEITO508},
	{"efeito509",		MAGIC_EFFECT_EFEITO509},
	{"efeito510",		MAGIC_EFFECT_EFEITO510},
	{"efeito511",		MAGIC_EFFECT_EFEITO511},
	{"efeito512",		MAGIC_EFFECT_EFEITO512},
	{"efeito513",		MAGIC_EFFECT_EFEITO513},
	{"efeito514",		MAGIC_EFFECT_EFEITO514},
	{"efeito515",		MAGIC_EFFECT_EFEITO515},
	{"efeito516",		MAGIC_EFFECT_EFEITO516},
	{"efeito517",		MAGIC_EFFECT_EFEITO517},
	{"efeito518",		MAGIC_EFFECT_EFEITO518},
	{"efeito519",		MAGIC_EFFECT_EFEITO519},
	{"efeito520",		MAGIC_EFFECT_EFEITO520},
	{"efeito521",		MAGIC_EFFECT_EFEITO521},
	{"efeito522",		MAGIC_EFFECT_EFEITO522},
	{"efeito523",		MAGIC_EFFECT_EFEITO523},
	{"efeito524",		MAGIC_EFFECT_EFEITO524},
	{"efeito525",		MAGIC_EFFECT_EFEITO525},
	{"efeito526",		MAGIC_EFFECT_EFEITO526},
	{"efeito527",		MAGIC_EFFECT_EFEITO527},
	{"efeito528",		MAGIC_EFFECT_EFEITO528},
	{"efeito529",		MAGIC_EFFECT_EFEITO529},
	{"efeito530",		MAGIC_EFFECT_EFEITO530},
	{"efeito531",		MAGIC_EFFECT_EFEITO531},
	{"efeito532",		MAGIC_EFFECT_EFEITO532},
	{"efeito533",		MAGIC_EFFECT_EFEITO533},
	{"efeito534",		MAGIC_EFFECT_EFEITO534},
	{"efeito535",		MAGIC_EFFECT_EFEITO535},
	{"efeito536",		MAGIC_EFFECT_EFEITO536},
	{"efeito537",		MAGIC_EFFECT_EFEITO537},
	{"efeito538",		MAGIC_EFFECT_EFEITO538},
	{"efeito539",		MAGIC_EFFECT_EFEITO539},
	{"efeito540",		MAGIC_EFFECT_EFEITO540},
	{"efeito541",		MAGIC_EFFECT_EFEITO541},
	{"efeito542",		MAGIC_EFFECT_EFEITO542},
	{"efeito543",		MAGIC_EFFECT_EFEITO543},
	{"efeito544",		MAGIC_EFFECT_EFEITO544},
	{"efeito545",		MAGIC_EFFECT_EFEITO545},
	{"efeito546",		MAGIC_EFFECT_EFEITO546},
	{"efeito547",		MAGIC_EFFECT_EFEITO547},
	{"efeito548",		MAGIC_EFFECT_EFEITO548},
	{"efeito549",		MAGIC_EFFECT_EFEITO549},
	{"efeito550",		MAGIC_EFFECT_EFEITO550},
	{"efeito551",		MAGIC_EFFECT_EFEITO551},
	{"efeito552",		MAGIC_EFFECT_EFEITO552},
	{"efeito553",		MAGIC_EFFECT_EFEITO553},
	{"efeito554",		MAGIC_EFFECT_EFEITO554},
	{"efeito555",		MAGIC_EFFECT_EFEITO555},
	{"efeito556",		MAGIC_EFFECT_EFEITO556},
	{"efeito557",		MAGIC_EFFECT_EFEITO557},
	{"efeito558",		MAGIC_EFFECT_EFEITO558},
	{"efeito559",		MAGIC_EFFECT_EFEITO559},
	{"efeito560",		MAGIC_EFFECT_EFEITO560},
	{"efeito561",		MAGIC_EFFECT_EFEITO561},
	{"efeito562",		MAGIC_EFFECT_EFEITO562},
	{"efeito563",		MAGIC_EFFECT_EFEITO563},
	{"efeito564",		MAGIC_EFFECT_EFEITO564},
	{"efeito565",		MAGIC_EFFECT_EFEITO565},
	{"efeito566",		MAGIC_EFFECT_EFEITO566},
	{"efeito567",		MAGIC_EFFECT_EFEITO567},
	{"efeito568",		MAGIC_EFFECT_EFEITO568},
	{"efeito569",		MAGIC_EFFECT_EFEITO569},
	{"efeito570",		MAGIC_EFFECT_EFEITO570},
	{"efeito571",		MAGIC_EFFECT_EFEITO571},
	{"efeito572",		MAGIC_EFFECT_EFEITO572},
	{"efeito573",		MAGIC_EFFECT_EFEITO573},
	{"efeito574",		MAGIC_EFFECT_EFEITO574},
	{"efeito575",		MAGIC_EFFECT_EFEITO575},
	{"efeito576",		MAGIC_EFFECT_EFEITO576},
	{"efeito577",		MAGIC_EFFECT_EFEITO577},
	{"efeito578",		MAGIC_EFFECT_EFEITO578},
	{"efeito579",		MAGIC_EFFECT_EFEITO579},
	{"efeito580",		MAGIC_EFFECT_EFEITO580},
	{"efeito581",		MAGIC_EFFECT_EFEITO581},
	{"efeito582",		MAGIC_EFFECT_EFEITO582},
	{"efeito583",		MAGIC_EFFECT_EFEITO583},
	{"efeito584",		MAGIC_EFFECT_EFEITO584},
	{"efeito585",		MAGIC_EFFECT_EFEITO585},
	{"efeito586",		MAGIC_EFFECT_EFEITO586},
	{"efeito587",		MAGIC_EFFECT_EFEITO587},
	{"efeito588",		MAGIC_EFFECT_EFEITO588},
	{"efeito589",		MAGIC_EFFECT_EFEITO589},
	{"efeito590",		MAGIC_EFFECT_EFEITO590},
	{"efeito591",		MAGIC_EFFECT_EFEITO591},
	{"efeito592",		MAGIC_EFFECT_EFEITO592},
	{"efeito593",		MAGIC_EFFECT_EFEITO593},
	{"efeito594",		MAGIC_EFFECT_EFEITO594},
	{"efeito595",		MAGIC_EFFECT_EFEITO595},
	{"efeito596",		MAGIC_EFFECT_EFEITO596},
	{"efeito597",		MAGIC_EFFECT_EFEITO597},
	{"efeito598",		MAGIC_EFFECT_EFEITO598},
	{"efeito599",		MAGIC_EFFECT_EFEITO599},
	{"efeito600",		MAGIC_EFFECT_EFEITO600},
	{"efeito601",		MAGIC_EFFECT_EFEITO601},
	{"efeito602",		MAGIC_EFFECT_EFEITO602},
	{"efeito603",		MAGIC_EFFECT_EFEITO603},
	{"efeito604",		MAGIC_EFFECT_EFEITO604},
	{"efeito605",		MAGIC_EFFECT_EFEITO605},
	{"efeito606",		MAGIC_EFFECT_EFEITO606},
	{"efeito607",		MAGIC_EFFECT_EFEITO607},
	{"efeito608",		MAGIC_EFFECT_EFEITO608},
	{"efeito609",		MAGIC_EFFECT_EFEITO609},
	{"efeito610",		MAGIC_EFFECT_EFEITO610},
	{"efeito611",		MAGIC_EFFECT_EFEITO611},
	{"efeito612",		MAGIC_EFFECT_EFEITO612},
	{"efeito613",		MAGIC_EFFECT_EFEITO613},
	{"efeito614",		MAGIC_EFFECT_EFEITO614},
	{"efeito615",		MAGIC_EFFECT_EFEITO615},
	{"efeito616",		MAGIC_EFFECT_EFEITO616},
	{"efeito617",		MAGIC_EFFECT_EFEITO617},
	{"efeito618",		MAGIC_EFFECT_EFEITO618},
	{"efeito619",		MAGIC_EFFECT_EFEITO619},
	{"efeito620",		MAGIC_EFFECT_EFEITO620},
	{"efeito621",		MAGIC_EFFECT_EFEITO621},
	{"efeito622",		MAGIC_EFFECT_EFEITO622},
	{"efeito623",		MAGIC_EFFECT_EFEITO623},
	{"efeito624",		MAGIC_EFFECT_EFEITO624},
	{"efeito625",		MAGIC_EFFECT_EFEITO625},
	{"efeito626",		MAGIC_EFFECT_EFEITO626},
	{"efeito627",		MAGIC_EFFECT_EFEITO627},
	{"efeito628",		MAGIC_EFFECT_EFEITO628},
	{"efeito629",		MAGIC_EFFECT_EFEITO629},
	{"efeito630",		MAGIC_EFFECT_EFEITO630},
	{"efeito631",		MAGIC_EFFECT_EFEITO631},
	{"efeito632",		MAGIC_EFFECT_EFEITO632},
	{"efeito633",		MAGIC_EFFECT_EFEITO633},
	{"efeito634",		MAGIC_EFFECT_EFEITO634},
	{"efeito635",		MAGIC_EFFECT_EFEITO635},
	{"efeito636",		MAGIC_EFFECT_EFEITO636},
	{"efeito637",		MAGIC_EFFECT_EFEITO637},
	{"efeito638",		MAGIC_EFFECT_EFEITO638},
	{"efeito639",		MAGIC_EFFECT_EFEITO639},
	{"efeito640",		MAGIC_EFFECT_EFEITO640},
	{"efeito641",		MAGIC_EFFECT_EFEITO641},
	{"efeito642",		MAGIC_EFFECT_EFEITO642},
	{"efeito643",		MAGIC_EFFECT_EFEITO643},
	{"efeito644",		MAGIC_EFFECT_EFEITO644},
	{"efeito645",		MAGIC_EFFECT_EFEITO645},
	{"efeito646",		MAGIC_EFFECT_EFEITO646},
	{"efeito647",		MAGIC_EFFECT_EFEITO647},
	{"efeito648",		MAGIC_EFFECT_EFEITO648},
	{"efeito649",		MAGIC_EFFECT_EFEITO649},
	{"efeito650",		MAGIC_EFFECT_EFEITO650},
	{"efeito651",		MAGIC_EFFECT_EFEITO651},
	{"efeito652",		MAGIC_EFFECT_EFEITO652},
	{"efeito653",		MAGIC_EFFECT_EFEITO653},
	{"efeito654",		MAGIC_EFFECT_EFEITO654},
	{"efeito655",		MAGIC_EFFECT_EFEITO655},
	{"efeito656",		MAGIC_EFFECT_EFEITO656},
	{"efeito657",		MAGIC_EFFECT_EFEITO657},
	{"efeito658",		MAGIC_EFFECT_EFEITO658},
	{"efeito659",		MAGIC_EFFECT_EFEITO659},
	{"efeito660",		MAGIC_EFFECT_EFEITO660},
	{"efeito661",		MAGIC_EFFECT_EFEITO661},
	{"efeito662",		MAGIC_EFFECT_EFEITO662},
	{"efeito663",		MAGIC_EFFECT_EFEITO663},
	{"efeito664",		MAGIC_EFFECT_EFEITO664},
	{"efeito665",		MAGIC_EFFECT_EFEITO665},
	{"efeito666",		MAGIC_EFFECT_EFEITO666},
	{"efeito667",		MAGIC_EFFECT_EFEITO667},
	{"efeito668",		MAGIC_EFFECT_EFEITO668},
	{"efeito669",		MAGIC_EFFECT_EFEITO669},
	{"efeito670",		MAGIC_EFFECT_EFEITO670},
	{"efeito671",		MAGIC_EFFECT_EFEITO671},
	{"efeito672",		MAGIC_EFFECT_EFEITO672},
	{"efeito673",		MAGIC_EFFECT_EFEITO673},
	{"efeito674",		MAGIC_EFFECT_EFEITO674},
	{"efeito675",		MAGIC_EFFECT_EFEITO675},
	{"efeito676",		MAGIC_EFFECT_EFEITO676},
	{"efeito677",		MAGIC_EFFECT_EFEITO677},
	{"efeito678",		MAGIC_EFFECT_EFEITO678},
	{"efeito679",		MAGIC_EFFECT_EFEITO679},
	{"efeito680",		MAGIC_EFFECT_EFEITO680},
	{"efeito681",		MAGIC_EFFECT_EFEITO681},
	{"efeito682",		MAGIC_EFFECT_EFEITO682},
	{"efeito683",		MAGIC_EFFECT_EFEITO683},
	{"efeito684",		MAGIC_EFFECT_EFEITO684},
	{"efeito685",		MAGIC_EFFECT_EFEITO685},
	{"efeito686",		MAGIC_EFFECT_EFEITO686},
	{"efeito687",		MAGIC_EFFECT_EFEITO687},
	{"efeito688",		MAGIC_EFFECT_EFEITO688},
	{"efeito689",		MAGIC_EFFECT_EFEITO689},
	{"efeito690",		MAGIC_EFFECT_EFEITO690},
	{"efeito691",		MAGIC_EFFECT_EFEITO691},
	{"efeito692",		MAGIC_EFFECT_EFEITO692},
	{"efeito693",		MAGIC_EFFECT_EFEITO693},
	{"efeito694",		MAGIC_EFFECT_EFEITO694},
	{"efeito695",		MAGIC_EFFECT_EFEITO695},
	{"efeito696",		MAGIC_EFFECT_EFEITO696},
	{"efeito697",		MAGIC_EFFECT_EFEITO697},
	{"efeito698",		MAGIC_EFFECT_EFEITO698},
	{"efeito699",		MAGIC_EFFECT_EFEITO699},
	{"efeito700",		MAGIC_EFFECT_EFEITO700}
};

ShootTypeNames shootTypeNames[] =
{
	{"spear",		SHOOT_EFFECT_SPEAR},
	{"bolt",		SHOOT_EFFECT_BOLT},
	{"arrow",		SHOOT_EFFECT_ARROW},
	{"fire",		SHOOT_EFFECT_FIRE},
	{"energy",		SHOOT_EFFECT_ENERGY},
	{"poisonarrow",		SHOOT_EFFECT_POISONARROW},
	{"burstarrow",		SHOOT_EFFECT_BURSTARROW},
	{"throwingstar",	SHOOT_EFFECT_THROWINGSTAR},
	{"throwingknife",	SHOOT_EFFECT_THROWINGKNIFE},
	{"smallstone",		SHOOT_EFFECT_SMALLSTONE},
	{"death",		SHOOT_EFFECT_DEATH},
	{"largerock",		SHOOT_EFFECT_LARGEROCK},
	{"snowball",		SHOOT_EFFECT_SNOWBALL},
	{"powerbolt",		SHOOT_EFFECT_POWERBOLT},
	{"poison",		SHOOT_EFFECT_POISONFIELD},
	{"infernalbolt",	SHOOT_EFFECT_INFERNALBOLT},
	{"huntingspear",	SHOOT_EFFECT_HUNTINGSPEAR},
	{"enchantedspear",	SHOOT_EFFECT_ENCHANTEDSPEAR},
	{"redstar",		SHOOT_EFFECT_REDSTAR},
	{"greenstar",		SHOOT_EFFECT_GREENSTAR},
	{"royalspear",		SHOOT_EFFECT_ROYALSPEAR},
	{"sniperarrow",		SHOOT_EFFECT_SNIPERARROW},
	{"onyxarrow",		SHOOT_EFFECT_ONYXARROW},
	{"piercingbolt",	SHOOT_EFFECT_PIERCINGBOLT},
	{"whirlwindsword",	SHOOT_EFFECT_WHIRLWINDSWORD},
	{"whirlwindaxe",	SHOOT_EFFECT_WHIRLWINDAXE},
	{"whirlwindclub",	SHOOT_EFFECT_WHIRLWINDCLUB},
	{"etherealspear",	SHOOT_EFFECT_ETHEREALSPEAR},
	{"ice",			SHOOT_EFFECT_ICE},
	{"earth",		SHOOT_EFFECT_EARTH},
	{"holy",		SHOOT_EFFECT_HOLY},
	{"suddendeath",		SHOOT_EFFECT_SUDDENDEATH},
	{"flasharrow",		SHOOT_EFFECT_FLASHARROW},
	{"flammingarrow",	SHOOT_EFFECT_FLAMMINGARROW},
	{"flamingarrow",	SHOOT_EFFECT_FLAMMINGARROW},
	{"shiverarrow",		SHOOT_EFFECT_SHIVERARROW},
	{"energyball",		SHOOT_EFFECT_ENERGYBALL},
	{"smallice",		SHOOT_EFFECT_SMALLICE},
	{"smallholy",		SHOOT_EFFECT_SMALLHOLY},
	{"smallearth",		SHOOT_EFFECT_SMALLEARTH},
	{"eartharrow",		SHOOT_EFFECT_EARTHARROW},
	{"explosion",		SHOOT_EFFECT_EXPLOSION},
	{"cake",		SHOOT_EFFECT_CAKE},
	{"efeito42",		SHOOT_EFFECT_EFEITO42},
	{"efeito43",		SHOOT_EFFECT_EFEITO43},
	{"efeito44",		SHOOT_EFFECT_EFEITO44},
	{"efeito45",		SHOOT_EFFECT_EFEITO45},
	{"efeito46",		SHOOT_EFFECT_EFEITO46},
	{"efeito47",		SHOOT_EFFECT_EFEITO47},
	{"efeito48",		SHOOT_EFFECT_EFEITO48},
	{"efeito49",		SHOOT_EFFECT_EFEITO49},
	{"efeito50",		SHOOT_EFFECT_EFEITO50},
	{"efeito51",		SHOOT_EFFECT_EFEITO51},
	{"efeito52",		SHOOT_EFFECT_EFEITO52},
	{"efeito53",		SHOOT_EFFECT_EFEITO53},
	{"efeito54",		SHOOT_EFFECT_EFEITO54},
	{"efeito55",		SHOOT_EFFECT_EFEITO55},
	{"efeito56",		SHOOT_EFFECT_EFEITO56},
	{"efeito57",		SHOOT_EFFECT_EFEITO57},
	{"efeito58",		SHOOT_EFFECT_EFEITO58},
	{"efeito59",		SHOOT_EFFECT_EFEITO59},
	{"efeito60",		SHOOT_EFFECT_EFEITO60},
	{"efeito61",		SHOOT_EFFECT_EFEITO61},
	{"efeito62",		SHOOT_EFFECT_EFEITO62},
	{"efeito63",		SHOOT_EFFECT_EFEITO63},
	{"efeito64",		SHOOT_EFFECT_EFEITO64},
	{"efeito65",		SHOOT_EFFECT_EFEITO65},
	{"efeito66",		SHOOT_EFFECT_EFEITO66},
	{"efeito67",		SHOOT_EFFECT_EFEITO67},
	{"efeito68",		SHOOT_EFFECT_EFEITO68},
	{"efeito69",		SHOOT_EFFECT_EFEITO69},
	{"efeito70",		SHOOT_EFFECT_EFEITO70},
	{"efeito71",		SHOOT_EFFECT_EFEITO71},
	{"efeito72",		SHOOT_EFFECT_EFEITO72},
	{"efeito73",		SHOOT_EFFECT_EFEITO73},
	{"efeito74",		SHOOT_EFFECT_EFEITO74},
	{"efeito75",		SHOOT_EFFECT_EFEITO75},
	{"efeito76",		SHOOT_EFFECT_EFEITO76},
	{"efeito77",		SHOOT_EFFECT_EFEITO77},
	{"efeito78",		SHOOT_EFFECT_EFEITO78},
	{"efeito79",		SHOOT_EFFECT_EFEITO79},
	{"efeito80",		SHOOT_EFFECT_EFEITO80},
	{"efeito81",		SHOOT_EFFECT_EFEITO81},
	{"efeito82",		SHOOT_EFFECT_EFEITO82},
	{"efeito83",		SHOOT_EFFECT_EFEITO83},
	{"efeito84",		SHOOT_EFFECT_EFEITO84},
	{"efeito85",		SHOOT_EFFECT_EFEITO85},
	{"efeito86",		SHOOT_EFFECT_EFEITO86},
	{"efeito87",		SHOOT_EFFECT_EFEITO87},
	{"efeito88",		SHOOT_EFFECT_EFEITO88},
	{"efeito89",		SHOOT_EFFECT_EFEITO89},
	{"efeito90",		SHOOT_EFFECT_EFEITO90},
	{"efeito91",		SHOOT_EFFECT_EFEITO91},
	{"efeito92",		SHOOT_EFFECT_EFEITO92},
	{"efeito93",		SHOOT_EFFECT_EFEITO93},
	{"efeito94",		SHOOT_EFFECT_EFEITO94},
	{"efeito95",		SHOOT_EFFECT_EFEITO95},
	{"efeito96",		SHOOT_EFFECT_EFEITO96},
	{"efeito97",		SHOOT_EFFECT_EFEITO97},
	{"efeito98",		SHOOT_EFFECT_EFEITO98},
	{"efeito99",		SHOOT_EFFECT_EFEITO99},
	{"efeito100",		SHOOT_EFFECT_EFEITO100},
	{"efeito101",		SHOOT_EFFECT_EFEITO101},
	{"efeito102",		SHOOT_EFFECT_EFEITO102},
	{"efeito103",		SHOOT_EFFECT_EFEITO103},
	{"efeito104",		SHOOT_EFFECT_EFEITO104},
	{"efeito105",		SHOOT_EFFECT_EFEITO105},
	{"efeito106",		SHOOT_EFFECT_EFEITO106},
	{"efeito107",		SHOOT_EFFECT_EFEITO107},
	{"efeito108",		SHOOT_EFFECT_EFEITO108},
	{"efeito109",		SHOOT_EFFECT_EFEITO109},
	{"efeito110",		SHOOT_EFFECT_EFEITO110},
	{"efeito111",		SHOOT_EFFECT_EFEITO111},
	{"efeito112",		SHOOT_EFFECT_EFEITO112},
	{"efeito113",		SHOOT_EFFECT_EFEITO113},
	{"efeito114",		SHOOT_EFFECT_EFEITO114},
	{"efeito115",		SHOOT_EFFECT_EFEITO115},
	{"efeito116",		SHOOT_EFFECT_EFEITO116},
	{"efeito117",		SHOOT_EFFECT_EFEITO117},
	{"efeito118",		SHOOT_EFFECT_EFEITO118},
	{"efeito119",		SHOOT_EFFECT_EFEITO119},
	{"efeito120",		SHOOT_EFFECT_EFEITO120},
	{"efeito121",		SHOOT_EFFECT_EFEITO121},
	{"efeito122",		SHOOT_EFFECT_EFEITO122},
	{"efeito123",		SHOOT_EFFECT_EFEITO123},
	{"efeito124",		SHOOT_EFFECT_EFEITO124},
	{"efeito125",		SHOOT_EFFECT_EFEITO125},
	{"efeito126",		SHOOT_EFFECT_EFEITO126},
	{"efeito127",		SHOOT_EFFECT_EFEITO127},
	{"efeito128",		SHOOT_EFFECT_EFEITO128},
	{"efeito129",		SHOOT_EFFECT_EFEITO129},
	{"efeito130",		SHOOT_EFFECT_EFEITO130},
	{"efeito131",		SHOOT_EFFECT_EFEITO131},
	{"efeito132",		SHOOT_EFFECT_EFEITO132},
	{"efeito133",		SHOOT_EFFECT_EFEITO133},
	{"efeito134",		SHOOT_EFFECT_EFEITO134},
	{"efeito135",		SHOOT_EFFECT_EFEITO135},
	{"efeito136",		SHOOT_EFFECT_EFEITO136},
	{"efeito137",		SHOOT_EFFECT_EFEITO137},
	{"efeito138",		SHOOT_EFFECT_EFEITO138},
	{"efeito139",		SHOOT_EFFECT_EFEITO139},
	{"efeito140",		SHOOT_EFFECT_EFEITO140},
	{"efeito141",		SHOOT_EFFECT_EFEITO141},
	{"efeito142",		SHOOT_EFFECT_EFEITO142},
	{"efeito143",		SHOOT_EFFECT_EFEITO143},
	{"efeito144",		SHOOT_EFFECT_EFEITO144},
	{"efeito145",		SHOOT_EFFECT_EFEITO145},
	{"efeito146",		SHOOT_EFFECT_EFEITO146},
	{"efeito147",		SHOOT_EFFECT_EFEITO147},
	{"efeito148",		SHOOT_EFFECT_EFEITO148},
	{"efeito149",		SHOOT_EFFECT_EFEITO149},
	{"efeito150",		SHOOT_EFFECT_EFEITO150},
	{"efeito151",		SHOOT_EFFECT_EFEITO151}
};

CombatTypeNames combatTypeNames[] =
{
	{"physical",		COMBAT_PHYSICALDAMAGE},
	{"energy",		COMBAT_ENERGYDAMAGE},
	{"earth",		COMBAT_EARTHDAMAGE},
	{"poison",		COMBAT_POISONDAMAGE},
	{"fire",		COMBAT_FIREDAMAGE},
	{"undefined",		COMBAT_UNDEFINEDDAMAGE},
	{"lifedrain",		COMBAT_LIFEDRAIN},
	{"life drain",		COMBAT_LIFEDRAIN},
	{"manadrain",		COMBAT_MANADRAIN},
	{"mana drain",		COMBAT_MANADRAIN},
	{"healing",		COMBAT_HEALING},
	{"drown",		COMBAT_DROWNDAMAGE},
	{"ice",			COMBAT_ICEDAMAGE},
	{"holy",		COMBAT_HOLYDAMAGE},
	{"death",		COMBAT_DEATHDAMAGE},
	{"wind",		COMBAT_WINDDAMAGE}
};

AmmoTypeNames ammoTypeNames[] =
{
	{"spear",		AMMO_SPEAR},
	{"arrow",		AMMO_ARROW},
	{"poisonarrow",		AMMO_ARROW},
	{"burstarrow",		AMMO_ARROW},
	{"bolt",		AMMO_BOLT},
	{"powerbolt",		AMMO_BOLT},
	{"smallstone",		AMMO_STONE},
	{"largerock",		AMMO_STONE},
	{"throwingstar",	AMMO_THROWINGSTAR},
	{"throwingknife",	AMMO_THROWINGKNIFE},
	{"snowball",		AMMO_SNOWBALL},
	{"huntingspear",	AMMO_SPEAR},
	{"royalspear",		AMMO_SPEAR},
	{"enchantedspear",	AMMO_SPEAR},
	{"sniperarrow",		AMMO_ARROW},
	{"onyxarrow",		AMMO_ARROW},
	{"piercingbolt",	AMMO_BOLT},
	{"infernalbolt",	AMMO_BOLT},
	{"flasharrow",		AMMO_ARROW},
	{"flammingarrow",	AMMO_ARROW},
	{"flamingarrow",	AMMO_ARROW},
	{"shiverarrow",		AMMO_ARROW},
	{"eartharrow",		AMMO_ARROW},
	{"etherealspear",	AMMO_SPEAR}
};

AmmoActionNames ammoActionNames[] =
{
	{"move",		AMMOACTION_MOVE},
	{"moveback",		AMMOACTION_MOVEBACK},
	{"move back",		AMMOACTION_MOVEBACK},
	{"removecharge",	AMMOACTION_REMOVECHARGE},
	{"remove charge",	AMMOACTION_REMOVECHARGE},
	{"removecount",		AMMOACTION_REMOVECOUNT},
	{"remove count",	AMMOACTION_REMOVECOUNT}
};

FluidTypeNames fluidTypeNames[] =
{
	{"none",		FLUID_NONE},
	{"water",		FLUID_WATER},
	{"blood",		FLUID_BLOOD},
	{"beer",		FLUID_BEER},
	{"slime",		FLUID_SLIME},
	{"lemonade",		FLUID_LEMONADE},
	{"milk",		FLUID_MILK},
	{"mana",		FLUID_MANA},
	{"life",		FLUID_LIFE},
	{"oil",			FLUID_OIL},
	{"urine",		FLUID_URINE},
	{"coconutmilk",		FLUID_COCONUTMILK},
	{"coconut milk",	FLUID_COCONUTMILK},
	{"wine",		FLUID_WINE},
	{"mud",			FLUID_MUD},
	{"fruitjuice",		FLUID_FRUITJUICE},
	{"fruit juice",		FLUID_FRUITJUICE},
	{"lava",		FLUID_LAVA},
	{"rum",			FLUID_RUM},
	{"swamp",		FLUID_SWAMP}
};

SkillIdNames skillIdNames[] =
{
	{"fist",		SKILL_FIST},
	{"sword",		SKILL_SWORD},
	{"axe",		SKILL_AXE},
	{"club",			SKILL_CLUB},
	{"distance",		SKILL_DIST},
	{"dist",		SKILL_DIST},
	{"shielding",		SKILL_SHIELD},
	{"shield",		SKILL_SHIELD},
	{"fishing",		SKILL_FISH},
	{"fish",		SKILL_FISH},
	{"level",		SKILL__LEVEL},
	{"magiclevel",		SKILL__MAGLEVEL},
	{"magic level",		SKILL__MAGLEVEL}
};

MagicEffect_t getMagicEffect(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(magicEffectNames) / sizeof(MagicEffectNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), magicEffectNames[i].name))
			return magicEffectNames[i].magicEffect;
	}

	return MAGIC_EFFECT_UNKNOWN;
}

ShootEffect_t getShootType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(shootTypeNames) / sizeof(ShootTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), shootTypeNames[i].name))
			return shootTypeNames[i].shootType;
	}

	return SHOOT_EFFECT_UNKNOWN;
}

CombatType_t getCombatType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(combatTypeNames) / sizeof(CombatTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), combatTypeNames[i].name))
			return combatTypeNames[i].combatType;
	}

	return COMBAT_NONE;
}

Ammo_t getAmmoType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoTypeNames) / sizeof(AmmoTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), ammoTypeNames[i].name))
			return ammoTypeNames[i].ammoType;
	}

	return AMMO_NONE;
}

AmmoAction_t getAmmoAction(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(ammoActionNames) / sizeof(AmmoActionNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), ammoActionNames[i].name))
			return ammoActionNames[i].ammoAction;
	}

	return AMMOACTION_NONE;
}

FluidTypes_t getFluidType(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(fluidTypeNames) / sizeof(FluidTypeNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), fluidTypeNames[i].name))
			return fluidTypeNames[i].fluidType;
	}

	return FLUID_NONE;
}

skills_t getSkillId(const std::string& strValue)
{
	for(uint32_t i = 0; i < sizeof(skillIdNames) / sizeof(SkillIdNames); ++i)
	{
		if(!strcasecmp(strValue.c_str(), skillIdNames[i].name))
			return skillIdNames[i].skillId;
	}

	return SKILL_FIST;
}

std::string getCombatName(CombatType_t combatType)
{
	switch(combatType)
	{
		case COMBAT_PHYSICALDAMAGE:
			return "physical";
		case COMBAT_ENERGYDAMAGE:
			return "energy";
		case COMBAT_EARTHDAMAGE:
			return "earth";
		case COMBAT_POISONDAMAGE:
			return "poison";
		case COMBAT_FIREDAMAGE:
			return "fire";
		case COMBAT_UNDEFINEDDAMAGE:
			return "undefined";
		case COMBAT_LIFEDRAIN:
			return "life drain";
		case COMBAT_MANADRAIN:
			return "mana drain";
		case COMBAT_HEALING:
			return "healing";
		case COMBAT_DROWNDAMAGE:
			return "drown";
		case COMBAT_ICEDAMAGE:
			return "ice";
		case COMBAT_HOLYDAMAGE:
			return "holy";
		case COMBAT_DEATHDAMAGE:
			return "death";
		case COMBAT_WINDDAMAGE:
			return "wind";		
		default:
			break;
	}

	return "unknown";
}

std::string getSkillName(uint16_t skillId, bool suffix/* = true*/)
{
	switch(skillId)
	{
		case SKILL_FIST:
		{
			std::string tmp = "fist";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SWORD:
		{
			std::string tmp = "sword";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_AXE:
		{
			std::string tmp = "axe";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_CLUB:
		{
			std::string tmp = "club";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_DIST:
		{
			std::string tmp = "distance";
			if(suffix)
				tmp += " fighting";

			return tmp;
		}
		case SKILL_SHIELD:
			return "shield";
		case SKILL_FISH:
			return "fish";
		case SKILL__MAGLEVEL:
			return "magic level";
		case SKILL__LEVEL:
			return "level";
		default:
			break;
	}

	return "unknown";
}

std::string getReason(int32_t reasonId)
{
	switch(reasonId)
	{
		case 0:
			return "Offensive Name";
		case 1:
			return "Invalid Name Format";
		case 2:
			return "Unsuitable Name";
		case 3:
			return "Name Inciting Rule Violation";
		case 4:
			return "Offensive Statement";
		case 5:
			return "Spamming";
		case 6:
			return "Illegal Advertising";
		case 7:
			return "Off-Topic Public Statement";
		case 8:
			return "Non-English Public Statement";
		case 9:
			return "Inciting Rule Violation";
		case 10:
			return "Bug Abuse";
		case 11:
			return "Game Weakness Abuse";
		case 12:
			return "Using Unofficial Software to Play";
		case 13:
			return "Hacking";
		case 14:
			return "Multi-Clienting";
		case 15:
			return "Account Trading or Sharing";
		case 16:
			return "Threatening Gamemaster";
		case 17:
			return "Pretending to Have Influence on Rule Enforcement";
		case 18:
			return "False Report to Gamemaster";
		case 19:
			return "Destructive Behaviour";
		case 20:
			return "Excessive Unjustified Player Killing";
		default:
			break;
	}

	return "Unknown Reason";
}

std::string getAction(ViolationAction_t actionId, bool ipBanishment)
{
	std::string action = "Unknown";
	switch(actionId)
	{
		case ACTION_NOTATION:
			action = "Notation";
			break;
		case ACTION_NAMEREPORT:
			action = "Name Report";
			break;
		case ACTION_BANISHMENT:
			action = "Banishment";
			break;
		case ACTION_BANREPORT:
			action = "Name Report + Banishment";
			break;
		case ACTION_BANFINAL:
			action = "Banishment + Final Warning";
			break;
		case ACTION_BANREPORTFINAL:
			action = "Name Report + Banishment + Final Warning";
			break;
		case ACTION_STATEMENT:
			action = "Statement Report";
			break;
		//internal use
		case ACTION_DELETION:
			action = "Deletion";
			break;
		case ACTION_NAMELOCK:
			action = "Name Lock";
			break;
		case ACTION_BANLOCK:
			action = "Name Lock + Banishment";
			break;
		case ACTION_BANLOCKFINAL:
			action = "Name Lock + Banishment + Final Warning";
			break;
		default:
			break;
	}

	if(ipBanishment)
		action += " + IP Banishment";

	return action;
}

std::string parseVocationString(StringVec vocStringVec)
{
	std::string str = "";
	if(!vocStringVec.empty())
	{
		for(StringVec::iterator it = vocStringVec.begin(); it != vocStringVec.end(); ++it)
		{
			if((*it) != vocStringVec.front())
			{
				if((*it) != vocStringVec.back())
					str += ", ";
				else
					str += " and ";
			}

			str += (*it);
			str += "s";
		}
	}

	return str;
}

bool parseVocationNode(xmlNodePtr vocationNode, VocationMap& vocationMap, StringVec& vocStringVec, std::string& errorStr)
{
	if(xmlStrcmp(vocationNode->name,(const xmlChar*)"vocation"))
		return true;

	int32_t vocationId = -1;
	std::string strValue, tmpStrValue;
	if(readXMLString(vocationNode, "name", strValue))
	{
		vocationId = Vocations::getInstance()->getVocationId(strValue);
		if(vocationId != -1)
		{
			vocationMap[vocationId] = true;
			int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
			if(promotedVocation != -1)
				vocationMap[promotedVocation] = true;
		}
		else
		{
			errorStr = "Wrong vocation name: " + strValue;
			return false;
		}
	}
	else if(readXMLString(vocationNode, "id", strValue))
	{
		IntegerVec intVector;
		if(!parseIntegerVec(strValue, intVector))
		{
			errorStr = "Invalid vocation id - '" + strValue + "'";
			return false;
		}

		size_t size = intVector.size();
		for(size_t i = 0; i < size; ++i)
		{
			Vocation* vocation = Vocations::getInstance()->getVocation(intVector[i]);
			if(vocation && vocation->getName() != "")
			{
				vocationId = vocation->getId();
				strValue = vocation->getName();

				vocationMap[vocationId] = true;
				int32_t promotedVocation = Vocations::getInstance()->getPromotedVocation(vocationId);
				if(promotedVocation != -1)
					vocationMap[promotedVocation] = true;
			}
			else
			{
				std::stringstream ss;
				ss << "Wrong vocation id: " << intVector[i];

				errorStr = ss.str();
				return false;
			}
		}
	}

	if(vocationId != -1 && (!readXMLString(vocationNode, "showInDescription", tmpStrValue) || booleanString(tmpStrValue)))
		vocStringVec.push_back(asLowerCaseString(strValue));

	return true;
}

bool parseIntegerVec(std::string str, IntegerVec& intVector)
{
	StringVec strVector = explodeString(str, ";");
	IntegerVec tmpIntVector;
	for(StringVec::iterator it = strVector.begin(); it != strVector.end(); ++it)
	{
		tmpIntVector = vectorAtoi(explodeString((*it), "-"));
		if(!tmpIntVector[0] && it->substr(0, 1) != "0")
			continue;

		intVector.push_back(tmpIntVector[0]);
		if(tmpIntVector.size() > 1)
		{
			while(tmpIntVector[0] < tmpIntVector[1])
				intVector.push_back(++tmpIntVector[0]);
		}
	}

	return true;
}

bool fileExists(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	if(!f)
		return false;

	fclose(f);
	return true;
}

uint32_t adlerChecksum(uint8_t *data, size_t length)
{
	if(length > NETWORKMESSAGE_MAXSIZE || length < 0)
		return 0;

	const uint16_t adler = 65521;
	uint32_t a = 1, b = 0;
	while(length > 0)
	{
		size_t tmp = length > 5552 ? 5552 : length;
		length -= tmp;
		do
		{
			a += *data++;
			b += a;
		}
		while(--tmp);

		a %= adler;
		b %= adler;
	}

	return (b << 16) | a;
}

std::string getFilePath(FileType_t filetype, std::string filename)
{
	#ifdef __FILESYSTEM_HIERARCHY_STANDARD__
	std::string path = "/usr/share/tfs/";
	#endif
	std::string path = g_config.getString(ConfigManager::DATA_DIRECTORY);
	switch(filetype)
	{
		case FILE_TYPE_OTHER:
			path += filename;
			break;
		case FILE_TYPE_XML:
			path += "XML/" + filename;
			break;
		case FILE_TYPE_LOG:
			#ifndef __FILESYSTEM_HIERARCHY_STANDARD__
			path += "logs/" + filename;
			#else
			path = "/var/log/tfs/" + filename;
			#endif
			break;
		case FILE_TYPE_MOD:
		{
			#ifndef __FILESYSTEM_HIERARCHY_STANDARD__
			path = "mods/" + filename;
			#else
			path = "/etc/tfs/mods/" + filename;
			#endif
			break;
		}
		case FILE_TYPE_CONFIG:
		{
			#if defined(__FILESYSTEM_HIERARCHY_STANDARD__) && defined(__HOMEDIR_CONF__)
			if(fileExists("~/.tfs/" + filename))
				path = "~/.tfs/" + filename;
			else
				path = "/etc/tfs/" + filename;

			#elif defined(__FILESYSTEM_HIERARCHY_STANDARD__)
			path = "/etc/tfs/" + filename;
			#else
			path = filename;
			#endif
			break;
		}
		default:
			std::cout << "ERROR: Wrong file type!" << std::endl;
			break;
	}
	return path;
}
