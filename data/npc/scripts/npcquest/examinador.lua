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
if(msgcontains(msg, 'chunin')) then
selfSay('Hahaha, entao ira fazer o {exame} chunin? Essa e apenas a primeira fase do exame garoto.', cid)
end
---------------------------------------------------------
if(msgcontains(msg, 'exame')) then
selfSay('Tudo bem entao, para {confirmar}, vou pegar todas medalhas que voce possue que provam que voce fez essas missoes, e lembrese, essa e apenas a primeira fase, hahaha!', cid)
talkState[talkUser] = 1
elseif(msgcontains(msg, 'confirmar') and talkState[talkUser] == 1) then
if (getPlayerStorageValue(cid,24301) > 0) then
selfSay('Voce ja terminou essa missao.', cid)
else
if(doPlayerRemoveItem(cid, 10135, 7) == TRUE) then
setPlayerStorageValue(cid,24301,1)
doPlayerAddExperience(cid,1000)
doPlayerAddItem(cid,10135,1)
selfSay('Muito bom garoto, ja pode avancar essa porta, e veja o que o nosso proximo examinador ira lhe pedir!', cid)
else
selfSay('Haha, voce nao pode me passar a perna, voce tem que me trazer os comprovantes que completaste as missoes, volte aqui com eles.', cid)
end
end
return true
end
 
 
end
npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())