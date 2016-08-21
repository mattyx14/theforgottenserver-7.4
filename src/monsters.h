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

#ifndef FS_MONSTERS_H_776E8327BCE2450EB7C4A260785E6C0D
#define FS_MONSTERS_H_776E8327BCE2450EB7C4A260785E6C0D

#include "creature.h"


const uint32_t MAX_LOOTCHANCE = 100000;
const uint32_t MAX_STATICWALK = 100;

struct LootBlock {
	uint16_t id;
	uint32_t countmax;
	uint32_t chance;

	//optional
	int32_t subType;
	int32_t actionId;
	std::string text;

	std::vector<LootBlock> childLoot;
	LootBlock() {
		id = 0;
		countmax = 0;
		chance = 0;

		subType = -1;
		actionId = -1;
	}
};

struct summonBlock_t {
	std::string name;
	uint32_t chance;
	uint32_t speed;
	bool force = false;
};

class BaseSpell;
struct spellBlock_t {
	spellBlock_t() = default;
	~spellBlock_t();
	spellBlock_t(const spellBlock_t& other) = delete;
	spellBlock_t& operator=(const spellBlock_t& other) = delete;
	spellBlock_t(spellBlock_t&& other):
		spell(other.spell),
		chance(other.chance),
		speed(other.speed),
		range(other.range),
		minCombatValue(other.minCombatValue),
		maxCombatValue(other.maxCombatValue),
		combatSpell(other.combatSpell),
		isMelee(other.isMelee) {
		other.spell = nullptr;
	}

	BaseSpell* spell = nullptr;
	uint32_t chance = 100;
	uint32_t speed = 2000;
	uint32_t range = 0;
	int32_t minCombatValue = 0;
	int32_t maxCombatValue = 0;
	bool combatSpell = false;
	bool isMelee = false;
};

struct voiceBlock_t {
	std::string text;
	bool yellText;
};

class MonsterType
{
	public:
		MonsterType();
		~MonsterType() = default;

		// non-copyable
		MonsterType(const MonsterType&) = delete;
		MonsterType& operator=(const MonsterType&) = delete;

		void reset();

		std::map<CombatType_t, int32_t> elementMap;

		std::vector<voiceBlock_t> voiceVector;

		std::vector<LootBlock> lootItems;
		std::vector<std::string> scripts;
		std::vector<spellBlock_t> attackSpells;
		std::vector<spellBlock_t> defenseSpells;
		std::vector<summonBlock_t> summons;

		std::string name;
		std::string nameDescription;

		LuaScriptInterface* scriptInterface;

		uint64_t experience;

		Outfit_t outfit;

		uint32_t manaCost;
		uint32_t yellChance;
		uint32_t yellSpeedTicks;
		uint32_t staticAttackChance;
		uint32_t maxSummons;
		uint32_t changeTargetSpeed;
		uint32_t conditionImmunities;
		uint32_t damageImmunities;
		uint32_t baseSpeed;

		int32_t creatureAppearEvent;
		int32_t creatureDisappearEvent;
		int32_t creatureMoveEvent;
		int32_t creatureSayEvent;
		int32_t thinkEvent;
		int32_t targetDistance;
		int32_t runAwayHealth;
		int32_t health;
		int32_t healthMax;
		int32_t changeTargetChance;
		int32_t defense;
		int32_t armor;

		RaceType_t race;

		uint16_t lookcorpse;

		Skulls_t skull;
		uint8_t lightLevel;
		uint8_t lightColor;

		bool canPushItems;
		bool canPushCreatures;
		bool pushable;
		bool isSummonable;
		bool isIllusionable;
		bool isConvinceable;
		bool isAttackable;
		bool isHostile;
		bool hiddenHealth;

		void createLoot(Container* corpse);
		bool createLootContainer(Container* parent, const LootBlock& lootblock);
		std::vector<Item*> createLootItem(const LootBlock& lootBlock);
};

class Monsters
{
	public:
		Monsters();
		~Monsters() = default;
		// non-copyable
		Monsters(const Monsters&) = delete;
		Monsters& operator=(const Monsters&) = delete;

		bool loadFromXml(bool reloading = false);
		bool isLoaded() const {
			return loaded;
		}
		bool reload();

		MonsterType* getMonsterType(const std::string& name);
		uint32_t getIdByName(const std::string& name);

		static uint32_t getLootRandom();

	private:
		ConditionDamage* getDamageCondition(ConditionType_t conditionType,
		                                    int32_t maxDamage, int32_t minDamage, int32_t startDamage, uint32_t tickInterval);
		bool deserializeSpell(const pugi::xml_node& node, spellBlock_t& sb, const std::string& description = "");

		bool loadMonster(const std::string& file, const std::string& monsterName, std::list<std::pair<MonsterType*, std::string>>& monsterScriptList, bool reloading = false);

		void loadLootContainer(const pugi::xml_node& node, LootBlock&);
		bool loadLootItem(const pugi::xml_node& node, LootBlock&);

		std::map<std::string, MonsterType> monsters;
		std::unique_ptr<LuaScriptInterface> scriptInterface;

		bool loaded;
};

#endif
