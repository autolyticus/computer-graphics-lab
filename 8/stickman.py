#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 g <g@ABCL>
#
# Distributed under terms of the MIT license.

import pygame
import numpy as np
from time import sleep

deg2rad = np.deg2rad


class stickMan(object):
    def __init__(s, screen, position=(0, 0), size=1, color=(255, 255, 255)):
        s.surface = screen
        s.center = position
        s.color = color
        s.spineLen = 30 * size
        s.neckLen = 5 * size
        s.legLen = 40 * size
        s.uArmLen = 13 * size
        s.lArmLen = 17 * size
        headCenter = (s.center[0], s.center[1] - s.spineLen)
        s.headRect = pygame.Rect((0, 0, 10, 10))
        s.headRect.size = (10 * size, 12 * size)
        s.headRect.center = headCenter
        s.lArmAngles = (0, 0)
        s.rArmAngles = (180, 180)
        s.rLegAngle = 105
        s.lLegAngle = 75

    def dance(s):
        phase = 0
        noPhases = 4
        while True:
            if phase == 0:
                if s.lArmAngles[0] > -20:
                    s.lArmAngles = (s.lArmAngles[0] - 1, s.lArmAngles[1] + 1)
                    if s.lArmAngles[0] % 3 == 0:
                        s.headRect.bottom -= 1
                        s.center = (s.center[0], s.center[1] + 1)
                else:
                    phase = (phase + 1) % noPhases
            elif phase == 1:
                if s.lArmAngles[0] < 0:
                    s.lArmAngles = (s.lArmAngles[0] + 1, s.lArmAngles[1] - 1)
                    if s.lArmAngles[0] % 3 == 0:
                        s.headRect.bottom += 1
                        s.center = (s.center[0], s.center[1] - 1)
                else:
                    phase = (phase + 1) % noPhases
            elif phase == 2:
                if s.rArmAngles[0] < 200:
                    s.rArmAngles = (s.rArmAngles[0] + 1, s.rArmAngles[1] - 1)
                    # s.lLegAngle += 1
                    # s.rLegAngle -= 1
                else:
                    phase = (phase + 1) % noPhases
            elif phase == 3:
                if s.rArmAngles[0] > 180:
                    s.rArmAngles = (s.rArmAngles[0] - 1, s.rArmAngles[1] + 1)
                    # s.lLegAngle -= 1
                    # s.rLegAngle += 1
                else:
                    phase = (phase + 1) % noPhases
            yield

    def draw(s):
        surf = s.surface
        col = s.color
        draw = pygame.draw
        # Spine
        draw.line(surf, col, s.center, s.headRect.center, 2)
        # Head
        draw.ellipse(surf, (0, 0, 0), s.headRect)
        draw.ellipse(surf, col, s.headRect, 2)
        # Left arm
        upperArmEnd = s.drawAngle(
            (s.headRect.midbottom[0], s.headRect.midbottom[1]), s.lArmAngles[0], s.uArmLen)
        s.drawAngle(upperArmEnd, s.lArmAngles[1], s.lArmLen)
        # Right arm
        upperArmEnd = s.drawAngle(
            (s.headRect.midbottom[0], s.headRect.midbottom[1]), s.rArmAngles[0], s.uArmLen)
        s.drawAngle(upperArmEnd, s.rArmAngles[1], s.lArmLen)
        # Left leg
        s.drawAngle(s.center, s.lLegAngle, s.legLen)
        # Right leg
        s.drawAngle(s.center, s.rLegAngle, s.legLen)

    def drawAngle(s, point, angle, l, width=2):
        surf = s.surface
        col = s.color
        draw = pygame.draw
        startx = point[0]
        starty = point[1]
        endx = startx + l * np.cos(deg2rad(angle))
        endy = starty + l * np.sin(deg2rad(angle))
        draw.line(surf, col, (startx, starty), (endx, endy), width)
        return (endx, endy)
