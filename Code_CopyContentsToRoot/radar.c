/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

void initRadar(void)
{
	memset(&stage.radar, 0, sizeof(SDL_Rect));
	SDL_Rect radarView = { PADDING, SCREEN_HEIGHT - (RADAR_SIZE + PADDING), RADAR_SIZE, RADAR_SIZE };
	stage.radar = radarView;
}
void drawBackground(void)
{
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(app.renderer, &stage.radar);
	// make an outline
	SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(app.renderer, &stage.radar);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}
void drawTitle(void)
{	
	SDL_SetRenderDrawColor(app.renderer, 20, 20, 20, 25);
	SDL_Rect r = { stage.radar.x, stage.radar.y - GLYPH_HEIGHT, RADAR_SIZE, GLYPH_HEIGHT};
	SDL_RenderFillRect(app.renderer, &r);
	// Added simple Title reusing drawText function	
	drawText(stage.radar.x + (stage.radar.w * .5), stage.radar.y - GLYPH_HEIGHT, 1, 55, 255, TEXT_CENTER, "RADAR");
	// Add simple outline effect
	drawText(stage.radar.x + (stage.radar.w * .5) + 1, stage.radar.y - GLYPH_HEIGHT + 1, 255, 22, 255, TEXT_CENTER, "RADAR");
}

//convert sprite position into radar scale
SDL_FRect calcRadarPos(int x, int y, int w, int h)
{
	float max_width = (float)RADAR_SIZE / (MAP_WIDTH * TILE_SIZE); // *-1;
	float radar_x = x * max_width;
	float max_height = (float)RADAR_SIZE / (MAP_HEIGHT * TILE_SIZE); // *-1;
	float radar_y = y * max_height;
	w = w * max_width;
	h = h * max_height;
	float width = w * .5;
	float height = h * .5;
	SDL_FRect r = { stage.radar.x + radar_x - width, stage.radar.y + radar_y - height, w, h };
	return r;
}

void drawWorld(void)
{
	Entity* e;
	// loop through all entities
	for (e = stage.entityHead.next; e != NULL; e = e->next)
	{
		// if the entity hasn't been collected and is of type Pizza, draw circle
		if (e->health > 0 && e->type == ENTITY_PIZZA) {
			//should be a pizza, could put a type into the entity struc
			SDL_SetRenderDrawColor(app.renderer, 205, 205, 0, 1);
			SDL_FRect drawRect = calcRadarPos(e->x, e->y , 40, 40);			
			DrawCircleF(app.renderer, drawRect);
		}
		// if entity still alive and is of type Platform, draw rectangle
		if (e->health > 0 && e->type == ENTITY_PLATFORM) {			
			SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 1);
			SDL_FRect drawRect = calcRadarPos(e->x, e->y, 124, 34);
			SDL_RenderDrawRectF(app.renderer, &drawRect);
		}
		// if entity still alive and is of type Player, draw rectangle
		if (e->health > 0 && e->type == ENTITY_PLAYER) {
			
			SDL_FRect drawRect = calcRadarPos(e->x, e->y, 52, 48);
			// draw orangish box
			SDL_SetRenderDrawColor(app.renderer, 255, 155, 57, 1);
			SDL_RenderFillRectF(app.renderer, &drawRect);
			//draw green outline
			SDL_SetRenderDrawColor(app.renderer, 5, 255, 5, 1);
			SDL_RenderDrawRectF(app.renderer, &drawRect);
		}
		if (e->health > 0 && e->type == ENTITY_BLOCK) {
			// If we want to draw an outline of the ground we'd need to pass in the map
			SDL_FRect drawRect = calcRadarPos(e->x, e->y, 128, 64);
			SDL_SetRenderDrawColor(app.renderer, 100, 100, 255, 1);
			SDL_RenderDrawRectF(app.renderer, &drawRect);
		}
	}
}
void drawRadar(void)
{	
	drawBackground();
	drawTitle();
	drawWorld();
}

// Found this function online to draw circles
// https://stackoverflow.com/questions/38334081/how-to-draw-circles-arcs-and-vector-graphics-in-sdl
void DrawCircleF(SDL_Renderer* renderer, SDL_FRect circ)
{
	const float diameter = circ.w * 2;

	float x = (circ.w - 1);
	float y = 0;
	float tx = 1;
	float ty = 1;
	float error = (tx - diameter);
	float centreX = circ.x;
	float centreY = circ.y;
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPointF(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPointF(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPointF(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPointF(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPointF(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPointF(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPointF(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPointF(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}