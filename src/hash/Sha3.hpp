#pragma once 

#include <string>

#include "cryptopp/sha3.h"
#include "./detail/CryptoppHasher.hpp"


namespace Ethereum{


typedef CryptoppHasher<CryptoPP::SHA3_256, 32> Sha3;




}

