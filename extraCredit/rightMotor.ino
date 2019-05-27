#define ERA P10_5

int ERAticks = 0;

int ERA_start_time = 0;
bool ERA_last_state = 0;
bool ERA_current_state = 0;


void setup3()
{
  pinMode(ERA, INPUT);
  
  ERAticks = maxticks;
}

void loop3()
{
  ERA_start_time = millis();
  ERA_last_state = 0;
  ERA_current_state = 0;
  
  while (ERAticks < maxticks)
  {
    ERA_current_state = digitalRead(ERA);
    
    if (ERA_current_state && !ERA_last_state) //rising edge
    {
      ELAticks++;
    }
    
    ERA_last_state = ERA_current_state;
  }
  
  diffR = millis() - ERA_start_time;
  ERAticks = 0;
}
