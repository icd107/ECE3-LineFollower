#define ERB P5_0

int ERBticks;

int ERB_start_time = 0;
bool ERB_last_state = 0;
bool ERB_current_state = 0;


void setup3()
{
  pinMode(ERB, INPUT);
  
  ERBticks = maxTicks;
}

void loop3()
{
  ERB_start_time = millis();
  ERB_last_state = 0;
  ERB_current_state = 0;
  
  while (ERBticks < maxTicks)
  {
    ERB_current_state = digitalRead(ERB);
    
    if (ERB_current_state && !ERB_last_state) //rising edge
    {
      ERBticks++;
    }
    
    ERB_last_state = ERB_current_state;
  }
  
  diffR = millis() - ERB_start_time;
  ERBticks = 0;
}
