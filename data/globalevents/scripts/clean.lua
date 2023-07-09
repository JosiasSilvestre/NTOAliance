function executeClean()
	doCleanMap()
	doBroadcastMessage("O mapa foi limpo, proxima limpeza em 2 horas.")
	return true
end

function onThink(interval, lastExecution, thinkInterval)
	doBroadcastMessage("O mapa vai ser limpo dentro de 30 segundos, por favor pegue seus itens!")
	addEvent(executeClean, 30000)
	return true
end
