-- Lottery System
local config = {
    lottery_hour = "2 Hours", -- Tempo ate a proxima loteria (Esse tempo vai aparecer somente como broadcast message)
    rewards_id = {7402, 7382, 2160}, -- ID dos Itens Sorteados na Loteria
    crystal_counts = 100, -- Usado somente se a rewards_id for crystal coin (ID: 2160).
    website = "no" -- Only if you have php scripts and table `lottery` in your database!
    }
function onThink(interval, lastExecution)
        if(getWorldCreatures(0) == 0)then
                return true
        end
 
    local list = {}
    for i, tid in ipairs(getPlayersOnline()) do
                list[i] = tid
        end

        local winner = list[math.random(1, #list)]
        local random_item = config.rewards_id[math.random(1, #config.rewards_id)]
        
        if(random_item == 2160) then
                doPlayerAddItem(winner, random_item, config.crystal_counts)
                doBroadcastMessage("[SISTEMA DE LOTERIA] Vencedor: " .. getCreatureName(winner) .. ", Recompensa: " .. config.crystal_counts .. " " .. getItemNameById(random_item) .. "s! Parabens! (Proxima Loteria em " .. config.lottery_hour .. ")")
        else
                doBroadcastMessage("[SISTEMA DE LOTERIA] Vencedor: " .. getCreatureName(winner) .. ", Recompensa: " .. getItemNameById(random_item) .. "! Parabens! (Proxima Loteria em " .. config.lottery_hour .. ")")
                doPlayerAddItem(winner, random_item, 1)
        end
       
        if(config.website == "yes") then
                db.executeQuery("INSERT INTO `lottery` (`name`, `item`) VALUES ('".. getCreatureName(winner) .."', '".. getItemNameById(random_item) .."');")
        end
        return true
end