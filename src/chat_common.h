#ifndef CHAT_COMMON_H
#define CHAT_COMMON_H

#include <stdbool.h>
#include <glib.h>

/* Secure socket layer headers */
#include <openssl/ssl.h>
#include <openssl/err.h>


#define MAX_PACKET_SIZE 1000 // maximum size of packet sent by server/client in bytes
#define MAX_IDLE_TIME 180 // in seconds
#define MAX_USERNAME_LENGTH 32 // characters
#define MAX_PASSWORD_LENGTH 32 // characters


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


typedef enum ErrorCode {
	//ROOM_NOT_FOUND,  // not used, since user will create the room if it does not exist
	WRONG_PASSWORD,
	WRONG_USERNAME,
	UNKNOWN
} ErrorCode;


//string "Room [%s] was not found.",  // not used, since user will create the room if it does not exist
#define WRONG_PASSWORD_MSG "Authentication failed (wrong password). Remaining tries: %d."
#define WRONG_USERNAME_MSG "Authentication failed (wrong username). Remaining tries: %d."
#define UNKNOWN_ERROR_MSG "Unknown error."


extern const char * const error_message_[];


bool read_message(SSL *ssl, GString *message);
void print_colored(char *message, char *color);


// CLIENT_TO_SERVER_OPCODES
typedef enum {
	WHO,      //  /who          # list of all users
	LIST,     //  /list         # list of all rooms
	JOIN,     //  /join <room>
	USER,     //  /user <username> <password>    # login
	SAY,      //  /say <username> <msg>          # private message
	//BYE,    //  /bye   # maybe just close the connection after this command
	MSG,
	GAME,     //  /game <username>
	ROLL,     //  /roll
	ACCEPT,   //  /accept
	DECLINE   //  /decline
} CLIENT_TO_SERVER_OPCODE;


// SERVER_TO_CLIENT_OPCODES
typedef enum {
	ERROR,            // for example - room does not exist, username does not exist, bad password, etc.
	INFO,             // for example "Welcome message"
	CHANGE_ROOM,      // after receiving this message client can set up internal variable with room
	LOGGED_IN,        // after receiving this message client can set up internal variable with username
	ROOM_MESSAGE,     // just print out room message "<OPCODE><USERNAME> <MESSAGE>"
	PRIVATE_MESSAGE,  // private message (client should print that in different way from room messages) "<OPCODE><USERNAME> <MESSAGE>"
	CHALLENGE,        // challenge from another user (game)
	CLIENT_ERROR      // this message is not part of protocol (just for purposes of output formatting)
} SERVER_TO_CLIENT_OPCODE;


#endif