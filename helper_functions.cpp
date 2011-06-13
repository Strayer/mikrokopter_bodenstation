#include "helper_functions.h"
#include "messages/parameter_type_ids.h"

#include <QByteArray>
#include <QString>

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
		theInt+= (unsigned char) bytes.at(i) << (8 * (bytes.length() - 1 - i));

	return theInt;
}

QString ParameterTypeIdToString(uint16_t typeId)
{
	if (typeId == Parameters::MISC_ACC_HORIZ_KI)
		return QString("MISC_ACC_HORIZ_KI");
	else if (typeId == Parameters::MISC_ACC_VERT_KI)
		return QString("MISC_ACC_VERT_KI");
	else if (typeId == Parameters::MISC_COMPASS_KI)
		return QString("MISC_COMPASS_KI");
	else if (typeId == Parameters::MISC_IDLE_SPEED)
		return QString("MISC_IDLE_SPEED");
	else if (typeId == Parameters::MISC_SKIP_CONTROL_CYCLES)
		return QString("MISC_SKIP_CONTROL_CYCLES");
	else if (typeId == Parameters::MISC_START_THRESHOLD)
		return QString("MISC_START_THRESHOLD");
	else if (typeId == Parameters::MISC_STOP_THRESHOLD)
		return QString("MISC_STOP_THRESHOLD");
	else if (typeId == Parameters::PITCH_AVERAGINGFILTER)
		return QString("PITCH_AVERAGINGFILTER");
	else if (typeId == Parameters::PITCH_ILIMIT)
		return QString("PITCH_ILIMIT");
	else if (typeId == Parameters::PITCH_KD)
		return QString("PITCH_KD");
	else if (typeId == Parameters::PITCH_KI)
		return QString("PITCH_KI");
	else if (typeId == Parameters::PITCH_KP)
		return QString("PITCH_KP");
	else if (typeId == Parameters::PITCH_RESOLUTIONFILTER)
		return QString("PITCH_RESOLUTIONFILTER");
	else if (typeId == Parameters::ROLL_AVERAGINGFILTER)
		return QString("ROLL_AVERAGINGFILTER");
	else if (typeId == Parameters::ROLL_ILIMIT)
		return QString("ROLL_ILIMIT");
	else if (typeId == Parameters::ROLL_KD)
		return QString("ROLL_KD");
	else if (typeId == Parameters::ROLL_KI)
		return QString("ROLL_KI");
	else if (typeId == Parameters::ROLL_KP)
		return QString("ROLL_KP");
	else if (typeId == Parameters::ROLL_RESOLUTIONFILTER)
		return QString("ROLL_RESOLUTIONFILTER");
	else if (typeId == Parameters::YAW_AVERAGINGFILTER)
		return QString("YAW_AVERAGINGFILTER");
	else if (typeId == Parameters::YAW_ILIMIT)
		return QString("YAW_ILIMIT");
	else if (typeId == Parameters::YAW_KD)
		return QString("YAW_KD");
	else if (typeId == Parameters::YAW_KI)
		return QString("YAW_KI");
	else if (typeId == Parameters::YAW_KP)
		return QString("YAW_KP");
	else if (typeId == Parameters::YAW_RESOLUTIONFILTER)
		return QString("YAW_RESOLUTIONFILTER");

	return QString();
}
