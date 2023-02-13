/**
 * \~english @file except.h
 * \~english @author Quentin (quentin.horgues@outlook.fr)
 * \~english @brief Module to simulate an error handling based on a switch
 * \~english @version 0.1
 * \~english @date 2022-02-23
 * 
 * \~english example of use by testing an error :
 * @code
 * fprintf(stdout, "Hello World");
 * try
 * {
 * catch(ERROR_ILLEGUAL_BYTE_SEQUENCE): // In case a wide character code that does not match a valid character was detected
 * perror("fprintf");
 * break;
 * 
 * } endTry; // Exit the try IMPORTANT reset EXCEPTION to 0 with endTry;
 * @endcode
 * \~english example by retrieving all the exceptions :
 * @code
 * fprintf(stdout, "Hello World");
 * try
 * {
 * catchAllExcept: // Catch all errors
 * perror("fprintf");
 * break;
 * } endTry;
 * @endcode
 * \~english and here is a complete example:
 * @code 
 * #include <stdio.h>
 * #include "except.h"
 * 
 * void foo(int a)
 * {
 * if (a > 10)
 * {
 * throw(ERROR_INVALID_ARGUMENT, NO_VALUE); // throw an invalid argument exception
 * }
 * printf("%d\n", a);
 * returnExcept
 * // Code
 * }
 * 
 * int main(void)
 * {
 * foo(12);
 * try
 * {
 * catch(ERROR_INVALID_ARGUMENT): // If the error is an invalid argument
 * perror("Error argument in function f");
 * break;
 * catchAllExcept: // If this is another error
 * perror("Error in function f");
 * break;
 * endTry;
 * return 0;
 * }
 * @endcode
 * 
 * \~english @copyright Copyright (c) 2022 by Quentin Horgues
 * 
 * 
 *
 * \~french @file except.h
 * \~french @author Quentin (quentin.horgues@outlook.fr)
 * \~french @brief Module permettant de simuler une gestion d'erreur basé sur un switch
 * \~french @version 0.1
 * \~french @date 2022-02-23
 * 
 * \~french exemple d'utilistation en testant une erreur :
 * @code
 * fprintf(stdout, "Hello World");
 * try
 * {
 *     catch(ERROR_ILLEGUAL_BYTE_SEQUENCE): // Dans le cas d'un code de caractères larges qui ne correspond pas à un caractère valide a été détecté
 *          perror("fprintf");
 *          break;
 * 
 * } endTry; // On quitte le try IMPORTANT on réinitialise EXCEPTION à 0 avec endTry;
 * @endcode
 * \~french exemple en recuperant toutes les exceptions :
 * @code
 * fprintf(stdout, "Hello World");
 * try
 * {
 *     catchAllExcept: // On recupere toutes les erreurs
 *          perror("fprintf");
 *          break;
 * } endTry;
 * @endcode
 * \~french et voici un exemple complet :
 * @code 
 * #include <stdio.h>
 * #include "except.h"
 * 
 * void foo(int a)
 * {
 *     if (a > 10)
 *     {
 *         throw(ERROR_INVALID_ARGUMENT, NO_VALUE); // On lance une exception d'argument invalide
 *     }
 *     printf("%d\n", a);
 *     returnExcept
 *     // Code
 * }
 * 
 * int main(void)
 * {
 *     foo(12);
 *     try
 *     {
 *         catch(ERROR_INVALID_ARGUMENT): // Si l'erreur est un argument invalide
 *             perror("Error argument in function f");
 *             break;
 *         catchAllExcept: // Si c'est une autre erreur
 *             perror("Error in function f");
 *             break;
 *     } endTry;
 *     return 0;
 * }
 * @endcode
 * 
 * \~french @copyright Copyright (c) 2022 par Quentin Horgues
 */
#ifndef EXCEPT_H
#define EXCEPT_H
#include <errno.h>


/**
 * @def EXCEPTION
 * \~english @brief contains the error code
 * \~french @brief contient le code d'erreur
 */
#define EXCEPTION errno

/**
 * @def throw
 * \~english @brief throw une exception 
 * \~french @brief lance une exception 
 */
#define throw(ERROR_XXX, return_value) \
    {                                  \
        EXCEPTION = ERROR_XXX;             \
        return return_value;           \
    }

/**
 * @def NO_VALUE
 * \~english @brief Use in the throw/returnExcept of a function returning void
 * \~french @brief Utiliser dans le throw/returnExcept d'une fonction retournant void
 */
#define NO_VALUE

#define try if(EXCEPTION) { switch (EXCEPTION)

#define catch case

#define endTry    \
    EXCEPTION = 0; \
    }

#define catchAllExcept default

/**
 * @def no_try
 * \~english @brief If no test is performed, EXCEPTION is reset to 0
 * \~french @brief Si aucun teste n'est effectué on reinitialise EXCEPTION a 0
 */
#define no_try EXCEPTION = 0

/**
 * \~english @def returnExcept
 * \~english @brief Raises an exception to the calling function
 * 
 * \~english In simple use
 * @code
 * fprintf("%d\n", 8);
 * returnExcept(NO_VALUE);
 * @endcode
 * 
 * \~english @warning It is necessary to perform memory releases before doing a returnExcept
 * @code
 * int* tabInt = malloc(sizeof(int)*8);
 * returnExcept(NO_VALUE);
 * int* tab2 = malloc(sizeof(int)*10);
 * if (tab2 == NULL)
 * {
 * free(tabInt);
 * return;
 * }
 * @endcode
 * \~english Since we have to free the memory we do the returnExcept manually
 * 
 * 
 * \~french @def returnExcept
 * \~french @brief Remonte une exception a la fonction appelante
 * 
 * \~french Dans une utilisation simple
 * @code
 * fprintf("%d\n", 8);
 * returnExcept(NO_VALUE);
 * @endcode
 * 
 * \~french @warning Il est necessaire de réaliser les liberations memoire avant de faire un returnExcept
 * @code
 * int* tabInt = malloc(sizeof(int)*8);
 * returnExcept(NO_VALUE);
 * int* tab2 = malloc(sizeof(int)*10);
 * if (tab2 == NULL)
 * {
 *     free(tabInt);
 *     return;
 * }
 * @endcode
 * \~french Vu que l'on doit liberer la memoire on realise le returnExcept manuelement
 */
#define returnExcept(return_value) \
    {                               \
        if (EXCEPTION)                  \
        {                           \
            return return_value;    \
        }                           \
    }

#define NO_ERROR 0
#define ERROR_OPERATION_NOT_PERMITTED 1
#define ERROR_NO_SUCH_FILE_OR_DIRECTORY 2
#define ERROR_NO_SUCH_PROCESS 3
#define ERROR_INTERRUPTED_FUNCTION_CALL 4
#define ERROR_INPUT_OUTPUT_ERROR 5
#define ERROR_NO_SUCH_DEVICE_OR_ADDRESS 6
#define ERROR_ARG_LIST_TOO_LONG 7
#define ERROR_EXEC_FORMAT_ERROR 8
#define ERROR_BAD_FILE_DESCRIPTOR 9
#define ERROR_NO_CHILD_PROCESSES 10
#define ERROR_RESOURCE_TEMPORARILY_UNAVAILABLE 11
#define ERROR_NOT_ENOUGH_SPACE 12
#define ERROR_PERMISSION_DENIED 13
#define ERROR_BAD_ADDRESS 14
#define ERROR_UNKNOWN_ERROR 15
#define ERROR_RESOURCE_DEVICE 16
#define ERROR_FILE_EXISTS 17
#define ERROR_IMPROPER_LINK 18
#define ERROR_NO_SUCH_DEVICE 19
#define ERROR_NOT_A_DIRECTORY 20
#define ERROR_IS_A_DIRECTORY 21
#define ERROR_INVALID_ARGUMENT 22
#define ERROR_TOO_MANY_OPEN_FILES_IN_SYSTEM 23
#define ERROR_TOO_MANY_OPEN_FILES 24
#define ERROR_INAPPROPRIATE_I_O_CONTROL_OPERATION 25
#define ERROR_FILE_TOO_LARGE 27
#define ERROR_NO_SPACE_LEFT_ON_DEVICE 28
#define ERROR_INVALID_SEEK 29
#define ERROR_READ_ONLY_FILE_SYSTEM 30
#define ERROR_TOO_MANY_LINKS 31
#define ERROR_BROKEN_PIPE 32
#define ERROR_DOMAIN_ERROR 33
#define ERROR_RESULT_TOO_LARGE 34
#define ERROR_RESOURCE_DEADLOCK_AVOIDED 36
#define ERROR_FILENAME_TOO_LONG 38
#define ERROR_NO_LOCKS_AVAILABLE 39
#define ERROR_FUNCTION_NOT_IMPLEMENTED 40
#define ERROR_DIRECTORY_NOT_EMPTY 41
#define ERROR_ILLEGAL_BYTE_SEQUENCE 42
#define ERROR_ADDRESS_IN_USE 100
#define ERROR_ADDRESS_NOT_AVAILABLE 101
#define ERROR_ADDRESS_FAMILY_NOT_SUPPORTED 102
#define ERROR_CONNECTION_ALREADY_IN_PROGRESS 103
#define ERROR_BAD_MESSAGE 104
#define ERROR_OPERATION_CANCELED 105
#define ERROR_CONNECTION_ABORTED 106
#define ERROR_CONNECTION_REFUSED 107
#define ERROR_CONNECTION_RESET 108
#define ERROR_DESTINATION_ADDRESS_REQUIRED 109
#define ERROR_HOST_UNREACHABLE 110
#define ERROR_IDENTIFIER_REMOVED 111
#define ERROR_OPERATION_IN_PROGRESS 112
#define ERROR_ALREADY_CONNECTED 113
#define ERROR_TOO_MANY_SYMBOLIC_LINK_LEVELS 114
#define ERROR_MESSAGE_SIZE 115
#define ERROR_NETWORK_DOWN 116
#define ERROR_NETWORK_RESET 117
#define ERROR_NETWORK_UNREACHABLE 118
#define ERROR_NO_BUFFER_SPACE 119
#define ERROR_NO_MESSAGE_AVAILABLE 120
#define ERROR_NO_LINK 121
#define ERROR_NO_MESSAGE 122
#define ERROR_NO_PROTOCOL_OPTION 123
#define ERROR_NO_STREAM_RESOURCES 124
#define ERROR_NOT_A_STREAM 125
#define ERROR_NOT_CONNECTED 126
#define ERROR_STATE_NOT_RECOVERABLE 127
#define ERROR_NOT_A_SOCKET 128
#define ERROR_NOT_SUPPORTED 129
#define ERROR_OPERATION_NOT_SUPPORTED 130
#define ERROR_VALUE_TOO_LARGE 132
#define ERROR_OWNER_DEAD 133
#define ERROR_PROTOCOL_ERROR 134
#define ERROR_PROTOCOL_NOT_SUPPORTED 135
#define ERROR_WRONG_PROTOCOL_TYPE 136
#define ERROR_STREAM_TIMEOUT 137
#define ERROR_TIMED_OUT 138
#define ERROR_TEXT_FILE_BUSY 139
#define ERROR_OPERATION_WOULD_BLOCK 140

#endif