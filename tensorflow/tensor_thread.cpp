
#include "tensor_thread.h"

#include "main_functions.h"

#include "mbed.h"

static Thread* tensor_thread = NULL;

static void tensor_thread_main(void);

void tensor_thread_init(void)
{
    tensor_thread = new Thread(osPriorityNormal, TENSOR_THREAD_STACK_SIZE , NULL, "mqtt_service");
}

void tensor_thread_start(void)
{
    
    if (tensor_thread) {
//        printf("\n before tensor_thread_start \n");
        tensor_thread->start(tensor_thread_main);
//        printf("\n after tensor_thread_start \n");
    }
}

static void tensor_thread_main(void)
{
//    printf("tensor_thread_main() before setup\r\n");
    setup();
//    printf("tensor_thread_main() after setup\r\n");

    for (;;) {
//        printf("tensor_thread_main() in the loop()   \r\n");
        loop();
//        printf("tensor_thread_main() after loop()   \r\n");
        ThisThread::yield();
    }
}
