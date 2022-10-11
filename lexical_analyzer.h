#pragma once

#ifndef LEX_H_
#define LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE *file;
char c;
char id_table[1000][100] = { 0 };

long total_lines = 1; // total lines
long total_chars = 0; // total character

long number_count = 0;
long string_count = 0;
long char_count = 0;
long keyword_count = 0;
long comment_count = 0;
long delimiter_count = 0;
long operator_count = 0;
long identifier_count = 0;
long error_count = 0;

typedef struct ReturnType {
  char* token;
  int type_id;
  int index;
} ReturnType;

const char* keywords[] = {
  "auto", "break", "case", "char", "const", "continue", "default", "do", 
  "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", 
  "long", "register", "return", "short", "signed", "sizeof", "static", "struct",
  "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

const char delimiters[] = {
  '{', '}', '[', ']', ';', ',', '.', '(', ')', ':', '*', '#', '/', '\'', '\"',
};

ReturnType analyzer();

bool isKeyword(char* str);
bool isLetter(char c);
bool isDigit(char c);
int insertTable(char* token);

#endif