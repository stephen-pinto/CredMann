#include "pch.h"
#include "PasswordStrengthner.h"

using namespace CredMannLib::Password;
using namespace CryptoPP;
using namespace std;

SecByteBlock PasswordStrengthner::GenerateKey_PKCS5_PBKDF2(const SecByteBlock& password,const SecByteBlock& salt, size_t iterations)
{
    SecByteBlock key(SHA256::DIGESTSIZE);
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    pbkdf.DeriveKey(key, key.size(), 0, password.data(), password.size(), salt.data(), salt.size(), iterations, 0.0f);
    return key;
}
