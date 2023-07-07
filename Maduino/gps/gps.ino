#define DEBUG false

const int PWR_KEY = 9;
const int RST_KEY = 6;
const int LOW_PWR_KEY = 5;


float GPS_coordinates[2] = {0.0, 0.0};
float last_GPS_coordinates[2] = {0.0, 0.0};
long measure_time = 0;
long last_measure_time = 0;

const float pi = 3.141593;
const long earth_radius = 6378160;


void setup() {
  // put your setup code here, to run once:
  pinMode(PWR_KEY, OUTPUT);
  pinMode(RST_KEY, OUTPUT);
  pinMode(LOW_PWR_KEY, OUTPUT);
  digitalWrite(PWR_KEY, LOW);
  digitalWrite(LOW_PWR_KEY, HIGH);
  digitalWrite(PWR_KEY, HIGH);

  // Configure USB Serial communication
  SerialUSB.begin(115200);
  while(!SerialUSB) {} // wait for serial port to connect

  // Configure and setup A9G
  configure_A9G();
  
  Serial1.println("AT+GPS=1"); // turn on GPS
  Serial1.println("AT+GPSRD=0");
  SerialUSB.println("\nSetup done.\n");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  last_GPS_coordinates[0] = GPS_coordinates[0];
  last_GPS_coordinates[1] = GPS_coordinates[1];
  last_measure_time = measure_time;
  measure_time = millis();
  get_GPS_coordinates();
  float distance = calc_distance(last_GPS_coordinates, GPS_coordinates);
  float speed_km = calc_speed(distance, last_measure_time, measure_time);
  SerialUSB.print("Longitude: ");
  SerialUSB.print(GPS_coordinates[0], 6);
  SerialUSB.print("\tLatitude: ");
  SerialUSB.print(GPS_coordinates[1], 6);
  //SerialUSB.print("\t");
  //SerialUSB.print(distance);
  SerialUSB.print("\tSnelheid: ");
  SerialUSB.print(speed_km);
  SerialUSB.print(" km/u\n");
  //delay(2000);
}

void configure_A9G() {
  Serial1.begin(115200);
  digitalWrite(PWR_KEY, LOW);
  delay(3000);
  digitalWrite(PWR_KEY, HIGH);
  delay(5000);
  bool module_on = false;
  for (int i = 0; i < 10; i++) {
    String msg = send_message("AT", DEBUG);
    if (msg.indexOf("OK") >= 0) {
      module_on = true;
      SerialUSB.println("module was already turned on");
      SerialUSB.println(msg);
      break;
    }
  }
  if (!module_on) {
    digitalWrite(PWR_KEY, LOW);
    delay(3000);
    digitalWrite(PWR_KEY, HIGH);
    delay(5000);
    SerialUSB.println("module was not turned on");
  }
}

String send_message(String command, boolean debug) {
  Serial1.println(command);
  while (Serial1.available() == 0) {};
  return Serial1.readString();
}
void get_GPS_coordinates() {
  String answer = send_message("AT+LOCATION=2", DEBUG);
  GPS_coordinates[0] = answer.substring(answer.indexOf("AT+LOCATION=2")+15, answer.indexOf(",")).toFloat();
  GPS_coordinates[1] = answer.substring(answer.indexOf(",")+1, answer.indexOf("OK")-1).toFloat(); 
}

float calc_distance(float GPS_point1[], float GPS_point2[]) {
  // formulas from https://www.movable-type.co.uk/scripts/latlong.html
  float phi_1 = GPS_point1[1] * pi / 180;
  float phi_2 = GPS_point2[1] * pi / 180;
  float delta_phi = (GPS_point2[1] - GPS_point1[1]) * pi / 180;
  float delta_lambda = (GPS_point2[0] - GPS_point1[0]) * pi / 180;

  double a = pow(sin(delta_phi / 2), 2) + cos(phi_1) * cos(phi_2) * pow(sin(delta_lambda / 2), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));

  return earth_radius * c;
}

float calc_speed(float distance, long t1, long t2) {
  distance /= 1000;
  long delta_time = abs(t2 - t1);
  return distance * 1000 * 60 * 60 / delta_time;
}
