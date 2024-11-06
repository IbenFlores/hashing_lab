#Generar N°
import matplotlib
import numpy as np
import matplotlib.pyplot as plt
from random import choice
import random

#creemos una función pseudo-aleatória
def RandomHashFun(M, n=10):
    fnTable = [ None for i in range(M) ]
    for x in range(M):
        fnTable[x] = choice(range(n))
    def randomFn(x):
        return fnTable[x]
    return randomFn


# Initialize the hash function
randomHash = RandomHashFun(5, 10)

# fnTable could look something like [3, 7, 2, 5, 8] (randomly chosen values)

# Calling the function with different inputs
print(randomHash(0))  # Output: 3
print(randomHash(1))  # Output: 7
print(randomHash(2))  # Output: 2
print(randomHash(3))  # Output: 5
print(randomHash(4))  # Output: 8
print(randomHash(0))