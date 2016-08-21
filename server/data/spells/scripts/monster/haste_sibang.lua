local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_GREEN)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, 0)

local condition = Condition(CONDITION_HASTE)
condition:setParameter(CONDITION_PARAM_TICKS, 3*1000)
condition:setFormula(0, 140, 0, 160)
combat:setCondition(condition)

function onCastSpell(creature, var)
	return combat:execute(creature, var)
end
