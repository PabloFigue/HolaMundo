#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"

// Variables para el bot�n y el antirrebote
uint8_t buttonState = 0; // Estado del bot�n (presionado o no)
uint8_t buttonPressFlag = 0; // Indicador de que se ha presionado el bot�n
uint8_t buttonInput;

// Funci�n de antirrebote para el bot�n
void DebounceButton(void) {

    buttonInput = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    if (buttonInput == 0) { // Verifica si el bot�n est� presionado
        if (buttonState == 0) { // Bot�n previamente no presionado
            buttonPressFlag = 1; // Indicador de que se ha presionado el bot�n
            buttonState = 1; // Cambia el estado del bot�n
        }
    } else { // Bot�n no presionado
        buttonState = 0; // Restablece el estado del bot�n
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

// Manejador de interrupci�n para el bot�n
void ButtonIntHandler(void) {
    // Limpia la interrupci�n del pin del bot�n
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
    // Llama a la funci�n de antirrebote para manejar el estado del bot�n
    DebounceButton();

}

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Configura el pin del bot�n (SW1) como entrada con resistencia de pull-up
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Configura el bot�n (SW1) como fuente de interrupci�n
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);

    // Habilita la interrupci�n del bot�n
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);

    // Registra el manejador de interrupci�n del bot�n
    GPIOIntRegister(GPIO_PORTF_BASE, ButtonIntHandler);


    // Configuraci�n del sistema como se mencion� anteriormente
    //GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    // Configura el pin del bot�n (SW1) como entrada con resistencia de pull-up
    //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Configura el pin del LED rojo (PF1) como salida
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);


    while (1) {
        // Verifica si el bot�n est� presionado
        if (buttonPressFlag == 1) {
            // Si el bot�n est� presionado, enciende el LED rojo
            ledHandler();
            buttonPressFlag = 0; // Restablece el indicador
        }
    }
}


