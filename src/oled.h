//
// OLED Library. Written by Alex Griffiths 2021
//
// This library has been tested on the Newhaven NHD-0420ZW-AY6.
//

#ifndef OLED_H
#define OLED_H

typedef struct {
        uint16_t FunctionMode;
        uint16_t EntryMode;
        uint16_t FontMode;
        OLED_Pin RS;
        OLED_Pin EN;
        OLED_Pin[] DB;

} OLED_Typedef;

typedef struct {
        GPIO_Type *Port;
        uint32_t Pin;
} OLED_Pin;

/**
 * Function Prototypes
 */
void OLED_send_byte(OLED_Typedef *oled, uint32_t byte);
void OLED_send_command(OLED_Typedef *oled, uint32_t command);
void OLED8_send_command(OLED_Typedef *oled, uint32_t command);
void OLED4_send_command(OLED_Typedef *oled, uint32_t command);
void OLED_write_str(OLED_Typedef *oled, uint8_t *str);
void OLED_write_line(OLED_Typedef *oled, uint8_t *str);
void OLED_move_cursor(OLED_Typedef *oled, uint16_t row, uint16_t col);

/**
 * Command value definitions
 */

#define OLED_CLEAR                      (0x001U) // Clears the display
#define OLED_HOME                       (0x002U) // Sets DDRAM address to 0x00 
#define OLED_DISPLAY_ON                 (0x00CU) // Turns the display on
#define OLED_DISPLAY_OFF                (0x008U) // Turns the display off

/**
 * Entry Modes
 *
 * Entry modes can be ORd together to combine them. Typical use would be
 * OLED_ENTRY_INC | OLED_ENTRY_SHIFTR
 */

#define OLED_ENTRY_INC                  (0x006U) // Auto-inc DDRAM
#define OLED_ENTRY_DEC                  (0x004U) // Auto-inc DDRAM
#define OLED_ENTRY_SHIFTL               (0x004U) // Shift display to left
#define OLED_ENTRY_SHIFTR               (0x005U) // Shift display to left

/**
 * Cursor modes
 *
 * These values determine how the cursor on the OLED behaves and should be ORd
 * together with OLED_DISPLAY_ON or OLED_DISPLAY_OFF
 */
#define OLED_CURSOR_ON                  (0x00AU) // Turn the cursor on
#define OLED_CURSOR_OFF                 (0x008U) // Turn cursor off
#define OLED_CURSOR_BLINK               (0x009U) // BLinks the cursor
#define OLED_CURSOR_NBLINK              (0x008U) // Cursor does not blink

/**
 * Cursor/Display shifting.
 *
 * Display shifts do not change the Address Counter.
 */
#define OLED_CURSOR_SHIFT_LEFT          (0x010U) // Shifts cursor one pos left
#define OLED_CURSOR_SHIFT_RIGHT         (0x014U) // Shifts cursor one pos right
#define OLED_DISPLAY_SHIFT_LEFT         (0x018U) // Shift display to the left
#define OLED_DISPLAY_SHIFT_RIGHT        (0x01CU) // Shift display to the right

/**
 * Function/Font modes
 */
#define OLED_MODE_8BIT                  (0x038U) 
#define OLED_MODE_4BIT                  (0x028U)
#define OLED_FONT_ENJP                  (0x028U) // English/Japanese
#define OLED_FONT_WEU1                  (0x029U) // Western European #1
#define OLED_FONT_ENRU                  (0x02AU) // English/Russian
#define OLED_FONT_WEU2                  (0x02BU) // Western European #2

// @TODO: Implement Read/Write for CGRAM and DDRAM

#endif 
