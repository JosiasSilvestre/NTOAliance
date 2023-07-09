function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65531
if getPlayerStorageValue(cid,65531) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Kubikiribocho!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 7888, 1)
setPlayerStorageValue(cid,65531, 1)
return true
end

if getPlayerStorageValue(cid,65531) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Kubikiribocho!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end