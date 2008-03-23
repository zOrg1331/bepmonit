#ifndef DATA_H
#define DATA_H

#include "log.h"
#include "statdata.h"

class DATA {
	public:
		DATA(log *, statdata *);
		~DATA();

	public:
		// выдаем всем текущие параметры железок
		bool getLdefState();
// 		bool getLdefOff();

// 		bool getACOff();
		float getACU();
// 		float getACHz();

		// в качестве аргумента порядковый номер железки (начиная с 1)
		bool getKNSOff(int);
// 		bool getKNSNorma(int);
		bool getKNSAvar(int);
		bool getKNSAvarseti(int);
		bool getKNSOgran(int);
		bool getKNSPeregrev(int);
		float getKNSTemp(int);

		// в качестве аргумента порядковый номер железки (начиная с 1)
		bool getAKBOff(int);
// 		bool getAKBCharging(int);
// 		bool getAKBDischarging(int);
// 		bool getAKBFulldischarg(int);
// 		bool getAKBTrening(int);
		float getAKBU1(int);
		float getAKBU2(int);
		float getAKBU3(int);
		float getAKBU4(int);
		float getAKBU5(int);
		float getAKBI(int);
		float getAKBTemp(int);

		bool getLoadOff();
		float getLoadI();

// 		bool getLoad1Off();
		bool getLoad1State();
// 		float getLoad1U();
// 		float getLoad1I();

// 		bool getLoad2Off();
		bool getLoad2State();
// 		float getLoad2U();
// 		float getLoad2I();

// 		bool getLoad3Off();
		bool getLoad3State();
// 		float getLoad3U();
// 		float getLoad3I();

		bool getCoolerOff();
		bool getCoolerForcedOn();

		float getExitU();

		// задаем параметры железок
		void setLdefState(bool);
// 		void setLdefOff(bool);

// 		void setACOff(bool);
		void setACU(float);
// 		void setACHz(float);

		// в качестве аргумента порядковый номер железки (начиная с 1)
		void setKNSOff(int, bool);
// 		void setKNSNorma(int, bool);
		void setKNSAvar(int, bool);
		void setKNSAvarseti(int, bool);
		void setKNSOgran(int, bool);
		void setKNSPeregrev(int, bool);
		void setKNSTemp(int, float);

		// в качестве аргумента порядковый номер железки (начиная с 1)
		void setAKBOff(int, bool);
// 		void setAKBCharging(int, bool);
// 		void setAKBDischarging(int, bool);
// 		void setAKBFulldischarg(int, bool);
// 		void setAKBTrening(int, bool);
		void setAKBU1(int, float);
		void setAKBU2(int, float);
		void setAKBU3(int, float);
		void setAKBU4(int, float);
		void setAKBU5(int, float);
		void setAKBI(int, float);
		void setAKBTemp(int, float);

		void setLoadOff(bool);
		void setLoadI(float);

// 		void setLoad1Off(bool);
		void setLoad1State(bool);
// 		void setLoad1U(float);
// 		void setLoad1I(float);

// 		void setLoad2Off(bool);
		void setLoad2State(bool);
// 		void setLoad2U(float);
// 		void setLoad2I(float);

// 		void setLoad3Off(bool);
		void setLoad3State(bool);
// 		void setLoad3U(float);
// 		void setLoad3I(float);

		void setCoolerOff(bool);
		void setCoolerForcedOn(bool);

		void setExitU(float);

	private:
		log *logger;
		statdata *stats;

		// остальные параметры железок
		bool LdefState;
// 		bool LdefOff;

// 		bool ACOff;
		float ACU;
// 		float ACHz;

		// массивы со значениями параметров каждой железки
		bool KNSOff[255];
// 		bool KNSNorma[255];
		bool KNSAvar[255];
		bool KNSAvarseti[255];
		bool KNSOgran[255];
		bool KNSPeregrev[255];
		float KNSTemp[255];

		bool AKBOff[255];
// 		bool AKBCharging[255];
// 		bool AKBDischarging[255];
// 		bool AKBFulldischarg[255];
// 		bool AKBTrening[255];
		float AKBU1[255];
		float AKBU2[255];
		float AKBU3[255];
		float AKBU4[255];
		float AKBU5[255];
		float AKBI[255];
		float AKBTemp[255];

		bool LoadOff;
		float LoadI;

// 		bool Load1Off;
		bool Load1State;
// 		float Load1U;
// 		float Load1I;

// 		bool Load2Off;
		bool Load2State;
// 		float Load2U;
// 		float Load2I;

// 		bool Load3Off;
		bool Load3State;
// 		float Load3U;
// 		float Load3I;

		bool CoolerOff;
		bool CoolerForcedOn;

		float ExitU;

};

#endif
