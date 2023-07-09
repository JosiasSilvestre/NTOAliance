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
	{id = 11659, price = 10}, -- hinata skin coelhinha
	{id = 11660, price = 10}, -- sasuke skin vegeta
	{id = 11661, price = 10}, -- sakura skin exercito
	{id = 11662, price = 10}, -- naruto skin goku
	{id = 11666, price = 10}, -- lee skin lee sin
	{id = 11667, price = 10}, -- lee skin bruce lee
	{id = 11669, price = 10}, -- naruto skin ichigo
	{id = 11674, price = 10}, -- zetsu skin marshmallow
	{id = 11675, price = 10}, -- shikamaru skin kaneki
	{id = 11657, price = 15}, -- haku skin toshiro
	{id = 11665, price = 15}, -- raikage skin shinigami
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