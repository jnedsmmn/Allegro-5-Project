#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <sstream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define Screenwidth 800
#define ScreenHeigt 608

bool colision(float x, float y, float ex, float ey, int width, int height){
if(x+width<ex|| x>ex+width || y+height<ey || y>ey+height){
    return false;
}
return true;
}

bool colision2 (float x, float y, float ex, float ey, int width, int height){
if(x+width<ex|| x>ex+width || y+height<!ey || y>!ey+height){
    return false;
}
return true;
}
int main()
{
    ALLEGRO_DISPLAY *display;

    enum DIRECCIONES  { ARRIBA=0, ABAJO=3, IZQUIERDA=6, DERECHA=9 };
    const float FPS= 30.0;
    const int interval=3;
    al_init();
    display = al_create_display(Screenwidth,ScreenHeigt);
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_acodec_addon();
    al_install_mouse();
    al_set_window_title(display," Jumper ");

    ALLEGRO_SAMPLE *soundEffect = al_load_sample("SMB.wav");
    ALLEGRO_SAMPLE *loobs = al_load_sample("Ah_ah_ah.wav");
    al_reserve_samples(2);

    bool done =false, draw=true, active=false;
    float x=128, y=564 ,velocidad= 5;
    int dir= ABAJO, prevdir=ABAJO, index=0;
    float velx, vely;
    velx, vely = 0;
    bool jump = false;
    float Jumpspeed = 15;
    const float gravedad = 1;
    ALLEGRO_BITMAP *personajecam[12];
    for(int i=0;i<12;i++){
            std::stringstream str;
            str<<"des/"<<i+1<<".png";
        personajecam[i]=al_load_bitmap(str.str().c_str());
    }
ALLEGRO_EVENT_QUEUE *event_queue= al_create_event_queue();
ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
ALLEGRO_BITMAP *roca= al_load_bitmap("roca.bmp");
ALLEGRO_KEYBOARD_STATE keystate;
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);
    al_hide_mouse_cursor(display);
   while(!done){
ALLEGRO_EVENT events;
al_wait_for_event(event_queue, &events);
al_get_keyboard_state(&keystate);ALLEGRO_FONT *font = al_load_font("valuoldcaps.ttf", 50, NULL);
al_draw_text(font, al_map_rgb(150, 150, 255), Screenwidth / 2, ScreenHeigt / 7, ALLEGRO_ALIGN_CENTRE, " Jumper ");

if(events.type== ALLEGRO_EVENT_DISPLAY_CLOSE){
    done=true;
}
else if(events.type==ALLEGRO_EVENT_TIMER)
   {
       active=true;
       prevdir=dir;
       if(al_key_down(&keystate,ALLEGRO_KEY_RIGHT)){
    velx = velocidad;
     dir=DERECHA;
     al_play_sample(soundEffect, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
   else if(al_key_down(&keystate,ALLEGRO_KEY_LEFT)){
     velx= -velocidad;
     dir=IZQUIERDA;
      al_play_sample(soundEffect, 1.0, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, 0);
   }
   else
   {
       velx = 0;
      active=false;
   }
    if(al_key_down(&keystate,ALLEGRO_KEY_UP)&& jump){
     vely = -Jumpspeed;
     jump = false;
     al_play_sample(loobs, 1.0, 0.0, 5.0, ALLEGRO_PLAYMODE_ONCE, 0);
   }

    if(active){
        index++;
    }
    else{
        index=dir+1;
    }
    if(index>=dir+3){
        index=dir;
    }
    if(dir!=prevdir){
        index=dir;
    }


   if(!jump)
   vely += gravedad;
   else
    vely = 0;
   x += velx;
   y += vely;


   jump = (y + 40 >= 566);

   if(jump)
        y = 566 - 40;
   }

    if(draw){

al_draw_bitmap(personajecam[index],x,y,NULL);
  for(int i=0;i<=575;i+=32){
    al_draw_bitmap(roca,0,i,NULL);
       for (int i = 0; i <= 600; i+=32){
   draw=true;
if(colision(x,y,-10,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }

   }

    }
for(int i=0;i<=575;i+=32){
    al_draw_bitmap(roca,768,i,NULL);
    for (int i = 0; i <= 600; i+=32){
   draw=true;
if(colision(x,y,758,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }

   }

    }
    for(int i=0;i<=800;i+=32){
    al_draw_bitmap(roca,i,0,NULL);
         for (int i = 0; i <= 800; i+=32){
   draw=true;
if(colision(x,y, i ,-20,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
    if(!jump)
   vely -= gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (x + 40 >= 176);
      if(jump)
        y = 176 - 30;
       }

   }

    }
    for(int i=0;i<=800;i+=32){
    al_draw_bitmap(roca,i,576,NULL);
    }

    //escaleras
    for (int i = 608; i >= 491; i-=32){
    al_draw_bitmap(roca,192,i,NULL);
    draw = true;
    for (int i = 608; i >= 491; i-=32){
    if(colision(x,y,191,i,32,32)){
           if(dir == 0){
            y += velocidad;
            }
        else if(dir == 3){
            y-=velocidad;
            }
        else if(dir == 6){
            x+=velocidad;
            }
        else if(dir == 9){
            x-=velocidad;
            }
        }
        }
        }
    for (int i = 608; i >= 432; i-=32){
    al_draw_bitmap(roca,288,i,NULL);
    draw = true;
    for (int i = 608; i >= 432; i-=32){
    if(colision(x,y,288,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }
       }
    }
    for (int i = 608; i >= 368; i-=32){
    al_draw_bitmap(roca,384,i,NULL);
    draw = true;
    for (int i = 608; i >= 368; i-=32){
    if(colision(x,y, 384,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }
       }
    }
for (int i = 608; i >= 304; i-=32){
    al_draw_bitmap(roca,480,i,NULL);
    draw = true;
    for (int i = 608; i >= 304; i-=32){
    if(colision(x,y, 480,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }
       }
    }
    for (int i = 608; i >= 240; i-=32){
    al_draw_bitmap(roca,576,i,NULL);
    draw = true;
    for (int i = 608; i >= 240; i-=32){
    if(colision(x,y,576,i,32,32)){
        if(dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }
       }
    }
        for (int i = 608; i >= 176; i-=32){
    al_draw_bitmap(roca,672,i,NULL);
    draw = true;
    for (int i = 608; i >= 176; i-=32){
    if(colision(x,y,672,i,32,32)){
        if (dir ==0){
            y += velocidad;
    }
        else if(dir==3){
            y-=velocidad;
    }
        else if(dir ==6){
            x+=velocidad;
    }
        else if(dir==9){
            x-=velocidad;
    }
       }
       }
        }
// Cambio de gravedad
if(colision(x,y,191,491,32,32)){
           if(dir = 0){
            y += velocidad;
            }
        else if(dir = 3){
            y-=velocidad;
            }
        else if(dir = 6){
            x+=velocidad;
            }
        else if(dir = 9){
            x-=velocidad;
            }
     if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 497);
      if(jump)
        y = 494 - 30;
        }

if(colision(x,y,288,432,32,32)){
        if(dir =0){
            y += velocidad;
    }
        else if(dir=3){
            y-=velocidad;
    }
        else if(dir =6){
            x+=velocidad;
    }
        else if(dir=9){
            x-=velocidad;
    }
         if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 432);
      if(jump)
        y = 432 - 30;
        }
            if(colision(x,y, 384,368,32,32)){
        if(dir =0){
            y += velocidad;
    }
        else if(dir=3){
            y-=velocidad;
    }
        else if(dir =6){
            x+=velocidad;
    }
        else if(dir=9){
            x-=velocidad;
    }
     if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 368);
      if(jump)
        y = 368 - 30;
       }
           if(colision(x,y, 480,304,32,32)){
        if(dir =0){
            y += velocidad;
    }
        else if(dir=3){
            y-=velocidad;
    }
        else if(dir =6){
            x+=velocidad;
    }
        else if(dir=9){
            x-=velocidad;
    }
     if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 304);
      if(jump)
        y = 304 - 30;
       }
           if(colision(x,y, 576,240,32,32)){
        if(dir =0){
            y += velocidad;
    }
        else if(dir=3){
            y-=velocidad;
    }
        else if(dir =6){
            x+=velocidad;
    }
        else if(dir=9){
            x-=velocidad;
    }
     if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 240);
      if(jump)
        y = 240 - 30;
       }
                  if(colision(x,y, 672,176,32,32)){
        if(dir =0){
            y += velocidad;
    }
        else if(dir=3){
            y-=velocidad;
    }
        else if(dir =6){
            x+=velocidad;
    }
        else if(dir=9){
            x-=velocidad;
    }
     if(!jump)
   vely += gravedad;
   else
      vely = 0;
      x += velx;
      y += vely;
      jump = (y + 40 >= 176);
      if(jump)
        y = 176 - 30;
       }

al_flip_display();
al_clear_to_color(al_map_rgb(0,0,0));
al_destroy_font(font);
   }
   }

al_destroy_display(display);
al_destroy_event_queue(event_queue);
al_destroy_timer(timer);
for(int i=0;i<12;i++){
    al_destroy_bitmap(personajecam[i]);
    }
al_destroy_sample(soundEffect);
    return 0;
}
