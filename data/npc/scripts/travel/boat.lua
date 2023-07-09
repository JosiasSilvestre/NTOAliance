local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

function onCreatureAppear(cid)				npcHandler:onCreatureAppear(cid) end
function onCreatureDisappear(cid) 			npcHandler:onCreatureDisappear(cid) end
function onCreatureSay(cid, type, msg) 	npcHandler:onCreatureSay(cid, type, msg) end
function onThink() 						npcHandler:onThink() end

local travelNode = keywordHandler:addKeyword({'suna'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para a Vila da Areia, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler,  level = 25, cost = 0, destination = {x=564, y=1145, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'kirigakure'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para a Vila da Nevoa, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler,  level = 25, cost = 0, destination = {x=1149, y=1218, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'konoha'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para a Vila da Folha, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 25, cost = 0, destination = {x=1015, y=906, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'amegakure'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Vila da Chuva, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=972, y=1430, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'vale do fim'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Vale do Fim, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=965, y=830, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'monte myoboku'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Monte Myoboku, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=1103, y=1539, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'south florest'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Souty Florest, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=912, y=1179, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'west desert'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para West Desert, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=1496, y=1053, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'south island'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Sounth Island, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=1084, y=1400, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

local travelNode = keywordHandler:addKeyword({'ice island'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Ice Island, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=1997, y=1118, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})
	
local travelNode = keywordHandler:addKeyword({'vilarejo'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce quer ir para Vilarejo, voce tem certeza?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, level = 120, cost = 0, destination = {x=456, y=1326, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Ok, ate a proxima.'})

        keywordHandler:addKeyword({'travel'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Eu posso te levar para Suna, Kirigakure, Konoha, Amegakure, Vale do Fim, Monte Myoboku, South Florest, South Island, West Desert, Vilarejo e Ice Island.'})
        -- Makes sure the npc reacts when you say hi, bye etc.
        npcHandler:addModule(FocusModule:new())
		-- PRA COLOCAR UMA VILA PREMIUM É SO BOTAR ANTES DE LEVEL premium = true,