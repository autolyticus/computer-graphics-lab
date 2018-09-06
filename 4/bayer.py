#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2018 g <g@ABCL>
#
# Distributed under terms of the MIT license.

import itertools


def bayer(height, width):
    if width % 2 != 0:
        width += 1

    blueGen = itertools.cycle("BG")
    redGen = itertools.cycle("GR")

    l = []

    swapArray = [blueGen, redGen]
    index = 0

    for i in range(height):
        newl = list(itertools.islice(swapArray[index], width))
        l.append(newl)
        index = (index + 1) % 2

    return l


def bayerImage(height, width):
    colorDict = {"R": (255, 0, 0),
                 "G": (0, 255, 0),
                 "B": (0, 0, 255),
                 }
    return [[colorDict.get(j) for j in i] for i in bayer(height, width)]


def demosaic(image):
    # def case1():

    newImage = [[(0, 0, 0)] * len(image[0]) for row in range(len(image))]
    # Case 1 (Red pixels) ODD ODD
    for i in range(1, len(image) - 1, 2):
        for j in range(1, len(image[0]) - 1, 2):
            newImage[i][j] = (
                image[i][j][0],
                (image[i-1][j][1] + image[i][j+1][1] +
                 image[i+1][j][1] + image[i][j-1][1]) / 4,
                (image[i-1][j-1][2] + image[i - 1][j+1][2] +
                 image[i+1][j+1][2] + image[i+1][j-1][2]) / 4
            )
    # Case 2 (Blue pixels) EVEN EVEN
    for i in range(2, len(image) - 1, 2):
        for j in range(2, len(image[0]) - 1, 2):
            newImage[i][j] = (
                (image[i-1][j-1][0] + image[i - 1][j+1][0] +
                 image[i+1][j+1][0] + image[i+1][j-1][0]) / 4,
                (image[i-1][j][1] + image[i][j+1][1] +
                 image[i+1][j][1] + image[i][j-1][1]) / 4,
                image[i][j][2],
            )

    # Case 3 (Green) EVEN ODD
    for i in range(1, len(image) - 1, 2):
        for j in range(2, len(image[0]) - 1, 2):
            newImage[i][j] = (
                (image[i][j-1][0] + image[i][j+1][0]) / 2,
                (image[i-1][j-1][1] + image[i - 1][j+1][1] +
                 image[i+1][j+1][1] + image[i+1][j-1][1] + image[i][j][1]) / 5,
                (image[i-1][j][2] + image[i + 1][j][2]) / 2,
            )

    # Case 4 (Green) ODD EVEN
    for i in range(2, len(image) - 1, 2):
        for j in range(1, len(image[0]) - 1, 2):
            newImage[i][j] = (
                (image[i-1][j][0] + image[i + 1][j][0]) / 2,
                (image[i-1][j-1][1] + image[i - 1][j+1][1] +
                 image[i+1][j+1][1] + image[i+1][j-1][1] + image[i][j][1]) / 5,
                (image[i][j-1][2] + image[i][j+1][2]) / 2,
            )

    return newImage
