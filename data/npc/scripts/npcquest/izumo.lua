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
if(msgcontains(msg, 'ajudar')) then
selfSay('Ouvi falar que alguns White Renagade estao se agrupando em Ice Island, eles possuem alguns "pergaminhos" da Vila Oculta da Nevoa, preciso que me traga 12.', cid)
end
---------------------------------------------------------
if(msgcontains(msg, 'pergaminhos')) then
selfSay('Voce ja tem os 12 pergaminhos para me "conseguir"?', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'conseguir') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,325) > 0) then
selfSay('Voce ja terminou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 2218, 12) == TRUE) then
setPlayerStorageValue(cid,325,1)
doPlayerAddExperience(cid,5000)
doPlayerAddItem(cid,5091,1)
selfSay('Obrigado Shinobi! Como recompensa pegue o Mapa Secreto ele lhe dara informacoes sobre um valioso tesouro da Vila Oculta da Nevoa... (Voce recebeu 5000 pontos de experiencia)', cid)
else
selfSay('Voce ainda nao conseguiu o que preciso, estou esperando amigo.', cid)
end
end
return true
end
 
 
end
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())