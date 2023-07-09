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
if(msgcontains(msg, 'pergaminho')) then
selfSay('Muito bem shinobi, esse pergaminho e muito antigo e uma {reliquia} secreta de nossa aldeia.', cid)
end
---------------------------------------------------------
if(msgcontains(msg, 'reliquia')) then
selfSay('Por sua bravura em combate quando me {devolver} esse pergaminho, te darei o titulo de Genin, por esse enorme espirito shinobi que ha dentro de voce.', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'devolver') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,89745) > 0) then
selfSay('Voce ja terminou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 2155, 1) == TRUE) then
setPlayerStorageValue(cid,89745,1)
doPlayerAddExperience(cid,7000)
doPlayerAddItem(cid,10140,1)
selfSay('Muito Bem Genin, de agora em diante tambem tera acesso a lugares que os guardas deixao apenas genin passarem, como recompensa tome esse livro, esta anotado varios jutsus nele...{voce leu o livro}... (Voce recebeu 7000 pontos de experiencia)', cid)
else
selfSay('Ueh.. cade o pergaminho? nao me digas que perdeu? volte e pegue ele...', cid)
end
end
return true
end
 
 
end
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())