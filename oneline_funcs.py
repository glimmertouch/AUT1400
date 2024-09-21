def adjacentElementsProduct(inputArray):
    return max(inputArray[i] * inputArray[i + 1] for i in range(len(inputArray) - 1))

def allLongestStrings(inputArray):
    return list(filter(lambda x: len(x) == max(map(len, inputArray)), inputArray))

def checkPalindrome(inputString):
    return inputString == inputString[::-1]

def commonCharacterCount(s1, s2):
    return sum(min(s1.count(x), s2.count(x)) for x in set(s1))

def areSimilar(a, b):
    return sorted(a) == sorted(b) and sum(i != j for i, j in zip(a, b)) < 3

def palindromeRearranging(inputString):
    return sum(inputString.count(x) % 2 for x in set(inputString)) < 2

def arrayReplace(inputArray, elemToReplace, substitutionElem):
    return [x if x != elemToReplace else substitutionElem for x in inputArray]

def evenDigitsOnly(n):
    return all(int(x) % 2 == 0 for x in str(n))

def alphabeticShift(inputString):
    return ''.join(chr(97 + (ord(x) - 96) % 26) for x in inputString)

def firstDigit(inputString):
    return int(next(filter(str.isdigit, inputString)))