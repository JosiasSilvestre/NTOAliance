function onJoinChannel(cid, channelId, users)
	if(channelId == CHANNEL_GUILD) then
		local guildId = getPlayerGuildId(cid)
		if(guildId and guildId ~= 0) then
			local guildMotd = getGuildMotd(guildId)
			if(guildMotd and guildMotd ~= "") then
				addEvent(doPlayerSendChannelMessage, 150, cid, "", "Menssagem do dia: " .. guildMotd, TALKTYPE_CHANNEL_W, CHANNEL_GUILD)
			end
		end
	end

	return true
end
