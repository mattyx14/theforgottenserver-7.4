local combat = createCombatObject()
setCombatParam(combat, COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_BLUE)

local area = createCombatArea(AREA_CIRCLE3X3)
setCombatArea(combat, area)

function onTargetCorpse(cid, pos)
	local getPos = pos
	getPos.stackpos = 255
	corpse = getThingfromPos(getPos)
	if(corpse.uid > 0 and isCreature(corpse.uid) == FALSE and isInArray(CORPSES, corpse.itemid) ) then
		doRemoveItem(corpse.uid)
		local monster = Game.createMonster("Skeleton", pos)
		monster:setMaster(cid)
	end
end
setCombatCallback(combat, CALLBACK_PARAM_TARGETTILE, "onTargetCorpse")

function onCastSpell(cid, var)
	return doCombat(cid, combat, var)
end