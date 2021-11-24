This is just a basic OLED libray.

It has been tested using the Newhaven NHD-0420ZW-AY6 OLED display using an STM32
F446RE Nucleo dev board. It has also primarily only been tested in 8-Bit mode.

For more information about this display specifically, check the datasheet.

## Initialisation

When defining the OLED_Typedef structure, there are three modes, `FunctionMode`, `EntryMode` and `FontMode`. Only `FunctionMode` is required for proper operation of the OLED. This is due to its usage when determining how to send bytes to the OLED peripheral.

Each OLED will probably have different initialisation sequences. For the 0420ZW-AY6 
display in 8-bit mode, use the following:

```c
void init_oled(OLED_Typedef *oled) {
        HAL_Delay(500); // Wait for power stabilisation

        OLED_send_command(oled, oled->FunctionMode | OLED_FONT_WEU1); // Set the function and font modes
        delay_us(600);
        OLED_send_command(oled, OLED_DISPLAY_OFF);
        delay_us(600);
        OLED_send_command(oled, OLED_CLEAR);
        HAL_Delay(2);
        OLED_send_command(oled, OLED_ENTRY_INC);
        delay_us(600);
        OLED_send_command(oled, OLED_HOME);
        delay_us(600);
        OLED_send_command(oled, OLED_DISPLAY_ON | OLED_CURSOR_ON 
                                | OLED_CURSOR_BLINK);
        delay_us(600);
}

```
