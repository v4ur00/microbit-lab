#include "uart.h"
#include "gpio.h"

#define UART_REG ((NRF_UART_REG*)0x40002000)
typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED2a[1]; // ny
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED3[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED4[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED5[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED7a[1]; // ny
    volatile uint32_t PSEL_RTS;
    volatile uint32_t PSEL_TXD;
    volatile uint32_t PSEL_CTS;
    volatile uint32_t PSEL_RXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED7b[1]; // ny
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED8[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init() {

    // Enable input and output on pin 8 and 29
    GPIO0->PIN_CNF[8] = 0; // RXD
    GPIO0->PIN_CNF[29] = 1; // TXD

    // Set which pin 8 to RXD and pin 29 to TXD
    UART_REG->PSEL_RXD = 0x8;
    UART_REG->PSEL_TXD = 0x1D;

    // Set baudrate to 9600
    UART_REG->BAUDRATE = 0x00275000;

    // Disable RTS and CTS
    UART_REG->PSEL_RTS = (1 << 31);
    UART_REG->PSEL_CTS = (1 << 31);

    // Enable UART
    UART_REG->ENABLE = 0x4;
    // // Make UART recieve messages
    // UART_REG->TASKS_STARTRX = 1;

}

void uart_send(char letter) {
    // Start sending data
    UART_REG->TASKS_STARTTX = 1;
    

    // Load data to be sent into register
    uint32_t message = (uint32_t) letter;

    // Wait for confirmation that the byte has been sent
    for (int i = 4; i > 0; i--) {
        UART_REG->TXD = message;
        while ((UART_REG->EVENTS_TXDRDY & 0x1) == 0);
        message = message >> 8;
    };

    // Stop sending data
    UART_REG->TASKS_STOPTX = 1;

}

char uart_read() {
    // Start reading data
    char recieved_data;
    UART_REG->TASKS_STARTRX = 1;

    // Return '\0' if no messages recieved
    if ((UART_REG->EVENTS_RXDRDY & 0x1) == 0) return '\0';

    UART_REG->EVENTS_RXDRDY = 0;
    recieved_data = (char) UART_REG->RXD;

    // Stop recieving data
    UART_REG->TASKS_STOPRX = 1; // This might be wrong !!!!!!!

    return recieved_data;

}

