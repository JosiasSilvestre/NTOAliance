function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65530
if getPlayerStorageValue(cid,65530) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Samehada!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2413, 1)
setPlayerStorageValue(cid,65530, 1)
return true
end

if getPlayerStorageValue(cid,65530) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Samehada!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end