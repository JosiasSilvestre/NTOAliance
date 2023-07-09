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
if(msgcontains(msg, 'missao')) then
selfSay('O GamaBunta e o guardiao do Pergaminho Sannin, para completar seu treinamento e ganhar o Manto Sannin voce precisa me "entregar" 100 deles.', cid)
end
---------------------------------------------------------
if(msgcontains(msg, 'entregar')) then
selfSay('Voce ja tem os 100 Pergaminhos Sannin para me "conseguir"?', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'conseguir') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,325) > 0) then
selfSay('Voce ja terminou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 2688, 100) == TRUE) then
setPlayerStorageValue(cid,325,1)
doPlayerAddExperience(cid,5000)
doPlayerAddItem(cid,11501,1)
doPlayerAddItem(cid,11502,1)
doPlayerAddItem(cid,11503,1)
doPlayerAddItem(cid,11504,1)
selfSay('Parabens! Voce acaba de receber o Manto Sannin, faca bom uso das forcas da natureza... (Voce recebeu 5000 pontos de experiencia)', cid)
else
selfSay('Voce ainda nao conseguiu o que preciso, volte ao treinamento.', cid)
end
end
return true
end
 
 
end
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())