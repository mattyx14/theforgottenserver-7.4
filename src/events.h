/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2016  Mark Samman <mark.samman@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef FS_EVENTS_H_BD444CC0EE167E5777E4C90C766B36DC
#define FS_EVENTS_H_BD444CC0EE167E5777E4C90C766B36DC

#include "luascript.h"

class Party;
class ItemType;
class Tile;

class Events
{
	public:
		Events();

		void clear();
		bool load();

		// Creature
		bool eventCreatureOnChangeOutfit(Creature* creature, const Outfit_t& outfit);
		ReturnValue eventCreatureOnAreaCombat(Creature* creature, Tile* tile, bool aggressive);
		ReturnValue eventCreatureOnTargetCombat(Creature* creature, Creature* target);

		// Party
		bool eventPartyOnJoin(Party* party, Player* player);
		bool eventPartyOnLeave(Party* party, Player* player);
		bool eventPartyOnDisband(Party* party);

		// Player
		void eventPlayerOnLook(Player* player, const Position& position, Thing* thing, uint8_t stackpos, int32_t lookDistance);
		void eventPlayerOnLookInBattleList(Player* player, Creature* creature, int32_t lookDistance);
		void eventPlayerOnLookInTrade(Player* player, Player* partner, Item* item, int32_t lookDistance);
		bool eventPlayerOnMoveItem(Player* player, Item* item, uint16_t count, const Position& fromPosition, const Position& toPosition);
		bool eventPlayerOnMoveCreature(Player* player, Creature* creature, const Position& fromPosition, const Position& toPosition);
		bool eventPlayerOnTurn(Player* player, Direction direction);
		bool eventPlayerOnTradeRequest(Player* player, Player* target, Item* item);
		bool eventPlayerOnTradeAccept(Player* player, Player* target, Item* item, Item* targetItem);
		void eventPlayerOnGainExperience(Player* player, Creature* source, uint64_t& exp, uint64_t rawExp);
		void eventPlayerOnLoseExperience(Player* player, uint64_t& exp);
		void eventPlayerOnGainSkillTries(Player* player, skills_t skill, uint64_t& tries);

	private:
		LuaScriptInterface scriptInterface;

		// Creature
		int32_t creatureOnChangeOutfit;
		int32_t creatureOnAreaCombat;
		int32_t creatureOnTargetCombat;

		// Party
		int32_t partyOnJoin;
		int32_t partyOnLeave;
		int32_t partyOnDisband;

		// Player
		int32_t playerOnLook;
		int32_t playerOnLookInBattleList;
		int32_t playerOnLookInTrade;
		int32_t playerOnMoveItem;
		int32_t playerOnMoveCreature;
		int32_t playerOnTurn;
		int32_t playerOnTradeRequest;
		int32_t playerOnTradeAccept;
		int32_t playerOnGainExperience;
		int32_t playerOnLoseExperience;
		int32_t playerOnGainSkillTries;
};

#endif
