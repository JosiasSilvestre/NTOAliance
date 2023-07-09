--- skull remover by kakilo - quinto script

function onSay(cid, words, param, channel)

if (getCreatureSkullType(cid) == SKULL_BLACK) then
if doPlayerRemoveMoney(cid, 20000) then
doCreatureSetSkullType(cid, SKULL_NONE)
doPlayerSendTextMessage(cid, 22, "Sua black skull foi removida.")
else
doPlayerSendTextMessage(cid, 22, "Voce precisa de 20000 gold pieces para remover a black skull")
end
end

if (getCreatureSkullType(cid) == SKULL_RED) then
if doPlayerRemoveMoney(cid, 10000) then
doCreatureSetSkullType(cid, SKULL_NONE)
doPlayerSendTextMessage(cid, 22, "Sua red skull foi removida.")
else
doPlayerSendTextMessage(cid, 22, "Voce precisa de 10000 gold pieces para remover a red skull")
end
end

if (getCreatureSkullType(cid) == SKULL_WHITE) then
if doPlayerRemoveMoney(cid, 1000) then
doCreatureSetSkullType(cid, SKULL_NONE)
doPlayerSendTextMessage(cid, 22, "Your soul was been cleaned.")
else
doPlayerSendTextMessage(cid, 22, "Voce precisa de 1000 gold pieces para remover a white skull")
end
end

if (getCreatureSkullType(cid) == SKULL_NONE) then
doPlayerSendTextMessage(cid, 22, "Sua white skull foi removida!")
end

return TRUE
end
