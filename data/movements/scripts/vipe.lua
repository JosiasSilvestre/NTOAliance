-- Vip System by Zero
function onStepIn(cid, item, position, fromPosition)

 

local config = {

msgDenied = "Voce nao e vip, compre no npc Mayron no predio da Hokage.",

msgWelcome = "Seja Bem Vindo a Area vip."

}

 

if getPlayerPremiumDays(cid) <= 0 then

doTeleportThing(cid, fromPosition, true)

doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, config.msgDenied)

doSendMagicEffect(getThingPos(cid), CONST_ME_MAGIC_BLUE)

return true

end

doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, config.msgWelcome)

return true

end