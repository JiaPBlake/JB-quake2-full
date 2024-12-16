/*
Copyright (C) 1997-2001 Id Software, Inc.

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
#include "g_local.h"


/*
==============================================================================

PLAYER TRAIL

==============================================================================

This is a circular list containing the a list of points of where
the player has been recently.  It is used by monsters for pursuit.

.origin		the spot
.owner		forward link
.aiment		backward link
*/


#define	TRAIL_LENGTH	8

edict_t		*trail[TRAIL_LENGTH];	//J NOTE: an array of edict_t pointers.   I'm assuming these are the individual "Trail 'objects'/entities"
int			trail_head;
qboolean	trail_active = false;

#define NEXT(n)		(((n) + 1) & (TRAIL_LENGTH - 1))
#define PREV(n)		(((n) - 1) & (TRAIL_LENGTH - 1))


void PlayerTrail_Init (void)
{
	int		n;

	if (deathmatch->value /* FIXME || coop */)
		return;

	for (n = 0; n < TRAIL_LENGTH; n++)
	{
		trail[n] = G_Spawn();	//J NOTE: fill the array of pointers with Entities. (spawning the entities using G_Spawn() )
		trail[n]->classname = "player_trail"; //J NOTE: Set the classname of the entity we just made to "player_trail"
	}

	trail_head = 0;
	trail_active = true;
}
//J NOTE: By the time the Trail has been initialized,  we have an array of (8) brand new 'player_trail' entities.  And the head =0


void PlayerTrail_Add (vec3_t spot)
{
	vec3_t	temp;

	if (!trail_active) //J NOTE: add to the head of the list
		return;

	VectorCopy (spot, trail[trail_head]->s.origin);	//J NOTE:  HOH   OHOHOH OKKO SO!  we copy the Spot into the Trail ENTITY'S ORIGIN.

	trail[trail_head]->timestamp = level.time;	//J NOTE: with a specific timestamp -- the level's timestamp
								//J NOTE: I think this is -1  AND THE BIT-WISE AND WORKS OUT ALSO!!!! -1 is a string of 1's,  so AND'ed with 7 is 7 !!!
	VectorSubtract (spot, trail[PREV(trail_head)]->s.origin, temp); //J NOTE: SO!! Remove the end of the list!
	trail[trail_head]->s.angles[1] = vectoyaw (temp);

	trail_head = NEXT(trail_head);
}


void PlayerTrail_New (vec3_t spot)
{
	if (!trail_active)
		return;

	PlayerTrail_Init ();
	PlayerTrail_Add (spot);
}


edict_t *PlayerTrail_PickFirst (edict_t *self)
{
	int		marker;
	int		n;

	if (!trail_active)
		return NULL;

	for (marker = trail_head, n = TRAIL_LENGTH; n; n--)
	{									//J NOTE:  the time at which the monster started trailing  ?
		if(trail[marker]->timestamp <= self->monsterinfo.trail_time)	//because all entities (edict_t's) have a monsterinfo member
			marker = NEXT(marker);
		else
			break;
	}
	//finds which piece of the trail the monster should pick up on BASED on the time the monster (self) started trailing
	if (visible(self, trail[marker]))  //if they're visible AT that spot,  return the spot
	{
		return trail[marker];
	}

	if (visible(self, trail[PREV(marker)]))
	{
		return trail[PREV(marker)];
	}
	//but :melting:  if I'm not visible why are you returning the spot anyway!! :(
	return trail[marker];
}

edict_t *PlayerTrail_PickNext (edict_t *self)
{
	int		marker;
	int		n;

	if (!trail_active)
		return NULL;

	for (marker = trail_head, n = TRAIL_LENGTH; n; n--)
	{
		if(trail[marker]->timestamp <= self->monsterinfo.trail_time)
			marker = NEXT(marker);
		else
			break;
	}

	return trail[marker];
}

edict_t *PlayerTrail_LastSpot (void)
{
	return trail[PREV(trail_head)];
}
