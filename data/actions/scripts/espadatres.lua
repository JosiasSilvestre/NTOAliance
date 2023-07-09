function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65533
if getPlayerStorageValue(cid,65533) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Kabutowari!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2182, 1)
setPlayerStorageValue(cid,65533, 1)
return true
end

if getPlayerStorageValue(cid,65533) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Kabutowari!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end