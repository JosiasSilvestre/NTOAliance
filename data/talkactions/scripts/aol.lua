function onSay(cid, words, param)
        if doPlayerRemoveMoney(cid, 50000) == TRUE then
doPlayerAddItem(cid, 2138, 1)
                        doSendMagicEffect(getPlayerPosition(cid), 5)
doPlayerSendTextMessage(cid,MESSAGE_INFO_DESCR,'Aol!') 
else
            doPlayerSendCancel(cid, "Voce precisa de 5 gold bars para comprar um amuleto!")
                end
return TRUE
                end
