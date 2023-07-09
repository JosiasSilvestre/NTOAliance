function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 40919
if getPlayerItemCount(cid,8300) == 0 then
doPlayerSendTextMessage(cid,25,"Voce precisa de um Water Crystal na backpack!")
doSendMagicEffect(getCreaturePosition(cid),2)
return true
end

if getPlayerStorageValue(cid,40919) then
doSendMagicEffect(getCreaturePosition(cid),12)
doTeleportThing(cid,{x=1068, y=1218, z=9})
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerSendTextMessage(cid,25,"Voce achou o covil dos espadachins da nevoa!")
doPlayerRemoveItem(cid,8300,1)
return true
end

end