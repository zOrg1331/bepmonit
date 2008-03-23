#include "data.h"

DATA::DATA(log *Logger, statdata *Stats) {
	logger = Logger;
	stats = Stats;

	LdefState = true;
// 	LdefOff = false;

// 	ACOff = false;
	ACU = 0.0;
// 	ACHz = 0.0;

	KNSOff[1] = false;
	KNSOff[2] = false;
	KNSOff[3] = false;
	KNSOff[4] = false;

// 	KNSNorma[1] = true;
// 	KNSNorma[2] = true;
// 	KNSNorma[3] = true;
// 	KNSNorma[4] = true;

	KNSAvar[1] = false;
	KNSAvar[2] = false;
	KNSAvar[3] = false;
	KNSAvar[4] = false;

	KNSAvarseti[1] = false;
	KNSAvarseti[2] = false;
	KNSAvarseti[3] = false;
	KNSAvarseti[4] = false;

	KNSOgran[1] = false;
	KNSOgran[2] = false;
	KNSOgran[3] = false;
	KNSOgran[4] = false;

	KNSPeregrev[1] = false;
	KNSPeregrev[2] = false;
	KNSPeregrev[3] = false;
	KNSPeregrev[4] = false;

	KNSTemp[1] = 25;
	KNSTemp[2] = 25;
	KNSTemp[3] = 25;
	KNSTemp[4] = 25;

	AKBOff[1] = false;
	AKBOff[2] = false;

// 	AKBCharging[1] = true;
// 	AKBCharging[2] = true;

// 	AKBDischarging[1] = false;
// 	AKBDischarging[2] = false;

// 	AKBFulldischarg[1] = false;
// 	AKBFulldischarg[2] = false;

// 	AKBTrening[1] = false;
// 	AKBTrening[2] = false;

	AKBU1[1] = 0.0;
	AKBU1[2] = 0.0;

	AKBU2[1] = 0.0;
	AKBU2[2] = 0.0;

	AKBU3[1] = 0.0;
	AKBU3[2] = 0.0;

	AKBU4[1] = 0.0;
	AKBU4[2] = 0.0;

	AKBU5[1] = 0.0;
	AKBU5[2] = 0.0;

	AKBI[1] = 0.0;
	AKBI[2] = 0.0;

	AKBTemp[1] = 0.0;
	AKBTemp[2] = 0.0;

	LoadOff = false;
	LoadI = 10;

// 	Load1Off = false;
	Load1State = true;
// 	Load1U = 0.0;
// 	Load1I = 0.0;

// 	Load2Off = false;
	Load2State = true;
// 	Load2U = 0.0;
// 	Load2I = 0.0;

// 	Load3Off = false;
	Load3State = true;
// 	Load3U = 0.0;
// 	Load3I = 0.0;

	CoolerOff = true;
	CoolerForcedOn = false;

	ExitU = 60;
}

DATA::~DATA() {

}

void DATA::setLdefState(bool N) {
	if (LdefState != N) {
		LdefState = N;
		if (N) {
			logger->setMsg(1, 0, "Грозозащита;работает;1");
		} else {
			logger->setMsg(1, 0, "Грозозащита;не работает;0");
		}
	}
}

// void DATA::setLdefOff(bool N) {
// 	if (LdefOff != N) {
// 		LdefOff = N;
// 		if (!N) {
// 			logger->setMsg(1, 0, "Грозозащита;включена;1");
// 		} else {
// 			logger->setMsg(1, 0, "Грозозащита;отключена;0");
// 		}
// 	}
// }

// void DATA::setACOff(bool N) {
// 	if (ACOff != N) {
// 		ACOff = N;
// 		if (!N) {
// 			logger->setMsg(1, 0, "Питание;включено;1");
// 		} else {
// 			logger->setMsg(1, 0, "Питание;отключено;0");
// 		}
// 	}
// }

void DATA::setACU(float N) {
	if (ACU != N) {
		ACU = N;
		logger->setMsg(2, 0, "Питание;Напряжение;", N);
		stats->addValue("Питание;Напряжение;", 0, N);
	}
}

// void DATA::setACHz(float N) {
// 	if (ACHz != N) {
// 		ACHz = N;
// 		logger->setMsg(2, 0, "Питание;Частота;", N);
// 		stats->addValue("Питание;Частота;", 0, N);
// 	}
// }

void DATA::setKNSOff(int num, bool N) {
	if (KNSOff[num] != N) {
		KNSOff[num] = N;
		if (!N) {
			logger->setMsg(1, num, "КНС;включено;1");
		} else {
			logger->setMsg(1, num, "КНС;отключено;0");
		}
	}
}

// void DATA::setKNSNorma(int num, bool N) {
// 	if (KNSNorma[num] != N) {
// 		KNSNorma[num] = N;
// 		if (N) {
// 			logger->setMsg(1, num, "КНС;норма;1");
// 		} else {
// 			logger->setMsg(3, num, "КНС;не норма;0");
// 		}
// 	}
// }

void DATA::setKNSAvar(int num, bool N) {
	if (KNSAvar[num] != N) {
		KNSAvar[num] = N;
		if (!N) {
			logger->setMsg(3, num, "КНС;не авария;1");
		} else {
			logger->setMsg(1, num, "КНС;авария;0");
		}
	}
}

void DATA::setKNSAvarseti(int num, bool N) {
	if (KNSAvarseti[num] != N) {
		KNSAvarseti[num] = N;
		if (!N) {
			logger->setMsg(3, num, "КНС;не авария сети;1");
		} else {
			logger->setMsg(1, num, "КНС;авария сети;0");
		}
	}
}

void DATA::setKNSOgran(int num, bool N) {
	if (KNSOgran[num] != N) {
		KNSOgran[num] = N;
		if (!N) {
			logger->setMsg(3, num, "КНС;не ограничение;1");
		} else {
			logger->setMsg(1, num, "КНС;ограничение;0");
		}
	}
}

void DATA::setKNSPeregrev(int num, bool N) {
	if (KNSPeregrev[num] != N) {
		KNSPeregrev[num] = N;
		if (!N) {
			logger->setMsg(3, num, "КНС;не перегрев;1");
		} else {
			logger->setMsg(1, num, "КНС;перегрев;0");
		}
	}
}

void DATA::setKNSTemp(int num, float N) {
	if (KNSTemp[num] != N) {
		KNSTemp[num] = N;
		logger->setMsg(2, num, "КНС;Температура;", N);
		stats->addValue("КНС;Температура;", num, N);
	}
}

void DATA::setAKBOff(int num, bool N) {
	if (AKBOff[num] != N) {
		AKBOff[num] = N;
		if (!N) {
			logger->setMsg(1, num, "АКБ;включена;1");
		} else {
			logger->setMsg(1, num, "АКБ;отключена;0");
		}
	}
}

// void DATA::setAKBCharging(int num, bool N) {
// 	if (AKBCharging[num] != N) {
// 		AKBCharging[num] = N;
// 		if (N) {
// 			logger->setMsg(1, num, "АКБ;заряд;1");
// 		} else {
// 			logger->setMsg(3, num, "АКБ;не заряд;1");
// 		}
// 	}
// }
//
// void DATA::setAKBDischarging(int num, bool N) {
// 	if (AKBDischarging[num] != N) {
// 		AKBDischarging[num] = N;
// 		if (N) {
// 			logger->setMsg(1, num, "АКБ;разряд;1");
// 		} else {
// 			logger->setMsg(3, num, "АКБ;не разряд;1");
// 		}
// 	}
// }
//
// void DATA::setAKBFulldischarg(int num, bool N) {
// 	if (AKBFulldischarg[num] != N) {
// 		AKBFulldischarg[num] = N;
// 		if (N) {
// 			logger->setMsg(1, num, "АКБ;глуб. разряд;1");
// 		} else {
// 			logger->setMsg(3, num, "АКБ;не глуб. разряд;1");
// 		}
// 	}
// }
//
// void DATA::setAKBTrening(int num, bool N) {
// 	if (AKBTrening[num] != N) {
// 		AKBTrening[num] = N;
// 		if (N) {
// 			logger->setMsg(1, num, "АКБ;авт. тренинг;1");
// 		} else {
// 			logger->setMsg(3, num, "АКБ;не авт. тренинг;1");
// 		}
// 	}
// }

void DATA::setAKBU1(int num, float N) {
	if (AKBU1[num] != N) {
		AKBU1[num] = N;
		logger->setMsg(2, num, "АКБ;Напряжение1;", N);
		stats->addValue("АКБ;Напряжение1;", num, N);
	}
}

void DATA::setAKBU2(int num, float N) {
	if (AKBU2[num] != N) {
		AKBU2[num] = N;
		logger->setMsg(2, num, "АКБ;Напряжение2;", N);
		stats->addValue("АКБ;Напряжение2;", num, N);
	}
}

void DATA::setAKBU3(int num, float N) {
	if (AKBU3[num] != N) {
		AKBU3[num] = N;
		logger->setMsg(2, num, "АКБ;Напряжение3;", N);
		stats->addValue("АКБ;Напряжение3;", num, N);
	}
}

void DATA::setAKBU4(int num, float N) {
	if (AKBU4[num] != N) {
		AKBU4[num] = N;
		logger->setMsg(2, num, "АКБ;Напряжение4;", N);
		stats->addValue("АКБ;Напряжение4;", num, N);
	}
}

void DATA::setAKBU5(int num, float N) {
	if (AKBU5[num] != N) {
		AKBU5[num] = N;
		logger->setMsg(2, num, "АКБ;Напряжение5;", N);
		stats->addValue("АКБ;Напряжение5;", num, N);
	}
}

void DATA::setAKBI(int num, float N) {
	if (AKBI[num] != N) {
		AKBI[num] = N;
		logger->setMsg(2, num, "АКБ;Ток;", N);
		stats->addValue("АКБ;Ток;", num, N);
	}
}

void DATA::setAKBTemp(int num, float N) {
	if (AKBTemp[num] != N) {
		AKBTemp[num] = N;
		logger->setMsg(2, num, "АКБ;Температура;", N);
		stats->addValue("АКБ;Температура;", num, N);
	}
}

void DATA::setLoadOff(bool N) {
	if (LoadOff != N) {
		LoadOff = N;
		if (N) {
			logger->setMsg(1, 0, "Нагрузка;отключена;0");
		} else {
			logger->setMsg(1, 0, "Нагрузка;включена;1");
		}
	}
}

void DATA::setLoadI(float N) {
	if (LoadI != N) {
		LoadI = N;
		logger->setMsg(2, 0, "Нагрузка;Ток;", N);
		stats->addValue("Нагрузка;Ток;", 0, N);
	}
}

// void DATA::setLoad1Off(bool N) {
// 	Load1Off = N;
// }

void DATA::setLoad1State(bool N) {
	if (Load1State != N) {
		Load1State = N;
		if (N) {
			logger->setMsg(3, 0, "Нагрузка1;не авария;1");
		} else {
			logger->setMsg(1, 0, "Нагрузка1;авария;0");
		}
	}
}

// void DATA::setLoad1U(float N) {
// 	Load1U = N;
// }
//
// void DATA::setLoad1I(float N) {
// 	Load1I = N;
// }
//
// void DATA::setLoad2Off(bool N) {
// 	Load2Off = N;
// }

void DATA::setLoad2State(bool N) {
	if (Load2State != N) {
		Load2State = N;
		if (N) {
			logger->setMsg(3, 0, "Нагрузка2;не авария;1");
		} else {
			logger->setMsg(1, 0, "Нагрузка2;авария;0");
		}
	}
}

// void DATA::setLoad2U(float N) {
// 	Load2U = N;
// }
//
// void DATA::setLoad2I(float N) {
// 	Load2I = N;
// }
//
// void DATA::setLoad3Off(bool N) {
// 	Load3Off = N;
// }

void DATA::setLoad3State(bool N) {
	if (Load3State != N) {
		Load3State = N;
		if (N) {
			logger->setMsg(3, 0, "Нагрузка3;не авария;1");
		} else {
			logger->setMsg(1, 0, "Нагрузка3;авария;0");
		}
	}
}

// void DATA::setLoad3U(float N) {
// 	Load3U = N;
// }
//
// void DATA::setLoad3I(float N) {
// 	Load3I = N;
// }

void DATA::setCoolerOff(bool N) {
	if (CoolerOff != N) {
		CoolerOff = N;
		if (N) {
			logger->setMsg(1, 0, "Вентилятор;отключен;1");
		} else {
			logger->setMsg(1, 0, "Вентилятор;работает;1");
		}
	}
}

void DATA::setCoolerForcedOn(bool N) {
	if (CoolerForcedOn != N) {
		CoolerForcedOn = N;
		if (N) {
			logger->setMsg(1, 0, "Вентилятор;включен;1");
		} else {
			logger->setMsg(3, 0, "Вентилятор;не включен;1");
		}
	}
}

void DATA::setExitU(float N) {
	if (ExitU != N) {
		ExitU = N;
		logger->setMsg(2, 0, "Общее;Вых. напряжение;", N);
		stats->addValue("Общее;Вых. нарпяжение;", 0, N);
	}
}

bool DATA::getLdefState() {
	return LdefState;
}

// bool DATA::getLdefOff() {
// 	return LdefOff;
// }
//
// bool DATA::getACOff() {
// 	return ACOff;
// }

float DATA::getACU() {
	return ACU;
}

// float DATA::getACHz() {
// 	return ACHz;
// }

bool DATA::getKNSOff(int num) {
	return KNSOff[num];
}

// bool DATA::getKNSNorma(int num) {
// 	return KNSNorma[num];
// }

bool DATA::getKNSAvar(int num) {
	return KNSAvar[num];
}

bool DATA::getKNSAvarseti(int num) {
	return KNSAvarseti[num];
}

bool DATA::getKNSOgran(int num) {
	return KNSOgran[num];
}

bool DATA::getKNSPeregrev(int num) {
	return KNSPeregrev[num];
}

float DATA::getKNSTemp(int num) {
	return KNSTemp[num];
}

bool DATA::getAKBOff(int num) {
	return AKBOff[num];
}

// bool DATA::getAKBCharging(int num) {
// 	return AKBCharging[num];
// }
//
// bool DATA::getAKBDischarging(int num) {
// 	return AKBDischarging[num];
// }
//
// bool DATA::getAKBFulldischarg(int num) {
// 	return AKBFulldischarg[num];
// }
//
// bool DATA::getAKBTrening(int num) {
// 	return AKBTrening[num];
// }

float DATA::getAKBU1(int num) {
	return AKBU1[num];
}

float DATA::getAKBU2(int num) {
	return AKBU2[num];
}

float DATA::getAKBU3(int num) {
	return AKBU3[num];
}

float DATA::getAKBU4(int num) {
	return AKBU4[num];
}

float DATA::getAKBU5(int num) {
	return AKBU5[num];
}

float DATA::getAKBI(int num) {
	return AKBI[num];
}

float DATA::getAKBTemp(int num) {
	return AKBTemp[num];
}

bool DATA::getLoadOff() {
	return LoadOff;
}

float DATA::getLoadI() {
	return LoadI;
}

// bool  DATA::getLoad1Off() {
// 	return Load1Off;
// }

bool  DATA::getLoad1State() {
	return Load1State;
}

// float DATA::getLoad1U() {
// 	return Load1U;
// }
//
// float DATA::getLoad1I() {
// 	return Load1I;
// }
//
// bool  DATA::getLoad2Off() {
// 	return Load2Off;
// }

bool  DATA::getLoad2State() {
	return Load2State;
}

// float DATA::getLoad2U() {
// 	return Load2U;
// }
//
// float DATA::getLoad2I() {
// 	return Load2I;
// }
//
// bool  DATA::getLoad3Off() {
// 	return Load3Off;
// }

bool  DATA::getLoad3State() {
	return Load3State;
}

// float DATA::getLoad3U() {
// 	return Load3U;
// }
//
// float DATA::getLoad3I() {
// 	return Load3I;
// }

bool DATA::getCoolerOff() {
	return CoolerOff;
}

bool DATA::getCoolerForcedOn() {
	return CoolerForcedOn;
}

float DATA::getExitU() {
	return ExitU;
}
