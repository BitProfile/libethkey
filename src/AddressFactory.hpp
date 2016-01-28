#pragma once 

#include "PublicKey.hpp"
#include "Address.hpp"

#include "encoding/Base16Encoder.hpp"
#include "CompressedPoint.hpp"
#include "serialization/BinaryPublicKeySerializer.hpp"
#include "DoubleHash.hpp"
#include "Sha3.hpp"
#include "Literal.hpp"


namespace Ethereum{



class AddressFactory 
{
    public:

        bool createFromPublicKey(const PublicKey &, Address &) const;
        Address createFromPublicKey(const PublicKey &) const;

        bool createFromString(const std::string &, Address &) const;
        Address createFromString(const std::string &) const;

        bool createFromString(const char *, size_t, Address &) const;
        Address createFromString(const char *, size_t ) const;
};



}