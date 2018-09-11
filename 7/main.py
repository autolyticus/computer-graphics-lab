#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 g <g@ABCL>
#
# Distributed under terms of the MIT license.
import pygame
from time import sleep
from element import elements


pygame.init()
screen = pygame.display.set_mode((700, 350))
done = False
a = True
sleepTime = 0.4


def drawElement(ele):
    e = elements.get(ele)
    pygame.draw.polygon(screen, e.color, e.vertList, 0)


def drawFrame():
    for e in elements:
        drawElement(e)
        sleep(sleepTime)
        pygame.display.flip()
    sleep(sleepTime)
    font = pygame.font.SysFont('Source Sans', 17, True, False)
    text = font.render(
        "INDIAN INSTITUTE OF INFORMATION TECHNOLOGY, DESIGN AND MANUFACTURING ", True, (0, 0, 0))
    text = pygame.transform.rotate(text, 1.5)
    screen.blit(text, [44, 102])
    pygame.display.flip()


def handleEvent(event):
    global done, a, sleepTime
    if event.type == pygame.QUIT:
        done = True
    if event.type == pygame.KEYUP:
        if event.key == pygame.K_SPACE:
            a = not a
    if event.type == pygame.MOUSEBUTTONUP:
        if event.button == 4:
            if sleepTime != 1.0:
                sleepTime += 0.1
        if event.button == 5:
            if sleepTime != 1.0:
                sleepTime += 0.1


clock = pygame.time.Clock()
while not done:
    for event in pygame.event.get():
        handleEvent(event)

    screen.fill((0, 0, 0))
    # __import__('pdb').set_trace()
    # pygame.display.flip()
    if a:
        drawFrame()
pygame.quit()
