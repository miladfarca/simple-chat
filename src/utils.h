#define BOOL unsigned char
#define TRUE 1
#define FALSE 0

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

// Network
#define PORT 61753

// Encryption
#define DEFAULT_KEY "not_safe_please_use_your_own_key" // 32 bytes.
#define KEY_LENGTH 32
#define IV_LENGTH 16

// Globals
extern char username[MAX_USER_NAME_LENGTH];
extern unsigned char key[KEY_LENGTH];
extern unsigned char iv[IV_LENGTH];

// Functions
void init_env();
void set_username_from_sys();
void set_username(char *username);
char *get_username();
void set_key(char *new_key);
void end();