#include <boost/test/unit_test.hpp>

#include "ethcrypto/key/KeyGenerator.hpp"
#include "ethcrypto/signature/Signer.hpp"
#include "ethcrypto/signature/SignatureValidator.hpp"
#include "ethcrypto/hash/Sha256.hpp"
#include "ethcrypto/serialization/Literal.hpp"

#include <iostream>

using namespace Ethereum;


BOOST_AUTO_TEST_SUITE(KeyGeneratorTest)

BOOST_AUTO_TEST_CASE(generateSecret)
{
    PrivateKeyGenerator generator;
    PublicKeyFactory factory;
    Sha256 hasher;
    Signer signer;
    SignatureValidator validator;
    PrivateKey privateKey = generator.generate();
    PublicKey pubKey = factory.createFromSecret(privateKey);
    const char * text = "test here";
    Data hash = hasher.hash(text, text+strlen(text));
    Signature signature = signer.sign(privateKey, hash);

    BOOST_REQUIRE(validator.verify(pubKey, signature, hash));
}




BOOST_AUTO_TEST_CASE(generate)
{
    KeyGenerator generator;
    Sha256 hasher;
    Signer signer;
    SignatureValidator validator;

    KeyPair pair = generator.generate();

    const char * text = "test here";
    Data hash = hasher.hash(text, text+strlen(text));
    Signature signature = signer.sign(pair.getPrivateKey(), hash);

    BOOST_REQUIRE(validator.verify(pair.getPublicKey(), signature, hash));
}









BOOST_AUTO_TEST_SUITE_END()
