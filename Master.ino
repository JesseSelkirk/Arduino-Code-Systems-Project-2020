//librarys
#include <Adafruit_PMTK.h>
#include <NMEA_data.h>

//GPS--------------------------------------------------------------------
    // Pin Latout  ________________________
        /* 
        * Vin = 5V
        * GND = GND 
        * RX = D3
        * TX = D4
        */
    
    #include <Adafruit_GPS.h>
    SoftwareSerial mySerial(3, 4);
    Adafruit_GPS GPS(&mySerial);

//Gryo-------------------------------------------------------------------
    
    // Pin Latout  ________________________
        /* 
        * VCC = 5V
        * GND = GND 
        * SCL = SCL
        * SDA = SDA
        * XDA = A4
        * XCL = A5
        * INT = D2  
        * servo = D9
        * LED = D13 
        */

    #include <MPU6050_tockn.h>
    #include <Wire.h>

//Servo------------------------------------------------------------------
    // Pin Latout  ________________________
        /* 
        * Red = 5V
        * Brown = GND 
        * Orangex  = D9
        * Orangey = D10
        */

    #include <Servo.h>
    Servo servo;
    Servo servo_x;

// Defining var  --------------------------------------------------------
MPU6050 mpu6050(Wire);
int last = 90;
long timer = 0;


void setup()
{
    // Serial rate ____________________
    Serial.begin(115200);

    // MPU6050 ________________________
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    mpu6050.update();

    // LED To Pin _____________________
    pinMode(13, OUTPUT);

    // Sevo To Pin ____________________
    servo.attach(9);
    servo_x.attach(10);
}


void loop()
{   
    int x = 0;
    while (x != 10){

        // LED On _________________________
        digitalWrite(LED_BUILTIN, HIGH);

        //Gryo---------------------------------------------------------------
            // Makeing Data ___________________
                mpu6050.update();
                Serial.print("\tangleY : ");
                Serial.print(mpu6050.getAngleY());


        //GPS----------------------------------------------------------------
        GPS.parse(GPS.lastNMEA());
        GPS.newNMEAreceived();
        ((int)GPS.fix);
        ((int)GPS.fixquality);
        //If GPS module has a fix, line by line prints the GPS information
        if (GPS.fix){
                Serial.print("Location: ");
                Serial.print(GPS.latitude, 4);
                Serial.print(GPS.lat);
                Serial.print(", ");
                Serial.print(GPS.longitude, 4);
                Serial.println(GPS.lon);
                Serial.print("Location (in degrees, works with Google Maps): ");
                Serial.print(GPS.latitudeDegrees, 4);
                Serial.print(", ");
                Serial.println(GPS.longitudeDegrees, 4);
                Serial.print("Speed (knots): ");
                Serial.println(GPS.speed);
                Serial.print("Angle: ");
                Serial.println(GPS.angle);
        }

        //Servo--------------------------------------------------------------
            // Variables ______________________
                int xt = ((2*mpu6050.getAngleY())+ 90);
                int xty = ((2*mpu6050.getAngleY())+ 90);
                Serial.println(xt);

            // Servo tern axes ________________
                if (mpu6050.getAngleY()<1){
                    
                    servo.write(xt);

                }
                if (mpu6050.getAngleY()> -1){
                    
                    servo.write(xty);
        //Variables
        x + 1;
        Serial.println(x);
        } 
    }
    
    int tristan = random(0, 90);
    servo_x.write(tristan);
    x = 0;
}
