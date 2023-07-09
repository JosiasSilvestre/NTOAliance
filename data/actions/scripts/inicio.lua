function onUse(cid, item, frompos, item2, topos)


if item.uid == 50001 then
if getPlayerStorageValue(cid,50001) == -1 then
doPlayerSendTextMessage(cid,25,"Bem vindo ao NTOAliance !.")
doPlayerAddItem(cid,2534,1)
setPlayerStorageValue(cid,50001,1)
else
doPlayerSendTextMessage(cid,25,"Esta Vazio.")
end

end
return TRUE
end