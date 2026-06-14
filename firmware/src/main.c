/*
 * CT 321 PBL 07
 * Project: External Interrupt-Based Emergency Stop and Event Counter System
 * Target MCU: ATmega32
 * Clock: 8 MHz
 * IDE: MPLAB for VS Code / AVR-GCC compatible toolchain
 *
 * INT0 (PD2): Emergency stop button, active LOW
 * INT1 (PD3): Event pulse sensor/button, active LOW
 * INT2 (PB2): Recovery/reset button, active LOW
 * PB0: Green LED, PB1: Red LED, PB3: Buzzer
 * PD1/TXD: Serial output for event count
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DEBOUNCE_MS 200UL
#define LED_NORMAL  PB0
#define LED_STOP    PB1
#define BUZZER      PB3

volatile uint16_t event_count = 0;
volatile uint8_t emergency_mode = 0;
volatile uint8_t display_update_required = 1;
volatile uint32_t system_ms = 0;
volatile uint32_t last_int0_ms = 0;
volatile uint32_t last_int1_ms = 0;
volatile uint32_t last_int2_ms = 0;

static void uart_send_char(char c)
{
    while (!(UCSRA & (1 << UDRE))) {
        ;
    }
    UDR = c;
}

static void uart_send_text(const char *text)
{
    while (*text) {
        uart_send_char(*text++);
    }
}

static void uart_send_uint16(uint16_t value)
{
    char buffer[6];
    uint8_t index = 0;

    if (value == 0) {
        uart_send_char('0');
        return;
    }

    while (value > 0 && index < sizeof(buffer)) {
        buffer[index++] = (value % 10) + '0';
        value = value / 10;
    }

    while (index > 0) {
        uart_send_char(buffer[--index]);
    }
}

static void uart_init(void)
{
    /* 9600 baud at 8 MHz, normal speed: UBRR = 51 */
    UBRRH = 0;
    UBRRL = 51;
    UCSRB = (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

static void timer0_init(void)
{
    /* CTC mode, prescaler 64. 8 MHz / 64 = 125 kHz; OCR0 = 124 gives 1 ms. */
    TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00);
    OCR0 = 124;
    TIMSK |= (1 << OCIE0);
}

static void gpio_init(void)
{
    /* Interrupt inputs with internal pull-up resistors enabled. */
    DDRD &= ~((1 << PD2) | (1 << PD3));
    PORTD |= (1 << PD2) | (1 << PD3);

    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    /* Output pins for LEDs and buzzer. */
    DDRB |= (1 << LED_NORMAL) | (1 << LED_STOP) | (1 << BUZZER);
    PORTB &= ~((1 << LED_NORMAL) | (1 << LED_STOP) | (1 << BUZZER));
}

static void external_interrupts_init(void)
{
    /* INT0 falling edge: ISC01 = 1, ISC00 = 0 */
    MCUCR |= (1 << ISC01);
    MCUCR &= ~(1 << ISC00);

    /* INT1 falling edge: ISC11 = 1, ISC10 = 0 */
    MCUCR |= (1 << ISC11);
    MCUCR &= ~(1 << ISC10);

    /* INT2 falling edge: ISC2 = 0 */
    MCUCSR &= ~(1 << ISC2);

    /* Clear any pending interrupt flags before enabling. */
    GIFR |= (1 << INTF0) | (1 << INTF1) | (1 << INTF2);

    /* Enable INT0, INT1 and INT2. */
    GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);
}

static void update_outputs(uint8_t emergency)
{
    if (emergency) {
        PORTB &= ~(1 << LED_NORMAL);
        PORTB |= (1 << LED_STOP) | (1 << BUZZER);
    } else {
        PORTB |= (1 << LED_NORMAL);
        PORTB &= ~((1 << LED_STOP) | (1 << BUZZER));
    }
}

static void print_status(uint16_t count, uint8_t emergency)
{
    uart_send_text("Mode: ");
    uart_send_text(emergency ? "EMERGENCY STOP" : "NORMAL");
    uart_send_text(" | Count: ");
    uart_send_uint16(count);
    uart_send_text("\r\n");
}

ISR(TIMER0_COMP_vect)
{
    system_ms++;
}

ISR(INT0_vect)
{
    uint32_t now = system_ms;

    if ((now - last_int0_ms) >= DEBOUNCE_MS) {
        emergency_mode = 1;
        display_update_required = 1;
        last_int0_ms = now;
    }
}

ISR(INT1_vect)
{
    uint32_t now = system_ms;

    if ((now - last_int1_ms) >= DEBOUNCE_MS) {
        if (!emergency_mode) {
            event_count++;
            display_update_required = 1;
        }
        last_int1_ms = now;
    }
}

ISR(INT2_vect)
{
    uint32_t now = system_ms;

    if ((now - last_int2_ms) >= DEBOUNCE_MS) {
        if (emergency_mode) {
            emergency_mode = 0;
        } else {
            event_count = 0;
        }
        display_update_required = 1;
        last_int2_ms = now;
    }
}

int main(void)
{
    uint16_t local_count;
    uint8_t local_emergency;

    gpio_init();
    uart_init();
    timer0_init();
    external_interrupts_init();

    sei();

    uart_send_text("ATmega32 External Interrupt Event Counter System\r\n");

    while (1) {
        if (display_update_required) {
            cli();
            local_count = event_count;
            local_emergency = emergency_mode;
            display_update_required = 0;
            sei();

            update_outputs(local_emergency);
            print_status(local_count, local_emergency);
        }
    }

    return 0;
}
