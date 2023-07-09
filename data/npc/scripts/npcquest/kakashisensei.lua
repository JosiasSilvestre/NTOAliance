local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local talkState = {}
function onCreatureAppear(cid) npcHandler:onCreatureAppear(cid) end
function onCreatureDisappear(cid) npcHandler:onCreatureDisappear(cid) end
function onCreatureSay(cid, type, msg) npcHandler:onCreatureSay(cid, type, msg) end
function onThink() npcHandler:onThink() end
function creatureSayCallback(cid, type, msg)
if(not npcHandler:isFocused(cid)) then
return false
end
local talkUser = NPCHANDLER_CONVBEHAVIOR == CONVERSATION_DEFAULT and 0 or cid
if(msgcontains(msg, 'missoes')) then
selfSay('Ok, Para começar vamos fazer a {primeira missao}?', cid)
end
---------------------------------------------------------
if(msgcontains(msg, 'primeira missao')) then
selfSay('Mate uns nekenins e me traga 10 Nukenin {talisma}', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'talisma') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,111) > 0) then
selfSay('Voce ja terminou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 10551, 10) == TRUE) then
setPlayerStorageValue(cid,111,1)
doPlayerAddExperience(cid,1000)
doPlayerAddItem(cid,10136,1)
selfSay('Obrigado! Se quiser ja pode fazer a {segunda missao}.. (ganhou um livro do kakashi de presente e ganhou 1000 de exp por ler)', cid)
else
selfSay('Voce nao tem os 10 nukenins talisma ainda..', cid)
end
end
return true
end
---------------------------------------------------------
if(msgcontains(msg, 'segunda missao')) then
selfSay('Va ate a Florest Renegade, quero que me tragas 25 renegade {essence}', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'essence') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,112) > 0) then
selfSay('Voce ja acabou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 6500, 25) == TRUE) then
setPlayerStorageValue(cid,112,1)
doPlayerAddExperience(cid,1000)
doPlayerAddItem(cid,10136,1)
selfSay('Obrigado! Se quiser ja pode fazer a {terceira missao}.. (ganhou um livro do kakashi de presente e ganhou 1000 de exp por ler)', cid)
else
selfSay('Voce nao tem os 25 renegade essence ainda', cid)
end
end
return true
end
---------------------------------------------------------
if(msgcontains(msg, 'terceira missao')) then
selfSay('Va ate o Local 05 do mapa que fica na Floresta Renegade, la tem um Shinobi de graduação Jounin que roubou 1 saco de {dinheiro} de um aldeao, pegue e traga para mim.', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'dinheiro') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,13608) > 0) then
selfSay('Voce ja terminou essa missao e ainda nao tenho uma quarta missao para lhe dar.', cid)
else
if(doPlayerRemoveItem(cid, 2690, 1) == TRUE) then
setPlayerStorageValue(cid,13608,1)
doPlayerAddExperience(cid,1000)
doPlayerAddItem(cid,10136,1)
selfSay('Obrigado! Voce ja terminou 3 missoes minhas, e agora voce ja e digno de fazer o exame Jounin. (ganhou um livro do kakashi de presente e ganhou 1000 de exp por ler)', cid)
else
selfSay('Voce nao pegou o Saco de Dinheiro ainda', cid)
end
end
return true
end
 
 
end
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())