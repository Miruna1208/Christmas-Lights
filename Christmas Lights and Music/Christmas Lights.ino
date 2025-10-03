#include <DIYables_IRcontroller.h>
#define IR_RECEIVER_PIN 7

// Constants and pins
const byte releuPin = 6;
const int buzzerPin = 4;

// Initialize the remote controller object
DIYables_IRcontroller_17 irController(IR_RECEIVER_PIN, 200);

// Note frequencies (in microseconds for tone durations)
const int NOTE_B4 = 1014;
const int NOTE_C5 = 956;
const int NOTE_D5 = 852;
const int NOTE_E5 = 758;
const int NOTE_F5 = 716;
const int NOTE_G5 = 637;
const int NOTE_A5 = 568;
const int NOTE_B5 = 532;
const int NOTE_C6 = 506;
const int NOTE_D6 = 451;

// "Jingle Bells" melody and durations (KEY_1)
const int melody1[] = {
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5
};
const int noteDurations1[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

// "Deck the Halls" melody and durations (KEY_2)
const int melody2[] = {
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
    NOTE_F5, NOTE_A5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5
};
const int noteDurations2[] = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

// "We Wish You a Merry Christmas" melody and durations (KEY_3)
const int melody3[] = {
    NOTE_E5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_A5, NOTE_A5,
    NOTE_A5, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_C6, NOTE_C6, NOTE_B5
};
const int noteDurations3[] = {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
};

void setup() {
    Serial.begin(9600);       // Start serial communication for debugging
    irController.begin();     // Initialize the IR controller
    pinMode(releuPin, OUTPUT); // Set relay pin as output
    pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
    digitalWrite(releuPin, LOW); // Ensure relay starts in LOW state
}

void loop() {
    // Check for key press from the remote
    Key17 key = irController.getKey();

    if (key != Key17::NONE) {
        Serial.println(int(key));  // Print the pressed key for debugging
        if (key == Key17::KEY_1) {
            playJingleBellsWithRelay();  // Continuously toggle relay while playing Jingle Bells
        } else if (key == Key17::KEY_2) {
            digitalWrite(releuPin, HIGH); // Turn relay ON
            playDeckTheHalls();          // Play "Deck the Halls"
        } else if (key == Key17::KEY_3) {
            digitalWrite(releuPin, LOW); // Turn relay OFF
            playWeWishYou();             // Play "We Wish You a Merry Christmas"
        }
    }
}

// Function to play a single tone
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(buzzerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(buzzerPin, LOW);
        delayMicroseconds(tone);
    }
}

// Function to play "Jingle Bells" melody with relay toggling
void playJingleBellsWithRelay() {
    int melodyLength = sizeof(melody1) / sizeof(melody1[0]);
    for (int i = 0; i < melodyLength; i++) {
        // Toggle relay state
        digitalWrite(releuPin, HIGH);
        delay(50); // Brief delay for relay ON
        digitalWrite(releuPin, LOW);
        delay(50); // Brief delay for relay OFF

        // Play the current note
        int noteDuration = 1000 / noteDurations1[i];
        playTone(melody1[i], noteDuration);

        // Pause between notes
        int pauseBetweenNotes = noteDuration * 1.3;
        delay(pauseBetweenNotes);
    }
}

// Function to play "Deck the Halls" melody
void playDeckTheHalls() {
    int melodyLength = sizeof(melody2) / sizeof(melody2[0]);
    for (int i = 0; i < melodyLength; i++) {
        int noteDuration = 1000 / noteDurations2[i];
        playTone(melody2[i], noteDuration);

        // Pause between notes
        int pauseBetweenNotes = noteDuration * 1.3;
        delay(pauseBetweenNotes);
    }
}

// Function to play "We Wish You a Merry Christmas" melody
void playWeWishYou() {
    int melodyLength = sizeof(melody3) / sizeof(melody3[0]);
    for (int i = 0; i < melodyLength; i++) {
        int noteDuration = 1000 / noteDurations3[i];
        playTone(melody3[i], noteDuration);

        // Pause between notes
        int pauseBetweenNotes = noteDuration * 1.3;
        delay(pauseBetweenNotes);
    }
}
