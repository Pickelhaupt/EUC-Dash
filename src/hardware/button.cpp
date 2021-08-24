//#include <Arduino.h>
#include "button.h"
#include "hardware.h"
#include "system/eventmgm.h"
#include <EasyButton.h>

lv_group_t *button_group;

static EasyButton encoder_button(BUTTON_1);
static EasyButton up_button(BUTTON_3);
static EasyButton down_button(BUTTON_2);
//static int previousCount = 0;
//static int set_count = 0;

volatile bool DRAM_ATTR button_irq_flag = false;
portMUX_TYPE DRAM_ATTR BTN_IRQ_Mux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR button_irq( void );

void button_enter_read()
{
  encoder_button.read();
  log_i("enter button read");
}
void button_up_read()
{
  up_button.read();
  log_i("up button read");
}
void button_down_read()
{
  down_button.read();
  log_i("down button read");
}

void button_encoder_setup(){

	encoder_button.begin();
	up_button.begin();
	down_button.begin();
	
	if (encoder_button.supportsInterrupt())
    {
        encoder_button.enableInterrupt(button_enter_read);
		log_i("encoder button supports interrupt");
		//pinMode( BUTTON_1, INPUT );
    	attachInterrupt( BUTTON_1, button_irq, FALLING );
    }
	if (up_button.supportsInterrupt())
    {
        //up_button.enableInterrupt(button_up_read);
		log_i("up button supports interrupt");
		//pinMode( BUTTON_3, INPUT );
    	//attachInterrupt( BUTTON_3, button_irq, RISING );
    }
	if (down_button.supportsInterrupt())
    {
        down_button.enableInterrupt(button_down_read);
		log_i("down button supports interrupt");
		//pinMode( BUTTON_2, INPUT );
    	attachInterrupt( BUTTON_2, button_irq, RISING );
    }
}

bool button_eventmgm_event_cb ( EventBits_t event, void *arg ) {
	
    switch( event ) {
        case EVENTMGM_ENABLE_INTERRUPTS:
										log_i("attaching button interrupts");
										//attachInterrupt( BUTTON_1, button_irq, RISING );
										//attachInterrupt( BUTTON_2, button_irq, RISING );
										//attachInterrupt( BUTTON_3, button_irq, RISING );
                                        break;
        case EVENTMGM_DISABLE_INTERRUPTS:
										log_i("detaching button interrupts");
                                        //detachInterrupt( BUTTON_1 );
										//detachInterrupt( BUTTON_2 );
										//detachInterrupt( BUTTON_3 );
                                        break;
    }
    return( true );
}

bool button_eventmgm_loop_cb ( EventBits_t event, void *arg ) {

	portENTER_CRITICAL(&BTN_IRQ_Mux);
	bool temp_button_irq_flag = button_irq_flag;
    button_irq_flag = false;
	//log_i("btn_irq event loop");
    portEXIT_CRITICAL(&BTN_IRQ_Mux);
	if ( temp_button_irq_flag ) { 
		log_i("btn_irq event loop");     
		if (!eventmgm_get_event(EVENTMGM_WAKEUP)) eventmgm_set_event(EVENTMGM_WAKEUP_REQUEST);
    }
	return( true );
}


bool button_encoder_read(lv_indev_drv_t *drv, lv_indev_data_t * data){
	static bool encoder_pressed = false;
	static bool up_pressed = false;
	static bool down_pressed = false;
	static int press_time = 0;

	if(encoder_button.read()){
		if (!encoder_pressed) {
			data->state = LV_INDEV_STATE_PR;
			data->key = LV_KEY_ENTER;
			data->btn_id = LV_KEY_ENTER;
			Serial.println("enter button pressed");
			press_time = millis();
		}
		encoder_pressed = true;
	} else {
		if (encoder_pressed) {
			if (millis() - press_time > LONG_PRESS_DELAY) {
			}
			data->state = LV_INDEV_STATE_REL; 
			encoder_pressed = false;
			Serial.println("enter button released");
		}
	}	
	if(up_button.read()){
		if (!up_pressed) {		
			Serial.println("up button released");
			data->state = LV_INDEV_STATE_REL;
			//set_count++;			
		}
		up_pressed = true;
		} else {
			if (up_pressed) {
				up_pressed = false;
				
				Serial.println("up button pressed");
				data->btn_id = LV_KEY_RIGHT;
				data->key = LV_KEY_RIGHT;
				data->state = LV_INDEV_STATE_PR;
			}
		}
	if(down_button.read()){
		if (!down_pressed) {
			Serial.println("down button released");
			//set_count--;
			data->state = LV_INDEV_STATE_REL;
		}
		down_pressed = true;
	} else {
		if (down_pressed) {
			down_pressed = false;	
			Serial.println("down button pressed");
			data->btn_id = LV_KEY_LEFT;
			data->key = LV_KEY_LEFT;
			data->state = LV_INDEV_STATE_PR;
		}
	}
	/*
	//int enccnt = encoder.getCount();
	int newCount = set_count;
	int enc_diff = 0;
	if(newCount - previousCount != 0 ){ //This encoder clicks in steps of 2
		//enc_diff = (newCount-previousCount)/2;
		enc_diff = newCount-previousCount;
		previousCount = newCount;
		Serial.printf("encoder diff = %d \n", enc_diff);
		Serial.printf("encoder count = %d \n", newCount);
		data->enc_diff = enc_diff;
	}  
	*/
	  
	return 0;
}

void IRAM_ATTR button_irq( void ) {
    portENTER_CRITICAL_ISR(&BTN_IRQ_Mux);
    button_irq_flag = true;
	  log_i("button IRQ");
    portEXIT_CRITICAL_ISR(&BTN_IRQ_Mux);
	  if (!eventmgm_get_event(EVENTMGM_WAKEUP)) eventmgm_set_event(EVENTMGM_WAKEUP_REQUEST);
}

void button_init(){
    button_encoder_setup();
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = button_encoder_read;
    lv_indev_t * keyenc_indev = lv_indev_drv_register(&indev_drv);
	//lv_indev_enable(keyenc_indev, true);
	button_group = lv_group_create();
    lv_indev_set_group(keyenc_indev, button_group);
	gpio_wakeup_enable( (gpio_num_t)BUTTON_1, GPIO_INTR_HIGH_LEVEL );
	gpio_wakeup_enable( (gpio_num_t)BUTTON_2, GPIO_INTR_HIGH_LEVEL );
	gpio_wakeup_enable( (gpio_num_t)BUTTON_3, GPIO_INTR_HIGH_LEVEL );
	

	//eventmgm_register_cb(EVENTMGM_ENABLE_INTERRUPTS | EVENTMGM_DISABLE_INTERRUPTS, button_eventmgm_event_cb, "eventmgm button");
	eventmgm_register_loop_cb(EVENTMGM_SILENCE_WAKEUP | EVENTMGM_STANDBY | EVENTMGM_WAKEUP, button_eventmgm_loop_cb, "eventmgm button loop");
}
