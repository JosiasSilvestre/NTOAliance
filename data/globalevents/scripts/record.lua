function onRecord(current, old, cid)
	db.executeQuery("INSERT INTO `server_record` (`record`, `world_id`, `timestamp`) VALUES (" .. current .. ", " .. getConfigValue('worldId') .. ", " .. os.time() .. ");")
	addEvent(doBroadcastMessage, 150, "Novo record: " .. current .. " Jogadores estao logados!", MESSAGE_STATUS_DEFAULT)
end
