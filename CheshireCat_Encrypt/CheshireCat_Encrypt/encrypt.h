#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

struct public_key_class;

int fileEncrypt(const char*, const struct public_key_class*);
int folderEncrypt(const char*, const struct public_key_class*);
int isDirectory(const char*);

#endif // ENCRYPT_H_INCLUDED
