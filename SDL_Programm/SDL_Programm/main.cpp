#include <iostream>
#include <fstream>
#include <clocale>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

using namespace std;

struct Window
{
	SDL_Window *win;
	SDL_Renderer *rend;
};
struct Sym
{
	int row, pos;
	char symbol;
	bool ihl;
	Sym(char s,int r, int p , bool b)
	{
		row = r;
		pos = p;
		symbol = s;
		ihl = b;
	}
};
struct text
{
	Sym *syms, *cs,*bff;
	TTF_Font *font;
	SDL_Rect symbox;
	SDL_Texture *list;
	char* nf;
	long i;
	int c;
	bool Load_Text(SDL_Renderer *rend, SDL_Rect wc, char* name)
	{ 
		bff = nullptr;
		nf = new char[20];
		char *cur = (char*)malloc(1 * sizeof(char));
		SDL_Rect rect; symbox.x = wc.x + 30; symbox.y = wc.y + 15; symbox.h = 16; symbox.w = 10;
		ifstream f;
		f.open(name);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderFillRect(rend, &wc);
		if (!f.is_open())
			return false;
		strcpy(nf, name);
		i = 0;
		int r = 0, p = 0, w = 0, h = 0;
		syms = nullptr;
		while (!f.eof())
		{
			f.read(cur, 1 * sizeof(char));
			if (wc.w + wc.x < wc.x + 30 + p * symbox.w)
			{
				r++; p = 0;
			}
			if (cur[0] == '\n')
			{
				syms = (Sym*)realloc(syms, (i + 1) * sizeof(struct Sym));
				syms[i] = Sym('\n', r, p, false);
				r++; p = 0;
				i++;
			}
			else
			{
				syms = (Sym*)realloc(syms, (i + 1) * sizeof(struct Sym));
				syms[i] = Sym(cur[0], r, p, false);
				i++; p++;
			}
		}
		f.close();
		cs = &syms[i];
		if (symbox.y + symbox.h*r < wc.h)
			list = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wc.w, wc.h);
		else
			list = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, wc.w, symbox.y + symbox.h*(r+1));
		Draw(rend, wc);
		return true;
	}
	SDL_Rect Centrd(SDL_Rect r, int w, int h)
	{
		SDL_Rect ret;
		ret.x = r.x + r.w / 2 - w / 2;
		ret.y = r.y + r.h / 2 - h / 2;
		ret.w = w;
		ret.h = h;
		return ret;
	}
	void Draw(SDL_Renderer *rend,SDL_Rect wc)
	{
		SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
		SDL_Rect rect;
		int w, h;
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_SetTextureBlendMode(list, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(rend, list);
		SDL_RenderClear(rend);
		for (int j = 0; j < i; j++)
		{
			if (syms[j].symbol != '\n')
			{
				SDL_Texture *t = SDL_CreateTextureFromSurface(rend, TTF_RenderUTF8_Blended(font, (char*)&syms[j].symbol, color));
				SDL_QueryTexture(t, NULL, NULL, &w, &h);
				symbox.x = 30 + syms[j].pos * symbox.w;
				symbox.y = 15 + syms[j].row * symbox.h;
				rect = Centrd(symbox, w, h);
				SDL_RenderCopy(rend, t, NULL, &rect);
				SDL_DestroyTexture(t);
			}
		}
		rect = wc; rect.x = 0; rect.y = 0;
		SDL_SetRenderTarget(rend, NULL);
		SDL_RenderCopy(rend, list, &rect, &wc);
		SDL_RenderPresent(rend);
	}
	bool Search(SDL_Renderer *rend, SDL_Rect wc, int x, int y, int lx, int ly, int scrolled)
	{
		int r1, r2, p1, p2;
		if (x - wc.x - 30 < 0)
			p1 = 0;
		else
			p1 = (x - wc.x - 30) / symbox.w;
		if (lx - wc.x - 30 < 0)
			p2 = 0;
		else 
			p2 = (lx - wc.x - 30) / symbox.w;
		if (y - wc.y - 15 < 0)
			r1 = 0;
		else
			r1 = (y - wc.y - 15 - scrolled) / symbox.h;
		if (ly - wc.y - 15 < 0)
			r2 = 0;
		else
			r2 = (ly - wc.y - 15 - scrolled) / symbox.h;
		if (r1 > r2)
		{
			return OutLine(rend, wc, r2, p2, r1, p1);
		}
		else
		if (r1 < r2)
		{
			return OutLine(rend, wc, r1, p1, r2, p2);
		}
		else
		{
			if (p1 > p2)
				return OutLine(rend, wc, r2, p2, r1, p1);
			else
				return OutLine(rend, wc, r1, p1, r2, p2);
		}
	}
	void Backspace(SDL_Renderer * rend)
	{
		i--;
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_Rect rt; rt.h = symbox.h; rt.w = symbox.w; rt.x = 30 + syms[i].pos * symbox.w; rt.y = 15 + syms[i].row * symbox.h;
		SDL_RenderFillRect(rend, &rt);
		syms = (Sym*)realloc(syms, i * sizeof(Sym));
	}
	bool OutLine(SDL_Renderer *rend,SDL_Rect wc,int r1, int p1, int r2, int p2)
	{
		bool k = false;
		SDL_SetRenderTarget(rend, list);
		for (int j = 0; j < i; j++)
		{
			if (syms[j].row == r1)
			{
				while (j < i && syms[j].row == r1)
				{
					if (syms[j].pos == p1)
						break;
					j++;
				}
				if (syms[j].row != r1)
					break;
				SDL_Rect r = symbox; r.x = 30 + syms[j].pos * symbox.w; r.y =  15 + syms[j].row * symbox.h;
				while (j < i)
				{
					if (!syms[j].ihl)
					{
						r.x = 30 + syms[j].pos * symbox.w; r.y = 15 + syms[j].row * symbox.h;
						SDL_SetRenderDrawColor(rend, 0, 0, 255, 100);
						SDL_RenderFillRect(rend, &r);
						syms[j].ihl = !syms[j].ihl;
						k = true;
					}
					if (syms[j].row == r2)
						break;
					j++;
				}
				while (syms[j].row == r2 && j < i)
				{
					if (!syms[j].ihl)
					{
						r.x = 30 + syms[j].pos * symbox.w;
						SDL_SetRenderDrawColor(rend, 0, 0, 255, 100);
						SDL_RenderFillRect(rend, &r);
						syms[j].ihl = !syms[j].ihl;
						k = true;
					}
					if (syms[j].pos == p2)
						break;
					j++;
				}
				break;
			}
		}
		SDL_SetRenderTarget(rend, NULL);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		return k;
	}
	void Put(SDL_Renderer *rend,SDL_Rect wc, char * chr)
	{
		char *buf = (char*)calloc(1, sizeof(char));
		strcpy(buf, chr);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_SetTextureBlendMode(list, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(rend, list);
		SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
		SDL_Rect rect;
		int r = syms[i - 1].row, p = syms[i - 1].pos, w, h;
		if (syms[i - 1].symbol == '\n')
		{
			r++; p = 0;
		}
		else
		p++;
		if (wc.w + wc.x < wc.x + 30 + p * symbox.w)
		{
			r++; p = 0;
		}
		if (chr[0] == '\n')
		{
			syms = (Sym*)realloc(syms, (i + 1) * sizeof(struct Sym));
			syms[i] = Sym('\n', r, p, false);
			i++;
		}
		else
		{
			syms = (Sym*)realloc(syms, (i + 1) * sizeof(struct Sym));
			syms[i] = Sym(buf[0], r, p, false);
			i++;
			SDL_Texture *t = SDL_CreateTextureFromSurface(rend, TTF_RenderUTF8_Blended(font, (char*)&syms[i - 1].symbol, color));
			SDL_QueryTexture(t, NULL, NULL, &w, &h);
			symbox.x = 30 + syms[i - 1].pos * symbox.w;
			symbox.y = 15 + syms[i - 1].row * symbox.h;
			rect = Centrd(symbox, w, h);
			SDL_RenderCopy(rend, t, NULL, &rect);
			SDL_DestroyTexture(t);
		}
		SDL_SetRenderTarget(rend, NULL);
		rect = wc; rect.x = 0; rect.y = 0;
		SDL_RenderCopy(rend, list, &rect, &wc);
		SDL_RenderPresent(rend);
	}
	void Click(SDL_Renderer* rend, SDL_Rect wc)
	{
		int w, h;
		SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
		SDL_Rect rect;
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_SetTextureBlendMode(list, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(rend, list);
		for (int j = 0; j < i; j++)
		{
			if (syms[j].ihl)
			{
				if (syms[j].symbol != '\n')
				{
					SDL_Texture *t = SDL_CreateTextureFromSurface(rend, TTF_RenderUTF8_Blended(font, (char*)&syms[j].symbol, color));
					SDL_QueryTexture(t, NULL, NULL, &w, &h);
					symbox.x = 30 + syms[j].pos * symbox.w;
					symbox.y = 15 + syms[j].row * symbox.h;
					SDL_RenderFillRect(rend, &symbox);
					rect = Centrd(symbox, w, h);
					SDL_RenderCopy(rend, t, NULL, &rect);
					syms[j].ihl = false;
					SDL_DestroyTexture(t);
				}
				else
				{
					symbox.x = 30 + syms[j].pos * symbox.w;
					symbox.y = 15 + syms[j].row * symbox.h;
					SDL_RenderFillRect(rend, &symbox);
					syms[j].ihl = false;
				}
			}
		}
		rect = wc; rect.x = 0; rect.y = 0;
		SDL_SetRenderTarget(rend, NULL);
		SDL_RenderCopy(rend, list, &rect, &wc);
		SDL_RenderPresent(rend);
	}
	void Paste(SDL_Renderer *rend, SDL_Rect wc)
	{
		if (bff != nullptr)
		{
			for (int j = 0; j < c; j++)
			{
				SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
				SDL_Rect rect;
				int r = syms[i - 1].row, p = syms[i - 1].pos, w, h;
				p++;
				if (wc.w + wc.x < wc.x + 30 + p * symbox.w)
				{
					r++; p = 0;
				}
				syms = (Sym*)realloc(syms, (i + 1) * sizeof(struct Sym));
				syms[i] = Sym(bff[j].symbol, r, p, false);
				i++;
				SDL_Texture *t = SDL_CreateTextureFromSurface(rend, TTF_RenderUTF8_Blended(font, (char*)&syms[i-1].symbol, color));
				SDL_QueryTexture(t, NULL, NULL, &w, &h);
				symbox.x = 30 + syms[i-1].pos * symbox.w;
				symbox.y = 15 + syms[i-1].row * symbox.h;
				rect = Centrd(symbox, w, h);
				SDL_RenderCopy(rend, t, NULL, &rect);
				SDL_DestroyTexture(t);
			}
		}
		c = 0;
	}
	void Copy()
	{
		c = 0;
		bool on = false;
		for (int j = 0; j < i; j++)
		{
			if (syms[j].ihl)
			{
				bff = (Sym*)realloc(bff, (c + 1) * sizeof(Sym));
				bff[c] = syms[j];
				c++;
				on = true;
			}
			else
				if (on)
					break;
		}
	}
};
struct button
{
	bool is_pressed;
	SDL_Rect box;
	SDL_Texture *pressed, *unpressed;
	button(SDL_Renderer *rend, const char* unpr, const char* prsd, int x, int y)
	{
		is_pressed = false;
		box.x = x;
		box.y = y;
		SDL_Surface *image = SDL_LoadBMP(prsd);
		box.h = image->h;
		box.w = image->w;
		pressed = SDL_CreateTextureFromSurface(rend, image);
		image = SDL_LoadBMP(unpr);
		unpressed = SDL_CreateTextureFromSurface(rend, image);
	}
	button(SDL_Renderer *rend, TTF_Font* font, const char* text, int x, int y)
	{
		is_pressed = false;
		SDL_Color color;
		SDL_Rect rect;
		color.r = 0; color.g = 0; color.b = 0;
		box.x = x;
		box.y = y;
		SDL_Surface *tr = TTF_RenderUTF8_Solid(font, text, color);
		SDL_Surface *su = SDL_CreateRGBSurface(0, 120, 30, 24, 255, 255, 255, 255);
		box.h = su->h;
		box.w = su->w;
		su = common_button(su, false);
		rect = Centrd(tr, su);
		SDL_BlitSurface(tr, NULL, su, &rect);
		SDL_SetClipRect(su, &box);
		pressed = SDL_CreateTextureFromSurface(rend, su);
		SDL_Surface *sp = SDL_CreateRGBSurface(0, 120, 30, 24, 255, 255, 255, 255);
		sp = common_button(sp, true);
		rect = Centrd(tr, sp);
		SDL_BlitSurface(tr, NULL, sp, &rect);
		SDL_SetClipRect(sp, &box);
		unpressed = SDL_CreateTextureFromSurface(rend, sp);
	}
	button(SDL_Renderer *rend,const char* file_name, SDL_Rect r)
	{
		is_pressed = false;
		box = r;
		SDL_Color color;
		SDL_Rect rect;
		color.r = 0; color.g = 0; color.b = 0;
		SDL_Surface *ic = SDL_LoadBMP(file_name);
		SDL_Surface *su = SDL_CreateRGBSurface(0, r.h, r.w, 24, 255, 255, 255, 255);
		su = common_button(su, false);
		rect = Centrd(ic, su);
		SDL_BlitSurface(ic, NULL, su, &rect);
		SDL_SetClipRect(su, &box);
		pressed = SDL_CreateTextureFromSurface(rend, su);
		SDL_Surface *sp = SDL_CreateRGBSurface(0, r.h, r.w, 24, 255, 255, 255, 255);
		sp = common_button(sp, true);
		rect = Centrd(ic, sp);
		SDL_BlitSurface(ic, NULL, sp, &rect);
		SDL_SetClipRect(sp, &box);
		unpressed = SDL_CreateTextureFromSurface(rend, sp);
	}
	SDL_Rect Centrd(SDL_Surface* one, SDL_Surface* two)
	{
		SDL_Rect o = one->clip_rect, t = two->clip_rect,ret;
		ret.x = t.w / 2 - o.w / 2;
		ret.y = t.h / 2 - o.h / 2;
		ret.h = o.h;
		ret.w = o.w;
		return ret;
	}
	SDL_Surface *common_button(SDL_Surface* sur,bool prsd)
	{
		if (prsd)
		{
			Uint32 color = SDL_MapRGB(sur->format, 200, 200, 200);
			SDL_Rect but;
			but.x = 0;
			but.y = 0;
			but.h = sur->h;
			but.w = sur->w;
			SDL_FillRect(sur, &but, color);
			color = SDL_MapRGB(sur->format, 170, 170, 170);
			but.x = 3;
			but.y = 3;
			but.h = sur->h - 6;
			but.w = sur->w - 6;
			SDL_FillRect(sur, &but, color);
		}
		else
		{
			Uint32 color = SDL_MapRGB(sur->format, 170, 170, 170);
			SDL_Rect but;
			but.x = 0;
			but.y = 0;
			but.h = sur->h;
			but.w = sur->w;
			SDL_FillRect(sur, &but, color);
			color = SDL_MapRGB(sur->format, 200, 200, 200);
			but.x = 3;
			but.y = 3;
			but.h = sur->h - 6;
			but.w = sur->w - 6;
			SDL_FillRect(sur, &but, color);
		}
		return sur;
	}
};
struct picture
{
	SDL_Texture *texture;
	char *nf;
	SDL_Texture *Load_Pic(const char* file_name, SDL_Renderer *rend)
	{
		SDL_Surface *image = SDL_LoadBMP(file_name);
		SDL_Texture *t = SDL_CreateTextureFromSurface(rend, image);
		if (t == nullptr)
			return NULL;
		return t;
	}
	SDL_Texture *Load_Pic(char* file_name, SDL_Renderer *rend)
	{
		nf = new char[20];
		SDL_Texture *t = nullptr;
		SDL_Surface *image = SDL_LoadBMP(file_name);
		if(image != nullptr)
		t = SDL_CreateTextureFromSurface(rend, image);
		if (t == nullptr)
			return NULL;
		else
		{
			strcpy(nf, file_name);
			texture = t;
			return t;
		}
	}
	void Blit(SDL_Renderer* rend,SDL_Texture* t, int x, int y)
	{
		int w, h;
		SDL_QueryTexture(t, NULL, NULL, &w, &h);
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.h = h;
		rect.w = w;
		if (t)
		{
			SDL_RenderCopy(rend, t, NULL, &rect);
		}
	}
	void Blit(SDL_Renderer* rend, button *b)
	{
		if (b->is_pressed)
		{
			SDL_RenderCopy(rend, b->pressed, NULL, &b->box);
		}
		else
		{
			SDL_RenderCopy(rend, b->unpressed, NULL, &b->box);
		}
	}
	void DrawLine(SDL_Renderer* rend,double mul,SDL_Rect r,SDL_Rect wc,int x, int y, int lx, int ly)
	{
		SDL_SetRenderDrawColor(rend, 120, 120, 120, 255);
		SDL_RenderDrawLine(rend, r.x + ((x - wc.x) * mul), r.y + ((y - wc.y) * mul), r.x + ((lx - wc.x) * mul), r.y + ((ly - wc.y) * mul));
	}
	void PrintDraw(SDL_Renderer* rend,SDL_Texture* print , double mul, SDL_Rect r, SDL_Rect wc, int x, int y)
	{
		int w, h;
		SDL_QueryTexture(print, NULL, NULL, &w, &h);
		SDL_Rect pd; pd.h = h; pd.w = w; pd.x = r.x - w / 2 + ((x - wc.x)*mul); pd.y = r.y - h / 2 + ((y - wc.y)*mul);
		SDL_RenderCopy(rend, print, NULL, &pd);
	}
};
struct interf : public Window
{
	SDL_Texture *back;
	button *b1, *b2, *bx;
	SDL_Rect work_space;
	picture Pred;
	text Wred;
	interf(const char* t, int w, int h)
	{
		win = SDL_CreateWindow(t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_BORDERLESS);
		rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
		Pred.texture = nullptr;
		Wred.syms = nullptr;
		Wred.nf = nullptr;
		Pred.nf = nullptr;
		Wred.font = TTF_OpenFont("cour.ttf", 14);
	}
	bool in_check(SDL_Rect r, int x, int y)
	{
		if ((r.x + r.w > x && r.x < x) && (r.y + r.h > y && r.y < y))
			return true;
		else 
			return false;
	}
	void Overdraw(button *b)
	{
		int w,h;
		SDL_GetWindowSize(win, &w, &h);
		SDL_Rect top, side;
		top.x = 0;
		top.y = 0;
		top.h = b->box.h;
		top.w = w;
		side.x = 0;
		side.y = 0;
		side.h = h;
		side.w = b->box.w/3;
		SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);
		SDL_RenderFillRect(rend, &top);
		SDL_RenderFillRect(rend, &side);
		top.x = 0;
		top.y = b->box.h-3;
		top.h = 3;
		top.w = w;
		side.x = b->box.w / 3-3;
		side.y = 0;
		side.h = h;
		side.w = 3;
		SDL_SetRenderDrawColor(rend, 220, 220, 220, 255);
		SDL_RenderFillRect(rend, &top);
		SDL_RenderFillRect(rend, &side);
		work_space.h = h - b->box.h; work_space.w = w - b->box.w / 3; work_space.x = b->box.w / 3; work_space.y = b->box.h;
	}
	char *Open(bool is_there)
	{
		char* fname;
		char text[18] = { 0 };
		SDL_Rect top, rinp, inp;
		SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
		int x, y, wig, hei,counter = 0;
		TTF_Font *font = TTF_OpenFont("cour.ttf", 13);
		Window w = Window();
		w.win = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_BORDERLESS);
		w.rend = SDL_CreateRenderer(w.win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		button *bo1, *bo2, *bxo, *boi;
		SDL_GetWindowSize(w.win, &wig, &hei);
		bxo = new button(w.rend, "xbut1.bmp", "xbut2.bmp", wig - 80, 0);
		bo1 = new button(w.rend, font, "Открыть", 240, 80);
		boi = new button(w.rend, font, "Продолжить", 140, 160);
		SDL_SetRenderDrawColor(w.rend, 230, 230, 230, 255);
		SDL_RenderClear(w.rend);
		SDL_SetRenderDrawColor(w.rend, 200, 200, 200, 255);
		top.h = 35; top.w = wig; top.x = 0; top.y = 0;
		SDL_RenderFillRect(w.rend, &top);
		rinp.h = bo1->box.h; rinp.w = 216; rinp.x = 10; rinp.y = bo1->box.y;
		SDL_SetRenderDrawColor(w.rend, 255, 255, 255, 255);
		SDL_RenderFillRect(w.rend, &rinp);
		SDL_SetRenderDrawColor(w.rend, 200, 200, 200, 255);
		SDL_RenderDrawRect(w.rend, &rinp);
		if (is_there)
		{
			Pred.Blit(w.rend, boi);
		}
		Pred.Blit(w.rend, bo1);
		Pred.Blit(w.rend, bxo);
		SDL_RenderPresent(w.rend);
		SDL_Event e;
		inp.h = 16; inp.w = 8; inp.x = rinp.x + 2; inp.y = rinp.y + 7;
		while (true)
		{
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
				{
					SDL_HideWindow(w.win);
					SDL_DestroyRenderer(w.rend);
					SDL_DestroyWindow(w.win);
					return nullptr;
				}
				case SDL_TEXTINPUT:
				{
					char* chr;
					if (counter < 18)
					{
						chr = e.text.text;
						text[counter] = chr[0];
						SDL_RenderCopy(w.rend, SDL_CreateTextureFromSurface(w.rend, TTF_RenderUTF8_Blended(font, chr, color)), NULL, &inp);
						SDL_RenderPresent(w.rend);
						inp.x += 12;
						counter++;
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					if (e.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
					{
						if (counter > 0)
						{
							const char *cr = " ";
							inp.x -= 12;
							counter--;
							text[counter] = cr[0];
							SDL_SetRenderDrawColor(w.rend, 255, 255, 255, 255);
							SDL_RenderFillRect(w.rend, &inp);
							SDL_RenderPresent(w.rend);
							break;
						}
					}
					if (e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER)
					{
						if (text[0] != NULL)
						{
							SDL_DestroyRenderer(w.rend);
							SDL_DestroyWindow(w.win);
							fname = (char*)calloc(strlen(text) + 1, sizeof(char));
							strcpy_s(fname, strlen(text) + 1, text);
							return fname;
						}
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					SDL_GetMouseState(&x, &y);
					if (is_there)
					{
						if (in_check(boi->box, x, y))
						{
							Press(w.rend, boi);
							break;
						}
					}
					if (in_check(bo1->box, x, y))
					{
						Press(w.rend,bo1);
						break;
					}
					if (in_check(bxo->box, x, y))
					{
						Press(w.rend,bxo);
						break;
					}
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					SDL_GetMouseState(&x, &y);
					if (is_there)
					{
						if (in_check(boi->box, x, y) && boi->is_pressed)
						{
							Press(w.rend, boi);
							SDL_DestroyRenderer(w.rend);
							SDL_DestroyWindow(w.win);
							return nullptr;
						}
					}
					if (bo1->is_pressed && in_check(bo1->box, x, y))
					{
						Press(w.rend,bo1);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						fname = (char*)calloc(strlen(text) + 1,sizeof(char));
						strcpy_s(fname, strlen(text) + 1, text);
						return fname;
					}
					if (bxo->is_pressed && in_check(bxo->box, x, y))
					{
						Press(w.rend,bxo);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						return nullptr;
					}
					if (bo1->is_pressed)
					{
						Press(w.rend,bo1);
						break;
					}
					if (bxo->is_pressed)
					{
						Press(w.rend,bxo);
						break;
					}
					break;
				}
				}
			}
		}
	}
	int Save(char* name)
	{
		TTF_Font *font = TTF_OpenFont("cour.ttf", 13);
		int x, y, wig, hei;
		SDL_Rect top;
		button *bxo, *bo1, *bo2, *bo3;
		Window w = Window();
		char buff[20],b[30];
		strcpy(buff, name);
		SDL_Color color; color.r = 0; color.g = 0; color.b = 0;
		sprintf(b, "Сохранить %s?", buff);
		w.win = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, SDL_WINDOW_BORDERLESS);
		w.rend = SDL_CreateRenderer(w.win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		SDL_Texture *t = SDL_CreateTextureFromSurface(w.rend, TTF_RenderUTF8_Blended(Wred.font, b, color));
		SDL_GetWindowSize(w.win, &wig, &hei);
		bxo = new button(w.rend, "xbut1.bmp", "xbut2.bmp", wig - 80, 0);
		bo1 = new button(w.rend, font, "Да", 40, 80);
		bo2 = new button(w.rend, font, "Нет", 240, 80);
		bo3 = new button(w.rend, font, "Отмена", 140, 160);
		SDL_SetRenderDrawColor(w.rend, 230, 230, 230, 255);
		SDL_RenderClear(w.rend);
		SDL_SetRenderDrawColor(w.rend, 200, 200, 200, 255);
		top.h = 35; top.w = wig; top.x = 0; top.y = 0;
		SDL_RenderFillRect(w.rend, &top);
		SDL_QueryTexture(t, NULL, NULL, &wig, &hei);
		top.w = wig; top.h = hei;
		SDL_RenderCopy(w.rend, t, NULL, &top);
		Pred.Blit(w.rend, bxo);
		Pred.Blit(w.rend, bo1);
		Pred.Blit(w.rend, bo2);
		Pred.Blit(w.rend, bo3);
		SDL_RenderPresent(w.rend);
		SDL_Event e;
		while (true)
		{
			while (SDL_PollEvent(&e))
			{
				SDL_GetMouseState(&x, &y);
				switch (e.type)
				{
				case SDL_MOUSEBUTTONDOWN:
				{
					if (in_check(bxo->box, x, y))
					{
						Press(w.rend,bxo);
					}
					if (in_check(bo1->box, x, y))
					{
						Press(w.rend, bo1);
					}
					if (in_check(bo2->box, x, y))
					{
						Press(w.rend, bo2);
					}
					if (in_check(bo3->box, x, y))
					{
						Press(w.rend, bo3);
					}
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					if (bxo->is_pressed && in_check(bxo->box, x, y))
					{
						Press(w.rend, bxo);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						return 1;
					}
					if (bo1->is_pressed && in_check(bo1->box, x, y))
					{
						Press(w.rend, bo1);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						return 0;
					}
					if (bo2->is_pressed && in_check(bo2->box, x, y))
					{
						Press(w.rend, bo2);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						return 2;
					}
					if (bo3->is_pressed && in_check(bo3->box, x, y))
					{
						Press(w.rend, bo3);
						SDL_DestroyRenderer(w.rend);
						SDL_DestroyWindow(w.win);
						return 1;
					}
					break;
				}
				}
			}
		}
	}
	void Show_Interface()
	{
		int x, y, w, h;
		SDL_GetWindowSize(win, &w, &h);
		b1 = new button(rend, "but1.1.bmp", "but1.2.bmp", 0, 0);
		b2 = new button(rend, "but2.1.bmp", "but2.2.bmp", b1->box.w, 0);
		bx = new button(rend, "xbut1.bmp", "xbut2.bmp", w - 80, 0);
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderClear(rend);
		Overdraw(b1);
		Pred.Blit(rend, b1);
		Pred.Blit(rend, b2);
		Pred.Blit(rend, bx);
		SDL_RenderPresent(rend);
		SDL_Event e;
		while (true)
		{
			while (SDL_PollEvent(&e))
			{
				I_Events(e);
			}
		}
	}
	bool I_Events(SDL_Event e)
	{
		int x, y;
		switch (e.type)
		{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			{
				SDL_DestroyRenderer(rend);
				SDL_DestroyWindow(win);
				SDL_Quit();
				exit(0);
			}
			break;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			SDL_GetMouseState(&x, &y);
			char* word, *name;
			if (in_check(b1->box, x, y))
			{
				Press(rend, b1);
				if (Wred.nf == nullptr)
				{
					word = Open(false);
					if (word == nullptr)
					{
						Press(rend, b1);
						return true;
					}
					else
					{
						if (Wred.Load_Text(rend, work_space, word))
						{
							if (b2->is_pressed)
							{
								Overdraw(b1);
								Pred.Blit(rend, b1);
								Pred.Blit(rend, b2);
								Pred.Blit(rend, bx);
								SDL_RenderPresent(rend);
								Press(rend, b2);
							}
							Word();
						}
						else
							Press(rend, b1);
						return true;
					}
				}
				else
				{
					word = Open(true);
					if (word == nullptr)
					{
						Word();
						return true;
					}
					else
					{
						if (Wred.Load_Text(rend, work_space, word))
						{
							if (b2->is_pressed)
							{
								Overdraw(b1);
								Pred.Blit(rend, b1);
								Pred.Blit(rend, b2);
								Pred.Blit(rend, bx);
								SDL_RenderPresent(rend);
								Press(rend, b2);
							}
							Word();
						}
						else
							Press(rend, b1);
						return true;
					}
				}
				return true;
				break;
			}
			if (in_check(b2->box, x, y))
			{
				if (b1->is_pressed)
				{
					Press(rend, b1);
				}
				Press(rend, b2);
				if (Pred.texture == nullptr)
				{
					word = Open(false);
					if (word == nullptr)
					{
						Press(rend, b2);
						return true;
					}
					else
					{
						if (Pred.Load_Pic(word, rend) != NULL)
							Paint();
						return true;
						break;
					}
				}
				else
				{
					word = Open(true);
					if (word == nullptr)
					{
						Paint();
						return true;
					}
					else
					{
						if(Pred.Load_Pic(word, rend)!=NULL)
						Paint();
						return true;
						break;
					}
				}
				return true;
				break;
			}
			if (in_check(bx->box, x, y))
			{
				Press(rend, bx);
				return true;
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			SDL_GetMouseState(&x, &y);
			if (bx->is_pressed && in_check(bx->box, x, y))
			{
				Press(rend, bx);
				if (Pred.nf!=nullptr)
				{
					switch (Save(Pred.nf))
					{
					case 0:
					{
						SDL_SetRenderTarget(rend, back);
						int width, height;
						SDL_QueryTexture(Pred.texture, NULL, NULL, &width, &height);
						SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
						SDL_RenderReadPixels(rend, NULL, surface->format->format, surface->pixels, surface->pitch);
						SDL_SaveBMP(surface, Pred.nf);
						SDL_FreeSurface(surface);
						SDL_SetRenderTarget(rend, NULL);
						break;
					}
					case 1:
					{
						return true;
					}
					case 2:
					{
						break;
					}
					}
				}
				if (Wred.nf != nullptr)
				{
					switch (Save(Wred.nf))
					{
					case 0:
					{
						ofstream f;
						f.open(Wred.nf, ios::beg | ios::trunc);
						for (int j = 0; j < Wred.i; j++)
						{
							f << Wred.syms[j].symbol;
						}
						f.close();
						break;
					}
					case 1:
					{
						return true;
					}
					case 2:
					{
						break;
					}
					}
				}
				SDL_DestroyRenderer(rend);
				SDL_DestroyWindow(win);
				SDL_Quit();
				exit(0);
			}
			if (bx->is_pressed)
			{
				Press(rend, bx);
				return true;
			}
			break;
		}
		}
		return false;
	}
	void Press(SDL_Renderer* rnd,button *b)
	{
		b->is_pressed = !b->is_pressed;
		Pred.Blit(rnd, b);
		SDL_RenderPresent(rnd);
	}
	void Word()
	{
		SDL_Rect cur_space = work_space; cur_space.x = 0; cur_space.y = 0;
		SDL_Event e;
		int x = 0, y = 0, xl = 0, yl = 0;
		int scrolled = 0, t_size;
		char *buff;
		SDL_QueryTexture(Wred.list, NULL, NULL, NULL, &t_size);
		SDL_RenderCopy(rend, Wred.list, &cur_space, &work_space);
		SDL_RenderPresent(rend);
		while (true)
		{
			while (SDL_PollEvent(&e))
			{
				if (!I_Events(e))
				{
					SDL_GetMouseState(&x, &y);
					switch (e.type)
					{
					case SDL_KEYDOWN:
					{
						switch (e.key.keysym.scancode)
						{
						case SDL_SCANCODE_KP_ENTER:
						{
							char *chr = new char[1];
							chr[0] = '\n';
							Wred.Click(rend, work_space);
							Wred.Put(rend, work_space, chr);
							break;
						}
						case SDL_SCANCODE_BACKSPACE:
						{
							if (Wred.i > 0 && e.button.state != SDL_PRESSED)
							{
								SDL_SetRenderTarget(rend, Wred.list);
								Wred.Backspace(rend);
								SDL_SetRenderTarget(rend, NULL);
								SDL_RenderCopy(rend, Wred.list, &cur_space, &work_space);
								SDL_RenderPresent(rend);
							}
							break;
						}
						case SDL_SCANCODE_LCTRL:
						{
							if (e.button.state != SDL_PRESSED)
							{
								Wred.Copy();
							}
							break;
						}
						case SDL_SCANCODE_LALT:
						{
							if (e.button.state != SDL_PRESSED)
							{
								SDL_SetRenderTarget(rend, Wred.list);
								Wred.Paste(rend, work_space);
								SDL_SetRenderTarget(rend, NULL);
								SDL_RenderCopy(rend, Wred.list, &cur_space, &work_space);
								SDL_RenderPresent(rend);
							}
							break;
						}
						}
						break;
					}
					case SDL_TEXTINPUT:
					{
						if (e.button.state != SDL_PRESSED)
						{
							char* chr;
							chr = e.text.text;
							Wred.Click(rend, work_space);
							Wred.Put(rend, work_space, chr);
						}
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						if (in_check(work_space, x, y))
						{
							Wred.Click(rend,work_space);
							xl = x;
							yl = y;
						}
						break;
					}
					case SDL_MOUSEBUTTONUP:
					{
						if (xl != 0)
						{
							Wred.Search(rend, work_space, xl, yl, x, y, scrolled);
							SDL_RenderCopy(rend, Wred.list, &cur_space, &work_space);
							SDL_RenderPresent(rend);
						}
						xl = 0;
						yl = 0;
						break;
					}
					case SDL_MOUSEWHEEL:
					{
						if (e.button.state != SDL_PRESSED)
						{
							if (e.button.x > 0)
								if (scrolled >= Wred.symbox.h)
									scrolled -= Wred.symbox.h;
								else
									scrolled = 0;
							else
								if (scrolled <= t_size - work_space.h - Wred.symbox.h)
									scrolled += Wred.symbox.h;
								else
									scrolled = t_size - work_space.h;
							cur_space.y = scrolled;
							SDL_RenderCopy(rend, Wred.list, &cur_space, &work_space);
							SDL_RenderPresent(rend);
							break;
						}
						break;
					}
					}
				}
			}
		}
	}
	void Paint()
	{
		int w,h,x = 0, y = 0, xl = 0, yl = 0;
		double mul = 1;
		SDL_Rect r,fp;
		button *sb1, *sb2,*sb3,*act=nullptr;
		r.w = b1->box.w / 6;
		r.h = r.w;
		r.x = 0;
		r.y = b1->box.h;
		sb1 = new button(rend, "pbut1.bmp", r);
		r.x = r.w;
		sb2 = new button(rend, "pbut2.bmp", r);
		r.x = 0;
		r.y = b1->box.h + r.w;
		sb3 = new button(rend, "pbut3.bmp", r);
		Pred.Blit(rend, sb1);
		Pred.Blit(rend, sb2);
		Pred.Blit(rend, sb3);
		r.h = work_space.h;
		r.w = work_space.w;
		r.x = 0;
		r.y = 0;
		int iw = r.w, ih = r.h;
		auto cur_space = work_space;
		fp = work_space;
		SDL_QueryTexture(Pred.texture, NULL, NULL, &w, &h);
		SDL_RenderCopy(rend, Pred.texture, &r, &work_space);
		back = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_Texture *print = SDL_CreateTextureFromSurface(rend, SDL_LoadBMP("tod.bmp"));
		SDL_SetTextureBlendMode(back, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(rend, back);
		SDL_RenderCopy(rend, Pred.texture, NULL, NULL);
		SDL_SetRenderTarget(rend, NULL);
		SDL_RenderPresent(rend);
		SDL_Event e;
		while (true)
		{
			while (SDL_PollEvent(&e))
			{
				SDL_GetMouseState(&x, &y);
				if(!I_Events(e))
				switch (e.type)
				{
				case SDL_MOUSEWHEEL:
				{
					if (e.button.x > 0)
					{
						if (mul > 0.0625)
						{
							mul /= 2;
							r.h = r.h / 2;
							r.w = r.w / 2;
							if (r.w > w || r.h > h)
							{
								r.x = 0;
								r.y = 0;
								cur_space.w = iw / mul;
								cur_space.h = ih / mul;
								SDL_RenderCopy(rend, back, &r, &cur_space);
								SDL_RenderPresent(rend);
							}
							else
							{
								SDL_RenderCopy(rend, back, &r, &work_space);
								SDL_RenderPresent(rend);
							}
						}
						break;
					}
					else
					{
						if (mul < 16.0)
						{
							mul *= 2;
							r.h = r.h * 2;
							r.w = r.w * 2;
							if (r.w > w || r.h > h)
							{
								r.x = 0;
								r.y = 0;
								cur_space.w = iw / mul;
								cur_space.h = ih / mul;
								SDL_SetRenderDrawColor(rend, 228, 228, 228, 255);
								SDL_RenderFillRect(rend, &work_space);
								SDL_RenderCopy(rend, back, &r, &cur_space);
								SDL_RenderPresent(rend);
							}
							else
							{
								if (w - r.x < r.w)
									r.x = w - r.w;
								if (h - r.y < r.h)
									r.y = h - r.h;
								SDL_RenderCopy(rend, back, &r, &work_space);
								SDL_RenderPresent(rend);
							}
						}
						break;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
					{
						if (in_check(sb1->box, x, y))
						{
							if(act!=nullptr)
								Press(rend, act);
							act = sb1;
							Press(rend,sb1);
						}
						if (in_check(sb2->box, x, y))
						{
							if (act != nullptr)
								Press(rend, act);
							act = sb2;
							Press(rend,sb2);
						}
						if (in_check(sb3->box, x, y))
						{
							if (act != nullptr)
								Press(rend, act);
							act = sb3;
							Press(rend, sb3);
						}
						if (in_check(work_space, x, y))
						{
							xl = x; yl = y;
							if (act == sb2)
							{
								SDL_SetRenderTarget(rend, back);
								Pred.PrintDraw(rend, print, mul, r, work_space, x, y);
								SDL_SetRenderTarget(rend, NULL);
								if (r.w > w || r.h > h)
								{
									SDL_RenderCopy(rend, back, &r, &cur_space);
								}
								else
								{
									SDL_RenderCopy(rend, back, &r, &work_space);
								}
								SDL_RenderPresent(rend);
							}
							if (act == sb1)
							{
								SDL_SetRenderTarget(rend, back);
								Pred.DrawLine(rend, mul, r, work_space, x, y, xl, yl);
								xl = x; yl = y;
								SDL_SetRenderTarget(rend, NULL);
								if (r.w > w || r.h > h)
								{
									SDL_RenderCopy(rend, back, &r, &cur_space);
								}
								else
								{
									SDL_RenderCopy(rend, back, &r, &work_space);
								}
								SDL_RenderPresent(rend);
							}
						}
						break;
					}
				case SDL_MOUSEMOTION:
					{
						if (xl!=0)
						{
							if (in_check(work_space, x, y))
							{
								if (act == sb3)
								{
									if (r.w > w || r.h > h)
									{}
									else
									{
										if (x - xl > 0)
										{
											if (r.x > x - xl)
												r.x -= (x - xl)*mul;
											else
												r.x -= r.x;
										}
										else
										{
											if (w - (r.x + r.w) > -(x - xl))
												r.x -= (x - xl)*mul;
											else
												r.x = w - r.w;
										}
										if (y - yl > 0)
										{
											if (r.y > y - yl)
												r.y -= (y - yl)*mul;
											else
												r.y -= r.y;
										}
										else
										{
											if (h - (r.y + r.h) > -(y - yl))
												r.y -= (y - yl)*mul;
											else
												r.y = h - r.h;
										}
										SDL_RenderCopy(rend, back, &r, &work_space);
										SDL_RenderPresent(rend);
									}
									xl = x; yl = y;
								}
								if (act == sb1)
								{
									SDL_SetRenderTarget(rend, back);
									Pred.DrawLine(rend, mul, r, work_space, x, y, xl, yl);
									xl = x; yl = y;
									SDL_SetRenderTarget(rend, NULL);
									if (r.w > w || r.h > h)
									{
										SDL_RenderCopy(rend, back, &r, &cur_space);
									}
									else
									{
										SDL_RenderCopy(rend, back, &r, &work_space);
									}
									SDL_RenderPresent(rend);
								}
								if (act == sb2)
								{
									SDL_SetRenderTarget(rend, back);
									Pred.PrintDraw(rend,print, mul, r, work_space, x, y);
									SDL_SetRenderTarget(rend, NULL);
									if (r.w > w || r.h > h)
									{
										SDL_RenderCopy(rend, back, &r, &cur_space);
									}
									else
									{
										SDL_RenderCopy(rend, back, &r, &work_space);
									}
									SDL_RenderPresent(rend);
								}
							}
						}
						break;
					}
				case SDL_MOUSEBUTTONUP:
					{
						xl = 0; yl = 0;
						break;
					}
				}
			}
		}
	}
};
int main(int argc, char **argv) {
	setlocale(LC_ALL, "Russian");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Can't init everything"<< endl;
		return 1;
	}
	if (IMG_Init(IMG_INIT_JPG) != 1)
	{
		cout << "Can't init jpg" << endl;
		return 1;
	}
	if (TTF_Init() == -1)
	{
		cout << "Can't init ttf" << endl;
		return 1;
	}
	interf interf("Redactor 2019", 800, 600);
	interf.Show_Interface();
	return 0;
}