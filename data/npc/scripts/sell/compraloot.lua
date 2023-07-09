local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

function onCreatureAppear(cid)			npcHandler:onCreatureAppear(cid)			end
function onCreatureDisappear(cid)		npcHandler:onCreatureDisappear(cid)			end
function onCreatureSay(cid, type, msg)	npcHandler:onCreatureSay(cid, type, msg)	end
function onThink()						npcHandler:onThink()						end

local shopModule = ShopModule:new()
npcHandler:addModule(shopModule)

shopModule:addSellableItem({'orochimaru tunic'}, 2534, 20000, 'orochimaru tunic')
shopModule:addSellableItem({'leaft jounin protector'}, 7427, 15000, 'leaft jounin protector')
shopModule:addSellableItem({'speed boots'}, 2525, 5000, 'speed boots')
shopModule:addSellableItem({'chakra boots'}, 7417, 10000, 'chakra boots')
shopModule:addSellableItem({'akatsuki boots'}, 2529, 10000, 'akatsuki boots')
shopModule:addBuyableItem({'dual slayer'}, 7867, 5000, 'dual slayer')
shopModule:addBuyableItem({'gaara legs'}, 7457, 2500, 'gaara legs')
shopModule:addBuyableItem({'chunin legs'}, 8851, 1500, 'chunin legs')
shopModule:addBuyableItem({'elite kunai'}, 2416, 500, 'elite kunai')
shopModule:addBuyableItem({'taijutsu glove'}, 2380, 500, 'taijutsu glove')
shopModule:addBuyableItem({'katana imperium'}, 2376, 7500, 'katana imperium')
shopModule:addBuyableItem({'sound glove'}, 2435, 10000, 'sound glove')
shopModule:addBuyableItem({'chakra armor'}, 2397, 2500, 'chakra armor')
shopModule:addBuyableItem({'jounin armor'}, 2400, 12500, 'jounin armor')
shopModule:addBuyableItem({'kankuru hat'}, 7438, 1000, 'kankuro hat')

-------BUYABLE
shopModule:addBuyableItem({'orochimaru tunic'}, 2534, 40000, 'orochimaru tunic')
shopModule:addBuyableItem({'leaft jounin protector'}, 7427, 30000, 'leaft jounin protector')
shopModule:addBuyableItem({'speed boots'}, 2525, 10000, 'speed boots')
shopModule:addBuyableItem({'chakra boots'}, 7417, 20000, 'chakra boots')
shopModule:addBuyableItem({'akatsuki boots'}, 2529, 20000, 'akatsuki boots')
shopModule:addBuyableItem({'dual slayer'}, 7867, 10000, 'dual slayer')
shopModule:addBuyableItem({'gaara legs'}, 7457, 5000, 'gaara legs')
shopModule:addBuyableItem({'chunin legs'}, 8851, 3000, 'chunin legs')
shopModule:addBuyableItem({'elite kunai'}, 2416, 1000, 'elite kunai')
shopModule:addBuyableItem({'taijutsu glove'}, 2380, 1000, 'taijutsu glove')
shopModule:addBuyableItem({'katana imperium'}, 2376, 15000, 'katana imperium')
shopModule:addBuyableItem({'sound glove'}, 2435, 20000, 'sound glove')
shopModule:addBuyableItem({'chakra armor'}, 2397, 5000, 'chakra armor')
shopModule:addBuyableItem({'jounin armor'}, 2400, 25000, 'jounin armor')
shopModule:addBuyableItem({'kankuru hat'}, 7438, 2000, 'kankuro hat')


npcHandler:addModule(FocusModule:new())