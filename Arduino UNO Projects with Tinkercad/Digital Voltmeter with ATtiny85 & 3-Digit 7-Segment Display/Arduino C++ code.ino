/*
 * Project 23: Digital Voltmeter with ATtiny85 & 3-Digit 7-Segment Display
 * Author: Md. Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Reads analog voltage using ATtiny85 ADC,
 *              converts it to voltage, and displays it using
 *              3 multiplexed 7-segment displays via 74HC595 shift register.
 * Hardware: ATtiny85, 1x potentiometer, 1x 74HC595, 3x 7-segment display,
 *           1x 2kΩ, 1x 750Ω, 8x 100Ω resistors, USB 5V supply.
 */

#define NOP() asm ("nop")
long V=0; // Variable to store calculated voltage
const unsigned char DIGH[] = {
    //00 01    02   03  04 
    //0   1     2   3   4
    0x3F,  0x06, 0x5B, 0x4F, 0x66,
    // 05   06    07   08   09  10
    // 5   6     7    8    9   10
    0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x40
};
unsigned char DISP[3] = {0, 0, 0}; // Array to hold display values
boolean flag = 0 ; // Flag for display update
unsigned char period = 0; // Variable to control display update frequency

void setup() {
    DDRB=0X1F; // Set PB0-PB4 as output (for 74HC595 and segments)
    PORTB=0X1C; // Initialize segments to off (PB0-PB4 low)
    TCCR0A=(1<<WGM01); // Set Timer0 to CTC mode
    TCCR0B=(1<<CS02); // Set Timer0 prescaler to 256

    TCNT0=0X00; // Correction: Use TCNT0 (not TCNTO) for Timer0 counter register

    OCR0A=0X95; // Set Timer0 compare value for 100ms period
    OCR0B=0X00;
    TIMSK=(1<<OCIE0A); // Correction: Use TIMSK (not TIMSK0) for ATtiny85

    DIDR0=(1<<ADC0D); // Disable digital input on ADC0 (PB2)
    ADMUX=0X00;
    ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);   // Enable ADC, set prescaler to 64
    ADCSRB=0X00; // Free running mode
    sei(); // Enable global interrupts
}
void loop() {
    if (!flag)
        return;
    int v = adcRead0(); // declare v as int
    if (v == 1023) { // use == for comparison, not =
        DISP[2] = DISP[1] = DISP[0] = 10; // Display "Err" for over-range
    }
    else { // typo: esle -> else
        V = (v * 160L) / 1023L;
        DISP[2] = V / 100;
        DISP[1] = (V / 10) % 10;
        DISP[0] = V % 10;
    }
    flag = false;
}
void softDelay(unsigned char dl)
{
    for (; dl>0; dl--  );
}
void transmit(unsigned char bt)
{
    unsigned char j;
    for (j=0; j<8; j++) {
        if (bt & 0x80) 
            PORTB |= (1<<PB0); // Set data pin high
         else 
            PORTB &= ~(1<<PB0); // Set data pin low
            NOP(); // No operation for timing
        PORTB |= (1<<0); // Set latch pin high
        NOP(); // No operation for timing   
        PORTB &= ~(1<<PB0); // Set latch pin low
        // Clock the data into the shift register
        bt <<= 1; // Shift left for next bit
    }
    NOP(); // No operation for timing
    PORTB &=~(1<<0); // Set latch pin low to update display
    NOP(); // No operation for timing
    PORTB |= (1<<0); // Set latch pin high to apply changes
}
ISR(TIM0_COMPA_vect) {
    static unsigned char p = 0;
    unsigned char s;
    PORTB |= 0x1C;
    s = DIGH[DISP[p]];
    transmit(s);
    PORTB &= ~(4 << p);
    p++;
    if (p == 3) p = 0;
    period++;
    if (period == 25) {
        period = 0;
        flag = true;
    }
}
int adcRead0(void) {
    ADMUX = 0x00;
    softDelay(10);
    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);
    return (((int)ADCL) | ((int)ADCH << 8));
}

// --- USB Overcurrent/Overflow Issue Advice ---

/*
 * If your USB port is overloaded or shuts down when running this code,
 * the most likely causes are:
 * 1. Too much current drawn by the 7-segment displays (especially if all segments are ON).
 * 2. Not using current-limiting resistors for each segment.
 * 3. Multiplexing is not fast enough, so multiple digits are ON at once.
 *
 * Solutions:
 * - Make sure you have a 100Ω resistor in series with each segment pin (total 8 resistors).
 * - Use 2kΩ and 750Ω resistors for digit/common lines as per your circuit plan.
 * - Never connect 7-segment displays directly to 5V or GND without resistors.
 * - If possible, reduce the ON time for each digit (make multiplexing faster).
 * - Power the circuit from an external 5V adapter if your USB port cannot supply enough current.
 * - Double-check wiring for shorts or mistakes.
 *
 * Example: If all segments of all digits are ON at once, current can exceed USB limits.
 * Proper multiplexing and resistors are essential!
 */