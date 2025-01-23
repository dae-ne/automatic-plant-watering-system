#define SENSOR_ANALOG_INPUT A0
#define SENSOR_POWER_PIN 3
#define ENGINE_OUTPUT 2

#define DELAY_MIN 60
#define ENGINE_WORK_TIME_MS 1000
#define MAX_SENSOR_VALUE 1023
#define MOISTURE_PERCENTAGE_THRESHOLD 50
#define MIN_MOISTURE_PERCENTAGE 30

void setup()
{
    pinMode(SENSOR_POWER_PIN, OUTPUT);
    pinMode(ENGINE_OUTPUT, OUTPUT);

    digitalWrite(SENSOR_POWER_PIN, LOW);
    digitalWrite(ENGINE_OUTPUT, LOW);

    Serial.begin(9600);
}

void loop()
{
    int sensorValue = readSensor();

    Serial.print("Moisture level: ");
    Serial.print(sensorValue);
    Serial.println("%");

    if (sensorValue < MOISTURE_PERCENTAGE_THRESHOLD &&
        sensorValue >= MIN_MOISTURE_PERCENTAGE)
    {
        digitalWrite(ENGINE_OUTPUT, HIGH);
        delay(ENGINE_WORK_TIME_MS);
        digitalWrite(ENGINE_OUTPUT, LOW);
    }

    delay(DELAY_MIN * 60000);
}

int readSensor()
{
    digitalWrite(SENSOR_POWER_PIN, HIGH);
	delay(10);

    int sensorValue = analogRead(SENSOR_ANALOG_INPUT);
    int percentage = calculatePercentage(sensorValue, MAX_SENSOR_VALUE);

    digitalWrite(SENSOR_POWER_PIN, LOW);

    return percentage;
}

int calculatePercentage(int value, int maxValue)
{
    return 100.f - (float)value / maxValue * 100.f;
}
