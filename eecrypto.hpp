#ifndef EECrypto_HPP_
#define EECrypto_HPP_

#include <QString>

class EECrypto
{

public:
    EECrypto();
    ~EECrypto();

    void MakeKey(QString *passPhrase);
    void CipherText(QString *plainText, QString *cipherText);
    bool DecipherText(QString *cipherText, QString *plainText);

private:
    unsigned long long key[256];

};

#endif /* EECrypto_HPP_ */
