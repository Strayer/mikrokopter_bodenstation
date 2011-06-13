#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <QByteArray>
#include <stdint.h>

QByteArray intToQByteArray(uint32_t integer, int numberOfBytes);
uint32_t QByteArrayToInt(QByteArray bytes);
QString ParameterTypeIdToString(uint16_t typeId);

#endif // HELPER_FUNCTIONS_H
