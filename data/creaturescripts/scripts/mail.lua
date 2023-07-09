function onReceiveMail(cid, sender, item, openBox)
	if(openBox) then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "Um novo email chegou.")
	end

	return true
end
