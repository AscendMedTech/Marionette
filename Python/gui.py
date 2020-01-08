from Comm import Comm
import pygame

width,height = 500, 500
positions = [[width*.25,height*.25],[width*.75,height*.25],[width*.25,height*.75],[width*.75, height*.75]]
pygame.init()
screen = pygame.display.set_mode((width,height))
pygame.display.set_caption('Deflection Results')

font = pygame.font.Font(pygame.font.get_default_font(), 32)

#ser = Comm('COM1', 9600)

done = False

def createText(messages, font):
    texts = []
    for i in range(len(messages)):
        text = font.render(messages[i], True, (50,50,0))
        textRect = text.get_rect()
        textRect.center = (positions[i][0], positions[i][1])
        texts.append([text,textRect])
    return texts

while not done:
    screen.fill((255,255,255))
    texts = createText(['test1', 'test2', 'test3', 'test4'], font)
    for text in texts:
        screen.blit(text[0], text[1])
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            quit()
    pygame.display.flip()
