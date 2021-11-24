void init_oled(OLED_Typedef *oled) {

    HAL_Delay(500);
    OLED_send_command(oled, 0b0000111001); // Function set
    delay_us(600);
    OLED_send_command(oled, 0b0000001011); // Display off
    HAL_Delay(6);
    OLED_send_command(oled, 0b0000000001); // display clear
    delay_us(600);
    OLED_send_command(oled, 0b0000000110); // entry mode
    delay_us(600);
    OLED_send_command(oled, 0b0000000010); // home display
    delay_us(600);
    OLED_send_command(oled, 0b0000001111); // display on
}

