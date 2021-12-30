#include <Adafruit_NeoPixel.h>

#define RING0_PIN 9
#define RING1_PIN 10
#define RING2_PIN 11
#define LED_COUNT 16
#define LED_BRIGHTNESS 20
#define CHANGE_INTERVAL_MS 5000

Adafruit_NeoPixel ring0( LED_COUNT, RING0_PIN, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel ring1( LED_COUNT, RING1_PIN, NEO_GRB + NEO_KHZ800 );
Adafruit_NeoPixel ring2( LED_COUNT, RING2_PIN, NEO_GRB + NEO_KHZ800 );

Adafruit_NeoPixel* rings[] = { &ring0, &ring1, &ring2 };
uint32_t colors[] = { ring0.Color( 255, 0, 0 ), ring2.Color( 0, 255, 0 ), ring1.Color( 255, 191, 0 ) };

enum colors {
    COLOR_RED = 0,
    COLOR_AMBER = 1,
    COLOR_GREEN = 2
};

int current_color = COLOR_RED;

void setup() {
    for( int i = 0; i < 3; i++ ) {
        //Required to set up NeoPixels
        rings[i]->begin();

        //Turn off NeoPixels
        rings[i]->show();

        //Set brightness
        rings[i]->setBrightness( LED_BRIGHTNESS );

        setColor( rings[i], colors[i] );
    }

    delay( CHANGE_INTERVAL_MS );
}

void loop() {
    for( int i = 0; i < 3; i++ ) {
        if ( i == current_color ) {
            setColor( rings[i], colors[i] );
        }
        else {
            setOff( rings[i] );
        }
    }

    if ( current_color == COLOR_GREEN ) {
        current_color = COLOR_RED;
    }
    else {
        current_color++;
    }

    delay( CHANGE_INTERVAL_MS );
}

void setColor( Adafruit_NeoPixel* ring, uint32_t color ) {
    for( int i = 0; i < ring->numPixels(); i++ ) {
        ring->setPixelColor( i, color );
    }
    ring->show();
}

void setOff( Adafruit_NeoPixel* ring ) {
    ring->clear();
    ring->show();
}