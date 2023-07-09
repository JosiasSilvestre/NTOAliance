function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 56432
if getPlayerStorageValue(cid,56432) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber uma Kage Shuriken!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 11530, 1)
setPlayerStorageValue(cid,56432, 1)
return true
end

if getPlayerStorageValue(cid,56432) == 1 then
doPlayerSendTextMessage(cid,25,"Voce ja recebeu a Kage Shuriken!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end