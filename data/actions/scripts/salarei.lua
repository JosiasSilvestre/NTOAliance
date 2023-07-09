function onUse(cid, item, fromPosition, itemEX, toPosition)

quest = 19082
if getPlayerStorageValue(cid,19082) == -1 then
doPlayerSendTextMessage(cid,25,"Voce acaba de receber o item do rei!")
doSendMagicEffect(getCreaturePosition(cid),12)
doPlayerAddItem(cid, 2322, 1)
setPlayerStorageValue(cid,19082, 1)
return true
end

if getPlayerStorageValue(cid,19082) == 1 then
doPlayerSendTextMessage(cid,25,"O Rei ja lhe deu esse item!")
doSendMagicEffect(getCreaturePosition(cid),2)
end

end