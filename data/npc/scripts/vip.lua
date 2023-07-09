---- NPC Trader Loja Vip ----

local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local talkState = {}


function onCreatureAppear(cid)                npcHandler:onCreatureAppear(cid)            end
function onCreatureDisappear(cid)            npcHandler:onCreatureDisappear(cid)            end
function onCreatureSay(cid, type, msg)            npcHandler:onCreatureSay(cid, type, msg)        end
function onThink()                    npcHandler:onThink()                    end
    
--- configure aqui
local str = ""
local coin = 9020 --ID Do Item Que é Usado Como Moeda
    
local buyable_items = { -- ID Dos Itens e Seus Preços  
    {id = 8981, price = 30}, -- Hagoromo Vocation
	{id = 11408, price = 30}, -- Kaguya Vocation
	{id = 11409, price = 30}, -- Mizukage Vocation
	{id = 11410, price = 30}, -- Hashirama Vocation
	{id = 11411, price = 30}, -- Indra Vocation
	{id = 11412, price = 30}, -- Ashura Vocation
	{id = 11416, price = 15}, -- 30 dias premium
}


for u, offers in pairs(buyable_items) do
    
    function buyingit(cid, message, keywords, parameters, node)
        if(not npcHandler:isFocused(cid)) then
            return false
        end


        if getPlayerItemCount(cid,coin) >= offers.price then
            if doPlayerRemoveItem(cid,coin,offers.price) then
                npcHandler:say('Foi um prazer fazer negocios com voce.', cid)
                doPlayerAddItem(cid,offers.id,1)
            end
        else
            npcHandler:say('Voce nao tem ' .. getItemNameById(coin) .. ' o suficiente!', cid)
        end
    end
        
    for i = 1, (#buyable_items - 1) do
        local name = getItemNameById(buyable_items[i].id)
        str = str .. name .. ', '
    end
    str = str .. getItemNameById(buyable_items[#buyable_items].id)
        
    local item_name = getItemNameById(offers.id)        
    
    keywordHandler:addKeyword({'trade'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = "Eu troco {" .. str .. "} por apenas alguns " .. getItemNameById(coin) .. "."})
    local node1 = keywordHandler:addKeyword({''.. item_name .. ''}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Voce deseja trocar ' .. item_name .. ' por ' .. offers.price .. ' ' .. getItemNameById(coin) .. '?'})
    node1:addChildKeyword({'yes'}, buyingit, {npcHandler = npcHandler, onlyFocus = true, reset = true})
    node1:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Ok, volte quando estiver pronto para negociar!', reset = true})
end
npcHandler:addModule(FocusModule:new())