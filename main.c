#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1080

struct particle
{
    int x;
    int y;
    float vx;
    float vy;
    float ax;
    float ay;
    int radius; 
};

void update_particle(struct particle *p) {
    p->x += p->vx;
    p->y += p->vy;
    p->vx += p->ax;
    p->vy += p->ay;
}

void accelerate(struct particle *p, float ax, float ay) {
    p->ax = ax;
    p->ay = ay;
}

int main()
{
    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    struct particle p1;
    p1.x = WIDTH/2;
    p1.y = 100;
    p1.vx = 20;
    p1.vy = 1;
    p1.ax = 0;
    p1.ay = 1;
    p1.radius = 50;

    struct particle p2;
    p2.x = WIDTH/2;
    p2.y = 0;
    p2.vx = 10;
    p2.vy = 1;
    p2.ax = 0;
    p2.ay = 1;
    p2.radius = 50;
    
    while(1)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(100, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_draw_filled_circle(p1.x, p1.y, p1.radius, al_map_rgb(255,255,255));
            al_draw_filled_circle(p2.x, p2.y, p2.radius, al_map_rgb(255,255,255));
            al_flip_display();

            accelerate(&p1, p1.ax, p1.ay);
            update_particle(&p1);
            update_particle(&p2);

            redraw = false;
        }
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}