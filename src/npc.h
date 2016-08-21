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

#ifndef FS_NPC_H_B090D0CB549D4435AFA03647195D156F
#define FS_NPC_H_B090D0CB549D4435AFA03647195D156F

#include "creature.h"
#include "luascript.h"

#include <set>

class Npc;
class Player;

class Npcs
{
	public:
		static void reload();
};

class NpcScriptInterface final : public LuaScriptInterface
{
	public:
		NpcScriptInterface();

		bool loadNpcLib(const std::string& file);

	protected:
		void registerFunctions();

		static int luaActionSay(lua_State* L);
		static int luaActionMove(lua_State* L);
		static int luaActionMoveTo(lua_State* L);
		static int luaActionTurn(lua_State* L);
		static int luaActionFollow(lua_State* L);
		static int luagetDistanceTo(lua_State* L);
		static int luaSetNpcFocus(lua_State* L);
		static int luaGetNpcCid(lua_State* L);
		static int luaGetNpcParameter(lua_State* L);
		static int luaDoSellItem(lua_State* L);

		// metatable
		static int luaNpcGetParameter(lua_State* L);
		static int luaNpcSetFocus(lua_State* L);

	private:
		bool initState() final;
		bool closeState() final;

		bool libLoaded;
};

class NpcEventsHandler
{
	public:
		NpcEventsHandler(const std::string& file, Npc* npc);

		void onCreatureAppear(Creature* creature);
		void onCreatureDisappear(Creature* creature);
		void onCreatureMove(Creature* creature, const Position& oldPos, const Position& newPos);
		void onCreatureSay(Creature* creature, SpeakClasses, const std::string& text);
		void onThink();

		bool isLoaded() const;

	protected:
		Npc* npc;
		NpcScriptInterface* scriptInterface;

		int32_t creatureAppearEvent;
		int32_t creatureDisappearEvent;
		int32_t creatureMoveEvent;
		int32_t creatureSayEvent;
		int32_t thinkEvent;
		bool loaded;
};

class Npc final : public Creature
{
	public:
		~Npc();

		// non-copyable
		Npc(const Npc&) = delete;
		Npc& operator=(const Npc&) = delete;

		Npc* getNpc() final {
			return this;
		}
		const Npc* getNpc() const final {
			return this;
		}

		bool isPushable() const final {
			return walkTicks > 0;
		}

		void setID() final {
			if (id == 0) {
				id = npcAutoID++;
			}
		}

		void removeList() final;
		void addList() final;

		static Npc* createNpc(const std::string& name);

		bool canSee(const Position& pos) const final;

		bool load();
		void reload();

		const std::string& getName() const final {
			return name;
		}
		const std::string& getNameDescription() const final {
			return name;
		}

		CreatureType_t getType() const final {
			return CREATURETYPE_NPC;
		}

		void doSay(const std::string& text);
		void doSayToPlayer(Player* player, const std::string& text);

		void doMoveTo(const Position& pos);

		int32_t getMasterRadius() const {
			return masterRadius;
		}
		const Position& getMasterPos() const {
			return masterPos;
		}
		void setMasterPos(Position pos, int32_t radius = 1) {
			masterPos = pos;
			if (masterRadius == -1) {
				masterRadius = radius;
			}
		}

		void turnToCreature(Creature* creature);
		void setCreatureFocus(Creature* creature);

		NpcScriptInterface* getScriptInterface();

		static uint32_t npcAutoID;

	protected:
		explicit Npc(const std::string& name);

		void onCreatureAppear(Creature* creature, bool isLogin) final;
		void onRemoveCreature(Creature* creature, bool isLogout) final;
		void onCreatureMove(Creature* creature, const Tile* newTile, const Position& newPos,
		                            const Tile* oldTile, const Position& oldPos, bool teleport) final;

		void onCreatureSay(Creature* creature, SpeakClasses type, const std::string& text) final;
		void onThink(uint32_t interval) final;
		std::string getDescription(int32_t lookDistance) const final;

		bool isImmune(CombatType_t) const final {
			return !attackable;
		}
		bool isImmune(ConditionType_t) const final {
			return !attackable;
		}
		bool isAttackable() const final {
			return attackable;
		}
		bool getNextStep(Direction& dir, uint32_t& flags) final;

		bool canWalkTo(const Position& fromPos, Direction dir) const;
		bool getRandomStep(Direction& dir) const;

		void reset();
		bool loadFromXml();

		std::map<std::string, std::string> parameters;

		std::string name;
		std::string filename;

		NpcEventsHandler* npcEventHandler;

		Position masterPos;

		uint32_t walkTicks;
		int32_t focusCreature;
		int32_t masterRadius;

		bool floorChange;
		bool attackable;
		bool ignoreHeight;
		bool loaded;

		static NpcScriptInterface* scriptInterface;

		friend class Npcs;
		friend class NpcScriptInterface;
};

#endif
