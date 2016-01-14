#pragma once

#include <stdint.h>

#include "secp256k1/secp256k1.h"

#include "Secp256k1ContextPtr.hpp"
#include "Data.hpp"


namespace BitCrypto{


class PubKey
{
    public:
        typedef  uint8_t * Iterator;
        typedef const uint8_t * ConstIterator;

    public:
        PubKey();
        PubKey(const PubKey &);
        PubKey(const Data &);
        PubKey(const Secp256k1ContextPtr &);
        PubKey(const Data &, const Secp256k1ContextPtr &);

        operator secp256k1_pubkey & ();
        operator const secp256k1_pubkey & () const;
        secp256k1_pubkey * operator & ();
        const secp256k1_pubkey * operator & () const;
        
        uint8_t operator [](int i) const;
        const uint8_t * getData() const;

        ConstIterator begin() const;
        ConstIterator end() const;

        Iterator begin();
        Iterator end();

    private:
        secp256k1_pubkey _data;
        Secp256k1ContextPtr _context;

};



}
