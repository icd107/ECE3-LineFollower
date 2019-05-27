const int ELB = 12;

int ELBticks = 0;

int ELB_start_time = 0;
bool ELB_last_state = 0;
bool ELB_current_state = 0;


void setup2 ()
{
  pinMode(ELB, INPUT);
  
  ELBticks = maxticks;
}

void loop2()
{
  ELB_start_time = millis();
  ELB_last_state = 0;
  ELB_current_state = 0;
  
  while (ELBticks < maxticks)
  {
    ELB_current_state = digitalRead(ELB);
    
    if (ELB_current_state && !ELB_last_state) //rising edge
    {
      ELBticks++;
    }
    
    ELB_last_state = ELB_current_state;
  }
  
  diffL = millis() - ELB_start_time;
  ELBticks = 0;
}
