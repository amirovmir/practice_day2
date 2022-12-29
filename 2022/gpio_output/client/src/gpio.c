#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpio/gpio.h>
#include <stdbool.h>

#ifdef __arm__
#include <bsp/bsp.h>
#endif

#define GPIO_PIN_NUM_IN1 12U
#define GPIO_PIN_NUM_IN2 13U
#define GPIO_PIN_NUM_ENA 6U
#define GPIO_PIN_NUM_IN4 20U
#define GPIO_PIN_NUM_IN3 21U
#define GPIO_PIN_NUM_ENB 26U
#define DELAY_S 2

#define HIGH 1
#define LOW 0

/**
 * exceptionPinArr is an array of GPIO pin numbers that should be excluded
 * from the example. This may be necessary if some of the pins are already
 * used for other functions, for example, if the pins are used for UART
 * connections during debugging.
 */
//const int exceptionPinArr[] = {14, 15};
//const int pinArr[] = {GPIO_PIN_NUM_IN1, GPIO_PIN_NUM_IN2, GPIO_PIN_NUM_IN3, GPIO_PIN_NUM_IN4, GPIO_PIN_NUM_ENA, GPIO_PIN_NUM_ENB};

/*static bool IsExceptionPin(int pin)
{
    bool ret = false;

    for(int i = 0; i < sizeof(exceptionPinArr) / sizeof(int); i++)
    {
        if(exceptionPinArr[i] == pin)
        {
            ret = true;

            break;
        }
    }

    return ret;
}*/

void forward(GpioHandle* handle){
    fprintf(stderr, "forward\n");
    GpioOut(*handle, GPIO_PIN_NUM_IN1, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, HIGH);
}

void stop(GpioHandle* handle) {
    GpioOut(*handle, GPIO_PIN_NUM_IN1, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, LOW);
}

void backward(GpioHandle* handle) {
    fprintf(stderr, "backward\n");
    GpioOut(*handle, GPIO_PIN_NUM_IN1, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, HIGH);
}

void left(GpioHandle* handle) {
    fprintf(stderr, "left\n");
    GpioOut(*handle, GPIO_PIN_NUM_IN1, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, HIGH);
}

void right(GpioHandle* handle) {
     fprintf(stderr, "right\n");
    GpioOut(*handle, GPIO_PIN_NUM_IN1, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_IN4, LOW);
    GpioOut(*handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(*handle, GPIO_PIN_NUM_ENB, HIGH);
}

void trajectory(GpioHandle* handle) {
    forward(handle);
    sleep(2);
    //stop(handle);
    //right(handle);
    //sleep(1);
   // stop(handle);
}

int main(int argc, const char *argv[])
{
    fprintf(stderr, "Start GPIO_output test\n");

#ifdef __arm__
    /**
     * InitializeGPIO_PIN_NUM board support package (BSP) driver and set configuration
     * for GPIO pins. It`s required for stdout by UART.
     */
    {
        BspError rc = BspInit(NULL);
        if (rc != BSP_EOK)
        {
            fprintf(stderr, "Failed to initialize BSP\n");
            return EXIT_FAILURE;
        }

        rc = BspSetConfig("gpio0", "raspberry_pi4b.default");
        if (rc != BSP_EOK)
        {
            fprintf(stderr, "Failed to set mux configuration for gpio0 module\n");
            return EXIT_FAILURE;
        }
    }
#endif

    if (GpioInit())
    {
        fprintf(stderr, "GpioInit failed\n");
        return EXIT_FAILURE;
    }

    /* initialize and setup gpio0 port */
    GpioHandle handle = NULL;
    if (GpioOpenPort("gpio0", &handle) || handle == GPIO_INVALID_HANDLE)
    {
        fprintf(stderr, "GpioOpenPort failed\n");
        return EXIT_FAILURE;
    }

    GpioSetMode(handle, GPIO_PIN_NUM_IN1, GPIO_DIR_OUT);
    GpioSetMode(handle, GPIO_PIN_NUM_IN2, GPIO_DIR_OUT);
    GpioSetMode(handle, GPIO_PIN_NUM_IN3, GPIO_DIR_OUT);
    GpioSetMode(handle, GPIO_PIN_NUM_IN4, GPIO_DIR_OUT);
    GpioSetMode(handle, GPIO_PIN_NUM_ENA, GPIO_DIR_OUT);
    GpioSetMode(handle, GPIO_PIN_NUM_ENB, GPIO_DIR_OUT);

    //GpioOut(handle, GPIO_PIN_NUM_ENA, HIGH);
    //GpioOut(handle, GPIO_PIN_NUM_ENB, HIGH);
/*
    for(int i = 0; i < sizeof(pinArr); i++)
    {
            if (GpioSetMode(handle, pinArr[i], GPIO_DIR_OUT))
            {
                fprintf(stderr, "GpioSetMode for GPIO%d failed\n", i);
                return -1;
            }
    }
    */
    fprintf(stderr, "Starting move\n");
   // trajectory(*handle);

    GpioOut(handle, GPIO_PIN_NUM_IN1, HIGH);
    GpioOut(handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(handle, GPIO_PIN_NUM_IN4, HIGH);
    GpioOut(handle, GPIO_PIN_NUM_ENA, HIGH);
    GpioOut(handle, GPIO_PIN_NUM_ENB, HIGH);

    sleep(50);

    GpioOut(handle, GPIO_PIN_NUM_IN1, LOW);
    GpioOut(handle, GPIO_PIN_NUM_IN2, LOW);
    GpioOut(handle, GPIO_PIN_NUM_IN3, LOW);
    GpioOut(handle, GPIO_PIN_NUM_IN4, LOW);
    GpioOut(handle, GPIO_PIN_NUM_ENA, LOW);
    GpioOut(handle, GPIO_PIN_NUM_ENB, LOW);

    if(GpioClosePort(handle))
    {
        fprintf(stderr, "GpioClosePort failed\n");
        return EXIT_FAILURE;
    }

    fprintf(stderr, "Test finished.\n");

    return EXIT_SUCCESS;
}