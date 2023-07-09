function onThink(interval, lastExecution)
  MENSAGEM = {
    "Acesse a nossa Pagina no Instagram para mais atualizacoes @ntoaliance!",
    "Precisamos de um HOST fixo, para isso ajude fazendo doacoes e ganhando beneficios.",
    "Ajude-nos a crescer, divulgue o: NtoAliance.",
    "Para ter um Bom jogo reporte no discord BUGs encontrados, assim o jogo melhora.",
	"Sempre use scrolls Quest/Vip/Skins em personagens free.",
  }
  doBroadcastMessage(MENSAGEM[math.random(1,#MENSAGEM)],22)
  return TRUE
end