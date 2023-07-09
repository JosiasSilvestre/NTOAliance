function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65529
if getPlayerStorageValue(cid,65529) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Kiba!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 7878, 1)
setPlayerStorageValue(cid,65529, 1)
return true
end

if getPlayerStorageValue(cid,65529) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Kiba!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end