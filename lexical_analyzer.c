#include "lexical_analyzer.h"

int main(int argc, char **argv)
{
  if (!argv[1])
  {
    printf("require 1 argument!");
    exit(1);
  }

  if ((file = fopen(argv[1], "r+")) == NULL)
  {
    printf("file not found error!");
    exit(1);
  }

  if ((file = fopen(argv[1], "r+")) == NULL)
  {
    printf("file not found error!");
    exit(1);
  }

  ReturnType output;

  c = (char)fgetc(file);
  while (c != EOF)
  {
    fseek(file, -1, SEEK_CUR);
    output = analyzer();
    printf("(%s, %d, %d)\n", output.token, output.type_id, output.index);
    c = (char)fgetc(file);
  } // loop till end of file

  printf("-----------------------------------------------------------------\n");
  printf("total lines:      %d\n", total_lines);
  printf("total characters: %d\n", total_chars);
  printf("number:           %d\n", number_count);
  printf("string:           %d\n", string_count);
  printf("char:             %d\n", char_count);
  printf("keyword:          %d\n", keyword_count);
  printf("comment:          %d\n", comment_count);
  printf("delimiter:        %d\n", delimiter_count);
  printf("operator:         %d\n", operator_count);
  printf("identifier:       %d\n", identifier_count);
  printf("error:            %d\n", error_count);
  printf("-----------------------------------------------------------------\n");

  return 0;
}

bool isKeyword(char *token)
{
  for (int i = 0; i < 32; i++)
  {
    if (!strcmp(token, keywords[i]))
    {
      return true;
    }
  }
  return false;
}

bool isLetter()
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

bool isDigit()
{
  return (c >= '0' && c <= '9');
}

int insertTable(char *token)
{
  for (int i = 0; i < 1000; i++)
  {
    if (!id_table[i][0])
    {
      strcpy(id_table[i], token);
      return i;
    }
    if (strcmp(token, id_table[i]) == 0)
    {
      return i;
    }
  }
  return -1;
}

ReturnType analyzer()
{
  int state = 0;
  char *token;
  do
  {
    switch (state)
    {
    case 0: // start state
      token = (char *)malloc(1000 * sizeof(char));
      strcpy(token, "");
      c = (char)fgetc(file);
      if (c == EOF)
      {
        state = -1;
        break;
      }
      total_chars++;
      if (c)
        total_chars++;
      while (c == ' ' || c == '\n' || c == '\t')
      {
        if (c == '\n')
          total_lines++;
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
      }

      if (isLetter())
      {
        state = 1;
        break;
      }
      if (isDigit())
      {
        state = 2;
        break;
      }
      switch (c)
      {
      case '#':
        while (c != '\n' && c != EOF)
        {
          c = (char)fgetc(file);
          if (c == EOF)
            break;
          total_chars++;
        }
        total_lines++;
        break;
      case '<':
        state = 8;
        break;
      case '>':
        state = 9;
        break;
      case '/':
        state = 11;
        break;
      case '=':
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '=')
        {
          strcat(token, &c);
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        else
        {
          fseek(file, -1, SEEK_CUR);
          total_chars--;
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        break;
      case '+':
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '+' || c == '=')
        {
          strcat(token, &c);
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        else
        {
          fseek(file, -1, SEEK_CUR);
          total_chars--;
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        break;
      case '-':
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '-' || c == '=')
        {
          strcat(token, &c);
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        else
        {
          fseek(file, -1, SEEK_CUR);
          total_chars--;
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        break;
      case '*':
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '=')
        {
          strcat(token, &c);
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        else
        {
          fseek(file, -1, SEEK_CUR);
          total_chars--;
          operator_count++;
          return (ReturnType){token, 7, NULL};
        }
        break;
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
      case ':':
      case ';':
      case ',':
        strcat(token, &c);
        delimiter_count++;
        return (ReturnType){token, 6, NULL};

        break;
      case '\'': // character
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '\\')
        {
          strcat(token, &c);
          c = (char)fgetc(file);
          if (c == EOF)
            break;
          total_chars++;
          switch (c)
          {
          case 'a':
          case 'b':
          case 'f':
          case 'n':
          case 'r':
          case 't':
          case 'v':
          case '\\':
          case '\'':
          case '\"':
          case '0':
            strcat(token, &c);
            break;
          default:
            error_count++;
            return (ReturnType){token, -1, NULL};
            break;
          }
        }
        else
        {
          strcat(token, &c);
        }
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
        if (c == '\'')
        {
          strcat(token, &c);
          char_count++;
          return (ReturnType){token, 3, NULL};
        }
        else
        {
          error_count++;
          return (ReturnType){token, -1, NULL};
        }
        break;
      case '\"':
        state = 10;
        break;
      default:
        break;
      }
      break;
    case 1: // identifier or keyword
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit() || isLetter())
      {
        state = 1;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        if (isKeyword(token))
        {
          keyword_count++;
          return (ReturnType){token, 4, NULL};
        }
        else
        {
          int index = insertTable(token);
          identifier_count++;
          return (ReturnType){token, 8, index};
        }
      }
      break;
    case 2: // integer
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 2;
        break;
      }
      else if (c == '.')
      {
        state = 3;
        break;
      }
      else if (c == 'E')
      {
        state = 5;
        break;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        number_count++;
        return (ReturnType){token, 1, NULL};
      }
      break;
    case 3: // float point
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 4;
      }
      else
      {
        printf("line %d: error!", total_lines);
        error_count++;
        return (ReturnType){token, -1, NULL};
      }
      break;
    case 4: // float
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 4;
        break;
      }
      else if (c == 'E')
      {
        state = 5;
        break;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        number_count++;
        return (ReturnType){token, 1, NULL};
      }
      break;
    case 5: // exponent
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 7;
        break;
      }
      else if (c == '-' || c == '+')
      {
        state = 6;
        break;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        error_count++;
        return (ReturnType){token, -1, NULL};
      }
      break;
    case 6:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 7;
        break;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        error_count++;
        return (ReturnType){token, -1, NULL};
      }
      break;
    case 7:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (isDigit())
      {
        state = 7;
        break;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        number_count++;
        return (ReturnType){token, 1, NULL};
      }
      break;
    case 8:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (c == '=')
      {
        strcat(token, &c);
        operator_count++;
        return (ReturnType){token, 7, NULL};
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        number_count++;
        return (ReturnType){token, 1, NULL};
      }
      break;
    case 9:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (c == '=')
      {
        strcat(token, &c);
        operator_count++;
        return (ReturnType){token, 7, NULL};
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        number_count++;
        return (ReturnType){token, 1, NULL};
      }
      break;
    case 10:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      while (c != '\"')
      {
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        total_chars++;
      }
      strcat(token, &c);
      string_count++;
      return (ReturnType){token, 2, NULL};

      break;
    case 11:
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (c == '/')
      {
        while (c != '\n')
        {
          strcat(token, &c);
          c = (char)fgetc(file);
          if (c == EOF)
            break;
          total_chars++;
        }
        total_lines++;
        operator_count++;
        return (ReturnType){token, 7, NULL};
      }
      else if (c == '*')
      {
        state = 12;
      }
      else
      {
        fseek(file, -1, SEEK_CUR);
        total_chars--;
        comment_count++;
        return (ReturnType){token, 5, NULL};
      }
      break;
    case 12:
      while (c != '*')
      {
        strcat(token, &c);
        c = (char)fgetc(file);
        if (c == EOF)
          break;
        if (c == '\n')
          total_lines++;
        total_chars++;
      }
      strcat(token, &c);
      c = (char)fgetc(file);
      if (c == EOF)
        break;
      total_chars++;
      if (c == '/')
      {
        strcat(token, &c);
        comment_count++;
        return (ReturnType){token, 5, NULL};
      }
      else
      {
        state = 12;
      }
      break;
    case 13:
      printf("line %d: error!", total_lines);
      break;
    default:
      break;
    }
  } while (state != -1);
  error_count++;
  return (ReturnType){token, -1, NULL};
}