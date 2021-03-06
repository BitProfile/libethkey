#include <boost/test/unit_test.hpp>


#include "ethcrypto/serialization/Literal.hpp"
#include "ethcrypto/key/PublicKeyFactory.hpp"
#include "ethcrypto/key/Address.hpp"

using namespace Ethereum;

BOOST_AUTO_TEST_SUITE(AddressTest)



BOOST_AUTO_TEST_CASE(fromPublicKey)
{
    PublicKeyFactory factory;
    PrivateKey secret = Literal<PrivateKey>("187900ed539bce26777e806b63a732aac8829ccceea9ac0288ac3457cb1accd8");
    PublicKey pubKey = factory.createFromSecret(secret);
    Address address(pubKey);
    BOOST_REQUIRE_EQUAL(address.toStringCheckSum(), "0x0f3947A26863e72193756090cf5190E9Ac42ce70");
}

BOOST_AUTO_TEST_CASE(fromPublicKey2)
{
    PublicKeyFactory factory;
    PrivateKey secret = Literal<PrivateKey>("6264896b11f6987100129a2667c28e29acca23863ba9dae0c67fa25296f95f24");
    PublicKey pubKey = factory.createFromSecret(secret);
    Address address(pubKey);
    BOOST_REQUIRE_EQUAL(address.toStringCheckSum(), "0x4463FD4DD1993Fc5Beeb51554fdEFa97abEDe8CC"); 
}



BOOST_AUTO_TEST_SUITE_END()
