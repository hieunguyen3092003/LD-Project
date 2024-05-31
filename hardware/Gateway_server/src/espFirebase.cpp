#include "global.h"
#include "espFirebase.h"

#ifdef ESPFIREBASE

#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

void initEspFirebase(void);
void espFirebaseSync(void);
// bool espFirebaseButtonDown(void);


#define WIFI_SSID "BKIT_LUGIA_CS2"
#define WIFI_PASSWORD "cselabc5c6"
#define API_KEY "AIzaSyAzR7TWnD9Qed-r_65ofVwokfsYCZyltMk"
#define DATABASE_URL "https://ld-project-8f0cd-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool is_signup = false;

void initEspFirebase()
{
    WiFi.mode(WIFI_AP_STA);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
        is_signup = true;
    }
    else
    {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("finished init firebase");

    // stream
    // if (!Firebase.RTDB.beginStream(&fbdo_s, "/Button"))
    // {
    //     Serial.printf("stream begin error, %s\n\n", fbdo_s.errorReason().c_str());
    // }
}

void espFirebaseSync()
{
    if (Firebase.ready() && is_signup)
    {
        if (Firebase.RTDB.setInt(&fbdo, "/Sensor/moisture_pct", packet_receive.moisture_pct))
        {
            Serial.println();
            Serial.print(packet_receive.moisture_pct);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setFloat(&fbdo, "/Sensor/temp", packet_receive.temp))
        {
            Serial.println();
            Serial.print(packet_receive.temp);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setFloat(&fbdo, "/Sensor/humid", packet_receive.humid))
        {
            Serial.println();
            Serial.print(packet_receive.humid);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setBool(&fbdo, "/Sensor/is_dry", packet_receive.is_dry))
        {
            Serial.println();
            Serial.print(packet_receive.is_dry);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setBool(&fbdo, "/Sensor/is_night", packet_receive.is_night))
        {
            Serial.println();
            Serial.print(packet_receive.is_night);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setBool(&fbdo, "/Pump/is_pump_on", packet_receive.is_pump_on))
        {
            Serial.println();
            Serial.print(packet_receive.is_pump_on);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "/Pump/pump_mode", packet_send.pump_mode))
        {
            Serial.println();
            Serial.print(packet_send.pump_mode);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "/Pump/pump_limit", packet_send.pump_limit))
        {
            Serial.println();
            Serial.print(packet_send.pump_limit);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }

        if (Firebase.RTDB.setInt(&fbdo, "/Pump/pump_interval", packet_send.pump_interval))
        {
            Serial.println();
            Serial.print(packet_send.pump_interval);
            Serial.print(" - Successful saved to: ");
            Serial.print(fbdo.dataPath());
            Serial.print(" (");
            Serial.print(fbdo.dataType());
            Serial.println(")");
        }
        else
        {
            Serial.print("Failed: ");
            Serial.println(fbdo.errorReason());
        }
    }
}

// bool espFirebaseButtonDown()
// {
// if (Firebase.ready() && is_signup)
// {
//     if (!Firebase.RTDB.readStream(&fbdo_s))
//     {
//         Serial.printf("Stream read error, %s\n\n", fbdo_s.errorReason().c_str());
//     }
//     if (fbdo_s.streamAvailable())
//     {
//         if (fbdo_s.dataType() == "boolean")
//         {
//             Serial.println("Successful read");
//             return fbdo_s.boolData();
//         }
//     }
// }
// return false;
// }

#endif /* ESPFIREBASE */