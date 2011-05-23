#include "helper_functions.h"

QByteArray intToQByteArray(uint32_t integer, int numberOfBytes)
{
	QByteArray tmp;
	tmp.resize(numberOfBytes);

	for (int i = 0; i < sizeof(integer); i++)
	{
		if (i >= sizeof(integer) - numberOfBytes)
			tmp[(int) (i - sizeof(integer) + numberOfBytes)] = integer >> 24;

		integer<<= 8;
	}

	return tmp;
}

uint32_t QByteArrayToInt(QByteArray bytes)
{
	uint32_t theInt = 0;

	for (int i = 0; i < bytes.length(); i++)
		theInt+= bytes.at(i) << 8 * (bytes.length() - 1 - i);

	return theInt;
}
