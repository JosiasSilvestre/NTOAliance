function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65535
if getPlayerStorageValue(cid,65535) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Nuibari!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2188, 1)
setPlayerStorageValue(cid,65535, 1)
return true
end

if getPlayerStorageValue(cid,65535) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Nuibari!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end