#include "power.h"




void power_init(void) {

    #ifdef HAS_AXP202
        adc1enable(( AXP202_BATT_VOL_ADC1 | AXP202_BATT_CUR_ADC1 | AXP202_VBUS_VOL_ADC1 | AXP202_VBUS_CUR_ADC1, AXP202_ON);
        enableIRQ( AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_FINISHED_IRQ | AXP202_CHARGING_IRQ | AXP202_TIMER_TIMEOUT_IRQ, AXP202_ON );
        clearIRQ();
        setChargingTargetVoltage( AXP202_TARGET_VOL_4_2V );
        setChargeControlCur( 300 );
        setAdcSamplingRate( AXP_ADC_SAMPLING_RATE_200HZ );

        pinMode( AXP202_INT, INPUT );
        attachInterrupt( AXP202_INT, &pmu_irq, FALLING );
    #endif

    #ifdef NO_PMU
        pinMode(EXT_PWR_PIN, INPUT);
        pinMode(BATT_MON_PIN, INPUT);
    #endif
}

bool power_charging(void){
    #ifdef NO_PMU
        bool charging = digitalRead(EXT_PWR_PIN);
        if (charging) {
            log_i("charging");
        } else log_i("not charging");
        return charging;
    #endif
    #ifdef HAS_AXP202
        //add axp202 charge detect
    #endif
}

uint16_t power_batt_analog_read( void ){
    #ifdef NO_PMU
        analogReadResolution(12);
        analogSetPinAttenuation(BATT_MON_PIN, ADC_11db);
        //pinMode(BATT_MON_PIN, INPUT);
        uint16_t value = analogRead(BATT_MON_PIN);
        log_i("battery read = %d", value);
        return value;
    #endif
    #ifdef HAS_AXP202
        //probably not necessary
    #endif
}

float power_get_battvolt(void) {
    uint16_t a_read = power_batt_analog_read();
    float value = (4.2 * a_read) / 115.0;
    log_i("battery voltage = %f", value);
    return value;
}

byte power_get_battpct(void){
    float a_read = power_batt_analog_read();
    byte value = (a_read / 1.1);
    if (value > 100) value = 100;
    log_i("battery percent = %d", value);
    return value;
}