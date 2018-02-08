int ForeAft_Pin = 0;       // Fore / Aft input is Arduino pin A0
int LeftRight_Pin = 1;     // Left / Right input is Arduino pin A1

int ForeAft_Input;         // Expected Range 220-800 for a hall-effect joystick
int LeftRight_Input;       // Expected Range 220-800 for a hall-effect joystick

void setup()               // Main Program Initialization
  {
    Serial.begin(9600);    // Prepare debug 
  }

void loop()
  {
    ForeAft_Input = analogRead(ForeAft_Pin) ;          // Read Fore/Aft Value
    LeftRight_Input = analogRead(LeftRight_Pin) ;      // Read Left/Right Value
  
    Serial.print(LeftRight_Input);                     // Send Left/Right to terminal
    Serial.print("\t");
    Serial.println(ForeAft_Input);                     // Send Fore/Aft to terminal

    delay( 1000 );                                     // Wait 1 second before looping
  }
