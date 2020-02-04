//PID constants
double kp = 2;
double ki = 5;
double kd = 1;
const int lm35_pin = A1;  /* LM35 O/P pin */
int In1 = 7;
int In2 = 8;
int ENA = 5;
int speed = 255; 
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;
//double setTemperature;
 
void setup(){
        pinMode(In1, OUTPUT);
        pinMode(In2, OUTPUT);
        pinMode(ENA, OUTPUT);
        digitalWrite(In1 , LOW);
        digitalWrite(In2 , HIGH);
        analogWrite(ENA, speed);
        Serial.begin(9600);
        setPoint = 24;
        //setPoint = setTemperature*10/4.88;                          //set point at zero degrees
}    
 
void loop(){
        int temp_adc_val;
        float temp_val;
        temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
        temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
        temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
        Serial.print("Temperature = ");
        Serial.print(temp_val);
        Serial.print(" Degree Celsius\n");
        input = temp_val;                //read from rotary encoder connected to A1
        output = computePID(input);
        delay(100);
        if(output < 0){
          digitalWrite(In1 , HIGH);
          digitalWrite(In2 , LOW);
          output = output * -1;
        }
        if(output > 255){
            output = 255;  
        }
        speed = output;
        //analogWrite(3, output);       //control the motor based on PID value
        analogWrite(ENA,speed);
}
 
double computePID(double inp){     
        currentTime = millis();                //get current time
        elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
        error = setPoint - inp;                                // determine error
        cumError += error * elapsedTime;                // compute integral
        rateError = (error - lastError)/elapsedTime;   // compute derivative
 
        double out = kp*error + ki*cumError + kd*rateError;                //PID output               
 
        lastError = error;                                //remember current error
        previousTime = currentTime;                        //remember current time
 
        return out;                                        //have function return the PID output
}
