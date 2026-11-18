import random
import pygame

PERGUNTAS = [
    ("O Sol é uma estrela.", True),
    ("A Great Wall da China é visível a olho nu da Lua.", False),
    ("Python é uma linguagem de programação.", True),
    ("O Brasil tem 30 estados.", False),
    ("A água ferve a 100 °C ao nível do mar.", True),
    ("Os morcegos são aves.", False),
    ("O Sol nasce no leste.", True),
    ("Um ano bissexto tem 365 dias.", False),
    ("O corpo humano adulto tem 206 ossos.", True),
    ("A capital do Brasil é o Rio de Janeiro.", False),
]

LARGURA, ALTURA = 800, 500
TEMPO_FEEDBACK = 1200  # milissegundos

# Cores
FUNDO = (25, 25, 50)
BRANCO = (240, 240, 240)
VERDE = (60, 170, 90)
VERMELHO = (200, 70, 70)
CINZA = (120, 120, 150)


def quebrar_texto(texto, fonte, largura_max):
    """Divide o texto em linhas que cabem na largura máxima."""
    linhas, atual = [], ""
    for palavra in texto.split():
        teste = f"{atual} {palavra}".strip()
        if fonte.size(teste)[0] <= largura_max:
            atual = teste
        else:
            linhas.append(atual)
            atual = palavra
    if atual:
        linhas.append(atual)
    return linhas


def desenhar_centro(tela, texto, fonte, cor, y):
    img = fonte.render(texto, True, cor)
    tela.blit(img, img.get_rect(center=(LARGURA // 2, y)))


def desenhar_botao(tela, rect, texto, cor, fonte):
    pygame.draw.rect(tela, cor, rect, border_radius=12)
    img = fonte.render(texto, True, BRANCO)
    tela.blit(img, img.get_rect(center=rect.center))


def main():
    pygame.init()
    tela = pygame.display.set_mode((LARGURA, ALTURA))
    pygame.display.set_caption("Quiz: Verdadeiro ou Falso")
    relogio = pygame.time.Clock()

    fonte_pergunta = pygame.font.SysFont("arial", 30)
    fonte_botao = pygame.font.SysFont("arial", 34, bold=True)
    fonte_info = pygame.font.SysFont("arial", 22)
    fonte_titulo = pygame.font.SysFont("arial", 48, bold=True)

    btn_v = pygame.Rect(100, 340, 250, 80)
    btn_f = pygame.Rect(450, 340, 250, 80)

    def novo_jogo():
        perguntas = PERGUNTAS[:]
        random.shuffle(perguntas)
        return perguntas

    perguntas = novo_jogo()
    indice = 0
    pontos = 0
    estado = "pergunta"  # "pergunta", "feedback" ou "fim"
    acertou = False
    inicio_feedback = 0

    def responder(resposta):
        nonlocal estado, acertou, pontos, inicio_feedback
        acertou = resposta == perguntas[indice][1]
        if acertou:
            pontos += 1
        estado = "feedback"
        inicio_feedback = pygame.time.get_ticks()

    rodando = True
    while rodando:
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                rodando = False

            elif estado == "pergunta":
                if evento.type == pygame.KEYDOWN:
                    if evento.key in (pygame.K_v, pygame.K_LEFT):
                        responder(True)
                    elif evento.key in (pygame.K_f, pygame.K_RIGHT):
                        responder(False)
                elif evento.type == pygame.MOUSEBUTTONDOWN and evento.button == 1:
                    if btn_v.collidepoint(evento.pos):
                        responder(True)
                    elif btn_f.collidepoint(evento.pos):
                        responder(False)

            elif estado == "fim":
                if evento.type == pygame.KEYDOWN and evento.key == pygame.K_r:
                    perguntas = novo_jogo()
                    indice, pontos, estado = 0, 0, "pergunta"

        # Avança sozinho depois do feedback
        if estado == "feedback":
            if pygame.time.get_ticks() - inicio_feedback >= TEMPO_FEEDBACK:
                indice += 1
                estado = "fim" if indice >= len(perguntas) else "pergunta"

        # ---------- Desenho ----------
        tela.fill(FUNDO)

        if estado in ("pergunta", "feedback"):
            desenhar_centro(
                tela, f"Pergunta {indice + 1}/{len(perguntas)}   |   Pontos: {pontos}",
                fonte_info, CINZA, 30,
            )
            linhas = quebrar_texto(perguntas[indice][0], fonte_pergunta, LARGURA - 120)
            y = 130
            for linha in linhas:
                desenhar_centro(tela, linha, fonte_pergunta, BRANCO, y)
                y += 40

            desenhar_botao(tela, btn_v, "VERDADEIRO (V)", VERDE, fonte_botao)
            desenhar_botao(tela, btn_f, "FALSO (F)", VERMELHO, fonte_botao)

            if estado == "feedback":
                if acertou:
                    desenhar_centro(tela, "Acertou!", fonte_titulo, VERDE, 270)
                else:
                    desenhar_centro(tela, "Errou!", fonte_titulo, VERMELHO, 270)

        else:  # fim
            desenhar_centro(tela, "Fim de jogo!", fonte_titulo, BRANCO, 160)
            desenhar_centro(
                tela, f"Você acertou {pontos} de {len(perguntas)}",
                fonte_pergunta, BRANCO, 250,
            )
            desenhar_centro(tela, "Pressione R para jogar de novo", fonte_info, CINZA, 340)

        pygame.display.flip()
        relogio.tick(60)

    pygame.quit()


if __name__ == "__main__":
    main()