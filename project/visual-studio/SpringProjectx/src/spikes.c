#include "common.h"

//static void tick(void);
static void touch(Entity* other);

void initSpikes(char* line)
{
	Entity* e; // e is entity, pointer to entity. entity is struct

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));

	stage.entityTail->next = e; //appended to list of entities 
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1; // 1 so gets drawn

	e->flags = EF_WEIGHTLESS;
	e-> touch = touch;
	e->texture = loadTexture("gfx/MCCactus.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);  //width and height based on the image itself


}

static void touch(Entity* other)
{
	if (self->health == 1 &&other == player)
	{ // to stop the hearts from -2 instead of 1
	    self->health =0;
		stage.playerHearts--;

	}
}

void LoseOrWin()
{
	if (stage.playerHearts == 0)
	{
		if (app.keyboard[SDL_SCANCODE_RETURN])
		{
			exit(1);
		}
	}
	
	if (stage.pizzaFound == stage.pizzaTotal)
	{
		if (app.keyboard[SDL_SCANCODE_RETURN])
		{
			exit(1);
		}
	}
}
