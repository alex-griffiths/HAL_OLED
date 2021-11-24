#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "oled.h"

/**
 * Writes a byte of data to the OLED device.
 *
 * @param OLED_Typedef *oled - A pointer to the OLED peripheral
 * @param uint32_t byte - The byte of data to send to the peripheral. These are
 *                        the values that will be sent to DB0-DB7
 * @param uint8_t np - The number of pins being used for the write. This allows
 *                     for flexible use of this function in both 8-bit and 4-bit
 *                     modes
 */
void OLED_send_byte(OLED_Typedef *oled, uint32_t byte, uint8_t np){
        // Trigger the OP EN
        HAL_GPIO_WritePin(oled->EN.Port, oled->EN.Pin, PIN_HIGH);

        for (int i = 0; i < np; i++) {
                int pin_num = np - 1 - i;
                HAL_GPIO_WritePin(oled->DB[pin_num].Port, oled->DB[pin_num].Pin,
                                  byte & (0x01 << pin_num));
        }

        // Set OP EN LOW.
        HAL_GPIO_WritePin(oled->EN.Port, oled->EN.Pin, PIN_LOW);
        delay_us(50); // Allow time until the next command.
}

/**
 * Send a command to the OLED peripheral
 *
 * @param OLED_Typedef *oled - A pointer to the OLED peripheral
 * @param uint32_t command - The command to send to the OLED peripheral
 *
 */
void OLED_send_command(OLED_Typedef *oled, uint32_t command){
        if (oled->FunctionMode == OLED_MODE_8BIT) {
                OLED8_send_command(oled, command);
        } else {
                OLED4_send_command(oled, command);
        }
}

/**
 * Sends an 8bit command to the OLED peripheral. This function is called by the
 * more general purpose OLED_send_command function
 *
 * @param OLED_Typedef *oled - A pointer to the OLED peripheral
 * @param uint32_t command - The command to send to the OLED peripheral
 *
 */
void OLED8_send_command(OLED_Typedef *oled, uint32_t command){
        // Set RS LOW
        HAL_GPIO_WritePin(oled->RS.Port, oled->RS.Pin, PIN_LOW);
        OLED_send_byte(oled, command, 8);
}

/**
 * Sends a 4bit command to the OLED peripheral. This function is called by the
 * more general purpose OLED_send_command function
 *
 * @param OLED_Typedef *oled - A pointer to the OLED peripheral
 * @param uint32_t command - The command to send to the OLED peripheral.
 *                           This command is formatted as a full 8 bit command
 *                           which is then shifted as required to meet the 4bit
 *                           requirements.
 *
 */
void OLED4_send_command(OLED_Typedef *oled, uint32_t command){
        HAL_GPIO_WritePin(oled->RS.Port, oled->RS.Pin, PIN_LOW);
        OLED_send_byte(oled, command, 4);
        OLED_send_byte(oled, command << 4, 4);
}

void OLED_send_data(OLED_Typedef *oled, uint8_t byte) {

    HAL_GPIO_WritePin(oled->RS.Port, oled->RS.Pin, PIN_HIGH);
    if (oled->FunctionMode == OLED_MODE_8BIT) {
        OLED_send_byte(oled, byte, 8);
    } else {
        OLED_send_byte(oled, byte, 4);
        OLED_send_byte(oled, byte << 4, 4);
    }

}

void OLED_write_str(OLED_Typedef *oled, uint8_t *str){
        while(*str) {
                OLED_send_data(oled, *str++);
        }
}

void OLED_write_line(OLED_Typedef *oled, uint8_t *str){
}

void OLED_move_cursor(OLED_Typedef *oled, uint16_t row, uint16_t col){
}

// A janky little delay function
void delay_us(volatile uint16_t delay){
    delay *= 4;
    while(delay--);
}

