// Data sizes in bytes (total 2048 bytes).
//  2B      32B                 2014B
// ---- ---------- ----------------------------------
//  MD     NAME                 TEXT
#define MAX_USER_NAME_LENGTH 32
#define MAX_INPUT_LENGTH 2014
#define MAX_INPUT_LENGTH_S "2014"
#define MAGIC_DATA_LENGTH 2
#define MAGIC_DATA 0xAAAA
#define MAX_DATA_LENGTH 2048
#define MAX_ADDRESS_LEGNTH 15 // char size
#define MAX_PORT_LEGNTH 5     // char size

// Generic
#define BOOL unsigned char
#define TRUE 1
#define FALSE 0
#define ADDRESS INADDR_BROADCAST
#define PORT 61753
#define SCRC_FILE_PATH "/.scrc"

// Encryption
#define DEFAULT_KEY "not_safe_please_use_your_own_key" // 32 bytes.
#define KEY_LENGTH 32
#define IV_LENGTH 16

// Globals
extern BOOL initialized;
extern char username[MAX_USER_NAME_LENGTH];
extern unsigned char key[KEY_LENGTH];
extern unsigned char iv[IV_LENGTH];
extern unsigned int address;
extern unsigned short port;

// Functions
BOOL env_initialized();
void init_env();
void maybe_read_scrc();
void set_username_from_sys();
void set_username(char *username);
char *get_username();
void set_key(char *new_key);
BOOL set_address(char *new_address);
void set_port(char *new_port);
void print_info();
void end();
