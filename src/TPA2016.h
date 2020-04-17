#ifndef _TPA2016_H
#define _TPA2016_H

#include <Arduino.h>
#include <DTWI.h>
#include <I2S.h>

class TPA2016 : public Amplifier {
	private:
        DTWI *dtwi;
        uint8_t enable;

        void initAmp();
        void setAmp(uint8_t reg, uint8_t val);

	public:
		TPA2016(DTWI *d, uint8_t e) : dtwi(d), enable(e) {}
		TPA2016(DTWI &d, uint8_t e) : dtwi(&d), enable(e) {}
		void begin();
        void setGain(int8_t vol);
        void enableAmplifier();
        void disableAmplifier();
};

#endif
