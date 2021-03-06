#ifndef PARAMETER_TYPE_IDS_H
#define PARAMETER_TYPE_IDS_H

#include <vector>

class Parameters {
public:
	enum {
		YAW_KP = 0x000000,
		YAW_KI = 0x000001,
		YAW_KD = 0x000002,
		YAW_ILIMIT = 0x000003,
		YAW_RESOLUTIONFILTER = 0x000004,
		YAW_AVERAGINGFILTER = 0x000005,
		ROLL_KP = 0x000006,
		ROLL_KI = 0x000007,
		ROLL_KD = 0x000008,
		ROLL_ILIMIT = 0x000009,
		ROLL_RESOLUTIONFILTER = 0x00000a,
		ROLL_AVERAGINGFILTER = 0x00000b,
		PITCH_KP = 0x00000c,
		PITCH_KI = 0x00000d,
		PITCH_KD = 0x00000e,
		PITCH_ILIMIT = 0x00000f,
		PITCH_RESOLUTIONFILTER = 0x000010,
		PITCH_AVERAGINGFILTER = 0x000011,
		MISC_ACC_HORIZ_KI = 0x000012,
		MISC_ACC_VERT_KI = 0x000013,
		MISC_COMPASS_KI = 0x000014,
		MISC_IDLE_SPEED = 0x000015,
		MISC_START_THRESHOLD = 0x000016,
		MISC_STOP_THRESHOLD = 0x000017,
		MISC_SKIP_CONTROL_CYCLES = 0x000018,
		MISC_ACC_RANGE = 0x000019,
		SPECIAL_BATT_VOLTAGE = 0x00001a
	};
	static std::vector<int> getParameterVector() {
		std::vector<int> v;
		v.push_back(0x000000);
		v.push_back(0x000001);
		v.push_back(0x000002);
		v.push_back(0x000003);
		v.push_back(0x000004);
		v.push_back(0x000005);
		v.push_back(0x000006);
		v.push_back(0x000007);
		v.push_back(0x000008);
		v.push_back(0x000009);
		v.push_back(0x00000a);
		v.push_back(0x00000b);
		v.push_back(0x00000c);
		v.push_back(0x00000d);
		v.push_back(0x00000e);
		v.push_back(0x00000f);
		v.push_back(0x000010);
		v.push_back(0x000011);
		v.push_back(0x000012);
		v.push_back(0x000013);
		v.push_back(0x000014);
		v.push_back(0x000015);
		v.push_back(0x000016);
		v.push_back(0x000017);
		v.push_back(0x000018);
		v.push_back(0x000019);
		v.push_back(0x00001a);
		return v;
	}
};

#endif // PARAMETER_TYPE_IDS_H
