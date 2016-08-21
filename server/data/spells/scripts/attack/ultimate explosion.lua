local combat = createCombatObject()
setCombatParam(combat, COMBAT_PARAM_TYPE, COMBAT_PHYSICALDAMAGE)
setCombatParam(combat, COMBAT_PARAM_EFFECT, CONST_ME_EXPLOSIONAREA)

local area = createCombatArea(AREA_CROSS5X5)
setCombatArea(combat, area)

function onGetFormulaValues(cid, level, maglevel)
	if (((level * 2) + (maglevel * 3)) * 2.3) < 250 then
		min = -250
	else
		min = -((level * 2) + (maglevel * 3)) * 2.3
	end
	if (((level * 2) + (maglevel * 3)) * 3) < 250 then
		max = -250
	else
		max = -((level * 2) + (maglevel * 3)) * 3
	end
	return min, max
end

setCombatCallback(combat, CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

function onCastSpell(cid, var)
	-- check for stairHop delay
	if not getCreatureCondition(cid, CONDITION_PACIFIED) then
		return doCombat(cid, combat, var)
	else
		cid:sendCancelMessage(RETURNVALUE_YOUAREEXHAUSTED)
		cid:getPosition():sendMagicEffect(CONST_ME_POFF)
		return false
	end
end