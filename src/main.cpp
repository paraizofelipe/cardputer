#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <M5Cardputer.h>
#include <M5GFX.h>
#include <WiFi.h>

#include "images.h"

int indexMarked = 0;
const int statusBarHeight = 20;
bool isBooted = false;

int item_selected = 0;
int item_sel_previous;
int item_sel_next;

int current_screen = 0;

const char* ssid = "";
const char* password = "";

const char* URL = "https://api.spaceflightnewsapi.net/v4/articles/";

const int NUM_ITEMS = 5;
const int MAX_ITEMS_LENGTH = 20;

char menu_itens[NUM_ITEMS][MAX_ITEMS_LENGTH] = {"Wi-fi", "Bluetooth",
                                                "Smart Home", "SD Card", "Battery"};

const unsigned char* bitmap_icons[5] = {
    wifi_icon,
    bluetooth_icon,
    smart_home_icon,
    sdcard_icon,
    battery_icon,
};

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    M5Cardputer.Display.setRotation(1);

    M5Cardputer.Display.setTextColor(GREEN);
    M5Cardputer.Display.setTextSize(2.4);

}

void loop() {
    M5Cardputer.update();

    // if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed())
    // {
    //     if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
    //         if (WiFi.status() == WL_CONNECTED) {
    //             M5Cardputer.Display.clearDisplay();
    //             HTTPClient http;
    //
    //             http.begin(URL);
    //             int httpResonseCode = http.GET();
    //
    //             if (httpResonseCode > 0) {
    //                 M5Cardputer.Display.printf("HTTP Response code: %d\n",
    //                                            httpResonseCode);
    //
    //                 String payload = http.getString();
    //
    //                 JsonDocument doc;
    //                 deserializeJson(doc, payload);
    //
    //                 String status = doc["next"];
    //                 M5Cardputer.Display.printf("Next: %s\n", status);
    //             } else {
    //                 M5Cardputer.Display.printf("Error code: %d\n",
    //                                            httpResonseCode);
    //             }
    //         } else {
    //             M5Cardputer.Display.println("Falha na conexão");
    //         }
    //     }
    // }

    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        if (M5Cardputer.Keyboard.isKeyPressed('.')) {
            item_selected = item_selected + 1;
            if (item_selected >= NUM_ITEMS) {
                item_selected = 0;
            }
            M5Cardputer.Display.clearDisplay();
        }

        if (M5Cardputer.Keyboard.isKeyPressed(';')) {
            item_selected = item_selected - 1;
            if (item_selected < 0) {
                item_selected = NUM_ITEMS - 1;
            }
            M5Cardputer.Display.clearDisplay();
        }

        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
            current_screen = item_selected;
        }
    }

    item_sel_previous = item_selected - 1;
    if (item_sel_previous < 0) {
        item_sel_previous = NUM_ITEMS - 1;
    }

    item_sel_next = item_selected + 1;
    if (item_sel_next >= NUM_ITEMS) {
        item_sel_next = 0;
    }

    // previus item
    M5Cardputer.Display.drawBitmap(12, 10, bitmap_icons[item_sel_previous], 25,
                                   25, GREEN);
    M5Cardputer.Display.drawString(menu_itens[item_sel_previous], 50, 10);

    // selected item
    M5Cardputer.Display.drawBitmap(12, 55, bitmap_icons[item_selected], 25, 25,
                                   GREEN);
    M5Cardputer.Display.drawString(menu_itens[item_selected], 50, 58);
    M5Cardputer.Display.drawBitmap(5, 46, item_sel_outline, 223, 45, GREEN);

    // next item
    M5Cardputer.Display.drawBitmap(12, 101, bitmap_icons[item_sel_next], 25, 25,
                                   GREEN);
    M5Cardputer.Display.drawString(menu_itens[item_sel_next], 50, 101);

    // scrollbar
    M5Cardputer.Display.drawBitmap(224, 3, scrollbar_background, 8, 129, GREEN);

    // draw scrollbar handle
    M5Cardputer.Display.fillRect(226, 129 / NUM_ITEMS * item_selected, 8,
                                 129 / NUM_ITEMS, GREEN);

    while(current_screen == 1) {
        M5Cardputer.Display.clearDisplay();

        WiFi.begin(ssid, password);
        M5Cardputer.Display.print("Conectando ao WiFi");
        while (WiFi.status() != WL_CONNECTED) {
            M5Cardputer.Display.print(".");
            delay(1000);
        }
        current_screen = 0;
        M5Cardputer.Display.clearDisplay();
        break;
    }
}
