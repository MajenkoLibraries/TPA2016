#include <TPA2016.h>

void TPA2016::begin() {
    enableAmplifier();
    dtwi->beginMaster();

    setAmp(1, 0b11000000);
    setAmp(2, 0x01);
    setAmp(6, 0x80);
    setAmp(7, 0xF0);
    setGain(0);
}

void TPA2016::setAmp(uint8_t reg, uint8_t val) {
    uint8_t state = 0;
    uint32_t ts = millis();
    while (1) {
        if (millis() - ts >= 100) {
            dtwi->stopMaster();
            return;
        }
        switch (state) {
            case 0: // begin write
                if (dtwi->startMasterWrite(0x58)) {
                    state = 1;
                }
                break;
            case 1: // Send register address
                if (dtwi->write(&reg, 1) == 1) {
                    state = 2;
                }
                break;
            case 2: // Send register address
                if (dtwi->write(&val, 1) == 1) {
                    state = 3;
                }
                break;
            case 3: // Stop Master
                if (dtwi->stopMaster()) {
                    return;
                }
                break;
        }
    }

}

void TPA2016::setGain(int8_t v) {
    if (v > 30) {
        v = 30;
    }
    setAmp(5, v);
}

void TPA2016::enableAmplifier() {
    pinMode(enable, OUTPUT);
    digitalWrite(enable, HIGH);
}

void TPA2016::disableAmplifier() {
    pinMode(enable, OUTPUT);
    digitalWrite(enable, LOW);
}
