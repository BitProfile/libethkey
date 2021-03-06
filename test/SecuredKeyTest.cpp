#include <boost/test/unit_test.hpp>

#include "ethcrypto/cipher/AesCipher.hpp"
#include "ethcrypto/cipher/Scrypt.hpp"


#include "ethcrypto/key/Address.hpp"
#include "ethcrypto/serialization/Literal.hpp"
#include "ethcrypto/key/PublicKeyFactory.hpp"
#include "ethcrypto/key/SecuredKey.hpp"

using namespace Ethereum;

BOOST_AUTO_TEST_SUITE(SecuredKeyPairTest)

typedef AesCipher<Scrypt> Cipher;

BOOST_AUTO_TEST_CASE(fromSecret)
{
    Ethereum::PrivateKey secret = Literal<Ethereum::PrivateKey>("6264896b11f6987100129a2667c28e29acca23863ba9dae0c67fa25296f95f24");
    Ethereum::SecuredKey<Cipher> key(secret, Cipher(MakeRandomIV(), MakeRandomScryptParams()), "asdasd123");
    BOOST_REQUIRE_EQUAL(key.getAddress().toStringCheckSum(), "0x4463FD4DD1993Fc5Beeb51554fdEFa97abEDe8CC");
    Ethereum::PrivateKey secret2 = key.getPrivateKey().unlock("asdasd123");
    BOOST_REQUIRE(secret2==secret);
    BOOST_REQUIRE_EQUAL(Literal(secret2), "6264896b11f6987100129a2667c28e29acca23863ba9dae0c67fa25296f95f24");
}

BOOST_AUTO_TEST_CASE(keyUnlock)
{
    Ethereum::PrivateKey secret = Literal<Ethereum::PrivateKey>("6264896b11f6987100129a2667c28e29acca23863ba9dae0c67fa25296f95f24");
    Ethereum::SecuredKey<Cipher> key(secret, Cipher(MakeRandomIV(), MakeRandomScryptParams()), "asdasd123");
    BOOST_REQUIRE_EQUAL(key.getAddress().toStringCheckSum(), "0x4463FD4DD1993Fc5Beeb51554fdEFa97abEDe8CC");

    Ethereum::SecuredKey<Cipher> key2(key.getPrivateKey().unlock("asdasd123"), Cipher(MakeRandomIV(), MakeRandomScryptParams()), "asdasd123");
    BOOST_REQUIRE_EQUAL(key2.getAddress().toStringCheckSum(), "0x4463FD4DD1993Fc5Beeb51554fdEFa97abEDe8CC");

}


BOOST_AUTO_TEST_SUITE_END()
