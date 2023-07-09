local condition = createConditionObject(CONDITION_ATTRIBUTES)
setConditionParam(condition, CONDITION_PARAM_TICKS, 40000) -- Tempo que ira durar
setConditionParam(condition, CONDITION_PARAM_SKILL_MELEE, 40) -- Quanto de axe,sword,club ira adionar
setConditionParam(condition, CONDITION_PARAM_SKILL_SHIELD, 40) -- Quanto de shield ira adicionar
setConditionParam(condition, CONDITION_PARAM_STAT_MAGICLEVEL, 40) -- Quanto de magic level ira adicionar
setConditionParam(condition, CONDITION_PARAM_SKILL_DISTANCE, 40) -- Quanto de distancia ira adicionar
setConditionParam(condition, CONDITION_PARAM_HEALTHGAIN, 500)
setConditionParam(condition, CONDITION_PARAM_HEALTHTICKS, 1000)
setConditionParam(condition, CONDITION_PARAM_MANAGAIN, 500)
setConditionParam(condition, CONDITION_PARAM_MANATICKS, 1000)

function onUse(cid, item)

local f = {
"Iahahhh",
"CrockCrockCrock",
}        

    if getPlayerGroupId(cid) >= 3 then
              doSendMagicEffect(getPlayerPosition(cid), 2)
              doSendAnimatedText(getPlayerPosition(cid), "Nao posso usar agora..", math.random(1,255))
              return doPlayerSendTextMessage(cid, 22, "Nao posso usar agora..!")
    end

    if(doAddCondition(cid, condition)) then
              doRemoveItem(item.uid, 1)
              doPlayerSay(cid, f[math.random(#f)], TALKTYPE_ORANGE_1)
              doSendMagicEffect(getPlayerPosition(cid), 67)
    end

return TRUE
end 