#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"

// Variables para el botón y el antirrebote
uint8_t buttonState = 0; // Estado del botón (presionado o no)
uint8_t buttonPressFlag = 0; // Indicador de que se ha presionado el botón
uint8_t buttonInput;

// Función de antirrebote para el botón
void DebounceButton(void) {

    buttonInput = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    if (buttonInput == 0) { // Verifica si el botón está presionado
        if (buttonState == 0) { // Botón previamente no presionado
            buttonPressFlag = 1; // Indicador de que se ha presionado el botón
            buttonState = 1; // Cambia el estado del botón
        }
    } else { // Botón no presionado
        buttonState = 0; // Restablece el estado del botón
    }
}



void ledHandler(void) {
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(40000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
    SysCtlDelay(4000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0A);
    SysCtlDelay(40000000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x02);
    SysCtlDelay(40000000);

}

// Manejador de interrupción para el botón
void ButtonIntHandler(void) {
    // Limpia la interrupción del pin del botón
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    // Llama a la función de antirrebote para manejar el estado del botón
    DebounceButton();

}

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Configura el pin del botón (SW1) como entrada con resistencia de pull-up
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Configura el botón (SW1) como fuente de interrupción
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);

    // Habilita la interrupción del botón
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);

    // Registra el manejador de interrupción del botón
    GPIOIntRegister(GPIO_PORTF_BASE, ButtonIntHandler);


    // Configuración del sistema como se mencionó anteriormente
    //GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    // Configura el pin del botón (SW1) como entrada con resistencia de pull-up
    //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Configura el pin del LED rojo (PF1) como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);


    while (1) {
        // Verifica si el botón está presionado
        if (buttonPressFlag == 1) {
            // Si el botón está presionado, enciende el LED rojo
            ledHandler();
            buttonPressFlag = 0; // Restablece el indicador
        }
    }
}


