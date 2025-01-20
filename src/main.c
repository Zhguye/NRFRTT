#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <modem/sms.h>
#include <modem/lte_lc.h>
#include "connect_example.h"
#include <modem/modem_info.h>
#include <modem/nrf_modem_lib.h>
#include <stdbool.h>
#include <string.h>
#include <nrf_modem_at.h> 
#include <zephyr/sys/printk.h>




LOG_MODULE_REGISTER(at_rtt_modem, LOG_LEVEL_INF);


/* Initialize modem */
static void modem_init(void) {
    int32_t retval = 0;

    struct modem_param_info modem_info;


	
	
	
  	modem_info_init();
    

    /* Get modem information */
    modem_info_params_init(&modem_info);
    LOG_INF("Initializing LTE modem...");


    retval = nrf_modem_lib_init();
	if(retval != 0){
		LOG_ERR("Failed to initialize nrf modem lib (%d)",retval);
		k_msleep(5000);
		
	}

    LOG_INF("Modem initialized");
}


int main(void) {
    char resp[256];
    int32_t retval;

    LOG_INF("AT Command over RTT Interface Example");


    modem_init();


      //  TRACE_START();
      SEGGER_SYSVIEW_Start();
    /* Send some example AT commands */
    
    retval = nrf_modem_at_scanf("AT+CFUN?","%s",resp);
    if(retval == 1){
        LOG_INF("Query modem functionality: %s",resp);
    }

    retval = nrf_modem_at_scanf("AT+CGMI","%s",resp);
    if(retval == 1){
        LOG_INF(" Manufacturer identification: %s",resp);
    }

    retval = nrf_modem_at_scanf("AT+CGSN","%s",resp);
    if(retval == 1){
        LOG_INF("Request product serial number: %s",resp);
    }

    retval = nrf_modem_at_scanf("AT+CIMI","%s",resp);
    if(retval == 1){
        LOG_INF("Request IMSI: %s",resp);
    }

    retval = nrf_modem_at_scanf("AT+CREG?","%s",resp);
    if(retval == 1){
        LOG_INF("Network Registration Status: %s",resp);
    }
         // TRACE_STOP();
         SEGGER_SYSVIEW_Stop();
    //Register to cereg notifications
    retval = nrf_modem_at_printf("AT+CEREG=%d",CEREG_NOTIFICATION_LEVEL);
	if (retval) {
		LOG_INF("AT+CEREG failed");
		return -1;
	}


    return 0;
    
}
