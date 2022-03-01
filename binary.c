//Copyright by elvirrrk

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<math.h>

char* getString() {
  int len = 1;
  char* returnedString = (char*)malloc(len * sizeof(char));
  returnedString[0] = '\0';

  char inputChar;
  scanf("%c", &inputChar);
  while (inputChar != '\n') {
    returnedString[len - 1] = inputChar;
    len++;
    returnedString = (char*)realloc(returnedString, len * sizeof(char));
    returnedString[len - 1] = '\0';
    scanf("%c", &inputChar);
  }

  return returnedString;
}

int* encodeSymbolToBinary(int symbol) {
  int* result = (int*)malloc(8 * sizeof(int));
  for (int i = 0; i < 8; i++) {
    result[i] = 0;
  }
  int index = 7;

  while (symbol != 1) {
    int binary = symbol % 2;
    result[index] = binary;
    index--;
    symbol = symbol / 2;
  }
  result[index] = 1;

  return result;
}

int* encodeThreeSymbolToBinary(char b1, char b2, char b3) {
  int* a1 = encodeSymbolToBinary(b1);
  int* a2 = encodeSymbolToBinary(b2);
  int* a3 = encodeSymbolToBinary(b3);
  int* result = (int*)malloc(24 * sizeof(int));
  for (int i = 0; i < 8; i++)
    result[i] = a1[i];

  for (int i = 8; i < 16; i++)
    result[i] = a2[i - 8];

  for (int i = 16; i < 24; i++)
    result[i] = a3[i - 16];

  return result;
}

int encodeBinaryToDecimal(int* binary) {
  int result = 0;
  for (int i = 5; i >= 0; i--) {
    result += binary[5 - i] * (int)pow(2, i);
  }
  return result;
}

char* Alphabet() {
  char* result = (char*)malloc(64 * sizeof(char));
  for (int i = 0; i < 26; i++) {
    result[i] = 'A' + i;
  }
  for (int i = 0; i < 26; i++) {
    result[i + 26] = 'a' + i;
  }
  for (int i = 0; i < 10; i++) {
    result[i + 52] = '0' + i;
  }
  result[62] = '\0';
  return result;
}

char* encodeBinaryToFourSymbol(int* binary) {
  char* result = (char*)malloc(4 * sizeof(char));
  int* a1 = (int*)malloc(6 * sizeof(int));
  int* a2 = (int*)malloc(6 * sizeof(int));
  int* a3 = (int*)malloc(6 * sizeof(int));
  int* a4 = (int*)malloc(6 * sizeof(int));
  for (int i = 0; i < 6; i++) {
    a1[i] = binary[i];
  }
  for (int i = 6; i < 12; i++) {
    a2[i - 6] = binary[i];
  }
  for (int i = 12; i < 18; i++) {
    a3[i - 12] = binary[i];
  }
  for (int i = 18; i < 24; i++) {
    a4[i - 18] = binary[i];
  }
  char* alphabet = Alphabet();
  int b1 = encodeBinaryToDecimal(a1);
  int b2 = encodeBinaryToDecimal(a2);
  int b3 = encodeBinaryToDecimal(a3);
  int b4 = encodeBinaryToDecimal(a4);
  result[0] = alphabet[b1];
  result[1] = alphabet[b2];
  result[2] = alphabet[b3];
  result[3] = alphabet[b4];
  return result;
}

int len(char* inputString) {
  int result = 0;

  for (int i = 0; inputString[i] != '\0'; i++) {
    result++;
  }

  return result;
}
char* base64(char* inputString) {
  char* result = (char*)malloc(1 * sizeof(char));
  result[0] = '\0';
  for (int i = 0; i < len(inputString) - 2; i += 3) {
    int* localBinary = encodeThreeSymbolToBinary(inputString[i], inputString[i + 1], inputString[i + 2]);
    char* localLetters = encodeBinaryToFourSymbol(localBinary);
    int localLen = len(result) + 4;
    result = (char*)realloc(result, localLen * sizeof(char));
    result[localLen] = '\0';
    result[localLen - 4] = localLetters[0];
    result[localLen - 3] = localLetters[1];
    result[localLen - 2] = localLetters[2];
    result[localLen - 1] = localLetters[3];
  }
  if (len(inputString) % 3 != 0) {
    if (len(inputString) % 3 == 1) {
      char* alphabet = Alphabet();
      char symbol = inputString[len(inputString) - 1];
      int* binary = encodeSymbolToBinary(symbol);
      int index = encodeBinaryToDecimal(binary);
      char addedSymbol = alphabet[index];
      int* newBinary = (int*)malloc(6 * sizeof(int));
      newBinary[0] = binary[6];
      newBinary[1] = binary[7];
      newBinary[2] = 0;
      newBinary[3] = 0;
      newBinary[4] = 0;
      newBinary[5] = 0;
      int newIndex = encodeBinaryToDecimal(newBinary);
      char newAddedSymbol = alphabet[newIndex];
      int localLen = len(result) + 4;
      result = (char*)realloc(result, localLen * sizeof(char));
      result[localLen] = '\0';
      result[localLen - 4] = addedSymbol;
      result[localLen - 3] = newAddedSymbol;
      result[localLen - 2] = '=';
      result[localLen - 1] = '=';
    }
    else {
      char symbol1 = inputString[len(inputString) - 2];
      char symbol2 = inputString[len(inputString) - 1];
      char* alphabet = Alphabet();
      int* binary1 = encodeSymbolToBinary(symbol1);
      int* binary2 = encodeSymbolToBinary(symbol2);
      int index = encodeBinaryToDecimal(binary1);
      char addedSymbol1 = alphabet[index];
      int* newBinary1 = (int*)malloc(6 * sizeof(int));
      newBinary1[0] = binary1[6];
      newBinary1[1] = binary1[7];
      newBinary1[2] = binary2[0];
      newBinary1[3] = binary2[1];
      newBinary1[4] = binary2[2];
      newBinary1[5] = binary2[3];
      index = encodeBinaryToDecimal(newBinary1);
      char addedSymbol2 = alphabet[index];
      int* newBinary2 = (int*)malloc(6 * sizeof(int));
      newBinary2[0] = binary2[4];
      newBinary2[1] = binary2[5];
      newBinary2[2] = binary2[6];
      newBinary2[3] = binary2[7];
      newBinary2[4] = 0;
      newBinary2[5] = 0;
      index = encodeBinaryToDecimal(newBinary2);
      char addedSymbol3 = alphabet[index];
      int localLen = len(result) + 4;
      result = (char*)realloc(result, localLen * sizeof(char));
      result[localLen] = '\0';
      result[localLen - 4] = addedSymbol1;
      result[localLen - 3] = addedSymbol2;
      result[localLen - 2] = addedSymbol3;
      result[localLen - 1] = '=';
    }
  }
  return result;
}

int main()
{
  char* inputString = getString();
  char* result = base64(inputString);
  printf("%s", result);
}
