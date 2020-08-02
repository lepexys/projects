#include <stdio.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_draw.h"
#include <time.h>
#define file_name "save.txt"
using namespace std;

struct Elemento
{
    Elemento* prev;
    Elemento* next;
    SDL_Rect cord;
    bool is_bonus;
    Elemento()
    {
        prev = NULL;
        next = NULL;
        is_bonus=false;
    }
    Elemento(SDL_Rect c,Elemento* p,Elemento* n,bool ib)
    {
        prev=p;
        next=n;
        cord=c;
        is_bonus=ib;
    }
};
struct Chain
{
    Elemento* start;
    Elemento* fin;
    int ball_counter, ball_timer;
    Chain(SDL_Rect rect)
    {
        ball_timer=0;
        ball_counter=1;
        Elemento* temp = new(Elemento);
        temp->prev=NULL;
        temp->next=NULL;
        temp->cord=rect;
        temp->is_bonus=false;
        start = temp;
        fin= temp;
    }
    void New_Balls(SDL_Surface *screen)
    {
        if (ball_timer<100)
            {
                ball_timer++;
                if(ball_timer%(100/(ball_counter+1))==0)
                {
                    SDL_Rect *ball_loc = new(SDL_Rect);
                    ball_loc->w=72;
                    ball_loc->h=70;
                    ball_loc->y = 0;
                    ball_loc->x=rand()%(screen->w-72);
                    Add(*ball_loc,false);
                }
            }
            else
            {
                ball_timer = 0;
                ball_counter++;
                if(ball_counter%2==0)
                {
                    SDL_Rect *bon_loc=new (SDL_Rect);
                    bon_loc->w=72;
                    bon_loc->h=81;
                    bon_loc->y=0;
                    bon_loc->x=rand()%(screen->w-72);
                    Add(*bon_loc,true);
                }
            }
    }
    void Add(SDL_Rect rect,bool ib)
    {
        Elemento* temp = new(Elemento);
        if(start)
            {
                temp->cord=rect;
                temp->prev=fin;
                temp->next=NULL;
                temp->is_bonus=ib;
                fin->next=temp;
                fin=temp;
            }
        else
            {
                temp->cord=rect;
                temp->prev=NULL;
                temp->next=NULL;
                temp->is_bonus=ib;
                fin = temp;
                start = temp;
            }
    }
    Elemento* Delete(Elemento* elem)
    {
        Elemento* temp=elem->next;
        if(elem->prev!=NULL)
        elem->prev->next=elem->next;
        else
            start=elem->next;
        if(elem->next!=NULL)
        elem->next->prev=elem->prev;
        else
            fin=elem->prev;
        return temp;
    }
};
struct Man
{
    int hp;
    bool run;
    SDL_Rect hitbox,bigbox;
    Man(SDL_Rect h,SDL_Rect b)
    {
        hitbox=h;
        bigbox=b;
        hp = 400;
        run = false;
    }

    void Move(int a)
    {
        hitbox.x+=a;
        bigbox.x+=a;
    }
    bool Draw_HP(SDL_Surface* screen)
    {
        if(hp<=0)
            return true;
        SDL_Rect bar,filld;
        bar.x=screen->w/2-200;
        bar.y=screen->h-80;
        bar.h=40;
        bar.w=400;
        filld.x=screen->w/2-200;
        filld.y=screen->h-80;
        filld.h=40;
        filld.w=hp;
        Uint32 color = SDL_MapRGB(screen->format,20,0,0);
        SDL_FillRect(screen,&bar,color);
        color = SDL_MapRGB(screen->format,255,0,0);
        SDL_FillRect(screen,&filld,color);
        return false;
    }
};
struct Game
{
    SDL_Surface *screen;
    TTF_Font *fnt;
    short Start_Game()
    {
        SDL_Surface* stage1l,*stage2l,*stage3l,*stage4l,*stage1r,*stage2r,*stage3r,*stage4r,*sb,*bon,*bg;
        bg=SDL_LoadBMP("back.bmp");
        bon=SDL_LoadBMP("bonus.bmp");
        bon->format->Amask = 0xFF000000;
        bon->format->Ashift = 24;
        SDL_SetAlpha(bon,SDL_SRCALPHA,0);
        sb=SDL_LoadBMP("snow_ball.bmp");
        sb->format->Amask = 0xFF000000;
        sb->format->Ashift = 24;
        SDL_SetAlpha(sb,SDL_SRCALPHA,0);
        stage1l = SDL_LoadBMP("man_prof_walk_l_forw_l.bmp");
        stage1l->format->Amask = 0xFF000000;
        stage1l->format->Ashift = 24;
        SDL_SetAlpha(stage1l,SDL_SRCALPHA,0);
        stage2l = SDL_LoadBMP("man_prof_stand_l.bmp");
        stage2l->format->Amask = 0xFF000000;
        stage2l->format->Ashift = 24;
        SDL_SetAlpha(stage2l,SDL_SRCALPHA,0);
        stage3l = SDL_LoadBMP("man_prof_walk_r_forw_l.bmp");
        stage3l->format->Amask = 0xFF000000;
        stage3l->format->Ashift = 24;
        SDL_SetAlpha(stage3l,SDL_SRCALPHA,0);
        stage4l = SDL_LoadBMP("man_prof_stand_l.bmp");
        stage4l->format->Amask = 0xFF000000;
        stage4l->format->Ashift = 24;
        SDL_SetAlpha(stage4l,SDL_SRCALPHA,0);
        stage1r = SDL_LoadBMP("man_prof_walk_l_forw_r.bmp");
        stage1r->format->Amask = 0xFF000000;
        stage1r->format->Ashift = 24;
        SDL_SetAlpha(stage1r,SDL_SRCALPHA,0);
        stage2r = SDL_LoadBMP("man_prof_stand_r.bmp");
        stage2r->format->Amask = 0xFF000000;
        stage2r->format->Ashift = 24;
        SDL_SetAlpha(stage2r,SDL_SRCALPHA,0);
        stage3r = SDL_LoadBMP("man_prof_walk_r_forw_r.bmp");
        stage3r->format->Amask = 0xFF000000;
        stage3r->format->Ashift = 24;
        SDL_SetAlpha(stage3r,SDL_SRCALPHA,0);
        stage4r = SDL_LoadBMP("man_prof_stand_r.bmp");
        stage4r->format->Amask = 0xFF000000;
        stage4r->format->Ashift = 24;
        SDL_SetAlpha(stage4r,SDL_SRCALPHA,0);
        SDL_Rect hitbox,bigbox;
        hitbox.w=40;
        hitbox.h=200;
        hitbox.x=screen->w/2-20;
        hitbox.y=screen->h-300;
        bigbox.w=100;
        bigbox.h=200;
        bigbox.x=screen->w/2-50;
        bigbox.y=screen->h-300;
        Man person(hitbox,bigbox);
        int stage;
        short fcounter = 0;
        bool right,k=false,go = false;
        SDL_Event event;
        long times;
        clock_t time_counter;
        Draw_Back();
        SDL_Rect message;
        Uint32 color = SDL_MapRGB(screen->format,220,220,255);
        message.x=(screen->w/2)-280;
        message.y=(screen->h/2)-80;
        message.h=160;
        message.w=560;
        SDL_FillRect(screen,&message,color);
        SDL_Color mes_col;
        mes_col.r = 120;
        mes_col.g = 120;
        mes_col.b = 255;
        Text("Нажмите любую клавишу",fnt,mes_col,(screen->w/2)-240,(screen->h/2)-35);
        SDL_Flip(screen);
        while(SDL_WaitEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
                break;
        }
        SDL_Rect ball_loc;
        ball_loc.w=72;
        ball_loc.h=70;
        ball_loc.y = 0;
        ball_loc.x=rand()%screen->w;
        Chain chain_of_balls = Chain(ball_loc);
        Elemento* cur_ball;
        time_counter=clock();
        while(true)
        {
        while(SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                return 0;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        return 1;
                    case SDLK_LSHIFT:
                    {
                        person.run=true;
                        break;
                    }
                    case SDLK_RSHIFT:
                    {
                        person.run=true;
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        stage = 0;
                        go = true;
                        right = true;
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        stage =0;
                        go = true;
                        right = false;
                        break;
                    }
                    }
                    break;
                }
                case SDL_KEYUP:
                {
                    if(event.key.keysym.sym==SDLK_LSHIFT||event.key.keysym.sym==SDLK_RSHIFT)
                        person.run = false;
                    if((event.key.keysym.sym==SDLK_RIGHT && right) || (event.key.keysym.sym==SDLK_LEFT && !right))
                    go=false;
                    fcounter = 0;
                    break;
                }
                }
            }
            Draw_Back(bg);
            chain_of_balls.New_Balls(screen);
            cur_ball=chain_of_balls.start;
            bool k=false;
            while(cur_ball!=NULL)
            {
                if(cur_ball->is_bonus)
                {
                    Snow_ball(bon,cur_ball->cord);
                    cur_ball->cord.y+=10;
                    if(((person.hitbox.x<(cur_ball->cord.x+72)&&(person.hitbox.x+40)>cur_ball->cord.x)&&person.hitbox.y<(cur_ball->cord.y+81))||(cur_ball->cord.y+70>screen->h-100))
                {
                    if((person.hitbox.x<(cur_ball->cord.x+72)&&(person.hitbox.x+40)>cur_ball->cord.x)&&person.hitbox.y<(cur_ball->cord.y+81))
                      {
                        if(person.hp<=300) person.hp+=100;
                        else person.hp=400;
                      }
                    cur_ball=chain_of_balls.Delete(cur_ball);
                }
                    else
                cur_ball=cur_ball->next;
                person.Draw_HP(screen);
                }
                else
                {
                Snow_ball(sb,cur_ball->cord);
                cur_ball->cord.y+=10;
                if(((person.hitbox.x<(cur_ball->cord.x+72)&&(person.hitbox.x+40)>cur_ball->cord.x)&&person.hitbox.y<(cur_ball->cord.y+70))||(cur_ball->cord.y+70>screen->h-100))
                {
                    if((person.hitbox.x<(cur_ball->cord.x+72)&&(person.hitbox.x+40)>cur_ball->cord.x)&&person.hitbox.y<(cur_ball->cord.y+70))
                    {
                        person.hp-=150;
                    }
                    cur_ball=chain_of_balls.Delete(cur_ball);
                }
                    else
                cur_ball=cur_ball->next;
                k=person.Draw_HP(screen);
                }
            }
            if(k)
            {
                times = clock() - time_counter;
                ofstream file;
                file.open(file_name, ios::out|ios::app|ios::binary);
                char text[30];
                double buff = (double)times/1000;
                sprintf(text, "Вы прожили %d.%d сек", times/1000,times%1000);
                file.write((char*)&buff,sizeof buff);
                file.close();
                Draw_Back();
                Text(text,fnt,mes_col,(screen->w/2)-240,(screen->h/2)-35);
                SDL_Flip(screen);
                SDL_Delay(800);
        while(SDL_WaitEvent(&event))
        {
            if(event.type==SDL_KEYDOWN)
                break;
        }
                return 1;
            }
            if(go)
            {
                if(right)
                {
                    if(person.run)
                        fcounter+=3;
                    else
                    fcounter+=2;
                    if(fcounter >= 12)
                    {
                    fcounter=0;
                    stage++;
                    if(stage==4)
                        stage=0;
                    }
                    if(person.run)
                    {
                    if(screen->w-person.bigbox.x-100>12)
                    {
                person.Move(12);
                    }
                else
                {
                    person.Move(screen->w-person.bigbox.x-100);
                }
                    }
                    else
                    {
                    if(screen->w-person.bigbox.x-100>7)
                    {
                person.Move(7);
                    }
                else
                {
                    person.Move(screen->w-person.bigbox.x-100);
                }
                    }
                switch (stage)
                {
                case 0:
                SDL_BlitSurface(stage1r,NULL,screen,&person.bigbox);
                break;
                case 1:
                SDL_BlitSurface(stage2r,NULL,screen,&person.hitbox);
                break;
                case 2:
                SDL_BlitSurface(stage3r,NULL,screen,&person.bigbox);
                break;
                case 3:
                SDL_BlitSurface(stage4r,NULL,screen,&person.hitbox);
                break;
                }
                }
                else
            {
                if(person.run)
                        fcounter+=3;
                    else
                fcounter+=2;
                    if(fcounter >= 12)
                    {
                    fcounter=0;
                    stage++;
                    if(stage==4)
                        stage=0;
                    }
                    if(person.run)
                    {
                        if(person.bigbox.x>12)
                    {
                person.Move(-12);
                    }
                else
                {
                    person.Move(-person.bigbox.x);
                }
                    }
                    else
                    {
                    if(person.bigbox.x>7)
                    {
                person.Move(-7);
                    }
                else
                {
                    person.Move(-person.bigbox.x);
                }
                    }
                    switch (stage)
                    {
                case 0:
                SDL_BlitSurface(stage1l,NULL,screen,&person.bigbox);
                break;
                case 1:
                SDL_BlitSurface(stage2l,NULL,screen,&person.hitbox);
                break;
                case 2:
                SDL_BlitSurface(stage3l,NULL,screen,&person.bigbox);
                break;
                case 3:
                SDL_BlitSurface(stage4l,NULL,screen,&person.hitbox);
                break;
                    }
        }
        }
            else
            {
                if(right)
                {
                    SDL_BlitSurface(stage2r,NULL,screen,&person.hitbox);
                }
                else
                {
                    SDL_BlitSurface(stage2l,NULL,screen,&person.hitbox);
                }
            }
            SDL_Delay(18);
            SDL_Flip(screen);
        }
    }
    void Snow_ball(SDL_Surface* thing,SDL_Rect place)
    {
        SDL_BlitSurface(thing,NULL,screen,&place);
    }
    void Draw_Back()
    {
        Uint32 back_color = SDL_MapRGB(screen->format,200,200,255);
        SDL_Rect pl;
        pl.x=0;pl.y=0;pl.h=1080;pl.w=1920;
        SDL_FillRect(screen,&pl,back_color);
    }
    void Draw_Back(SDL_Surface* bg)
    {
        SDL_Rect pl;
        pl.x=0;pl.y=0;pl.h=1080;pl.w=1920;
        SDL_BlitSurface(bg,NULL,screen,&pl);
    }
    void Text(char* text,TTF_Font *f,SDL_Color col,int x, int y)
{
    SDL_Surface* b;
    SDL_Rect d;
    d.x=x;
    d.y=y;
    if(b = TTF_RenderUTF8_Solid(f,
                          text, col))
  {
    SDL_BlitSurface(b, NULL, screen,
                    &d);
    SDL_FreeSurface(b);
    b = NULL;
  }
}
};
struct Menu : public Game
{
    Menu(SDL_Surface *s,TTF_Font *f)
    {
        screen = s;
        fnt = f;
    }
void High_Scores()
{
    SDL_Event event;
    TTF_Font* lb;
    if(!(lb = TTF_OpenFont("CharisSILR.ttf", 30))){
    TTF_Quit();
    SDL_Quit();
    }
    Draw_Back();
    Uint32 table_color = SDL_MapRGB(screen->format,255,255,255),color = SDL_MapRGB(screen->format,100,100,255);
    SDL_Color text_color,t_color;
    Sint16 sizex = 200;
    Sint16 sizey = 60;
     Sint16 x=screen->w/2;
     Sint16 y=screen->h/4;
     Draw_FillRect(screen,x-500,y-150,5*sizex,650,table_color);
     Draw_FillRect(screen,x-sizex,3*y-sizey+85,2*sizex,2*sizey,color);
     Draw_FillRect(screen,x-sizex+600,3*y-sizey+85,2*sizex,2*sizey,color);
     int locx=x-450,locy=y-50;
  SDL_Surface* b;
  t_color.r=0;
  t_color.g=0;
  t_color.b=0;
  text_color.r = 0;
  text_color.g = 0;
  text_color.b = 255;
  ifstream file;
  file.open(file_name, ios::in|ios::binary);
  char text[30];
  double buff,temp;
  int cntr = 1;
  Game::Text("Назад",fnt,text_color,x-50,3*y+50);
  Game::Text("Сбросить",fnt,text_color,x+520,3*y+50);
  Game::Text("Лучшие результаты",fnt,t_color,x-160,y-140);
  double mas[9]={0};
    while(!file.eof())
    {
        file.read((char*)&buff,sizeof buff);
        for(int i = 0;i<9;i++)
            if(buff>mas[i])
            {
            for(int j=i;j<9;j++)
            {
                temp=mas[j];
                mas[j]=buff;
                buff=temp;
            }
            break;
            }
    }
    while(true)
    {
        if(cntr==9||(int)mas[cntr-1]==0)
            break;
        sprintf(text,"%d. %lf",cntr,mas[cntr-1]);
        Game::Text(text,lb,t_color,locx,locy);
        locy+=60;
        cntr++;
    }
    file.close();
  SDL_Flip(screen);
  while(SDL_WaitEvent(&event))
  {
      if(event.type == SDL_QUIT ||
      (event.type == SDL_KEYDOWN &&
      event.key.keysym.sym == SDLK_ESCAPE))
      return;
      if(event.type==SDL_MOUSEBUTTONDOWN)
        if(event.button.button == SDL_BUTTON_LEFT)
        {
        if(event.button.x<=x+sizex&&event.button.x>=x-sizex&&event.button.y<=3*y+sizey+85&&event.button.y>=3*y-sizey+85)
         Menu_Event();
        if(event.button.x<=x+600+sizex&&event.button.x>=x+600-sizex&&event.button.y<=3*y+sizey+85&&event.button.y>=3*y-sizey+85)
        {
            ofstream clc;
            clc.open(file_name, ofstream::trunc);
            clc.close();
            return;
        }
        }
  }
}
void Menu_Event()
{
    Sint16 x=screen->w/2;
    Sint16 y=screen->h/4;
    Sint16 sizex = 300;
    Sint16 sizey = 60;
    SDL_Event event;
while(true)
{
    Draw_Menu();
    while(SDL_PollEvent(&event))
    {
    if(event.type == SDL_QUIT ||
      (event.type == SDL_KEYDOWN &&
      event.key.keysym.sym == SDLK_ESCAPE))
    {
        return;
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
        if(event.button.button == SDL_BUTTON_LEFT)
        {
        if(event.button.x<=x+sizex&&event.button.x>=x-sizex&&event.button.y<=3*y+sizey&&event.button.y>=3*y-sizey)
         return;
        if(event.button.x<=x+sizex&&event.button.x>=x-sizex&&event.button.y<=2*y+sizey&&event.button.y>=2*y-sizey)
            High_Scores();
        if(event.button.x<=x+sizex&&event.button.x>=x-sizex&&event.button.y<=y+sizey&&event.button.y>=y-sizey)
            if(!Game::Start_Game())
                return;
        }
    }
}
}
void Draw_Menu()
{
    SDL_Surface *text_surface = NULL,*play,*hs,*escape;
    SDL_Color text_color;
    Uint32 back_color;
  back_color = SDL_MapRGB(screen->format,200,200,255);
  SDL_Rect pl;
  pl.x=0;pl.y=0;pl.h=1080;pl.w=1920;
  SDL_FillRect(screen,&pl,back_color);
    Uint32 color = SDL_MapRGB(screen->format,100,100,255);
    Sint16 sizex = 300;
    Sint16 sizey = 60;
     Sint16 x=screen->w/2;
     Sint16 y=screen->h/4;
     Draw_FillRect(screen,x-sizex,y-sizey,2*sizex,2*sizey,color);
     Draw_FillRect(screen,x-sizex,2*y-sizey,2*sizex,2*sizey,color);
     Draw_FillRect(screen,x-sizex,3*y-sizey,2*sizex,2*sizey,color);
  text_color.r = 0;
  text_color.g = 0;
  text_color.b = 255;
  Game::Text("Снег на голову",fnt,text_color,200,100);
  Game::Text("Начать игру",fnt,text_color,x-100,y-35);
  Game::Text("Лучшие результаты",fnt,text_color,x-180,y*2-35);
  Game::Text("Выход",fnt,text_color,x-50,y*3-35);
  SDL_Flip(screen);
}
void Screen_Saver()
{
    SDL_Event event;
    SDL_Color text_color;
    SDL_Rect dest;
    text_color.r = 0;
    text_color.g = 0;
    text_color.b = 255;
    dest.x=screen->w/2-140;
    dest.y=2*screen->h/5;
    Draw_Back();
    SDL_Surface* text;
    if(text = TTF_RenderUTF8_Solid(fnt,
                          "Снег на голову", text_color))
  {
    SDL_BlitSurface(text, NULL, screen,
                    &dest);
    SDL_FreeSurface(text);
    text = NULL;
  }
  dest.x=screen->w/2-280;
    dest.y=3*screen->h/5;
  if(text = TTF_RenderUTF8_Solid(fnt,
                          "Автор: Степанов, группа И976", text_color))
  {
    SDL_BlitSurface(text, NULL, screen,
                    &dest);
    SDL_FreeSurface(text);
    text = NULL;
  }
    SDL_Flip(screen);
    SDL_Delay(3500);
}
};
int main(int argc, char *argv[])
{
    srand(time(0));
    TTF_Font *fnt;
  SDL_Surface *screen;
  if (SDL_Init(SDL_INIT_EVERYTHING))
    return 1;
  if (TTF_Init())
    return 1;
  if(!(screen=SDL_SetVideoMode(1920,1080,32,
                               SDL_FULLSCREEN|SDL_ANYFORMAT|SDL_HWSURFACE))){
    TTF_Quit();
    SDL_Quit();
    return 1;
  }
  if(!(fnt = TTF_OpenFont("CharisSILR.ttf", 40))){
    TTF_Quit();
    SDL_Quit();
  }
  Menu menu = Menu(screen,fnt);
  menu.Screen_Saver();
  menu.Menu_Event();
  TTF_CloseFont(fnt);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
