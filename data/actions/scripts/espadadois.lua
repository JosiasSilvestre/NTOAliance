function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65534
if getPlayerStorageValue(cid,65534) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Shibuki!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2190, 1)
setPlayerStorageValue(cid,65534, 1)
return true
end

if getPlayerStorageValue(cid,65534) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Shibuki!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end