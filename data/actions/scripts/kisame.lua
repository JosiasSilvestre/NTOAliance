function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 12306
if getPlayerStorageValue(cid,12306) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber um Water Crystal!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 8300, 1)
setPlayerStorageValue(cid,12306, 1)
return true
end

if getPlayerStorageValue(cid,12306) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Water Crystal!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end