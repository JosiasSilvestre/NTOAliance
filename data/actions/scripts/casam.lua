function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 23042
if getPlayerItemCount(cid,2091) == 0 then
doPlayerSendTextMessage(cid,25,"Voce precisa de uma golden key na backpack!")
doSendMagicEffect(getCreaturePosition(cid),2)
return true
end

if getPlayerStorageValue(cid,23042) then
doSendMagicEffect(getCreaturePosition(cid),12)
doTeleportThing(cid,{x=1320, y=551, z=7})
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerSendTextMessage(cid,25,"Voce achou a passagem secreta!")
doPlayerRemoveItem(cid,2091,1)
return true
end

end