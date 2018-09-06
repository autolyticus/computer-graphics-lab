#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 g <g@ABCL>
#
# Distributed under terms of the MIT license.
import pygame
from bayer import bayer, bayerImage, demosaic
from random import randint


def displayImage(image, widthPixel=1, heightPixel=1):
    for i in range(len(image)):
        for j in range(len(image[0])):
            pygame.draw.rect(
                screen,
                image[i][j],
                [i * heightPixel, j * widthPixel, heightPixel, widthPixel]
            )


def getRandomShade(color):
    if color == "R":
        return (randint(0, 255), 0, 0)
    elif color == "G":
        return (0, randint(0, 255), 0)
    elif color == "B":
        return (0, 0, randint(0, 255))


def makeRandomMosaicedImage(height, width):
    bFilter = bayer(height, width)
    return [[getRandomShade(bFilter[i][j]) for j in range(width)] for i in range(height)]


def printImage(fileName, image):
    with open(fileName, "w") as f:
        for i in range(len(image)):
            for j in range(len(image[0])):
                f.write(str(image[i][j]))
                f.write('\n')


pygame.init()
screen = pygame.display.set_mode((0, 0))
done = False
pixSize = 1
current = 0
bImage = bayerImage(70, 40)
printImage("bayerFilter.txt", bImage)
dembImage = demosaic(bImage)
mosaicImage = makeRandomMosaicedImage(70, 40)
printImage("mosaicImage.txt", mosaicImage)
demosaiced = demosaic(mosaicImage)


def drawFrame():
    imageToDisplay = [
        bImage,
        dembImage,
        mosaicImage,
        demosaiced,
    ]
    displayImage(imageToDisplay[current], pixSize, pixSize)


def handleEvent(event):
    global done, pixSize, current
    if event.type == pygame.QUIT:
        done = True
    if event.type == pygame.KEYUP:
        if event.key == pygame.K_q:
            done = True
    if event.type == pygame.MOUSEBUTTONUP:
        if event.button == 1:
            if current != 3:
                current += 1
        if event.button == 3:
            if current != 0:
                current -= 1
        if event.button == 4:
            pixSize += 1
        if event.button == 5:
            pixSize -= 1


clock = pygame.time.Clock()
while not done:
    clock.tick(60)
    for event in pygame.event.get():
        handleEvent(event)

    screen.fill((0, 0, 0))
    drawFrame()
    pygame.display.flip()
pygame.quit()
