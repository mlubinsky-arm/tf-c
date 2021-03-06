// ----------------------------------------------------------------------------
// Copyright 2016-2019 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------
#ifndef MBED_TEST_MODE
#include "mbed.h"
#include "kv_config.h"
#include "mbed-cloud-client/MbedCloudClient.h" // Required for new MbedCloudClient()
#include "factory_configurator_client.h"       // Required for fcc_* functions and FCC_* defines
#include "m2mresource.h"                       // Required for M2MResource

#include "mbed-trace/mbed_trace.h"             // Required for mbed_trace_*

#include "cypress_capsense.h"
#include "blinker_app.h"


#include "get_temp.h"

#define TF_MICRO

#ifdef TF_MICRO
#include "tensor_thread.h"
#endif

// Pointers to the resources that will be created in main_application().
static MbedCloudClient *cloud_client;
static bool cloud_client_running = true;
static NetworkInterface *network = NULL;

// Fake entropy needed for non-TRNG boards. Suitable only for demo devices.
const uint8_t MBED_CLOUD_DEV_ENTROPY[] = { 0xf6, 0xd6, 0xc0, 0x09, 0x9e, 0x6e, 0xf2, 0x37, 0xdc, 0x29, 0x88, 0xf1, 0x57, 0x32, 0x7d, 0xde, 0xac, 0xb3, 0x99, 0x8c, 0xb9, 0x11, 0x35, 0x18, 0xeb, 0x48, 0x29, 0x03, 0x6a, 0x94, 0x6d, 0xe8, 0x40, 0xc0, 0x28, 0xcc, 0xe4, 0x04, 0xc3, 0x1f, 0x4b, 0xc2, 0xe0, 0x68, 0xa0, 0x93, 0xe6, 0x3a };

static M2MResource* m2m_get_res;
static M2MResource* m2m_get_res_led_rate;
static M2MResource* m2m_get_res_led_rate_min;
static M2MResource* m2m_get_res_led_rate_max;
static M2MResource* m2m_put_res;
static M2MResource* m2m_post_res;
static M2MResource* m2m_deregister_res;

Thread res_thread;
EventQueue res_queue;

DigitalOut thermVDD(P10_3,1);
DigitalOut thermGND(P10_0,0);
//AnalogIn thermOut(P10_1);
DigitalOut led(LED1);

#define ARR_SIZE 10    //to store 10 temperature points
#define BUFF_SIZE   100 // used by td rest api

float temp_value[ARR_SIZE];
volatile int temp_index =0;

void init_temp(){
    printf("init_temp() \n\n");
    for (int i=0; i<ARR_SIZE; i++){
      temp_value[i]=20.0f;
    }
    printf("\n");
}
/*
float readTemp()
{
    float refVoltage = thermOut.read() * 2.4; // Range of ADC 0->2*Vref
    float refCurrent = refVoltage  / 10000.0; // 10k Reference Resistor
    float thermVoltage = 3.3 - refVoltage;    // Assume supply voltage is 3.3v
    float thermResistance = thermVoltage / refCurrent;
    float logrT = (float32_t)log((float64_t)thermResistance);

    // Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation 
    float stEqn = (float32_t)((0.0009032679) + ((0.000248772) * logrT) +
                             ((2.041094E-07) * pow((float64)logrT, (float32)3)));

    float temperatureC = (float32_t)(((1.0 / stEqn) - 273.15)  + 0.5);
    return temperatureC;
}
*/
void print_client_ids(void)
{
    printf("Account ID: %s\n", cloud_client->endpoint_info()->account_id.c_str());
    printf("Endpoint name: %s\n", cloud_client->endpoint_info()->internal_endpoint_name.c_str());
    printf("Device ID: %s\n\n", cloud_client->endpoint_info()->endpoint_name.c_str());
}

void button_press(void)
{
    m2m_get_res->set_value(m2m_get_res->get_value_int() + 1);
    printf("Counter %" PRIu64 "\n", m2m_get_res->get_value_int());
}

void put_update(const char* /*object_name*/)
{
    printf("PUT update %d\n", (int)m2m_put_res->get_value_int());
}

void execute_post(void* /*arguments*/)
{
    printf("POST executed\n");
}

void deregister_client(void)
{
    printf("Unregistering and disconnecting from the network.\n");
    cloud_client->close();
}

void deregister(void* /*arguments*/)
{
    printf("POST deregister executed\n");
    m2m_deregister_res->send_delayed_post_response();

    deregister_client();
}

void client_registered(void)
{
    printf("Client registered.\n");
    print_client_ids();
}

void client_unregistered(void)
{
    printf("Client unregistered.\n");
    (void) network->disconnect();
    cloud_client_running = false;
}

void client_error(int err)
{
    printf("client_error(%d) -> %s\n", err, cloud_client->error_description());
}

void update_progress(uint32_t progress, uint32_t total)
{
    uint8_t percent = (uint8_t)((uint64_t)progress * 100 / total);
    printf("Update progress = %" PRIu8 "%%\n", percent);
}

void update_resources(void)
{
    m2m_get_res_led_rate->set_value(blinker_rate_get());
    printf("Blink Rate %" PRIu64 "\n", m2m_get_res_led_rate->get_value_int());
}

int main(void)
{
    int status;

    while(1 > 2){
    //   printf("temp=%f", readTemp());
       printf("temp=%f", get_temp());
    }

#ifdef TF_MICRO
    tensor_thread_init();
    tensor_thread_start();
#endif
    status = mbed_trace_init();
    if (status != 0) {
        printf("mbed_trace_init() failed with %d\n", status);
        return -1;
    }

    // Mount default kvstore
    printf("Application ready\n");
    status = kv_init_storage_config();
    if (status != MBED_SUCCESS) {
        printf("kv_init_storage_config() - failed, status %d\n", status);
        return -1;
    }

    // Connect with NetworkInterface
    printf("Connect to network\n");
    network = NetworkInterface::get_default_instance();
    if (network == NULL) {
        printf("Failed to get default NetworkInterface\n");
        return -1;
    }
    status = network->connect();
    if (status != NSAPI_ERROR_OK) {
        printf("NetworkInterface failed to connect with %d\n", status);
        return -1;
    }

    printf("Network initialized, connected with IP %s\n\n", network->get_ip_address());

    // Run developer flow
    printf("Start developer flow\n");
    status = fcc_init();
    if (status != FCC_STATUS_SUCCESS) {
        printf("fcc_init() failed with %d\n", status);
        return -1;
    }

    // Inject hardcoded entropy for the device. Suitable only for demo devices.
    (void) fcc_entropy_set(MBED_CLOUD_DEV_ENTROPY, sizeof(MBED_CLOUD_DEV_ENTROPY));
    status = fcc_developer_flow();
    if (status != FCC_STATUS_SUCCESS && status != FCC_STATUS_KCM_FILE_EXIST_ERROR && status != FCC_STATUS_CA_ERROR) {
        printf("fcc_developer_flow() failed with %d\n", status);
        return -1;
    }

    printf("Initializing Capacitive Touch Sensors\n");

    if(capsense_main() != 0)
    {
        printf("Capacitive Touch Sensors failed to initialize \n");
        return -1;
    }

    blinker_init();

    printf("Create resources\n");
    M2MObjectList m2m_obj_list;

    // GET resource 3200/0/5501
    m2m_get_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 3200, 0, 5501, M2MResourceInstance::INTEGER, M2MBase::GET_ALLOWED);
    if (m2m_get_res->set_value(0) != true) {
        printf("m2m_get_res->set_value() failed\n");
        return -1;
    }

    // Resource for storing led blink rate
    // GET resource current rate
    m2m_get_res_led_rate = M2MInterfaceFactory::create_resource(m2m_obj_list, 3346, 0, 5700, M2MResourceInstance::INTEGER, M2MBase::GET_ALLOWED);
    if (m2m_get_res_led_rate->set_value(0) != true) {
        printf("m2m_get_res_led_rate->set_value() failed\n");
        return -1;
    }

    // GET resource min rate
    m2m_get_res_led_rate_min = M2MInterfaceFactory::create_resource(m2m_obj_list, 3346, 0, 5603, M2MResourceInstance::INTEGER, M2MBase::GET_ALLOWED);
    if (m2m_get_res_led_rate_min->set_value(0) != true) {
        printf("m2m_get_res_led_rate_min->set_value() failed\n");
        return -1;
    }

    // GET resource max rate
    m2m_get_res_led_rate_max = M2MInterfaceFactory::create_resource(m2m_obj_list, 3346, 0, 5604, M2MResourceInstance::INTEGER, M2MBase::GET_ALLOWED);
    if (m2m_get_res_led_rate_max->set_value(7) != true) {
        printf("m2m_get_res_led_rate_max->set_value() failed\n");
        return -1;
    }

    // Resource for generic variable
    // PUT resource 3201/0/5853
    m2m_put_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 3201, 0, 5853, M2MResourceInstance::INTEGER, M2MBase::GET_PUT_ALLOWED);
    if (m2m_put_res->set_value(0) != true) {
        printf("m2m_led_res->set_value() failed\n");
        return -1;
    }
    if (m2m_put_res->set_value_updated_function(put_update) != true) {
        printf("m2m_put_res->set_value_updated_function() failed\n");
        return -1;
    }

    // POST resource 3201/0/5850
    m2m_post_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 3201, 0, 5850, M2MResourceInstance::INTEGER, M2MBase::POST_ALLOWED);
    if (m2m_post_res->set_execute_function(execute_post) != true) {
        printf("m2m_post_res->set_execute_function() failed\n");
        return -1;
    }

    // POST resource 5000/0/1 to trigger deregister.
    m2m_deregister_res = M2MInterfaceFactory::create_resource(m2m_obj_list, 5000, 0, 1, M2MResourceInstance::INTEGER, M2MBase::POST_ALLOWED);

    // Use delayed response
    m2m_deregister_res->set_delayed_response(true);

    if (m2m_deregister_res->set_execute_function(deregister) != true) {
        printf("m2m_post_res->set_execute_function() failed\n");
        return -1;
    }

    printf("Register Pelion Device Management Client\n\n");

#ifdef MBED_CLOUD_CLIENT_SUPPORT_UPDATE
    cloud_client = new MbedCloudClient(client_registered, client_unregistered, client_error, NULL, update_progress);
#else
    cloud_client = new MbedCloudClient(client_registered, client_unregistered, client_error);
#endif // MBED_CLOUD_CLIENT_SUPPORT_UPDATE

    cloud_client->add_objects(m2m_obj_list);
    cloud_client->setup(network); // cloud_client->setup(NULL); -- https://jira.arm.com/browse/IOTCLT-3114

    //start a thread to update resources once every 2 seconds
    res_thread.start(callback(&res_queue, &EventQueue::dispatch_forever));
    res_queue.call_every(2000, update_resources);

/*
    while(cloud_client_running) {
        int in_char = getchar();
        if (in_char == 'i') {
            print_client_ids(); // When 'i' is pressed, print endpoint info
            continue;
        } else if (in_char == 'r') {
            (void) fcc_storage_delete(); // When 'r' is pressed, erase storage and reboot the board.
            printf("Storage erased, rebooting the device.\n\n");
            wait(1);
            NVIC_SystemReset();
        } else if (in_char > 0 && in_char != 0x03) { // Ctrl+C is 0x03 in Mbed OS and Linux returns negative number
            button_press(); // Simulate button press
            continue;
        }
        deregister_client();
        break;
    }
*/
    return 0;
}

#endif /* MBED_TEST_MODE */
