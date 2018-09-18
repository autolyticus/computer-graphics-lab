#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 g <g@ABCL>
#
# Distributed under terms of the MIT license.
import pygame
from stickman import stickMan
from time import sleep


pygame.init()
screen = pygame.display.set_mode((700, 350))
done = False
a = True
# sleepTime = 0.05


def handleEvent(event):
    global done, a, sleepTime
    if event.type == pygame.QUIT:
        done = True
    if event.type == pygame.KEYUP:
        if event.key == pygame.K_SPACE:
            a = not a
    if event.type == pygame.MOUSEBUTTONUP:
        if event.button == 1:
            print(event.pos)
        if event.button == 4:
            if sleepTime != 1.0:
                sleepTime += 0.1
        if event.button == 5:
            if sleepTime != 1.0:
                sleepTime += 0.1


stick = stickMan(screen, position=(150, 150), size=3)
dancer = iter(stick.dance())
# clock = pygame.time.Clock()
while not done:
    for event in pygame.event.get():
        handleEvent(event)

    screen.fill((0, 0, 0))
    # __import__('pdb').set_trace()
    stick.draw()
    sleep(0.01)
    next(dancer)
    # rect.width -= 1
    pygame.display.flip()
pygame.quit()
