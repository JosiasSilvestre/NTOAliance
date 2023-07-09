function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 65532
if getPlayerStorageValue(cid,65532) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Hiramekarei!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2474, 1)
setPlayerStorageValue(cid,65532, 1)
return true
end

if getPlayerStorageValue(cid,65532) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Hiramekarei!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end