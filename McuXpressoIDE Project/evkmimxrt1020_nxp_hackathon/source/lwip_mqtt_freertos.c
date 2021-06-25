/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "lwip/opt.h"

#if LWIP_IPV4 && LWIP_RAW && LWIP_NETCONN && LWIP_DHCP && LWIP_DNS

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_phy.h"

#include "lwip/api.h"
#include "lwip/apps/mqtt.h"
#include "lwip/dhcp.h"
#include "lwip/netdb.h"
#include "lwip/netifapi.h"
#include "lwip/prot/dhcp.h"
#include "lwip/tcpip.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"
#include "enet_ethernetif.h"
#include "lwip_mqtt_id.h"

#include "ctype.h"
#include "stdio.h"

#include "fsl_gpio.h"
#include "fsl_iomuxc.h"
#include "fsl_phyksz8081.h"
#include "fsl_enet_mdio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "fsl_debug_console.h"
#include "littlevgl_support.h"

#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

#include "fsl_edma.h"
#include "fsl_dmamux.h"

#include "fsl_enc.h"

#include "ext_modules.h"

#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LPSPI_MASTER_DMA_BASEADDR     DMA0
#define LPSPI_MASTER_DMA_MUX_BASEADDR DMAMUX


/* IP address configuration. */
#define configIP_ADDR0 192
#define configIP_ADDR1 168
#define configIP_ADDR2 0
#define configIP_ADDR3 102

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

/* Gateway address configuration. */
#define configGW_ADDR0 192
#define configGW_ADDR1 168
#define configGW_ADDR2 0
#define configGW_ADDR3 100

/* MAC address configuration. */
#define configMAC_ADDR                     \
    {                                      \
        0x02, 0x12, 0x13, 0x10, 0x15, 0x11 \
    }

/* Address of PHY interface. */
#define EXAMPLE_PHY_ADDRESS BOARD_ENET0_PHY_ADDRESS

/* MDIO operations. */
#define EXAMPLE_MDIO_OPS enet_ops

/* PHY operations. */
#define EXAMPLE_PHY_OPS phyksz8081_ops

/* ENET clock frequency. */
#define EXAMPLE_CLOCK_FREQ CLOCK_GetFreq(kCLOCK_IpgClk)

#ifndef EXAMPLE_NETIF_INIT_FN
/*! @brief Network interface initialization function. */
#define EXAMPLE_NETIF_INIT_FN ethernetif0_init
#endif /* EXAMPLE_NETIF_INIT_FN */

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define APP_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define APP_THREAD_PRIO DEFAULT_THREAD_PRIO

/* IBM watson account info*/
#define ORG						"YOUR ORG"						//	change these according to your account
#define DEVICE_TYPE				"YOUR DEVICE TYPE"				//	change these according to your account
#define DEVICE_ID				"YOUR DEVICE ID"				//	change these according to your account
#define AUTHENTICATION_TOKEN	"YOUR AUTHENTICATION TOKEN"		//	change these according to your account
#define AUTHENTICATION_METHOD	"use-token-auth"

#define MQTT_BROKER_ADDRESS		ORG ".messaging.internetofthings.ibmcloud.com"
#define MQTT_BROKER_PORT		1883
#define CLIENT_ID				"d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID

#define MQTT_PUBLISH_TOPIC                "iot-2/evt/status/fmt/json"
#define MQTT_SUBSCRIBE_TOPIC              "iot-2/cmd/update/fmt/json"

// OR use these to publish respective data separately
#define MQTT_PUBLISH_TOPIC_1              "iot-2/evt/environmental/fmt/json"
#define MQTT_PUBLISH_TOPIC_2              "iot-2/evt/power/fmt/json"
#define MQTT_PUBLISH_TOPIC_3              "iot-2/evt/rgb/fmt/json"
#define MQTT_PUBLISH_TOPIC_4              "iot-2/evt/control/fmt/json"

/*
// Data packet to enable remote device management (Restart, Factory Reset or Firmware update) //
#define DEVICE_MANNAGE_STR   "{\"d\":{\"supports\":{\"deviceActions\":true,\"firmwareActions\":true}},\"reqId\":\"REPLACE WITH 40 RANDOM CHARACTERS STRING\"}"

#define MQTT_MANAGEDEVICE_TOPIC           "iotdm-1/#"

// Name of DM requests topic //
#define MQTT_DMRESPONSE_TOPIC           "iotdm-1/response"
#define MQTT_DMOBSERVE_TOPIC            "iotdm-1/observe"
#define MQTT_DMCANCEL_TOPIC             "iotdm-1/cancel"

// Name of response topic //
#define MQTT_RESPONSE_TOPIC             "iotdevice-1/response"
#define MQTT_NOTIFY_TOPIC               "iotdevice-1/notify"

// Name of management topic //
#define MQTT_MANAGE_TOPIC               "iotdevice-1/mgmt/manage"
#define MQTT_UUNMANAGE_TOPIC            "iotdevice-1/mgmt/unmanage"

// Name of device management topic //
#define MQTT_UPDATE_LOCATION_TOPIC      "iotdevice-1/device/update/location"
#define MQTT_CREATE_ERRCODES_TOPIC      "iotdevice-1/add/diag/errorCodes"
#define MQTT_CLEAR_ERRCODES_TOPIC       "iotdevice-1/clear/diag/errorCodes"
#define MQTT_ADD_LOG_TOPIC              "iotdevice-1/add/diag/log"
#define MQTT_CLEAR_LOG_TOPIC            "iotdevice-1/clear/diag/log"

// Name of firmware actions topic //
#define MQTT_FWACTIONS_TOPIC            "iotdm-1/device/update"
#define MQTT_FWUPDATE_TOPIC             "iotdm-1/mgmt/initiate/firmware/update"
#define MQTT_FWDOWNLOAD_TOPIC           "iotdm-1/mgmt/initiate/firmware/download"

// Name of device actions topic //
#define MQTT_REBOOT_TOPIC               "iotdm-1/mgmt/initiate/device/reboot"
#define MQTT_FACTORYRESET_TOPIC         "iotdm-1/mgmt/initiate/device/factory_reset"

*/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void connect_to_mqtt(void *ctx);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static mdio_handle_t mdioHandle = {.ops = &EXAMPLE_MDIO_OPS};
static phy_handle_t phyHandle   = {.phyAddr = EXAMPLE_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &EXAMPLE_PHY_OPS};

/*! @brief MQTT client data. */
static mqtt_client_t *mqtt_client;

/*! @brief MQTT client ID string. */
static char client_id[40];

/*! @brief MQTT client information. */
static const struct mqtt_connect_client_info_t mqtt_client_info = {
//    .client_id   = (const char *)&client_id[0],
    .client_id   = CLIENT_ID,
    .client_user = AUTHENTICATION_METHOD,
    .client_pass = AUTHENTICATION_TOKEN,
    .keep_alive  = 100,
    .will_topic  = NULL,
    .will_msg    = NULL,
    .will_qos    = 2,
    .will_retain = 0,
#if LWIP_ALTCP && LWIP_ALTCP_TLS
    .tls_config = NULL,
#endif
};

/*! @brief MQTT broker IP address. */
static ip_addr_t mqtt_addr;

/*! @brief Indicates connection to MQTT broker. */
static volatile bool connected = false;

static bool led_status = false;


static volatile bool s_lvgl_initialized = false;
lv_ui guider_ui;

extern float dht_readings[3];
extern float power_readings[3];
extern float adc_readings[4];
extern float als_reading;
extern uint16_t proximity_reading;
extern uint16_t pwm_readings[16];
extern bool COB_status;

/*******************************************************************************
 * Code
 ******************************************************************************/
void read_sensors_values(lv_task_t * task)
{
	power_module_Readings();
	adc_module_readings();
	als_module_Readings();
	dht_module_readings();

	GPIO_PinWrite(BOARD_INITPINS_COB_GPIO_GPIO, BOARD_INITPINS_COB_GPIO_GPIO_PIN, !COB_status);
}

static void GUI_task(void *param)
{
    lv_port_pre_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    s_lvgl_initialized = true;

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);
	lv_task_create(read_sensors_values, 2000, LV_TASK_PRIO_MID, NULL);

    for (;;)
    {
        lv_task_handler();
        vTaskDelay(5);
    }
}

void BOARD_InitModuleClock(void)
{
    const clock_enet_pll_config_t config = {
        .enableClkOutput = true, .enableClkOutput500M = false, .enableClkOutput25M = false, .loopDivider = 1};
    CLOCK_InitEnetPll(&config);
}

void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*!
 * @brief Called when subscription request finishes.
 */
static void mqtt_topic_subscribed_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Subscribed to the topic \"%s\".\r\n", topic);
    }
    else
    {
        PRINTF("Failed to subscribe to the topic \"%s\": %d.\r\n", topic, err);
    }
}

/*!
 * @brief Called when there is a message on a subscribed topic.
 */
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    LWIP_UNUSED_ARG(arg);

    PRINTF("Received %u bytes from the topic \"%s\": \"", tot_len, topic);
}

/*!
 * @brief Called when recieved incoming published message fragment.
 */
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    int i;

    LWIP_UNUSED_ARG(arg);

    for (i = 0; i < len; i++)
    {
        if (isprint(data[i]))
        {
            PRINTF("%c", (char)data[i]);
        }
        else
        {
            PRINTF("\\x%02x", data[i]);
        }
    }

    if (flags & MQTT_DATA_FLAG_LAST)
    {
        PRINTF("\"\r\n");
    }
}

/*!
 * @brief Subscribe to MQTT topics.
 */
static void mqtt_subscribe_topics(mqtt_client_t *client)
{
    static const char *topics[] = {MQTT_SUBSCRIBE_TOPIC};
    int qos[]                   = {2};
    err_t err;
    int i;

    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb,
                            LWIP_CONST_CAST(void *, &mqtt_client_info));

    for (i = 0; i < ARRAY_SIZE(topics); i++)
    {
        err = mqtt_subscribe(client, topics[i], qos[i], mqtt_topic_subscribed_cb, LWIP_CONST_CAST(void *, topics[i]));

        if (err == ERR_OK)
        {
            PRINTF("Subscribing to the topic \"%s\" with QoS %d...\r\n", topics[i], qos[i]);
        }
        else
        {
            PRINTF("Failed to subscribe to the topic \"%s\" with QoS %d: %d.\r\n", topics[i], qos[i], err);
        }
    }
}

/*!
 * @brief Called when connection state changes.
 */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    const struct mqtt_connect_client_info_t *client_info = (const struct mqtt_connect_client_info_t *)arg;

    connected = (status == MQTT_CONNECT_ACCEPTED);

    switch (status)
    {
        case MQTT_CONNECT_ACCEPTED:
            PRINTF("MQTT client \"%s\" connected.\r\n", client_info->client_id);
            mqtt_subscribe_topics(client);
            break;

        case MQTT_CONNECT_DISCONNECTED:
            PRINTF("MQTT client \"%s\" not connected.\r\n", client_info->client_id);
            /* Try to reconnect 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_TIMEOUT:
            PRINTF("MQTT client \"%s\" connection timeout.\r\n", client_info->client_id);
            /* Try again 1 second later */
            sys_timeout(1000, connect_to_mqtt, NULL);
            break;

        case MQTT_CONNECT_REFUSED_PROTOCOL_VERSION:
        case MQTT_CONNECT_REFUSED_IDENTIFIER:
        case MQTT_CONNECT_REFUSED_SERVER:
        case MQTT_CONNECT_REFUSED_USERNAME_PASS:
        case MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_:
            PRINTF("MQTT client \"%s\" connection refused: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;

        default:
            PRINTF("MQTT client \"%s\" connection status: %d.\r\n", client_info->client_id, (int)status);
            /* Try again 10 seconds later */
            sys_timeout(10000, connect_to_mqtt, NULL);
            break;
    }
}

/*!
 * @brief Starts connecting to MQTT broker. To be called on tcpip_thread.
 */
static void connect_to_mqtt(void *ctx)
{
    LWIP_UNUSED_ARG(ctx);

    PRINTF("Connecting to MQTT broker at %s...\r\n", ipaddr_ntoa(&mqtt_addr));

    mqtt_client_connect(mqtt_client, &mqtt_addr, MQTT_BROKER_PORT, mqtt_connection_cb,
                        LWIP_CONST_CAST(void *, &mqtt_client_info), &mqtt_client_info);
}

/*!
 * @brief Called when publish request finishes.
 */
static void mqtt_message_published_cb(void *arg, err_t err)
{
    const char *topic = (const char *)arg;

    if (err == ERR_OK)
    {
        PRINTF("Published to the topic \"%s\".\r\n", topic);
    }
    else
    {
        PRINTF("Failed to publish to the topic \"%s\": %d.\r\n", topic, err);
    }
}

/*!
 * @brief Publishes a message. To be called on tcpip_thread.
 */
static void publish_message(void *ctx)
{
	static const char *topic   = MQTT_PUBLISH_TOPIC;

    static char publish_message[256]={0};

    memset(publish_message, 0, sizeof(publish_message));

/*
 * T -	DHT temperature
 * H -	DHT humidity
 * Hi-	DHT heat index
 * M1-	Soil moisture sensor 1
 * M2-	Soil moisture sensor 2
 * L -	Light level
 * PV-	Power supply voltage
 * PA-	Load current in mA
 * PW-	Load power in mW
 * SV-	Sensors and MCU voltage
 * F0-	Fan-0 pwm value
 * F1-	Fan-1 pwm value
 * WP-	Water Pump pwm value
 * GL-	small glow lights pwm value connected to irf520
 * CS-	CoB led grow light relay status
 * R -	RGB-R pwm value
 * G -	RGB-G pwm value
 * B -	RGB-B pwm value
 */

    sprintf(publish_message, "{\"d\":{\"T\":%.0f,\"H\":%.0f,\"Hi\":%.0f,\"M1\":%.0f,\"M2\":%.0f,\"L\":%.0f,\"PV\":%.1f,\"PA\":%.0f,\"PW\":%.0f,\"SV\":%.1f,\"F0\":%d,\"F1\":%d,\"WP\":%d,\"GL\":%d,\"CS\":%d,\"R\":%d,\"G\":%d,\"B\":%d}}", dht_readings[0], dht_readings[1], dht_readings[2], adc_readings[0], adc_readings[1], als_reading, power_readings[0], power_readings[1], power_readings[2], adc_readings[2],pwm_readings[4], pwm_readings[5], pwm_readings[6], pwm_readings[0], COB_status, pwm_readings[1], pwm_readings[2], pwm_readings[3]);

    LWIP_UNUSED_ARG(ctx);

    PRINTF("Going to publish to the topic \"%s\"...\r\n", topic);
    PRINTF("DATA: \"%s\"\r\n", publish_message);

    mqtt_publish(mqtt_client, topic, publish_message, strlen(publish_message), 2, 0, mqtt_message_published_cb, (void *)topic);
}

/*!
 * @brief Application thread.
 */
static void app_thread(void *arg)
{
    struct netif *netif = (struct netif *)arg;
    struct dhcp *dhcp;
    err_t err;
    int i;

    /* Wait for address from DHCP */

    PRINTF("Getting IP address from DHCP...\r\n");

    do
    {
        if (netif_is_up(netif))
        {
            dhcp = netif_dhcp_data(netif);
        }
        else
        {
            dhcp = NULL;
        }

        sys_msleep(20U);

    } while ((dhcp == NULL) || (dhcp->state != DHCP_STATE_BOUND));

    PRINTF("\r\nIPv4 Address     : %s\r\n", ipaddr_ntoa(&netif->ip_addr));
    PRINTF("IPv4 Subnet mask : %s\r\n", ipaddr_ntoa(&netif->netmask));
    PRINTF("IPv4 Gateway     : %s\r\n\r\n", ipaddr_ntoa(&netif->gw));

    /*
     * Check if we have an IP address or host name string configured.
     * Could just call netconn_gethostbyname() on both IP address or host name,
     * but we want to print some info if goint to resolve it.
     */
    if (ipaddr_aton(MQTT_BROKER_ADDRESS, &mqtt_addr) && IP_IS_V4(&mqtt_addr))
    {
        /* Already an IP address */
        err = ERR_OK;
    }
    else
    {
        /* Resolve MQTT broker's host name to an IP address */
        PRINTF("Resolving \"%s\"...\r\n", MQTT_BROKER_ADDRESS);
        err = netconn_gethostbyname(MQTT_BROKER_ADDRESS, &mqtt_addr);
    }

    if (err == ERR_OK)
    {
        /* Start connecting to MQTT broker from tcpip_thread */
        err = tcpip_callback(connect_to_mqtt, NULL);
        if (err != ERR_OK)
        {
            PRINTF("Failed to invoke broker connection on the tcpip_thread: %d.\r\n", err);
        }
    }
    else
    {
        PRINTF("Failed to obtain IP address: %d.\r\n", err);
    }

    /* Publish some messages */
    for (i = 0; i < 5000;)
    {
        if (connected)
        {
            err = tcpip_callback(publish_message, NULL);
            if (err != ERR_OK)
            {
                PRINTF("Failed to invoke publishing of a message on the tcpip_thread: %d.\r\n", err);
            }
            i++;
        }

        sys_msleep(10000U);
    }

    vTaskDelete(NULL);
}

static void generate_client_id(void)
{
    uint32_t mqtt_id[MQTT_ID_SIZE];
    int res;

    get_mqtt_id(&mqtt_id[0]);

    res = snprintf(client_id, sizeof(client_id), "nxp_%08lx%08lx%08lx%08lx", mqtt_id[3], mqtt_id[2], mqtt_id[1],
                   mqtt_id[0]);
    if ((res < 0) || (res >= sizeof(client_id)))
    {
        PRINTF("snprintf failed: %d\r\n", res);
        while (1)
        {
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    BaseType_t stat;

    static struct netif netif;
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
    static mem_range_t non_dma_memory[] = NON_DMA_MEMORY_ARRAY;
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
    ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;
    ethernetif_config_t enet_config = {
        .phyHandle  = &phyHandle,
        .macAddress = configMAC_ADDR,
#if defined(FSL_FEATURE_SOC_LPC_ENET_COUNT) && (FSL_FEATURE_SOC_LPC_ENET_COUNT > 0)
        .non_dma_memory = non_dma_memory,
#endif /* FSL_FEATURE_SOC_LPC_ENET_COUNT */
    };

    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    BOARD_ConfigMPU();
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

///////////////////////////////////////////////////////////////////
    init_ext_modules_i2c();

    pwm_module_begin(1000);
    power_module_begin();
	adc_module_begin();
	als_module_begin();
	dht_module_begin();

    PRINTF("Delay Start\n");

    for(int temp=0; temp<100; temp++){
//    	delay();
    }

	PRINTF("Delay End\n");

    enc_config_t mEncConfigStruct;

    /* Initialize the ENC module. */
    ENC_GetDefaultConfig(&mEncConfigStruct);
    /* Setup the hardware. */
    ENC_Init(ENC1, &mEncConfigStruct);
    /* Update position counter from initial position register. */
    ENC_DoSoftwareLoadInitialPositionValue(ENC1);

    ENC_ClearStatusFlags(ENC1, kENC_INDEXPulseFlag);

	PRINTF("Encoder init\n");

    /* DMA Mux init and EDMA init */
    edma_config_t edmaConfig = {0};
    EDMA_GetDefaultConfig(&edmaConfig);
    EDMA_Init(LPSPI_MASTER_DMA_BASEADDR, &edmaConfig);
#if (defined(FSL_FEATURE_SOC_DMAMUX_COUNT) && FSL_FEATURE_SOC_DMAMUX_COUNT)
    DMAMUX_Init(LPSPI_MASTER_DMA_MUX_BASEADDR);
#endif

    stat = xTaskCreate(GUI_task, "littlevgl", configMINIMAL_STACK_SIZE + 800, NULL, tskIDLE_PRIORITY + 2, NULL);

    if (pdPASS != stat)
    {
        PRINTF("Failed to create littlevgl task");
    }

////////////////////////////////////////////////////////////////////////////////

    BOARD_InitModuleClock();

    IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

    GPIO_PinInit(GPIO1, 4, &gpio_config);
    GPIO_PinInit(GPIO1, 22, &gpio_config);
    /* pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO1, 22, 1);
    GPIO_WritePinOutput(GPIO1, 4, 0);
    delay();
    GPIO_WritePinOutput(GPIO1, 4, 1);
    generate_client_id();

    mdioHandle.resource.csrClock_Hz = EXAMPLE_CLOCK_FREQ;

    IP4_ADDR(&netif_ipaddr, 0U, 0U, 0U, 0U);
    IP4_ADDR(&netif_netmask, 0U, 0U, 0U, 0U);
    IP4_ADDR(&netif_gw, 0U, 0U, 0U, 0U);

    tcpip_init(NULL, NULL);

    mqtt_client = mqtt_client_new();
    if (mqtt_client == NULL)
    {
        PRINTF("mqtt_client_new() failed.\r\n");
        while (1)
        {
        }
    }

    netifapi_netif_add(&netif, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, EXAMPLE_NETIF_INIT_FN,
                       tcpip_input);
    netifapi_netif_set_default(&netif);
    netifapi_netif_set_up(&netif);

    netifapi_dhcp_start(&netif);

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" MQTT client example\r\n");
    PRINTF("************************************************\r\n");

    if (sys_thread_new("app_task", app_thread, &netif, APP_THREAD_STACKSIZE, APP_THREAD_PRIO) == NULL)
    {
        LWIP_ASSERT("main(): Task creation failed.", 0);
    }

    vTaskStartScheduler();

    /* Will not get here unless a task calls vTaskEndScheduler ()*/
    return 0;
}

/*!
 * @brief Malloc failed hook.
 */
void vApplicationMallocFailedHook(void)
{
    for (;;)
        ;
}

/*!
 * @brief FreeRTOS tick hook.
 */
void vApplicationTickHook(void)
{
    if (s_lvgl_initialized)
    {
        lv_tick_inc(1);
    }
}

/*!
 * @brief Stack overflow hook.
 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
    (void)pcTaskName;
    (void)xTask;

    for (;;)
        ;
}

#endif
