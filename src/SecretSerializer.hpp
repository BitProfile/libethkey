#pragma once

#include "Secret.hpp"
#include "SecuredSecret.hpp"

#include "Base58Encoder.hpp"
#include "Base16Encoder.hpp"

#include "Secp256k1ContextPtr.hpp"

namespace BitCrypto{


template<class Encoder>
class SecretSerializer
{
    public:
    
        SecretSerializer();
        SecretSerializer(const Secp256k1ContextPtr &);
    
        std::string serialize(const Secret &) const;
        Secret unserialize(const std::string &) const;

        template<class Cipher>
        std::string serialize(const SecuredSecret<Cipher> &) const;

        template<class Cipher>
        SecuredSecret<Cipher> unserialize(const std::string &, const Cipher &) const;


    private:
       Secp256k1ContextPtr _context;

};



typedef SecretSerializer<Base58Encoder> Base58SecretSerializer;
typedef SecretSerializer<Base16Encoder> Base16SecretSerializer;


}

#include "SecretSerializer.ipp"