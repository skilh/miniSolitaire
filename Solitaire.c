#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define  NO_CARD_COLOR_ON_THAT_PLACE ' '
#define  NO_CARD_RANG_ON_THAT_PLACE  0

struct _Stacks_
{
    int rang;
    char color;
    int card_number;
    struct _Stacks_ *next;
    struct _Stacks_ *previous;
};

typedef enum _ReturnValues_
{
    ALL_OK = 0,
    INVALID_ARGV_ARGC = 1,
    NO_MEMORY = 2,
    INVALID_FILE = 3,
    INVALID_GAME_COMMAND,
    INVALID_COMMAND_MOVE,
    EXIT = 6,
} ReturnValues;

///------------------------------------------------------------------------------
///
/// Function declares for each return value it's print messages;
/// Note that some cases are intentionally!
///
/// @param return_value
/// @return
//
ReturnValues printErrorMessages(ReturnValues return_value)
{
  switch(return_value)
  {
    case INVALID_ARGV_ARGC:
      printf("[ERR] Usage: ./ass3 [file-name]\n");
      break;
    case NO_MEMORY:
      printf(
        "[ERR] Out of memory.\n");
      break;
    case INVALID_FILE :
      printf("[ERR] Invalid file!\n");
      break;
    case INVALID_GAME_COMMAND:
      printf("[INFO] Invalid command!\n");
      break;
    case INVALID_COMMAND_MOVE :
      printf("[INFO] Invalid move command!\n");
      break;
    case ALL_OK:
      //left blank intentionally
      break;
  }
  return return_value;
}


///------------------------------------------------------------------------------
/// Function checks if file is valid.
///
/// @param buffer in which is saved loaded file;
/// @param length of that file;
/// @return ALL_OK if file is valid;
/// @return INVALID_FILE if there are no 13(A - K) RED and 13 BLACK(A - K) cards;
//
ReturnValues fileIsValid( char *buffer, int length)
{
  int counter1 = 0;
  int counter2 = 0;
  int counter3 = 0;

  int mark_begin_word;
  int mark_end_word;
  int word_length;

  int count_red_cards = 0;
  int count_black_cards = 0;

  int count_card_two = 0;
  int count_card_three = 0;
  int count_card_four = 0;
  int count_card_five = 0;
  int count_card_six = 0;
  int count_card_seven = 0;
  int count_card_eight = 0;
  int count_card_nine = 0;
  int count_card_ten = 0;
  int count_card_jack = 0;
  int count_card_queen = 0;
  int count_card_king = 0;
  int count_card_ace = 0;

  char compare_red[4];
  char compare_black[6];

  char compare_card_two[2];
  char compare_card_three[2];
  char compare_card_four[2];
  char compare_card_five[2];
  char compare_card_six[2];
  char compare_card_seven[2];
  char compare_card_eight[2];
  char compare_card_nine[2];
  char compare_card_ten[3];
  char compare_card_jack[2];
  char compare_card_queen[2];
  char compare_card_king[2];
  char compare_card_ace[2];

  int str_cmp_res_red;
  int str_cmp_res_black;

  int str_cmp_res_ace;
  int str_cmp_res_two;
  int str_cmp_res_three;
  int str_cmp_res_four;
  int str_cmp_res_five;
  int str_cmp_res_six;
  int str_cmp_res_seven;
  int str_cmp_res_eight;
  int str_cmp_res_nine;
  int str_cmp_res_ten;
  int str_cmp_res_jack;
  int str_cmp_res_queen;
  int str_cmp_res_king;

  strcpy(compare_red, "RED");
  strcpy(compare_black, "BLACK");

  strcpy(compare_card_two, "2");
  strcpy(compare_card_three, "3");
  strcpy(compare_card_four, "4");
  strcpy(compare_card_five, "5");
  strcpy(compare_card_six, "6");
  strcpy(compare_card_seven, "7");
  strcpy(compare_card_eight, "8");
  strcpy(compare_card_nine, "9");
  strcpy(compare_card_ten, "10");
  strcpy(compare_card_jack, "J");
  strcpy(compare_card_queen, "Q");
  strcpy(compare_card_king, "K");
  strcpy(compare_card_ace, "A");


  while(counter1 != length)
  {
    /// This temporary array changes it's size every time new word/letter occurs;
    char *temp_array = (char*)malloc(sizeof(char));

    if(temp_array == NULL)
    {
      printErrorMessages(NO_MEMORY);
      return NO_MEMORY;
    }
    /// When beginning of word/letter has been found;
    if ((buffer[counter1] != ' ') & (buffer[counter1] != '\n'))
    {
      mark_begin_word = counter1;

      while((buffer[counter1] != ' ') & (buffer[counter1] != '\n'))
      {
        counter1++;
      }

      mark_end_word = counter1;
      /// When end of the word has been reached and;
      /// now we calculate it's length;
      word_length = mark_end_word - mark_begin_word;
      temp_array = realloc(temp_array, (sizeof(char) * (word_length + 1)));

      if(temp_array == NULL)
      {
        printErrorMessages(NO_MEMORY);
        return NO_MEMORY;
      }

      /// Store a word into an array which we will use for comparison;
      counter3 = mark_begin_word;
      while ((counter2 <= word_length) & (counter3 <= (mark_end_word - 1)))
      {
        temp_array[counter2] = buffer[counter3];
        counter2++;
        counter3++;
      }
      temp_array[word_length ] = '\0';

      /// Check if word is part of 'allowed' words (e.g. RED, BLACK, K, Q..);
      switch (word_length)
      {
        case 3:
          str_cmp_res_red = strcmp(compare_red, temp_array);
          if (str_cmp_res_red != 0)
          {
            return INVALID_FILE;
          }
          else
          {
            count_red_cards++;
          }
          break;

        case 5:
          str_cmp_res_black = strcmp(compare_black, temp_array);
          if (str_cmp_res_black != 0)
          {
            return INVALID_FILE;
          }
          else
          {
            count_black_cards++;
          }
          break;

        case 2:
          str_cmp_res_ten = strcmp(compare_card_ten, temp_array);
          if (str_cmp_res_ten != 0)
          {
            return INVALID_FILE;
          }
          else
          {
            count_card_ten++;
          }
          break;

        case 1:
          str_cmp_res_ace = strcmp(compare_card_ace, temp_array);
          str_cmp_res_two = strcmp(compare_card_two, temp_array);
          str_cmp_res_three = strcmp(compare_card_three, temp_array);
          str_cmp_res_four = strcmp(compare_card_four, temp_array);
          str_cmp_res_five = strcmp(compare_card_five, temp_array);
          str_cmp_res_six = strcmp(compare_card_six, temp_array);
          str_cmp_res_seven = strcmp(compare_card_seven, temp_array);
          str_cmp_res_eight = strcmp(compare_card_eight, temp_array);
          str_cmp_res_nine = strcmp(compare_card_nine, temp_array);
          str_cmp_res_jack = strcmp(compare_card_jack, temp_array);
          str_cmp_res_queen = strcmp(compare_card_queen, temp_array);
          str_cmp_res_king = strcmp(compare_card_king, temp_array);

          if (str_cmp_res_ace == 0)
          {
            count_card_ace++;
            break;
          }
          else if (str_cmp_res_two == 0)
          {
            count_card_two++;
            break;
          }
          else if (str_cmp_res_three == 0)
          {
            count_card_three++;
            break;
          }
          else if (str_cmp_res_four == 0)
          {
            count_card_four++;
            break;
          }
          else if (str_cmp_res_five == 0)
          {
            count_card_five++;
            break;
          }
          else if (str_cmp_res_six == 0)
          {
            count_card_six++;
            break;
          }
          else if (str_cmp_res_seven == 0)
          {
            count_card_seven++;
            break;
          }
          else if (str_cmp_res_eight == 0)
          {
            count_card_eight++;
            break;
          }
          else if (str_cmp_res_nine == 0)
          {
            count_card_nine++;
            break;
          }
          else if (str_cmp_res_jack == 0)
          {
            count_card_jack++;
            break;
          }
          else if (str_cmp_res_queen == 0)
          {
            count_card_queen++;
            break;
          }
          else if (str_cmp_res_king == 0)
          {
            count_card_king++;
            break;
          }
          else
          {
            return INVALID_FILE;
          }
      }
    }
    free(temp_array);
    counter1++;
    counter2 = 0;
    counter3 = 0;
  }

  if((count_black_cards != 13) |
     (count_red_cards != 13) |
     (count_card_ace != 2) |
     (count_card_two != 2) |
     (count_card_three != 2) |
     (count_card_four != 2) |
     (count_card_five != 2) |
     (count_card_six != 2) |
     (count_card_seven != 2) |
     (count_card_eight != 2) |
     (count_card_nine != 2) |
     (count_card_ten != 2) |
     (count_card_jack != 2) |
     (count_card_queen != 2) |
     (count_card_king != 2))
  {
    return INVALID_FILE;
  }
  else
    return ALL_OK;
}

///------------------------------------------------------------------------------
/// Function checks if every card is in only one line;
///
/// @param buffer is file;
/// @param legth of file;
/// @return ALL_OK if one card is in only one line;
/// @return INVALID_FILE if not every card in only one line;
//
ReturnValues countLinesOfFile(char *buffer, int legth)
{
  int counter1 = 0;
  int counter2 = 0;

  for (; counter1 != legth; counter1++)
  {
    if((buffer[counter1] != ' ') & (buffer[counter1] != '\n'))
    {
      counter2++;
    }

    if(buffer[counter1] == '\n')
    {
      if(((((counter2 != 0) & (counter2 != 4)) & (counter2 != 5)) &
          (counter2 != 6)) & (counter2 != 7 ))
      {
        break;
        return INVALID_FILE;
      }
      else
      {
        counter2 = 0;
      }
    }
  }
  return printErrorMessages(ALL_OK);
}

///------------------------------------------------------------------------------
/// Since I decided to store rang of each card as int value, I needed function
/// which will return char values for letters A, Q, K, J.
/// This function was necessary for easier printing later on.
///
///
/// @param number_to_convert
/// @return
//
char *convertCharToInteger(int number_to_convert)
{

  char *string = (char*)malloc(sizeof(char) * 3);
  char temp_char;

  if(number_to_convert == 10)
  {
    sprintf(string, "%d", number_to_convert);
    return string;
  }
  else if( number_to_convert == 14)
  {
    strcpy(string, "A");
    return string;
  }
  else if( number_to_convert == 13)
  {
    strcpy(string, "K");
    return string;
  }
  else if( number_to_convert == 12)
  {
    strcpy(string, "Q");
    return string;
  }
  else if( number_to_convert == 11)
  {
    strcpy(string, "J");
    return string;
  }
  else if( number_to_convert < 10)
  {
    sprintf(string, "%d", number_to_convert);
    return string;
  }
  return string;
}


///------------------------------------------------------------------------------
/// Here is an example which represent what this
/// function prints:
///
///  0   | 1   | 2   | 3   | 4   | DEP | DEP\n
///  ---------------------------------------\n
///  X   | BK  | BQ  | BJ  | B10 |     |    \n
///  X   |     | B9  | B8  | B7  |     |    \n
///  X   |     |     | B6  | B5  |     |    \n
///  X   |     |     |     | B4  |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  X   |     |     |     |     |     |    \n
///  B3  |     |     |     |     |     |    \n
///
/// @param array_of_head_nodes pointer to bottom of each stack
//
void printStacks(struct _Stacks_* array_of_head_nodes)
{
  int counter1 = 0;
  int counter2 = 0;
  struct _Stacks_ *help_ptr;

  printf("0   | 1   | 2   | 3   | 4   | DEP | DEP\n");
  printf("---------------------------------------\n");

  struct _Stacks_* stack_null_ptr = (array_of_head_nodes + 0);
  struct _Stacks_* stack_one_ptr = (array_of_head_nodes + 1);
  struct _Stacks_* stack_two_ptr = (array_of_head_nodes + 2);
  struct _Stacks_* stack_three_ptr = (array_of_head_nodes + 3);
  struct _Stacks_* stack_four_ptr = (array_of_head_nodes + 4);
  struct _Stacks_* stack_five_ptr = (array_of_head_nodes + 5);
  struct _Stacks_* stack_six_ptr = (array_of_head_nodes + 6);
  int counter = 0;
  int first_card_on_stack_null = 22; /// 23 means there are no cards
                                     /// | Some random number which shows
                                     /// there was no taken cards from Stack0
  int first_card_on_stack_one = 22;
  int first_card_on_stack_two = 22;
  int first_card_on_stack_three = 22;
  int first_card_on_stack_four = 22;
  int first_card_on_stack_five = 22;
  int first_card_on_stack_six = 22;
  char *string;
  char *string1;

  while(stack_null_ptr != NULL)
  {
    if((array_of_head_nodes + 0)->rang == 0)
    {
      first_card_on_stack_null = 23;
      break;
    }
    if(stack_null_ptr->rang == 0)
    {
      first_card_on_stack_null = stack_null_ptr->previous->card_number;
      break;

    }
    stack_null_ptr = stack_null_ptr->next;
  }
  while(stack_one_ptr != NULL)
  {
    if((array_of_head_nodes + 1)->rang == 0)
    {
      first_card_on_stack_one = 23;
      break;
    }
    if(stack_one_ptr->rang == 0)
    {
      first_card_on_stack_one = stack_one_ptr->previous->card_number;
      break;
    }
    stack_one_ptr = stack_one_ptr->next;
  }
  while(stack_two_ptr != NULL)
  {
    if((array_of_head_nodes + 2)->rang == 0)
    {
      first_card_on_stack_two = 23;
      break;
    }
    if(stack_two_ptr->rang == 0)
    {
      first_card_on_stack_two = stack_two_ptr->previous->card_number;
      break;

    }
    stack_two_ptr = stack_two_ptr->next;
  }
  while(stack_three_ptr != NULL)
  {
    if((array_of_head_nodes + 3)->rang == 0)
    {
      first_card_on_stack_three = 23;
      break;
    }
    if(stack_three_ptr->rang == 0)
    {
      first_card_on_stack_three = stack_three_ptr->previous->card_number;
      break;

    }
    stack_three_ptr = stack_three_ptr->next;
  }
  while(stack_four_ptr != NULL)
  {
    if((array_of_head_nodes + 4)->rang == 0)
    {
      first_card_on_stack_four = 23;
      break;
    }
    if(stack_four_ptr->rang == 0)
    {
      first_card_on_stack_four = stack_four_ptr->previous->card_number;
      break;

    }
    stack_four_ptr = stack_four_ptr->next;
  }
  while(stack_five_ptr != NULL)
  {
    if((array_of_head_nodes + 5)->rang == 0)
    {
      first_card_on_stack_five = 23;
      break;
    }
    if(stack_five_ptr->rang == 0)
    {
      first_card_on_stack_five = stack_five_ptr->previous->card_number;
      break;

    }
    stack_five_ptr = stack_five_ptr->next;
  }
  while(stack_six_ptr != NULL)
  {
    if((array_of_head_nodes + 6)->rang == 0)
    {
      first_card_on_stack_six = 23;
      break;
    }
    if(stack_six_ptr->rang == 0)
    {
      first_card_on_stack_six = stack_six_ptr->previous->card_number;
      break;

    }
    stack_six_ptr = stack_six_ptr->next;
  }

  stack_null_ptr = (array_of_head_nodes + 0);
  stack_one_ptr = (array_of_head_nodes + 1);
  stack_two_ptr = (array_of_head_nodes + 2);
  stack_three_ptr = (array_of_head_nodes + 3);
  stack_four_ptr = (array_of_head_nodes + 4);
  stack_five_ptr = (array_of_head_nodes + 5);
  stack_six_ptr = (array_of_head_nodes + 6);

  for(counter; counter <= 15; counter++)
  {
    /// Before any move was made
    if((first_card_on_stack_null == 22) && (stack_null_ptr->card_number == 15))
    {
      /// Before any move and number 10 is last card
      if( stack_null_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_null_ptr->rang);
        printf("%c%s |", stack_null_ptr->color, string);
        free(string);
      }
       /// Before first move and numb. between 2 and 9 are on top
      else if((stack_null_ptr->rang < 10 && stack_null_ptr->rang > 1)
              || (stack_null_ptr->rang >= 11 && stack_null_ptr->rang <= 14))
      {

        string = convertCharToInteger(stack_null_ptr->rang);
        printf("%c%s  |", stack_null_ptr->color, string);
        free(string);
      }
    }
    else if((first_card_on_stack_null == 22) &&
      (stack_null_ptr->card_number < 15))
      printf("X   |");

    /// kada nema  niti jedna karta na Stack0
    else if(first_card_on_stack_null == 23)
    {
      printf("    |");
    }
    /// Kada ima min. jedna karta na Stacku a maksimalno 14;
    else if(first_card_on_stack_null <= 14)
    {
      /// Dok ne dodjes do te karte sa caunterom
      if (counter < first_card_on_stack_null)
        printf("X   |");
        /// Kada si dosao na tu kartu
      else if (counter == first_card_on_stack_null)
      {
        if (stack_null_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_null_ptr->rang);
          printf("%c%s |", stack_null_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i broj od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_null_ptr->rang);
          printf("%c%s  |", stack_null_ptr->color, string);
          free(string);
        }
      }
      else if(counter > first_card_on_stack_null)
        printf("    |");
    }
    else if(counter > first_card_on_stack_null)
      printf("    |");
      ///Print Stack1
      /// Case when there is no cards on Stack1
    if(first_card_on_stack_one == 23)
        printf("     |");
      ///Case when Stack1 is full
    else if(first_card_on_stack_one == 22)
    {
        /// Kada nista nije dirano  i 10 zadnja
      if( stack_one_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_one_ptr->rang);
        printf(" %c%s |", stack_one_ptr->color, string);
        free(string);
      }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_one_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_one_ptr->rang);
        printf(" %c%s  |", stack_one_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_one <= 14)
    {
      if(counter <= first_card_on_stack_one)
      {
        if (stack_one_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_one_ptr->rang);
          printf(" %c%s |", stack_one_ptr->color, string);
          free(string);
        }
            ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_one_ptr->rang);
          printf(" %c%s  |", stack_one_ptr->color, string);
          free(string);
        }
      }
      else
        printf("     |");
    }
    ///For Stack2
    if(first_card_on_stack_two == 23)
      printf("     |");
      ///Case when Stack1 is full
    else if(first_card_on_stack_two == 22)
    {
      /// Kada nista nije dirano  i 10 zadnja
      if( stack_two_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_two_ptr->rang);
        printf(" %c%s |", stack_two_ptr->color, string);
        free(string);
      }
        ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_two_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_two_ptr->rang);
        printf(" %c%s  |", stack_two_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_two <= 14)
    {
      if(counter <= first_card_on_stack_two)
      {
        if (stack_two_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_two_ptr->rang);
          printf(" %c%s |", stack_two_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_two_ptr->rang);
          printf(" %c%s  |", stack_two_ptr->color, string);
          free(string);
        }
      }
      else
        printf("     |");
    }
    ///For Stack3
    if(first_card_on_stack_three == 23)
      printf("     |");
      ///Case when Stack1 is full
    else if(first_card_on_stack_three == 22)
    {
      /// Kada nista nije dirano  i 10 zadnja
      if( stack_three_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_three_ptr->rang);
        printf(" %c%s |", stack_three_ptr->color, string);
        free(string);
      }
        ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_three_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_three_ptr->rang);
        printf(" %c%s  |", stack_three_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_three <= 14)
    {
      if(counter <= first_card_on_stack_three)
      {
        if (stack_three_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_three_ptr->rang);
          printf(" %c%s |", stack_three_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_three_ptr->rang);
          printf(" %c%s  |", stack_three_ptr->color, string);
          free(string);
        }
      }
      else
        printf("     |");
    }
    ///For Stack4
    if(first_card_on_stack_four == 23)
      printf("     |");
      ///Case when Stack1 is full
    else if(first_card_on_stack_four == 22)
    {
      /// Kada nista nije dirano  i 10 zadnja
      if( stack_four_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_four_ptr->rang);
        printf(" %c%s |", stack_four_ptr->color, string);
        free(string);
      }
        ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_four_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_four_ptr->rang);
        printf(" %c%s  |", stack_four_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_four <= 14)
    {
      if(counter <= first_card_on_stack_four)
      {
        if (stack_four_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_four_ptr->rang);
          printf(" %c%s |", stack_four_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_four_ptr->rang);
          printf(" %c%s  |", stack_four_ptr->color, string);
          free(string);
        }
      }
      else
        printf("     |");
    }
    ///For Stack5
    if(first_card_on_stack_five == 23)
      printf("     |");
      ///Case when Stack1 is full
    else if(first_card_on_stack_five == 22)
    {
      /// Kada nista nije dirano  i 10 zadnja
      if( stack_five_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_five_ptr->rang);
        printf(" %c%s |", stack_five_ptr->color, string);
        free(string);
      }
        ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_five_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_five_ptr->rang);
        printf(" %c%s  |", stack_five_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_five <= 14)
    {
      if(counter <= first_card_on_stack_five)
      {
        if (stack_five_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_five_ptr->rang);
          printf(" %c%s |", stack_five_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_five_ptr->rang);
          printf(" %c%s  |", stack_five_ptr->color, string);
          free(string);
        }
      }
      else
        printf("     |");
    }
    ///For Stack63
    if(first_card_on_stack_six == 23)
      printf("    \n");
      ///Case when Stack1 is full
    else if(first_card_on_stack_six == 22)
    {
      /// Kada nista nije dirano  i 10 zadnja
      if( stack_six_ptr->rang == 10)
      {
        string = convertCharToInteger(stack_six_ptr->rang);
        printf(" %c%s\n", stack_six_ptr->color, string);
        free(string);
      }
        ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
      else if(stack_six_ptr->rang < 10)
      {
        string = convertCharToInteger(stack_six_ptr->rang);
        printf(" %c%s \n", stack_six_ptr->color, string);
        free(string);
      }
    }
    else if(first_card_on_stack_six <= 14)
    {
      if(counter <= first_card_on_stack_six)
      {
        if (stack_six_ptr->rang == 10)
        {
          string = convertCharToInteger(stack_six_ptr->rang);
          printf(" %c%s\n", stack_six_ptr->color, string);
          free(string);
        }
          ///Kada nista nije dirano i brojevi od 2 do 9 zadnji
        else
        {
          string = convertCharToInteger(stack_six_ptr->rang);
          printf(" %c%s \n", stack_six_ptr->color, string);
          free(string);
        }
      }
      else
        printf("    \n");
    }

    stack_null_ptr = stack_null_ptr->next;
    stack_one_ptr = stack_one_ptr->next;
    stack_two_ptr = stack_two_ptr->next;
    stack_three_ptr = stack_three_ptr->next;
    stack_four_ptr = stack_four_ptr->next;
    stack_five_ptr = stack_five_ptr->next;
    stack_six_ptr = stack_six_ptr->next;
  }
}

///------------------------------------------------------------------------------
/// Read cards from file and store it in buffer.
/// If file contains nothing, return NULL.
///
///
/// @param path(location of file);
/// @return pointer to first elem., in this case it is first
///         letter/character in file;
//
char *loadCardsFromFile(const char *path)
{
  FILE *stream;
  int loop_counter = 0;
  int length_of_file = 0;
  ReturnValues return_value;

  stream = fopen(path, "r");
  if(stream == NULL)
    return NULL;

  fseek(stream, 0, SEEK_END);
  length_of_file = (int)ftell(stream);
  fseek(stream, 0, SEEK_SET);

  /// Reserve enough memory for input;
  char *file_buffer =
    (char*) malloc(sizeof(char) * (size_t )(length_of_file + 10));
  if(file_buffer == NULL)
    return NULL;

  /// Save everything into buffer
  while((file_buffer[loop_counter] = (char) fgetc(stream)) != EOF)
  {
    loop_counter++;
  }

  fclose(stream);
  *(file_buffer + loop_counter) = '\0';
  return_value = fileIsValid(file_buffer, loop_counter);
  if(return_value == INVALID_FILE || return_value == NO_MEMORY)
  {
    free(file_buffer);
    return NULL;
  }
  return_value = countLinesOfFile(file_buffer, loop_counter);
  if(return_value == INVALID_FILE || return_value == NO_MEMORY)
  {
    free(file_buffer);
    return NULL;
  }

  return file_buffer;
}

///------------------------------------------------------------------------------
/// Array which holds heads(bottoms) of Stack0/1/.../6 will
/// be returned.
/// This function could be seen as "setting up a table" on
/// which game will be played later on.
///
/// @return pointer to array of structs.
//
struct _Stacks_ *setGame()
{
  struct  _Stacks_* array_of_head_nodes;
  struct _Stacks_* help_ptr;
  struct _Stacks_* current;
  int counter_one = 0;
  int counter_two = 0;
  int mark_position = 0;

  array_of_head_nodes =
    (struct _Stacks_*) malloc(sizeof(struct _Stacks_) * 7);
  if (array_of_head_nodes == NULL)
    return NULL; //NO mem ERR

  for(counter_one; counter_one <= 6; counter_one++)
  {
    (array_of_head_nodes + counter_one)->next =
      (struct _Stacks_*) malloc(sizeof(struct _Stacks_));
    (array_of_head_nodes+counter_one)->previous = NULL;
    (array_of_head_nodes+counter_one)->color = ' ';
    (array_of_head_nodes+counter_one)->rang = 0;
    (array_of_head_nodes + counter_one)->card_number = 0;
    help_ptr = (array_of_head_nodes + counter_one)->next;
    help_ptr->previous = (array_of_head_nodes + counter_one);

    for(counter_two = 0; counter_two <= 14; counter_two++)
    {
      help_ptr->card_number = ++mark_position;
      help_ptr->rang = 0;
      help_ptr->color = ' ';
      if(counter_two != 14)
      {
        help_ptr->next = (struct _Stacks_*) malloc(sizeof(struct _Stacks_));
        current = help_ptr;
        help_ptr = help_ptr->next;
        help_ptr->previous = current;
      }
      else
      {
        help_ptr->next = NULL;
      }
    }
    mark_position = 0;
  }
  return array_of_head_nodes;
}

///------------------------------------------------------------------------------
/// Function will free all memory which was allocated for stacks, every time when
/// function was called.
///
///
/// @param array_of_head_nodes
//
void freeMemory(struct _Stacks_* array_of_head_nodes)
{
  struct _Stacks_* help_ptr;
  struct _Stacks_* head;
  int counter = 0;
  for(counter; counter <= 6; counter++)
  {
    head = (array_of_head_nodes + counter)->next;
    while (head != NULL)
    {
      help_ptr = head->next;
      free(head);
      head = NULL;
      head = help_ptr;
    }
    help_ptr = NULL;
  }
  free(array_of_head_nodes);
}

///------------------------------------------------------------------------------
/// Every card is loaded from File and than stored on Stack,
/// otherwise said- game has form as described in part
/// "Austeilen der Karten".
///
/// @param head_nodes
/// @param buffer
/// @return
//
struct _Stacks_ *loadCardsOnStacks(char* buffer)
{
  char loaded_color[26];
  int loaded_rang[26];
  char space = ' ';
  char A = 'A';

  int counter = 0;
  int counter_col = 0;
  int count_rang = 0;
  int cnt = 0;
  struct _Stacks_ *nodes = setGame();
  if(nodes == NULL)
    return NULL;

  while(buffer[counter] != '\0')
  {
    if(buffer[counter] == 'R')
    {
      loaded_color[counter_col] = 'R';
      counter_col++;
    }
    else if(buffer[counter] == 'B')
    {
      loaded_color[counter_col] = 'B';
      counter_col++;
    }
    else if(((int)buffer[counter] >= 50) && ((int)buffer[counter] <= 57))
    {
      loaded_rang[count_rang] = (int)buffer[counter]-48;
      count_rang++;
    }
    else if(buffer[counter] == 'J')
    {
      loaded_rang[count_rang] = 11;
      count_rang++;
    }
    else if(buffer[counter] == 'Q')
    {
      loaded_rang[count_rang] = 12;
      count_rang++;
    }
    else if(counter != 0)
    {
      if(((int)*(buffer + (counter-1)) == 49) &&
        ((int)*(buffer + (counter)) == 48))
      {
        loaded_rang[count_rang] = 10;
        count_rang++;
      }
      else if((buffer[(counter-1)] == space) && (buffer[counter] == 'K'))
      {
        loaded_rang[count_rang] = 13;
        count_rang++;
      }
      else if((buffer[counter-1] == space) && (buffer[counter] == A))
      {
      loaded_rang[count_rang] = 14;
      count_rang++;
      }
    }
    counter++;
  }
  counter = 25;
  count_rang = 0;
  counter_col = 0;
  struct _Stacks_* help_ptr;

  for(counter; counter >= 16; counter--)
  {
    if(counter == 25)
    {
      help_ptr = (nodes + 1);
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 24)
    {
      help_ptr = (nodes + 2);
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 23)
    {
      help_ptr = (nodes + 3);
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 22)
    {
      help_ptr = (nodes + 4);
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 21)
    {
      help_ptr = (nodes + 2)->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 20)
    {
      help_ptr = (nodes + 3)->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 19)
    {
      help_ptr = (nodes + 4)->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 18)
    {
      help_ptr = (nodes + 3)->next->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 17)
    {
      help_ptr = (nodes + 4)->next->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
    else if(counter == 16)
    {
      help_ptr = (nodes + 4)->next->next->next;
      help_ptr->color = loaded_color[counter];
      help_ptr->rang = loaded_rang[counter];
    }
  }
  help_ptr = nodes;
  while(cnt != 16)
  {
    help_ptr->rang = loaded_rang[cnt];
    help_ptr->color = loaded_color[cnt];
    help_ptr = help_ptr->next;
    cnt++;
  }
  return nodes;
}

///------------------------------------------------------------------------------
/// Function stores card on top of given stack
///
/// @param buffer of heads(bottom card) for each stack;
/// @param num of stack on which card should be stored;
/// @param rang of card to store;
/// @param col of card to store;
/// @return pointer to same array;
//
ReturnValues addCardsOnTop(struct _Stacks_ *buffer,
                           int num, int rang, char col)
{
  struct _Stacks_ *help_var = buffer;
  struct _Stacks_ *temp;

  while(help_var[num].next != NULL)
  {
    *(help_var + num) = *(help_var + num)->next;
  }

  /* Now we add a new variable */
  help_var[num].next = malloc(sizeof(struct _Stacks_));

  if(help_var[num].next == NULL)
    return NO_MEMORY;

  help_var[num].next->rang = rang;
  help_var[num].next->color = col;

  return ALL_OK;
}

///------------------------------------------------------------------------------
///
/// This code was copied and used, source:
/// https://stackoverflow.com/questions/12698836/counting-words-in-a-string-c-programming
///
///
/// @param sentence
/// @return counted words in sentence
//
int countWords(char *sentence)
{
  int counted = 0; // result

  // state:
  char *it = sentence;
  int inword = 0;

  do
    switch(*it)
    {
      case '\0':
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        if (inword)
        {
          inword = 0;
          counted++;
        }
        break;
      default:
        inword = 1;
    }
  while(*it++);

  return counted;
}

///------------------------------------------------------------------------------
/// Whenever user enters 1 word than this function is called.
/// Function returns INVALID COMMAND if command isn't EXIT or HELP.
/// If command is EXIT than EXIT will be returned, after that program stops.
/// If command is HELP than all possible commands are listed on STDOUT and
/// program waits for next command.
///
/// @param command is pointer to an array which holds command;
//
ReturnValues checkCommandTypeWhenOneWord(char *command)
{
  long unsigned leng;
  int counter = 0;
  int counter2 = 0;
  char exit[] = "EXIT\0";
  char help[] = "HELP\0";
  int result_of_comparisson;
  leng = strlen(command);
  leng++;
  char *temp = (char*)malloc(sizeof(char) * leng);
  for(counter; counter <= (leng - 1); counter++)
  {
    if((int)command[counter] >= 65 && (int)command[counter] <= 90)
    {
      temp[counter2] = command[counter];
      counter2++;
    }
  }
  temp[counter2] = '\0';
  if((result_of_comparisson = strcmp(temp, exit)) == 0)
  {
    free(temp);
    return EXIT;
  }
  else if((result_of_comparisson = strcmp(temp, help)) == 0)
  {
    printf("possible command:\n"
             " - move <color> <value> to <stacknumber>\n"
             " - help\n"
             " - exit\n");
    free(temp);
    return ALL_OK;
  }
  else
  {
    printErrorMessages(INVALID_GAME_COMMAND);
    free(temp);
    return INVALID_GAME_COMMAND;
  }
}

///------------------------------------------------------------------------------
/// Function receives pointer to start position,
/// it is first empty place after 'D' (if color is RED) or 'K' (if color is BLACK).
/// Another param. is pointer on place in memory
/// just before place where char 'T'(TO part of command) is saved.
///
/// Both pointers are pointing to same dynamically allocated array,
/// only on different members of that array.
///
/// @param start_position place from which function searches for rang
/// @param end_position   place where that search ends.
/// @return card_rang     is rang of a card from user's input.
//
int findRangNumbersInCommand(char *start_position, char *end_position)
{
  int card_rang = 0;
  int counter = 0;
  char number_area[100];
  while((start_position + counter) != end_position)
  {
    number_area[counter] = *(start_position + counter);
    counter++;
  }
  number_area[counter] = '\0';
  sscanf(number_area, "%d", &card_rang);

  return card_rang;
}

///------------------------------------------------------------------------------
/// Since the command should contain StackNr. on which card should be moved,
/// there is task to find that number. This function does exactly that!
///
/// (Valid) Command must has a form in which last number represent StackNr.
/// This number could be placed anywhere after preposition word 'TO',
/// which is also place from where this functions starts to search that number.
///
/// @param start_position pointer on place in memory where the end of command is saved.
/// @return StackNr. that user entered.
//
int findStackNumberInCommand(char *start_position)
{
  int stack_number = 10;
  int counter = 0;
  char number_area[100];

  while(*(start_position + counter) != '\0')
  {
    number_area[counter] = *(start_position + counter);
    counter++;
  }

  number_area[counter] = '\0';
  sscanf(number_area, "%d", &stack_number);

  return stack_number;
}

///------------------------------------------------------------------------------
/// Function finds and returns card on Stack.
/// Stack on which to search is given in command that user entered.
///
///
/// @param array_of_head_nodes   pointer to bottom of each Stack
/// @param col_to_find
/// @param rang_to_find
/// @param stack_to_search
/// @return
//
struct _Stacks_ *findFirstCardOnStackNumber
  (struct _Stacks_ *array_of_head_nodes,int stack_to_search)
{
  struct _Stacks_ *last_card;
  struct _Stacks_ *temp_ptr = (array_of_head_nodes + stack_to_search);

  /// No cards on that stack;
  if((array_of_head_nodes + stack_to_search)->rang == 0)
    last_card = (array_of_head_nodes + stack_to_search);

  /// At least one card on stack but less than 15 cards;
  else
  {
    while (temp_ptr != NULL)
    {
      if (temp_ptr->rang == 0)
      {
        last_card = temp_ptr->previous;
        break;
      }
      temp_ptr = temp_ptr->next;
    }
  }
  return last_card;
}

///------------------------------------------------------------------------------
/// This function searches for card which user wants to move
///
/// @param array_of_head_nodes is array of last card on each Stach(or head node)
/// @param rang                represents rang of card which user wants to move
/// @param color               represents coloro of card which user wants to move
/// @return                    pointer to place in memory where that card is stored
//
struct _Stacks_ *findCard(struct _Stacks_ *array_of_head_nodes,
                          int rang, char color)
{
  struct _Stacks_ *card_location;
  struct _Stacks_ *iterator;
  int counter = 0;
  iterator = array_of_head_nodes;
  int counter2 = 0;
  for(counter; counter <= 6; counter++)
  {
    iterator = (array_of_head_nodes + counter);
    for(counter2 = 0; counter2 <= 15; counter2++)
    {
      if((iterator->color == color) && (iterator->rang == rang))
      {
        card_location = iterator;
        return  card_location;
      }
      iterator = iterator->next;
    }
  }
}

///------------------------------------------------------------------------------
/// Sometimes user wants to move more than just one card to some stack.
/// This is only possible if cards(to move) are in right order,
/// or in other words: previous card color != next card color and
///                    previous card rang - next card rang = 1.
///
/// Function will return bool value ( 0 = FALSE and 1 = TRUE).
///
/// @param pointer_to_first card         is pointer to first card on stack on which cards should be moved
/// @param pointer_on_card_to_move       last card in group of cards to move.
/// @return bool
//
int counter = 1;
int analysePossibilityOfMovingMoreCards
  (struct _Stacks_ *pointer_on_card_to_move,
   struct _Stacks_ *pointer_to_first_card)
{
  int bool = 1; /// 1 for TRUE
                /// 0 for FALSE
  struct _Stacks_ *mark_beginn = pointer_on_card_to_move;
  struct _Stacks_ *mark_end = pointer_on_card_to_move;
  int counter = 0;

  while ((mark_end->next != NULL) && (mark_end->rang != 0))
  {
    mark_end = mark_end->next;
  }
  mark_end = mark_end->previous;

  struct _Stacks_ *mark_end_help_ptr = mark_end;

  while(mark_end != mark_beginn)
  {
    if(((mark_end->previous->rang - mark_end->rang != 1) ||
       mark_end->previous->color == mark_end->color))
    {
      bool = 0;
      return bool;
    }
    mark_end = mark_end->previous;
  }

  if(bool == 1)
  {
    while(mark_beginn != mark_end_help_ptr->next)
    {
      pointer_to_first_card = pointer_to_first_card->next;

      pointer_to_first_card->rang = mark_beginn->rang;
      mark_beginn->rang = 0;
      pointer_to_first_card->color = mark_beginn->color;
      mark_beginn->color = ' ';

      mark_beginn = mark_beginn->next;
    }
  }
  return bool;
}

///------------------------------------------------------------------------------
/// Whenever input has 5 words than this function is called.
/// If input has form: move <color> <value> to <stacknumber>,
/// than this function finds wanted card and checks if command is under game rules.
/// If move makes sense than card/s are moved and prints out state of each stack
/// and waits for new command to be entered.
///
/// This function does more-less everything what is under "move <color> <value> to <stacknumber>"
/// part this task description.
///
/// @param user_input command that user entered.
/// @return different return values, depending on command.
/// Please look at task description under "Return Values" for more about return values used in this part of code.
/// Task description could be found on the beginning of this code in "Introduction" section.
//
ReturnValues isValidMoveCommand(char *user_input,
                                struct _Stacks_ *array_of_head_nodes)
{
  /// U ovom dijelu prvo provjeri da li je komanda ispravno usisana, tj. da li
  /// ima format: move <color> <rang> to <stack number>\n ?!
  int bool_is_valid_command = 0;
  int bool;

  char move[] = "MOVE ";
  char to[] = " TO ";
  char black[] = " BLACK ";
  char red[] = " RED ";
  char A[] = " A ";
  char K[] = " K ";
  char Q[] = " Q ";
  char J[] = " J ";

  char input_col;

  char *move_place = strstr(user_input, move);
  char *to_place = strstr(user_input, to);
  char *black_place = strstr(user_input, black);
  char *red_place = strstr(user_input, red);
  char *A_place = strstr(user_input, A);
  char *K_place = strstr(user_input, K);
  char *Q_place = strstr(user_input, Q);
  char *J_place = strstr(user_input, J);

  /// When there are no words "move" or "to" or "red/black":
  if((move_place == NULL) || (to_place == NULL) ||
    (red_place == NULL && black_place == NULL))
  {
    printErrorMessages(INVALID_GAME_COMMAND); /// Exit function and print error
    return INVALID_GAME_COMMAND;
  }

  int move_sentence_position = 0;
  int red_sentence_position = 0;
  int black_sentence_position = 0;
  int to_sentence_position = 0;
  int A_sentence_position = 0;
  int K_sentence_position = 0;
  int Q_sentence_position = 0;
  int J_sentence_position = 0;

  move_sentence_position = (int)move_place;
  black_sentence_position = (int)black_place;
  red_sentence_position = (int)red_place;
  A_sentence_position = (int)A_place;
  K_sentence_position = (int)K_place;
  Q_sentence_position = (int)Q_place;
  J_sentence_position = (int)J_place;
  to_sentence_position = (int)to_place;

  int rang = 0;
  int stack_destination;

  /// MOVE; TO; RED/BLACK are present words,
  /// now check if they have correct positions(order).
  if(black_place == NULL)
  {
    if ((move_sentence_position < red_sentence_position) &&
        (red_sentence_position < to_sentence_position))
    {
      //continue;
    }
    else
    {
      printErrorMessages(INVALID_GAME_COMMAND);
      return INVALID_GAME_COMMAND;
    }
  }
  else if(red_place == NULL)
  {
    if ((move_sentence_position < black_sentence_position) &&
        (black_sentence_position < to_sentence_position))
    {
     // continue;
    }
    else
    {
      printErrorMessages(INVALID_GAME_COMMAND);
      return INVALID_GAME_COMMAND;
    }
  }

  if((A_place == NULL) && (K_place == NULL) && (Q_place == NULL) &&
    (J_place == NULL))
  {
    if(red_place != NULL)
    {
      rang = findRangNumbersInCommand((red_place + 4), to_place);
      if(rang < 2 || rang >= 11)
      {
        printErrorMessages(INVALID_GAME_COMMAND);
        return  INVALID_GAME_COMMAND;
      }
    }
    else if(black_place != NULL)
    {
      rang = findRangNumbersInCommand((black_place + 6), to_place);
      if(rang < 2 || rang >= 11)
      {
        printErrorMessages(INVALID_GAME_COMMAND);
        return  INVALID_GAME_COMMAND;
      }
    }
  }
  else if( A_place != NULL)
    rang = 14;
  else if( K_place != NULL)
    rang = 13;
  else if( Q_place != NULL)
    rang = 12;
  else if( J_place != NULL)
    rang = 11;


  stack_destination = findStackNumberInCommand((to_place + 3));
  if(stack_destination < 1 || stack_destination > 6)
  {
    printErrorMessages(INVALID_GAME_COMMAND);
    return INVALID_GAME_COMMAND;
  }


  if(red_place != NULL)
    input_col = 'R';
  else if(black_place != NULL)
    input_col = 'B';

  struct _Stacks_ *pointer_to_first_card = findFirstCardOnStackNumber
                                           (array_of_head_nodes,
                                            stack_destination);

  struct _Stacks_ *pointer_on_card_to_be_moved = findCard(array_of_head_nodes
                                                          , rang, input_col);

  /// If this part of function is reached than it means that command has form
  ///  move <color> <value> to <stacknumber> .
  /// Now it is only up to validity of move or, in other words, does wanted move
  /// respects game rules.
  /// If does, than move will be done and each stack will be printed.

  /// User wants to move card on stack 5/6
  /// -> if 5 or 6 are empty, than first card has to be B/R A!
  if(stack_destination == 5 || stack_destination == 6)
  {
    /// When user wants to move A
    if(rang == 14 && (pointer_on_card_to_be_moved ->next == NULL ||
      //(pointer_on_card_to_be_moved->next)->next->rang == 0))
      (pointer_on_card_to_be_moved->next->rang == 0)))
    {
      pointer_to_first_card->rang = 14;
      pointer_to_first_card->color =  pointer_on_card_to_be_moved->color;
      pointer_on_card_to_be_moved->rang = 0;
      pointer_on_card_to_be_moved->color = ' ';
      printStacks(array_of_head_nodes);
    }
    ///When user wants to move some other card
    else if((rang < 14) && ((pointer_on_card_to_be_moved->next == NULL) ||
           (pointer_on_card_to_be_moved->next->rang == 0)))
    {
      /// Order of cards must be: A,2,3,4,5,...,Q,K and color must be same for each card!
      /// Case when A is already on 5/6, next card color must be same color as A
      ///                                next card rang  must be 2;
      if(((pointer_to_first_card->rang == 14) &&
           pointer_on_card_to_be_moved->rang == 2) &&
        (pointer_to_first_card->color == pointer_on_card_to_be_moved->color))
      {
        pointer_to_first_card->next->rang = 2;
        pointer_to_first_card->next->color = pointer_on_card_to_be_moved->color;
        pointer_on_card_to_be_moved->rang = 0;
        pointer_on_card_to_be_moved->color = ' ';
        printStacks(array_of_head_nodes);
      }
      else if(((pointer_on_card_to_be_moved->rang -
                  pointer_to_first_card->rang) == 1) &&
        (pointer_on_card_to_be_moved->color == pointer_to_first_card->color))
      {
        pointer_to_first_card->next->rang = pointer_on_card_to_be_moved->rang;
        pointer_to_first_card->next->color =
                              pointer_on_card_to_be_moved->color;
        pointer_on_card_to_be_moved->rang = 0;
        pointer_on_card_to_be_moved->color = ' ';
        printStacks(array_of_head_nodes);
      }
      else
      {
        printErrorMessages(INVALID_COMMAND_MOVE);
        return INVALID_COMMAND_MOVE;
      }
    }
    else
    {
      printErrorMessages(INVALID_COMMAND_MOVE);
      return INVALID_COMMAND_MOVE;
    }
  }
  /// Card should be moved on stack 1/2/3/4
  if(stack_destination >= 1 && stack_destination <= 4)
  {
    /// Move one card
    if((( pointer_to_first_card->rang - pointer_on_card_to_be_moved->rang)
          == 1) &&
      (pointer_on_card_to_be_moved->color != pointer_to_first_card->color) &&
      (pointer_on_card_to_be_moved->next == NULL))
    {
      pointer_to_first_card->next->rang = pointer_on_card_to_be_moved->rang;
      pointer_to_first_card->next->color = pointer_on_card_to_be_moved->color;
      pointer_on_card_to_be_moved->rang = 0;
      pointer_on_card_to_be_moved->color = ' ';
      printStacks(array_of_head_nodes);
    }
    else if((( pointer_to_first_card->rang - pointer_on_card_to_be_moved->rang)
               == 1) &&
      (pointer_on_card_to_be_moved->color != pointer_to_first_card->color) &&
      (pointer_on_card_to_be_moved->next->rang == 0))
    {
      pointer_to_first_card->next->rang = pointer_on_card_to_be_moved->rang;
      pointer_to_first_card->next->color = pointer_on_card_to_be_moved->color;
      pointer_on_card_to_be_moved->rang = 0;
      pointer_on_card_to_be_moved->color = ' ';
      printStacks(array_of_head_nodes);
    }
    /// When user wants to move more than 1 card
    else if((( pointer_to_first_card->rang - pointer_on_card_to_be_moved->rang)
               == 1) &&
      (pointer_on_card_to_be_moved->color != pointer_to_first_card->color) &&
      (pointer_on_card_to_be_moved->next->rang != 0))
    {
      bool = analysePossibilityOfMovingMoreCards(pointer_on_card_to_be_moved,
                                                 pointer_to_first_card);
      if(bool == 1)
      {
        printStacks(array_of_head_nodes);
        return ALL_OK;
      }
      else
      {
        printErrorMessages(INVALID_COMMAND_MOVE);
        return INVALID_COMMAND_MOVE;
      }
    }
    /// When user wants to move card on empty Stack
    else if(pointer_to_first_card->rang == 0 &&
      pointer_on_card_to_be_moved->next == NULL)
    {
      pointer_to_first_card->rang = pointer_on_card_to_be_moved->rang;
      pointer_to_first_card->color = pointer_on_card_to_be_moved->color;
      pointer_on_card_to_be_moved->rang = 0;
      pointer_on_card_to_be_moved->color = ' ';
      printStacks(array_of_head_nodes);
    }
    else if(pointer_to_first_card->rang == 0 &&
      pointer_on_card_to_be_moved->next->rang == 0)
    {
      pointer_to_first_card->rang = pointer_on_card_to_be_moved->rang;
      pointer_to_first_card->color = pointer_on_card_to_be_moved->color;
      pointer_on_card_to_be_moved->rang = 0;
      pointer_on_card_to_be_moved->color = ' ';
      printStacks(array_of_head_nodes);
    }
    else
    {
      printErrorMessages(INVALID_COMMAND_MOVE);
      return INVALID_COMMAND_MOVE;
    }
  }
  return ALL_OK;
}

///------------------------------------------------------------------------------
/// Before each command function prints "esp> " on STDOUT which implies
/// that user needs to enter a command.
/// Each entered command is later processed and function returns EXIT after "exit",
/// ALL_OK after "help" or " move <color> <value> to <stacknumber> ".
/// If command is invalid than function return INVALID_COMMAND and
/// INVALID_MOVE_COMMAND if move command doesn't respect game rules.
///
/// @param array_of_head_nodes array of pointers on bottom of each stack;
/// @return some of ReturnValues, depends on input.
//
ReturnValues playGame(struct _Stacks_* array_of_head_nodes)
{
  long unsigned counter1 = 0;
  char *user_input = (char*)malloc(sizeof(char) * 15);
  if(user_input == NULL)
    return NO_MEMORY;
  int temp_variable;
  int number_of_words_in_input = 0;
  int check_return;
  ReturnValues return_value;
  struct _Stacks_ *first_card_stack1 = (array_of_head_nodes + 5);
  struct _Stacks_ *last_card_stack1 = (array_of_head_nodes + 5);
  struct _Stacks_ *first_card_stack2 = (array_of_head_nodes + 6);
  struct _Stacks_ *last_card_stack2 = (array_of_head_nodes + 6);

  while(last_card_stack1->next->card_number != 13)
  {
    last_card_stack1 = last_card_stack1->next;
    last_card_stack2 = last_card_stack2->next;
  }

  printf("esp> ");
  while((temp_variable = getchar()) != '\n')
  {
    user_input = realloc(user_input, (sizeof(char) * ((counter1 + 5))));
    *(user_input + counter1) = (char)toupper((char)temp_variable);
    counter1++;
  }
  user_input[counter1] = '\0';

  number_of_words_in_input = countWords(user_input);
  if(number_of_words_in_input == 1)
  {
    return_value = checkCommandTypeWhenOneWord(user_input);
    if(return_value == EXIT)
    {
      free(user_input);
      return EXIT;
    }
    else
    {
      free(user_input);
      return ALL_OK;
    }
  }
  else if(number_of_words_in_input == 5)
  {
    return_value = isValidMoveCommand(user_input, array_of_head_nodes);
    free(user_input);
    if((first_card_stack1->rang == 14) &&
       (last_card_stack2->rang == 13) &&
       (first_card_stack2->rang == 14) &&
       (last_card_stack2->rang = 13))
      return EXIT;
    return return_value;
  }
  else
  {
    free(user_input);
    printErrorMessages(INVALID_GAME_COMMAND); /// Exit function and print error
    return INVALID_GAME_COMMAND;
  }

  free(user_input);
  return ALL_OK;
}

ReturnValues main(int argc, char *argv[])
{
  char *loaded_cards;
  ReturnValues return_value = ALL_OK;

  if(argc != 2)
  {
    printErrorMessages(INVALID_FILE);
    return INVALID_FILE;
  }

  loaded_cards = loadCardsFromFile(argv[1]);
  if(loaded_cards == NULL)
  {
    free(loaded_cards);
    printErrorMessages(INVALID_FILE);
    return INVALID_FILE;
  }
  struct _Stacks_ *array_of_head_nodes;

  array_of_head_nodes = loadCardsOnStacks(loaded_cards);
  if(array_of_head_nodes == NULL)
    return printErrorMessages(NO_MEMORY);
  printStacks(array_of_head_nodes);
  while(return_value != EXIT)
  {
    return_value = playGame(array_of_head_nodes);
  }
  free(loaded_cards);
  freeMemory(array_of_head_nodes);

  return ALL_OK;
}

